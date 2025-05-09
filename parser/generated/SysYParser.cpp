
// Generated from SysY.g4 by ANTLR 4.9.3


#include "SysYListener.h"
#include "SysYVisitor.h"

#include "SysYParser.h"


using namespace antlrcpp;
using namespace antlr4;

SysYParser::SysYParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SysYParser::~SysYParser() {
  delete _interpreter;
}

std::string SysYParser::getGrammarFileName() const {
  return "SysY.g4";
}

const std::vector<std::string>& SysYParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SysYParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

SysYParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::CompUnitContext* SysYParser::ProgramContext::compUnit() {
  return getRuleContext<SysYParser::CompUnitContext>(0);
}


size_t SysYParser::ProgramContext::getRuleIndex() const {
  return SysYParser::RuleProgram;
}

void SysYParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void SysYParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any SysYParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ProgramContext* SysYParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, SysYParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    compUnit();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompUnitContext ------------------------------------------------------------------

SysYParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::CompUnitContext::EOF() {
  return getToken(SysYParser::EOF, 0);
}

std::vector<SysYParser::DeclContext *> SysYParser::CompUnitContext::decl() {
  return getRuleContexts<SysYParser::DeclContext>();
}

SysYParser::DeclContext* SysYParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<SysYParser::DeclContext>(i);
}

std::vector<SysYParser::FuncDefContext *> SysYParser::CompUnitContext::funcDef() {
  return getRuleContexts<SysYParser::FuncDefContext>();
}

SysYParser::FuncDefContext* SysYParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<SysYParser::FuncDefContext>(i);
}


size_t SysYParser::CompUnitContext::getRuleIndex() const {
  return SysYParser::RuleCompUnit;
}

void SysYParser::CompUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompUnit(this);
}

void SysYParser::CompUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompUnit(this);
}


antlrcpp::Any SysYParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::CompUnitContext* SysYParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__0)
      | (1ULL << SysYParser::T__3)
      | (1ULL << SysYParser::T__4)
      | (1ULL << SysYParser::T__12))) != 0)) {
      setState(76);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(74);
        decl();
        break;
      }

      case 2: {
        setState(75);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(80);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(81);
    match(SysYParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

SysYParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ConstDeclContext* SysYParser::DeclContext::constDecl() {
  return getRuleContext<SysYParser::ConstDeclContext>(0);
}

SysYParser::VarDeclContext* SysYParser::DeclContext::varDecl() {
  return getRuleContext<SysYParser::VarDeclContext>(0);
}


size_t SysYParser::DeclContext::getRuleIndex() const {
  return SysYParser::RuleDecl;
}

void SysYParser::DeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecl(this);
}

void SysYParser::DeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecl(this);
}


antlrcpp::Any SysYParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::DeclContext* SysYParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(83);
        constDecl();
        break;
      }

      case SysYParser::T__3:
      case SysYParser::T__4: {
        enterOuterAlt(_localctx, 2);
        setState(84);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

SysYParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BTypeContext* SysYParser::ConstDeclContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::ConstDefContext *> SysYParser::ConstDeclContext::constDef() {
  return getRuleContexts<SysYParser::ConstDefContext>();
}

SysYParser::ConstDefContext* SysYParser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<SysYParser::ConstDefContext>(i);
}


size_t SysYParser::ConstDeclContext::getRuleIndex() const {
  return SysYParser::RuleConstDecl;
}

void SysYParser::ConstDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDecl(this);
}

void SysYParser::ConstDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDecl(this);
}


antlrcpp::Any SysYParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstDeclContext* SysYParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(SysYParser::T__0);
    setState(88);
    bType();
    setState(89);
    constDef();
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(90);
      match(SysYParser::T__1);
      setState(91);
      constDef();
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(97);
    match(SysYParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

SysYParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::BTypeContext::getRuleIndex() const {
  return SysYParser::RuleBType;
}

void SysYParser::BTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBType(this);
}

void SysYParser::BTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBType(this);
}


antlrcpp::Any SysYParser::BTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBType(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BTypeContext* SysYParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYParser::RuleBType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    _la = _input->LA(1);
    if (!(_la == SysYParser::T__3

    || _la == SysYParser::T__4)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

SysYParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::ConstDefContext::getRuleIndex() const {
  return SysYParser::RuleConstDef;
}

void SysYParser::ConstDefContext::copyFrom(ConstDefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ConstDefSingleContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ConstDefSingleContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::ConstInitValContext* SysYParser::ConstDefSingleContext::constInitVal() {
  return getRuleContext<SysYParser::ConstInitValContext>(0);
}

SysYParser::ConstDefSingleContext::ConstDefSingleContext(ConstDefContext *ctx) { copyFrom(ctx); }

void SysYParser::ConstDefSingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDefSingle(this);
}
void SysYParser::ConstDefSingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDefSingle(this);
}

antlrcpp::Any SysYParser::ConstDefSingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstDefSingle(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstDefArrayContext ------------------------------------------------------------------

SysYParser::InitLValContext* SysYParser::ConstDefArrayContext::initLVal() {
  return getRuleContext<SysYParser::InitLValContext>(0);
}

SysYParser::ConstInitValContext* SysYParser::ConstDefArrayContext::constInitVal() {
  return getRuleContext<SysYParser::ConstInitValContext>(0);
}

SysYParser::ConstDefArrayContext::ConstDefArrayContext(ConstDefContext *ctx) { copyFrom(ctx); }

void SysYParser::ConstDefArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDefArray(this);
}
void SysYParser::ConstDefArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDefArray(this);
}

antlrcpp::Any SysYParser::ConstDefArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstDefArray(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::ConstDefContext* SysYParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYParser::RuleConstDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::ConstDefSingleContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(101);
      match(SysYParser::Identifier);
      setState(102);
      match(SysYParser::T__5);
      setState(103);
      constInitVal();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::ConstDefArrayContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(104);
      initLVal();
      setState(105);
      match(SysYParser::T__5);
      setState(106);
      constInitVal();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

SysYParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::ConstInitValContext::getRuleIndex() const {
  return SysYParser::RuleConstInitVal;
}

void SysYParser::ConstInitValContext::copyFrom(ConstInitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ConstInitValSingleContext ------------------------------------------------------------------

SysYParser::ConstExpContext* SysYParser::ConstInitValSingleContext::constExp() {
  return getRuleContext<SysYParser::ConstExpContext>(0);
}

SysYParser::ConstInitValSingleContext::ConstInitValSingleContext(ConstInitValContext *ctx) { copyFrom(ctx); }

void SysYParser::ConstInitValSingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstInitValSingle(this);
}
void SysYParser::ConstInitValSingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstInitValSingle(this);
}

antlrcpp::Any SysYParser::ConstInitValSingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstInitValSingle(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstInitValArrayContext ------------------------------------------------------------------

std::vector<SysYParser::ConstInitValContext *> SysYParser::ConstInitValArrayContext::constInitVal() {
  return getRuleContexts<SysYParser::ConstInitValContext>();
}

SysYParser::ConstInitValContext* SysYParser::ConstInitValArrayContext::constInitVal(size_t i) {
  return getRuleContext<SysYParser::ConstInitValContext>(i);
}

SysYParser::ConstInitValArrayContext::ConstInitValArrayContext(ConstInitValContext *ctx) { copyFrom(ctx); }

void SysYParser::ConstInitValArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstInitValArray(this);
}
void SysYParser::ConstInitValArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstInitValArray(this);
}

antlrcpp::Any SysYParser::ConstInitValArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstInitValArray(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::ConstInitValContext* SysYParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(123);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Identifier:
      case SysYParser::DecimalConstant:
      case SysYParser::OctalConstant:
      case SysYParser::HexadecimalConstant:
      case SysYParser::FloatingConstant: {
        _localctx = _tracker.createInstance<SysYParser::ConstInitValSingleContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(110);
        constExp();
        break;
      }

      case SysYParser::T__6: {
        _localctx = _tracker.createInstance<SysYParser::ConstInitValArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(111);
        match(SysYParser::T__6);
        setState(120);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SysYParser::T__6)
          | (1ULL << SysYParser::T__10)
          | (1ULL << SysYParser::T__19)
          | (1ULL << SysYParser::T__20)
          | (1ULL << SysYParser::T__21)
          | (1ULL << SysYParser::Identifier)
          | (1ULL << SysYParser::DecimalConstant)
          | (1ULL << SysYParser::OctalConstant)
          | (1ULL << SysYParser::HexadecimalConstant)
          | (1ULL << SysYParser::FloatingConstant))) != 0)) {
          setState(112);
          constInitVal();
          setState(117);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::T__1) {
            setState(113);
            match(SysYParser::T__1);
            setState(114);
            constInitVal();
            setState(119);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(122);
        match(SysYParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

SysYParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BTypeContext* SysYParser::VarDeclContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::VarDefContext *> SysYParser::VarDeclContext::varDef() {
  return getRuleContexts<SysYParser::VarDefContext>();
}

SysYParser::VarDefContext* SysYParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<SysYParser::VarDefContext>(i);
}


size_t SysYParser::VarDeclContext::getRuleIndex() const {
  return SysYParser::RuleVarDecl;
}

void SysYParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void SysYParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


antlrcpp::Any SysYParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::VarDeclContext* SysYParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    bType();
    setState(126);
    varDef();
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(127);
      match(SysYParser::T__1);
      setState(128);
      varDef();
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(134);
    match(SysYParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

SysYParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::VarDefContext::getRuleIndex() const {
  return SysYParser::RuleVarDef;
}

void SysYParser::VarDefContext::copyFrom(VarDefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- VarDefSingleInitValContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::VarDefSingleInitValContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::InitValContext* SysYParser::VarDefSingleInitValContext::initVal() {
  return getRuleContext<SysYParser::InitValContext>(0);
}

SysYParser::VarDefSingleInitValContext::VarDefSingleInitValContext(VarDefContext *ctx) { copyFrom(ctx); }

void SysYParser::VarDefSingleInitValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDefSingleInitVal(this);
}
void SysYParser::VarDefSingleInitValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDefSingleInitVal(this);
}

antlrcpp::Any SysYParser::VarDefSingleInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitVarDefSingleInitVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDefArrayInitValContext ------------------------------------------------------------------

SysYParser::InitLValContext* SysYParser::VarDefArrayInitValContext::initLVal() {
  return getRuleContext<SysYParser::InitLValContext>(0);
}

SysYParser::InitValContext* SysYParser::VarDefArrayInitValContext::initVal() {
  return getRuleContext<SysYParser::InitValContext>(0);
}

SysYParser::VarDefArrayInitValContext::VarDefArrayInitValContext(VarDefContext *ctx) { copyFrom(ctx); }

void SysYParser::VarDefArrayInitValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDefArrayInitVal(this);
}
void SysYParser::VarDefArrayInitValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDefArrayInitVal(this);
}

