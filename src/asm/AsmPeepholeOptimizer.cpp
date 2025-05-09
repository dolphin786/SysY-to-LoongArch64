#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <functional>

#include "asm/AsmPeepholeOptimizer.h"

// 优化规则1: 消除冗余的加载/存储操作
bool AsmPeepholeOptimizer::applyOptimizationRules() {
    bool changed = false;
    for(size_t i = 0; i < assemblyCode.size(); i++) {
        if(isLabelOrComment(assemblyCode[i])) continue;
        bool tempChanged = false;
        tempChanged |= optimizeRedundantLoadStore(i);
        tempChanged |= optimizeConsecutiveAddSub(i);
        tempChanged |= optimizeRegisterMoves(i);
        tempChanged |= removeUselessInstructions(i);
        if(tempChanged) {
            changed = true;
            i--;
        }
    }
    return changed;
}
bool AsmPeepholeOptimizer::optimizeRedundantLoadStore(int index) {
    bool changed = false;
    if(index >= assemblyCode.size() - 1) return changed;
    if(isLabelOrComment(assemblyCode[index])) return changed;
    // for (size_t i = 0; i < assemblyCode.size() - 1; i++) {
    //     // 跳过标签和注释
    //     if (isLabelOrComment(assemblyCode[i])) continue;
        
        // 模式1: 存储后立即加载相同位置的值
        // st.w $rx, $ry, offset
        // ld.w $rx, $ry, offset
        std::regex storePattern(R"(\s*st\.([wdus])\s+(\$[a-z0-9]+),\s*(\$[a-z0-9]+),\s*(-?\d+|[0-9a-fA-Fx]+))");
        std::regex loadPattern(R"(\s*ld\.([wdus])\s+(\$[a-z0-9]+),\s*(\$[a-z0-9]+),\s*(-?\d+|[0-9a-fA-Fx]+))");
        
        std::smatch storeMatch, loadMatch;
        if (std::regex_match(assemblyCode[index], storeMatch, storePattern) &&
            std::regex_match(assemblyCode[index+1], loadMatch, loadPattern)) {
            
            if (storeMatch.str(3) == loadMatch.str(3) && // 检查基地址寄存器 (如 $fp)
                storeMatch.str(4) == loadMatch.str(4))
            { // 检查偏移量是否相同
                if (storeMatch.str(2) == loadMatch.str(2) && storeMatch.str(1) == loadMatch.str(1))
                {                                                     // 校验存储/加载寄存器是否相同，以及字长是否相同
                    assemblyCode.erase(assemblyCode.begin() + index + 1); // 删除冗余加载
                    optimizationCount++;
                    changed = true;
                }
            }
        }
    // }
    
    return changed;
}

// 优化规则2: 合并连续的加减操作
// bool AsmPeepholeOptimizer::optimizeConsecutiveAddSub() {
//     bool changed = false;
    
//     for (size_t i = 0; i < assemblyCode.size() - 1; i++) {
//         // 跳过标签和注释
//         if (isLabelOrComment(assemblyCode[i])) continue;
        
//         // 模式: 连续对同一寄存器执行加减操作
//         // addi.d $rx, $rx, imm1
//         // addi.d $rx, $rx, imm2
//         std::regex addiPattern(R"(\s*addi\.([wd])\s+(\$[a-z0-9]+),\s*(\$[a-z0-9]+),\s*(\-?\d+))");
        
//         std::smatch match1, match2;
//         if (std::regex_match(assemblyCode[i], match1, addiPattern) &&
//             std::regex_match(assemblyCode[i+1], match2, addiPattern)) {
//             if(match1.str(1) == match2.str(1))
//             {
//                 if (match1.str(2) == match2.str(2) && match1.str(3) == match2.str(2)) {
//                 // 合并立即数
//                     int imm1 = std::stoi(match1.str(4), nullptr, 0);
//                     int imm2 = std::stoi(match2.str(4), nullptr, 0);
//                     int combinedImm = imm1 + imm2;
                    
//                     // 如果合并后的立即数在有效范围内 (-2048 to 2047 for ADDI)
//                     if (combinedImm >= -2048 && combinedImm <= 2047) {
//                         std::string newInstr = "    addi." + std::string(match1[0].str().find(".d") != std::string::npos ? "d" : "w") +
//                                             " $r" + std::string(match1[1]) + ", $r" + std::string(match1[2]) + 
//                                             ", " + std::to_string(combinedImm);
                        
