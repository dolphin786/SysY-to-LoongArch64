#include "ir/IROptimizer.h"

// 执行所有优化
bool SysYIROptimizer::optimize() {
    bool changed = false;
    bool iterChanged;
    
    // 多次迭代直到没有变化为止
    do {
        iterChanged = false;
        
        // 执行常量折叠
        bool foldingChanged = constantFolding();
        
        // 执行死代码删除
        bool dceChanged = deadCodeElimination();

        // 提升 alloca 指令到函数入口基本块
        bool allocaPromotionChanged = promoteStaticAllocas();

        iterChanged = foldingChanged || dceChanged || allocaPromotionChanged;
        changed |= iterChanged;
    } while (iterChanged);
    
    return changed;
}




// 判断指令是否为纯计算指令，没有副作用
bool SysYIROptimizer::isPureComputation(Instruction* inst) {
    if (dynamic_cast<BinaryInst*>(inst) || 
        dynamic_cast<ICmpInst*>(inst) ||
        dynamic_cast<FCmpInst*>(inst) ||
        dynamic_cast<ZextInst*>(inst) ||
        dynamic_cast<FpToSiInst*>(inst) ||
        dynamic_cast<SiToFpInst*>(inst)) {
        return true;
    }
    return false;
}

// 判断指令是否有副作用（例如内存访问、函数调用等）
bool SysYIROptimizer::hasSideEffect(Instruction* inst) {
    if (dynamic_cast<StoreInst*>(inst) ||
        dynamic_cast<CallInst*>(inst) ||
        dynamic_cast<ReturnInst*>(inst) ||
        dynamic_cast<BranchInst*>(inst)) {
        return true;
    }
    return false;
}

// 判断指令是否被使用
// bool SysYIROptimizer::isUsed(Instruction* inst) {
//     if (hasSideEffect(inst)) return true;

//     for (auto& use : inst->use_list_) {
//         if (use.val_ != nullptr) {
//             return true;
//         }
//     }
//     return false;
// }

// 常量折叠优化
bool SysYIROptimizer::constantFolding() {
    bool changed = false;
    
    // 遍历每个函数
    for (auto& func : module->function_list_) {
        // 跳过没有函数体的声明
        if (func->basic_blocks_.empty()) {
            continue;
        }
        
        // 遍历函数中的每个基本块
        for (auto& bb : func->basic_blocks_) {
            // 使用迭代器遍历指令，以便安全删除
            auto it = bb->instr_list_.begin();
            while (it != bb->instr_list_.end()) {
                auto inst = *it;
                
                // 尝试将指令折叠为常量
                Value* foldedValue = tryFoldInstruction(inst);
                
                if (foldedValue && foldedValue != inst) {
                    // 如果可以折叠，替换所有使用
                    inst->replace_all_use_with(foldedValue);
                    
                    // 删除指令（如果它没有副作用）
                    if (!hasSideEffect(inst)) {
                        it = bb->instr_list_.erase(it);
                        changed = true;
                        continue;
                    }
                }
                
                ++it;
            }
        }
    }
    
    return changed;
}