antlrcpp::Any SysYParser::VarDefArrayInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitVarDefArrayInitVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDefSingleContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::VarDefSingleContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::VarDefSingleContext::VarDefSingleContext(VarDefContext *ctx) { copyFrom(ctx); }

void SysYParser::VarDefSingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDefSingle(this);
}
void SysYParser::VarDefSingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDefSingle(this);
}

antlrcpp::Any SysYParser::VarDefSingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitVarDefSingle(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDefArrayContext ------------------------------------------------------------------

SysYParser::InitLValContext* SysYParser::VarDefArrayContext::initLVal() {
  return getRuleContext<SysYParser::InitLValContext>(0);
}

SysYParser::VarDefArrayContext::VarDefArrayContext(VarDefContext *ctx) { copyFrom(ctx); }

void SysYParser::VarDefArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDefArray(this);
}
void SysYParser::VarDefArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDefArray(this);
}

antlrcpp::Any SysYParser::VarDefArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitVarDefArray(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::VarDefContext* SysYParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 16, SysYParser::RuleVarDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(145);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::VarDefSingleContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(136);
      match(SysYParser::Identifier);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::VarDefArrayContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(137);
      initLVal();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::VarDefSingleInitValContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(138);
      match(SysYParser::Identifier);
      setState(139);
      match(SysYParser::T__5);
      setState(140);
      initVal();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SysYParser::VarDefArrayInitValContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(141);
      initLVal();
      setState(142);
      match(SysYParser::T__5);
      setState(143);
      initVal();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitLValContext ------------------------------------------------------------------

SysYParser::InitLValContext::InitLValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::InitLValContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::InitLValContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::InitLValContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}


size_t SysYParser::InitLValContext::getRuleIndex() const {
  return SysYParser::RuleInitLVal;
}

void SysYParser::InitLValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitLVal(this);
}

void SysYParser::InitLValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitLVal(this);
}


antlrcpp::Any SysYParser::InitLValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitInitLVal(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::InitLValContext* SysYParser::initLVal() {
  InitLValContext *_localctx = _tracker.createInstance<InitLValContext>(_ctx, getState());
  enterRule(_localctx, 18, SysYParser::RuleInitLVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    match(SysYParser::Identifier);
    setState(152); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(148);
      match(SysYParser::T__8);
      setState(149);
      constExp();
      setState(150);
      match(SysYParser::T__9);
      setState(154); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == SysYParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

SysYParser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::InitValContext::getRuleIndex() const {
  return SysYParser::RuleInitVal;
}

void SysYParser::InitValContext::copyFrom(InitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InitValArrayContext ------------------------------------------------------------------

std::vector<SysYParser::InitValContext *> SysYParser::InitValArrayContext::initVal() {
  return getRuleContexts<SysYParser::InitValContext>();
}

SysYParser::InitValContext* SysYParser::InitValArrayContext::initVal(size_t i) {
  return getRuleContext<SysYParser::InitValContext>(i);
}

SysYParser::InitValArrayContext::InitValArrayContext(InitValContext *ctx) { copyFrom(ctx); }

void SysYParser::InitValArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitValArray(this);
}
void SysYParser::InitValArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitValArray(this);
}

antlrcpp::Any SysYParser::InitValArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitInitValArray(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InitValSingleContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::InitValSingleContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::InitValSingleContext::InitValSingleContext(InitValContext *ctx) { copyFrom(ctx); }

void SysYParser::InitValSingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitValSingle(this);
}
void SysYParser::InitValSingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitValSingle(this);
}

antlrcpp::Any SysYParser::InitValSingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitInitValSingle(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::InitValContext* SysYParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 20, SysYParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(169);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Identifier:
      case SysYParser::DecimalConstant:
      case SysYParser::OctalConstant:
      case SysYParser::HexadecimalConstant:
      case SysYParser::FloatingConstant: {
        _localctx = _tracker.createInstance<SysYParser::InitValSingleContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(156);
        exp();
        break;
      }

      case SysYParser::T__6: {
        _localctx = _tracker.createInstance<SysYParser::InitValArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(157);
        match(SysYParser::T__6);
        setState(166);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << SysYParser::T__6)
          | (1ULL << SysYParser::T__10)
          | (1ULL << SysYParser::T__19)
          | (1ULL << SysYParser::T__20)
          | (1ULL << SysYParser::T__21)
          | (1ULL << SysYParser::Identifier)
          | (1ULL << SysYParser::DecimalConstant)
          | (1ULL << SysYParser::OctalConstant)
          | (1ULL << SysYParser::HexadecimalConstant)
          | (1ULL << SysYParser::FloatingConstant))) != 0)) {
          setState(158);
          initVal();
          setState(163);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::T__1) {
            setState(159);
            match(SysYParser::T__1);
            setState(160);
            initVal();
            setState(165);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(168);
        match(SysYParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

SysYParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::FuncTypeContext* SysYParser::FuncDefContext::funcType() {
  return getRuleContext<SysYParser::FuncTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncDefContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::BlockContext* SysYParser::FuncDefContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::FuncFParamsContext* SysYParser::FuncDefContext::funcFParams() {
  return getRuleContext<SysYParser::FuncFParamsContext>(0);
}


size_t SysYParser::FuncDefContext::getRuleIndex() const {
  return SysYParser::RuleFuncDef;
}

void SysYParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void SysYParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


antlrcpp::Any SysYParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncDefContext* SysYParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 22, SysYParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    funcType();
    setState(172);
    match(SysYParser::Identifier);
    setState(173);
    match(SysYParser::T__10);
    setState(175);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::T__3

    || _la == SysYParser::T__4) {
      setState(174);
      funcFParams();
    }
    setState(177);
    match(SysYParser::T__11);
    setState(178);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

SysYParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::FuncTypeContext::getRuleIndex() const {
  return SysYParser::RuleFuncType;
}

void SysYParser::FuncTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncType(this);
}

void SysYParser::FuncTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncType(this);
}


antlrcpp::Any SysYParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncTypeContext* SysYParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 24, SysYParser::RuleFuncType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__3)
      | (1ULL << SysYParser::T__4)
      | (1ULL << SysYParser::T__12))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

SysYParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::FuncFParamContext *> SysYParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<SysYParser::FuncFParamContext>();
}

SysYParser::FuncFParamContext* SysYParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<SysYParser::FuncFParamContext>(i);
}


size_t SysYParser::FuncFParamsContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParams;
}

void SysYParser::FuncFParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParams(this);
}

void SysYParser::FuncFParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParams(this);
}


antlrcpp::Any SysYParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncFParamsContext* SysYParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 26, SysYParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    funcFParam();
    setState(187);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(183);
      match(SysYParser::T__1);
      setState(184);
      funcFParam();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

SysYParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::FuncFParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParam;
}

void SysYParser::FuncFParamContext::copyFrom(FuncFParamContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncFParamArrayContext ------------------------------------------------------------------

SysYParser::BTypeContext* SysYParser::FuncFParamArrayContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncFParamArrayContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

std::vector<SysYParser::ExpContext *> SysYParser::FuncFParamArrayContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::FuncFParamArrayContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}

SysYParser::FuncFParamArrayContext::FuncFParamArrayContext(FuncFParamContext *ctx) { copyFrom(ctx); }

void SysYParser::FuncFParamArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParamArray(this);
}
void SysYParser::FuncFParamArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParamArray(this);
}

antlrcpp::Any SysYParser::FuncFParamArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncFParamArray(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncFParamSingleContext ------------------------------------------------------------------

SysYParser::BTypeContext* SysYParser::FuncFParamSingleContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncFParamSingleContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::FuncFParamSingleContext::FuncFParamSingleContext(FuncFParamContext *ctx) { copyFrom(ctx); }

void SysYParser::FuncFParamSingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncFParamSingle(this);
}
void SysYParser::FuncFParamSingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncFParamSingle(this);
}

antlrcpp::Any SysYParser::FuncFParamSingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncFParamSingle(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::FuncFParamContext* SysYParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 28, SysYParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::FuncFParamSingleContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(190);
      bType();
      setState(191);
      match(SysYParser::Identifier);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::FuncFParamArrayContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(193);
      bType();
      setState(194);
      match(SysYParser::Identifier);
      setState(195);
      match(SysYParser::T__8);
      setState(196);
      match(SysYParser::T__9);
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::T__8) {
        setState(197);
        match(SysYParser::T__8);
        setState(198);
        exp();
        setState(199);
        match(SysYParser::T__9);
        setState(205);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SysYParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::BlockItemContext *> SysYParser::BlockContext::blockItem() {
  return getRuleContexts<SysYParser::BlockItemContext>();
}

SysYParser::BlockItemContext* SysYParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<SysYParser::BlockItemContext>(i);
}


size_t SysYParser::BlockContext::getRuleIndex() const {
  return SysYParser::RuleBlock;
}

void SysYParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void SysYParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