//                         assemblyCode[i] = newInstr;
//                         assemblyCode.erase(assemblyCode.begin() + i + 1);
//                         optimizationCount++;
//                         changed = true;
//                     }
//                 }
//             }
            
//         }
//     }
    
//     return changed;
// }

bool AsmPeepholeOptimizer::optimizeConsecutiveAddSub(int index) {
    bool changed = false;
    if(index >= assemblyCode.size() - 1) return changed;
    if(isLabelOrComment(assemblyCode[index])) return changed;
    const int MIN_IMM = -2048, MAX_IMM = 2047; // ADDI 的有效立即数范围

    // for (size_t i = 0; i < assemblyCode.size() - 1; ++i) {
    //     if (isLabelOrComment(assemblyCode[i])) continue;

        // 匹配连续两个 addi.d 或 addi.w，且源寄存器和目标寄存器相同
        std::regex addiPattern(R"(\s*addi\.([dw])\s+(\$[a-z0-9]+),\s*(\$[a-z0-9]+),\s*(-?\d+|0x[0-9a-fA-F]+))");
        std::smatch firstMatch, secondMatch;
        if (std::regex_match(assemblyCode[index], firstMatch, addiPattern) &&
            std::regex_match(assemblyCode[index+1], secondMatch, addiPattern)) {

            // 提取两个操作的信息
            std::string type1 = firstMatch.str(1);
            std::string type2 = secondMatch.str(1);
            std::string reg1Dst = firstMatch.str(2);
            std::string reg1Src = firstMatch.str(3);
            std::string reg2Dst = secondMatch.str(2);
            std::string reg2Src = secondMatch.str(3);

            // 条件1: 两次操作字长相同；条件2: 目标寄存器相同；条件3: 两次操作的源和目标寄存器相同
            if (type1 == type2 && reg1Dst == reg1Src && reg2Dst == reg2Src && reg1Dst == reg2Dst) {
                // 解析立即数
                int imm1 = 0, imm2 = 0;
                try {
                    imm1 = std::stoi(firstMatch.str(4), nullptr, 0); // 支持十进制和十六进制（如 "0x10"）
                    imm2 = std::stoi(secondMatch.str(4), nullptr, 0);
                } catch (...) { 
                    return changed;
                } // 格式不合法时跳过

                int total = imm1 + imm2;
                
                // 合并后立即数必须在合法范围内
                if (total >= MIN_IMM && total <= MAX_IMM) {
                    // 构造新的指令
                    std::string newInstr = "addi." + type1 + " " + reg1Dst + ", " + reg1Dst + ", " + std::to_string(total);
                    
                    // 替换两条指令为新指令
                    assemblyCode[index] = newInstr;
                    assemblyCode.erase(assemblyCode.begin() + index + 1);
                    optimizationCount++;
                    changed = true;
                    // i--; // 调整索引，避免遗漏后续合并
                }
            }
        }
    // }
    return changed;
}

// 优化规则3: 优化寄存器之间的移动
// bool AsmPeepholeOptimizer::optimizeRegisterMoves() {
//     bool changed = false;
    
//     for (size_t i = 0; i < assemblyCode.size() - 1; i++) {
//         // 跳过标签和注释
//         if (isLabelOrComment(assemblyCode[i])) continue;
        
//         // 模式: 移动寄存器然后又移动回来
//         // or $rx, $ry, $r0  # 将$ry移动到$rx
//         // or $ry, $rx, $r0  # 将$rx移动回$ry
//         std::regex movePattern(R"(\s*or\s+\$r(\d+),\s*\$r(\d+),\s*\$r0)");
        
//         std::smatch match1, match2;
//         if (std::regex_match(assemblyCode[i], match1, movePattern) &&
//             std::regex_match(assemblyCode[i+1], match2, movePattern)) {
            
//             // 检查是否是互相移动
//             if (match1[1] == match2[2] && match1[2] == match2[1]) {
//                 // 移除第二条移动指令
//                 assemblyCode.erase(assemblyCode.begin() + i + 1);
//                 optimizationCount++;
//                 changed = true;
//             }
//         }
        
//         // 模式: 移动后立即使用原寄存器，并且不再使用目标寄存器
//         // 这种优化需要更复杂的数据流分析，此处简化处理
//     }
    
