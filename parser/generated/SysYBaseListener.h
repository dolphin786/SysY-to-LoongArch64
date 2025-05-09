
// Generated from SysY.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "SysYListener.h"


/**
 * This class provides an empty implementation of SysYListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  SysYBaseListener : public SysYListener {
public:

  virtual void enterProgram(SysYParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(SysYParser::ProgramContext * /*ctx*/) override { }

  virtual void enterCompUnit(SysYParser::CompUnitContext * /*ctx*/) override { }
  virtual void exitCompUnit(SysYParser::CompUnitContext * /*ctx*/) override { }

  virtual void enterDecl(SysYParser::DeclContext * /*ctx*/) override { }
  virtual void exitDecl(SysYParser::DeclContext * /*ctx*/) override { }

  virtual void enterConstDecl(SysYParser::ConstDeclContext * /*ctx*/) override { }
  virtual void exitConstDecl(SysYParser::ConstDeclContext * /*ctx*/) override { }

  virtual void enterBType(SysYParser::BTypeContext * /*ctx*/) override { }
  virtual void exitBType(SysYParser::BTypeContext * /*ctx*/) override { }

  virtual void enterConstDefSingle(SysYParser::ConstDefSingleContext * /*ctx*/) override { }
  virtual void exitConstDefSingle(SysYParser::ConstDefSingleContext * /*ctx*/) override { }

  virtual void enterConstDefArray(SysYParser::ConstDefArrayContext * /*ctx*/) override { }
  virtual void exitConstDefArray(SysYParser::ConstDefArrayContext * /*ctx*/) override { }

  virtual void enterConstInitValSingle(SysYParser::ConstInitValSingleContext * /*ctx*/) override { }
  virtual void exitConstInitValSingle(SysYParser::ConstInitValSingleContext * /*ctx*/) override { }

  virtual void enterConstInitValArray(SysYParser::ConstInitValArrayContext * /*ctx*/) override { }
  virtual void exitConstInitValArray(SysYParser::ConstInitValArrayContext * /*ctx*/) override { }

  virtual void enterVarDecl(SysYParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(SysYParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterVarDefSingle(SysYParser::VarDefSingleContext * /*ctx*/) override { }
  virtual void exitVarDefSingle(SysYParser::VarDefSingleContext * /*ctx*/) override { }

  virtual void enterVarDefArray(SysYParser::VarDefArrayContext * /*ctx*/) override { }
  virtual void exitVarDefArray(SysYParser::VarDefArrayContext * /*ctx*/) override { }

  virtual void enterVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext * /*ctx*/) override { }
  virtual void exitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext * /*ctx*/) override { }

  virtual void enterVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext * /*ctx*/) override { }
  virtual void exitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext * /*ctx*/) override { }

  virtual void enterInitLVal(SysYParser::InitLValContext * /*ctx*/) override { }
  virtual void exitInitLVal(SysYParser::InitLValContext * /*ctx*/) override { }

  virtual void enterInitValSingle(SysYParser::InitValSingleContext * /*ctx*/) override { }
  virtual void exitInitValSingle(SysYParser::InitValSingleContext * /*ctx*/) override { }

  virtual void enterInitValArray(SysYParser::InitValArrayContext * /*ctx*/) override { }
  virtual void exitInitValArray(SysYParser::InitValArrayContext * /*ctx*/) override { }

  virtual void enterFuncDef(SysYParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(SysYParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterFuncType(SysYParser::FuncTypeContext * /*ctx*/) override { }
  virtual void exitFuncType(SysYParser::FuncTypeContext * /*ctx*/) override { }

  virtual void enterFuncFParams(SysYParser::FuncFParamsContext * /*ctx*/) override { }
  virtual void exitFuncFParams(SysYParser::FuncFParamsContext * /*ctx*/) override { }

  virtual void enterFuncFParamSingle(SysYParser::FuncFParamSingleContext * /*ctx*/) override { }
  virtual void exitFuncFParamSingle(SysYParser::FuncFParamSingleContext * /*ctx*/) override { }

  virtual void enterFuncFParamArray(SysYParser::FuncFParamArrayContext * /*ctx*/) override { }
  virtual void exitFuncFParamArray(SysYParser::FuncFParamArrayContext * /*ctx*/) override { }

  virtual void enterBlock(SysYParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(SysYParser::BlockContext * /*ctx*/) override { }

  virtual void enterBlockItem(SysYParser::BlockItemContext * /*ctx*/) override { }
  virtual void exitBlockItem(SysYParser::BlockItemContext * /*ctx*/) override { }

  virtual void enterStmtAssign(SysYParser::StmtAssignContext * /*ctx*/) override { }
  virtual void exitStmtAssign(SysYParser::StmtAssignContext * /*ctx*/) override { }

  virtual void enterStmtExp(SysYParser::StmtExpContext * /*ctx*/) override { }
  virtual void exitStmtExp(SysYParser::StmtExpContext * /*ctx*/) override { }

  virtual void enterStmtBlock(SysYParser::StmtBlockContext * /*ctx*/) override { }
  virtual void exitStmtBlock(SysYParser::StmtBlockContext * /*ctx*/) override { }

  virtual void enterStmtCond(SysYParser::StmtCondContext * /*ctx*/) override { }
  virtual void exitStmtCond(SysYParser::StmtCondContext * /*ctx*/) override { }

  virtual void enterStmtWhile(SysYParser::StmtWhileContext * /*ctx*/) override { }
  virtual void exitStmtWhile(SysYParser::StmtWhileContext * /*ctx*/) override { }

  virtual void enterStmtBreak(SysYParser::StmtBreakContext * /*ctx*/) override { }
  virtual void exitStmtBreak(SysYParser::StmtBreakContext * /*ctx*/) override { }

  virtual void enterStmtContinue(SysYParser::StmtContinueContext * /*ctx*/) override { }
  virtual void exitStmtContinue(SysYParser::StmtContinueContext * /*ctx*/) override { }

  virtual void enterStmtReturn(SysYParser::StmtReturnContext * /*ctx*/) override { }
  virtual void exitStmtReturn(SysYParser::StmtReturnContext * /*ctx*/) override { }

  virtual void enterExp(SysYParser::ExpContext * /*ctx*/) override { }
  virtual void exitExp(SysYParser::ExpContext * /*ctx*/) override { }

  virtual void enterCond(SysYParser::CondContext * /*ctx*/) override { }
  virtual void exitCond(SysYParser::CondContext * /*ctx*/) override { }

  virtual void enterLValSingle(SysYParser::LValSingleContext * /*ctx*/) override { }
  virtual void exitLValSingle(SysYParser::LValSingleContext * /*ctx*/) override { }

  virtual void enterLValArray(SysYParser::LValArrayContext * /*ctx*/) override { }
  virtual void exitLValArray(SysYParser::LValArrayContext * /*ctx*/) override { }

  virtual void enterPrimaryExpParen(SysYParser::PrimaryExpParenContext * /*ctx*/) override { }
  virtual void exitPrimaryExpParen(SysYParser::PrimaryExpParenContext * /*ctx*/) override { }

  virtual void enterPrimaryExpLVal(SysYParser::PrimaryExpLValContext * /*ctx*/) override { }
  virtual void exitPrimaryExpLVal(SysYParser::PrimaryExpLValContext * /*ctx*/) override { }

  virtual void enterPrimaryExpNumber(SysYParser::PrimaryExpNumberContext * /*ctx*/) override { }
  virtual void exitPrimaryExpNumber(SysYParser::PrimaryExpNumberContext * /*ctx*/) override { }

  virtual void enterNumber(SysYParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(SysYParser::NumberContext * /*ctx*/) override { }

  virtual void enterUnaryExpPrimaryExp(SysYParser::UnaryExpPrimaryExpContext * /*ctx*/) override { }
  virtual void exitUnaryExpPrimaryExp(SysYParser::UnaryExpPrimaryExpContext * /*ctx*/) override { }

  virtual void enterUnaryExpFuncR(SysYParser::UnaryExpFuncRContext * /*ctx*/) override { }
  virtual void exitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext * /*ctx*/) override { }

  virtual void enterUnaryExpUnary(SysYParser::UnaryExpUnaryContext * /*ctx*/) override { }
  virtual void exitUnaryExpUnary(SysYParser::UnaryExpUnaryContext * /*ctx*/) override { }

  virtual void enterUnaryOp(SysYParser::UnaryOpContext * /*ctx*/) override { }
  virtual void exitUnaryOp(SysYParser::UnaryOpContext * /*ctx*/) override { }

  virtual void enterFuncRParams(SysYParser::FuncRParamsContext * /*ctx*/) override { }
  virtual void exitFuncRParams(SysYParser::FuncRParamsContext * /*ctx*/) override { }

  virtual void enterFuncRParam(SysYParser::FuncRParamContext * /*ctx*/) override { }
  virtual void exitFuncRParam(SysYParser::FuncRParamContext * /*ctx*/) override { }

  virtual void enterMulExp(SysYParser::MulExpContext * /*ctx*/) override { }
  virtual void exitMulExp(SysYParser::MulExpContext * /*ctx*/) override { }

  virtual void enterAddExp(SysYParser::AddExpContext * /*ctx*/) override { }
  virtual void exitAddExp(SysYParser::AddExpContext * /*ctx*/) override { }

  virtual void enterRelExp(SysYParser::RelExpContext * /*ctx*/) override { }
  virtual void exitRelExp(SysYParser::RelExpContext * /*ctx*/) override { }

  virtual void enterEqExp(SysYParser::EqExpContext * /*ctx*/) override { }
  virtual void exitEqExp(SysYParser::EqExpContext * /*ctx*/) override { }

  virtual void enterLAndExp(SysYParser::LAndExpContext * /*ctx*/) override { }
  virtual void exitLAndExp(SysYParser::LAndExpContext * /*ctx*/) override { }

  virtual void enterLOrExp(SysYParser::LOrExpContext * /*ctx*/) override { }
  virtual void exitLOrExp(SysYParser::LOrExpContext * /*ctx*/) override { }

  virtual void enterConstExp(SysYParser::ConstExpContext * /*ctx*/) override { }
  virtual void exitConstExp(SysYParser::ConstExpContext * /*ctx*/) override { }

  virtual void enterIntDecConst(SysYParser::IntDecConstContext * /*ctx*/) override { }
  virtual void exitIntDecConst(SysYParser::IntDecConstContext * /*ctx*/) override { }

  virtual void enterIntOctConst(SysYParser::IntOctConstContext * /*ctx*/) override { }
  virtual void exitIntOctConst(SysYParser::IntOctConstContext * /*ctx*/) override { }

  virtual void enterIntHexConst(SysYParser::IntHexConstContext * /*ctx*/) override { }
  virtual void exitIntHexConst(SysYParser::IntHexConstContext * /*ctx*/) override { }

  virtual void enterFloatConst(SysYParser::FloatConstContext * /*ctx*/) override { }
  virtual void exitFloatConst(SysYParser::FloatConstContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