antlrcpp::Any SysYParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BlockContext* SysYParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 30, SysYParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(SysYParser::T__6);
    setState(212);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__0)
      | (1ULL << SysYParser::T__2)
      | (1ULL << SysYParser::T__3)
      | (1ULL << SysYParser::T__4)
      | (1ULL << SysYParser::T__6)
      | (1ULL << SysYParser::T__10)
      | (1ULL << SysYParser::T__13)
      | (1ULL << SysYParser::T__15)
      | (1ULL << SysYParser::T__16)
      | (1ULL << SysYParser::T__17)
      | (1ULL << SysYParser::T__18)
      | (1ULL << SysYParser::T__19)
      | (1ULL << SysYParser::T__20)
      | (1ULL << SysYParser::T__21)
      | (1ULL << SysYParser::Identifier)
      | (1ULL << SysYParser::DecimalConstant)
      | (1ULL << SysYParser::OctalConstant)
      | (1ULL << SysYParser::HexadecimalConstant)
      | (1ULL << SysYParser::FloatingConstant))) != 0)) {
      setState(209);
      blockItem();
      setState(214);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(215);
    match(SysYParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

SysYParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::DeclContext* SysYParser::BlockItemContext::decl() {
  return getRuleContext<SysYParser::DeclContext>(0);
}

SysYParser::StmtContext* SysYParser::BlockItemContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}


size_t SysYParser::BlockItemContext::getRuleIndex() const {
  return SysYParser::RuleBlockItem;
}

void SysYParser::BlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockItem(this);
}

void SysYParser::BlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockItem(this);
}


antlrcpp::Any SysYParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BlockItemContext* SysYParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 32, SysYParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__0:
      case SysYParser::T__3:
      case SysYParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(217);
        decl();
        break;
      }

      case SysYParser::T__2:
      case SysYParser::T__6:
      case SysYParser::T__10:
      case SysYParser::T__13:
      case SysYParser::T__15:
      case SysYParser::T__16:
      case SysYParser::T__17:
      case SysYParser::T__18:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Identifier:
      case SysYParser::DecimalConstant:
      case SysYParser::OctalConstant:
      case SysYParser::HexadecimalConstant:
      case SysYParser::FloatingConstant: {
        enterOuterAlt(_localctx, 2);
        setState(218);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

SysYParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::StmtContext::getRuleIndex() const {
  return SysYParser::RuleStmt;
}

void SysYParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- StmtExpContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::StmtExpContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::StmtExpContext::StmtExpContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtExp(this);
}
void SysYParser::StmtExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtExp(this);
}

antlrcpp::Any SysYParser::StmtExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtBlockContext ------------------------------------------------------------------

SysYParser::BlockContext* SysYParser::StmtBlockContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::StmtBlockContext::StmtBlockContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtBlock(this);
}
void SysYParser::StmtBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtBlock(this);
}

antlrcpp::Any SysYParser::StmtBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtBlock(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtBreakContext ------------------------------------------------------------------

SysYParser::StmtBreakContext::StmtBreakContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtBreakContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtBreak(this);
}
void SysYParser::StmtBreakContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtBreak(this);
}

antlrcpp::Any SysYParser::StmtBreakContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtBreak(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtWhileContext ------------------------------------------------------------------

SysYParser::CondContext* SysYParser::StmtWhileContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

SysYParser::StmtContext* SysYParser::StmtWhileContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}

SysYParser::StmtWhileContext::StmtWhileContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtWhileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtWhile(this);
}
void SysYParser::StmtWhileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtWhile(this);
}

antlrcpp::Any SysYParser::StmtWhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtCondContext ------------------------------------------------------------------

SysYParser::CondContext* SysYParser::StmtCondContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

std::vector<SysYParser::StmtContext *> SysYParser::StmtCondContext::stmt() {
  return getRuleContexts<SysYParser::StmtContext>();
}

SysYParser::StmtContext* SysYParser::StmtCondContext::stmt(size_t i) {
  return getRuleContext<SysYParser::StmtContext>(i);
}

SysYParser::StmtCondContext::StmtCondContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtCondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtCond(this);
}
void SysYParser::StmtCondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtCond(this);
}

antlrcpp::Any SysYParser::StmtCondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtCond(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtContinueContext ------------------------------------------------------------------

SysYParser::StmtContinueContext::StmtContinueContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtContinueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtContinue(this);
}
void SysYParser::StmtContinueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtContinue(this);
}

antlrcpp::Any SysYParser::StmtContinueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtContinue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtReturnContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::StmtReturnContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::StmtReturnContext::StmtReturnContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtReturnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtReturn(this);
}
void SysYParser::StmtReturnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtReturn(this);
}

antlrcpp::Any SysYParser::StmtReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtReturn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtAssignContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::StmtAssignContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::ExpContext* SysYParser::StmtAssignContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::StmtAssignContext::StmtAssignContext(StmtContext *ctx) { copyFrom(ctx); }

void SysYParser::StmtAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtAssign(this);
}
void SysYParser::StmtAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtAssign(this);
}

antlrcpp::Any SysYParser::StmtAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitStmtAssign(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::StmtContext* SysYParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 34, SysYParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(255);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::StmtAssignContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(221);
      lVal();
      setState(222);
      match(SysYParser::T__5);
      setState(223);
      exp();
      setState(224);
      match(SysYParser::T__2);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::StmtExpContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(227);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__10)
        | (1ULL << SysYParser::T__19)
        | (1ULL << SysYParser::T__20)
        | (1ULL << SysYParser::T__21)
        | (1ULL << SysYParser::Identifier)
        | (1ULL << SysYParser::DecimalConstant)
        | (1ULL << SysYParser::OctalConstant)
        | (1ULL << SysYParser::HexadecimalConstant)
        | (1ULL << SysYParser::FloatingConstant))) != 0)) {
        setState(226);
        exp();
      }
      setState(229);
      match(SysYParser::T__2);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::StmtBlockContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(230);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SysYParser::StmtCondContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(231);
      match(SysYParser::T__13);
      setState(232);
      match(SysYParser::T__10);
      setState(233);
      cond();
      setState(234);
      match(SysYParser::T__11);
      setState(235);
      stmt();
      setState(238);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
      case 1: {
        setState(236);
        match(SysYParser::T__14);
        setState(237);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SysYParser::StmtWhileContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(240);
      match(SysYParser::T__15);
      setState(241);
      match(SysYParser::T__10);
      setState(242);
      cond();
      setState(243);
      match(SysYParser::T__11);
      setState(244);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SysYParser::StmtBreakContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(246);
      match(SysYParser::T__16);
      setState(247);
      match(SysYParser::T__2);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SysYParser::StmtContinueContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(248);
      match(SysYParser::T__17);
      setState(249);
      match(SysYParser::T__2);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SysYParser::StmtReturnContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(250);
      match(SysYParser::T__18);
      setState(252);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__10)
        | (1ULL << SysYParser::T__19)
        | (1ULL << SysYParser::T__20)
        | (1ULL << SysYParser::T__21)
        | (1ULL << SysYParser::Identifier)
        | (1ULL << SysYParser::DecimalConstant)
        | (1ULL << SysYParser::OctalConstant)
        | (1ULL << SysYParser::HexadecimalConstant)
        | (1ULL << SysYParser::FloatingConstant))) != 0)) {
        setState(251);
        exp();
      }
      setState(254);
      match(SysYParser::T__2);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

SysYParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::AddExpContext* SysYParser::ExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}


size_t SysYParser::ExpContext::getRuleIndex() const {
  return SysYParser::RuleExp;
}

void SysYParser::ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExp(this);
}

void SysYParser::ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExp(this);
}


antlrcpp::Any SysYParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ExpContext* SysYParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 36, SysYParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(257);
    addExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

SysYParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::LOrExpContext* SysYParser::CondContext::lOrExp() {
  return getRuleContext<SysYParser::LOrExpContext>(0);
}


size_t SysYParser::CondContext::getRuleIndex() const {
  return SysYParser::RuleCond;
}

void SysYParser::CondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCond(this);
}

void SysYParser::CondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCond(this);
}


antlrcpp::Any SysYParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::CondContext* SysYParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 38, SysYParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(259);
    lOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

SysYParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::LValContext::getRuleIndex() const {
  return SysYParser::RuleLVal;
}

void SysYParser::LValContext::copyFrom(LValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LValArrayContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::LValArrayContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

std::vector<SysYParser::ExpContext *> SysYParser::LValArrayContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::LValArrayContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}

SysYParser::LValArrayContext::LValArrayContext(LValContext *ctx) { copyFrom(ctx); }

void SysYParser::LValArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLValArray(this);
}
void SysYParser::LValArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLValArray(this);
}

antlrcpp::Any SysYParser::LValArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLValArray(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LValSingleContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::LValSingleContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::LValSingleContext::LValSingleContext(LValContext *ctx) { copyFrom(ctx); }

void SysYParser::LValSingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLValSingle(this);
}
void SysYParser::LValSingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLValSingle(this);
}

antlrcpp::Any SysYParser::LValSingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLValSingle(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::LValContext* SysYParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 40, SysYParser::RuleLVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::LValSingleContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(261);
      match(SysYParser::Identifier);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::LValArrayContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(262);
      match(SysYParser::Identifier);
      setState(267); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(263);
        match(SysYParser::T__8);
        setState(264);
        exp();
        setState(265);
        match(SysYParser::T__9);
        setState(269); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SysYParser::T__8);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

SysYParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::PrimaryExpContext::getRuleIndex() const {
  return SysYParser::RulePrimaryExp;
}

void SysYParser::PrimaryExpContext::copyFrom(PrimaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PrimaryExpParenContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::PrimaryExpParenContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::PrimaryExpParenContext::PrimaryExpParenContext(PrimaryExpContext *ctx) { copyFrom(ctx); }

void SysYParser::PrimaryExpParenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpParen(this);
}
void SysYParser::PrimaryExpParenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpParen(this);
}

