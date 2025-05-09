#include<antlr4-runtime.h>
#include "checker/Checker.h"


#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)
#define CURRENT_LINE(c) (c->getStart()->getLine())
#define CURRENT_COLUMN(c) (c->getStart()->getCharPositionInLine()+1) 
#define REPORT_SEMANTIC_ERROR_AND_RETURN(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));return nullptr;}while(0)
#define REPORT_SEMANTIC_ERROR_AND_EXIT(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx)); printErrors(); std::exit(0);}while(0)


antlrcpp::Any SysYChecker::visitExp(SysYParser::ExpContext* ctx)
{
    // printf("visitExp\n");
    inExp++;
    visit(ctx->addExp());
    inExp--;
    return nullptr;
}



antlrcpp::Any SysYChecker::visitAddExp(SysYParser::AddExpContext* ctx)
{
    // printf("visitAddExp\n");
    if(inConstExp)
    {
        TYPE ret_t{};
        ConstValue ret(0, TYPE::TYPE_INT);
        
        visit( ctx->left );
        if(retType > ret_t)
        {
            ret_t = retType;
        }

        ret = ret + retConstValue;
        for(int i=0;i<ctx->op.size();i++)
        {
            visit(ctx->right[i]);
            if(ctx->op[i]->getText() == "+")
            {
                ret = ret + retConstValue;
            }
            else
            {
                ret = ret - retConstValue;
            }

            if(retType>ret_t)
            {
                ret_t = retType;
            }
        }
        retConstValue = ret;
        retType = ret_t;
    }
    else
    {
        TYPE ret_t{};
        for(auto* c : ctx->mulExp())
        {
            visit(c);
            if(retType > ret_t)
            {
                ret_t = retType;
            }
        }
        retType = ret_t;
    }
    // printf("retType: %d\n",retType);
    return nullptr;
}

antlrcpp::Any SysYChecker::visitMulExp(SysYParser::MulExpContext* ctx)
{
    // printf("visitMulExp\n");
    if(inConstExp)
    {
        TYPE ret_t{};
        ConstValue ret(1, TYPE::TYPE_INT);

        visit(ctx->left);
        if(retType > ret_t)
        {
            ret_t = retType;
        }

        ret = ret * retConstValue;
        for(int i=0;i<ctx->op.size();i++)
        {
            visit(ctx->right[i]);
            if(ctx->op[i]->getText() == "*")
            {
                ret = ret * retConstValue;
            }
            else if(ctx->op[i]->getText() == "/")
            {
                ret = ret / retConstValue;
            }
            else
            {
                ret = ret % retConstValue;
            }
            
            if(retType > ret_t)
            {
                ret_t = retType;
            }
        }
        retConstValue = ret;
        retType = ret_t;

    }
    else
    {
        TYPE ret_t{};
        for(auto* c : ctx->unaryExp())
        {
            visit(c);
            if(retType > ret_t)
            {
                ret_t = retType;
            }
        }
        retType = ret_t;

    }
    // printf("retType: %d\n",retType);
    return nullptr;
}

