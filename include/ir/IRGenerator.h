#pragma once
#include<antlr4-runtime.h>
#include "SysYBaseVisitor.h"

#include "common/ErrorReporter.h"
#include "ir/IR.h"
#include <variant>
#include <optional>
#include <string>

#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)

using std::vector;
using std::unique_ptr;

class ValueScope{
    private:
    std::vector<std::unordered_map<std::string, Value*>> varConstTables;//变量/常量的符号表
    std::vector<std::unordered_map<std::string, Value*>> funcTables;//函数的符号表
    int loopCount{};//在循环中的层数

    public:
    void enter() { varConstTables.push_back({}); funcTables.push_back({}); }
    void exit() { varConstTables.pop_back(); funcTables.pop_back(); }

    void startLoop() { loopCount++; }
    void endLoop() { loopCount--; }
    //插入变量/常量符号
    inline bool addVarConstEntry(std::string name, Value* sym) {
        if(varConstTables.empty())
        {
            //报错，没有作用域
            TODO("报错，没有作用域");
            return false;
        }
        auto& table = varConstTables.back();
        auto it = table.find(name);
        if(it != table.end())
        {
            // TODO("报错，说明该变量已定义，此处为重复定义");
            //报错，说明该变量已定义，此处为重复定义
            return false;
        }
        table[name] = sym;
        // printf("addEntry: %s\n",sym.name.c_str());
        // printf("scopesize: %ld\n",table.size());
        return true;
    }
    //插入函数符号
    inline bool addFuncEntry(std::string name, Value* sym) {
        if(funcTables.empty())
        {
            //报错，没有作用域
            TODO("报错，没有作用域");
            return false;
        }
        auto& table = funcTables.back();
        auto it = table.find(name);
        if(it != table.end())
        {
            // TODO("报错，说明该函数已定义，此处为重复定义");
            //报错，说明该函数已定义，此处为重复定义
            return false;
        }
        table[name] = sym;
        // printf("addEntry: %s\n",sym.name.c_str());
        // printf("scopesize: %ld\n",table.size());
        return true;
    }

    //查找变量/常量符号
    inline Value* lookupVarConst(const std::string& name) 
    {
        for(auto it = varConstTables.rbegin(); it!= varConstTables.rend();it++)
        {
            auto& table = (*it);
            auto tmp = table.find(name);
            if(tmp!=table.end())
            {
                return ((*tmp).second);
            }
        }
        return nullptr;
    }
    //查找函数符号
    inline Value* lookupFunc(const std::string& name) 
    {
        for(auto it = funcTables.rbegin(); it!= funcTables.rend();it++)
        {
            auto& table = (*it);
            auto tmp = table.find(name);
            if(tmp!=table.end())
            {
                return ((*tmp).second);
            }
        }
        return nullptr;
    }
    inline bool inLoop() {

        /* 检查当前是否在循环中 */
        return (loopCount > 0);
    }

    // inline void print()
    // {
    //     std::string typeToString[4] = {"void","int","float","bool"}; 
    //     int cnt0 = 0;
    //     for(const auto& scope : varConstTables)
    //     {
    //         cnt0++;
    //         printf("scope %d: %ld entries\n",cnt0, scope.size());
    //         printf("\nno  %-10s%-10s%-10s%-10s%-10s%-10s\n","name","type","array","func","const","constval");
    //         int cnt = 0;
    //         for(const auto& pair : scope)
    //         {
    //             cnt++;
    //             const Entry& e = pair.second;
    //             // e = (*it).second;
    //             printf("%-4d%-10s%-10s%-10d%-10d%-10d",cnt,e.name.c_str(), typeToString[e.type].c_str(), e.is_array,e.is_func,e.is_const);
    //             e.const_value.print();
    //             // if(e.const_value.type == TYPE_INT)
    //             // {
    //             //     printf("%-10d",std::get<int>(e.const_value.data));
    //             // }
    //             // else if(e.const_value.type == TYPE_FLOAT)
    //             // {
    //             //     printf("%-10f",std::get<float>(e.const_value.data));
    //             // }
    //             // else
    //             // {
    //             //     TODO("不支持的类型");
    //             // }
    //             printf("\n");
    //         }
    //     }
        
    // }
    bool inGlobalScope()
    {
        return (varConstTables.size() == 1);
    }
    
};

class SysYIRGenerator : public SysYBaseVisitor
{
    private:

    SysYErrorHandling::ErrorReporter errorReporter;//错误报告器

    Type *curDefType{}; // 当前定义的类型
    std::map<std::string, Type* > typeTable;//将类型名字符串转换成Type*

    void initTables();