antlrcpp::Any SysYParser::PrimaryExpParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryExpNumberContext ------------------------------------------------------------------

SysYParser::NumberContext* SysYParser::PrimaryExpNumberContext::number() {
  return getRuleContext<SysYParser::NumberContext>(0);
}

SysYParser::PrimaryExpNumberContext::PrimaryExpNumberContext(PrimaryExpContext *ctx) { copyFrom(ctx); }

void SysYParser::PrimaryExpNumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpNumber(this);
}
void SysYParser::PrimaryExpNumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpNumber(this);
}

antlrcpp::Any SysYParser::PrimaryExpNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryExpLValContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::PrimaryExpLValContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::PrimaryExpLValContext::PrimaryExpLValContext(PrimaryExpContext *ctx) { copyFrom(ctx); }

void SysYParser::PrimaryExpLValContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpLVal(this);
}
void SysYParser::PrimaryExpLValContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpLVal(this);
}

antlrcpp::Any SysYParser::PrimaryExpLValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpLVal(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::PrimaryExpContext* SysYParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 42, SysYParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(279);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10: {
        _localctx = _tracker.createInstance<SysYParser::PrimaryExpParenContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(273);
        match(SysYParser::T__10);
        setState(274);
        exp();
        setState(275);
        match(SysYParser::T__11);
        break;
      }

      case SysYParser::Identifier: {
        _localctx = _tracker.createInstance<SysYParser::PrimaryExpLValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(277);
        lVal();
        break;
      }

      case SysYParser::DecimalConstant:
      case SysYParser::OctalConstant:
      case SysYParser::HexadecimalConstant:
      case SysYParser::FloatingConstant: {
        _localctx = _tracker.createInstance<SysYParser::PrimaryExpNumberContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(278);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

SysYParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::IntConstContext* SysYParser::NumberContext::intConst() {
  return getRuleContext<SysYParser::IntConstContext>(0);
}

SysYParser::FloatConstContext* SysYParser::NumberContext::floatConst() {
  return getRuleContext<SysYParser::FloatConstContext>(0);
}


size_t SysYParser::NumberContext::getRuleIndex() const {
  return SysYParser::RuleNumber;
}

void SysYParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void SysYParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}


antlrcpp::Any SysYParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::NumberContext* SysYParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 44, SysYParser::RuleNumber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(283);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::DecimalConstant:
      case SysYParser::OctalConstant:
      case SysYParser::HexadecimalConstant: {
        enterOuterAlt(_localctx, 1);
        setState(281);
        intConst();
        break;
      }

      case SysYParser::FloatingConstant: {
        enterOuterAlt(_localctx, 2);
        setState(282);
        floatConst();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

SysYParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::UnaryExpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryExp;
}

void SysYParser::UnaryExpContext::copyFrom(UnaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExpFuncRContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::UnaryExpFuncRContext::Identifier() {
  return getToken(SysYParser::Identifier, 0);
}

SysYParser::FuncRParamsContext* SysYParser::UnaryExpFuncRContext::funcRParams() {
  return getRuleContext<SysYParser::FuncRParamsContext>(0);
}

SysYParser::UnaryExpFuncRContext::UnaryExpFuncRContext(UnaryExpContext *ctx) { copyFrom(ctx); }

void SysYParser::UnaryExpFuncRContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpFuncR(this);
}
void SysYParser::UnaryExpFuncRContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpFuncR(this);
}

antlrcpp::Any SysYParser::UnaryExpFuncRContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitUnaryExpFuncR(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExpPrimaryExpContext ------------------------------------------------------------------

SysYParser::PrimaryExpContext* SysYParser::UnaryExpPrimaryExpContext::primaryExp() {
  return getRuleContext<SysYParser::PrimaryExpContext>(0);
}

SysYParser::UnaryExpPrimaryExpContext::UnaryExpPrimaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }

void SysYParser::UnaryExpPrimaryExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpPrimaryExp(this);
}
void SysYParser::UnaryExpPrimaryExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpPrimaryExp(this);
}

antlrcpp::Any SysYParser::UnaryExpPrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitUnaryExpPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExpUnaryContext ------------------------------------------------------------------

SysYParser::UnaryOpContext* SysYParser::UnaryExpUnaryContext::unaryOp() {
  return getRuleContext<SysYParser::UnaryOpContext>(0);
}

SysYParser::UnaryExpContext* SysYParser::UnaryExpUnaryContext::unaryExp() {
  return getRuleContext<SysYParser::UnaryExpContext>(0);
}

SysYParser::UnaryExpUnaryContext::UnaryExpUnaryContext(UnaryExpContext *ctx) { copyFrom(ctx); }

void SysYParser::UnaryExpUnaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpUnary(this);
}
void SysYParser::UnaryExpUnaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpUnary(this);
}

antlrcpp::Any SysYParser::UnaryExpUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitUnaryExpUnary(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::UnaryExpContext* SysYParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 46, SysYParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(295);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::UnaryExpPrimaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(285);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::UnaryExpFuncRContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(286);
      match(SysYParser::Identifier);
      setState(287);
      match(SysYParser::T__10);
      setState(289);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__10)
        | (1ULL << SysYParser::T__19)
        | (1ULL << SysYParser::T__20)
        | (1ULL << SysYParser::T__21)
        | (1ULL << SysYParser::Identifier)
        | (1ULL << SysYParser::DecimalConstant)
        | (1ULL << SysYParser::OctalConstant)
        | (1ULL << SysYParser::HexadecimalConstant)
        | (1ULL << SysYParser::FloatingConstant)
        | (1ULL << SysYParser::StringLiteral))) != 0)) {
        setState(288);
        funcRParams();
      }
      setState(291);
      match(SysYParser::T__11);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::UnaryExpUnaryContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(292);
      unaryOp();
      setState(293);
      unaryExp();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOpContext ------------------------------------------------------------------

SysYParser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::UnaryOpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryOp;
}

void SysYParser::UnaryOpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOp(this);
}

void SysYParser::UnaryOpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOp(this);
}


antlrcpp::Any SysYParser::UnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitUnaryOp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::UnaryOpContext* SysYParser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 48, SysYParser::RuleUnaryOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__19)
      | (1ULL << SysYParser::T__20)
      | (1ULL << SysYParser::T__21))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

SysYParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::FuncRParamContext *> SysYParser::FuncRParamsContext::funcRParam() {
  return getRuleContexts<SysYParser::FuncRParamContext>();
}

SysYParser::FuncRParamContext* SysYParser::FuncRParamsContext::funcRParam(size_t i) {
  return getRuleContext<SysYParser::FuncRParamContext>(i);
}


size_t SysYParser::FuncRParamsContext::getRuleIndex() const {
  return SysYParser::RuleFuncRParams;
}

void SysYParser::FuncRParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncRParams(this);
}

void SysYParser::FuncRParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncRParams(this);
}


antlrcpp::Any SysYParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncRParamsContext* SysYParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 50, SysYParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(299);
    funcRParam();
    setState(304);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__1) {
      setState(300);
      match(SysYParser::T__1);
      setState(301);
      funcRParam();
      setState(306);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamContext ------------------------------------------------------------------

SysYParser::FuncRParamContext::FuncRParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ExpContext* SysYParser::FuncRParamContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

tree::TerminalNode* SysYParser::FuncRParamContext::StringLiteral() {
  return getToken(SysYParser::StringLiteral, 0);
}


size_t SysYParser::FuncRParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncRParam;
}

void SysYParser::FuncRParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncRParam(this);
}

void SysYParser::FuncRParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncRParam(this);
}


antlrcpp::Any SysYParser::FuncRParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFuncRParam(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncRParamContext* SysYParser::funcRParam() {
  FuncRParamContext *_localctx = _tracker.createInstance<FuncRParamContext>(_ctx, getState());
  enterRule(_localctx, 52, SysYParser::RuleFuncRParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(309);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::T__10:
      case SysYParser::T__19:
      case SysYParser::T__20:
      case SysYParser::T__21:
      case SysYParser::Identifier:
      case SysYParser::DecimalConstant:
      case SysYParser::OctalConstant:
      case SysYParser::HexadecimalConstant:
      case SysYParser::FloatingConstant: {
        enterOuterAlt(_localctx, 1);
        setState(307);
        exp();
        break;
      }

      case SysYParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(308);
        match(SysYParser::StringLiteral);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

SysYParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::UnaryExpContext *> SysYParser::MulExpContext::unaryExp() {
  return getRuleContexts<SysYParser::UnaryExpContext>();
}

SysYParser::UnaryExpContext* SysYParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<SysYParser::UnaryExpContext>(i);
}


size_t SysYParser::MulExpContext::getRuleIndex() const {
  return SysYParser::RuleMulExp;
}

void SysYParser::MulExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulExp(this);
}

void SysYParser::MulExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulExp(this);
}


antlrcpp::Any SysYParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::MulExpContext* SysYParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 54, SysYParser::RuleMulExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(311);
    antlrcpp::downCast<MulExpContext *>(_localctx)->left = unaryExp();
    setState(316);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__22)
      | (1ULL << SysYParser::T__23)
      | (1ULL << SysYParser::T__24))) != 0)) {
      setState(312);
      antlrcpp::downCast<MulExpContext *>(_localctx)->_tset661 = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__22)
        | (1ULL << SysYParser::T__23)
        | (1ULL << SysYParser::T__24))) != 0))) {
        antlrcpp::downCast<MulExpContext *>(_localctx)->_tset661 = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      antlrcpp::downCast<MulExpContext *>(_localctx)->op.push_back(antlrcpp::downCast<MulExpContext *>(_localctx)->_tset661);
      setState(313);
      antlrcpp::downCast<MulExpContext *>(_localctx)->unaryExpContext = unaryExp();
      antlrcpp::downCast<MulExpContext *>(_localctx)->right.push_back(antlrcpp::downCast<MulExpContext *>(_localctx)->unaryExpContext);
      setState(318);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

SysYParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::MulExpContext *> SysYParser::AddExpContext::mulExp() {
  return getRuleContexts<SysYParser::MulExpContext>();
}

SysYParser::MulExpContext* SysYParser::AddExpContext::mulExp(size_t i) {
  return getRuleContext<SysYParser::MulExpContext>(i);
}


size_t SysYParser::AddExpContext::getRuleIndex() const {
  return SysYParser::RuleAddExp;
}

void SysYParser::AddExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExp(this);
}

