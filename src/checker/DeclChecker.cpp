#include<antlr4-runtime.h>
#include "checker/Checker.h"


#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)
#define CURRENT_LINE(c) (c->getStart()->getLine())
#define CURRENT_COLUMN(c) (c->getStart()->getCharPositionInLine()+1) 
#define REPORT_SEMANTIC_ERROR_AND_RETURN(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));return nullptr;}while(0)
#define REPORT_SEMANTIC_ERROR_AND_EXIT(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx)); printErrors(); std::exit(0);}while(0)

antlrcpp::Any SysYChecker::visitConstDecl(SysYParser::ConstDeclContext* ctx) 
{
    // printf("visitConstDecl\n");
    curDefType = typeTable[ctx->bType()->getText()];
    // inConstExp = true;
    for(SysYParser::ConstDefContext* c : ctx->constDef())
    {
        visit(c);
    }
    // inConstExp = false;
    // curScopes.print();
    return nullptr;
}

antlrcpp::Any SysYChecker::visitConstDefSingle(SysYParser::ConstDefSingleContext* ctx) 
{
    // printf("visitConstDefSingle\n");
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>(); 
    // Entry *tmp = new Entry;
    tmp->name = ctx->Identifier()->getText();
    // std::cout<<tmp->name<<" 2314\n";
    tmp->is_func = false;
    tmp->is_array = false;
    tmp->is_const = true;
    tmp->type = curDefType;
    if(ctx->constInitVal()!=nullptr)
    {
        visit(ctx->constInitVal());
        // if(retMultipleConstValue.type != curDefType)
        // {
        //     TODO("常量类型不匹配");
        // }
        if(retMultipleConstValue.isArray())
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Non-array constant initialized with initializer list", ctx);
            // errorReporter.addError("Non-array constant initialized with initializer list", SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));
            // TODO("常量初始值不是单个值");
        }
        tmp->const_value = retMultipleConstValue;
        // printf("\n");
    }
    else
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Constant is not initialized", ctx);
        // errorReporter.addError("Constant is not initialized", SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));
        // TODO("常量未初始化");
    }
    
    if(!curScopes.addVarConstEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate constant/variable name", ctx);
    }
    return nullptr;
}

bool SysYChecker::viewMultipleConstValue(MultipleConstValue &val, const std::vector<int>& arlen_value, int array_length, int& cnt, std::string& error)//按照数组的维度查看多重常量，用0补全未给出的值，并检查多重常量是否超长。参见文档语义约束部分
{
    // if(!val.isArray())
    // {
    //     TODO("常量初始值维度不匹配");
    // }
    // std::vector<std::vector<MultipleConstValue>> dimStack[arlen_value.size()]; // 维度栈
    
    std::vector<MultipleConstValue>& curVec = val.getArray();
    // int cnt = 0;
    for(int i = 0;i<curVec.size();i++)
    {
        if(curVec[i].isArray())
        {
            std::vector<int> new_arlen_value(arlen_value);
            new_arlen_value.erase(new_arlen_value.begin());
            if(new_arlen_value.size() == 0)
            {
                error = "Constant initializer dimension mismatch";
                return false;
                // TODO("常量初始值维度不匹配");
            }
            int new_cnt = 0;
            int new_array_length = array_length/arlen_value[0];
            if(cnt % new_array_length != 0)
            {
                error = "Constant initializer dimension mismatch";
                return false;
                // TODO("常量初始值维度不匹配");
            }
            if(!viewMultipleConstValue(curVec[i], new_arlen_value, new_array_length, new_cnt, error))
            {
                return false;
            }
            cnt+= new_cnt;
        }
        else
        {
            cnt++;
        }
    }
    if(cnt > array_length)
    {
        error = "Constant initializer list is too long";
        return false;
        // TODO("常量初始值列表长度过长");
    }
    if(curDefType == TYPE_INT)
    {
        while(cnt<array_length)
        {
            val.addToArray(MultipleConstValue(0,TYPE_INT));
            cnt++;
        }
    }
    else
    {
        while(cnt<array_length)
        {
            val.addToArray(MultipleConstValue(0.0f,TYPE_FLOAT));
            cnt++;
        }
    }
    std::vector<MultipleConstValue> tmp;
    for(int i=0;i<curVec.size();i++)
    {
        if(curVec[i].isArray())
        {
            const std::vector<MultipleConstValue>& newVec = curVec[i].getArray();
            for(int j=0;j<newVec.size();j++)
            {
                tmp.push_back(newVec[j]);
            }
        }
        else
        {
            tmp.push_back(curVec[i]);
        }
    }
    curVec = tmp;
    return true;
}

