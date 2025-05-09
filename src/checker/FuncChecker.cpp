#include<antlr4-runtime.h>
#include "checker/Checker.h"


#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)
#define CURRENT_LINE(c) (c->getStart()->getLine())
#define CURRENT_COLUMN(c) (c->getStart()->getCharPositionInLine()+1) 
#define REPORT_SEMANTIC_ERROR_AND_RETURN(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));return nullptr;}while(0)
#define REPORT_SEMANTIC_ERROR_AND_EXIT(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx)); printErrors(); std::exit(0);}while(0)


antlrcpp::Any SysYChecker::visitFuncDef(SysYParser::FuncDefContext *ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>();
    // Entry *tmp = new Entry;
    tmp->name = ctx->Identifier()->getText();
    tmp->is_array = false;
    tmp->is_func = true;
    tmp->is_const = false;
    
    tmp->type = typeTable[ctx->funcType()->getText()];
    curFuncType = tmp->type;
    
    std::vector<Entry> funcParams;
    if(ctx->funcFParams() != nullptr)
    {
        for(auto &param : ctx->funcFParams()->funcFParam())
        {
            visit(param);
            funcParams.push_back(lastFuncFParam);
        }
    }
    tmp->func_params = funcParams;
    if(!curScopes.addFuncEntry(*tmp))
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate function name", ctx);
    }
    curScopes.enter();
    for(auto &e : funcParams)
    {
        if(!curScopes.addVarConstEntry(e))
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Duplicate parameter name", ctx);
        }
    }
    visit(ctx->block());
    curScopes.exit();
    // std::cout<<"curScopes exit @"<<CURRENT_LINE(ctx)<<":"<<CURRENT_COLUMN(ctx)<<std::endl;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitFuncFParamSingle(SysYParser::FuncFParamSingleContext *ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>();
    // Entry *tmp = new Entry;
    tmp->name = ctx->Identifier()->getText();
    tmp->is_array = false;
    tmp->is_func = false;
    tmp->is_const = false;
    tmp->type = typeTable[ctx->bType()->getText()];
    lastFuncFParam = *tmp;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitFuncFParamArray(SysYParser::FuncFParamArrayContext *ctx) 
{
    std::unique_ptr<Entry> tmp = std::make_unique<Entry>();
    // Entry *tmp = new Entry;
    tmp->name = ctx->Identifier()->getText();
    tmp->is_array = true;
    tmp->is_func = false;
    tmp->is_const = false;
    tmp->type = typeTable[ctx->bType()->getText()];
    std::vector<int> arlen_value;
    arlen_value.push_back(0x7fffffff);//根据文档，第一维长度省去，也就是说，第一维尺寸不受限，直接用int最大值
    if(!(ctx->exp().empty()))
    {
        for(auto &e : ctx->exp())
        {
            inConstExp++;
            visit(e);
            inConstExp--;
            if(retConstValue.type != TYPE::TYPE_INT)
            {
                REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions must be integers", ctx);
            }
            else if(retConstValue.getInt() < 0)
            {
                REPORT_SEMANTIC_ERROR_AND_EXIT("Array dimensions cannot be negative", ctx);
            }
            arlen_value.push_back(retConstValue.getInt());
        }
    }
    
    tmp->arlen_value = arlen_value;
    tmp->array_length = 0x7fffffff;//根据文档，第一维长度省去，也就是说，数组尺寸不受限，直接用int最大值
    lastFuncFParam = *tmp;
    return nullptr;
}