void SysYParser::AddExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExp(this);
}


antlrcpp::Any SysYParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::AddExpContext* SysYParser::addExp() {
  AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, getState());
  enterRule(_localctx, 56, SysYParser::RuleAddExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    antlrcpp::downCast<AddExpContext *>(_localctx)->left = mulExp();
    setState(324);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__19

    || _la == SysYParser::T__20) {
      setState(320);
      antlrcpp::downCast<AddExpContext *>(_localctx)->_tset694 = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == SysYParser::T__19

      || _la == SysYParser::T__20)) {
        antlrcpp::downCast<AddExpContext *>(_localctx)->_tset694 = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      antlrcpp::downCast<AddExpContext *>(_localctx)->op.push_back(antlrcpp::downCast<AddExpContext *>(_localctx)->_tset694);
      setState(321);
      antlrcpp::downCast<AddExpContext *>(_localctx)->mulExpContext = mulExp();
      antlrcpp::downCast<AddExpContext *>(_localctx)->right.push_back(antlrcpp::downCast<AddExpContext *>(_localctx)->mulExpContext);
      setState(326);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

SysYParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::AddExpContext *> SysYParser::RelExpContext::addExp() {
  return getRuleContexts<SysYParser::AddExpContext>();
}

SysYParser::AddExpContext* SysYParser::RelExpContext::addExp(size_t i) {
  return getRuleContext<SysYParser::AddExpContext>(i);
}


size_t SysYParser::RelExpContext::getRuleIndex() const {
  return SysYParser::RuleRelExp;
}

void SysYParser::RelExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelExp(this);
}

void SysYParser::RelExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelExp(this);
}


antlrcpp::Any SysYParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::RelExpContext* SysYParser::relExp() {
  RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, getState());
  enterRule(_localctx, 58, SysYParser::RuleRelExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    antlrcpp::downCast<RelExpContext *>(_localctx)->left = addExp();
    setState(332);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SysYParser::T__25)
      | (1ULL << SysYParser::T__26)
      | (1ULL << SysYParser::T__27)
      | (1ULL << SysYParser::T__28))) != 0)) {
      setState(328);
      antlrcpp::downCast<RelExpContext *>(_localctx)->_tset722 = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << SysYParser::T__25)
        | (1ULL << SysYParser::T__26)
        | (1ULL << SysYParser::T__27)
        | (1ULL << SysYParser::T__28))) != 0))) {
        antlrcpp::downCast<RelExpContext *>(_localctx)->_tset722 = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      antlrcpp::downCast<RelExpContext *>(_localctx)->op.push_back(antlrcpp::downCast<RelExpContext *>(_localctx)->_tset722);
      setState(329);
      antlrcpp::downCast<RelExpContext *>(_localctx)->addExpContext = addExp();
      antlrcpp::downCast<RelExpContext *>(_localctx)->right.push_back(antlrcpp::downCast<RelExpContext *>(_localctx)->addExpContext);
      setState(334);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

SysYParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::RelExpContext *> SysYParser::EqExpContext::relExp() {
  return getRuleContexts<SysYParser::RelExpContext>();
}

SysYParser::RelExpContext* SysYParser::EqExpContext::relExp(size_t i) {
  return getRuleContext<SysYParser::RelExpContext>(i);
}


size_t SysYParser::EqExpContext::getRuleIndex() const {
  return SysYParser::RuleEqExp;
}

void SysYParser::EqExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqExp(this);
}

void SysYParser::EqExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqExp(this);
}


antlrcpp::Any SysYParser::EqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitEqExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::EqExpContext* SysYParser::eqExp() {
  EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, getState());
  enterRule(_localctx, 60, SysYParser::RuleEqExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    antlrcpp::downCast<EqExpContext *>(_localctx)->left = relExp();
    setState(340);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__29

    || _la == SysYParser::T__30) {
      setState(336);
      antlrcpp::downCast<EqExpContext *>(_localctx)->_tset757 = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == SysYParser::T__29

      || _la == SysYParser::T__30)) {
        antlrcpp::downCast<EqExpContext *>(_localctx)->_tset757 = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      antlrcpp::downCast<EqExpContext *>(_localctx)->op.push_back(antlrcpp::downCast<EqExpContext *>(_localctx)->_tset757);
      setState(337);
      antlrcpp::downCast<EqExpContext *>(_localctx)->relExpContext = relExp();
      antlrcpp::downCast<EqExpContext *>(_localctx)->right.push_back(antlrcpp::downCast<EqExpContext *>(_localctx)->relExpContext);
      setState(342);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

SysYParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::EqExpContext *> SysYParser::LAndExpContext::eqExp() {
  return getRuleContexts<SysYParser::EqExpContext>();
}

SysYParser::EqExpContext* SysYParser::LAndExpContext::eqExp(size_t i) {
  return getRuleContext<SysYParser::EqExpContext>(i);
}


size_t SysYParser::LAndExpContext::getRuleIndex() const {
  return SysYParser::RuleLAndExp;
}

void SysYParser::LAndExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLAndExp(this);
}

void SysYParser::LAndExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLAndExp(this);
}


antlrcpp::Any SysYParser::LAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLAndExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::LAndExpContext* SysYParser::lAndExp() {
  LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, getState());
  enterRule(_localctx, 62, SysYParser::RuleLAndExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(343);
    antlrcpp::downCast<LAndExpContext *>(_localctx)->left = eqExp();
    setState(348);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__31) {
      setState(344);
      antlrcpp::downCast<LAndExpContext *>(_localctx)->s32 = match(SysYParser::T__31);
      antlrcpp::downCast<LAndExpContext *>(_localctx)->op.push_back(antlrcpp::downCast<LAndExpContext *>(_localctx)->s32);
      setState(345);
      antlrcpp::downCast<LAndExpContext *>(_localctx)->eqExpContext = eqExp();
      antlrcpp::downCast<LAndExpContext *>(_localctx)->right.push_back(antlrcpp::downCast<LAndExpContext *>(_localctx)->eqExpContext);
      setState(350);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

SysYParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::LAndExpContext *> SysYParser::LOrExpContext::lAndExp() {
  return getRuleContexts<SysYParser::LAndExpContext>();
}

SysYParser::LAndExpContext* SysYParser::LOrExpContext::lAndExp(size_t i) {
  return getRuleContext<SysYParser::LAndExpContext>(i);
}


size_t SysYParser::LOrExpContext::getRuleIndex() const {
  return SysYParser::RuleLOrExp;
}

void SysYParser::LOrExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLOrExp(this);
}

void SysYParser::LOrExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLOrExp(this);
}


antlrcpp::Any SysYParser::LOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitLOrExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::LOrExpContext* SysYParser::lOrExp() {
  LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, getState());
  enterRule(_localctx, 64, SysYParser::RuleLOrExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(351);
    antlrcpp::downCast<LOrExpContext *>(_localctx)->left = lAndExp();
    setState(356);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::T__32) {
      setState(352);
      antlrcpp::downCast<LOrExpContext *>(_localctx)->s33 = match(SysYParser::T__32);
      antlrcpp::downCast<LOrExpContext *>(_localctx)->op.push_back(antlrcpp::downCast<LOrExpContext *>(_localctx)->s33);
      setState(353);
      antlrcpp::downCast<LOrExpContext *>(_localctx)->lAndExpContext = lAndExp();
      antlrcpp::downCast<LOrExpContext *>(_localctx)->right.push_back(antlrcpp::downCast<LOrExpContext *>(_localctx)->lAndExpContext);
      setState(358);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

SysYParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::AddExpContext* SysYParser::ConstExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}


size_t SysYParser::ConstExpContext::getRuleIndex() const {
  return SysYParser::RuleConstExp;
}

void SysYParser::ConstExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstExp(this);
}

void SysYParser::ConstExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstExp(this);
}


antlrcpp::Any SysYParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstExpContext* SysYParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 66, SysYParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(359);
    addExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntConstContext ------------------------------------------------------------------

SysYParser::IntConstContext::IntConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::IntConstContext::getRuleIndex() const {
  return SysYParser::RuleIntConst;
}

void SysYParser::IntConstContext::copyFrom(IntConstContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntHexConstContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IntHexConstContext::HexadecimalConstant() {
  return getToken(SysYParser::HexadecimalConstant, 0);
}

SysYParser::IntHexConstContext::IntHexConstContext(IntConstContext *ctx) { copyFrom(ctx); }

void SysYParser::IntHexConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntHexConst(this);
}
void SysYParser::IntHexConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntHexConst(this);
}

antlrcpp::Any SysYParser::IntHexConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitIntHexConst(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntDecConstContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IntDecConstContext::DecimalConstant() {
  return getToken(SysYParser::DecimalConstant, 0);
}

SysYParser::IntDecConstContext::IntDecConstContext(IntConstContext *ctx) { copyFrom(ctx); }

void SysYParser::IntDecConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntDecConst(this);
}
void SysYParser::IntDecConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntDecConst(this);
}

antlrcpp::Any SysYParser::IntDecConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitIntDecConst(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntOctConstContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IntOctConstContext::OctalConstant() {
  return getToken(SysYParser::OctalConstant, 0);
}

SysYParser::IntOctConstContext::IntOctConstContext(IntConstContext *ctx) { copyFrom(ctx); }

void SysYParser::IntOctConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntOctConst(this);
}
void SysYParser::IntOctConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntOctConst(this);
}

