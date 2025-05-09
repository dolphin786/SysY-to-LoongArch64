#include "asm/AsmEmitter.h"
#include "ir/IRGenerator.h"

#define REPORT_COMPILER_ERROR_AND_EXIT(msg) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::COMPILER_ERROR, 0, 0); printErrors(); std::exit(0);}while(0)


bool AsmEmitter::outOfImmediateRange(int64_t value)
{
    return value < -2047 || value > 2047;
}

bool AsmEmitter::outOfImmediateRange(int value)
{
    return value < -2047 || value > 2047;
}

 // 线性扫描寄存器分配
void AsmEmitter::linearScanRegisterAllocation(Function* func) {
    // 计算每个指令的编号
    std::map<Instruction*, int> instr_index;
    int index = 0;
    
    // 首先处理函数参数
    int int_reg_count = 0;
    int float_reg_count = 0;
    int stack_offset = 16; // 从16开始（前16字节用于保存$ra和$fp，$fp被设置到保存$fp的位置了）
    
    // 为函数参数分配寄存器或栈空间
    for (auto& arg : func->arguments_) {
        bool is_float = arg->type_->tid_ == Type::FloatTyID;
        
        if (is_float) {
            // 浮点参数
            if (float_reg_count < 8) {
                // 还有可用的浮点寄存器
                std::string reg = "$fa" + std::to_string(float_reg_count);
                reg_map[arg] = reg;
                float_reg_count++;
            } else {
                // 浮点寄存器用完了，参数放在栈上
                stack_map[arg] = stack_offset;
                stack_offset += 8; // 浮点参数占4字节，但在栈上占据8字节空间
            }
        } else {
            // 整型参数
            if (int_reg_count < 8) {
                // 还有可用的整型寄存器
                std::string reg = "$a" + std::to_string(int_reg_count);
                reg_map[arg] = reg;
                int_reg_count++;
            } else {
                // 整型寄存器用完了，参数放在栈上
                stack_map[arg] = stack_offset;
                stack_offset += 8; // 整型参数占4字节，但在栈上占据8字节空间
            }
        }
        
        // 为参数创建初始活跃区间
        live_range_map[arg] = {0, 0}; // 从函数开始就是活跃的
    }
    
    // 第一遍：为每条指令分配索引并计算活跃区间
    for (BasicBlock* bb : func->basic_blocks_) {
        for (Instruction* inst : bb->instr_list_) {
            instr_index[inst] = index++;
            
            if(dynamic_cast<AllocaInst*>(inst))//跳过alloca指令，因为alloca指令的结果是编译期常量，无需分配寄存器
            {
                continue;
            }
            // 记录定义点
            live_range_map[inst] = {index, index};
            
            // 更新操作数的活跃区间结束点
            for (unsigned i = 0; i < inst->num_ops_; i++) {
                Value* operand = inst->get_operand(i);
                if (live_range_map.find(operand) != live_range_map.end()) {
                    live_range_map[operand].second = index;
                }
            }
        }
    }

    // 当前活跃的区间
    std::set<Value*> active;
    
    // 可用的寄存器
    std::set<std::string> free_int_regs(int_regs.begin(), int_regs.end());
    std::set<std::string> free_float_regs(float_regs.begin(), float_regs.end());

    std::set<std::string> non_free_int_regs;
    std::set<std::string> non_free_float_regs;

    std::set<std::string> changed_int_regs;
    std::set<std::string> changed_float_regs;

    
    // 按照活跃区间开始点排序
    std::vector<Value*> sorted_values;
    for (auto& pair : live_range_map) {
        // 跳过已经分配了寄存器或栈空间的函数参数，并将它们插入当前活跃的区间
        if (reg_map.find(pair.first) != reg_map.end() || 
            stack_map.find(pair.first) != stack_map.end()) 
        {
            active.insert(pair.first);

            if(reg_map.find(pair.first) != reg_map.end())
            {
                std::string reg = reg_map[pair.first];
                if(reg[1] == 'f')
                {
                    free_float_regs.erase(reg);
                    non_free_float_regs.insert(reg);
                    changed_float_regs.insert(reg);
                }
                else
                {
                    free_int_regs.erase(reg);
                    non_free_int_regs.insert(reg);
                    changed_int_regs.insert(reg);
                }
                
            }

            continue;
        }
        sorted_values.push_back(pair.first);
    }
    
    std::sort(sorted_values.begin(), sorted_values.end(), 
        [this](Value* a, Value* b) {
            return live_range_map[a].first < live_range_map[b].first;
        });
    
    // 线性扫描算法
    for (Value* value : sorted_values) {
        // 过期活跃区间
        std::vector<Value*> to_remove;
        for (Value* active_value : active) {
            if (live_range_map[active_value].second < live_range_map[value].first) {
                to_remove.push_back(active_value);
                
                // 释放寄存器
                if (reg_map.find(active_value) != reg_map.end()) {
                    std::string reg = reg_map[active_value];
                    if (reg[1] == 'f') { // 浮点寄存器
                        free_float_regs.insert(reg);
                        non_free_float_regs.erase(reg);
                    } else { // 整数寄存器
                        free_int_regs.insert(reg);
                        non_free_int_regs.erase(reg);
                    }
                }
            }
        }
        
        for (Value* v : to_remove) {
            active.erase(v);
        }
        
        if(auto call_inst = dynamic_cast<CallInst*>(value))
        {
            active_regs_map[call_inst] = std::make_pair(
                std::set<std::string>(non_free_int_regs.begin(), non_free_int_regs.end()),
                std::set<std::string>(non_free_float_regs.begin(), non_free_float_regs.end())
            );
        }

        // 为当前值分配寄存器
        bool is_float = value->type_->tid_ == Type::FloatTyID;
        
        if (is_float && !free_float_regs.empty()) {
            // 分配浮点寄存器
            std::string reg = *free_float_regs.begin();
            free_float_regs.erase(free_float_regs.begin());
            non_free_float_regs.insert(reg);
            changed_float_regs.insert(reg);
            reg_map[value] = reg;
        } else if (!is_float && !free_int_regs.empty()) {
            // 分配整数寄存器
            std::string reg = *free_int_regs.begin();
            free_int_regs.erase(free_int_regs.begin());
            non_free_int_regs.insert(reg);
            changed_int_regs.insert(reg);
            reg_map[value] = reg;
        } else {
            // 没有可用寄存器，分配到栈上，用8字节
            currentStackOffset += 8;
            stack_map[value] = -currentStackOffset;
        }
        
        // 将当前值加入活跃集合
        active.insert(value);
    }

    
    changed_regs_map[func] = std::make_pair(
        std::set<std::string>(changed_int_regs.begin(), changed_int_regs.end()),
        std::set<std::string>(changed_float_regs.begin(), changed_float_regs.end())
    );

}

// 在生成代码前调用寄存器分配
void AsmEmitter::allocateRegisters(Function* func)
{
    reg_map.clear();
    stack_map.clear();
    live_range_map.clear();
    
    
    // 执行寄存器分配（包含函数参数的处理）
    linearScanRegisterAllocation(func);
}


int64_t AsmEmitter::calculateArraySize(ArrayType* arrayType)
{
    if(arrayType->contained_->tid_ == Type::ArrayTyID)
    {
        return arrayType->num_elements_ * calculateArraySize( static_cast<ArrayType*>(arrayType->contained_));
    }
    return arrayType->num_elements_ * 4;
}

