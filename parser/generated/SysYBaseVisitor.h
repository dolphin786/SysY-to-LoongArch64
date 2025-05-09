
// Generated from SysY.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "SysYVisitor.h"


/**
 * This class provides an empty implementation of SysYVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SysYBaseVisitor : public SysYVisitor {
public:

  virtual antlrcpp::Any visitProgram(SysYParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompUnit(SysYParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecl(SysYParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDecl(SysYParser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBType(SysYParser::BTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDefSingle(SysYParser::ConstDefSingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstDefArray(SysYParser::ConstDefArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstInitValSingle(SysYParser::ConstInitValSingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstInitValArray(SysYParser::ConstInitValArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(SysYParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDefSingle(SysYParser::VarDefSingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDefArray(SysYParser::VarDefArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitLVal(SysYParser::InitLValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitValSingle(SysYParser::InitValSingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitValArray(SysYParser::InitValArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncDef(SysYParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncType(SysYParser::FuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncFParams(SysYParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncFParamSingle(SysYParser::FuncFParamSingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncFParamArray(SysYParser::FuncFParamArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(SysYParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockItem(SysYParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtAssign(SysYParser::StmtAssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtExp(SysYParser::StmtExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtBlock(SysYParser::StmtBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtCond(SysYParser::StmtCondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtWhile(SysYParser::StmtWhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtBreak(SysYParser::StmtBreakContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtContinue(SysYParser::StmtContinueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStmtReturn(SysYParser::StmtReturnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExp(SysYParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCond(SysYParser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLValSingle(SysYParser::LValSingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLValArray(SysYParser::LValArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpParen(SysYParser::PrimaryExpParenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpLVal(SysYParser::PrimaryExpLValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpNumber(SysYParser::PrimaryExpNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumber(SysYParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpPrimaryExp(SysYParser::UnaryExpPrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpUnary(SysYParser::UnaryExpUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryOp(SysYParser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncRParams(SysYParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncRParam(SysYParser::FuncRParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulExp(SysYParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddExp(SysYParser::AddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelExp(SysYParser::RelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEqExp(SysYParser::EqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLAndExp(SysYParser::LAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLOrExp(SysYParser::LOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstExp(SysYParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntDecConst(SysYParser::IntDecConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntOctConst(SysYParser::IntOctConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntHexConst(SysYParser::IntHexConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFloatConst(SysYParser::FloatConstContext *ctx) override {
    return visitChildren(ctx);
  }


};

