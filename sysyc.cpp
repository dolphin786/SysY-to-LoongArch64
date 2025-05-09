#include <antlr4-runtime.h>
#include "SysYLexer.h"
#include "SysYParser.h"
#include "checker/Checker.h"
#include "ir/IRGenerator.h"
#include "ir/IROptimizer.h"
#include "asm/AsmEmitter.h"
#include "asm/AsmPeepholeOptimizer.h"

#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

using std::cin;
using std::cout;

void printHelp(const char* progName) {
    std::cerr << "Usage: " << progName << " <input-file> [options]\n"
              << "Options:\n"
              << "  -S <file>        Place assembly output into <file>\n"
              << "  -i <file>        Output LLVM IR to <file>\n"
              << "  --ir <file>      Same as -i\n"
              << "  -h, --help       Print this help message\n";
}

struct CompilerOptions {
    std::string inputFile;
    std::string outputFile;  // 汇编输出文件
    std::string irOutputFile;  // IR输出文件
};

CompilerOptions parseArguments(int argc, const char* argv[]) {
    CompilerOptions options;
    bool hasInputFile = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-S") {
            if (i + 1 >= argc) {
                std::cerr << "Error: Missing filename after -S\n";
                exit(1);
            }
            options.outputFile = argv[++i];
        } 
        else if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            exit(0);
        }
        else if (arg == "-i" || arg == "--ir") {
            if (i + 1 >= argc) {
                std::cerr << "Error: Missing filename after " << arg << "\n";
                exit(1);
            }
            options.irOutputFile = argv[++i];
        }
        else if (arg[0] == '-') {
            std::cerr << "Error: Unknown option '" << arg << "'\n";
            printHelp(argv[0]);
            exit(1);
        }
        else {
            if (hasInputFile) {
                std::cerr << "Error: Multiple input files specified\n";
                exit(1);
            }
            options.inputFile = arg;
            hasInputFile = true;
        }
    }

    if (!hasInputFile) {
        std::cerr << "Error: No input file specified\n";
        printHelp(argv[0]);
        exit(1);
    }

    // 设置默认汇编输出文件名
    if (options.outputFile.empty()) {
        fs::path p = options.inputFile;
        options.outputFile = p.replace_extension(".s").string();
    }

    return options;
}

int main(int argc, const char* argv[]) {
    CompilerOptions options = parseArguments(argc, argv);
    
    // 读取输入文件
    std::ifstream stream;
    stream.open(options.inputFile);
    if (!stream.is_open()) {
        std::cerr << "Error: Cannot open input file '" << options.inputFile << "'\n";
        std::exit(1);
    }

    // 创建词法分析器
    antlr4::ANTLRInputStream input(stream);
    SysYLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    // 创建语法分析器
    SysYParser parser(&tokens);
    auto* tree = parser.program();

    // 语义检查
    SysYChecker checker;
    checker.setCurrentFile(options.inputFile);
    checker.visit(tree);
    checker.printErrors();

    // 生成IR
    SysYIRGenerator irgen;
    irgen.visit(tree);
    std::unique_ptr<Module> m = irgen.getModule();

    // 输出IR（如果需要）
    if (!options.irOutputFile.empty()) {
        std::ofstream irOut(options.irOutputFile);
        if (irOut.is_open()) {
            irOut << m->print();
            std::cout << "LLVM IR written to: " << options.irOutputFile << std::endl;
        } else {
            std::cerr << "Warning: Failed to open IR output file '" 
                      << options.irOutputFile << "'\n";
        }
    }

    // IR优化
    SysYIROptimizer irOptimizer(std::move(m));
    irOptimizer.optimize();
    m = irOptimizer.getModule();

    // 生成汇编
    std::ofstream outStream(options.outputFile);
    if (!outStream.is_open()) {
        std::cerr << "Error: Cannot open output file '" << options.outputFile << "'\n";
        std::exit(1);
    }

    AsmEmitter asmEmitter(std::move(m));
    std::string asmCode = asmEmitter.emit();

    // 汇编优化
    std::vector<std::string> asmCodeVec;
    std::stringstream ss(asmCode);
    std::string line;
    while (std::getline(ss, line)) {
        asmCodeVec.push_back(line);
    }
    // for(const auto& line : asmCodeVec)
    // {
    //     std::cout << line << std::endl;
    // }
    AsmPeepholeOptimizer optimizer(asmCodeVec);
    asmCodeVec = optimizer.optimize();
    // for(const auto& line : asmCodeVec)
    // {
    //     std::cout << line << std::endl;
    // }
    // 输出最终汇编
    for (const auto& line : asmCodeVec) {
        outStream << line << "\n";
    }
    std::cout<<"asmCodeVec.size(): "<<asmCodeVec.size()<<" optimizationCount: "<<optimizer.getOptimizationCount()<<std::endl;
    outStream.close();
    std::cout << "Done! Assembly written to: " << options.outputFile << std::endl;
    std::exit(0);
    return 0;
}



