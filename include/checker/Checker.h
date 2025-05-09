#pragma once
#include<antlr4-runtime.h>
#include "SysYBaseVisitor.h"
#include "common/ConstValue.h"
#include "common/Type.h"
#include "common/ErrorReporter.h"
#include <variant>
#include <optional>

#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)

// enum TYPE { TYPE_VOID, TYPE_INT, TYPE_FLOAT/*, TYPE_INT*/ };




struct Entry //符号表表项
{
    std::string name;
    bool is_array{};                       //是否为数组
    bool is_func{};                        //是否为函数
    bool is_const{};                       //是否为常量
    TYPE type;                             //变量类型or返回值类型，注意是基础类型/函数返回值类型，仅有void，int，float
    int array_length{};                    //如果是数组，则长度非0
    std::vector<int> arlen_value;          //数组的每一维长度
    std::vector<struct Entry> func_params; //函数参数列表
    MultipleConstValue const_value;                //为常量时的数值

};

//存放运行时库函数符号表项的数组
const Entry libFuncTable[] = {
    // 1. int getint()
    {
        "getint",
        false,  // is_array
        true,   // is_func
        false,  // is_const
        TYPE_INT,
        0,
        {},
        {},     // 无参数
        // const_value
    },

    // 2. int getch()
    {
        "getch",
        false,
        true,
        false,
        TYPE_INT,
        0,
        {},
        {},
        // const_value
    },

    // 3. float getfloat()
    {
        "getfloat",
        false,
        true,
        false,
        TYPE_FLOAT,
        0,
        {},
        {},
        // const_value
    },

    // 4. int getarray(int[])
    {
        "getarray",
        false,
        true,
        false,
        TYPE_INT,
        0,
        {},
        { // 参数列表
            {
                "",      // 参数无名
                true,    // is_array（参数是数组）
                false,
                false,
                TYPE_INT,
                0x7fffffff,
                {0x7fffffff},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 5. int getfarray(float[])
    {
        "getfarray",
        false,
        true,
        false,
        TYPE_INT,
        0,
        {},
        {
            {
                "",
                true,
                false,
                false,
                TYPE_FLOAT,
                0x7fffffff,
                {0x7fffffff},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 6. void putint(int)
    {
        "putint",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        {
            {
                "",
                false,
                false,
                false,
                TYPE_INT,
                0,
                {},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 7. void putch(int)
    {
        "putch",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        {
            {
                "",
                false,
                false,
                false,
                TYPE_INT,
                0,
                {},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 8. void putfloat(float)
    {
        "putfloat",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        {
            {
                "",
                false,
                false,
                false,
                TYPE_FLOAT,
                0,
                {},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 9. void putarray(int, int[])
    {
        "putarray",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        { // 两个参数
            { // int参数
                "",
                false,
                false,
                false,
                TYPE_INT,
                0,
                {},
                {},
                // const_value
            },
            { // int数组参数
                "",
                true,
                false,
                false,
                TYPE_INT,
                0x7fffffff,
                {0x7fffffff},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 10. void putfarray(int, float[])
    {
        "putfarray",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        { // 两个参数
            { // int参数
                "",
                false,
                false,
                false,
                TYPE_INT,
                0,
                {},
                {},
                // const_value
            },
            { // float数组参数
                "",
                true,
                false,
                false,
                TYPE_FLOAT,
                0x7fffffff,
                {0x7fffffff},
                {},
                // const_value
            }
        },
        // const_value
    },
    // 11. void putf(string, ...)
    {
        "putf",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        { // 一个字符串字面量参数，后面的可变参数不写
            { // string参数
                "",
                false,
                false,
                false,
                TYPE_STRING,
                0,
                {},
                {},
                // const_value
            }
        },
        // const_value
    },

    // 12. void starttime()
    {
        "starttime",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        {},     // 无参数
        // const_value
    },
    
    //13. void stoptime()
    {
        "stoptime",
        false,
        true,
        false,
        TYPE_VOID,
        0,
        {},
        {},     // 无参数
        // const_value
    }
};

class Scope{
    private:
    std::vector<std::unordered_map<std::string, Entry>> varConstTables;//变量/常量的符号表
    std::vector<std::unordered_map<std::string, Entry>> funcTables;//函数的符号表
    int loopCount{};//在循环中的层数

    public:
    void enter() { varConstTables.push_back({}); funcTables.push_back({}); }
    void exit() { varConstTables.pop_back(); funcTables.pop_back(); }

    void startLoop() { loopCount++; }
    void endLoop() { loopCount--; }
    //插入变量/常量符号
    inline bool addVarConstEntry(const Entry& sym) {
        if(varConstTables.empty())
        {
            //报错，没有作用域
            TODO("报错，没有作用域");
            return false;
        }
        auto& table = varConstTables.back();
        auto it = table.find(sym.name);
        if(it != table.end())
        {
            // TODO("报错，说明该变量已定义，此处为重复定义");
            //报错，说明该变量已定义，此处为重复定义
            return false;
        }
        table[sym.name] = sym;
        // printf("addEntry: %s\n",sym.name.c_str());
        // printf("scopesize: %ld\n",table.size());
        return true;
    }
    //插入函数符号
    inline bool addFuncEntry(const Entry& sym) {
        if(funcTables.empty())
        {
            //报错，没有作用域
            TODO("报错，没有作用域");
            return false;
        }
        auto& table = funcTables.back();
        auto it = table.find(sym.name);
        if(it != table.end())
        {
            // TODO("报错，说明该函数已定义，此处为重复定义");
            //报错，说明该函数已定义，此处为重复定义
            return false;
        }
        table[sym.name] = sym;
        // printf("addEntry: %s\n",sym.name.c_str());
        // printf("scopesize: %ld\n",table.size());
        return true;
    }

    //查找变量/常量符号
    inline Entry* lookupVarConst(const std::string& name) 
    {
        for(auto it = varConstTables.rbegin(); it!= varConstTables.rend();it++)
        {
            auto& table = (*it);
            auto tmp = table.find(name);
            if(tmp!=table.end())
            {
                return &((*tmp).second);
            }
        }
        return nullptr;
    }
    //查找函数符号
    inline Entry* lookupFunc(const std::string& name) 
    {
        for(auto it = funcTables.rbegin(); it!= funcTables.rend();it++)
        {
            auto& table = (*it);
            auto tmp = table.find(name);
            if(tmp!=table.end())
            {
                return &((*tmp).second);
            }
        }
        return nullptr;
    }
    inline bool inLoop() {

        /* 检查当前是否在循环中 */
        return (loopCount > 0);
    }

    inline void print()
    {
        printf("%d scopes:\n",varConstTables.size());
        std::string typeToString[4] = {"void","int","float","bool"}; 
        int cnt0 = 0;
        for(const auto& scope : varConstTables)
        {
            cnt0++;
            printf("scope %d: %ld entries\n",cnt0, scope.size());
            printf("\nno  %-10s%-10s%-10s%-10s%-10s%-10s\n","name","type","array","func","const","constval");
            int cnt = 0;
            for(const auto& pair : scope)
            {
                cnt++;
                const Entry& e = pair.second;
                // e = (*it).second;
                printf("%-4d%-10s%-10s%-10d%-10d%-10d",cnt,e.name.c_str(), typeToString[e.type].c_str(), e.is_array,e.is_func,e.is_const);
                e.const_value.print();
                // if(e.const_value.type == TYPE_INT)
                // {
                //     printf("%-10d",std::get<int>(e.const_value.data));
                // }
                // else if(e.const_value.type == TYPE_FLOAT)
                // {
                //     printf("%-10f",std::get<float>(e.const_value.data));
                // }
                // else
                // {
                //     TODO("不支持的类型");
                // }
                printf("\n");
            }
        }
        
    }
    bool inGlobalScope()
    {
        return (varConstTables.size() == 1);
    }
    
};

class SysYChecker : public SysYBaseVisitor
{
    private:

    SysYErrorHandling::ErrorReporter errorReporter;//错误报告器

    Scope curScopes;//当前的各个作用域以及它们的符号表

    bool inGlobalScope()//检查当前是否在全局作用域中
    {
        return curScopes.inGlobalScope();
    }

    TYPE curDefType{};//当前定义语句的类型

    TYPE curFuncType{};//当前函数的返回值类型

    std::map<std::string, TYPE> typeTable;//将类型名字符串转换成TYPE

    TYPE retType{};//返回的表达式类型，仅在visitExp, visitAddExp, visitMulExp中使用，不适用于条件表达式和常量表达式

    MuiltipleType retMultipleType; //返回的多重类型，用于检查初始化列表类型

    int inExp{};//当前是否处在int/float型表达式中，即不是条件表达式，由于可能出现多个Exp嵌套，因此用int代替bool，用+=1/-=1代替=true/=false

    int inConstExp{};//当前是否处在常量表达式中，由于可能出现多个常量表达式嵌套，因此用int代替bool，用+=1/-=1代替=true/=false

    int inGlobalVarDecl{};//当前是否处在全局变量声明中

    ConstValue retConstValue;//要返回的常量表达式的值

    MultipleConstValue retMultipleConstValue;//要返回的多重常量的值，用于检查常量初始化列表

    Entry lastFuncFParam; //上一个函数参数的符号表项，从visitFuncFParamSingle/visitFuncFparamArray返回给visitFuncDef做进一步操作

    // class Array
    // {
    //     TYPE type;
    //     std::vector<int> arlen_value; //数组的每一维长度
    // };
    // std::optional<Array> retArray{}; //要返回的数组类型，用于函数的数组实参的类型检查，当返回值不是数组时设置为nulopt

    

    void initTables();
    // TYPE getResultingType(TYPE x, TYPE y);//获得两个类型算术运算后的类型

    void addLibFunc();//插入运行时库函数（除了putf，putf使用特判）

    bool viewMultipleConstValue(MultipleConstValue &val, const std::vector<int>& arlen_value, int array_length, int& cnt, std::string& error);
    bool viewMultipleTypes(MuiltipleType &val, const std::vector<int>& arlen_value, int array_length, int& cnt, std::string& error);

    bool checkFuncRParamArrayExp(SysYParser::ExpContext* ctx, TYPE type, const std::vector<int>& arlen_value);//检查函数的数组实参里的表达式是否符合要求
    // void initcurScopes();
    // void buildVariable(std::String name)
    public:
    antlrcpp::Any visitProgram(SysYParser::ProgramContext *ctx) override;

    antlrcpp::Any visitErrorNode(antlr4::tree::ErrorNode *node) override;

    

    antlrcpp::Any visitConstDecl(SysYParser::ConstDeclContext* ctx) override;

    antlrcpp::Any visitConstDefSingle(SysYParser::ConstDefSingleContext* ctx) override;

    antlrcpp::Any visitConstDefArray(SysYParser::ConstDefArrayContext* ctx) override;

    antlrcpp::Any visitConstInitValSingle(SysYParser::ConstInitValSingleContext* ctx) override;

    antlrcpp::Any visitConstInitValArray(SysYParser::ConstInitValArrayContext* ctx) override;

    antlrcpp::Any visitInitValSingle(SysYParser::InitValSingleContext* ctx) override;

    antlrcpp::Any visitInitValArray(SysYParser::InitValArrayContext* ctx) override;
    
    antlrcpp::Any visitVarDecl(SysYParser::VarDeclContext* ctx) override;
    
    antlrcpp::Any visitVarDefSingle(SysYParser::VarDefSingleContext* ctx) override;

    antlrcpp::Any visitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext* ctx) override;

    antlrcpp::Any visitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext* ctx) override;
    
    antlrcpp::Any visitVarDefArray(SysYParser::VarDefArrayContext* ctx) override;



    antlrcpp::Any visitConstExp(SysYParser::ConstExpContext* ctx) override;

    antlrcpp::Any visitExp(SysYParser::ExpContext* ctx) override;

    antlrcpp::Any visitAddExp(SysYParser::AddExpContext* ctx) override;

    antlrcpp::Any visitMulExp(SysYParser::MulExpContext* ctx) override;

    antlrcpp::Any visitUnaryExpUnary(SysYParser::UnaryExpUnaryContext* ctx) override;

    antlrcpp::Any visitLValSingle(SysYParser::LValSingleContext* ctx) override;

    antlrcpp::Any visitLValArray(SysYParser::LValArrayContext* ctx) override;

    antlrcpp::Any visitNumber(SysYParser::NumberContext* ctx) override;

    antlrcpp::Any visitRelExp(SysYParser::RelExpContext* ctx) override;

    antlrcpp::Any visitEqExp(SysYParser::EqExpContext* ctx) override;

    antlrcpp::Any visitLAndExp(SysYParser::LAndExpContext* ctx) override;

    antlrcpp::Any visitLOrExp(SysYParser::LOrExpContext* ctx) override;



    antlrcpp::Any visitFuncDef(SysYParser::FuncDefContext *ctx) override;

    antlrcpp::Any visitFuncFParamSingle(SysYParser::FuncFParamSingleContext *ctx) override;

    antlrcpp::Any visitFuncFParamArray(SysYParser::FuncFParamArrayContext *ctx) override;

    antlrcpp::Any visitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext* ctx) override;



    antlrcpp::Any visitStmtReturn(SysYParser::StmtReturnContext* ctx) override;

    antlrcpp::Any visitStmtBlock(SysYParser::StmtBlockContext* ctx) override;

    antlrcpp::Any visitStmtBreak(SysYParser::StmtBreakContext* ctx) override;

    antlrcpp::Any visitStmtContinue(SysYParser::StmtContinueContext* ctx) override;

    antlrcpp::Any visitStmtWhile(SysYParser::StmtWhileContext* ctx) override;

    void printErrors()
    {
        printf("%s",errorReporter.toString().c_str());
    }
    void setCurrentFile(const std::string& file)
    {
        errorReporter.setCurrentFile(file);
    }
    
};