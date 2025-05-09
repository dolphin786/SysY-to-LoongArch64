#include<antlr4-runtime.h>
#include "checker/Checker.h"


#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)
#define CURRENT_LINE(c) (c->getStart()->getLine())
#define CURRENT_COLUMN(c) (c->getStart()->getCharPositionInLine()+1) 
#define REPORT_SEMANTIC_ERROR_AND_RETURN(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));return nullptr;}while(0)
#define REPORT_SEMANTIC_ERROR_AND_EXIT(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx)); printErrors(); std::exit(0);}while(0)


void SysYChecker::initTables()
{
    typeTable.clear();
    typeTable["void"] = TYPE::TYPE_VOID;
    typeTable["int"] = TYPE::TYPE_INT;
    typeTable["float"] = TYPE::TYPE_FLOAT;
}

void SysYChecker::addLibFunc()
{
    for(auto e: libFuncTable)
    {
        curScopes.addFuncEntry(e);
    }
}

// TYPE SysYChecker::getResultingType(TYPE x, TYPE y)
// {
//     if(x == TYPE::TYPE_VOID || y == TYPE::TYPE_VOID)
//     {
//         return TYPE::TYPE_ERROR;
//     }
//     else if(x == TYPE::TYPE_ARRAY || y == TYPE::TYPE_ARRAY)
//     {
//         return TYPE::TYPE_ERROR;
//     }
//     else if(x == TYPE::TYPE_FLOAT && y == TYPE::TYPE_FLOAT)
//     {
//         return TYPE::TYPE_FLOAT;
//     }
//     else if(x == TYPE::TYPE_FLOAT && y == TYPE::TYPE_INT)
//     {
//         return TYPE::TYPE_FLOAT;
//     }
//     else if(x == TYPE::TYPE_INT && y == TYPE::TYPE_FLOAT)
//     {
//         return TYPE::TYPE_FLOAT;
//     }
//     else if(x == TYPE::TYPE_INT && y == TYPE::TYPE_INT)
//     {
//         return TYPE::TYPE_INT;
//     }
//     else
//     {
//         return TYPE::TYPE_ERROR;
//     }
// }


antlrcpp::Any SysYChecker::visitProgram(SysYParser::ProgramContext *ctx)
{
    initTables();
    curScopes.enter();
    addLibFunc();
    visit(ctx->compUnit());
    curScopes.exit();
    // std::cout<<"curScopes exit @"<<CURRENT_LINE(ctx)<<":"<<CURRENT_COLUMN(ctx)<<std::endl;
    return nullptr;
}
// antlrcpp::Any SysYChecker::visitBlock(SysYParser::BlockContext *ctx)
// {
//     for(SysYParser::BlockItemContext* c : ctx->blockItem())
//     {
//         visit(c);
//     }
//     return nullptr;
// }
antlrcpp::Any SysYChecker::visitErrorNode(antlr4::tree::ErrorNode *node)
{
    // printf("visitErrorNode\n");
    int line = node->getSymbol()->getLine();
    int column = node->getSymbol()->getCharPositionInLine();
    errorReporter.addError("Unexpected token: " + node->getText(), SysYErrorHandling::ErrorType::SYNTAX_ERROR, line, column);
    // printErrors();
    // std::exit(0);
    return nullptr;
}