antlrcpp::Any SysYParser::IntOctConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitIntOctConst(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::IntConstContext* SysYParser::intConst() {
  IntConstContext *_localctx = _tracker.createInstance<IntConstContext>(_ctx, getState());
  enterRule(_localctx, 68, SysYParser::RuleIntConst);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::DecimalConstant: {
        _localctx = _tracker.createInstance<SysYParser::IntDecConstContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(361);
        match(SysYParser::DecimalConstant);
        break;
      }

      case SysYParser::OctalConstant: {
        _localctx = _tracker.createInstance<SysYParser::IntOctConstContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(362);
        match(SysYParser::OctalConstant);
        break;
      }

      case SysYParser::HexadecimalConstant: {
        _localctx = _tracker.createInstance<SysYParser::IntHexConstContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(363);
        match(SysYParser::HexadecimalConstant);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatConstContext ------------------------------------------------------------------

SysYParser::FloatConstContext::FloatConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::FloatConstContext::FloatingConstant() {
  return getToken(SysYParser::FloatingConstant, 0);
}


size_t SysYParser::FloatConstContext::getRuleIndex() const {
  return SysYParser::RuleFloatConst;
}

void SysYParser::FloatConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatConst(this);
}

void SysYParser::FloatConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<SysYListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatConst(this);
}


antlrcpp::Any SysYParser::FloatConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYVisitor*>(visitor))
    return parserVisitor->visitFloatConst(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FloatConstContext* SysYParser::floatConst() {
  FloatConstContext *_localctx = _tracker.createInstance<FloatConstContext>(_ctx, getState());
  enterRule(_localctx, 70, SysYParser::RuleFloatConst);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(366);
    match(SysYParser::FloatingConstant);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> SysYParser::_decisionToDFA;
atn::PredictionContextCache SysYParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SysYParser::_atn;
std::vector<uint16_t> SysYParser::_serializedATN;

std::vector<std::string> SysYParser::_ruleNames = {
  "program", "compUnit", "decl", "constDecl", "bType", "constDef", "constInitVal", 
  "varDecl", "varDef", "initLVal", "initVal", "funcDef", "funcType", "funcFParams", 
  "funcFParam", "block", "blockItem", "stmt", "exp", "cond", "lVal", "primaryExp", 
  "number", "unaryExp", "unaryOp", "funcRParams", "funcRParam", "mulExp", 
  "addExp", "relExp", "eqExp", "lAndExp", "lOrExp", "constExp", "intConst", 
  "floatConst"
};

std::vector<std::string> SysYParser::_literalNames = {
  "", "'const'", "','", "';'", "'int'", "'float'", "'='", "'{'", "'}'", 
  "'['", "']'", "'('", "')'", "'void'", "'if'", "'else'", "'while'", "'break'", 
  "'continue'", "'return'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<'", 
  "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'"
};

std::vector<std::string> SysYParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "Identifier", 
  "DecimalConstant", "OctalConstant", "HexadecimalConstant", "FloatingConstant", 
  "StringLiteral", "Whitespace", "Newline", "BlockComment", "LineComment"
};

dfa::Vocabulary SysYParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SysYParser::_tokenNames;

SysYParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x2d, 0x173, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x4f, 0xa, 0x3, 0xc, 0x3, 
       0xe, 0x3, 0x52, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 
       0x5, 0x4, 0x58, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x7, 0x5, 0x5f, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x62, 0xb, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x6f, 
       0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 
       0x8, 0x76, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x79, 0xb, 0x8, 0x5, 0x8, 
       0x7b, 0xa, 0x8, 0x3, 0x8, 0x5, 0x8, 0x7e, 0xa, 0x8, 0x3, 0x9, 0x3, 
       0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x84, 0xa, 0x9, 0xc, 0x9, 0xe, 
       0x9, 0x87, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x5, 0xa, 0x94, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x3, 0xb, 0x6, 0xb, 0x9b, 0xa, 0xb, 0xd, 0xb, 0xe, 0xb, 0x9c, 0x3, 
       0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0xa4, 0xa, 
       0xc, 0xc, 0xc, 0xe, 0xc, 0xa7, 0xb, 0xc, 0x5, 0xc, 0xa9, 0xa, 0xc, 
       0x3, 0xc, 0x5, 0xc, 0xac, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x5, 0xd, 0xb2, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0xbc, 
       0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xbf, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 
       0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
       0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 0xcc, 0xa, 0x10, 0xc, 
       0x10, 0xe, 0x10, 0xcf, 0xb, 0x10, 0x5, 0x10, 0xd1, 0xa, 0x10, 0x3, 
       0x11, 0x3, 0x11, 0x7, 0x11, 0xd5, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 
       0xd8, 0xb, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x5, 
       0x12, 0xde, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
       0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xe6, 0xa, 0x13, 0x3, 0x13, 0x3, 
       0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
       0x13, 0x3, 0x13, 0x5, 0x13, 0xf1, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 
       0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
       0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xff, 0xa, 
       0x13, 0x3, 0x13, 0x5, 0x13, 0x102, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 
       0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
       0x3, 0x16, 0x3, 0x16, 0x6, 0x16, 0x10e, 0xa, 0x16, 0xd, 0x16, 0xe, 
       0x16, 0x10f, 0x5, 0x16, 0x112, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 
       0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x11a, 0xa, 0x17, 
       0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x11e, 0xa, 0x18, 0x3, 0x19, 0x3, 
       0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x124, 0xa, 0x19, 0x3, 0x19, 
       0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x12a, 0xa, 0x19, 0x3, 
       0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x7, 0x1b, 0x131, 
       0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 0x134, 0xb, 0x1b, 0x3, 0x1c, 0x3, 
       0x1c, 0x5, 0x1c, 0x138, 0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
       0x7, 0x1d, 0x13d, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x140, 0xb, 0x1d, 
       0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x145, 0xa, 0x1e, 0xc, 
       0x1e, 0xe, 0x1e, 0x148, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 
       0x7, 0x1f, 0x14d, 0xa, 0x1f, 0xc, 0x1f, 0xe, 0x1f, 0x150, 0xb, 0x1f, 
       0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x7, 0x20, 0x155, 0xa, 0x20, 0xc, 
       0x20, 0xe, 0x20, 0x158, 0xb, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
       0x7, 0x21, 0x15d, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x160, 0xb, 0x21, 
       0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x7, 0x22, 0x165, 0xa, 0x22, 0xc, 
       0x22, 0xe, 0x22, 0x168, 0xb, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 
       0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x16f, 0xa, 0x24, 0x3, 0x25, 0x3, 
       0x25, 0x3, 0x25, 0x2, 0x2, 0x26, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
       0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 
       0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 
       0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x2, 0x9, 0x3, 0x2, 0x6, 
       0x7, 0x4, 0x2, 0x6, 0x7, 0xf, 0xf, 0x3, 0x2, 0x16, 0x18, 0x3, 0x2, 
       0x19, 0x1b, 0x3, 0x2, 0x16, 0x17, 0x3, 0x2, 0x1c, 0x1f, 0x3, 0x2, 
       0x20, 0x21, 0x2, 0x180, 0x2, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x50, 
       0x3, 0x2, 0x2, 0x2, 0x6, 0x57, 0x3, 0x2, 0x2, 0x2, 0x8, 0x59, 0x3, 
       0x2, 0x2, 0x2, 0xa, 0x65, 0x3, 0x2, 0x2, 0x2, 0xc, 0x6e, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x10, 0x7f, 0x3, 0x2, 0x2, 
       0x2, 0x12, 0x93, 0x3, 0x2, 0x2, 0x2, 0x14, 0x95, 0x3, 0x2, 0x2, 0x2, 
       0x16, 0xab, 0x3, 0x2, 0x2, 0x2, 0x18, 0xad, 0x3, 0x2, 0x2, 0x2, 0x1a, 
       0xb6, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xd0, 
       0x3, 0x2, 0x2, 0x2, 0x20, 0xd2, 0x3, 0x2, 0x2, 0x2, 0x22, 0xdd, 0x3, 
       0x2, 0x2, 0x2, 0x24, 0x101, 0x3, 0x2, 0x2, 0x2, 0x26, 0x103, 0x3, 
       0x2, 0x2, 0x2, 0x28, 0x105, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x111, 0x3, 
       0x2, 0x2, 0x2, 0x2c, 0x119, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x11d, 0x3, 
       0x2, 0x2, 0x2, 0x30, 0x129, 0x3, 0x2, 0x2, 0x2, 0x32, 0x12b, 0x3, 
       0x2, 0x2, 0x2, 0x34, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x36, 0x137, 0x3, 
       0x2, 0x2, 0x2, 0x38, 0x139, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x141, 0x3, 
       0x2, 0x2, 0x2, 0x3c, 0x149, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x151, 0x3, 
       0x2, 0x2, 0x2, 0x40, 0x159, 0x3, 0x2, 0x2, 0x2, 0x42, 0x161, 0x3, 
       0x2, 0x2, 0x2, 0x44, 0x169, 0x3, 0x2, 0x2, 0x2, 0x46, 0x16e, 0x3, 
       0x2, 0x2, 0x2, 0x48, 0x170, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x5, 
       0x4, 0x3, 0x2, 0x4b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4f, 0x5, 0x6, 
       0x4, 0x2, 0x4d, 0x4f, 0x5, 0x18, 0xd, 0x2, 0x4e, 0x4c, 0x3, 0x2, 
       0x2, 0x2, 0x4e, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x52, 0x3, 0x2, 0x2, 
       0x2, 0x50, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 0x2, 0x2, 
       0x51, 0x53, 0x3, 0x2, 0x2, 0x2, 0x52, 0x50, 0x3, 0x2, 0x2, 0x2, 0x53, 
       0x54, 0x7, 0x2, 0x2, 0x3, 0x54, 0x5, 0x3, 0x2, 0x2, 0x2, 0x55, 0x58, 
       0x5, 0x8, 0x5, 0x2, 0x56, 0x58, 0x5, 0x10, 0x9, 0x2, 0x57, 0x55, 
       0x3, 0x2, 0x2, 0x2, 0x57, 0x56, 0x3, 0x2, 0x2, 0x2, 0x58, 0x7, 0x3, 
       0x2, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x3, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0xa, 
       0x6, 0x2, 0x5b, 0x60, 0x5, 0xc, 0x7, 0x2, 0x5c, 0x5d, 0x7, 0x4, 0x2, 
       0x2, 0x5d, 0x5f, 0x5, 0xc, 0x7, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 
       0x5f, 0x62, 0x3, 0x2, 0x2, 0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 
       0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 0x63, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 
       0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x7, 0x5, 0x2, 0x2, 0x64, 0x9, 0x3, 
       0x2, 0x2, 0x2, 0x65, 0x66, 0x9, 0x2, 0x2, 0x2, 0x66, 0xb, 0x3, 0x2, 
       0x2, 0x2, 0x67, 0x68, 0x7, 0x24, 0x2, 0x2, 0x68, 0x69, 0x7, 0x8, 
       0x2, 0x2, 0x69, 0x6f, 0x5, 0xe, 0x8, 0x2, 0x6a, 0x6b, 0x5, 0x14, 
       0xb, 0x2, 0x6b, 0x6c, 0x7, 0x8, 0x2, 0x2, 0x6c, 0x6d, 0x5, 0xe, 0x8, 
       0x2, 0x6d, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x67, 0x3, 0x2, 0x2, 0x2, 
       0x6e, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6f, 0xd, 0x3, 0x2, 0x2, 0x2, 0x70, 
       0x7e, 0x5, 0x44, 0x23, 0x2, 0x71, 0x7a, 0x7, 0x9, 0x2, 0x2, 0x72, 
       0x77, 0x5, 0xe, 0x8, 0x2, 0x73, 0x74, 0x7, 0x4, 0x2, 0x2, 0x74, 0x76, 
       0x5, 0xe, 0x8, 0x2, 0x75, 0x73, 0x3, 0x2, 0x2, 0x2, 0x76, 0x79, 0x3, 
       0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x3, 0x2, 
       0x2, 0x2, 0x78, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 0x3, 0x2, 0x2, 
       0x2, 0x7a, 0x72, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 
       0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7e, 0x7, 0xa, 0x2, 0x2, 0x7d, 
       0x70, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x71, 0x3, 0x2, 0x2, 0x2, 0x7e, 0xf, 
       0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x5, 0xa, 0x6, 0x2, 0x80, 0x85, 0x5, 
       0x12, 0xa, 0x2, 0x81, 0x82, 0x7, 0x4, 0x2, 0x2, 0x82, 0x84, 0x5, 
       0x12, 0xa, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x84, 0x87, 0x3, 
       0x2, 0x2, 0x2, 0x85, 0x83, 0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x3, 0x2, 
       0x2, 0x2, 0x86, 0x88, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 
       0x2, 0x88, 0x89, 0x7, 0x5, 0x2, 0x2, 0x89, 0x11, 0x3, 0x2, 0x2, 0x2, 
       0x8a, 0x94, 0x7, 0x24, 0x2, 0x2, 0x8b, 0x94, 0x5, 0x14, 0xb, 0x2, 
       0x8c, 0x8d, 0x7, 0x24, 0x2, 0x2, 0x8d, 0x8e, 0x7, 0x8, 0x2, 0x2, 
       0x8e, 0x94, 0x5, 0x16, 0xc, 0x2, 0x8f, 0x90, 0x5, 0x14, 0xb, 0x2, 
       0x90, 0x91, 0x7, 0x8, 0x2, 0x2, 0x91, 0x92, 0x5, 0x16, 0xc, 0x2, 
       0x92, 0x94, 0x3, 0x2, 0x2, 0x2, 0x93, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x93, 
       0x8b, 0x3, 0x2, 0x2, 0x2, 0x93, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x93, 0x8f, 
       0x3, 0x2, 0x2, 0x2, 0x94, 0x13, 0x3, 0x2, 0x2, 0x2, 0x95, 0x9a, 0x7, 
       0x24, 0x2, 0x2, 0x96, 0x97, 0x7, 0xb, 0x2, 0x2, 0x97, 0x98, 0x5, 
       0x44, 0x23, 0x2, 0x98, 0x99, 0x7, 0xc, 0x2, 0x2, 0x99, 0x9b, 0x3, 
       0x2, 0x2, 0x2, 0x9a, 0x96, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x3, 0x2, 
       0x2, 0x2, 0x9c, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9d, 0x3, 0x2, 0x2, 
       0x2, 0x9d, 0x15, 0x3, 0x2, 0x2, 0x2, 0x9e, 0xac, 0x5, 0x26, 0x14, 
       0x2, 0x9f, 0xa8, 0x7, 0x9, 0x2, 0x2, 0xa0, 0xa5, 0x5, 0x16, 0xc, 
       0x2, 0xa1, 0xa2, 0x7, 0x4, 0x2, 0x2, 0xa2, 0xa4, 0x5, 0x16, 0xc, 
       0x2, 0xa3, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa7, 0x3, 0x2, 0x2, 0x2, 
       0xa5, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa6, 
       0xa9, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa0, 
       0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x3, 
       0x2, 0x2, 0x2, 0xaa, 0xac, 0x7, 0xa, 0x2, 0x2, 0xab, 0x9e, 0x3, 0x2, 
       0x2, 0x2, 0xab, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xac, 0x17, 0x3, 0x2, 0x2, 
       0x2, 0xad, 0xae, 0x5, 0x1a, 0xe, 0x2, 0xae, 0xaf, 0x7, 0x24, 0x2, 
       0x2, 0xaf, 0xb1, 0x7, 0xd, 0x2, 0x2, 0xb0, 0xb2, 0x5, 0x1c, 0xf, 
       0x2, 0xb1, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 0x2, 
       0xb2, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0xe, 0x2, 0x2, 0xb4, 
       0xb5, 0x5, 0x20, 0x11, 0x2, 0xb5, 0x19, 0x3, 0x2, 0x2, 0x2, 0xb6, 
       0xb7, 0x9, 0x3, 0x2, 0x2, 0xb7, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xbd, 
       0x5, 0x1e, 0x10, 0x2, 0xb9, 0xba, 0x7, 0x4, 0x2, 0x2, 0xba, 0xbc, 
       0x5, 0x1e, 0x10, 0x2, 0xbb, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbf, 
       0x3, 0x2, 0x2, 0x2, 0xbd, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 
       0x2, 0x2, 0x2, 0xbe, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xbd, 0x3, 0x2, 
       0x2, 0x2, 0xc0, 0xc1, 0x5, 0xa, 0x6, 0x2, 0xc1, 0xc2, 0x7, 0x24, 
       0x2, 0x2, 0xc2, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x5, 0xa, 0x6, 
       0x2, 0xc4, 0xc5, 0x7, 0x24, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0xb, 0x2, 
       0x2, 0xc6, 0xcd, 0x7, 0xc, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0xb, 0x2, 0x2, 
       0xc8, 0xc9, 0x5, 0x26, 0x14, 0x2, 0xc9, 0xca, 0x7, 0xc, 0x2, 0x2, 
       0xca, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xcc, 
       0xcf, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 
       0x3, 0x2, 0x2, 0x2, 0xce, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xcd, 0x3, 
       0x2, 0x2, 0x2, 0xd0, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xc3, 0x3, 0x2, 
       0x2, 0x2, 0xd1, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd6, 0x7, 0x9, 0x2, 
       0x2, 0xd3, 0xd5, 0x5, 0x22, 0x12, 0x2, 0xd4, 0xd3, 0x3, 0x2, 0x2, 
       0x2, 0xd5, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd4, 0x3, 0x2, 0x2, 0x2, 
       0xd6, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd8, 
       0xd6, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x7, 0xa, 0x2, 0x2, 0xda, 0x21, 
       0x3, 0x2, 0x2, 0x2, 0xdb, 0xde, 0x5, 0x6, 0x4, 0x2, 0xdc, 0xde, 0x5, 
       0x24, 0x13, 0x2, 0xdd, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xdc, 0x3, 
       0x2, 0x2, 0x2, 0xde, 0x23, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe0, 0x5, 0x2a, 
       0x16, 0x2, 0xe0, 0xe1, 0x7, 0x8, 0x2, 0x2, 0xe1, 0xe2, 0x5, 0x26, 
       0x14, 0x2, 0xe2, 0xe3, 0x7, 0x5, 0x2, 0x2, 0xe3, 0x102, 0x3, 0x2, 
       0x2, 0x2, 0xe4, 0xe6, 0x5, 0x26, 0x14, 0x2, 0xe5, 0xe4, 0x3, 0x2, 
       0x2, 0x2, 0xe5, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x3, 0x2, 0x2, 
       0x2, 0xe7, 0x102, 0x7, 0x5, 0x2, 0x2, 0xe8, 0x102, 0x5, 0x20, 0x11, 
       0x2, 0xe9, 0xea, 0x7, 0x10, 0x2, 0x2, 0xea, 0xeb, 0x7, 0xd, 0x2, 
       0x2, 0xeb, 0xec, 0x5, 0x28, 0x15, 0x2, 0xec, 0xed, 0x7, 0xe, 0x2, 
       0x2, 0xed, 0xf0, 0x5, 0x24, 0x13, 0x2, 0xee, 0xef, 0x7, 0x11, 0x2, 
       0x2, 0xef, 0xf1, 0x5, 0x24, 0x13, 0x2, 0xf0, 0xee, 0x3, 0x2, 0x2, 
       0x2, 0xf0, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf1, 0x102, 0x3, 0x2, 0x2, 
       0x2, 0xf2, 0xf3, 0x7, 0x12, 0x2, 0x2, 0xf3, 0xf4, 0x7, 0xd, 0x2, 
       0x2, 0xf4, 0xf5, 0x5, 0x28, 0x15, 0x2, 0xf5, 0xf6, 0x7, 0xe, 0x2, 
       0x2, 0xf6, 0xf7, 0x5, 0x24, 0x13, 0x2, 0xf7, 0x102, 0x3, 0x2, 0x2, 
       0x2, 0xf8, 0xf9, 0x7, 0x13, 0x2, 0x2, 0xf9, 0x102, 0x7, 0x5, 0x2, 
       0x2, 0xfa, 0xfb, 0x7, 0x14, 0x2, 0x2, 0xfb, 0x102, 0x7, 0x5, 0x2, 
       0x2, 0xfc, 0xfe, 0x7, 0x15, 0x2, 0x2, 0xfd, 0xff, 0x5, 0x26, 0x14, 
       0x2, 0xfe, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 
       0xff, 0x100, 0x3, 0x2, 0x2, 0x2, 0x100, 0x102, 0x7, 0x5, 0x2, 0x2, 
       0x101, 0xdf, 0x3, 0x2, 0x2, 0x2, 0x101, 0xe5, 0x3, 0x2, 0x2, 0x2, 
       0x101, 0xe8, 0x3, 0x2, 0x2, 0x2, 0x101, 0xe9, 0x3, 0x2, 0x2, 0x2, 
       0x101, 0xf2, 0x3, 0x2, 0x2, 0x2, 0x101, 0xf8, 0x3, 0x2, 0x2, 0x2, 
       0x101, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x101, 0xfc, 0x3, 0x2, 0x2, 0x2, 
       0x102, 0x25, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x5, 0x3a, 0x1e, 0x2, 
       0x104, 0x27, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 0x5, 0x42, 0x22, 0x2, 
       0x106, 0x29, 0x3, 0x2, 0x2, 0x2, 0x107, 0x112, 0x7, 0x24, 0x2, 0x2, 
       0x108, 0x10d, 0x7, 0x24, 0x2, 0x2, 0x109, 0x10a, 0x7, 0xb, 0x2, 0x2, 
       0x10a, 0x10b, 0x5, 0x26, 0x14, 0x2, 0x10b, 0x10c, 0x7, 0xc, 0x2, 
       0x2, 0x10c, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x109, 0x3, 0x2, 0x2, 
       0x2, 0x10e, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x10d, 0x3, 0x2, 0x2, 
       0x2, 0x10f, 0x110, 0x3, 0x2, 0x2, 0x2, 0x110, 0x112, 0x3, 0x2, 0x2, 
       0x2, 0x111, 0x107, 0x3, 0x2, 0x2, 0x2, 0x111, 0x108, 0x3, 0x2, 0x2, 
       0x2, 0x112, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 0x7, 0xd, 0x2, 
       0x2, 0x114, 0x115, 0x5, 0x26, 0x14, 0x2, 0x115, 0x116, 0x7, 0xe, 
       0x2, 0x2, 0x116, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x117, 0x11a, 0x5, 0x2a, 
       0x16, 0x2, 0x118, 0x11a, 0x5, 0x2e, 0x18, 0x2, 0x119, 0x113, 0x3, 
       0x2, 0x2, 0x2, 0x119, 0x117, 0x3, 0x2, 0x2, 0x2, 0x119, 0x118, 0x3, 
       0x2, 0x2, 0x2, 0x11a, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11e, 0x5, 
       0x46, 0x24, 0x2, 0x11c, 0x11e, 0x5, 0x48, 0x25, 0x2, 0x11d, 0x11b, 
       0x3, 0x2, 0x2, 0x2, 0x11d, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x2f, 
       0x3, 0x2, 0x2, 0x2, 0x11f, 0x12a, 0x5, 0x2c, 0x17, 0x2, 0x120, 0x121, 
       0x7, 0x24, 0x2, 0x2, 0x121, 0x123, 0x7, 0xd, 0x2, 0x2, 0x122, 0x124, 
       0x5, 0x34, 0x1b, 0x2, 0x123, 0x122, 0x3, 0x2, 0x2, 0x2, 0x123, 0x124, 
       0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 0x125, 0x12a, 
       0x7, 0xe, 0x2, 0x2, 0x126, 0x127, 0x5, 0x32, 0x1a, 0x2, 0x127, 0x128, 
       0x5, 0x30, 0x19, 0x2, 0x128, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x129, 0x11f, 
       0x3, 0x2, 0x2, 0x2, 0x129, 0x120, 0x3, 0x2, 0x2, 0x2, 0x129, 0x126, 
       0x3, 0x2, 0x2, 0x2, 0x12a, 0x31, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12c, 
       0x9, 0x4, 0x2, 0x2, 0x12c, 0x33, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x132, 
       0x5, 0x36, 0x1c, 0x2, 0x12e, 0x12f, 0x7, 0x4, 0x2, 0x2, 0x12f, 0x131, 
       0x5, 0x36, 0x1c, 0x2, 0x130, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x131, 0x134, 
       0x3, 0x2, 0x2, 0x2, 0x132, 0x130, 0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 
       0x3, 0x2, 0x2, 0x2, 0x133, 0x35, 0x3, 0x2, 0x2, 0x2, 0x134, 0x132, 
       0x3, 0x2, 0x2, 0x2, 0x135, 0x138, 0x5, 0x26, 0x14, 0x2, 0x136, 0x138, 
       0x7, 0x29, 0x2, 0x2, 0x137, 0x135, 0x3, 0x2, 0x2, 0x2, 0x137, 0x136, 
       0x3, 0x2, 0x2, 0x2, 0x138, 0x37, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13e, 
       0x5, 0x30, 0x19, 0x2, 0x13a, 0x13b, 0x9, 0x5, 0x2, 0x2, 0x13b, 0x13d, 
       0x5, 0x30, 0x19, 0x2, 0x13c, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x140, 
       0x3, 0x2, 0x2, 0x2, 0x13e, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13f, 
       0x3, 0x2, 0x2, 0x2, 0x13f, 0x39, 0x3, 0x2, 0x2, 0x2, 0x140, 0x13e, 
       0x3, 0x2, 0x2, 0x2, 0x141, 0x146, 0x5, 0x38, 0x1d, 0x2, 0x142, 0x143, 
       0x9, 0x6, 0x2, 0x2, 0x143, 0x145, 0x5, 0x38, 0x1d, 0x2, 0x144, 0x142, 
       0x3, 0x2, 0x2, 0x2, 0x145, 0x148, 0x3, 0x2, 0x2, 0x2, 0x146, 0x144, 
       0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 0x2, 0x147, 0x3b, 
       0x3, 0x2, 0x2, 0x2, 0x148, 0x146, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14e, 
       0x5, 0x3a, 0x1e, 0x2, 0x14a, 0x14b, 0x9, 0x7, 0x2, 0x2, 0x14b, 0x14d, 
       0x5, 0x3a, 0x1e, 0x2, 0x14c, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x150, 
       0x3, 0x2, 0x2, 0x2, 0x14e, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 
       0x3, 0x2, 0x2, 0x2, 0x14f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x150, 0x14e, 
       0x3, 0x2, 0x2, 0x2, 0x151, 0x156, 0x5, 0x3c, 0x1f, 0x2, 0x152, 0x153, 
       0x9, 0x8, 0x2, 0x2, 0x153, 0x155, 0x5, 0x3c, 0x1f, 0x2, 0x154, 0x152, 
       0x3, 0x2, 0x2, 0x2, 0x155, 0x158, 0x3, 0x2, 0x2, 0x2, 0x156, 0x154, 
       0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 0x3, 0x2, 0x2, 0x2, 0x157, 0x3f, 
       0x3, 0x2, 0x2, 0x2, 0x158, 0x156, 0x3, 0x2, 0x2, 0x2, 0x159, 0x15e, 
       0x5, 0x3e, 0x20, 0x2, 0x15a, 0x15b, 0x7, 0x22, 0x2, 0x2, 0x15b, 0x15d, 
       0x5, 0x3e, 0x20, 0x2, 0x15c, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x160, 
       0x3, 0x2, 0x2, 0x2, 0x15e, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x15f, 
       0x3, 0x2, 0x2, 0x2, 0x15f, 0x41, 0x3, 0x2, 0x2, 0x2, 0x160, 0x15e, 
       0x3, 0x2, 0x2, 0x2, 0x161, 0x166, 0x5, 0x40, 0x21, 0x2, 0x162, 0x163, 
       0x7, 0x23, 0x2, 0x2, 0x163, 0x165, 0x5, 0x40, 0x21, 0x2, 0x164, 0x162, 
       0x3, 0x2, 0x2, 0x2, 0x165, 0x168, 0x3, 0x2, 0x2, 0x2, 0x166, 0x164, 
       0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0x3, 0x2, 0x2, 0x2, 0x167, 0x43, 
       0x3, 0x2, 0x2, 0x2, 0x168, 0x166, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16a, 
       0x5, 0x3a, 0x1e, 0x2, 0x16a, 0x45, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x16f, 
       0x7, 0x25, 0x2, 0x2, 0x16c, 0x16f, 0x7, 0x26, 0x2, 0x2, 0x16d, 0x16f, 
       0x7, 0x27, 0x2, 0x2, 0x16e, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x16c, 
       0x3, 0x2, 0x2, 0x2, 0x16e, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x47, 
       0x3, 0x2, 0x2, 0x2, 0x170, 0x171, 0x7, 0x28, 0x2, 0x2, 0x171, 0x49, 
       0x3, 0x2, 0x2, 0x2, 0x29, 0x4e, 0x50, 0x57, 0x60, 0x6e, 0x77, 0x7a, 
       0x7d, 0x85, 0x93, 0x9c, 0xa5, 0xa8, 0xab, 0xb1, 0xbd, 0xcd, 0xd0, 
       0xd6, 0xdd, 0xe5, 0xf0, 0xfe, 0x101, 0x10f, 0x111, 0x119, 0x11d, 
       0x123, 0x129, 0x132, 0x137, 0x13e, 0x146, 0x14e, 0x156, 0x15e, 0x166, 
       0x16e, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SysYParser::Initializer SysYParser::_init;