//     return changed;
// }

bool AsmPeepholeOptimizer::optimizeRegisterMoves(int index) {
    bool changed = false;
    if(index >= assemblyCode.size() - 1) return changed;
    if(isLabelOrComment(assemblyCode[index]) || isLabelOrComment(assemblyCode[index+1])) return changed;
    // for (size_t i = 0; i < assemblyCode.size() - 1; ++i) {
    //     if (isLabelOrComment(assemblyCode[i]) || isLabelOrComment(assemblyCode[i+1])) continue;

        // 匹配 OR 指令：or $dst, $src, $zero
        std::regex orPattern(R"(\s*or\s+(\$[a-z0-9]+),\s*(\$[a-z0-9]+),\s*\$zero\s*(#.*)?)");
        std::smatch firstMatch, secondMatch;

        // 检查连续两条 OR 移动操作
        if (std::regex_match(assemblyCode[index], firstMatch, orPattern) &&
            std::regex_match(assemblyCode[index+1], secondMatch, orPattern)) {
            
            std::string firstDst = firstMatch.str(1);
            std::string firstSrc = firstMatch.str(2);
            std::string secondDst = secondMatch.str(1);
            std::string secondSrc = secondMatch.str(2);

            // 条件：第二条将值移回原寄存器（如 or $y, $x, $zero → or $x, $y, $zero）
            if (secondDst == firstSrc && secondSrc == firstDst) {
                assemblyCode.erase(assemblyCode.begin() + index + 1); // 删除第二条
                optimizationCount++;
                changed = true;
                // i--;
            }
        }
    // }
    return changed;
}


// 优化规则4: 移除无效指令
// bool AsmPeepholeOptimizer::removeUselessInstructions() {
//     bool changed = false;
    
//     for (size_t i = 0; i < assemblyCode.size(); i++) {
//         // 跳过标签和注释
//         if (isLabelOrComment(assemblyCode[i])) continue;
        
//         // 模式1: 移动到自身
//         // or $rx, $rx, $r0
//         std::regex selfMovePattern(R"(\s*or\s+\$r(\d+),\s*\$r(\1),\s*\$r0)");
        
//         if (std::regex_match(assemblyCode[i], selfMovePattern)) {
//             assemblyCode.erase(assemblyCode.begin() + i);
//             optimizationCount++;
//             changed = true;
//             i--; // 调整索引
//             continue;
//         }
        
//         // 模式2: 加0
//         // addi.d $rx, $rx, 0
//         std::regex addZeroPattern(R"(\s*addi\.[wd]\s+\$r(\d+),\s*\$r(\1),\s*0)");
        
//         if (std::regex_match(assemblyCode[i], addZeroPattern)) {
//             assemblyCode.erase(assemblyCode.begin() + i);
//             optimizationCount++;
//             changed = true;
//             i--; // 调整索引
//         }
//     }
    
//     return changed;
// }

bool AsmPeepholeOptimizer::removeUselessInstructions(int index) {
    bool changed = false;
    if(index >= assemblyCode.size()) return changed;
    if(isLabelOrComment(assemblyCode[index])) return changed;
    std::regex moveSelfPattern(   // 移动自身的 or 指令
        R"(\s*or\s+(\$[a-z0-9]+),\s*(\1),\s*\$zero\s*(#.*)?)"
    );
    std::regex addZeroPattern(    // addi 加 0
        R"(\s*addi\.([dw])\s+(\$[a-z0-9]+),\s*(\$[a-z0-9]+),\s*0+\s*(#.*)?)"
    );
    std::regex branchNextPattern( // 跳转到下一行的标签
        R"(\s*b\s+(\w+)\s*(#.*)?)"
    );
    std::regex labelPattern(     // 标签行的正则
        R"(\s*(\w+):\s*(#.*)?)"
    );

    // for (size_t i = 0; i < assemblyCode.size(); ++i) {
        // 模式1: OR 移动到自身
        std::smatch match;
        std::smatch branchMatch, labelMatch;
        if (std::regex_match(assemblyCode[index], match, moveSelfPattern)) {
            assemblyCode.erase(assemblyCode.begin() + index);
            optimizationCount++;
            changed = true;
            // i--; // 调整索引
            // continue;
        }
        // 模式2: ADDI 加 0
        else if (std::regex_match(assemblyCode[index], match, addZeroPattern)) {
            std::string dstReg = match.str(2);
            std::string srcReg = match.str(3);
            if (dstReg == srcReg) { // 仅当目标寄存器与源寄存器相同时删除
                assemblyCode.erase(assemblyCode.begin() + index);
                optimizationCount++;
                changed = true;
                // i--;
                // continue;
            }
        }
        // 模式3: 分支到下一行的标签
        else if (std::regex_match(assemblyCode[index], branchMatch, branchNextPattern)) {
            std::string label = branchMatch.str(1);
            if (index + 1 < assemblyCode.size() && 
                std::regex_match(assemblyCode[index+1], labelMatch, labelPattern) &&
                labelMatch.str(1) == label) {
                
                assemblyCode.erase(assemblyCode.begin() + index); // 删除跳转指令
                optimizationCount++;
                changed = true;
                // i--;
            }
        }
    // }

    return changed;
}