antlrcpp::Any SysYChecker::visitConstDefArray(SysYParser::ConstDefArrayContext* ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>(); 
    // Entry *tmp = new Entry;
    tmp->name = ctx->initLVal()->Identifier()->getText();
    tmp->is_func = false;
    tmp->is_array = true;
    tmp->is_const = true;
    tmp->type = curDefType;
    tmp->array_length = 1;
    for(auto* c : ctx->initLVal()->constExp())
    {
        // TODO("计算常量表达式的值");
        visit(c);
        if(retConstValue.type != TYPE_INT)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions must be integers", ctx);
            // errorReporter.addError("Array subscript must be an integer", SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));
            // TODO("数组下标不是整型");
        }
        if(std::get<int>(retConstValue.data) < 0)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions cannot be negative", ctx);
            // errorReporter.addError("Array subscript cannot be negative", SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));
            // TODO("数组下标不能为负数");
        }
        int size = std::get<int>(retConstValue.data);
        tmp->arlen_value.push_back(size);
        tmp->array_length *= size;
    }

    visit(ctx->constInitVal());
    if(!retMultipleConstValue.isArray())
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Array constant initialized with a single value", ctx);
        // errorReporter.addError("Array constant initialized with a single value", SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));
        // TODO("常量初始值不是数组");
    }
    int cnt = 0;

    std::string error;
    if(!viewMultipleConstValue(retMultipleConstValue, tmp->arlen_value, tmp->array_length, cnt, error))
    {
        errorReporter.addError(error, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));
        //报错
    }


    tmp->const_value = retMultipleConstValue;
    if(!curScopes.addVarConstEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate constant/variable name", ctx);
    }
    return nullptr;
}

antlrcpp::Any SysYChecker::visitConstInitValSingle(SysYParser::ConstInitValSingleContext* ctx)
{
    visit(ctx->constExp());
    // if(retConstValue.type > curDefType)
    // {
    //     REPORT_SEMANTIC_ERROR_AND_EXIT("Constant type mismatch", ctx);
    //     // TODO("常量类型不匹配");
    // }
    if(curDefType == TYPE_FLOAT)
    {
        retConstValue.intToFloat();
        retMultipleConstValue = MultipleConstValue(retConstValue);
    }
    else
    {
        retConstValue.floatToInt();
        retMultipleConstValue = MultipleConstValue(retConstValue);
    }
    
    
    // retConstValue.print();
    // retMultipleConstValue.print();
    return nullptr;
}

antlrcpp::Any SysYChecker::visitConstInitValArray(SysYParser::ConstInitValArrayContext* ctx) 
{
    MultipleConstValue ret;

    std::vector<MultipleConstValue> tmp{};

    if(ctx->constInitVal().size() > 0)
    {
        for(auto* c : ctx->constInitVal())
        {
            visit(c);
            
            
            // if(retMultipleConstValue.type != curDefType)
            // {
            //     TODO("常量类型不匹配");
            // }
            tmp.push_back(retMultipleConstValue);
        }
    }

    ret.data = tmp;
    ret.type = curDefType;
    retMultipleConstValue = ret;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitVarDecl(SysYParser::VarDeclContext* ctx) 
{
    curDefType = typeTable[ctx->bType()->getText()];
    for(SysYParser::VarDefContext* c : ctx->varDef())
    {
        visit(c);
    }
    // curScopes.print();
    return nullptr;
}

antlrcpp::Any SysYChecker::visitVarDefSingle(SysYParser::VarDefSingleContext* ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>(); 
    // Entry *tmp = new Entry;
    tmp->name = ctx->Identifier()->getText();
    // std::cout<<tmp->name<<" 2314\n";
    tmp->is_func = false;
    tmp->is_array = false;
    tmp->is_const = false;
    tmp->type = curDefType;
    if(!curScopes.addVarConstEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate constant/variable name", ctx);
    }
    return nullptr;
}




antlrcpp::Any SysYChecker::visitVarDefArray(SysYParser::VarDefArrayContext* ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>(); 
    // Entry *tmp = new Entry;
    tmp->name = ctx->initLVal()->Identifier()->getText();
    tmp->is_func = false;
    tmp->is_array = true;
    tmp->is_const = false;
    tmp->type = curDefType;
    tmp->array_length = 1;
    for(auto* c : ctx->initLVal()->constExp())
    {
        // TODO("计算常量表达式的值");
        visit(c);
        if(retConstValue.type != TYPE_INT)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions must be integers", ctx);
            // TODO("数组下标不是整型");
        }
        if(std::get<int>(retConstValue.data) < 0)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions cannot be negative", ctx);
            // TODO("数组下标不能为负数");
        }
        int size = std::get<int>(retConstValue.data);
        tmp->arlen_value.push_back(size);
        tmp->array_length *= size;
    }


    if(!curScopes.addVarConstEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate constant/variable name", ctx);
    }
    

    return nullptr;
}
antlrcpp::Any SysYChecker::visitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext* ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>(); 
    // Entry *tmp = new Entry;
    tmp->name = ctx->Identifier()->getText();
    // std::cout<<tmp->name<<" 2314\n";
    tmp->is_func = false;
    tmp->is_array = false;
    tmp->is_const = false;
    tmp->type = curDefType;
    if(ctx->initVal() == nullptr)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Expected a initializer", ctx);
        // TODO("变量未初始化");
    }
    if(inGlobalScope())
    {
        //处在全局变量声明中

        inGlobalVarDecl++;
        visit(ctx->initVal());
        inGlobalVarDecl--;
    }
    else
    {
        visit(ctx->initVal());
    }
    
    if(retMultipleType.isArray())
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Non-array variable initialized with initializer list", ctx);
        // TODO("变量初始值不是单个值");
    }
    if(!curScopes.addVarConstEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate constant/variable name", ctx);
    }
    return nullptr;
}