std::string AsmEmitter::storeWordToStack(std::string reg, int64_t offset)
{
    std::string result;
    bool is_Float = (reg[1] == 'f');
    if(outOfImmediateRange(offset))
    {
        result += "    li.d $t4, " + std::to_string(offset) + "\n";
        result += "    add.d $t4, $sp, $t4\n";
        if(is_Float)
        {
            result += "    fst.s " + reg + ", $t4, 0\n";
        }
        else
        {
            result += "    st.w " + reg + ", $t4, 0\n";
        }
    }
    else
    {
        if(is_Float)
        {
            result += "    fst.s " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
        else
        {
            result += "    st.w " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
    }
    return result;
}

std::string AsmEmitter::loadWordFromStack(std::string reg, int64_t offset)
{
    std::string result;
    bool is_Float = (reg[1] == 'f');
    if(outOfImmediateRange(offset))
    {
        result += "    li.d $t4, " + std::to_string(offset) + "\n";
        result += "    add.d $t4, $sp, $t4\n";
        if(is_Float)
        {
            result += "    fld.s " + reg + ", $t4, 0\n";
        }
        else
        {
            result += "    ld.w " + reg + ", $t4, 0\n";
        }
    }
    else
    {
        if(is_Float)
        {
            result += "    fld.s " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
        else
        {
            result += "    ld.w " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
    }
    return result;
}

std::string AsmEmitter::storeDoubleWordToStack(std::string reg, int64_t offset)
{
    std::string result;
    bool is_Float = (reg[1] == 'f');
    if(outOfImmediateRange(offset))
    {
        result += "    li.d $t4, " + std::to_string(offset) + "\n";
        result += "    add.d $t4, $sp, $t4\n";
        if(is_Float)
        {
            result += "    fst.d " + reg + ", $t4, 0\n";
        }
        else
        {
            result += "    st.d " + reg + ", $t4, 0\n";
        }
    }
    else
    {
        if(is_Float)
        {
            result += "    fst.d " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
        else
        {
            result += "    st.d " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
    }
    return result;
}

std::string AsmEmitter::loadDoubleWordFromStack(std::string reg, int64_t offset)
{
    std::string result;
    bool is_Float = (reg[1] == 'f');
    if(outOfImmediateRange(offset))
    {
        result += "    li.d $t4, " + std::to_string(offset) + "\n"; 
        result += "    add.d $t4, $sp, $t4\n";
        if(is_Float)
        {
            result += "    fld.d " + reg + ", $t4, 0\n";
        }
        else
        {
            result += "    ld.d " + reg + ", $t4, 0\n";
        }
    }
    else
    {
        if(is_Float)
        {
            result += "    fld.d " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
        else
        {
            result += "    ld.d " + reg + ", $sp, " + std::to_string(offset) + "\n";
        }
    }
    return result;
}
// std::string AsmEmitter::handleAlloca(AllocaInst* inst)
// {
//     printf("handleAlloca\n");
//     int64_t size = 8;
//     // 根据分配类型调整大小
//     Type* allocType = inst->alloca_ty_;
//     if (allocType->tid_ == Type::ArrayTyID) {
//         // 如果是数组类型，计算总大小
//         ArrayType* arrayType = static_cast<ArrayType*>(allocType);
//         int64_t totalSize = calculateArraySize(arrayType);
//         size = totalSize;
//         // 确保大小是8的倍数（对齐）
//         if (size % 8 != 0) {
//             size = (size / 8 + 1) * 8;
//         }
//     } else if (allocType->tid_ == Type::FloatTyID || allocType->tid_ == Type::IntegerTyID) {
//         // 对于基本类型，使用4字节，但需要对齐到8字节，所以使用8字节
//         size = 8;
//     } else {
//         // 对于其他类型，默认使用8字节
//         size = 8;
//     }
//     printf("size: %d\n", size);
//     currentStackOffset += size;
//     // 为局部变量分配栈上存储空间
//     std::string result;
    
//     // 计算栈指针偏移量
//     int offset = -currentStackOffset;
//     printf("offset: %d\n", offset);
//     // 记录变量在栈上的位置
//     // reg_map[inst] = std::to_string(offset) + "($fp)";
//     if(reg_map.find(inst) != reg_map.end())
//     {
//         std::string reg = reg_map[inst];
//         result += "    addi.d $sp, $sp, -" + std::to_string(size) + "\n";
//         result += "    addi.d " + reg + ", $sp, " + "0\n";
//     }
//     else
//     {
//         int destOffset = stack_map[inst];
//         result += "    addi.d $sp, $sp, -" + std::to_string(size) + "\n";
//         result += "    st.d $sp, $fp, " + std::to_string(destOffset) + "\n";

//     }
    
//     result += "# Variable allocated at " + std::to_string(offset) + "($fp)\n";
//     printf("handleAlloca end\n");
//     return result;

// }


// 存储指令，目前已经支持超过2047字节的偏移
std::string AsmEmitter::handleStore(StoreInst* inst)
{
    std::string result;
    Value* valueToStore = inst->get_operand(0); // 要存储的值
    Value* pointerOperand = inst->get_operand(1); // 存储的目标地址
    bool valueToStoreIsPointer = valueToStore->type_->tid_ == Type::PointerTyID;


    // printf("store inst: %s  valueToStore: %s  pointerOperand: %s\n", inst->print().c_str(), valueToStore->print().c_str(), pointerOperand->print().c_str());

    
    // 获取变量名称作为注释
    std::string varName = pointerOperand->name_;
    // if (!varName.empty()) {
    //     result += "# Store to variable: " + varName + "\n";
    // } else {
    //     result += "# Store to memory\n";
    // }

    
    // 如果目标地址是编译期常量，则直接存储
    if(stack_offset_map.find(pointerOperand) != stack_offset_map.end())
    {
        bool offsetOutOfImmediateRange = false;
        if(outOfImmediateRange(stack_offset_map[pointerOperand]+currentStackOffset))
        {
            // result += "    # Stack offset out of immediate range, using $t0 as address\n";
            result += "    li.d $t0, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            result += "    add.d $t0, $sp, $t0\n";
            offsetOutOfImmediateRange = true;
        }

        if (auto* constInt = dynamic_cast<ConstantInt*>(valueToStore)) {
            
            int value = constInt->value_;
            result += "    li.w $t1, " + std::to_string(value) + "\n";
            if(offsetOutOfImmediateRange)
            {
                result += "    st.w $t1, $t0, 0\n";
            }
            else
            {
                result += "    st.w $t1, $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            }
        }
        // 如果要存储的是常量浮点数
        else if (auto* constFloat = dynamic_cast<ConstantFloat*>(valueToStore)) {
            float value = constFloat->value_;
            // 需要先将浮点数加载到浮点寄存器
            result += "    li.w $t1, " + std::to_string(*(int*)&value) + "\n";
            result += "    movgr2fr.w $ft0, $t1\n";
            if(offsetOutOfImmediateRange)
            {
                result += "    fst.s $ft0, $t0, 0\n";
            }
            else
            {
                result += "    fst.s $ft0, $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            }
        }
        // 如果要存储的是寄存器中的值
        else if (reg_map.find(valueToStore) != reg_map.end()) {
            std::string srcReg = reg_map[valueToStore];
            // 判断是整数寄存器还是浮点寄存器
            if (srcReg[0] == '$' && srcReg[1] == 'f') {
                if(offsetOutOfImmediateRange)
                {
                    result += "    fst.s " + srcReg + ", $t0, 0\n";
                }
                else
                {
                    result += "    fst.s " + srcReg + ", $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                }
            }
            else if(valueToStoreIsPointer)
            {
                if(offsetOutOfImmediateRange)
                {
                    result += "    st.d " + srcReg + ", $t0, 0\n";
                }
                else
                {
                    result += "    st.d " + srcReg + ", $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                }
            }
            else {
                if(offsetOutOfImmediateRange)
                {
                    result += "    st.w " + srcReg + ", $t0, 0\n";
                }
                else
                {
                    result += "    st.w " + srcReg + ", $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                }
            }
        }
        // 如果要存储的是栈上的值
        else if (stack_map.find(valueToStore) != stack_map.end())
        {

            if(valueToStoreIsPointer)
            {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.d $t1, $t2, 0\n";
                }
                else
                {
                    result += "    ld.d $t1, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                if(offsetOutOfImmediateRange)
                {
                    result += "    st.d $t1, $t0, 0\n";
                }
                else
                {
                    result += "    st.d $t1, $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                }
            }
            else {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.w $t1, $t2, 0\n";
                }
                else
                {
                    result += "    ld.w $t1, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                if(offsetOutOfImmediateRange)
                {
                    result += "    st.w $t1, $t0, 0\n";
                }
                else
                {
                    result += "    st.w $t1, $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                }
            }
        }
        // 如果要存储的值没有映射到寄存器，需要先加载，目前认为这种情况只有全局变量
        else {
            // result += "    # Warning: Value not in register/stack, regarded as a global variable\n";
            result += "    la.global    $t1, " + valueToStore->name_ + "\n";
            result += "    ld.w $t1, $t1, 0\n"; // 把全局变量的值写入t1
            if(offsetOutOfImmediateRange)
            {
                result += "    st.w $t1, $t0, 0\n";
            }
            else
            {
                result += "    st.w $t1, $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            }
        }
    }
    // 如果目标地址在寄存器中，直接存储
    else if(reg_map.find(pointerOperand) != reg_map.end())
    {
        if (auto* constInt = dynamic_cast<ConstantInt*>(valueToStore)) {
            int value = constInt->value_;
            result += "    li.w $t1, " + std::to_string(value) + "\n";
            result += "    st.w $t1, " + reg_map[pointerOperand] + ", 0\n";
        }
        // 如果要存储的是常量浮点数
        else if (auto* constFloat = dynamic_cast<ConstantFloat*>(valueToStore)) {
            float value = constFloat->value_;
            // 需要先将浮点数加载到浮点寄存器
            result += "    li.w $t1, " + std::to_string(*(int*)&value) + "\n";
            result += "    movgr2fr.w $ft0, $t1\n";
            result += "    fst.s $ft0, " + reg_map[pointerOperand] + ", 0\n";
        }
        // 如果要存储的是寄存器中的值
        else if (reg_map.find(valueToStore) != reg_map.end()) {
            std::string srcReg = reg_map[valueToStore];
            // 判断是整数寄存器还是浮点寄存器
            if (srcReg[0] == '$' && srcReg[1] == 'f') {
                result += "    fst.s " + srcReg + ", " + reg_map[pointerOperand] + ", 0\n";
            } else if(valueToStoreIsPointer)
            {
                result += "    st.d " + srcReg + ", " + reg_map[pointerOperand] + ", 0\n";
            }
            else {
                result += "    st.w " + srcReg + ", " + reg_map[pointerOperand] + ", 0\n";
            }
        }
        // 如果要存储的是栈上的值
        else if (stack_map.find(valueToStore) != stack_map.end())
        {
            if(valueToStoreIsPointer)
            {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.d $t0, $t2, 0\n";
                }
                else
                {
                    result += "    ld.d $t0, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                result += "    st.d $t0, " + reg_map[pointerOperand] + ", 0\n";
            }
            else
            {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.w $t0, $t2, 0\n";
                }
                else
                {
                    result += "    ld.w $t0, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                result += "    st.w $t0, " + reg_map[pointerOperand] + ", 0\n";
            }
        }
        // 如果要存储的值没有映射到寄存器，需要先加载，目前认为这种情况只有全局变量
        else {
            // result += "    # Warning: Value not in register/stack, regarded as a global variable\n";
            result += "    la.global    $t1, " + valueToStore->name_ + "\n";
            result += "    ld.w $t1, $t1, 0\n"; // 把全局变量的值写入t1
            result += "    st.w $t1, " + reg_map[pointerOperand] + ", 0\n";
        }
    }
    // 检查目标地址是否存储在栈上
    else if (stack_map.find(pointerOperand) != stack_map.end()) {
        int offset = stack_map[pointerOperand];

        if(outOfImmediateRange(offset+currentStackOffset))
        {
            result += "    li.d $t2, " + std::to_string(offset+currentStackOffset) + "\n";
            result += "    add.d $t2, $sp, $t2\n";
            result += "    ld.d $t0, $t2, 0\n";
        }
        
        result += "    ld.d $t0, $sp, " + std::to_string(offset+currentStackOffset) + "\n";//读取目标地址

        // 如果要存储的是常量整数
        if (auto* constInt = dynamic_cast<ConstantInt*>(valueToStore)) {
            int value = constInt->value_;
            result += "    li.w $t1, " + std::to_string(value) + "\n";
            result += "    st.w $t1, $t0, 0\n";
        }
        // 如果要存储的是常量浮点数
        else if (auto* constFloat = dynamic_cast<ConstantFloat*>(valueToStore)) {
            float value = constFloat->value_;
            // 需要先将浮点数加载到浮点寄存器
            result += "    li.w $t1, " + std::to_string(*(int*)&value) + "\n";
            result += "    movgr2fr.w $ft0, $t1\n";
            result += "    fst.s $ft0, $t0, 0\n";
        }
        // 如果要存储的是寄存器中的值
        else if (reg_map.find(valueToStore) != reg_map.end()) {
            std::string srcReg = reg_map[valueToStore];
            // 判断是整数寄存器还是浮点寄存器
            if (srcReg[0] == '$' && srcReg[1] == 'f') {
                result += "    fst.s " + srcReg + ", $t0, 0\n";
            }else if(valueToStoreIsPointer)
            {
                result += "    st.d " + srcReg + ", $t0, 0\n";
            }
            else {
                result += "    st.w " + srcReg + ", $t0, 0\n";
            }
        }
        // 如果要存储的是栈上的值
        else if (stack_map.find(valueToStore) != stack_map.end())
        {
            if(valueToStoreIsPointer)
            {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.d $t1, $t2, 0\n";
                }
                else
                {
                    result += "    ld.d $t1, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                result += "    st.d $t1, $t0, 0\n";
            }
            else {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.w $t1, $t2, 0\n";
                }
                else
                {
                    result += "    ld.w $t1, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                result += "    st.w $t1, $t0, 0\n";
            }
        }
        // 如果要存储的值没有映射到寄存器，需要先加载，目前认为这种情况只有全局变量
        else {
            // result += "    # Warning: Value not in register/stack, regarded as a global variable\n";
            result += "    la.global    $t1, " + valueToStore->name_ + "\n";
            result += "    ld.w $t1, $t1, 0\n"; // 把全局变量的值写入t1
            result += "    st.w $t1, $t0, 0\n";
        }
    }
    // 如果目标地址不在栈上，可能是全局变量或者通过指针访问
    else {
        // result += "    # Store to global variable\n";
        // 假设存到非栈内存只处理全局变量的情况
        result += "    la.global $t0, " + pointerOperand->name_ + "\n";
        
        // 如果要存储的是常量整数
        if (auto* constInt = dynamic_cast<ConstantInt*>(valueToStore)) {
            int value = constInt->value_;
            result += "    li.w $t1, " + std::to_string(value) + "\n";
            result += "    st.w $t1, $t0, 0\n";
        }
        // 如果要存储的是常量浮点数
        else if (auto* constFloat = dynamic_cast<ConstantFloat*>(valueToStore)) {
            float value = constFloat->value_;
            result += "    li.w $t1, " + std::to_string(*(int*)&value) + "\n";
            result += "    movgr2fr.w $ft0, $t1\n";
            result += "    fst.s $ft0, $t0, 0\n";
        }
        // 如果要存储的是寄存器中的值
        else if (reg_map.find(valueToStore) != reg_map.end()) {
            std::string srcReg = reg_map[valueToStore];
            if (srcReg[0] == '$' && srcReg[1] == 'f') {
                // 浮点寄存器
                result += "    fst.s " + srcReg + ", $t0, 0\n";
            } else if(valueToStoreIsPointer)
            {
                result += "    st.d " + srcReg + ", $t0, 0\n";
            }
            else {
                // 整数寄存器
                result += "    st.w " + srcReg + ", $t0, 0\n";
            }
        }
        // 如果要存储的是栈上的值
        else if (stack_map.find(valueToStore) != stack_map.end())
        {
            if(valueToStoreIsPointer)
            {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.d $t1, $t2, 0\n";
                }
                else
                {
                    result += "    ld.d $t1, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                result += "    st.d $t1, $t0, 0\n";
            }
            else {
                if(outOfImmediateRange(stack_map[valueToStore]+currentStackOffset))
                {
                    result += "    li.d $t2, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                    result += "    add.d $t2, $sp, $t2\n";
                    result += "    ld.w $t1, $t2, 0\n";
                }
                else
                {
                    result += "    ld.w $t1, $sp, " + std::to_string(stack_map[valueToStore]+currentStackOffset) + "\n";
                }
                result += "    st.w $t1, $t0, 0\n";
            }
        }
        // 如果要存储的值没有映射到寄存器
        else {
            // result += "    # Warning: Value not in register/stack, regarded as a global variable\n";
            result += "    la.global    $t1, " + valueToStore->name_ + "\n";
            result += "    ld.w $t1, $t1, 0\n"; // 把全局变量的值写入t1
            result += "    st.w $t1, $t0, 0\n";
        }
    }
    
    return result;
}

std::string AsmEmitter::handleLoad(LoadInst* inst)
{
    std::string result;
    Value* pointerOperand = inst->get_operand(0);
    Type* loadType = inst->type_;
    bool isFloat = loadType->tid_ == Type::FloatTyID;
    bool isPointer = loadType->tid_ == Type::PointerTyID;

    bool resultInReg = true;
    
    // 为结果分配寄存器
    std::string destReg;
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else {
        // 如果没有预分配寄存器，使用临时寄存器
        resultInReg = false;
        destReg = isFloat ? "$ft0" : "$t0";
        // result += "    # Warning: Result not mapped to register, using " + destReg + "\n";
    }
    

    // 如果指针操作数是编译期常量，则直接从栈上读取
    if(stack_offset_map.find(pointerOperand) != stack_offset_map.end())
    {
        bool offsetOutOfImmediateRange = false;
        if(outOfImmediateRange(stack_offset_map[pointerOperand]+currentStackOffset))
        {
            offsetOutOfImmediateRange = true;
        }

        if (isFloat) {
            // result += "    # Load from stack, regarded as a single float\n";
            if(offsetOutOfImmediateRange)
            {
                result += "    li.d $t2, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                result += "    add.d $t2, $sp, $t2\n";
                result += "    fld.s " + destReg + ", $t2, 0\n";
            }
            else
            {
                result += "    fld.s " + destReg + ", $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            }
        } 
        else if(isPointer)
        {
            // result += "    # Load from stack, regarded as a double word\n";
            if(offsetOutOfImmediateRange)
            {
                result += "    li.d $t2, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                result += "    add.d $t2, $sp, $t2\n";
                result += "    ld.d " + destReg + ", $t2, 0\n";
            }
            else
            {
                result += "    ld.d " + destReg + ", $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            }
        }
        else {
            // result += "    # Load from stack, regarded as a word\n";
            if(offsetOutOfImmediateRange)
            {
                result += "    li.d $t2, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
                result += "    add.d $t2, $sp, $t2\n";
                result += "    ld.w " + destReg + ", $t2, 0\n";
            }
            else
            {
                result += "    ld.w " + destReg + ", $sp, " + std::to_string(stack_offset_map[pointerOperand]+currentStackOffset) + "\n";
            }
        }
    }
    // 地址在栈上
    else if (stack_map.find(pointerOperand) != stack_map.end() ) {
        
        int64_t offset = stack_map[pointerOperand];

        //注意，这里在读取地址，地址是双字！！
        if(outOfImmediateRange(offset+currentStackOffset))
        {
            result += "    li.d $t2, " + std::to_string(offset+currentStackOffset) + "\n";
            result += "    add.d $t2, $sp, $t2\n";
            result += "    ld.d $t0, $t2, 0\n";
        }
        else
        {
            result += "    ld.d $t0, $sp, " + std::to_string(offset+currentStackOffset) + "\n";
        }

        if (isFloat) {
            // result += "    # Load from address in stack, regarded as a single float\n";
            result += "    fld.s " + destReg + ", $t0, 0\n";
        }
        else if(isPointer)
        {
            // result += "    # Load from address in stack, regarded as a double word\n";
            result += "    ld.d " + destReg + ", $t0, 0\n";
        }
        else {
            // result += "    # Load from address in stack, regarded as a word\n";
            result += "    ld.w " + destReg + ", $t0, 0\n";
        }
    }
    // 如果指针操作数在寄存器中（可能是GEP指令的结果或其他指针计算）
    else if (reg_map.find(pointerOperand) != reg_map.end()) {
        std::string ptrReg = reg_map[pointerOperand];

        // result += "    ld.w $t0, " + ptrReg + ", 0\n";
        
        if (isFloat) {
            // result += "    # Load from register, regarded as a single float\n";
            result += "    fld.s " + destReg + ", " + ptrReg + ", 0\n";
        } 
        else if(isPointer)
        {
            // result += "    # Load from register, regarded as a double word\n";
            result += "    ld.d " + destReg + ", " + ptrReg + ", 0\n";
        }
        else {
            // result += "    # Load from register, regarded as a word\n";
            result += "    ld.w " + destReg + ", " + ptrReg + ", 0\n";
        }
    }
    // 如果指针操作数是全局变量
    else if (auto* globalVar = dynamic_cast<GlobalVariable*>(pointerOperand)) {
        std::string globalName = globalVar->name_;
        
        // 先加载全局变量地址到临时寄存器
        result += "    la.global $t0, " + globalName + "\n";

        // // 如果指针操作数是全局变量，说明是从全局变量上加载地址
        // result += "    ld.w $t0, $t0, 0\n";
        
        if (isFloat) {
            result += "    fld.s " + destReg + ", $t0, 0\n";
        } 
        else if(isPointer)
        {
            result += "    ld.d " + destReg + ", $t0, 0\n";
        }
        else {
            result += "    ld.w " + destReg + ", $t0, 0\n";
        }
    }
    // 其他情况，目前认为没有
    else {

        REPORT_COMPILER_ERROR_AND_EXIT("Load from unknown source");
    }

    if(!resultInReg)
    {
        // Store the loaded value to stack if result is not kept in register
        int offset = stack_map[inst];
        bool offsetOutOfImmediateRange = false;
        if(outOfImmediateRange(offset+currentStackOffset))
        {
            result += "    li.d $t2, " + std::to_string(offset+currentStackOffset) + "\n";
            result += "    add.d $t2, $sp, $t2\n";
            offsetOutOfImmediateRange = true;
        }
        if (isFloat) {
            if(offsetOutOfImmediateRange)
            {
                result += "    fst.s " + destReg + ", $t2, 0\n";
            }
            else
            {
                result += "    fst.s " + destReg + ", $sp, " + std::to_string(offset+currentStackOffset) + "\n";
            }
        } 
        else if(isPointer)
        {
            if(offsetOutOfImmediateRange)
            {
                result += "    st.d " + destReg + ", $t2, 0\n";
            }
            else
            {
                result += "    st.d " + destReg + ", $sp, " + std::to_string(offset+currentStackOffset) + "\n";
            }
        }
        else {
            if(offsetOutOfImmediateRange)
            {
                result += "    st.w " + destReg + ", $t2, 0\n";
            }
            else
            {
                result += "    st.w " + destReg + ", $sp, " + std::to_string(offset+currentStackOffset) + "\n";
            }
        }
    }
    
    return result;
}

std::string AsmEmitter::handleSiToFp(SiToFpInst *inst) {
    std::string result;
    // 获取源操作数（整数）
    Value *srcVal = inst->get_operand(0);
    Type *destType = inst->dest_ty_; // 目标类型应为浮点
    bool isDestFloat = (destType->tid_ == Type::FloatTyID);
    assert(isDestFloat && "SiToFp destination must be float");

    // 确定目标寄存器
    std::string destReg;
    bool storeDest = false;

    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst]; // 目标寄存器预分配
    } else {
        destReg = "$ft0"; // 使用临时浮点寄存器
        storeDest = true;
        // result += "    # Result not mapped to register, using " + destReg + "\n";
    }

    // 处理源操作数
    if (stack_map.find(srcVal) != stack_map.end()) {
        // 从栈加载整数到整数寄存器
        result += loadWordFromStack("$t0", stack_map[srcVal]+currentStackOffset);
        // 转换到浮点
        result += "    movgr2fr.w " + destReg + ", $t0\n";
        result += "    ffint.s.w " + destReg + ", " + destReg + "\n";
    } else if (reg_map.find(srcVal) != reg_map.end()) {
        // 直接在寄存器中转换
        std::string srcReg = reg_map[srcVal];
        if (srcReg[1] == 'f') {
            // 如果源在浮点寄存器（异常情况）
            // result += "    movfr2gr.s $t0, " + srcReg + "\n";
            // result += "    movgr2fr.w " + destReg + ", $t0\n";
            result += "    ffint.s.w " + destReg + ", " + srcReg + "\n";
        } else {
            // 整数寄存器直接转换
            result += "    movgr2fr.w " + destReg + ", " + srcReg + "\n";
            result += "    ffint.s.w " + destReg + ", " + destReg + "\n";
        }
    } else if (auto *constInt = dynamic_cast<ConstantInt*>(srcVal)) {
        // 常量整数加载并转换
        int value = constInt->value_;
        result += "    li.w $t0, " + std::to_string(value) + "\n";
        result += "    movgr2fr.w " + destReg + ", $t0\n";
        result += "    ffint.s.w " + destReg + ", " + destReg + "\n";
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Source value for SiToFp is from unknown source");
    }

    // 如果目标不在寄存器，存储到栈
    if (storeDest) {
        // result += "    fst.s " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }

    return result;
}


std::string AsmEmitter::handleFpToSi(FpToSiInst *inst) {
    std::string result;
    // 获取源操作数（浮点）
    Value *srcVal = inst->get_operand(0);
    Type *destType = inst->dest_ty_; // 目标类型应为整数
    bool isDestInt = (destType->tid_ == Type::IntegerTyID);
    assert(isDestInt && "FpToSi destination must be integer");

    // 确定目标寄存器
    std::string destReg;
    bool storeDest = false;

    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst]; // 目标寄存器预分配
    } else {
        destReg = "$t0"; // 使用临时整数寄存器
        storeDest = true;
        // result += "    # Result not mapped to register, using " + destReg + "\n";
    }

    // 处理源操作数
    if (stack_map.find(srcVal) != stack_map.end()) {
        // 从栈加载浮点到浮点寄存器
        // result += "    fld.s $ft1, $sp, " + std::to_string(stack_map[srcVal]+currentStackOffset) + "\n";
        result += loadWordFromStack("$ft1", stack_map[srcVal]+currentStackOffset);
        // 转换到整数
        result += "    ftintrz.w.s $ft1, $ft1\n";
        result += "    movfr2gr.s " + destReg + ", $ft1\n";
    } else if (reg_map.find(srcVal) != reg_map.end()) {
        // 直接在寄存器中转换
        std::string srcReg = reg_map[srcVal];
        if (srcReg[1] != 'f') {
            // 如果源在整数寄存器，需要先转为浮点（异常情况）
            result += "    movgr2fr.w $ft1, " + srcReg + "\n";
            result += "    ftintrz.w.s $ft1, $ft1\n";
            result += "    movfr2gr.s " + destReg + ", $ft1\n";
        } else {
            // 浮点寄存器直接转换
            result += "    fmov.s $ft1, " + srcReg + "\n";
            result += "    ftintrz.w.s $ft1, $ft1\n";
            result += "    movfr2gr.s " + destReg + ", $ft1\n";
        }
    } else if (auto *constFloat = dynamic_cast<ConstantFloat*>(srcVal)) {
        // 常量浮点加载并转换
        float value = constFloat->value_;
        result += "    li.w $t1, " + std::to_string(*(int*)&value) + "\n";
        result += "    movgr2fr.w $ft1, $t1\n";
        result += "    ftintrz.w.s $ft1, $ft1\n";
        result += "    movfr2gr.s " + destReg + ", $ft1\n";
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Source value for FpToSi is from unknown source");
    }

    // 如果目标不在寄存器，存储到栈
    if (storeDest) {
        // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }

    return result;
}



// std::string AsmEmitter::handleAllAlloca(Function* func)
// {
//     int64_t allocaSize = 0;
    
//     std::string result;
//     // result += "    # Function entry basic block\n";
//     BasicBlock* entryBB = func->basic_blocks_.front();
//     for(auto& inst : entryBB->instr_list_)
//     {
//         if(auto* allocaInst = dynamic_cast<AllocaInst*>(inst))
//         {
//             // 根据分配类型调整大小
//             Type* allocType = allocaInst->alloca_ty_;
//             if (allocType->tid_ == Type::ArrayTyID) {
//                 // 如果是数组类型，计算总大小
//                 ArrayType* arrayType = static_cast<ArrayType*>(allocType);
//                 int64_t totalSize = calculateArraySize(arrayType);
//                 allocaSize += totalSize;
                
//             } else if (allocType->tid_ == Type::FloatTyID || allocType->tid_ == Type::IntegerTyID) {
//                 // 对于基本类型，使用4字节
//                 allocaSize += 4;
//             } else {
//                 // 对于其他类型，默认使用4字节
//                 allocaSize += 4;
//             }
//             stack_offset_map[allocaInst] = -(currentStackOffset + allocaSize); // 记录该alloca指令的栈偏移量结果，将其视为编译期常量
//         }
//     }
//     // 确保大小是8的倍数（对齐）
//     if (allocaSize % 8 != 0) {
//         allocaSize = (allocaSize / 8 + 1) * 8;
//     }
//     // printf("size: %d\n", allocaSize);
//     currentStackOffset += allocaSize;

//     result += "    addi.d $sp, $sp, " + std::to_string(-allocaSize) + "\n";


//     return result;
// }


std::string AsmEmitter::generateFunctionPrologue(Function* func)
{
    // args.clear();
    // args.insert(func->arguments_.begin(), func->arguments_.end());
    // allocateFunctionArguments(func);
    currentStackOffset = 0;


    std::string result;
    std::string funcName = func->name_;
    
    // 函数标签
    result += "# Function: " + funcName + "\n";
    result += funcName + ":\n";
    // result += func->basic_blocks_.front()->name_ + ":\n";
    
    // 保存返回地址和帧指针
    result += "    st.d $ra, $sp, -8\n";
    result += "    st.d $fp, $sp, -16\n";
    
    // 设置新的帧指针，目前取消，所有函数共用一个栈帧
    // result += "    addi.d $fp, $sp, -16\n";

    if(!isLeafFunction(func))
    {
        currentStackOffset += int_regs.size() * 8 + float_regs.size() * 8;//用来保存调用者保存的寄存器
        // printf("not leaf function, currentStackOffset: %lld\n",currentStackOffset);
    }

    int64_t allocaSize = 0;
    
    // std::string result;
    // result += "    # Function entry basic block\n";
    BasicBlock* entryBB = func->basic_blocks_.front();
    for(auto& inst : entryBB->instr_list_)
    {
        if(auto* allocaInst = dynamic_cast<AllocaInst*>(inst))
        {
            // 根据分配类型调整大小
            Type* allocType = allocaInst->alloca_ty_;
            if (allocType->tid_ == Type::ArrayTyID) {
                // 如果是数组类型，计算总大小
                ArrayType* arrayType = static_cast<ArrayType*>(allocType);
                int64_t totalSize = calculateArraySize(arrayType);
                allocaSize += totalSize;
                
            } else if (allocType->tid_ == Type::FloatTyID || allocType->tid_ == Type::IntegerTyID) {
                // 对于基本类型，使用4字节
                allocaSize += 4;
            } else {
                // 对于其他类型，默认使用8字节
                allocaSize += 8;
            }
            stack_offset_map[allocaInst] = -(currentStackOffset + allocaSize); // 记录该alloca指令的栈偏移量结果，将其视为编译期常量
        }
    }
    // 确保大小是8的倍数（对齐）
    // if (allocaSize % 8 != 0) {
    //     allocaSize = (allocaSize / 8 + 1) * 8;
    // }
    // printf("size: %d\n", allocaSize);
    currentStackOffset += allocaSize;
    // printf("")

    allocateRegisters(func);

    // result += "    addi.d $sp, $sp, -" + std::to_string(allocaSize) + "\n";
    
    // 计算栈帧大小（需要为局部变量和保存的寄存器分配空间）
    int64_t frameSize = 16 + currentStackOffset;  // 16为保存$ra和$fp的空间
    
    // printf("frameSize: %d\n", frameSize);
    // 为栈上的变量分配空间
    for (auto& pair : stack_map) {
        // 确保栈大小足够容纳所有变量
        int64_t varOffset = abs(pair.second);
        if (varOffset > frameSize) {
            frameSize = varOffset;
        }
    }
    
    // 对齐栈帧大小（16字节对齐）
    frameSize = (frameSize + 15) & ~15;
    // printf("frameSize: %d\n", frameSize);
    
    currentStackOffset = frameSize - 16;
    // 分配栈空间
    if(outOfImmediateRange(-frameSize))
    {
        result += "    li.d $t2, " + std::to_string(-frameSize) + "\n";
        result += "    add.d $sp, $sp, $t2\n";
    }
    else
    {
        result += "    addi.d $sp, $sp, " + std::to_string(-frameSize) + "\n";
    }


    // if(func->name_.compare("main") == 0)
    // {
    //     //设置浮点数舍入模式为向零舍入
    //     result += "    ori $t0, $zero, 0x1\n";
    //     result += "    movgr2fcsr $fcsr3, $t0\n";
    // }
    // printf("result: %s\n", result.c_str());
    
    return result;
}

// std::string AsmEmitter::handleBinaryInst(BinaryInst* inst)
// {
//     std::string result;
//     Value* lhs = inst->get_operand(0);
//     Value* rhs = inst->get_operand(1);
//     Type* resultType = inst->type_;
//     bool isFloat = resultType->tid_ == Type::FloatTyID;
//     bool storeDest = false;
    
//     // 为结果分配寄存器
//     std::string destReg;
//     if (reg_map.find(inst) != reg_map.end()) {
//         destReg = reg_map[inst];
//     } else { //结果不存在寄存器中，就一定存到栈上
//         destReg = isFloat ? "$ft0" : "$t0";
//         storeDest = true;
//         result += "    # Warning: Result not mapped to register, using " + destReg + "\n";
//     }

//     std::string lhsReg;
//     std::string rhsReg;

//     //为左操作数分配寄存器，或设置为常量
//     if(reg_map.find(lhs) != reg_map.end())
//     {
//         lhsReg = reg_map[lhs];
//     }
//     else if(stack_map.find(lhs) != stack_map.end())
//     {
//         lhsReg = isFloat ? "$ft0" : "$t0";
//         result += "    # Warning: Left operand not mapped to register, using " + lhsReg + "\n";
//         result += "    ld.w " + lhsReg + ", $fp, " + std::to_string(stack_map[lhs]) + "\n";
//     }
//     else if(dynamic_cast<Constant*>(lhs) != nullptr)
//     {
//         if(isFloat)
//         {
//             lhsReg = std::to_string(dynamic_cast<ConstantFloat*>(lhs)->value_);
//         }
//         else
//         {
//             lhsReg = std::to_string(dynamic_cast<ConstantInt*>(lhs)->value_);
//         }
        
//     }

//     //为右操作数分配寄存器，或设置为常量
//     if(reg_map.find(rhs) != reg_map.end())
//     {
//         rhsReg = reg_map[rhs];
//     }
//     else if(stack_map.find(rhs) != stack_map.end())
//     {
//         rhsReg = isFloat ? "$ft1" : "$t1";
//         result += "    # Warning: Right operand not mapped to register, using " + rhsReg + "\n";
//         result += "    ld.w " + rhsReg + ", $fp, " + std::to_string(stack_map[rhs]) + "\n";
//     }
//     else if(dynamic_cast<Constant*>(rhs) != nullptr)
//     {
//         if(isFloat)
//         {
//             rhsReg = std::to_string(dynamic_cast<ConstantFloat*>(rhs)->value_);
//         }
//         else
//         {
//             rhsReg = std::to_string(dynamic_cast<ConstantInt*>(rhs)->value_);
//         }
//     }

    
    
//     if(!isFloat)
//     {
//         if(inst->op_id_ == Instruction::Add)
//         {
//             result += "    add.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::Sub)
//         {
//             result += "    sub.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::Mul)
//         {
//             result += "    mul.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::SDiv)
//         {
//             result += "    div.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::SRem)
//         {
//             result += "    mod.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//     }
//     else
//     {
//         if(inst->op_id_ == Instruction::FAdd)
//         {
//             result += "    fadd.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::FSub)
//         {
//             result += "    fsub.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::FMul)
//         {
//             result += "    fmul.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//         else if(inst->op_id_ == Instruction::FDiv)
//         {
//             result += "    fdiv.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
//         }
//     }

//     if(storeDest)
//     {
//         result += "    st.w " + destReg + ", $fp, " + std::to_string(stack_map[inst]) + "\n";
//     }
    
//     return result;
// }

std::string AsmEmitter::handleBinaryInst(BinaryInst* inst)
{
    // printf("handleBinaryInst\n");
    std::string result = "";
    // result += "11\n";
    // std::cout<<result<<std::endl;
    Value* lhs = inst->get_operand(0);
    Value* rhs = inst->get_operand(1);
    Type* resultType = inst->type_;
    bool isFloat = resultType->tid_ == Type::FloatTyID;
    bool storeDest = false;
    
    // 为结果分配寄存器
    std::string destReg;
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else { //结果不存在寄存器中，就一定存到栈上
        destReg = isFloat ? "$ft0" : "$t0";
        storeDest = true;
        // result += "    # Warning: Result not mapped to register, using " + destReg + "\n";
    }
    // 检查操作数是否为常量值
    bool lhsIsConst = dynamic_cast<Constant*>(lhs) != nullptr;
    bool rhsIsConst = dynamic_cast<Constant*>(rhs) != nullptr;
    int lhsConstVal = 0;
    int rhsConstVal = 0;
    float lhsConstFloatVal = 0.0f;
    float rhsConstFloatVal = 0.0f;

    bool bothConst = lhsIsConst && rhsIsConst;
    
    // 获取常量值（如果有）
    if (lhsIsConst) {
        if (isFloat) {
            lhsConstFloatVal = dynamic_cast<ConstantFloat*>(lhs)->value_;
        } else {
            lhsConstVal = dynamic_cast<ConstantInt*>(lhs)->value_;
        }
    }
    
    if (rhsIsConst) {
        if (isFloat) {
            rhsConstFloatVal = dynamic_cast<ConstantFloat*>(rhs)->value_;
        } else {
            rhsConstVal = dynamic_cast<ConstantInt*>(rhs)->value_;
        }
    }
    std::string lhsReg;
    std::string rhsReg;
    // 为左操作数分配寄存器，或确认它是一个常量
    if (reg_map.find(lhs) != reg_map.end()) {
        lhsReg = reg_map[lhs];
    } else if (stack_map.find(lhs) != stack_map.end()) {
        if (isFloat) {
            // result += "    fld.s $ft0, $sp, " + std::to_string(stack_map[lhs]+currentStackOffset) + "\n";
            result += loadWordFromStack("$ft0", stack_map[lhs]+currentStackOffset);
            lhsReg = "$ft0";
        } else {
            // result += "    ld.w $t0, $sp, " + std::to_string(stack_map[lhs]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t0", stack_map[lhs]+currentStackOffset);
            lhsReg = "$t0";
        }
    } else if (lhsIsConst) {
        // 常量将直接在指令中使用，不需要寄存器
        lhsReg = isFloat ? 
            std::to_string(lhsConstFloatVal) : 
            std::to_string(lhsConstVal);
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Left operand is from unknown source");
        // result += "    # Warning: Left operand not found in register or stack\n";
        // lhsReg = isFloat ? "$ft0" : "$t0";
    }
    // 为右操作数分配寄存器，或确认它是一个常量
    if (reg_map.find(rhs) != reg_map.end()) {
        rhsReg = reg_map[rhs];
    } else if (stack_map.find(rhs) != stack_map.end()) {
        if (isFloat) {
            // result += "    fld.s $ft1, $sp, " + std::to_string(stack_map[rhs]+currentStackOffset) + "\n";
            result += loadWordFromStack("$ft1", stack_map[rhs]+currentStackOffset);
            rhsReg = "$ft1";
        } else {
            // result += "    ld.w $t1, $sp, " + std::to_string(stack_map[rhs]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t1", stack_map[rhs]+currentStackOffset);
            rhsReg = "$t1";
        }
    } else if (rhsIsConst) {
        // 常量将直接在指令中使用，不需要寄存器
        rhsReg = isFloat ? 
            std::to_string(rhsConstFloatVal) : 
            std::to_string(rhsConstVal);
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Right operand is from unknown source");
        // result += "    # Warning: Right operand not found in register or stack\n";
        // rhsReg = isFloat ? "$ft1" : "$t1";
    }
    // std::cout<<result<<std::endl;
    // printf("handleBinaryInst mid result: %s\n",result.c_str());
    // 处理浮点运算 - 浮点操作通常不支持立即数模式
    if (isFloat) {
        // 如果操作数是常量值，需要先加载到浮点寄存器
        // printf("isFloat\n");
        if (lhsIsConst) {
            result += "    li.w $t0, " + std::to_string(*(int*)&lhsConstFloatVal) + "\n";
            result += "    movgr2fr.w $ft0, $t0\n";
            lhsReg = "$ft0";
        }
        
        if (rhsIsConst) {
            result += "    li.w $t1, " + std::to_string(*(int*)&rhsConstFloatVal) + "\n";
            result += "    movgr2fr.w $ft1, $t1\n";
            rhsReg = "$ft1";
        }
        
        // 执行浮点运算
        if (inst->op_id_ == Instruction::FAdd) {
            result += "    fadd.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
        } else if (inst->op_id_ == Instruction::FSub) {
            result += "    fsub.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
        } else if (inst->op_id_ == Instruction::FMul) {
            result += "    fmul.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
        } else if (inst->op_id_ == Instruction::FDiv) {
            result += "    fdiv.s " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
        }
    } 
    // 处理整数运算 - 可以使用立即数模式
    else {
        // printf("isInt\n");
        // 对于整数操作，检查是否可以使用立即数版本的指令
        // 注意：LoongArch64的立即数范围通常为12位有符号整数 (-2048 ~ 2047)，由于立即数可能取负使用，所以取-2047
        const int IMMEDIATE_MIN = -2047;
        const int IMMEDIATE_MAX = 2047;
        bool useImmediate = false;
        
        // 我们只能在第二个操作数是常量时使用立即数指令
        if (rhsIsConst && rhsConstVal >= IMMEDIATE_MIN && rhsConstVal <= IMMEDIATE_MAX) {
            useImmediate = true;
        }
        
        // 如果需要交换操作数（当左操作数是常量时）
        // 注意：这只适用于可交换的操作（加法和乘法）
        if (!useImmediate && lhsIsConst && lhsConstVal >= IMMEDIATE_MIN && lhsConstVal <= IMMEDIATE_MAX) {
            if (inst->op_id_ == Instruction::Add || inst->op_id_ == Instruction::Mul) {
                // 交换操作数
                std::swap(lhsReg, rhsReg);
                std::swap(lhsConstVal, rhsConstVal);
                std::swap(lhsIsConst, rhsIsConst);
                useImmediate = true;
                // rhsConstVal = lhsConstVal;  // 更新常量值
            }
        }
        
        // 根据操作类型和操作数生成指令
        if (inst->op_id_ == Instruction::Add) {
            // printf("Add\n");
            if(bothConst)
            {
                result += "    li.w " + destReg + ", " + std::to_string(lhsConstVal + rhsConstVal) + "\n";
            }
            else if (useImmediate) {
                result += "    addi.w " + destReg + ", " + lhsReg + ", " + std::to_string(rhsConstVal) + "\n";
            } else {
                if(lhsIsConst)
                {
                    result += "    li.w $t0, " + std::to_string(lhsConstVal) + "\n";
                    lhsReg = "$t0";
                }
                if(rhsIsConst)
                {
                    result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
                    rhsReg = "$t1";
                }
                result += "    add.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            }
        } else if (inst->op_id_ == Instruction::Sub) {
            // printf("Sub\n");
            if(bothConst)
            {
                result += "    li.w " + destReg + ", " + std::to_string(lhsConstVal - rhsConstVal) + "\n";
            }
            else if (useImmediate) {
                // 使用加法和负数立即数实现减法
                result += "    addi.w " + destReg + ", " + lhsReg + ", " + std::to_string(-rhsConstVal) + "\n";
            } else {
                if(lhsIsConst)
                {
                    result += "    li.w $t0, " + std::to_string(lhsConstVal) + "\n";
                    lhsReg = "$t0";
                }
                if(rhsIsConst)
                {
                    result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
                    rhsReg = "$t1";
                }
                result += "    sub.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            }
        }
        else if (inst->op_id_ == Instruction::Mul)
        {
            // printf("Mul\n");
            // result += "    # Mul\n";
            // LoongArch64 没有直接的乘法立即数指令
            // 如果右侧是特定的2的幂，可以用移位代替
            if (bothConst)
            {
                result += "    li.w " + destReg + ", " + std::to_string(lhsConstVal * rhsConstVal) + "\n";
            }
            else if (useImmediate)
            {
                if (rhsIsConst && (rhsConstVal & (rhsConstVal - 1)) == 0 && rhsConstVal > 0)
                {
                    // 计算log2(rhsConstVal)
                    int shift = 0;
                    int temp = rhsConstVal;
                    while (temp > 1)
                    {
                        temp >>= 1;
                        shift++;
                    }
                    result += "    slli.w " + destReg + ", " + lhsReg + ", " + std::to_string(shift) + "\n";
                }
                else
                {
                    // 必须使用两个寄存器执行乘法
                    if (lhsIsConst)
                    {
                        result += "    li.w $t0, " + std::to_string(lhsConstVal) + "\n";
                        lhsReg = "$t0";
                    }
                    if (rhsIsConst)
                    {
                        result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
                        rhsReg = "$t1";
                    }
                    result += "    mul.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
                }
            }
            else
            {
                // 必须使用两个寄存器执行乘法
                if (lhsIsConst)
                {
                    result += "    li.w $t0, " + std::to_string(lhsConstVal) + "\n";
                    lhsReg = "$t0";
                }
                if (rhsIsConst)
                {
                    result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
                    rhsReg = "$t1";
                }
                result += "    mul.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            }
        }
        else if (inst->op_id_ == Instruction::SDiv) {
            // 除法没有立即数版本
            // if (rhsIsConst) {
            //     // 如果是2的幂，可以使用移位
            //     if ((rhsConstVal & (rhsConstVal - 1)) == 0 && rhsConstVal > 0) {
            //         int shift = 0;
            //         int temp = rhsConstVal;
            //         while (temp > 1) {
            //             temp >>= 1;
            //             shift++;
            //         }
            //         // 对于有符号除法，需要处理负数情况
            //         result += "    srai.w $t2, " + lhsReg + ", 31\n";                  // 符号扩展到$t2
            //         result += "    srli.w $t2, $t2, " + std::to_string(32 - shift) + "\n"; // 保留需要的位数
            //         result += "    add.w $t2, " + lhsReg + ", $t2\n";                  // 加上调整值
            //         result += "    srai.w " + destReg + ", $t2, " + std::to_string(shift) + "\n"; // 算术右移
            //     } else {
            //         result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
            //         result += "    div.w " + destReg + ", " + lhsReg + ", $t1\n";
            //     }
            // }
            if(bothConst)
            {
                result += "    li.w " + destReg + ", " + std::to_string(lhsConstVal / rhsConstVal) + "\n";
            }
            else if(rhsIsConst)
            {
                result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
                result += "    div.w " + destReg + ", " + lhsReg + ", $t1\n";
            }
            else if(lhsIsConst)
            {
                result += "    li.w $t0, " + std::to_string(lhsConstVal) + "\n";
                result += "    div.w " + destReg + ", $t0, " + rhsReg + "\n";
            }
            else {
                result += "    div.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            }
        } else if (inst->op_id_ == Instruction::SRem) {
            // printf("SRem %s, %s, %s\n",destReg.c_str(),lhsReg.c_str(),rhsReg.c_str());
            // 取模没有立即数版本
            if (bothConst)
            {
                result += "    li.w " + destReg + ", " + std::to_string(lhsConstVal % rhsConstVal) + "\n";
            }
            else if (rhsIsConst) {
                result += "    li.w $t1, " + std::to_string(rhsConstVal) + "\n";
                result += "    mod.w " + destReg + ", " + lhsReg + ", $t1\n";
            }
            else if(lhsIsConst)
            {
                result += "    li.w $t0, " + std::to_string(lhsConstVal) + "\n";
                result += "    mod.w " + destReg + ", $t0, " + rhsReg + "\n";
            }
            else {
                result += "    mod.w " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            }
        }
        else
        {
            // printf("..\n");
            REPORT_COMPILER_ERROR_AND_EXIT("Unknown type of BinaryInst.");
        }
    }
    // 如果结果需要存储到栈上
    if (storeDest) {
        if (isFloat) {
            // result += "    fst.s " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
            result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
        } else {
            // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
            result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
        }
    }

    // printf("handleBinaryInst end result: %s\n",result.c_str());
    
    return result;
}


std::string AsmEmitter::handleBranchInst(BranchInst* inst)
{
    std::string result;
    
    // 分支指令有两种形式：条件分支和无条件分支
    if (inst->is_cond_br()) {
        // 条件分支: br i1 %cond, label %true_bb, label %false_bb
        Value* condition = inst->get_operand(0);
        BasicBlock* trueBlock = static_cast<BasicBlock*>(inst->get_operand(1));
        BasicBlock* falseBlock = static_cast<BasicBlock*>(inst->get_operand(2));
        
        std::string condReg;
        
        // 获取条件值到寄存器
        if (reg_map.find(condition) != reg_map.end()) {
            condReg = reg_map[condition];
        } else if (stack_map.find(condition) != stack_map.end()) {
            // result += "    # Loading condition from stack\n";
            // result += "    ld.w $t0, $sp, " + std::to_string(stack_map[condition]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t0", stack_map[condition]+currentStackOffset);
            condReg = "$t0";
        } else if (auto* constInt = dynamic_cast<ConstantInt*>(condition)) {
            // 如果条件是常量，根据常量值直接决定分支
            if (constInt->value_ != 0) {
                // 条件为真，无条件跳转到真分支
                // result += "    # Condition is constant true\n";
                result += "    b " + trueBlock->name_ + "\n";
            } else {
                // 条件为假，无条件跳转到假分支
                // result += "    # Condition is constant false\n";
                result += "    b "+ falseBlock->name_ + "\n";
            }
            return result;
        } else {
            // result += "    # Warning: Condition value not found in register or stack\n";
            REPORT_COMPILER_ERROR_AND_EXIT("Condition value is from unknown source");
            // condReg = "$t0";
        }
        
        // 在 LoongArch64 中实现条件分支
        // 1. 检查条件是否为真
        // 2. 如果为真，跳转到真分支
        // 3. 否则，跳转到假分支
        
        // 检查条件是否为0（为0则为假）
        // result += "    # Conditional branch\n";
        result += "    bnez " + condReg + ", "+ trueBlock->name_ + "\n";
        // printf("trueBlock: %s\n", trueBlock->name_.c_str());
        // 如果条件为假，跳转到假分支（无条件跳转，因为前面的条件没有跳转）
        result += "    b " + falseBlock->name_ + "\n";
        // printf("falseBlock: %s\n", falseBlock->name_.c_str());
    } else {
        // 无条件分支: br label %dest
        BasicBlock* destBlock = static_cast<BasicBlock*>(inst->get_operand(0));
        
        // 简单的无条件跳转
        // result += "    # Unconditional branch\n";
        result += "    b " + destBlock->name_ + "\n";
    }
    
    return result;
}

std::string AsmEmitter::handleReturnInst(ReturnInst* inst)
{
    std::string result;
    
    // 如果是void返回，直接返回
    if (inst->num_ops_ == 0) {
        // 恢复栈指针
        if(outOfImmediateRange(currentStackOffset))
        {
            result += "    li.d $t2, " + std::to_string(currentStackOffset) + "\n";
            result += "    add.d $sp, $sp, $t2\n";
        }
        else
        {
            result += "    addi.d $sp, $sp, " + std::to_string(currentStackOffset) + "\n";
        }
        result += "    ld.d $ra, $sp, 8\n";    // 恢复返回地址
        result += "    ld.d $fp, $sp, 0\n";    // 恢复帧指针
        result += "    addi.d $sp, $sp, 16\n";  // 释放栈空间
        result += "    jr $ra\n";              // 返回
        return result;
    }
    
    // 获取返回值
    Value* retVal = inst->get_operand(0);
    std::string retReg;
    
    // 根据返回值类型选择寄存器
    if (retVal->type_ == module->int32_ty_ || retVal->type_ == module->int1_ty_) {
        // 整数返回值放在$a0
        if (reg_map.find(retVal) != reg_map.end()) {
            retReg = reg_map[retVal];
            result += "    or $a0, " + retReg + ", $zero\n";  // 将返回值移动到$a0
        } else if (auto constInt = dynamic_cast<ConstantInt*>(retVal)) {
            // 常量整数直接加载到$a0
            result += "    addi.w $a0, $zero, " + std::to_string(constInt->value_) + "\n";
        } else {
            // 从栈上加载
            if (stack_map.find(retVal) != stack_map.end()) {
                // result += "    ld.w $a0, $sp, " + std::to_string(stack_map[retVal]+currentStackOffset) + "\n";
                result += loadWordFromStack("$a0", stack_map[retVal]+currentStackOffset);
            }
        }
    } else if (retVal->type_ == module->float32_ty_) {
        // 浮点返回值放在$fa0
        if (reg_map.find(retVal) != reg_map.end()) {
            retReg = reg_map[retVal];
            result += "    fmov.s $fa0, " + retReg + "\n";  // 将返回值移动到$fa0
        } else if (auto constFloat = dynamic_cast<ConstantFloat*>(retVal)) {
            // 处理浮点常量，需要先加载到整数寄存器，再转换为浮点寄存器
            float value = constFloat->value_;
            result += "    li.w $t0, " + std::to_string(*(int*)&value) + "\n";
            result += "    movgr2fr.w $fa0, $t0\n";
        } else {
            // 从栈上加载
            if (stack_map.find(retVal) != stack_map.end()) {
                // result += "    fld.s $fa0, $sp, " + std::to_string(stack_map[retVal]+currentStackOffset) + "\n";
                result += loadWordFromStack("$fa0", stack_map[retVal]+currentStackOffset);
            }
        }
    }
    
    // 函数返回序列
    // 恢复栈指针
    if(outOfImmediateRange(currentStackOffset))
    {
        result += "    li.d $t2, " + std::to_string(currentStackOffset) + "\n";
        result += "    add.d $sp, $sp, $t2\n";
    }
    else
    {
        result += "    addi.d $sp, $sp, " + std::to_string(currentStackOffset) + "\n";
    }
    result += "    ld.d $ra, $sp, 8\n";    // 恢复返回地址
    result += "    ld.d $fp, $sp, 0\n";    // 恢复帧指针
    result += "    addi.d $sp, $sp, 16\n";  // 释放栈空间
    result += "    jr $ra\n";              // 返回
    
    return result;
}

std::string AsmEmitter::handleGetElementPtrInst(GetElementPtrInst* inst)
{
    std::string result;
    
    // 获取指令的操作数
    Value* basePtr = inst->get_operand(0);
    
    // 确定指令的目标寄存器
    std::string destReg;
    bool storeDest = false;
    
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else {
        destReg = "$t0";
        storeDest = true;
        // result += "    # Result not mapped to register, using temporary $t0\n";
    }
    
    // 获取基址指针所在寄存器
    std::string baseReg;
    bool baseIsGlobal = false;

    if(stack_offset_map.find(basePtr) != stack_offset_map.end())
    {
        if(outOfImmediateRange(stack_offset_map[basePtr]+currentStackOffset))
        {
            result += "    li.d $t2, " + std::to_string(stack_offset_map[basePtr]+currentStackOffset) + "\n";
            result += "    add.d $t1, $sp, $t2\n";
        }
        else
        {
            result += "    addi.d $t1, $sp, " + std::to_string(stack_offset_map[basePtr]+currentStackOffset) + "\n";
        }
        baseReg = "$t1";
    }
    else if (reg_map.find(basePtr) != reg_map.end()) {
        baseReg = reg_map[basePtr];
    } else if (stack_map.find(basePtr) != stack_map.end()) {
        // result += "    ld.d $t1, $sp, " + std::to_string(stack_map[basePtr]+currentStackOffset) + "\n";
        result += loadDoubleWordFromStack("$t1", stack_map[basePtr]+currentStackOffset);
        baseReg = "$t1";
    } else if (auto* globalVar = dynamic_cast<GlobalVariable*>(basePtr)) {
        result += "    la.global $t1, " + globalVar->name_ + "\n";
        baseReg = "$t1";
        baseIsGlobal = true;
    } else {
        // result += "    # Warning: Base pointer not found in register or stack\n";
        // baseReg = "$t1";
        REPORT_COMPILER_ERROR_AND_EXIT("Base pointer is from unknown source");
    }
    
    // 复制基址到目标寄存器
    result += "    or " + destReg + ", " + baseReg + ", $zero\n";
    // printf("baseReg: %s\n", baseReg.c_str());
    // printf("destReg: %s\n", destReg.c_str());
    
    // 获取指针操作的类型信息
    Type* ptrType = static_cast<PointerType*>(basePtr->type_)->contained_;
    
    // 跟踪当前类型，从基址开始
    Type* currentType = ptrType;
    
    // 处理所有索引
    for (unsigned i = 1; i < inst->num_ops_; i++) {
        Value* indexVal = inst->get_operand(i);
        std::string indexReg;
        bool indexIsConst = false;
        int constIndex = 0;
        
        // 获取索引值到寄存器
        if (auto* constInt = dynamic_cast<ConstantInt*>(indexVal)) {
            // 如果索引是常量，直接使用值
            indexIsConst = true;
            constIndex = constInt->value_;
        } else if (reg_map.find(indexVal) != reg_map.end()) {
            indexReg = reg_map[indexVal];
        } else if (stack_map.find(indexVal) != stack_map.end()) {
            // result += "    ld.w $t2, $sp, " + std::to_string(stack_map[indexVal]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t2", stack_map[indexVal]+currentStackOffset);
            indexReg = "$t2";
        } else {
            REPORT_COMPILER_ERROR_AND_EXIT("Index is from unknown source");
            // result += "    # Warning: Index not found in register or stack\n";
            // indexReg = "$t2";
        }
        
        
        
        // 计算元素偏移
        int elementSize = 0;
        
        // 根据当前类型计算元素大小
        // if (currentType->tid_ == Type::ArrayTyID) {
        //     ArrayType* arrayType = static_cast<ArrayType*>(currentType);
            
        //     // 计算该维度每个元素的字节大小
        //     if (arrayType->contained_->tid_ == Type::IntegerTyID ||
        //         arrayType->contained_->tid_ == Type::FloatTyID) {
        //         printf("int or float type: arrayType->contained_->tid_: %d\n", arrayType->contained_->tid_);
        //         elementSize = 4; // int和float占4字节
        //     } else if (arrayType->contained_->tid_ == Type::ArrayTyID) {
        //         printf("array type: arrayType->contained_->tid_: %d\n", arrayType->contained_->tid_);
        //         // 如果是嵌套数组，计算子数组的总大小
        //         elementSize = calculateArraySize(static_cast<ArrayType*>(arrayType->contained_));
        //     } else {
        //         // 其他类型默认按4字节处理
        //         printf("other type: arrayType->contained_->tid_: %d\n", arrayType->contained_->tid_);
        //         elementSize = 4;
        //     }
            
        //     // 更新为下一级类型
        //     currentType = arrayType->contained_;
        // } else {
        //     // 如果当前类型不是数组，默认为4字节
        //     elementSize = 4;
        // }

        if(currentType->tid_ == Type::ArrayTyID)
        {
            ArrayType* arrayType = static_cast<ArrayType*>(currentType);
            elementSize = calculateArraySize(arrayType);

            currentType = arrayType->contained_;
        }
        else {
            elementSize = 4;
        }

        // printf("elementSize: %d\n", elementSize);
        // result += "    # Element size: " + std::to_string(elementSize) + " bytes\n";

        // 第一个索引要特殊处理，因为是针对指针本身的偏移
        if (i == 1 && !baseIsGlobal) {
            // 对于第一个索引，当是0时可以跳过计算
            if (indexIsConst && constIndex == 0) {
                // result += "    # index is 0, skip calculation\n";
                continue;
            }
        }
        
        // 根据索引计算偏移并加到基址
        if (indexIsConst) {
            // result += "    # offset: " + std::to_string(constIndex * elementSize) + "\n";
            int offset = constIndex * elementSize;
            if (offset != 0) {
                if(outOfImmediateRange(offset))
                {
                    result += "    li.d $t3, " + std::to_string(offset) + "\n";
                    result += "    add.d " + destReg + ", " + destReg + ", $t3\n";
                }
                else
                {
                    result += "    addi.d " + destReg + ", " + destReg + ", " + std::to_string(offset) + "\n";
                }
            }
        } else {
            // result += "    # indexReg: " + indexReg + "\n";
            // 计算 index * elementSize
            if (elementSize == 1) {
                // 如果元素大小是1，不需要乘法
                result += "    add.d " + destReg + ", " + destReg + ", " + indexReg + "\n";
            } else if (elementSize == 2 || elementSize == 4 || elementSize == 8) {
                // 对于2/4/8的元素大小，使用移位来优化
                int shiftAmount = 0;
                if (elementSize == 2) shiftAmount = 1;
                else if (elementSize == 4) shiftAmount = 2;
                else if (elementSize == 8) shiftAmount = 3;
                
                result += "    slli.d $t3, " + indexReg + ", " + std::to_string(shiftAmount) + "\n";
                result += "    add.d " + destReg + ", " + destReg + ", $t3\n";
            } else {
                // 对于其他元素大小，使用乘法
                result += "    li.d $t3, " + std::to_string(elementSize) + "\n"; //改为双字版本
                result += "    mul.d $t3, " + indexReg + ", $t3\n"; //改为双字版本
                result += "    add.d " + destReg + ", " + destReg + ", $t3\n";
            }
        }
    }
    
    // 如果结果需要存储到栈上
    if (storeDest) {
        // result += "    st.d " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        result += storeDoubleWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }
    
    return result;
}


std::string AsmEmitter::generateFunction(Function* func)
{
    // printf("generateFunction\n");
    std::string result;
    for(BasicBlock* bb : func->basic_blocks_)
    {
        bb->name_ = func->name_ + "_" + bb->name_;
    }
    result += generateFunctionPrologue(func);
    // result += handleAllAlloca(func);
    
    for(BasicBlock* bb : func->basic_blocks_)
    {
        // result += "    # Basic block: " + bb->name_ + "\n";
        // if(bb->name_.compare("label_entry") != 0)
        // {
        result += bb->name_ + ":\n";
        // }
        for(Instruction* inst : bb->instr_list_)
        {
            if(auto* allocaInst = dynamic_cast<AllocaInst* >(inst))
            {
                continue;
            }
            else if(auto* storeInst = dynamic_cast<StoreInst*>(inst))
            {
                result += handleStore(storeInst);
            }
            else if(auto* loadInst = dynamic_cast<LoadInst*>(inst))
            {
                result += handleLoad(loadInst);
            }
            else if(auto* siToFpInst = dynamic_cast<SiToFpInst*>(inst))
            {
                result += handleSiToFp(siToFpInst);
            }
            else if(auto* fpToSiInst = dynamic_cast<FpToSiInst*>(inst))
            {
                result += handleFpToSi(fpToSiInst);
            }
            else if(auto* binaryInst = dynamic_cast<BinaryInst*>(inst))
            {
                result += handleBinaryInst(binaryInst);
            }
            else if(auto* icmpInst = dynamic_cast<ICmpInst*>(inst))
            {
                result += handleICmpInst(icmpInst);
            }
            else if(auto* fcmpInst = dynamic_cast<FCmpInst*>(inst))
            {
                result += handleFCmpInst(fcmpInst);
            }
            else if(auto* callInst = dynamic_cast<CallInst*>(inst))
            {
                result += handleCallInst(callInst);
            }
            else if(auto* branchInst = dynamic_cast<BranchInst*>(inst))
            {
                result += handleBranchInst(branchInst);
            }
            else if(auto* phiInst = dynamic_cast<PhiInst*>(inst))
            {
                // result += handlePhiInst(phiInst);
            }
            else if(auto* returnInst = dynamic_cast<ReturnInst*>(inst))
            {
                result += handleReturnInst(returnInst);
            }
            else if(auto* zextInst = dynamic_cast<ZextInst*>(inst))
            {
                result += handleZextInst(zextInst);
            }
            else if(auto* bitcastInst = dynamic_cast<Bitcast*>(inst))
            {
                result += handleBitcastInst(bitcastInst);
            }
            else if(auto* getElementPtrInst = dynamic_cast<GetElementPtrInst*>(inst))
            {
                result += handleGetElementPtrInst(getElementPtrInst);
            }
            // std::cout<< inst->print()<<":\n"<<result<<"\n------\n"<<std::endl;
        }
    }
    // printf("generateFunction end\n");

    return result;
}

int AsmEmitter::getZeroCount(ConstantZero* constantZero)//得到ConstantZero中0的个数
{
    int result = 1;
    if(constantZero->type_->tid_ == Type::ArrayTyID)
    {
        auto arrayType = static_cast<ArrayType*>(constantZero->type_);
        result *= arrayType->num_elements_;
        while(arrayType->contained_->tid_ == Type::ArrayTyID)
        {
            arrayType = static_cast<ArrayType*>(arrayType->contained_);
            result *= arrayType->num_elements_;
        }
        // result *= arrayType->num_elements_;
    }
    if(result<=0)
    {
        REPORT_COMPILER_ERROR_AND_EXIT("Zero count is less than 0");
    }
    // printf("Zero count: %d\n", result);
    return result;
}

std::vector<Constant*> AsmEmitter::getArrayInitVal(ConstantArray* init_array)
{
    std::vector<Constant*> result;
    for(Constant* element : init_array->const_array)
    {
        if(dynamic_cast<ConstantArray*>(element) != nullptr)
        {
            auto sub_array = dynamic_cast<ConstantArray*>(element);
            auto sub_result = getArrayInitVal(sub_array);
            result.insert(result.end(), sub_result.begin(), sub_result.end());
        }
        else
        {
            result.push_back(element);
        }
    }
    return result;
}

std::string AsmEmitter::generateGlobalVar(GlobalVariable* globalVar)
{
    // printf("generateGlobalVar\n");
    std::string result;
    // std::cout<<globalVar->print()<<std::endl;
    // std::cout<<globalVar->type_->print()<<std::endl;
    if(dynamic_cast<PointerType*>(globalVar->type_) == nullptr)
    {
        REPORT_COMPILER_ERROR_AND_EXIT("Global variable is not a pointer");
    }
    auto varType = dynamic_cast<PointerType*>(globalVar->type_)->contained_;
    // result += ".globl " + globalVar->name_ + "\n";
    // result += ".p2align 2\n";
    result += ".globl " + globalVar->name_ + "\n";
    result += ".p2align 2\n";
    result += globalVar->name_ + ":\n";
    if(varType->tid_ == Type::ArrayTyID)
    {

        // printf("generateGlobalVar: Array type\n");
        auto init_array = dynamic_cast<ConstantArray*>(globalVar->init_val_);
        auto zero_init_array = dynamic_cast<ConstantZero*>(globalVar->init_val_);
        int lastZeroCount = 0;
        if(init_array != nullptr)
        {
            int nonZeroBound = 0;
            auto init_val = getArrayInitVal(init_array);
            for(int i = init_val.size() - 1; i >= 0; i--)
            {
                if(dynamic_cast<ConstantZero*>(init_val[i]) == nullptr)
                {
                    nonZeroBound = i+1;
                    break;
                }
                else
                {
                    lastZeroCount += getZeroCount(dynamic_cast<ConstantZero*>(init_val[i]));
                }
            }
            for(int i = 0; i < nonZeroBound; i++)
            {
                Constant* element = init_val[i];
                if(dynamic_cast<ConstantFloat*>(element) != nullptr)
                {
                    result += ".float " + std::to_string(dynamic_cast<ConstantFloat*>(element)->value_) + "\n";
                }
                else if(dynamic_cast<ConstantInt*>(element) != nullptr)
                {
                    result += ".word " + std::to_string(dynamic_cast<ConstantInt*>(element)->value_) + "\n";
                }
                else if(dynamic_cast<ConstantZero*>(element) != nullptr)
                {
                    // printf("generateGlobalVar: Zero count: %d\n", getZeroCount(dynamic_cast<ConstantZero*>(element)));
                    result += ".zero " + std::to_string(getZeroCount(dynamic_cast<ConstantZero*>(element)) * 4) + "\n";
                }
                else
                {
                    // printf("generateGlobalVar: Unsupported global variable type\n");
                    REPORT_COMPILER_ERROR_AND_EXIT("Unsupported global variable type");
                }
            }
            
        }
        else
        {
            lastZeroCount = getZeroCount(zero_init_array);

        }
        // auto array = dynamic_cast<ArrayType*>(dynamic_cast<PointerType*>(globalVar->type_)->contained_);
        

        
        result += ".zero " + std::to_string( lastZeroCount * 4) + "\n";
        // result += ".zero " + std::to_string( (dynamic_cast<ConstantArray*>(globalVar->init_val_)->const_array.size() - nonZeroBound) * 4) + "\n";
    }
    else
    {
        // printf("generateGlobalVar: Non-array type\n");
        
        if(varType == module->float32_ty_)
        {
            result += ".float " + std::to_string((globalVar->init_val_ == nullptr) ? 0 : dynamic_cast<ConstantFloat*>(globalVar->init_val_)->value_) + "\n";
        }
        else if(varType == module->int32_ty_ || varType == module->int1_ty_)
        {
            result += ".word " + std::to_string((globalVar->init_val_ == nullptr) ? 0 : dynamic_cast<ConstantInt*>(globalVar->init_val_)->value_) + "\n";
        }
        else    
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Unsupported global variable type");
        }
    }
    // printf("generateGlobalVar end\n");
    return result;
}


std::string AsmEmitter::generateGlobalArrayInBss(GlobalVariable* globalVar)
{
    std::string result;
    assert(globalVar->type_->tid_ == Type::ArrayTyID);

    ArrayType* arrayType = static_cast<ArrayType*>(globalVar->type_);
    int64_t size = calculateArraySize(arrayType);

    result += ".globl " + globalVar->name_ + "\n";
    result += ".p2align 2\n";
    result += globalVar->name_ + ":\n";
    result += ".space " + std::to_string(size) + "\n";
    return result;
}

std::string AsmEmitter::emit()
{
    std::string assemblyText = ".text\n";
    std::string assemblyData = ".data\n";
    std::string assemblyBss = ".bss\n";
    for(GlobalVariable* globalVar : module->global_list_)
    {
        if(globalVar->type_->tid_ == Type::ArrayTyID && dynamic_cast<ConstantZero*>(globalVar->init_val_) != nullptr)
        {
            assemblyBss += generateGlobalArrayInBss(globalVar);
        }
        else
        {
            assemblyData += generateGlobalVar(globalVar);
        }
    }
    // printf("22.\n");
    for(Function* func : module->function_list_)
    {
        // printf("func: %s\n", func->name_.c_str());
        if(func->is_declaration())
        {
            changed_regs_map.insert(std::make_pair(func, std::make_pair(std::set<std::string>(int_regs.begin(),int_regs.end()), std::set<std::string>(float_regs.begin(),float_regs.end()))));
            //认为外部函数修改了所有可能的寄存器
            continue;
        }
        assemblyText += ".globl " + func->name_ + "\n";
        assemblyText += ".type " + func->name_ + ", @function\n";
        assemblyText += generateFunction(func);
        
    }
    // printf("33.\n");

    return assemblyText + assemblyData + assemblyBss;
}

// std::string AsmEmitter::handleICmpInst(ICmpInst* inst)
// {
//     std::string result;
//     Value* lhs = inst->get_operand(0);
//     Value* rhs = inst->get_operand(1);

//     std::string lhsReg;
//     std::string rhsReg;
//     std::string destReg;

//     if(reg_map.find(inst) != reg_map.end())
//     {
//         destReg = reg_map[inst];
//     }
//     else
//     {
//         destReg = "$t0";
//     }

//     if(reg_map.find(lhs) != reg_map.end())
//     {
//         lhsReg = reg_map[lhs];
//     }
//     else
//     {
//         lhsReg = "$t0";
//     }
//     if(reg_map.find(rhs) != reg_map.end())
//     {
//         rhsReg = reg_map[rhs];
//     }
//     else
//     {
//         rhsReg = "$t1";
//     }
    

std::string AsmEmitter::handleICmpInst(ICmpInst* inst)
{
    std::string result;
    Value* lhs = inst->get_operand(0);
    Value* rhs = inst->get_operand(1);
    ICmpInst::ICmpOp op = inst->icmp_op_;
    
    // 确定目标寄存器
    std::string destReg;
    bool storeDest = false;
    
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else {
        destReg = "$t0";
        storeDest = true;
        // result += "    # Result not mapped to register, using $t0\n";
    }
    
    // 获取左操作数到寄存器
    std::string lhsReg;
    if (reg_map.find(lhs) != reg_map.end()) {
        lhsReg = reg_map[lhs];
    } else if (stack_map.find(lhs) != stack_map.end()) {
        // result += "    ld.w $t1, $sp, " + std::to_string(stack_map[lhs]+currentStackOffset) + "\n";
        result += loadWordFromStack("$t1", stack_map[lhs]+currentStackOffset);
        lhsReg = "$t1";
    } else if (auto* constInt = dynamic_cast<ConstantInt*>(lhs)) {
        result += "    li.w $t1, " + std::to_string(constInt->value_) + "\n";
        lhsReg = "$t1";
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Left operand is from unknown source");
        // result += "    # Warning: Left operand not found in register or stack\n";
        // lhsReg = "$t1";
    }
    
    // 获取右操作数到寄存器
    std::string rhsReg;
    if (reg_map.find(rhs) != reg_map.end()) {
        rhsReg = reg_map[rhs];
    } else if (stack_map.find(rhs) != stack_map.end()) {
        // result += "    ld.w $t2, $sp, " + std::to_string(stack_map[rhs]+currentStackOffset) + "\n";
        result += loadWordFromStack("$t2", stack_map[rhs]+currentStackOffset);
        rhsReg = "$t2";
    } else if (auto* constInt = dynamic_cast<ConstantInt*>(rhs)) {
        result += "    li.w $t2, " + std::to_string(constInt->value_) + "\n";
        rhsReg = "$t2";
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Right operand is from unknown source");
        // result += "    # Warning: Right operand not found in register or stack\n";
        // rhsReg = "$t2";
    }
    // 在LoongArch64中实现各种整数比较操作
    // result += "    # Integer comparison: " + ICmpInst::ICmpOpName.at(op) + "\n";
    
    switch (op) {
        case ICmpInst::ICMP_EQ:
            // printf("ICMP_EQ:\n");
            // std::cout<<lhs->print()<<std::endl;
            // std::cout<<rhs->print()<<std::endl;
            // 相等 (a == b) => 如果a==b，设置为1，否则为0
            result += "    xor $t3, " + lhsReg + ", " + rhsReg + "\n";
            result += "    sltui " + destReg + ", $t3, 1\n";  // t3为0时设为1，否则为0
            break;
            
        case ICmpInst::ICMP_NE:
            // 不等 (a != b) => 如果a!=b，设置为1，否则为0
            result += "    xor $t3, " + lhsReg + ", " + rhsReg + "\n";
            result += "    sltu " + destReg + ", $zero, $t3\n";  // t3非0时设为1，否则为0
            break;
            
        case ICmpInst::ICMP_SGT:
            // 有符号大于 (a > b) => 如果a>b，设置为1，否则为0
            result += "    slt " + destReg + ", " + rhsReg + ", " + lhsReg + "\n";
            break;
            
        case ICmpInst::ICMP_SGE:
            // 有符号大于等于 (a >= b) => 如果a>=b，设置为1，否则为0
            result += "    slt " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            result += "    xori " + destReg + ", " + destReg + ", 1\n";  // 取反
            break;
            
        case ICmpInst::ICMP_SLT:
            // 有符号小于 (a < b) => 如果a<b，设置为1，否则为0
            result += "    slt " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            break;
            
        case ICmpInst::ICMP_SLE:
            // 有符号小于等于 (a <= b) => 如果a<=b，设置为1，否则为0
            result += "    slt " + destReg + ", " + rhsReg + ", " + lhsReg + "\n";
            result += "    xori " + destReg + ", " + destReg + ", 1\n";  // 取反
            break;
            
        case ICmpInst::ICMP_UGT:
            // 无符号大于 (a > b) => 如果a>b，设置为1，否则为0
            result += "    sltu " + destReg + ", " + rhsReg + ", " + lhsReg + "\n";
            break;
            
        case ICmpInst::ICMP_UGE:
            // 无符号大于等于 (a >= b) => 如果a>=b，设置为1，否则为0
            result += "    sltu " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            result += "    xori " + destReg + ", " + destReg + ", 1\n";  // 取反
            break;
            
        case ICmpInst::ICMP_ULT:
            // 无符号小于 (a < b) => 如果a<b，设置为1，否则为0
            result += "    sltu " + destReg + ", " + lhsReg + ", " + rhsReg + "\n";
            break;
            
        case ICmpInst::ICMP_ULE:
            // 无符号小于等于 (a <= b) => 如果a<=b，设置为1，否则为0
            result += "    sltu " + destReg + ", " + rhsReg + ", " + lhsReg + "\n";
            result += "    xori " + destReg + ", " + destReg + ", 1\n";  // 取反
            break;
            
        default:
            // result += "    # Warning: Unsupported ICmp operation\n";
            REPORT_COMPILER_ERROR_AND_EXIT("Unsupported ICmp operation");
            break;
    }
    
    // 如果结果需要存储到栈上
    if (storeDest) {
        // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }
    
    return result;
}


std::string AsmEmitter::handleFCmpInst(FCmpInst* inst)
{
    std::string result;
    Value* lhs = inst->get_operand(0);
    Value* rhs = inst->get_operand(1);
    FCmpInst::FCmpOp op = inst->fcmp_op_;
    
    // 确定目标寄存器
    std::string destReg;
    bool storeDest = false;
    
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else {
        destReg = "$t0";
        storeDest = true;
        // result += "    # Result not mapped to register, using $t0\n";
    }
    
    // 获取左操作数到浮点寄存器
    std::string lhsReg;
    if (reg_map.find(lhs) != reg_map.end()) {
        std::string srcReg = reg_map[lhs];
        if (srcReg[1] == 'f') {
            lhsReg = srcReg;
        } else {
            // 如果在整数寄存器，需要移到浮点寄存器
            result += "    movgr2fr.w $ft1, " + srcReg + "\n";
            lhsReg = "$ft1";
        }
    } else if (stack_map.find(lhs) != stack_map.end()) {
        // result += "    fld.s $ft1, $sp, " + std::to_string(stack_map[lhs]+currentStackOffset) + "\n";  
        result += loadWordFromStack("$ft1", stack_map[lhs]+currentStackOffset);
        lhsReg = "$ft1";
    } else if (auto* constFloat = dynamic_cast<ConstantFloat*>(lhs)) {
        // 加载浮点常量
        float value = constFloat->value_;
        result += "    li.w $t1, " + std::to_string(*(int*)&value) + "\n";
        result += "    movgr2fr.w $ft1, $t1\n";
        lhsReg = "$ft1";
    } else {
        // result += "    # Warning: Left operand not found in register or stack\n";
        lhsReg = "$ft1";
    }
    
    // 获取右操作数到浮点寄存器
    std::string rhsReg;
    if (reg_map.find(rhs) != reg_map.end()) {
        std::string srcReg = reg_map[rhs];
        if (srcReg[1] == 'f') {
            rhsReg = srcReg;
        } else {
            // 如果在整数寄存器，需要移到浮点寄存器
            result += "    movgr2fr.w $ft2, " + srcReg + "\n";
            rhsReg = "$ft2";
        }
    } else if (stack_map.find(rhs) != stack_map.end()) {
        // result += "    fld.s $ft2, $sp, " + std::to_string(stack_map[rhs]+currentStackOffset) + "\n";
        result += loadWordFromStack("$ft2", stack_map[rhs]+currentStackOffset);
        rhsReg = "$ft2";
    } else if (auto* constFloat = dynamic_cast<ConstantFloat*>(rhs)) {
        // 加载浮点常量
        float value = constFloat->value_;
        result += "    li.w $t2, " + std::to_string(*(int*)&value) + "\n";
        result += "    movgr2fr.w $ft2, $t2\n";
        rhsReg = "$ft2";
    } else {
        // result += "    # Warning: Right operand not found in register or stack\n";
        rhsReg = "$ft2";
    }
    
    // 在LoongArch64中实现各种浮点比较操作
    // result += "    # Float comparison: " + FCmpInst::FCmpOpName.at(op) + "\n";
    
    // LoongArch的fcmp.cond.s指令将结果存储在浮点标志寄存器中
    // 需要使用条件分支指令将结果转移到目标寄存器
    
    // 对于FCMP_FALSE和FCMP_TRUE，直接设置结果
    if (op == FCmpInst::FCMP_FALSE) {
        result += "    ori " + destReg + ", $zero, 0\n";
    } else if (op == FCmpInst::FCMP_TRUE) {
        result += "    ori " + destReg + ", $zero, 1\n";
    } else {
        // 为比较操作创建标签
        std::string trueLabel = "fcmp_true_" + std::to_string(fcmp_label_counter_);
        std::string endLabel = "fcmp_end_" + std::to_string(fcmp_label_counter_++);
        
        // 根据不同的比较操作生成相应的代码
        switch (op) {
            // case FCmpInst::FCMP_OEQ:
            case FCmpInst::FCMP_UEQ:
                // 等于 (a == b)
                result += "    fcmp.ceq.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
                break;
                
            // case FCmpInst::FCMP_OGT:
            case FCmpInst::FCMP_UGT:
                // 大于 (a > b)
                result += "    fcmp.clt.s $fcc0, " + rhsReg + ", " + lhsReg + "\n";
                break;
                
            // case FCmpInst::FCMP_OGE:
            case FCmpInst::FCMP_UGE:
                // 大于等于 (a >= b)
                result += "    fcmp.cle.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
                result += "    fcmp.cne.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";  // 取反
                break;
                
            // case FCmpInst::FCMP_OLT:
            case FCmpInst::FCMP_ULT:
                // 小于 (a < b)
                result += "    fcmp.clt.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
                break;
                
            // case FCmpInst::FCMP_OLE:
            case FCmpInst::FCMP_ULE:
                // 小于等于 (a <= b)
                result += "    fcmp.cle.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
                break;
                
            // case FCmpInst::FCMP_ONE:
            case FCmpInst::FCMP_UNE:
                // 不等于 (a != b)
                result += "    fcmp.cne.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
                break;
                
            // case FCmpInst::FCMP_ORD:
            //     // 两个操作数都是有序值（不是NaN）
            //     result += "    fcmp.cor.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
            //     break;
                
            case FCmpInst::FCMP_UNO:
                // 至少一个操作数是无序值（是NaN）
                result += "    fcmp.cun.s $fcc0, " + lhsReg + ", " + rhsReg + "\n";
                break;
                
            default:
                REPORT_COMPILER_ERROR_AND_EXIT("Unsupported FCmp operation");
                // result += "    # Warning: Unsupported FCmp operation, defaulting to false\n";
                // result += "    ori " + destReg + ", $zero, 0\n";
                // // 如果不支持的操作，直接返回
                // if (storeDest) {
                //     result += "    st.w " + destReg + ", $fp, " + std::to_string(stack_map[inst]) + "\n";
                // }
                return result;
        }
        
        // 根据条件设置结果
        result += "    ori " + destReg + ", $zero, 0\n";        // 先设置为0（假）
        result += "    bcnez $fcc0, " + trueLabel + "\n";       // 如果条件为真，跳转
        result += "    b " + endLabel + "\n";                   // 否则直接到结束
        result += trueLabel + ":\n";
        result += "    ori " + destReg + ", $zero, 1\n";        // 设置为1（真）
        result += endLabel + ":\n";
    }
    
    // 如果结果需要存储到栈上
    if (storeDest) {
        // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }
    
    return result;
}






    
    


std::string AsmEmitter::handleBitcastInst(Bitcast* inst)
{
    std::string result;
    Value* srcVal = inst->get_operand(0);
    Type* destType = inst->dest_ty_;
    
    // 确定目标寄存器
    std::string destReg;
    bool storeDest = false;
    
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else {
        // 如果目标是浮点类型，使用浮点临时寄存器
        if (destType->tid_ == Type::FloatTyID) {
            destReg = "$ft0";
        } else {
            destReg = "$t0";
        }
        storeDest = true;
        // result += "    # Result not mapped to register, using " + destReg + "\n";
    }
    
    // 获取源操作数
    std::string srcReg;
    
    // printf("srcVal: %s\n", srcVal->print().c_str());

    if(stack_offset_map.find(srcVal) != stack_offset_map.end())
    {
        // printf("srcVal in stack_offset_map, stack_offset_map[srcVal]: %d\n", stack_offset_map[srcVal]);
        if(outOfImmediateRange(stack_offset_map[srcVal]+currentStackOffset))
        {
            result += "    li.d $t4, " + std::to_string(stack_offset_map[srcVal]+currentStackOffset) + "\n";
            result += "    add.d $t1, $sp, $t4\n";
        }
        else
        {
            result += "    addi.d $t1, $sp, " + std::to_string(stack_offset_map[srcVal]+currentStackOffset) + "\n";
        }
        srcReg = "$t1";
    }
    else if (reg_map.find(srcVal) != reg_map.end()) {
        // printf("srcVal in reg_map, reg_map[srcVal]: %s\n", reg_map[srcVal].c_str());
        srcReg = reg_map[srcVal];
    } else if (stack_map.find(srcVal) != stack_map.end()) {
        // 根据源类型选择适当的加载指令
        if (srcVal->type_->tid_ == Type::FloatTyID) {
            // result += "    fld.s $ft1, $sp, " + std::to_string(stack_map[srcVal]+currentStackOffset) + "\n";
            result += loadWordFromStack("$ft1", stack_map[srcVal]+currentStackOffset);
            srcReg = "$ft1";
        } else {
            // result += "    ld.w $t1, $sp, " + std::to_string(stack_map[srcVal]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t1", stack_map[srcVal]+currentStackOffset);
            srcReg = "$t1";
        }
    }
    // else if (stack_offset_map.find(srcVal) != stack_offset_map.end()) {
    //     printf("srcVal in stack_offset_map, stack_offset_map[srcVal]: %d\n", stack_offset_map[srcVal]);
    //     result += "    add.d $t1, $fp, " + std::to_string(stack_offset_map[srcVal]) + "\n";
    //     srcReg = "$t1";
    // } 
    else {
        REPORT_COMPILER_ERROR_AND_EXIT("Source value is from unknown source");
        // result += "    # Warning: Source value not found in register or stack\n";
        // if (srcVal->type_->tid_ == Type::FloatTyID) {
        //     srcReg = "$ft1";
        // } else {
        //     srcReg = "$t1";
        // }
    }
    
    // 处理不同类型的转换情况
    // int <-> float 位转换 (位模式保持不变，只改变解释方式)
    if ((srcVal->type_->tid_ == Type::IntegerTyID && destType->tid_ == Type::FloatTyID) ||
        (srcVal->type_->tid_ == Type::FloatTyID && destType->tid_ == Type::IntegerTyID)) {
        
        if (srcVal->type_->tid_ == Type::IntegerTyID) {
            // 整数 -> 浮点 (位模式不变)
            // result += "    # Bitcast int to float\n";
            result += "    movgr2fr.w " + destReg + ", " + srcReg + "\n";
        } else {
            // 浮点 -> 整数 (位模式不变)
            // result += "    # Bitcast float to int\n";
            result += "    movfr2gr.s " + destReg + ", " + srcReg + "\n";
        }
    }
    // 数组或结构体指针转换为另一类型指针，在IRGenerator中只出现了这种用法
    else if (srcVal->type_->tid_ == Type::PointerTyID && destType->tid_ == Type::PointerTyID) {
        // 指针转换 - 通常只是重新解释指针，不需要实际操作
        // result += "    # Pointer type conversion (no operation needed)\n";
        if (srcReg != destReg) {
            result += "    or " + destReg + ", " + srcReg + ", $zero\n";
        }
    }
    // 其他类型转换，如整数间的位转换
    else {
        // 大多数情况下只需要复制值
        // result += "    # Generic bitcast\n";
        if (srcReg != destReg) {
            if (destReg[1] == 'f' && srcReg[1] != 'f') {
                result += "    movgr2fr.w " + destReg + ", " + srcReg + "\n";
            } else if (destReg[1] != 'f' && srcReg[1] == 'f') {
                result += "    movfr2gr.s " + destReg + ", " + srcReg + "\n";
            } else if (destReg[1] == 'f' && srcReg[1] == 'f') {
                result += "    fmov.s " + destReg + ", " + srcReg + "\n";
            } else {
                result += "    or " + destReg + ", " + srcReg + ", $zero\n";
            }
        }
    }
    
    // 如果结果需要存储到栈上
    if (storeDest) {

        // if (destReg[1] == 'f') {
        //     // result += "    fst.s " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";  
        //     result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
        // } else {
        //     // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        //     result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
        // }

        result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }
    
    return result;
}

std::string AsmEmitter::handleZextInst(ZextInst* inst)
{
    std::string result;
    Value* srcVal = inst->get_operand(0);
    Type* destType = inst->dest_ty_;
    

    // result+= "    # handleZextInst\n";
    // 确定目标寄存器
    std::string destReg;
    bool storeDest = false;
    
    if (reg_map.find(inst) != reg_map.end()) {
        destReg = reg_map[inst];
    } else {
        destReg = "$t0";
        storeDest = true;
        // result += "    # Result not mapped to register, using $t0\n";
    }
    
    // 获取源操作数
    std::string srcReg;
    
    if (reg_map.find(srcVal) != reg_map.end()) {
        srcReg = reg_map[srcVal];
    } else if (stack_map.find(srcVal) != stack_map.end()) {
        // result += "    ld.w $t1, $sp, " + std::to_string(stack_map[srcVal]+currentStackOffset) + "\n";
        result += loadWordFromStack("$t1", stack_map[srcVal]+currentStackOffset);
        srcReg = "$t1";
    } else if (auto* constInt = dynamic_cast<ConstantInt*>(srcVal)) {
        // 如果源是常量，直接使用值
        int value = constInt->value_;
        // 确保符合目标类型的宽度
        if (destType->tid_ == Type::IntegerTyID) {
            int width = static_cast<IntegerType*>(destType)->num_bits_;
            if (width == 32) {
                // 扩展到32位
                result += "    li.w " + destReg + ", " + std::to_string(value & 0xFFFFFFFF) + "\n";
                if (storeDest) {
                    // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
                    result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
                }
                return result;
            }
        }
        result += "    li.w $t1, " + std::to_string(value) + "\n";
        srcReg = "$t1";
    } else {
        REPORT_COMPILER_ERROR_AND_EXIT("Source value is from unknown source");
        // result += "    # Warning: Source value not found in register or stack\n";
        // srcReg = "$t1";
    }
    
    // 处理从i1到i32的零扩展
    // i1在LLVM中通常代表布尔值（0或1）
    if (srcVal->type_->tid_ == Type::IntegerTyID && 
        static_cast<IntegerType*>(srcVal->type_)->num_bits_ == 1 &&
        destType->tid_ == Type::IntegerTyID &&
        static_cast<IntegerType*>(destType)->num_bits_ == 32) {
        
        // 掩码操作：保留最低位，其余位清零
        // result += "    # Zero extend i1 to i32\n";
        result += "    andi " + destReg + ", " + srcReg + ", 1\n";
    }
    // 其他整数零扩展
    else if (srcVal->type_->tid_ == Type::IntegerTyID && destType->tid_ == Type::IntegerTyID) {
        int srcBits = static_cast<IntegerType*>(srcVal->type_)->num_bits_;
        int destBits = static_cast<IntegerType*>(destType)->num_bits_;
        
        if (srcBits < destBits) {
            // 创建掩码，保留源类型宽度的位
            uint32_t mask = (1ULL << srcBits) - 1;
            // result += "    # Zero extend i" + std::to_string(srcBits) + " to i" + std::to_string(destBits) + "\n";
            result += "    andi " + destReg + ", " + srcReg + ", " + std::to_string(mask) + "\n";
        } else {
            // 源和目标宽度相同或源比目标宽
            // result += "    # Warning: Source width >= destination width in zext\n";
            if (srcReg != destReg) {
                result += "    or " + destReg + ", " + srcReg + ", $zero\n";
            }
        }
    }
    // 其他类型的零扩展，默认直接复制
    else {
        // result += "    # Unsupported zext operation, copying value\n";
        if (srcReg != destReg) {
            result += "    or " + destReg + ", " + srcReg + ", $zero\n";
        }
    }
    
    // 如果结果需要存储到栈上
    if (storeDest) {
        // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
        result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
    }
    
    return result;
}
bool AsmEmitter::isLeafFunction(Function* func)
{
    // 检查函数是否是叶子函数（不调用其他函数）
    for (BasicBlock* bb : func->basic_blocks_) {
        for (Instruction* inst : bb->instr_list_) {
            if (dynamic_cast<CallInst*>(inst)) {
                // 如果找到任何调用指令，则不是叶子函数
                return false;
            }
        }
    }
    // 如果没有找到任何调用指令，则是叶子函数
    return true;
}

std::string AsmEmitter::handleCallInst(CallInst* inst)
{
    std::string result;
    
    // 获取被调用的函数
    Function* calledFunc = static_cast<Function*>(inst->get_operand(inst->num_ops_ - 1));
    std::string funcName = calledFunc->name_;

    // 检查是否调用的是 llvm.memset.p0.i32 函数
    // printf("funcName: %s\n", funcName.c_str());
    if (funcName.compare("llvm.memset.p0.i32") == 0) {
        // result += "    # Handling llvm.memset.p0.i32 intrinsic\n";
        // printf("handleCallInst: llvm.memset.p0.i32\n");


        // 获取参数：
        // 第一个参数：目标内存地址
        // 获取参数：
        // 第一个参数：目标内存地址
        // 第二个参数：填充值（通常为0）
        // 第三个参数：字节大小
        // 第四个参数：是否为易失性操作（忽略）
        Value* dstPtr = inst->get_operand(0);
        Value* valPtr = inst->get_operand(1);
        Value* sizeVal = inst->get_operand(2);
        // Value* volatileVal = inst->get_operand(3); // 在生成汇编时通常忽略这个参数
        
        // 获取目标地址的寄存器
        std::string dstReg;
        if(stack_offset_map.find(dstPtr) != stack_offset_map.end())
        {
            if(outOfImmediateRange(stack_offset_map[dstPtr]+currentStackOffset))
            {
                result += "    li.d $t4, " + std::to_string(stack_offset_map[dstPtr]+currentStackOffset) + "\n";
                result += "    add.d $t0, $sp, $t4\n";
            }
            else
            {
                result += "    addi.d $t0, $sp, " + std::to_string(stack_offset_map[dstPtr]+currentStackOffset) + "\n";
            }
            dstReg = "$t0";
        }
        else if (reg_map.find(dstPtr) != reg_map.end()) {
            dstReg = reg_map[dstPtr];
        } else if (stack_map.find(dstPtr) != stack_map.end()) {
            // result += "    ld.w $t0, $sp, " + std::to_string(stack_map[dstPtr]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t0", stack_map[dstPtr]+currentStackOffset);
            dstReg = "$t0";
        } else {
            REPORT_COMPILER_ERROR_AND_EXIT("Destination pointer is from unknown source");
        }
        
        // 获取填充值（通常为0，但这里做了通用处理）
        int fillValue = 0;
        if (auto* constInt = dynamic_cast<ConstantInt*>(valPtr)) {
            fillValue = constInt->value_ & 0xFF; // 只取低8位作为填充字节
        } else {
            // 如果填充值不是常量，需要额外获取（实际中很少见）
            std::string valReg;
            if (reg_map.find(valPtr) != reg_map.end()) {
                valReg = reg_map[valPtr];
                result += "    andi $t1, " + valReg + ", 0xff\n"; // 确保只保留低8位
                valReg = "$t1";
            } else if (stack_map.find(valPtr) != stack_map.end()) {
                // result += "    ld.w $t1, $sp, " + std::to_string(stack_map[valPtr]+currentStackOffset) + "\n";
                result += loadWordFromStack("$t1", stack_map[valPtr]+currentStackOffset);
                result += "    andi $t1, $t1, 0xff\n"; 
                valReg = "$t1";
            } else {
                REPORT_COMPILER_ERROR_AND_EXIT("Fill value is from unknown source");
            }
            
            // 注意：对于非0填充值的情况，后续代码需要使用valReg而不是0
            // 本实现重点关注常见的0填充情况
        }
        
        // 获取大小的寄存器或常量值
        int constSize = -1;
        std::string sizeReg;
        if (auto* constInt = dynamic_cast<ConstantInt*>(sizeVal)) {
            constSize = constInt->value_;
        } else if (reg_map.find(sizeVal) != reg_map.end()) {
            sizeReg = reg_map[sizeVal];
        } else if (stack_map.find(sizeVal) != stack_map.end()) {
            // result += "    ld.w $t2, $sp, " + std::to_string(stack_map[sizeVal]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t2", stack_map[sizeVal]+currentStackOffset);
            sizeReg = "$t2";
        } else {
            REPORT_COMPILER_ERROR_AND_EXIT("Size value is from unknown source");
        }
        
        // memset 实现
        // 针对 fillValue = 0 的常见情况进行了优化
        // 对于非0填充值，需要将所有的 $zero 替换为包含填充值的寄存器
        if(fillValue != 0)
        {
            //todo: 需要支持非0填充值
            REPORT_COMPILER_ERROR_AND_EXIT("Fill value is not 0");
        }
        // 对于fillValue为0的情况，可以直接使用$zero寄存器
        std::string fillReg = "$zero";
        // 对于非0填充值，需要准备填充模式
        if (fillValue != 0) {
            result += "    li.w $t9, " + std::to_string(fillValue) + "\n";
            // 创建一个4字节的填充模式 (复制相同的字节到4个位置)
            result += "    andi $t9, $t9, 0xff\n";                  // 确保只有低8位
            result += "    bstrpick.d $t8, $t9, 7, 0\n";            // 提取低8位
            result += "    slli.d $t7, $t8, 8\n";                   // 左移8位
            result += "    or $t9, $t9, $t7\n";                     // 合并
            result += "    slli.d $t7, $t9, 16\n";                  // 左移16位
            result += "    or $t9, $t9, $t7\n";                     // 合并，现在$t9包含4份相同的字节
            fillReg = "$t9";
        }
        
        if (constSize > 0) {
            // 如果是常量大小且较小，直接生成多条填充指令
            if (constSize <= 32) {
                int numWords = (constSize + 3) / 4; // 向上取整到字边界
                for (int i = 0; i < numWords; i++) {
                    if (i * 4 + 4 <= constSize) {
                        // 完整字填充
                        result += "    st.w " + fillReg + ", " + dstReg + ", " + std::to_string(i * 4) + "\n";
                    } else {
                        // 最后不足4字节的情况
                        int remainBytes = constSize - i * 4;
                        for (int j = 0; j < remainBytes; j++) {
                            if (fillValue == 0) {
                                result += "    st.b $zero, " + dstReg + ", " + std::to_string(i * 4 + j) + "\n";
                            } else {
                                result += "    andi $t7, " + fillReg + ", 0xff\n";
                                result += "    st.b $t7, " + dstReg + ", " + std::to_string(i * 4 + j) + "\n";
                            }
                        }
                    }
                }
            } else {
                // 对于较大的常量大小，使用循环
                result += "    li.w $t2, " + std::to_string(constSize / 4) + "\n"; // 计算字数量
                result += "    li.w $t3, 0\n"; // 初始化循环计数器
                std::string loopLabel = "memset_loop_" + std::to_string(memset_label_counter_);
                std::string endLabel = "memset_end_" + std::to_string(memset_label_counter_++);
                
                result += loopLabel + ":\n";
                result += "    beq $t3, $t2, " + endLabel + "\n";
                result += "    slli.d $t4, $t3, 2\n";        // 计算偏移量 (i * 4)
                result += "    add.d $t5, " + dstReg + ", $t4\n"; // 计算地址
                result += "    st.w " + fillReg + ", $t5, 0\n";        // 存储填充值
                result += "    addi.w $t3, $t3, 1\n";        // 增加计数器
                result += "    b " + loopLabel + "\n";
                result += endLabel + ":\n";
                
                // 处理剩余的字节 (不是4的倍数)
                if (constSize % 4 != 0) {
                    int remainder = constSize % 4;
                    result += "    addi.d $t5, " + dstReg + ", " + std::to_string((constSize / 4) * 4) + "\n";
                    for (int i = 0; i < remainder; i++) {
                        if (fillValue == 0) {
                            result += "    st.b $zero, $t5, " + std::to_string(i) + "\n";
                        } else {
                            result += "    andi $t7, " + fillReg + ", 0xff\n";
                            result += "    st.b $t7, $t5, " + std::to_string(i) + "\n";
                            // 每次填充后右移8位，处理下一个字节
                            if (i < remainder - 1) {
                                result += "    srli.d " + fillReg + ", " + fillReg + ", 8\n";
                            }
                        }
                    }
                }
            }
        } else {
            // 使用变量大小的循环
            std::string loopLabel = "memset_loop_" + std::to_string(memset_label_counter_);
            std::string endLabel = "memset_end_" + std::to_string(memset_label_counter_);
            std::string remLabel = "memset_rem_" + std::to_string(memset_label_counter_);
            std::string doneLabel = "memset_done_" + std::to_string(memset_label_counter_++);
            
            result += "    srli.w $t2, " + sizeReg + ", 2\n"; // 计算字数量 (size / 4)
            result += "    li.w $t3, 0\n"; // 初始化循环计数器
            
            result += loopLabel + ":\n";
            result += "    beq $t3, $t2, " + endLabel + "\n";
            result += "    slli.d $t4, $t3, 2\n";        // 计算偏移量 (i * 4)
            result += "    add.d $t5, " + dstReg + ", $t4\n"; // 计算地址
            result += "    st.w " + fillReg + ", $t5, 0\n"; // 存储填充值
            result += "    addi.w $t3, $t3, 1\n";        // 增加计数器
            result += "    b " + loopLabel + "\n";
            result += endLabel + ":\n";
            
            // 处理剩余的字节 (不是4的倍数)
            result += "    andi $t4, " + sizeReg + ", 3\n"; // 获取余数 (size % 4)
            result += "    beqz $t4, " + doneLabel + "\n";
            result += "    slli.d $t3, $t2, 2\n";     // 计算已填充字节数 (words * 4)
            result += "    add.d $t5, " + dstReg + ", $t3\n"; // 计算剩余地址起点
            
            // 按字节处理剩余部分
            result += "    li.w $t3, 0\n"; // 初始化剩余字节计数器
            result += remLabel + ":\n";
            result += "    beq $t3, $t4, " + doneLabel + "\n";
            result += "    add.d $t6, $t5, $t3\n";
            
            if (fillValue == 0) {
                result += "    st.b $zero, $t6, 0\n";
            } else {
                // 从填充模式中提取当前字节
                result += "    andi $t7, " + fillReg + ", 0xff\n";
                result += "    st.b $t7, $t6, 0\n";
                // 为下一个字节准备填充值
                result += "    srli.d " + fillReg + ", " + fillReg + ", 8\n";
                // 达到字的边界时，重置填充模式
                result += "    andi $t8, $t3, 3\n";
                result += "    bnez $t8, memset_skip_reset_" + std::to_string(memset_label_counter_) + "\n";
                result += "    li.w $t9, " + std::to_string(fillValue) + "\n";
                result += "    andi $t9, $t9, 0xff\n";
                result += "    bstrpick.d $t8, $t9, 7, 0\n";
                result += "    slli.d $t7, $t8, 8\n";
                result += "    or $t9, $t9, $t7\n";
                result += "    slli.d $t7, $t9, 16\n";
                result += "    or " + fillReg + ", $t9, $t7\n";
                result += "memset_skip_reset_" + std::to_string(memset_label_counter_) + ":\n";
            }
            
            result += "    addi.w $t3, $t3, 1\n";
            result += "    b " + remLabel + "\n";
            result += doneLabel + ":\n";
        }
        
        return result;
    }

    // /*
    // 你需要在这里检测函数名是否是__aeabi_memclr4，并生成相应的内联汇编代码插入result
    // */
   // 检查是否调用的是 __aeabi_memclr4 函数
    if (funcName.compare("__aeabi_memclr4") == 0) {
        // result += "    # Handling __aeabi_memclr4 as inline memset\n";
        
        // __aeabi_memclr4 的参数：
        // 第一个参数：目标内存地址
        // 第二个参数：要清零的字节数
        Value* dstPtr = inst->get_operand(0);
        Value* sizeVal = inst->get_operand(1);
        
        // 获取目标地址的寄存器
        std::string dstReg;
        if (stack_offset_map.find(dstPtr) != stack_offset_map.end()) {
            if(outOfImmediateRange(stack_offset_map[dstPtr]+currentStackOffset))
            {
                result += "    li.d $t4, " + std::to_string(stack_offset_map[dstPtr]+currentStackOffset) + "\n";
                result += "    add.d $t0, $sp, $t4\n";
            }
            else
            {
                result += "    addi.d $t0, $sp, " + std::to_string(stack_offset_map[dstPtr]+currentStackOffset) + "\n";
            }
            dstReg = "$t0";
        } else if (reg_map.find(dstPtr) != reg_map.end()) {
            dstReg = reg_map[dstPtr];
        } else if (stack_map.find(dstPtr) != stack_map.end()) {
            // result += "    ld.w $t0, $sp, " + std::to_string(stack_map[dstPtr]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t0", stack_map[dstPtr]+currentStackOffset);
            dstReg = "$t0";
        } else {
            REPORT_COMPILER_ERROR_AND_EXIT("Destination pointer is from unknown source");
        }
        
        // 获取大小的寄存器或常量值
        int constSize = -1;
        std::string sizeReg;
        if (auto* constInt = dynamic_cast<ConstantInt*>(sizeVal)) {
            constSize = constInt->value_;
        } else if (reg_map.find(sizeVal) != reg_map.end()) {
            sizeReg = reg_map[sizeVal];
        } else if (stack_map.find(sizeVal) != stack_map.end()) {
            // result += "    ld.w $t1, $sp, " + std::to_string(stack_map[sizeVal]+currentStackOffset) + "\n";
            result += loadWordFromStack("$t1", stack_map[sizeVal]+currentStackOffset);
            sizeReg = "$t1";
        } else {
            REPORT_COMPILER_ERROR_AND_EXIT("Size value is from unknown source");
        }
        
        // 使用 memset 实现内存清零
        // 实现方式：循环按字(4字节)清零
        if (constSize > 0) {
            // 如果是常量大小且较小，直接生成多条清零指令
            if (constSize <= 32) {
                int numWords = (constSize + 3) / 4; // 向上取整到字边界
                for (int i = 0; i < numWords; i++) {
                    result += "    st.w $zero, " + dstReg + ", " + std::to_string(i * 4) + "\n";
                }
            } else {
                // 对于较大的常量大小，使用循环
                result += "    li.w $t2, " + std::to_string(constSize / 4) + "\n"; // 计算字数量
                result += "    li.w $t3, 0\n"; // 初始化循环计数器
                std::string loopLabel = "memclr_loop_" + std::to_string(memclr_label_counter_);
                std::string endLabel = "memclr_end_" + std::to_string(memclr_label_counter_++);
                
                result += loopLabel + ":\n";
                result += "    beq $t3, $t2, " + endLabel + "\n";
                result += "    slli.d $t4, $t3, 2\n";        // 计算偏移量 (i * 4)
                result += "    add.d $t5, " + dstReg + ", $t4\n"; // 计算地址
                result += "    st.w $zero, $t5, 0\n";        // 存储 0
                result += "    addi.w $t3, $t3, 1\n";        // 增加计数器
                result += "    b " + loopLabel + "\n";
                result += endLabel + ":\n";
                
                // 处理剩余的字节 (不是4的倍数)
                if (constSize % 4 != 0) {
                    int remainder = constSize % 4;
                    result += "    addi.d $t5, " + dstReg + ", " + std::to_string((constSize / 4) * 4) + "\n";
                    for (int i = 0; i < remainder; i++) {
                        result += "    st.b $zero, $t5, " + std::to_string(i) + "\n";
                    }
                }
            }
        } else {
            // 使用变量大小的循环
            std::string loopLabel = "memclr_loop_" + std::to_string(memclr_label_counter_);
            std::string endLabel = "memclr_end_" + std::to_string(memclr_label_counter_++);
            
            result += "    srli.w $t2, " + sizeReg + ", 2\n"; // 计算字数量 (size / 4)
            result += "    li.w $t3, 0\n"; // 初始化循环计数器
            
            result += loopLabel + ":\n";
            result += "    beq $t3, $t2, " + endLabel + "\n";
            result += "    slli.d $t4, $t3, 2\n";        // 计算偏移量 (i * 4)
            result += "    add.d $t5, " + dstReg + ", $t4\n"; // 计算地址
            result += "    st.w $zero, $t5, 0\n";        // 存储 0
            result += "    addi.w $t3, $t3, 1\n";        // 增加计数器
            result += "    b " + loopLabel + "\n";
            result += endLabel + ":\n";
            
            // 处理剩余的字节 (不是4的倍数)
            result += "    andi $t4, " + sizeReg + ", 3\n"; // 获取余数 (size % 4)
            result += "    beqz $t4, memclr_done_" + std::to_string(memclr_label_counter_) + "\n";
            result += "    slli.d $t3, $t2, 2\n";     // 计算已清零字节数 (words * 4)
            result += "    add.d $t5, " + dstReg + ", $t3\n"; // 计算剩余地址起点
            
            // 按字节处理剩余部分
            std::string remLabel = "memclr_rem_" + std::to_string(memclr_label_counter_);
            std::string doneLabel = "memclr_done_" + std::to_string(memclr_label_counter_++);
            
            result += "    li.w $t3, 0\n"; // 初始化剩余字节计数器
            result += remLabel + ":\n";
            result += "    beq $t3, $t4, " + doneLabel + "\n";
            result += "    add.d $t6, $t5, $t3\n";
            result += "    st.b $zero, $t6, 0\n";
            result += "    addi.w $t3, $t3, 1\n";
            result += "    b " + remLabel + "\n";
            result += doneLabel + ":\n";
        }
        
        return result;
    }

    
    // result += "    # Call to function: " + funcName + "\n";
    
    // 保存调用者保存的寄存器（如果需要）
    // 注意：在真实的编译器中，应该只保存实际使用的寄存器
    // result += "    # Save caller-saved registers (if needed)\n";

    std::set<std::string> changed_int_regs = changed_regs_map[calledFunc].first;
    std::set<std::string> changed_float_regs = changed_regs_map[calledFunc].second;

    std::set<std::string> active_int_regs = active_regs_map[inst].first;
    std::set<std::string> active_float_regs = active_regs_map[inst].second;

    std::set<std::string> saved_int_regs;
    std::set<std::string> saved_float_regs;

    for(auto reg : changed_int_regs)
    {
        if(active_int_regs.find(reg) != active_int_regs.end())
        {
            saved_int_regs.insert(reg);
        }
    }

    for(auto reg : changed_float_regs)
    {
        if(active_float_regs.find(reg) != active_float_regs.end())
        {
            saved_float_regs.insert(reg);
        }
    }

    for(auto reg : saved_int_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    st.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += storeDoubleWordToStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    st.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }
    for(auto reg : saved_float_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    fst.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += storeDoubleWordToStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    fst.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }
    
    
    // 准备参数
    int intArgCount = 0;
    int floatArgCount = 0;

    std::map<Value*, int> arg_stack_map;
    int arg_stack_offset = 0;

    // 遍历所有参数（最后一个操作数是函数本身，不是参数），得到参数的传递方式
    for (unsigned i = 0; i < inst->num_ops_ - 1; i++) {
        Value* arg = inst->get_operand(i);
        bool isFloat = arg->type_->tid_ == Type::FloatTyID;
        if (isFloat) {
            if (floatArgCount < 8) {
                floatArgCount++;
            } else {
                // 浮点参数超过8个，需要放到栈上，ABI要求参数槽为8字节
                arg_stack_map[arg] = arg_stack_offset;
                arg_stack_offset+=8;
            }
        } else {
            if (intArgCount < 8) {
                intArgCount++;
            } else {
                // 整型参数超过8个，需要放到栈上，ABI要求参数槽为8字节
                arg_stack_map[arg] = arg_stack_offset;
                arg_stack_offset+=8;
            }
        }
    }

    intArgCount = 0;
    floatArgCount = 0;

    // 将arg_stack_offset向上取整对齐到16字节
    arg_stack_offset = (arg_stack_offset + 15) & ~15;

    // 为参数压栈开辟空间
    result += "    addi.d  $sp, $sp, " + std::to_string(-arg_stack_offset) + "\n";
    currentStackOffset += arg_stack_offset;

    // 遍历所有参数（最后一个操作数是函数本身，不是参数）
    for (unsigned i = 0; i < inst->num_ops_ - 1; i++) {
        Value* arg = inst->get_operand(i);
        bool isFloat = arg->type_->tid_ == Type::FloatTyID;
        
        bool storeArg = false;
        // 确定参数使用的寄存器
        std::string argReg;
        if (isFloat) {
            if (floatArgCount < 8) {
                argReg = "$fa" + std::to_string(floatArgCount++);
            } else {
                // 浮点参数超过8个，需要放到栈上，用$ft0暂存
                argReg = "$ft0";
                storeArg = true;
                // result += "    # Warning: More than 8 float args not fully supported\n";
                // continue;
            }
        } else {
            if (intArgCount < 8) {
                argReg = "$a" + std::to_string(intArgCount++);
            } else {
                // 整型参数超过8个，需要放到栈上，用$t0暂存
                argReg = "$t0";
                storeArg = true;
                // result += "    # Warning: More than 8 int args not fully supported\n";
                // continue;
            }
        }
        
        // 根据参数值的位置加载到对应的参数寄存器

        
        // result += "    # Load argument " + argReg + "\n";
        // if (saved_int_regs.find(argReg) != saved_int_regs.end())
        // {
        //     result += "    ld.d " + argReg + ", $sp, " + std::to_string(-((*(regs_num.find(argReg))).second * 8 + 8) + currentStackOffset) + "\n";
        // }
        // else if (saved_float_regs.find(argReg) != saved_float_regs.end())
        // {
        //     result += "    fld.d " + argReg + ", $sp, " + std::to_string(-((*(regs_num.find(argReg))).second * 8 + 8) + currentStackOffset) + "\n";
        // }
        // 加载参数到寄存器
        if (stack_offset_map.find(arg) != stack_offset_map.end())
        {
            if (isFloat) {
                // 将$fp + offset加载到参数寄存器
                if(outOfImmediateRange(stack_offset_map[arg]+currentStackOffset))
                {
                    result += "    li.d $t4, " + std::to_string(stack_offset_map[arg]+currentStackOffset) + "\n";
                    result += "    add.d $t0, $sp, $t4\n";
                }
                else
                {
                    result += "    addi.d $t0, $sp, " + std::to_string(stack_offset_map[arg]+currentStackOffset) + "\n";
                }
                result += "    movgr2fr.d " + argReg + ", $t0\n";
            } else {
                // 将$fp + offset的值加载到参数寄存器
                if(outOfImmediateRange(stack_offset_map[arg]+currentStackOffset))
                {
                    result += "    li.d $t4, " + std::to_string(stack_offset_map[arg]+currentStackOffset) + "\n";
                    result += "    add.d " + argReg + ", $sp, $t4\n";
                }
                else
                {
                    result += "    addi.d " + argReg + ", $sp, " + std::to_string(stack_offset_map[arg]+currentStackOffset) + "\n";
                }
            }

        }
        else if (reg_map.find(arg) != reg_map.end()) {
            std::string srcReg = reg_map[arg];
            // 如果参数寄存器在saved_int_regs或saved_float_regs中，则从栈中加载
            if (saved_int_regs.find(srcReg) != saved_int_regs.end())
            {
                // result += "    ld.d " + argReg + ", $sp, " + std::to_string(-((*(regs_num.find(srcReg))).second * 8 + 8) + currentStackOffset) + "\n";
                result += loadDoubleWordFromStack(argReg, -((*(regs_num.find(srcReg))).second * 8 + 8) + currentStackOffset);
            }
            else if (saved_float_regs.find(srcReg) != saved_float_regs.end())
            {
                // result += "    fld.d " + argReg + ", $sp, " + std::to_string(-((*(regs_num.find(srcReg))).second * 8 + 8) + currentStackOffset) + "\n";
                result += loadDoubleWordFromStack(argReg, -((*(regs_num.find(srcReg))).second * 8 + 8) + currentStackOffset);
            }
            // 如果参数寄存器未被保护进saved_int_regs或saved_float_regs中，则正常加载
            else if (srcReg != argReg) {
                if (isFloat) {
                    if (srcReg[1] == 'f') {
                        result += "    fmov.d " + argReg + ", " + srcReg + "\n";  //改成双字版本
                    } else {
                        result += "    movgr2fr.d " + argReg + ", " + srcReg + "\n";//改成双字版本
                    }
                } else {
                    if (srcReg[1] == 'f') {
                        result += "    movfr2gr.d " + argReg + ", " + srcReg + "\n";//改成双字版本
                    } else {
                        result += "    or " + argReg + ", " + srcReg + ", $zero\n";
                    }
                }
            }
        } else if (stack_map.find(arg) != stack_map.end()) {
            if (isFloat) {
                // result += "    fld.s " + argReg + ", $sp, " + std::to_string(stack_map[arg]+currentStackOffset) + "\n";
                result += loadDoubleWordFromStack(argReg, stack_map[arg]+currentStackOffset); //改成双字版本
            } else {
                // result += "    ld.w " + argReg + ", $sp, " + std::to_string(stack_map[arg]+currentStackOffset) + "\n";
                result += loadDoubleWordFromStack(argReg, stack_map[arg]+currentStackOffset); //改成双字版本
            }
        } else if (auto* constInt = dynamic_cast<ConstantInt*>(arg)) {
            result += "    li.w " + argReg + ", " + std::to_string(constInt->value_) + "\n";
        } else if (auto* constFloat = dynamic_cast<ConstantFloat*>(arg)) {
            // 加载浮点常量
            float value = constFloat->value_;
            result += "    li.w $t0, " + std::to_string(*(int*)&value) + "\n";
            result += "    movgr2fr.w " + argReg + ", $t0\n";
        } else if (auto* globalVar = dynamic_cast<GlobalVariable*>(arg)) {
            // 判断是否需要加载全局变量的值还是地址
            Type* containedType = static_cast<PointerType*>(globalVar->type_)->contained_;
            if (containedType->tid_ == Type::ArrayTyID) {
                // 如果是数组类型，传递地址
                result += "    la.global " + argReg + ", " + globalVar->name_ + "\n";
            } else {
                // 如果是基本类型，加载值
                if (isFloat) {
                    result += "    la.global $t0, " + globalVar->name_ + "\n";
                    result += "    fld.s " + argReg + ", $t0, 0\n";
                } else {
                    result += "    la.global $t0, " + globalVar->name_ + "\n";
                    result += "    ld.w " + argReg + ", $t0, 0\n";
                }
            }
        } else {
            REPORT_COMPILER_ERROR_AND_EXIT("Argument value is from unknown source");
            // result += "    # Warning: Argument value not in register or stack\n";
        }

        if(storeArg)
        {
            if (isFloat) {
                // result += "    fst.s " + argReg + ", $sp, " + std::to_string(arg_stack_map[arg]) + "\n";
                result += storeDoubleWordToStack(argReg, arg_stack_map[arg]); //改成双字版本
            } else {
                // result += "    st.w " + argReg + ", $sp, " + std::to_string(arg_stack_map[arg]) + "\n";
                result += storeDoubleWordToStack(argReg, arg_stack_map[arg]); //改成双字版本
            }
        }
    }
    
    // 调用函数
    result += "    bl " + funcName + "\n";
    
    // 处理返回值（如果有）
    if (inst->type_->tid_ != Type::VoidTyID) {
        // result += "    # Handle return value\n";
        std::string destReg;
        bool storeDest = false;
        
        if (reg_map.find(inst) != reg_map.end()) {
            destReg = reg_map[inst];
        } else {
            if (inst->type_->tid_ == Type::FloatTyID) {
                destReg = "$fa0";
            } else {
                destReg = "$a0";
            }
            storeDest = true;
            // result += "    # Return value not mapped to register, using " + destReg + "\n";
        }
        
        // 从返回值寄存器移动到目标寄存器
        if (inst->type_->tid_ == Type::FloatTyID) {
            if (destReg.compare("$fa0") != 0) {
                result += "    fmov.s " + destReg + ", $fa0\n";
            }
            // else
            // {
            //     result += "    # Return value in $fa0\n";
            // }
        } else {
            if (destReg.compare("$a0") != 0) {
                result += "    or " + destReg + ", $a0, $zero\n";
            }
            // else
            // {
            //     result += "    # Return value in $a0\n";
            // }
        }
        // result += "    # Return value in " + destReg + "\n";
        
        // 如果需要，存储返回值到栈上
        if (storeDest) {
            if (inst->type_->tid_ == Type::FloatTyID) {
                // result += "    fst.s " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
                result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
            } else {
                // result += "    st.w " + destReg + ", $sp, " + std::to_string(stack_map[inst]+currentStackOffset) + "\n";
                result += storeWordToStack(destReg, stack_map[inst]+currentStackOffset);
            }
        }
    }
    
    result += "    addi.d $sp, $sp, " + std::to_string(arg_stack_offset) + "\n";
    currentStackOffset -= arg_stack_offset;

    // 恢复调用者保存的寄存器（如果需要）
    // result += "    # Restore caller-saved registers (if needed)\n";

    // for(auto reg : saved_int_regs)
    // {
    //     result += "    ld.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    // }
    // for(auto reg : saved_float_regs)
    // {
    //     result += "    fld.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    // }

    for(auto reg : saved_int_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    ld.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += loadDoubleWordFromStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    st.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }
    for(auto reg : saved_float_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    fld.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += loadDoubleWordFromStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    fst.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }

    
    return result;
}


std::string AsmEmitter::storeCallerSavedRegisters(std::pair<std::set<std::string>,std::set<std::string>> active_regs, std::pair<std::set<std::string>,std::set<std::string>> changed_regs)
{
    std::string result;
    
    std::set<std::string> changed_int_regs = changed_regs.first;
    std::set<std::string> changed_float_regs = changed_regs.second;

    std::set<std::string> active_int_regs = active_regs.first;
    std::set<std::string> active_float_regs = active_regs.second;

    std::set<std::string> saved_int_regs;
    std::set<std::string> saved_float_regs;

    for(auto reg : changed_int_regs)
    {
        if(active_int_regs.find(reg) != active_int_regs.end())
        {
            saved_int_regs.insert(reg);
        }
    }

    for(auto reg : changed_float_regs)
    {
        if(active_float_regs.find(reg) != active_float_regs.end())
        {
            saved_float_regs.insert(reg);
        }
    }

    for(auto reg : saved_int_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    st.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += storeDoubleWordToStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    st.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }
    for(auto reg : saved_float_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    fst.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += storeDoubleWordToStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    fst.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }
    
    return result;
}

std::string AsmEmitter::restoreCallerSavedRegisters(std::pair<std::set<std::string>,std::set<std::string>> active_regs, std::pair<std::set<std::string>,std::set<std::string>> changed_regs)
{
    std::string result;
    
    std::set<std::string> changed_int_regs = changed_regs.first;
    std::set<std::string> changed_float_regs = changed_regs.second;

    std::set<std::string> active_int_regs = active_regs.first;
    std::set<std::string> active_float_regs = active_regs.second;

    std::set<std::string> saved_int_regs;
    std::set<std::string> saved_float_regs;

    for(auto reg : changed_int_regs)
    {
        if(active_int_regs.find(reg) != active_int_regs.end())
        {
            saved_int_regs.insert(reg);
        }
    }

    for(auto reg : changed_float_regs)
    {
        if(active_float_regs.find(reg) != active_float_regs.end())
        {
            saved_float_regs.insert(reg);
        }
    }


    for(auto reg : saved_int_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    ld.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += loadDoubleWordFromStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    st.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }
    for(auto reg : saved_float_regs)
    {
        if(regs_num.find(reg) != regs_num.end())
        {
            // result += "    fld.d " + reg + ", $sp, " + std::to_string(-((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset) + "\n";
            result += loadDoubleWordFromStack(reg, -((*(regs_num.find(reg))).second * 8 + 8) + currentStackOffset);
        }
        else
        {
            REPORT_COMPILER_ERROR_AND_EXIT("Register number not found");
        }
        // result += "    fst.d " + reg + ", $fp, -" + std::to_string(regs_num[reg]*8) + "\n";
    }

    
    return result;
}
