#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <functional>

class AsmPeepholeOptimizer {
private:
    // 存储汇编指令
    std::vector<std::string> assemblyCode;
    
    // 记录修改次数，用于评估优化效果
    int optimizationCount = 0;
    
    // 检查指令是否是标签或注释
    bool isLabelOrComment(const std::string& line) {
        return line.empty() || line[0] == '#' || line[0] == '.' || line.back() == ':';
    }
    
    // 根据正则表达式匹配指令
    // bool matchInstruction(size_t index, const std::regex& pattern) {
    //     if (index >= assemblyCode.size()) return false;
    //     return std::regex_match(assemblyCode[index], pattern);
    // }
    
    // 应用窥孔优化规则

    bool applyOptimizationRules();
    // 优化函数：消除冗余加载/存储
    bool optimizeRedundantLoadStore(int index);
    
    // 优化函数：合并连续加减操作
    bool optimizeConsecutiveAddSub(int index);
    
    // 优化函数：优化寄存器之间的移动
    bool optimizeRegisterMoves(int index);
    
    // 优化函数：移除无效指令
    bool removeUselessInstructions(int index);
    
    // 优化函数：优化条件分支
    // bool optimizeConditionalBranches();
    
    // 优化函数：合并立即数操作
    // bool optimizeImmediateOperations();

public:
    // 构造函数，接收汇编代码
    AsmPeepholeOptimizer(const std::vector<std::string>& code) 
        : assemblyCode(code) {}
    
    // 运行优化
    std::vector<std::string> optimize() {
        bool changed;
        do {
            changed = false;
            
            // 应用各种优化规则
            changed |= applyOptimizationRules();
            
        } while (changed); // 不断优化直到没有变化
        
        // std::cout<<"asmCodeVec.size(): "<<assemblyCode.size()<<" optimizationCount: "<<optimizationCount<<std::endl;
        return assemblyCode;
    }
    
    // 获取优化次数
    int getOptimizationCount() const {
        return optimizationCount;
    }
};