bool SysYChecker::viewMultipleTypes(MuiltipleType &val, const std::vector<int>& arlen_value, int array_length, int& cnt, std::string& error)
{
    std::vector<MuiltipleType>& curVec = val.getArray();
    // int cnt = 0;
    for(int i = 0;i<curVec.size();i++)
    {
        if(curVec[i].isArray())
        {
            std::vector<int> new_arlen_value(arlen_value);
            new_arlen_value.erase(new_arlen_value.begin());
            if(new_arlen_value.size() == 0)
            {
                error = "Variable initializer dimension mismatch";
                return false;
                // TODO("变量初始值维度不匹配");
            }
            int new_cnt = 0;
            int new_array_length = array_length/arlen_value[0];
            if(cnt % new_array_length != 0)
            {
                error = "Variable initializer dimension mismatch";
                return false;
                // TODO("变量初始值维度不匹配");
            }
            if(!viewMultipleTypes(curVec[i], new_arlen_value, new_array_length, new_cnt, error))
            {
                return false;
            }
            cnt+= new_cnt;
        }
        else
        {
            cnt++;
        }
    }
    if(cnt > array_length)
    {
        error = "Variable initializer list is too long";
        return false;
        // TODO("变量初始值列表长度过长");
    }
    cnt = array_length;
    return true;
}

antlrcpp::Any SysYChecker::visitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext* ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>(); 
    // Entry *tmp = new Entry;
    tmp->name = ctx->initLVal()->Identifier()->getText();
    tmp->is_func = false;
    tmp->is_array = true;
    tmp->is_const = false;
    tmp->type = curDefType;
    tmp->array_length = 1;
    for(auto* c : ctx->initLVal()->constExp())
    {
        // TODO("计算常量表达式的值");
        visit(c);
        if(retConstValue.type != TYPE_INT)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions must be integers", ctx);
            // TODO("数组下标不是整型");
        }
        if(std::get<int>(retConstValue.data) < 0)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions cannot be negative", ctx);
            // TODO("数组下标不能为负数");
        }
        int size = std::get<int>(retConstValue.data);
        tmp->arlen_value.push_back(size);
        tmp->array_length *= size;
    }
    if(ctx->initVal() == nullptr)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Expected a initializer", ctx);
        // TODO("变量未初始化");
    }
    if(inGlobalScope())
    {
        //处在全局变量声明中

        inGlobalVarDecl++;
        visit(ctx->initVal());
        inGlobalVarDecl--;
    }
    else
    {
        visit(ctx->initVal());
    }
    if(!retMultipleType.isArray())
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Array variable initialized with a single value",ctx);
        // TODO("变量初始值不是数组");
    }
    int cnt = 0;
    std::string error;
    if(!viewMultipleTypes(retMultipleType, tmp->arlen_value, tmp->array_length, cnt, error))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT(error, ctx);
    }
    
    if(!curScopes.addVarConstEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate constant/variable name", ctx);
    }
    
    return nullptr;
}

antlrcpp::Any SysYChecker::visitInitValSingle(SysYParser::InitValSingleContext* ctx) 
{
    if(inGlobalVarDecl)
    {
        //处在全局变量声明中，初值表达式必须是常量表达式

        inConstExp++;
        visit(ctx->exp());
        inConstExp--;
    }
    else
    {
        visit(ctx->exp());
    }
    // if(retType > curDefType)
    // {
    //     REPORT_SEMANTIC_ERROR_AND_EXIT("Variable initializer type mismatch",ctx);
    //     // TODO("初值类型与变量类型不匹配");
    // }
    retMultipleType = MuiltipleType(retType);
    return nullptr;
}

antlrcpp::Any SysYChecker::visitInitValArray(SysYParser::InitValArrayContext* ctx) 
{
    MuiltipleType ret;
    std::vector<MuiltipleType> tmp{};
    if(ctx->initVal().size() > 0)
    {
        for(auto* c : ctx->initVal())
        {
            visit(c);
            tmp.push_back(retMultipleType);
        }
    }
    ret = MuiltipleType(tmp);
    retMultipleType = ret;
    return nullptr;
}