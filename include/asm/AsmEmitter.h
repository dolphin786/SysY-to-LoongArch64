#pragma once
#include<antlr4-runtime.h>
#include "SysYBaseVisitor.h"

#include "common/ErrorReporter.h"
#include "ir/IR.h"
#include <variant>
#include <optional>
#include <string>

class AsmEmitter {

    SysYErrorHandling::ErrorReporter errorReporter;

    std::unique_ptr<Module> module;
    // 寄存器映射状态，表示某个虚拟寄存器对应的Loongarch64寄存器
    std::map<Value*, std::string> reg_map;

    // 栈分配状态，表示被存储到栈上的虚拟寄存器所在位置具体的偏移量
    std::map<Value*, int64_t> stack_map; //存储相对于fp的偏移量

    // 已知存储栈偏移量的虚拟寄存器的具体值，这些虚拟寄存器被当作编译期常量处理
    std::map<Value*, int64_t > stack_offset_map;

    int64_t currentStackOffset{};//当前栈顶偏移量

    std::map<Value*, std::pair<int, int>> live_range_map;//存储变量的生命周期

    int fcmp_label_counter_{};//用于生成浮点比较指令的标签

    int memclr_label_counter_{};

    int memset_label_counter_{};

    // std::map<Argument*, std::string> args_reg_map; //函数参数存放在哪个寄存器

    // std::map<Argument*, int> args_stack_map; //函数参数存放在栈上哪个位置（相对于fp的偏移量）

    // 寄存器分配相关常量
    // const std::vector<std::string> int_regs = {"$a0", "$a1", "$a2", "$a3", "$a4", "$a5", "$a6", "$a7", "$t5", "$t6", "$t7", "$t8"};

    const std::vector<std::string> int_regs = {"$a0", "$a1", "$a2", "$a3", "$a4", "$a5", "$a6", "$a7"};
    const std::vector<std::string> float_regs = {"$fa0", "$fa1", "$fa2", "$fa3", "$fa4", "$fa5", "$fa6", "$fa7", "$ft2", "$ft3", "$ft4", "$ft5", "$ft6", "$ft7", "$ft8"};

    const std::map<std::string, int> regs_num = {
        {"$a0", 0}, {"$a1", 1}, {"$a2", 2}, {"$a3", 3}, {"$a4", 4}, {"$a5", 5}, {"$a6", 6}, {"$a7", 7},
        {"$t4", 8}, {"$t5", 9}, {"$t6", 10}, {"$t7", 11}, {"$t8", 12},
        {"$fa0", 13}, {"$fa1", 14}, {"$fa2", 15}, {"$fa3", 16}, {"$fa4", 17}, {"$fa5", 18}, {"$fa6", 19}, {"$fa7", 20},
        {"$ft2", 21}, {"$ft3", 22}, {"$ft4", 23}, {"$ft5", 24}, {"$ft6", 25}, {"$ft7", 26}, {"$ft8", 27}
    };

    std::map<CallInst*, std::pair<std::set<std::string>,std::set<std::string>> > active_regs_map; //存储call指令处活跃的寄存器

    std::map<Function*, std::pair<std::set<std::string>,std::set<std::string>> > changed_regs_map; //存储函数中修改的寄存器

    bool isLeafFunction(Function* func);
    
    // std::string valueToReg(Value* val);


    bool outOfImmediateRange(int64_t value);

    bool outOfImmediateRange(int value);

    std::string storeWordToStack(std::string reg, int64_t offset); //把寄存器中的值存储到栈上，offset为相对于$sp的偏移量，过程中修改$t4

    std::string loadWordFromStack(std::string reg, int64_t offset); //从栈上读取值到寄存器，offset为相对于$sp的偏移量，过程中修改$t4

    std::string storeDoubleWordToStack(std::string reg, int64_t offset); //把寄存器中的值存储到栈上，offset为相对于$sp的偏移量，过程中修改$t4

    std::string loadDoubleWordFromStack(std::string reg, int64_t offset); //从栈上读取值到寄存器，offset为相对于$sp的偏移量，过程中修改$t4

    std::string storeCallerSavedRegisters(std::pair<std::set<std::string>,std::set<std::string>> active_regs, std::pair<std::set<std::string>,std::set<std::string>> changed_regs);

    std::string restoreCallerSavedRegisters(std::pair<std::set<std::string>,std::set<std::string>> active_regs, std::pair<std::set<std::string>,std::set<std::string>> changed_regs);

    // 寄存器分配
    void allocateRegisters(Function* func);
    void linearScanRegisterAllocation(Function* func);

    // 确定函数参数存储位置
    // void allocateFunctionArguments(Function* func);
    
    // 处理alloca指令
    // std::string handleAlloca(AllocaInst* inst);

    // 处理store指令
    std::string handleStore(StoreInst* inst);

    // 处理load指令
    std::string handleLoad(LoadInst* inst);

    // 处理siToFp指令
    std::string handleSiToFp(SiToFpInst* inst);

    // 处理fpToSi指令
    std::string handleFpToSi(FpToSiInst* inst);

    // 处理二元运算指令
    std::string handleBinaryInst(BinaryInst* inst);

    // 处理整数比较指令
    std::string handleICmpInst(ICmpInst* inst);

    // 处理浮点数比较指令
    std::string handleFCmpInst(FCmpInst* inst);

    // 处理函数调用指令
    std::string handleCallInst(CallInst* inst);

    // 处理分支指令
    std::string handleBranchInst(BranchInst* inst);

    // 处理phi指令
    // std::string handlePhiInst(PhiInst* inst);

    // 处理返回指令
    std::string handleReturnInst(ReturnInst* inst);

    // 处理zext指令
    std::string handleZextInst(ZextInst* inst);

    // 处理bitcast指令
    std::string handleBitcastInst(Bitcast* inst);

    std::string handleGetElementPtrInst(GetElementPtrInst* inst);

    int64_t calculateArraySize(ArrayType* arrayType);


    std::string generateFunctionPrologue(Function* func);

    std::string generateFunction(Function* func);
    
    std::string generateGlobalVar(GlobalVariable* globalVar);

    std::string generateGlobalArrayInBss(GlobalVariable* globalVar);

    // std::string handleAllAlloca(Function* func);

    std::vector<Constant*> getArrayInitVal(ConstantArray* init_array);

    int getZeroCount(ConstantZero* constantZero);
    void printErrors()
    {
        printf("%s",errorReporter.toString().c_str());
    }

    public:

    AsmEmitter(std::unique_ptr<Module> m): module(std::move(m)) {}
     

    std::string emit();
    

    // std::string lowerAdd(Instruction* inst) {
    //     std::string opcode;
    //     Type* ty = inst->getOperand(0)->getType();
        
    //     // 根据数据类型选择指令
    //     if (ty->isIntegerTy(32)) {
    //         opcode = "add.w";
    //     } else if (ty->isDoubleTy()) {
    //         opcode = "fadd.d";
    //     }
        
    //     std::string dest = assignReg(inst); // 分配目标寄存器
    //     std::string src1 = getOperandReg(inst->getOperand(0));
    //     std::string src2 = getOperandReg(inst->getOperand(1));
        
    //     return opcode + " " + dest + ", " + src1 + ", " + src2;
    // }
    // std::string lowerStore(Instruction* inst) {
    //     Value* val = inst->getOperand(0);
    //     Value* ptr = inst->getOperand(1);
        
    //     // 计算内存偏移量（假设已分析栈布局）
    //     int offset = getStackOffset(ptr);
    //     return "st.d " + getOperandReg(val) + ", $fp, " + std::to_string(offset);
    // }
};