antlrcpp::Any SysYChecker::visitRelExp(SysYParser::RelExpContext* ctx)
{
    // printf("visitRelExp\n");
    if(inConstExp)
    {
        ConstValue ret(0, TYPE::TYPE_INT);
        visit(ctx->left);
        ret = retConstValue;
        // printf("op.size(): %ld\n",ctx->op.size());
        for(int i=0;i<ctx->op.size();i++)
        {
            visit(ctx->right[i]);
            if(ctx->op[i]->getText() == "<")
            {
                ret = ret < retConstValue;
                // printf("<\n");
                // printf(retConstValue.toString().c_str());
                // printf(ret.toString().c_str());
            }
            else if(ctx->op[i]->getText() == ">")
            {
                ret = ret > retConstValue;
            }
            else if(ctx->op[i]->getText() == "<=")
            {
                ret = ret <= retConstValue;
            }
            else if(ctx->op[i]->getText() == ">=")
            {
                ret = ret >= retConstValue;
            }
        }
        retConstValue = ret;
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
    else
    {
        for(auto* c : ctx->addExp())
        {
            visit(c);
        }
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
}

antlrcpp::Any SysYChecker::visitEqExp(SysYParser::EqExpContext* ctx)
{
    // printf("visitEqExp\n");
    if(inConstExp)
    {
        ConstValue ret(0, TYPE::TYPE_INT);
        visit(ctx->left);
        ret = retConstValue;
        for(int i=0;i<ctx->op.size();i++)
        {
            visit(ctx->right[i]);
            if(ctx->op[i]->getText() == "==")
            {
                ret = ret == retConstValue;
            }
            else
            {
                ret = ret != retConstValue;
            }
        }
        retConstValue = ret;
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
    else
    {
        for(auto* c : ctx->relExp())
        {
            visit(c);
        }
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
}
antlrcpp::Any SysYChecker::visitLAndExp(SysYParser::LAndExpContext* ctx)
{
    // printf("visitLAndExp\n");
    if(inConstExp)
    {
        ConstValue ret(0, TYPE::TYPE_INT);
        visit(ctx->left);
        ret = retConstValue;
        for(int i=0;i<ctx->op.size();i++)
        {
            visit(ctx->right[i]);
            if(ctx->op[i]->getText() == "&&")
            {
                ret = ret && retConstValue;
            }
        }
        retConstValue = ret;
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
    else
    {
        for(auto* c : ctx->eqExp())
        {
            visit(c);
        }
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
}
antlrcpp::Any SysYChecker::visitLOrExp(SysYParser::LOrExpContext* ctx)
{
    // printf("visitLOrExp\n");
    if(inConstExp)
    {
        ConstValue ret(0, TYPE::TYPE_INT);
        visit(ctx->left);
        ret = retConstValue;
        for(int i=0;i<ctx->op.size();i++)
        {
            visit(ctx->right[i]);
            if(ctx->op[i]->getText() == "||")
            {
                ret = ret || retConstValue;
            }
        }
        retConstValue = ret;
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
    else
    {
        for(auto* c : ctx->lAndExp())
        {
            visit(c);
        }
        retType = TYPE::TYPE_INT;
        return nullptr;
    }
}

antlrcpp::Any SysYChecker::visitConstExp(SysYParser::ConstExpContext* ctx)
{
    // printf("visitConstExp\n");
    inConstExp++;
    visit(ctx->addExp());
    inConstExp--;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitUnaryExpUnary(SysYParser::UnaryExpUnaryContext* ctx)
{
    if(ctx->unaryOp()->getText() == "+")
    {
        if(inConstExp)
        {
            visit(ctx->unaryExp());
        }
        else
        {
            visit(ctx->unaryExp());
        }

    }
    else if(ctx->unaryOp()->getText() == "-")
    {
        if(inConstExp)
        {
            visit(ctx->unaryExp());
            retConstValue = -retConstValue;
        }
        else
        {
            visit(ctx->unaryExp());
        }

    }
    else if(ctx->unaryOp()->getText() == "!")
    {
        if(inExp)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Logical NOT operator cannot be applied to int/float expressions", ctx);
            // TODO("int/float型表达式不支持逻辑非单目运算符");
        }
        visit(ctx->unaryExp());
        retType = TYPE::TYPE_INT;
    }
    else
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Unsupported unary operator", ctx);
        // TODO("不支持的单目表达式");
    }
    return nullptr;
}

antlrcpp::Any SysYChecker::visitLValSingle(SysYParser::LValSingleContext* ctx)
{
    // printf("visitLValSingle\n");
    std::string name = ctx->Identifier()->getText();
    Entry *tmp = curScopes.lookupVarConst(name);
    if(tmp == nullptr)
    {
        // std::cout<<curScopes.varConstTables.size()<<std::endl;
        // curScopes.print();
        // std::cout<<name<<" "<<"not found\n";
        REPORT_SEMANTIC_ERROR_AND_EXIT("Undefined symbol used as l-value", ctx);
        // TODO("符号未定义");
    }
    if(tmp->is_array)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Symbol is not a scalar value", ctx);
        // TODO("符号不是单个值");
    }
    if(inConstExp)
    {
        if(tmp->is_const)
        {
            retConstValue = tmp->const_value.getConstValue();
        }
        else
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Symbol is not a constant", ctx);
            // TODO("符号不是常量");
        }
    }
    retType = tmp->type;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitLValArray(SysYParser::LValArrayContext* ctx)
{
    // printf("visitLValArray\n");
    std::string name = ctx->Identifier()->getText();
    Entry *tmp = curScopes.lookupVarConst(name);
    if(tmp == nullptr)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Undefined symbol used as l-value", ctx);
        // TODO("符号未定义");
    }
    if(!tmp->is_array)
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Symbol is not an array", ctx);
        // TODO("符号不是数组");
    }
    if(ctx->exp().size() != tmp->arlen_value.size())
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Incorrect number of array subscripts", ctx);
        // TODO("数组下标数量不匹配");
    }
    std::vector<int> indexs;
    for(auto* c : ctx->exp())
    {
        visit(c);
        if(retType != TYPE::TYPE_INT)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Array subscript must be an integer", ctx);
            // TODO("数组下标不是整型");
        }
        if(inConstExp)
        {
            indexs.push_back(std::get<int>(retConstValue.data));
        }
    }
    
    if(inConstExp)
    {
        if(tmp->is_const)
        {
            int oneDimIndex = 0;//把数组视作一维时的下标
            int curSizeProduct = 1;//目前逆序遍历过的数组维度的尺寸的乘积，例如有数组array[2][3][4][5]，那么遍历到倒数第三维（正数第二维）时，乘积是4*5=20
            for(auto it = tmp->arlen_value.rbegin();it!=tmp->arlen_value.rend();it++)
            {
                int index = indexs.back();
                indexs.pop_back();
                if(index < 0 || index >= *it)
                {
                    REPORT_SEMANTIC_ERROR_AND_EXIT("Array subscript out of bounds", ctx);
                    // TODO("数组下标越界");
                }
                oneDimIndex += index * curSizeProduct;
                curSizeProduct *= *it;
            }
            MultipleConstValue val= tmp->const_value[oneDimIndex];
            retConstValue = val.getConstValue();
        }
        else
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Symbol is not a constant", ctx);
            // TODO("符号不是常量");
        }
    }
    retType = tmp->type;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitNumber(SysYParser::NumberContext* ctx)
{
    // printf("visitNumber\n");
    if(inConstExp)
    {
        if(ctx->intConst()!=nullptr)
        {
            retConstValue = ConstValue(std::stoi(ctx->getText(),nullptr,0), TYPE::TYPE_INT);
            // retConstValue.print();
        }
        else if(ctx->floatConst()!=nullptr)
        {
            retConstValue = ConstValue(std::stof(ctx->getText()), TYPE::TYPE_FLOAT);
        }
        else
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Unsupported number type", ctx);
            // TODO("不支持的数字类型");
        }
    }
    if(ctx->intConst()!=nullptr)
    {
        retType = TYPE::TYPE_INT;
    }
    else if(ctx->floatConst()!=nullptr)
    {
        retType = TYPE::TYPE_FLOAT;
    }
    else
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Unsupported number type", ctx);
        // TODO("不支持的数字类型");
    }
    // printf("retType: %d\n",retType);
    return nullptr;
}