bool SysYChecker::checkFuncRParamArrayExp(SysYParser::ExpContext *ctx, TYPE type, const std::vector<int>& arlen_value)
{
    if(ctx == nullptr)
    {
        return false;
    }
    if(!(ctx->addExp()->right.empty()))
    {
        return false;
    }
    if(! (ctx->addExp()->mulExp()[0]->right.empty()) )
    {
        return false;
    }
    SysYParser::UnaryExpContext *unaryExp = ctx->addExp()->mulExp()[0]->unaryExp()[0];
    SysYParser::UnaryExpPrimaryExpContext *unaryExpPrimaryExp = dynamic_cast<SysYParser::UnaryExpPrimaryExpContext*>(unaryExp);
    if(unaryExpPrimaryExp == nullptr)
    {
        return false;
    }
    SysYParser::PrimaryExpContext *primaryExp = unaryExpPrimaryExp->primaryExp();
    SysYParser::PrimaryExpLValContext *primaryExpLVal = dynamic_cast<SysYParser::PrimaryExpLValContext*>(primaryExp);
    SysYParser::PrimaryExpParenContext *primaryExpParen = dynamic_cast<SysYParser::PrimaryExpParenContext*>(primaryExp);
    if(primaryExpLVal == nullptr && primaryExpParen == nullptr)
    {
        return false;
    }
    else if(primaryExpLVal != nullptr)
    {
        SysYParser::LValContext *lVal = primaryExpLVal->lVal();
        SysYParser::LValSingleContext *lValSingle = dynamic_cast<SysYParser::LValSingleContext*>(lVal);
        SysYParser::LValArrayContext *lValArray = dynamic_cast<SysYParser::LValArrayContext*>(lVal);
        if(lValSingle != nullptr)
        {
            std::string varName = lValSingle->Identifier()->getText();
            auto entry = curScopes.lookupVarConst(varName);
            if(entry == nullptr)
            {
                REPORT_SEMANTIC_ERROR_AND_EXIT("Undefined symbol used as l-value", ctx);
            }
            if(entry->type!=type)
            {
                return false;
            }
            if(!entry->is_array)
            {
                // REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                return false;
            }
            if(entry->arlen_value.size() != arlen_value.size())
            {
                // REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                return false;
            }
            for(int i=1;i<entry->arlen_value.size();i++)
            {
                if(entry->arlen_value[i] != arlen_value[i])
                {
                    // REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                    return false;
                }
            }
            return true;
        }
        else
        {
            std::string varName = lValArray->Identifier()->getText();
            auto entry = curScopes.lookupVarConst(varName);
            if(entry == nullptr)
            {
                REPORT_SEMANTIC_ERROR_AND_EXIT("Undefined symbol used as l-value", ctx);
            }
            if(entry->type!=type)
            {
                return false;
            }
            if(!entry->is_array)
            {
                return false;
            }
            if(lValArray->exp().size() > entry->arlen_value.size())
            {
                REPORT_SEMANTIC_ERROR_AND_EXIT("Incorrect number of array subscripts", ctx);
            }
            // SysYChecker tempChecker;//临时checker，需要当前checker的符号表信息
            for(auto *e : lValArray->exp())
            {
                visit(e);
                // tempChecker.visit(e);
                // TYPE tmp = tempChecker.retType;
                TYPE tmp = retType;
                if(tmp != TYPE::TYPE_INT)
                {
                    REPORT_SEMANTIC_ERROR_AND_EXIT("Array subscript must be an integer", ctx);
                }
                
            }
            std::vector<int> sliceArlenValue(entry->arlen_value.begin()+lValArray->exp().size(), entry->arlen_value.end());//多维数组切出来的传递给函数的部分的arlen_value
            if(sliceArlenValue.size() != arlen_value.size())
            {
                // REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                return false;
            }
            for(int i=1;i<sliceArlenValue.size();i++)
            {
                if(sliceArlenValue[i] != arlen_value[i])
                {
                    // REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                    return false;
                }
            }
            return true;
        }
    }
    else if(primaryExpParen != nullptr)
    {
        return checkFuncRParamArrayExp(primaryExpParen->exp(), type, arlen_value);
    }
    return false;
}

antlrcpp::Any SysYChecker::visitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext *ctx) 
{
    if(inConstExp)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Function call in constant expression", ctx);
    }
    std::string funcName = ctx->Identifier()->getText();
    auto funcEntry = curScopes.lookupFunc(funcName);
    if(funcEntry == nullptr)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Function not defined", ctx);
    }
    
    std::vector<Entry> funcParams = funcEntry->func_params;

    if(ctx->funcRParams() != nullptr)
    {
        //putf是可变参数函数，其他函数参数个数固定
        if(funcName != "putf" &&funcParams.size() != ctx->funcRParams()->funcRParam().size())
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Number of arguments mismatch", ctx);
        }
        //检查除了putf以外的函数的参数
        if(funcName != "putf")
        {
            int i = 0;
            for(auto &param : ctx->funcRParams()->funcRParam())
            {
                
                if(funcParams[i].is_array)
                {
                    if(param->exp() == nullptr)
                    {
                        REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                    }
                    if(!checkFuncRParamArrayExp(param->exp(), funcParams[i].type, funcParams[i].arlen_value))
                    {
                        REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid array argument: type or dimensions mismatch", ctx);
                    }

                    
                }
                else
                {
                    if(param->exp() == nullptr)//不能是字符串字面量
                    {
                        REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid argument: type mismatch", ctx);
                    }
                    visit(param->exp());
                    //无需检查类型是否匹配，有隐式类型转换
                    // if(retType != funcParams[i].type)
                    // {
                    //     REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid argument: type mismatch", ctx);
                    // }
                }
                i++;
            }
        }
        else
        {
            int i=0;
            for(auto &param : ctx->funcRParams()->funcRParam())
            {
                if(param->exp() == nullptr)//参数是字符串字面量
                {
                    if(i==0)
                    {
                        continue;
                    }
                    REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid argument: type mismatch", ctx);
                }
                visit(param->exp());
                if(retType != TYPE::TYPE_INT && retType != TYPE::TYPE_FLOAT)
                {
                    REPORT_SEMANTIC_ERROR_AND_EXIT("Invalid argument: type mismatch", ctx);
                }
                i++;
            }
        }
    }
    else
    {
        if(funcParams.size() != 0)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Number of arguments mismatch", ctx);
        }
    }

    retType = funcEntry->type;

    
    return nullptr;
}