    bool checkCalType(Value **val, int *intVal, float *floatVal);//根据待计算的两个Constant的类型，求出对应的值赋值到intVal，floatVal中，返回计算结果是否为int

    void checkCalType(Value* val[]);//根据待计算的两个寄存器数的类型，若需要转换类型输出转换指令

    Value* retValue{}; //最近的表达式的值

    int inConstExp{}; //是否在常量表达式中

    IRStmtBuilder *builder;
    ValueScope curScopes;
    std::unique_ptr<Module> module;

    bool requireLVal = false; //告诉lval结点是否是真左值，如果不是那么需要发射load指令把值放到寄存器中
    Function *currentFunction = nullptr;    //当前函数
    Value *recentVal = nullptr;             //最近的表达式的value
    BasicBlock *whileCondBB = nullptr;      //while语句cond分支
    BasicBlock *trueBB = nullptr;           //通用true分支，即while和if为真时所跳转的基本块
    BasicBlock *falseBB = nullptr;          //通用false分支，即while和if为假时所跳转的基本块
    BasicBlock * whileFalseBB;              //while语句false分支，用于break跳转
    int id = 1;                             //recent标号
    bool has_br = false;            //一个BB中是否已经出现了br
    bool is_single_exp = false;     //作为单独的exp语句出现，形如 "exp;"
    std::vector<Type *> params;             //函数形参类型表
    std::vector<std::string> paramNames;    //函数形参名表
    Value *retAlloca = nullptr;             //返回值
    BasicBlock *retBB = nullptr;            //返回语句块

    public:
    antlrcpp::Any visitProgram(SysYParser::ProgramContext *ctx) override;

    // antlrcpp::Any visitErrorNode(antlr4::tree::ErrorNode *node) override;

    

    antlrcpp::Any visitConstDecl(SysYParser::ConstDeclContext* ctx) override;

    antlrcpp::Any visitConstDefSingle(SysYParser::ConstDefSingleContext* ctx) override;

    antlrcpp::Any visitConstDefArray(SysYParser::ConstDefArrayContext* ctx) override;

    // antlrcpp::Any visitConstInitValSingle(SysYParser::ConstInitValSingleContext* ctx) override;

    // antlrcpp::Any visitConstInitValArray(SysYParser::ConstInitValArrayContext* ctx) override;

    // antlrcpp::Any visitInitValSingle(SysYParser::InitValSingleContext* ctx) override;

    // antlrcpp::Any visitInitValArray(SysYParser::InitValArrayContext* ctx) override;
    
    antlrcpp::Any visitVarDecl(SysYParser::VarDeclContext* ctx) override;
    
    antlrcpp::Any visitVarDefSingle(SysYParser::VarDefSingleContext* ctx) override;