// #include <antlr4-runtime.h>

// #include "SysYLexer.h"
// #include "SysYParser.h"
// #include "checker/Checker.h"
// #include "ir/IRGenerator.h"
// #include "ir/IROptimizer.h"
// #include "asm/AsmEmitter.h"
// #include "asm/AsmPeepholeOptimizer.h"

// #include <fstream> 
// using std::cin;
// using std::cout;

// int main(int argc, const char* argv[]) {
//     if (argc < 3) {
//         std::cerr << "Usage: " << argv[0] << " <input.sy> <output.s>" << std::endl;
//         return 1;
//     }
//     const std::string inputFile = argv[1];
//     const std::string outputFile = argv[2];
//     // 读取输入文件
//     std::ifstream stream;
    
//     stream.open(inputFile);
    
//     // 创建词法分析器
//     antlr4::ANTLRInputStream input(stream);

//     SysYLexer lexer(&input);

//     antlr4::CommonTokenStream tokens(&lexer);
//     // cout << "Successfully lexed.\n";

//             // 创建语法分析器
//     SysYParser parser(&tokens);
//     // cout << "Successfully parsed.\n";

//     auto* tree = parser.program();
//     // cout << "Start checking...\n";
//     SysYChecker checker;
//     checker.setCurrentFile(inputFile);
//     checker.visit(tree);
//     checker.printErrors();

//     SysYIRGenerator irgen;
//     // std::cout << "Start generating IR...\n";
//     irgen.visit(tree);
//     // std::cout << "Finish generating IR.\n";
    
//     std::unique_ptr<Module> m = irgen.getModule();
//     // std::cout << "Start optimizing IR...\n";
//     SysYIROptimizer irOptimizer(std::move(m));
//     irOptimizer.optimize();
//     // std::cout << "Finish optimizing IR.\n";
//     m = irOptimizer.getModule();
//     // 新增文件输出模块
//     std::ofstream outStream(outputFile);

//     // std::cout << "Start generating ASM...\n";
//     AsmEmitter asmEmitter(std::move(m));

//     std::string asmCode = asmEmitter.emit();
//     std::vector<std::string> asmCodeVec;
//     std::stringstream ss(asmCode);
//     std::string line;
//     while (std::getline(ss, line)) {
//         asmCodeVec.push_back(line);
//     }
//     // std::cout << "Finish generating ASM.\n";

//     // std::cout << "Start optimizing ASM...\n";
//     AsmPeepholeOptimizer optimizer(asmCodeVec);
//     asmCodeVec = optimizer.optimize();
//     std::string optimizedAsmCode;
//     for (const auto& line : asmCodeVec) {
//         optimizedAsmCode += line + "\n";
//     }
//     // std::cout << "Finish optimizing ASM. Applied " << optimizer.getOptimizationCount() << " optimizations.\n";
//     // std::cout << "11.\n";
//     // bool written = false;
//     if (outStream.is_open()) {
//         // outStream << m->print();  // 写入输出文件
//         outStream << optimizedAsmCode;  // 写入输出文件
//         outStream.close();
//         // cout << "Asm written to: " << outputFile << "\n";
//         std::cout << "Done! Asm written to: " << outputFile << std::endl;
//         std::exit(0);
//     } else {
//         std::cerr << "Failed to open output file!" << std::endl;
//         std::exit(1);
//         return 1;
//     }
    
//     // can't reach here

                
            
        
    
//     return 0;
// }