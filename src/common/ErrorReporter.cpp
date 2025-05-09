#include "common/ErrorReporter.h"
namespace SysYErrorHandling
{
    const std::string errorTypeTable[3] =
    {
        "Syntax Error",
        "Semantic Error",
        "Compiler Error" //编译器错误，由于编译器代码出错导致的正常情况下不应该出现的bug
    };
}