#include<antlr4-runtime.h>
#include "checker/Checker.h"


#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)
#define CURRENT_LINE(c) (c->getStart()->getLine())
#define CURRENT_COLUMN(c) (c->getStart()->getCharPositionInLine()+1) 
#define REPORT_SEMANTIC_ERROR_AND_RETURN(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));return nullptr;}while(0)
#define REPORT_SEMANTIC_ERROR_AND_EXIT(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx)); printErrors(); std::exit(0);}while(0)

antlrcpp::Any SysYChecker::visitStmtReturn(SysYParser::StmtReturnContext *ctx) 
{
    if(ctx->exp() != nullptr)
    {
        visit(ctx->exp());
        if(curFuncType == TYPE::TYPE_VOID)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Void function cannot return a value", ctx);
        }
        // if(retType != curFuncType)
        // {
        //     REPORT_SEMANTIC_ERROR_AND_EXIT("Function return type mismatch", ctx);
        // }
    }
    else
    {
        if(curFuncType != TYPE::TYPE_VOID)
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Non-void function must return a value", ctx);
        }
    }
    return nullptr;
}

antlrcpp::Any SysYChecker::visitStmtBlock(SysYParser::StmtBlockContext *ctx) 
{
    // std::cout<<"curScopes enter @"<<CURRENT_LINE(ctx)<<":"<<CURRENT_COLUMN(ctx)<<std::endl;
    curScopes.enter();
    // curScopes.print();
    visit(ctx->block());
    curScopes.exit();
    // std::cout<<"curScopes exit @"<<CURRENT_LINE(ctx)<<":"<<CURRENT_COLUMN(ctx)<<std::endl;
    return nullptr;
}

antlrcpp::Any SysYChecker::visitStmtWhile(SysYParser::StmtWhileContext *ctx) 
{
    visit(ctx->cond());
    curScopes.startLoop();
    visit(ctx->stmt());
    curScopes.endLoop();
    return nullptr;
}

antlrcpp::Any SysYChecker::visitStmtBreak(SysYParser::StmtBreakContext *ctx) 
{
    if(!curScopes.inLoop())
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Break statement not inside a loop", ctx);
    }
    return nullptr;
}

antlrcpp::Any SysYChecker::visitStmtContinue(SysYParser::StmtContinueContext *ctx) 
{
    // printf("visitStmtContinue\n");
    if(!curScopes.inLoop())
    {
        REPORT_SEMANTIC_ERROR_AND_EXIT("Continue statement not inside a loop", ctx);
    }
    return nullptr;
}