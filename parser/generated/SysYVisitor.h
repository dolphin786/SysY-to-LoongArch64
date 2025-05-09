
// Generated from SysY.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "SysYParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SysYParser.
 */
class  SysYVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SysYParser.
   */
    virtual antlrcpp::Any visitProgram(SysYParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitCompUnit(SysYParser::CompUnitContext *context) = 0;

    virtual antlrcpp::Any visitDecl(SysYParser::DeclContext *context) = 0;

    virtual antlrcpp::Any visitConstDecl(SysYParser::ConstDeclContext *context) = 0;

    virtual antlrcpp::Any visitBType(SysYParser::BTypeContext *context) = 0;

    virtual antlrcpp::Any visitConstDefSingle(SysYParser::ConstDefSingleContext *context) = 0;

    virtual antlrcpp::Any visitConstDefArray(SysYParser::ConstDefArrayContext *context) = 0;

    virtual antlrcpp::Any visitConstInitValSingle(SysYParser::ConstInitValSingleContext *context) = 0;

    virtual antlrcpp::Any visitConstInitValArray(SysYParser::ConstInitValArrayContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(SysYParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitVarDefSingle(SysYParser::VarDefSingleContext *context) = 0;

    virtual antlrcpp::Any visitVarDefArray(SysYParser::VarDefArrayContext *context) = 0;

    virtual antlrcpp::Any visitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext *context) = 0;

    virtual antlrcpp::Any visitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext *context) = 0;

    virtual antlrcpp::Any visitInitLVal(SysYParser::InitLValContext *context) = 0;

    virtual antlrcpp::Any visitInitValSingle(SysYParser::InitValSingleContext *context) = 0;

    virtual antlrcpp::Any visitInitValArray(SysYParser::InitValArrayContext *context) = 0;

    virtual antlrcpp::Any visitFuncDef(SysYParser::FuncDefContext *context) = 0;

    virtual antlrcpp::Any visitFuncType(SysYParser::FuncTypeContext *context) = 0;

    virtual antlrcpp::Any visitFuncFParams(SysYParser::FuncFParamsContext *context) = 0;

    virtual antlrcpp::Any visitFuncFParamSingle(SysYParser::FuncFParamSingleContext *context) = 0;

    virtual antlrcpp::Any visitFuncFParamArray(SysYParser::FuncFParamArrayContext *context) = 0;

    virtual antlrcpp::Any visitBlock(SysYParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitBlockItem(SysYParser::BlockItemContext *context) = 0;

    virtual antlrcpp::Any visitStmtAssign(SysYParser::StmtAssignContext *context) = 0;

    virtual antlrcpp::Any visitStmtExp(SysYParser::StmtExpContext *context) = 0;

    virtual antlrcpp::Any visitStmtBlock(SysYParser::StmtBlockContext *context) = 0;

    virtual antlrcpp::Any visitStmtCond(SysYParser::StmtCondContext *context) = 0;

    virtual antlrcpp::Any visitStmtWhile(SysYParser::StmtWhileContext *context) = 0;

    virtual antlrcpp::Any visitStmtBreak(SysYParser::StmtBreakContext *context) = 0;

    virtual antlrcpp::Any visitStmtContinue(SysYParser::StmtContinueContext *context) = 0;

    virtual antlrcpp::Any visitStmtReturn(SysYParser::StmtReturnContext *context) = 0;

    virtual antlrcpp::Any visitExp(SysYParser::ExpContext *context) = 0;

    virtual antlrcpp::Any visitCond(SysYParser::CondContext *context) = 0;

    virtual antlrcpp::Any visitLValSingle(SysYParser::LValSingleContext *context) = 0;

    virtual antlrcpp::Any visitLValArray(SysYParser::LValArrayContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpParen(SysYParser::PrimaryExpParenContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpLVal(SysYParser::PrimaryExpLValContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpNumber(SysYParser::PrimaryExpNumberContext *context) = 0;

    virtual antlrcpp::Any visitNumber(SysYParser::NumberContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpPrimaryExp(SysYParser::UnaryExpPrimaryExpContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpUnary(SysYParser::UnaryExpUnaryContext *context) = 0;

    virtual antlrcpp::Any visitUnaryOp(SysYParser::UnaryOpContext *context) = 0;

    virtual antlrcpp::Any visitFuncRParams(SysYParser::FuncRParamsContext *context) = 0;

    virtual antlrcpp::Any visitFuncRParam(SysYParser::FuncRParamContext *context) = 0;

    virtual antlrcpp::Any visitMulExp(SysYParser::MulExpContext *context) = 0;

    virtual antlrcpp::Any visitAddExp(SysYParser::AddExpContext *context) = 0;

    virtual antlrcpp::Any visitRelExp(SysYParser::RelExpContext *context) = 0;

    virtual antlrcpp::Any visitEqExp(SysYParser::EqExpContext *context) = 0;

    virtual antlrcpp::Any visitLAndExp(SysYParser::LAndExpContext *context) = 0;

    virtual antlrcpp::Any visitLOrExp(SysYParser::LOrExpContext *context) = 0;

    virtual antlrcpp::Any visitConstExp(SysYParser::ConstExpContext *context) = 0;

    virtual antlrcpp::Any visitIntDecConst(SysYParser::IntDecConstContext *context) = 0;

    virtual antlrcpp::Any visitIntOctConst(SysYParser::IntOctConstContext *context) = 0;

    virtual antlrcpp::Any visitIntHexConst(SysYParser::IntHexConstContext *context) = 0;

    virtual antlrcpp::Any visitFloatConst(SysYParser::FloatConstContext *context) = 0;


};