// 优化规则5: 优化条件分支
// bool AsmPeepholeOptimizer::optimizeConditionalBranches() {
//     bool changed = false;
    
//     for (size_t i = 0; i < assemblyCode.size() - 1; i++) {
//         // 跳过标签和注释
//         if (isLabelOrComment(assemblyCode[i])) continue;
        
//         // 模式: 条件分支到下一条指令
//         // beq/bne/etc $rx, $ry, label
//         // label:
//         std::regex branchPattern(R"(\s*b[a-z]+\s+.*,\s*(.+))");
//         std::regex labelPattern(R"((.+):)");
        
//         std::smatch branchMatch, labelMatch;
//         if (std::regex_match(assemblyCode[i], branchMatch, branchPattern) &&
//             i+1 < assemblyCode.size() &&
//             std::regex_match(assemblyCode[i+1], labelMatch, labelPattern)) {
            
//             // 检查分支目标是否是下一条指令的标签
//             if (branchMatch[1] == labelMatch[1]) {
//                 // 移除无意义的分支
//                 assemblyCode.erase(assemblyCode.begin() + i);
//                 optimizationCount++;
//                 changed = true;
//                 i--; // 调整索引
//             }
//         }
//     }
    
//     return changed;
// }

// 优化规则6: 合并立即数操作
// bool AsmPeepholeOptimizer::optimizeImmediateOperations() {
//     bool changed = false;
    
//     for (size_t i = 0; i < assemblyCode.size() - 1; i++) {
//         // 跳过标签和注释
//         if (isLabelOrComment(assemblyCode[i])) continue;
        
//         // 模式: 先加载立即数然后操作
//         // addi.d $rx, $r0, imm
//         // add.d $ry, $rz, $rx
//         std::regex loadImmPattern(R"(\s*addi\.[wd]\s+\$r(\d+),\s*\$r0,\s*(\d+))");
//         std::regex addPattern(R"(\s*add\.[wd]\s+\$r(\d+),\s*\$r(\d+),\s*\$r(\d+))");
        
//         std::smatch loadMatch, addMatch;
//         if (std::regex_match(assemblyCode[i], loadMatch, loadImmPattern) &&
//             std::regex_match(assemblyCode[i+1], addMatch, addPattern)) {
            
//             // 检查加载的寄存器是否用作加法的第二个操作数
//             if (loadMatch[1] == addMatch[3]) {
//                 // 检查此寄存器是否只用于此处
//                 // 这需要更全面的活跃性分析，此处简化处理
                
//                 // 转换为addi指令
//                 std::string newInstr = "    addi." + std::string(addMatch[0].str().find(".d") != std::string::npos ? "d" : "w") +
//                                      " $r" + std::string(addMatch[1]) + ", $r" + std::string(addMatch[2]) + 
//                                      ", " + std::string(loadMatch[2]);
                
//                 assemblyCode[i] = newInstr;
//                 assemblyCode.erase(assemblyCode.begin() + i + 1);
//                 optimizationCount++;
//                 changed = true;
//             }
//         }
//     }
    
//     return changed;
// }

// 使用示例
// std::vector<std::string> optimizeLoongArchAssembly(const std::vector<std::string>& assembly) {
//     AsmPeepholeOptimizer optimizer(assembly);
//     auto optimizedCode = optimizer.optimize();
    
//     std::cout << "Applied " << optimizer.getOptimizationCount() << " optimizations." << std::endl;
//     return optimizedCode;
// }
