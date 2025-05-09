#include <antlr4-runtime.h>
#include "SysYLexer.h"
#include "SysYParser.h"
#include "checker/Checker.h"
#include "ir/IRGenerator.h"
#include "ir/IROptimizer.h"
#include <fstream>  // 新增文件流头文件
using std::cin;
using std::cout;
// const std::string inputFile = "../test/ircases/test7.sy";
// const std::string outputFile = "output.ll";  // 新增输出文件路径
int main(int argc, const char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input.sy> <output.ll>" << std::endl;
        return 1;
    }
    const std::string inputFile = argv[1];
    const std::string outputFile = argv[2];
    // 读取输入文件
    std::ifstream stream;
    
    stream.open(inputFile);
    
    // 创建词法分析器
    antlr4::ANTLRInputStream input(stream);
    {
        SysYLexer lexer(&input);
        {
            antlr4::CommonTokenStream tokens(&lexer);
            cout << "Successfully lexed.\n";
            {
                // 创建语法分析器
                SysYParser parser(&tokens);
                cout << "Successfully parsed.\n";
                {
                    auto* tree = parser.program();
                    cout << "Start checking...\n";
                    SysYChecker checker;
                    checker.setCurrentFile(inputFile);
                    checker.visit(tree);
                    checker.printErrors();
                    SysYIRGenerator irgen;
                    std::cout << "Start generating IR...\n";
                    irgen.visit(tree);
                    std::cout << "Finish generating IR.\n";
                    
                    std::unique_ptr<Module> m = irgen.getModule();

                    SysYIROptimizer optimizer(std::move(m));
                    optimizer.optimize();

                    m = optimizer.getModule();
                    // 新增文件输出模块
                    std::ofstream outStream(outputFile);
                    bool written = false;
                    if (outStream.is_open()) {
                        outStream << m->print();  // 写入输出文件
                        outStream.close();
                        cout << "IR written to: " << outputFile << "\n";
                        written = true;
                    } else {
                        std::cerr << "Failed to open output file!" << std::endl;
                        return 1;
                    }
                    checker.printErrors();
                    if(written)
                    {
                        std::exit(0);
                    }
                    std::cout << "Done!" << std::endl;

                }
            }  
        }
    }
    return 0;
}