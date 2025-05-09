
// Generated from SysY.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "SysYParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by SysYParser.
 */
class  SysYListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(SysYParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(SysYParser::ProgramContext *ctx) = 0;

  virtual void enterCompUnit(SysYParser::CompUnitContext *ctx) = 0;
  virtual void exitCompUnit(SysYParser::CompUnitContext *ctx) = 0;

  virtual void enterDecl(SysYParser::DeclContext *ctx) = 0;
  virtual void exitDecl(SysYParser::DeclContext *ctx) = 0;

  virtual void enterConstDecl(SysYParser::ConstDeclContext *ctx) = 0;
  virtual void exitConstDecl(SysYParser::ConstDeclContext *ctx) = 0;

  virtual void enterBType(SysYParser::BTypeContext *ctx) = 0;
  virtual void exitBType(SysYParser::BTypeContext *ctx) = 0;

  virtual void enterConstDefSingle(SysYParser::ConstDefSingleContext *ctx) = 0;
  virtual void exitConstDefSingle(SysYParser::ConstDefSingleContext *ctx) = 0;

  virtual void enterConstDefArray(SysYParser::ConstDefArrayContext *ctx) = 0;
  virtual void exitConstDefArray(SysYParser::ConstDefArrayContext *ctx) = 0;

  virtual void enterConstInitValSingle(SysYParser::ConstInitValSingleContext *ctx) = 0;
  virtual void exitConstInitValSingle(SysYParser::ConstInitValSingleContext *ctx) = 0;

  virtual void enterConstInitValArray(SysYParser::ConstInitValArrayContext *ctx) = 0;
  virtual void exitConstInitValArray(SysYParser::ConstInitValArrayContext *ctx) = 0;

  virtual void enterVarDecl(SysYParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(SysYParser::VarDeclContext *ctx) = 0;

  virtual void enterVarDefSingle(SysYParser::VarDefSingleContext *ctx) = 0;
  virtual void exitVarDefSingle(SysYParser::VarDefSingleContext *ctx) = 0;

  virtual void enterVarDefArray(SysYParser::VarDefArrayContext *ctx) = 0;
  virtual void exitVarDefArray(SysYParser::VarDefArrayContext *ctx) = 0;

  virtual void enterVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext *ctx) = 0;
  virtual void exitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext *ctx) = 0;

  virtual void enterVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext *ctx) = 0;
  virtual void exitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext *ctx) = 0;

  virtual void enterInitLVal(SysYParser::InitLValContext *ctx) = 0;
  virtual void exitInitLVal(SysYParser::InitLValContext *ctx) = 0;

  virtual void enterInitValSingle(SysYParser::InitValSingleContext *ctx) = 0;
  virtual void exitInitValSingle(SysYParser::InitValSingleContext *ctx) = 0;

  virtual void enterInitValArray(SysYParser::InitValArrayContext *ctx) = 0;
  virtual void exitInitValArray(SysYParser::InitValArrayContext *ctx) = 0;

  virtual void enterFuncDef(SysYParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(SysYParser::FuncDefContext *ctx) = 0;

  virtual void enterFuncType(SysYParser::FuncTypeContext *ctx) = 0;
  virtual void exitFuncType(SysYParser::FuncTypeContext *ctx) = 0;

  virtual void enterFuncFParams(SysYParser::FuncFParamsContext *ctx) = 0;
  virtual void exitFuncFParams(SysYParser::FuncFParamsContext *ctx) = 0;

  virtual void enterFuncFParamSingle(SysYParser::FuncFParamSingleContext *ctx) = 0;
  virtual void exitFuncFParamSingle(SysYParser::FuncFParamSingleContext *ctx) = 0;

  virtual void enterFuncFParamArray(SysYParser::FuncFParamArrayContext *ctx) = 0;
  virtual void exitFuncFParamArray(SysYParser::FuncFParamArrayContext *ctx) = 0;

  virtual void enterBlock(SysYParser::BlockContext *ctx) = 0;
  virtual void exitBlock(SysYParser::BlockContext *ctx) = 0;

  virtual void enterBlockItem(SysYParser::BlockItemContext *ctx) = 0;
  virtual void exitBlockItem(SysYParser::BlockItemContext *ctx) = 0;

  virtual void enterStmtAssign(SysYParser::StmtAssignContext *ctx) = 0;
  virtual void exitStmtAssign(SysYParser::StmtAssignContext *ctx) = 0;

  virtual void enterStmtExp(SysYParser::StmtExpContext *ctx) = 0;
  virtual void exitStmtExp(SysYParser::StmtExpContext *ctx) = 0;

  virtual void enterStmtBlock(SysYParser::StmtBlockContext *ctx) = 0;
  virtual void exitStmtBlock(SysYParser::StmtBlockContext *ctx) = 0;

  virtual void enterStmtCond(SysYParser::StmtCondContext *ctx) = 0;
  virtual void exitStmtCond(SysYParser::StmtCondContext *ctx) = 0;

  virtual void enterStmtWhile(SysYParser::StmtWhileContext *ctx) = 0;
  virtual void exitStmtWhile(SysYParser::StmtWhileContext *ctx) = 0;

  virtual void enterStmtBreak(SysYParser::StmtBreakContext *ctx) = 0;
  virtual void exitStmtBreak(SysYParser::StmtBreakContext *ctx) = 0;

  virtual void enterStmtContinue(SysYParser::StmtContinueContext *ctx) = 0;
  virtual void exitStmtContinue(SysYParser::StmtContinueContext *ctx) = 0;

  virtual void enterStmtReturn(SysYParser::StmtReturnContext *ctx) = 0;
  virtual void exitStmtReturn(SysYParser::StmtReturnContext *ctx) = 0;

  virtual void enterExp(SysYParser::ExpContext *ctx) = 0;
  virtual void exitExp(SysYParser::ExpContext *ctx) = 0;

  virtual void enterCond(SysYParser::CondContext *ctx) = 0;
  virtual void exitCond(SysYParser::CondContext *ctx) = 0;

  virtual void enterLValSingle(SysYParser::LValSingleContext *ctx) = 0;
  virtual void exitLValSingle(SysYParser::LValSingleContext *ctx) = 0;

  virtual void enterLValArray(SysYParser::LValArrayContext *ctx) = 0;
  virtual void exitLValArray(SysYParser::LValArrayContext *ctx) = 0;

  virtual void enterPrimaryExpParen(SysYParser::PrimaryExpParenContext *ctx) = 0;
  virtual void exitPrimaryExpParen(SysYParser::PrimaryExpParenContext *ctx) = 0;

  virtual void enterPrimaryExpLVal(SysYParser::PrimaryExpLValContext *ctx) = 0;
  virtual void exitPrimaryExpLVal(SysYParser::PrimaryExpLValContext *ctx) = 0;

  virtual void enterPrimaryExpNumber(SysYParser::PrimaryExpNumberContext *ctx) = 0;
  virtual void exitPrimaryExpNumber(SysYParser::PrimaryExpNumberContext *ctx) = 0;

  virtual void enterNumber(SysYParser::NumberContext *ctx) = 0;
  virtual void exitNumber(SysYParser::NumberContext *ctx) = 0;

  virtual void enterUnaryExpPrimaryExp(SysYParser::UnaryExpPrimaryExpContext *ctx) = 0;
  virtual void exitUnaryExpPrimaryExp(SysYParser::UnaryExpPrimaryExpContext *ctx) = 0;

  virtual void enterUnaryExpFuncR(SysYParser::UnaryExpFuncRContext *ctx) = 0;
  virtual void exitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext *ctx) = 0;

  virtual void enterUnaryExpUnary(SysYParser::UnaryExpUnaryContext *ctx) = 0;
  virtual void exitUnaryExpUnary(SysYParser::UnaryExpUnaryContext *ctx) = 0;

  virtual void enterUnaryOp(SysYParser::UnaryOpContext *ctx) = 0;
  virtual void exitUnaryOp(SysYParser::UnaryOpContext *ctx) = 0;

  virtual void enterFuncRParams(SysYParser::FuncRParamsContext *ctx) = 0;
  virtual void exitFuncRParams(SysYParser::FuncRParamsContext *ctx) = 0;

  virtual void enterFuncRParam(SysYParser::FuncRParamContext *ctx) = 0;
  virtual void exitFuncRParam(SysYParser::FuncRParamContext *ctx) = 0;

  virtual void enterMulExp(SysYParser::MulExpContext *ctx) = 0;
  virtual void exitMulExp(SysYParser::MulExpContext *ctx) = 0;

  virtual void enterAddExp(SysYParser::AddExpContext *ctx) = 0;
  virtual void exitAddExp(SysYParser::AddExpContext *ctx) = 0;

  virtual void enterRelExp(SysYParser::RelExpContext *ctx) = 0;
  virtual void exitRelExp(SysYParser::RelExpContext *ctx) = 0;

  virtual void enterEqExp(SysYParser::EqExpContext *ctx) = 0;
  virtual void exitEqExp(SysYParser::EqExpContext *ctx) = 0;

  virtual void enterLAndExp(SysYParser::LAndExpContext *ctx) = 0;
  virtual void exitLAndExp(SysYParser::LAndExpContext *ctx) = 0;

  virtual void enterLOrExp(SysYParser::LOrExpContext *ctx) = 0;
  virtual void exitLOrExp(SysYParser::LOrExpContext *ctx) = 0;

  virtual void enterConstExp(SysYParser::ConstExpContext *ctx) = 0;
  virtual void exitConstExp(SysYParser::ConstExpContext *ctx) = 0;

  virtual void enterIntDecConst(SysYParser::IntDecConstContext *ctx) = 0;
  virtual void exitIntDecConst(SysYParser::IntDecConstContext *ctx) = 0;

  virtual void enterIntOctConst(SysYParser::IntOctConstContext *ctx) = 0;
  virtual void exitIntOctConst(SysYParser::IntOctConstContext *ctx) = 0;

  virtual void enterIntHexConst(SysYParser::IntHexConstContext *ctx) = 0;
  virtual void exitIntHexConst(SysYParser::IntHexConstContext *ctx) = 0;

  virtual void enterFloatConst(SysYParser::FloatConstContext *ctx) = 0;
  virtual void exitFloatConst(SysYParser::FloatConstContext *ctx) = 0;


};