// 尝试将指令折叠为常量
Value* SysYIROptimizer::tryFoldInstruction(Instruction* inst) {
    // 处理二元运算指令
    if (auto binOp = dynamic_cast<BinaryInst*>(inst)) {
        Value* lhs = binOp->get_operand(0);
        Value* rhs = binOp->get_operand(1);
        
        // 检查两个操作数是否都是常量
        auto constLhs = dynamic_cast<ConstantInt*>(lhs);
        auto constRhs = dynamic_cast<ConstantInt*>(rhs);
        
        if (constLhs && constRhs) {
            int result;
            switch (binOp->op_id_) {
                case Instruction::Add:
                    result = constLhs->value_ + constRhs->value_;
                    return new ConstantInt(module->int32_ty_, result);
                case Instruction::Sub:
                    result = constLhs->value_ - constRhs->value_;
                    return new ConstantInt(module->int32_ty_, result);
                case Instruction::Mul:
                    result = constLhs->value_ * constRhs->value_;
                    return new ConstantInt(module->int32_ty_, result);
                case Instruction::SDiv:
                    if (constRhs->value_ != 0) { // 避免除以零
                        result = constLhs->value_ / constRhs->value_;
                        return new ConstantInt(module->int32_ty_, result);
                    }
                    break;
                case Instruction::SRem:
                    if (constRhs->value_ != 0) { // 避免除以零
                        result = constLhs->value_ % constRhs->value_;
                        return new ConstantInt(module->int32_ty_, result);
                    }
                    break;
                default:
                    break;
            }
        }
        
        // 处理浮点数常量折叠
        auto constFloatLhs = dynamic_cast<ConstantFloat*>(lhs);
        auto constFloatRhs = dynamic_cast<ConstantFloat*>(rhs);
        
        if (constFloatLhs && constFloatRhs) {
            float result;
            switch (binOp->op_id_) {
                case Instruction::FAdd:
                    result = constFloatLhs->value_ + constFloatRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FSub:
                    result = constFloatLhs->value_ - constFloatRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FMul:
                    result = constFloatLhs->value_ * constFloatRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FDiv:
                    if (constFloatRhs->value_ != 0.0f) { // 避免除以零
                        result = constFloatLhs->value_ / constFloatRhs->value_;
                        return new ConstantFloat(module->float32_ty_, result);
                    }
                    break;
                default:
                    break;
            }
        }

        // 处理整数与浮点数混合运算
        if (constLhs && constFloatRhs) {
            float result;
            switch (binOp->op_id_) {
                case Instruction::FAdd:
                    result = constLhs->value_ + constFloatRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FSub:
                    result = constLhs->value_ - constFloatRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FMul:
                    result = constLhs->value_ * constFloatRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FDiv:
                    if (constFloatRhs->value_ != 0.0f) {
                        result = constLhs->value_ / constFloatRhs->value_;
                        return new ConstantFloat(module->float32_ty_, result);
                    }
                    break;
                default:
                    break;
            }
        }
        if (constFloatLhs && constRhs) {
            float result;
            switch (binOp->op_id_) {
                case Instruction::FAdd:
                    result = constFloatLhs->value_ + constRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FSub:
                    result = constFloatLhs->value_ - constRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FMul:
                    result = constFloatLhs->value_ * constRhs->value_;
                    return new ConstantFloat(module->float32_ty_, result);
                case Instruction::FDiv:
                    if (constRhs->value_ != 0) {
                        result = constFloatLhs->value_ / constRhs->value_;
                        return new ConstantFloat(module->float32_ty_, result);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
    // 处理比较指令
    if (auto cmpInst = dynamic_cast<ICmpInst*>(inst)) {
        Value* lhs = cmpInst->get_operand(0);
        Value* rhs = cmpInst->get_operand(1);
        
        auto constLhs = dynamic_cast<ConstantInt*>(lhs);
        auto constRhs = dynamic_cast<ConstantInt*>(rhs);
        
        if (constLhs && constRhs) {
            bool result;
            switch (cmpInst->icmp_op_) {
                case ICmpInst::ICMP_EQ:
                    // printf("constLhs: %d constRhs: %d\n",constLhs->value_, constRhs->value_);
                    // printf("eq: %d\n",constLhs->value_ == constRhs->value_);
                    result = constLhs->value_ == constRhs->value_;
                    break;
                case ICmpInst::ICMP_NE:
                    // if(constLhs->value_ == 18)
                    // {
                    // printf("constLhs: %d constRhs: %d\n",constLhs->value_, constRhs->value_);
                    // printf("ne: %d\n",constLhs->value_ != constRhs->value_);
                    // }
                    result = constLhs->value_ != constRhs->value_;
                    break;
                case ICmpInst::ICMP_SGT:
                    // printf("constLhs: %d constRhs: %d\n",constLhs->value_, constRhs->value_);
                    // printf("sgt: %d\n",constLhs->value_ > constRhs->value_);
                    result = constLhs->value_ > constRhs->value_;
                    break;
                case ICmpInst::ICMP_SGE:
                    // printf("constLhs: %d constRhs: %d\n",constLhs->value_, constRhs->value_);
                    // printf("sge: %d\n",constLhs->value_ >= constRhs->value_);
                    result = constLhs->value_ >= constRhs->value_;
                    break;
                case ICmpInst::ICMP_SLT:
                    // printf("constLhs: %d constRhs: %d\n",constLhs->value_, constRhs->value_);
                    // printf("slt: %d\n",constLhs->value_ < constRhs->value_);
                    result = constLhs->value_ < constRhs->value_;
                    break;
                case ICmpInst::ICMP_SLE:
                    // printf("constLhs: %d constRhs: %d\n",constLhs->value_, constRhs->value_);
                    // printf("sle: %d\n",constLhs->value_ <= constRhs->value_);
                    result = constLhs->value_ <= constRhs->value_;
                    break;
                default:
                    return nullptr;
            }
            auto temp = new ConstantInt(module->int1_ty_, result ? 1 : 0);
            // printf("inst: %s\nop_id_: %d\nnewinst: %s\n",inst->print().c_str(),cmpInst->op_id_,temp->print().c_str());
            // 创建一个布尔常量
            // return new ConstantInt(module->int1_ty_, result ? 1 : 0);
            return temp;
        }
    }
    
    // 处理浮点比较指令
    if (auto fcmpInst = dynamic_cast<FCmpInst*>(inst)) {
        Value* lhs = fcmpInst->get_operand(0);
        Value* rhs = fcmpInst->get_operand(1);
        
        auto constLhs = dynamic_cast<ConstantFloat*>(lhs);
        auto constRhs = dynamic_cast<ConstantFloat*>(rhs);
        
        if (constLhs && constRhs) {
            bool result;
            switch (fcmpInst->fcmp_op_) {
                case FCmpInst::FCMP_UEQ:
                    result = constLhs->value_ == constRhs->value_;
                    break;
                case FCmpInst::FCMP_UNE:
                    result = constLhs->value_ != constRhs->value_;
                    break;
                case FCmpInst::FCMP_UGT:
                    result = constLhs->value_ > constRhs->value_;
                    break;
                case FCmpInst::FCMP_UGE:
                    result = constLhs->value_ >= constRhs->value_;
                    break;
                case FCmpInst::FCMP_ULT:
                    result = constLhs->value_ < constRhs->value_;
                    break;
                case FCmpInst::FCMP_ULE:
                    result = constLhs->value_ <= constRhs->value_;
                    break;
                default:
                    return nullptr;
            }
            
            return new ConstantInt(module->int1_ty_, result ? 1 : 0);
        }
    }
    
    // 处理类型转换指令
    if (auto zextInst = dynamic_cast<ZextInst*>(inst)) {
        Value* operand = zextInst->get_operand(0);
        auto constOperand = dynamic_cast<ConstantInt*>(operand);
        
        if (constOperand) {
            return new ConstantInt(module->int32_ty_, constOperand->value_);
        }
    }
    
    if (auto fpToSiInst = dynamic_cast<FpToSiInst*>(inst)) {
        Value* operand = fpToSiInst->get_operand(0);
        auto constOperand = dynamic_cast<ConstantFloat*>(operand);
        
        if (constOperand) {
            return new ConstantInt(module->int32_ty_, static_cast<int>(constOperand->value_));
        }
    }
    
    if (auto siToFpInst = dynamic_cast<SiToFpInst*>(inst)) {
        Value* operand = siToFpInst->get_operand(0);
        auto constOperand = dynamic_cast<ConstantInt*>(operand);
        
        if (constOperand) {
            return new ConstantFloat(module->float32_ty_, static_cast<float>(constOperand->value_));
        }
    }
    
    // 折叠条件分支
    // if (auto brInst = dynamic_cast<BranchInst*>(inst)) {
    //     if (brInst->is_cond_br()) {
    //         auto condValue = dynamic_cast<ConstantInt*>(brInst->get_operand(0));
    //         if (condValue) {
    //             if (condValue->value_) {
    //                 // 如果条件始终为真，替换为无条件跳转到true分支
    //                 BasicBlock* trueBB = static_cast<BasicBlock*>(brInst->get_operand(1));
    //                 printf("inst: %s\nnewinst: br label %s\n",inst->print().c_str(),trueBB->print().c_str());
    //                 return new BranchInst(trueBB, brInst->parent_);
    //             } else {
    //                 // 如果条件始终为假，替换为无条件跳转到false分支
    //                 BasicBlock* falseBB = static_cast<BasicBlock*>(brInst->get_operand(2));
    //                 printf("inst: %s\nnewinst: br label %s\n",inst->print().c_str(),falseBB->print().c_str());
    //                 return new BranchInst(falseBB, brInst->parent_);
    //             }
    //         }
    //     }
    // }
    
    return nullptr;
}

// 死代码删除优化
bool SysYIROptimizer::deadCodeElimination() {
    bool changed = false;
    
    // 遍历每个函数
    for (auto& func : module->function_list_) {
        // 跳过函数声明
        if (func->basic_blocks_.empty()) {
            continue;
        }
        
        // 标记阶段：标记所有有用的指令
        std::set<Instruction*> usefulInstructions;
        markUsefulInstructions(func, usefulInstructions);
        
        // 删除阶段：删除所有无用的指令
        for (auto& bb : func->basic_blocks_) {
            auto it = bb->instr_list_.begin();
            while (it != bb->instr_list_.end()) {
                auto inst = *it;
                
                // 如果指令不在有用集合中，删除它
                if (usefulInstructions.find(inst) == usefulInstructions.end() /*&& 
                    !hasSideEffect(inst)*/) {
                    it = bb->instr_list_.erase(it);
                    changed = true;
                } else {
                    ++it;
                }
            }
        }
    }
    
    return changed;
}

// 标记所有有用的指令
void SysYIROptimizer::markUsefulInstructions(Function* func, std::set<Instruction*>& usefulInstructions) {
    std::vector<Instruction*> worklist;
    
    // // 首先，将所有有副作用的指令标记为有用
    // for (auto& bb : func->basic_blocks_) {
    //     for (auto& inst : bb->instr_list_) {
    //         if (hasSideEffect(inst)) {
    //             worklist.push_back(inst);
    //             usefulInstructions.insert(inst);
    //         }
    //     }
    // }

    // 首先，将所有有副作用的指令标记为有用，但要特殊处理终结指令
    for (auto& bb : func->basic_blocks_) {
        bool terminatorFound = false;
        
        // 从前向后遍历，只把第一个终结指令标记为有用
        for (auto it = bb->instr_list_.begin(); it != bb->instr_list_.end(); ++it) {
            auto inst = *it;
            
            if (dynamic_cast<BranchInst*>(inst) || dynamic_cast<ReturnInst*>(inst)) {
                // 如果是终结指令
                if (!terminatorFound) {
                    // 只有第一个终结指令标记为有用
                    worklist.push_back(inst);
                    usefulInstructions.insert(inst);
                    terminatorFound = true;
                }
                // 其他终结指令不标记为有用，会被后续删除
            } 
            else if (hasSideEffect(inst)) {
                // 其他有副作用的非终结指令正常标记
                worklist.push_back(inst);
                usefulInstructions.insert(inst);
            }
        }
    }
    
    // 然后，从有用的指令开始，向上标记所有被它们依赖的指令
    while (!worklist.empty()) {
        Instruction* inst = worklist.back();
        worklist.pop_back();
        
        // 对于指令的每个操作数
        for (int i = 0; i < inst->num_ops_; i++) {
            Value* operand = inst->get_operand(i);
            
            // 如果操作数是指令，则标记它为有用
            if (auto* operandInst = dynamic_cast<Instruction*>(operand)) {
                if (usefulInstructions.find(operandInst) == usefulInstructions.end()) {
                    usefulInstructions.insert(operandInst);
                    worklist.push_back(operandInst);
                }
            }
        }
    }
}

// 提升静态 alloca 指令到函数入口基本块
bool SysYIROptimizer::promoteStaticAllocas() {
    bool changed = false;
    
    // 遍历每个函数
    for (auto& func : module->function_list_) {
        // 跳过没有函数体的声明
        if (func->basic_blocks_.empty()) {
            continue;
        }
        
        // 找到函数的入口基本块
        BasicBlock* entryBB = func->basic_blocks_.front();
        
        // 如果没有label_entry基本块，尝试找到名为"label_entry"的基本块
        if (entryBB->name_ != "label_entry") {
            // for (auto& bb : func->basic_blocks_) {
            //     if (bb->name_ == "label_entry") {
            //         entryBB = bb;
            //         break;
            //     }
            // }
            // printf("Warning: label_entry basic block not found for function %s, using first basic block %s as entry.\n", func->name_.c_str(), entryBB->name_.c_str());
        }
        
        // 找到入口基本块中最后一条 alloca 指令的位置
        // 我们将把所有其他基本块的 alloca 指令移动到这个位置之后
        auto insertPos = entryBB->instr_list_.begin();
        for (auto it = entryBB->instr_list_.begin(); it != entryBB->instr_list_.end(); ++it) {
            if (dynamic_cast<AllocaInst*>(*it)) {
                insertPos = std::next(it);
            } 
            // else if (!dynamic_cast<AllocaInst*>(*it) && 
            //           !dynamic_cast<PhiInst*>(*it)) {
            //     // 一旦遇到非 alloca 且非 phi 指令，停止查找
            //     break;
            // }
        }
        
        // 收集所有非入口基本块中的静态 alloca 指令
        std::vector<std::pair<BasicBlock*, AllocaInst*>> allocasToMove;
        
        for (auto& bb : func->basic_blocks_) {
            if (bb == entryBB) continue;
            
            auto it = bb->instr_list_.begin();
            while (it != bb->instr_list_.end()) {
                if (auto allocaInst = dynamic_cast<AllocaInst*>(*it)) {
                    // 检查是否是静态分配（大小是常量）
                    if (isStaticAlloca(allocaInst)) {
                        allocasToMove.push_back({bb, allocaInst});
                        it = bb->instr_list_.erase(it);
                        changed = true;
                    } else {
                        ++it;
                    }
                } else {
                    ++it;
                }
            }
        }
        
        // 将收集到的 alloca 指令移动到入口基本块
        for (auto& [srcBB, allocaInst] : allocasToMove) {
            entryBB->instr_list_.insert(insertPos, allocaInst);
            // 更新 alloca 指令的父基本块
            allocaInst->parent_ = entryBB;
        }
    }
    
    return changed;
}
// 判断 alloca 指令是否是静态分配（分配大小是常量）
bool SysYIROptimizer::isStaticAlloca(AllocaInst* allocaInst) {
    // 如果 alloca 指令没有显式指定大小，或者大小是常量，则是静态分配
    // if (allocaInst->num_ops_ < 2) {
    //     return true; // 没有指定大小参数，使用默认大小1
    // }
    
    // // 检查大小参数是否是常量
    // Value* sizeOperand = allocaInst->get_operand(1);
    // return dynamic_cast<ConstantInt*>(sizeOperand) != nullptr;

    return true;
}