    antlrcpp::Any visitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext* ctx) override;

    antlrcpp::Any visitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext* ctx) override;
    
    antlrcpp::Any visitVarDefArray(SysYParser::VarDefArrayContext* ctx) override;



    antlrcpp::Any visitConstExp(SysYParser::ConstExpContext* ctx) override;

    // antlrcpp::Any visitExp(SysYParser::ExpContext* ctx) override;

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

    antlrcpp::Any visitStmtAssign(SysYParser::StmtAssignContext* ctx) override;

    antlrcpp::Any visitStmtCond(SysYParser::StmtCondContext* ctx) override;

    antlrcpp::Any visitStmtExp(SysYParser::StmtExpContext* ctx) override;

    antlrcpp::Any visitBlock(SysYParser::BlockContext* ctx) override;

    SysYIRGenerator()
    {
        module = std::unique_ptr<Module>(new Module());
        builder = new IRStmtBuilder(nullptr, module.get());
        auto TyVoid = module->void_ty_;
        auto TyInt32 = module->int32_ty_;
        auto TyInt32Ptr = module->get_pointer_type(module->int32_ty_);
        auto TyFloat = module->float32_ty_;
        auto TyFloatPtr = module->get_pointer_type(module->float32_ty_);

        auto input_type = new FunctionType(TyInt32, {});
        auto get_int = new Function(input_type, "getint", module.get());

        input_type = new FunctionType(TyFloat, {});
        auto get_float = new Function(input_type, "getfloat", module.get());

        input_type = new FunctionType(TyInt32, {});
        auto get_char = new Function(input_type, "getch", module.get());

        std::vector<Type *> input_params;
        std::vector<Type *>().swap(input_params);
        input_params.push_back(TyInt32Ptr);
        input_type = new FunctionType(TyInt32, input_params);
        auto get_int_array = new Function(input_type, "getarray", module.get());

        std::vector<Type *>().swap(input_params);
        input_params.push_back(TyFloatPtr);
        input_type = new FunctionType(TyInt32, input_params);
        auto get_float_array = new Function(input_type, "getfarray", module.get());

        std::vector<Type *> output_params;
        std::vector<Type *>().swap(output_params);
        output_params.push_back(TyInt32);
        auto output_type = new FunctionType(TyVoid, output_params);
        auto put_int = new Function(output_type, "putint", module.get());

        std::vector<Type *>().swap(output_params);
        output_params.push_back(TyFloat);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_float = new Function(output_type, "putfloat", module.get());

        std::vector<Type *>().swap(output_params);
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_char = new Function(output_type, "putch", module.get());

        std::vector<Type *>().swap(output_params);
        output_params.push_back(TyInt32);
        output_params.push_back(TyInt32Ptr);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_int_array = new Function(output_type, "putarray", module.get());

        std::vector<Type *>().swap(output_params);
        output_params.push_back(TyInt32);
        output_params.push_back(TyFloatPtr);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_float_array = new Function(output_type, "putfarray", module.get());

        output_params.clear();
        output_params.push_back(TyInt32);
        auto time_type = new FunctionType(TyVoid, output_params);
        auto sysy_start_time = new Function(time_type, "_sysy_starttime", module.get());
        auto sysy_stop_time = new Function(time_type, "_sysy_stoptime", module.get());

        output_params.clear();
        output_params.push_back(TyInt32Ptr);
        output_params.push_back(TyInt32Ptr);
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto memcpy = new Function(output_type, "__aeabi_memcpy4", module.get());

        output_params.clear();
        output_params.push_back(TyInt32Ptr);
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto memclr = new Function(output_type, "__aeabi_memclr4", module.get());

        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto memset = new Function(output_type, "__aeabi_memset4", module.get());

        output_params.clear();
        output_type = new FunctionType(TyVoid, output_params);
        auto llvm_memset = new Function(output_type, "llvm.memset.p0.i32", module.get());

        // output_params.clear();
        // output_params.push_back(TyInt32);
        // output_type = new FunctionType(TyInt32, output_params);
        // auto my_malloc = new Function(output_type, "malloc", module.get());


        curScopes.enter();
        curScopes.addFuncEntry("getint", get_int);
        curScopes.addFuncEntry("getfloat", get_float);
        curScopes.addFuncEntry("getch", get_char);
        curScopes.addFuncEntry("getarray", get_int_array);
        curScopes.addFuncEntry("getfarray", get_float_array);
        curScopes.addFuncEntry("putint", put_int);
        curScopes.addFuncEntry("putfloat", put_float);
        curScopes.addFuncEntry("putch", put_char);
        curScopes.addFuncEntry("putarray", put_int_array);
        curScopes.addFuncEntry("putfarray", put_float_array);
        curScopes.addFuncEntry("_sysy_starttime", sysy_start_time);
        curScopes.addFuncEntry("_sysy_stoptime", sysy_stop_time);
        curScopes.addFuncEntry("memcpy", memcpy);
        curScopes.addFuncEntry("memclr", memclr);
        curScopes.addFuncEntry("memset", memset);
        curScopes.addFuncEntry("llvm.memset.p0.i32", llvm_memset);
        // scope.push("malloc",my_malloc);
    }

    std::unique_ptr<Module> getModule() {
        return std::move(module);
    }

    void checkInitType();

    void printErrors()
    {
        printf("%s",errorReporter.toString().c_str());
    }
    void setCurrentFile(const std::string& file)
    {
        errorReporter.setCurrentFile(file);
    }

    static int getNextDim(vector<int> &elementsCnts, int up);

    ConstantArray *globalInit(vector<int> &dimensions, vector<ArrayType *> &arrayTys, int up, vector<SysYParser::ConstInitValContext*> &list);

    ConstantArray* globalInit(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, vector<SysYParser::InitValContext*> &list);

    static void
    mergeElements(vector<int> &dimensions, vector<ArrayType *> &arrayTys, int up, int dimAdd,
                  vector<Constant *> &elements,
                  vector<int> &elementsCnts);

    void finalMerge(vector<int> &dimensions, vector<ArrayType *> &arrayTys, int up, vector<Constant *> &elements,
                    vector<int> &elementsCnts) const;

    int getNextDim(vector<int> &dimensionsCnt, int up, int cnt);

    void localInit(Value* ptr, vector<SysYParser::ConstInitValContext*> &list, vector<int> &dimensionsCnt, int up);

    void localInit(Value* ptr, vector<SysYParser::InitValContext*> &list, vector<int> &dimensionsCnt, int up);

};