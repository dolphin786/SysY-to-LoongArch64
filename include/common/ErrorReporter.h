#pragma once

#include <variant> 
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)

namespace SysYErrorHandling
{
    enum ErrorType
    {
        SYNTAX_ERROR,
        SEMANTIC_ERROR,
        COMPILER_ERROR
    };

    extern const std::string errorTypeTable[3];

    struct Error
    {
        public:
        std::string message;
        ErrorType type;
        std::string file;
        int line;
        int column;

        Error(const std::string& msg, ErrorType t, const std::string& f, int l, int c)
            : message(msg), type(t), file(f), line(l), column(c) {}
    };

    class ErrorReporter
    {
        private:
        std::vector<Error> errors;
        std::string curFile;//当前所处文件
        
        public:
        ErrorReporter() : curFile(""),errors({}) {}
        void addError(const std::string& message, ErrorType type, int line, int column)
        {
            errors.emplace_back(message, type, curFile, line, column);
        }
        void setCurrentFile(const std::string& file)
        {
            curFile = file;
        }
        void clearErrors()
        {
            errors.clear();
        }
        
        std::string toString()
        {
            std::string result;
            for (const auto& error : errors)
            {
                result += "[" + errorTypeTable[error.type] + "] " + curFile + "@" + std::to_string(error.line) + ":" + std::to_string(error.column) + " -> " + error.message + "\n";
            }
            return result;
        }

    };
}

