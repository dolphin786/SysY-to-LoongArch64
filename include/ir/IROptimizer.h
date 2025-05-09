#pragma once
#include "ir/IR.h"
#include <memory>
#include <set>
#include <vector>
#include <unordered_map>

class SysYIROptimizer {
private:
    std::unique_ptr<Module> module;
    bool modified;

public:
    explicit SysYIROptimizer(std::unique_ptr<Module> m): module(std::move(m)), modified(false) {}
    bool optimize();

    std::unique_ptr<Module> getModule() {
        return std::move(module);
    }

private:
    bool isPureComputation(Instruction* inst);
    bool hasSideEffect(Instruction* inst);
    bool constantFolding();
    Value* tryFoldInstruction(Instruction* inst);
    bool deadCodeElimination();
    void markUsefulInstructions(Function* func, std::set<Instruction*>& usefulInstructions);
    bool promoteStaticAllocas();
    bool isStaticAlloca(AllocaInst* allocaInst);
};
