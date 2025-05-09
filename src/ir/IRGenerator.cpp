#include "ir/IRGenerator.h"
#include<antlr4-runtime.h>
#include<string>

#define TODO(s) do { printf("todo: %s\n", s); std::exit(0); } while (0)

#define CONST_INT(num) new ConstantInt(module->int32_ty_, num)
#define CONST_FLOAT(num) new ConstantFloat(module->float32_ty_, num)
#define VOID_T (module->void_ty_)
#define INT1_T (module->int1_ty_)
#define INT32_T  (module->int32_ty_)
#define FLOAT_T  (module->float32_ty_)
#define INT32PTR_T (module->get_pointer_type(module->int32_ty_))
#define FLOATPTR_T (module->get_pointer_type(module->float32_ty_))

#define CURRENT_LINE(c) (c->getStart()->getLine())
#define CURRENT_COLUMN(c) (c->getStart()->getCharPositionInLine()+1) 
#define REPORT_SEMANTIC_ERROR_AND_RETURN(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx));return nullptr;}while(0)
#define REPORT_SEMANTIC_ERROR_AND_EXIT(msg, ctx) \
    do{errorReporter.addError(msg, SysYErrorHandling::ErrorType::SEMANTIC_ERROR, CURRENT_LINE(ctx), CURRENT_COLUMN(ctx)); printErrors(); std::exit(0);}while(0)
#define PRINT_CURRENT_LINE_AND_COLUMN(c) \
    do{printf("当前行：%d, 当前列：%d\n", CURRENT_LINE(c), CURRENT_COLUMN(c));}while(0)

//根据待计算的两个Constant的类型，求出对应的值赋值到intVal，floatVal中，返回计算结果是否为int
bool SysYIRGenerator::checkCalType(Value* val[],int intVal[], float floatVal[]) {
    bool resultIsInt = false;
    if (dynamic_cast<ConstantInt*>(val[0]) && dynamic_cast<ConstantInt*>(val[1])) {
        resultIsInt = true;
        intVal[0] = dynamic_cast<ConstantInt*>(val[0])->value_;
        intVal[1] = dynamic_cast<ConstantInt*>(val[1])->value_;
    } else { //操作结果一定是float
        if (dynamic_cast<ConstantInt*>(val[0])) floatVal[0] = dynamic_cast<ConstantInt*>(val[0])->value_;
        else floatVal[0] = dynamic_cast<ConstantFloat*>(val[0])->value_;
        if (dynamic_cast<ConstantInt*>(val[1])) floatVal[1] = dynamic_cast<ConstantInt*>(val[1])->value_;
        else floatVal[1] = dynamic_cast<ConstantFloat*>(val[1])->value_;
    }
    return resultIsInt;
}

//根据待计算的两个寄存器数的类型，若需要转换类型输出转换指令
void SysYIRGenerator::checkCalType(Value* val[]) {
    if (val[0]->type_ == INT1_T) {
        val[0] = builder->create_zext(val[0], INT32_T);
    }
    if (val[1]->type_ == INT1_T) {
        val[1] = builder->create_zext(val[1], INT32_T);
    }
    if (val[0]->type_ == INT32_T && val[1]->type_ == FLOAT_T) {
        val[0] = builder->create_sitofp(val[0], FLOAT_T);
    }
    if (val[1]->type_ == INT32_T && val[0]->type_ == FLOAT_T) {
        val[1] = builder->create_sitofp(val[1], FLOAT_T);
    }
}

//判断得到的赋值与声明类型是否一致，并做转换
void SysYIRGenerator::checkInitType() {
    if (curDefType == INT32_T) {
        if (dynamic_cast<ConstantFloat*>(retValue)) {
            auto temp = dynamic_cast<ConstantFloat*>(retValue);
            retValue = CONST_INT((int)temp->value_);
        } else if (retValue->type_->tid_ == Type::FloatTyID) {
            retValue = builder->create_fptosi(retValue, INT32_T);
        }
    } else if (curDefType == FLOAT_T) {
        if (dynamic_cast<ConstantInt*>(retValue)) {
            auto temp = dynamic_cast<ConstantInt*>(retValue);
            retValue = CONST_FLOAT(temp->value_);
        } else if (retValue->type_->tid_ == Type::IntegerTyID) {
            retValue = builder->create_sitofp(retValue, FLOAT_T);
        }
    }
}

//嵌套大括号数组的维度，即倒数连续0的第一个。 如[0,1,0,0]，返回2；[0,0,0,1]，返回4；
//若全是0，[0,0,0,0],返回1
int SysYIRGenerator::getNextDim(vector<int> &elementsCnts, int up) {
    for (int i = elementsCnts.size() - 1; i > up; i--) {
        if (elementsCnts[i] != 0) return i + 1;
    }
    return up + 1;
}

//增加元素后，合并所有能合并的数组元素，即对齐
void SysYIRGenerator::mergeElements(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, int dimAdd, vector<Constant*> &elements, vector<int> &elementsCnts) {
    for (int i = dimAdd; i > up; i--) {
        if (elementsCnts[i] % dimensions[i] == 0) {
            vector<Constant*> temp;
            temp.assign(elements.end() - dimensions[i], elements.end());
            elements.erase(elements.end() - dimensions[i], elements.end());
            elements.push_back(new ConstantArray(arrayTys[i], temp));
            elementsCnts[i] = 0;
            elementsCnts[i - 1]++;
        } else break;
    }
}

//最后合并所有元素，不足合并则填0元素，使得elements只剩下一个arrayTys[up]类型的最终数组
void SysYIRGenerator::finalMerge(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, vector<Constant*> &elements, vector<int> &elementsCnts) const {
    for (int i = dimensions.size() - 1; i >= up; i--) {
        while (elementsCnts[i] % dimensions[i] != 0) { //补充当前数组类型所需0元素
            if (i == dimensions.size() - 1) {
                if (curDefType == INT32_T) {
                    elements.push_back(CONST_INT(0));
                } else {
                    elements.push_back(CONST_FLOAT(0));
                }
            } else {
                elements.push_back(new ConstantZero(arrayTys[i + 1]));
            }
            elementsCnts[i]++;
        }
        if (elementsCnts[i] != 0) {
            vector<Constant*> temp;
            temp.assign(elements.end() - dimensions[i], elements.end());
            elements.erase(elements.end() - dimensions[i], elements.end());
            elements.push_back(new ConstantArray(arrayTys[i], temp));
            elementsCnts[i] = 0;
            if (i != up) elementsCnts[i - 1]++;
        }
    }
}

//生成常量数组的初始化
ConstantArray* SysYIRGenerator::globalInit(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, vector<SysYParser::ConstInitValContext*> &list) {
    vector<int> elementsCnts(dimensions.size()); //对应各个维度的子数组的元素个数
    vector<Constant*> elements; //各个元素
    int dimAdd;
    std::cout<<list.size()<<std::endl;
    for (auto* val : list) {
        if (dynamic_cast<SysYParser::ConstInitValSingleContext*>(val) != nullptr) {
            auto *tmp = dynamic_cast<SysYParser::ConstInitValSingleContext*>(val);
            dimAdd = dimensions.size() - 1;
            visit(tmp->constExp());
            checkInitType();
            elements.push_back((Constant*)retValue);
            // std::cout << "elements.back(): " << elements.back()->print() << std::endl;
        } else {
            auto *tmp = dynamic_cast<SysYParser::ConstInitValArrayContext*>(val);
            auto nextUp = getNextDim(elementsCnts, up); //该嵌套数组的维度
            dimAdd = nextUp - 1; //比他高一维度的数组需要添加一个元素
            // if (nextUp == dimensions.size()) cout << "initial invalid" << endl;//没有连续0，没对齐，不合法
            if (tmp->constInitVal().size() == 0) { //空初始化列表
                elements.push_back(new ConstantZero(arrayTys[nextUp]));
            } else {
                vector<SysYParser::ConstInitValContext*> newList;
                for(auto* constInitVal : tmp->constInitVal()) {
                    newList.push_back(constInitVal);
                }
                // newList.assign(tmp->constInitVal().begin(), tmp->constInitVal().end());
                auto temp = globalInit(dimensions, arrayTys, nextUp, newList);
                elements.push_back(temp);
            }
        }
        elementsCnts[dimAdd]++;
        mergeElements(dimensions, arrayTys, up, dimAdd, elements, elementsCnts);
    }
    finalMerge(dimensions, arrayTys, up, elements, elementsCnts);
    return static_cast<ConstantArray*>(elements[0]);
}

//生成变量数组的初始化
ConstantArray* SysYIRGenerator::globalInit(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, vector<SysYParser::InitValContext*> &list) {
    vector<int> elementsCnts(dimensions.size()); //对应各个维度的子数组的元素个数
    vector<Constant*> elements; //各个元素
    int dimAdd;
    for (auto* val : list) {
        if (dynamic_cast<SysYParser::InitValSingleContext*>(val) != nullptr) {
            auto *tmp = dynamic_cast<SysYParser::InitValSingleContext*>(val);
            dimAdd = dimensions.size() - 1;
            visit(tmp->exp());
            checkInitType();
            elements.push_back((ConstantInt*)retValue);
        } else {
            auto *tmp = dynamic_cast<SysYParser::InitValArrayContext*>(val);
            auto nextUp = getNextDim(elementsCnts, up); //该嵌套数组的维度
            dimAdd = nextUp - 1; //比他高一维度的数组需要添加一个元素
            // if (nextUp == dimensions.size()) cout << "initial invalid" << endl;//没有连续0，没对齐，不合法
            if (tmp->initVal().size() == 0) { //空初始化列表
                elements.push_back(new ConstantZero(arrayTys[nextUp]));
            } else {
                vector<SysYParser::InitValContext*> newList;
                for(auto* initVal : tmp->initVal()) {
                    newList.push_back(initVal);
                }
                // newList.assign(tmp->initVal().begin(), tmp->initVal().end());
                auto temp = globalInit(dimensions, arrayTys, nextUp, newList);
                elements.push_back(temp);
            }
        }
        elementsCnts[dimAdd]++;
        mergeElements(dimensions, arrayTys, up, dimAdd, elements, elementsCnts);
    }
    finalMerge(dimensions, arrayTys, up, elements, elementsCnts);
    return static_cast<ConstantArray*>(elements[0]);
}

//根据初始化的量决定嵌套数组的维度
int SysYIRGenerator::getNextDim(vector<int> &dimensionsCnt, int up, int cnt) {
    for (int i = up; i < dimensionsCnt.size(); i++) {
        if (cnt % dimensionsCnt[i] == 0) return i;
    }
    return 0;
}

//根据首指针递归初始化数组,up表示子数组的最高对齐位置，比如[4][2][4]，子数组最高对齐[2][4],up为1
void SysYIRGenerator::localInit(Value* ptr, vector<SysYParser::ConstInitValContext*> &list, vector<int> &dimensionsCnt, int up) {
    int cnt = 0;
    Value* tempPtr = ptr;
    for (auto &initVal : list) {
        if (dynamic_cast<SysYParser::ConstInitValSingleContext*>(initVal) != nullptr) {
            if (cnt == 0) cnt++; //第一次赋值时可以少一次create_gep
            else tempPtr = builder->create_gep(ptr, {CONST_INT(cnt++)});
            auto *tmp = dynamic_cast<SysYParser::ConstInitValSingleContext*>(initVal);
            visit(tmp->constExp());
            checkInitType();
            builder->create_store(retValue, tempPtr);
        } else {
            auto nextUp = getNextDim(dimensionsCnt, up, cnt);
            auto *tmp = dynamic_cast<SysYParser::ConstInitValArrayContext*>(initVal);
            // if (nextUp == 0) cout << "initial invalid!" << endl;
            if (tmp->constInitVal().size() != 0) { //非空初始化列表
                if (cnt != 0) tempPtr = builder->create_gep(ptr, {CONST_INT(cnt)}); //没赋值过，那tempPtr实际就是ptr
                vector<SysYParser::ConstInitValContext*> newList;
                for(auto* constInitVal : tmp->constInitVal()) {
                    newList.push_back(constInitVal);
                }
                // newList.assign(tmp->constInitVal().begin(), tmp->constInitVal().end());
                localInit(tempPtr, newList, dimensionsCnt, nextUp);
            }
            cnt += dimensionsCnt[nextUp]; //数组初始化量一定增加这么多
        }
    }
}

//根据首指针递归初始化数组,up表示子数组的最高对齐位置，比如[4][2][4]，子数组最高对齐[2][4],up为1
void SysYIRGenerator::localInit(Value* ptr, vector<SysYParser::InitValContext*> &list, vector<int> &dimensionsCnt, int up) {
    int cnt = 0;
    Value* tempPtr = ptr;
    for (auto &initVal : list) {
        if (dynamic_cast<SysYParser::InitValSingleContext*>(initVal) != nullptr) {
            if (cnt == 0) cnt++; //第一次赋值时可以少一次create_gep
            else tempPtr = builder->create_gep(ptr, {CONST_INT(cnt++)});
            auto *tmp = dynamic_cast<SysYParser::InitValSingleContext*>(initVal);
            visit(tmp->exp());
            checkInitType();
            builder->create_store(retValue, tempPtr);
        } else {
            auto nextUp = getNextDim(dimensionsCnt, up, cnt);
            auto *tmp = dynamic_cast<SysYParser::InitValArrayContext*>(initVal);
            // if (nextUp == 0) cout << "initial invalid!" << endl;
            if (tmp->initVal().size() != 0) { //非空初始化列表
                if (cnt != 0) tempPtr = builder->create_gep(ptr, {CONST_INT(cnt)}); //没赋值过，那tempPtr实际就是ptr
                vector<SysYParser::InitValContext*> newList;
                for(auto* initVal : tmp->initVal()) {
                    newList.push_back(initVal);
                }
                // newList.assign(tmp->initVal().begin(), tmp->initVal().end());
                localInit(tempPtr, newList, dimensionsCnt, nextUp);
            }
            cnt += dimensionsCnt[nextUp]; //数组初始化量一定增加这么多
        }
    }
}



antlrcpp::Any SysYIRGenerator::visitProgram(SysYParser::ProgramContext *ctx)
{
    // printf("visitProgram\n");
    initTables();
    visit(ctx->compUnit());
    // printf("visitProgram end\n");
    return nullptr;
}
void SysYIRGenerator::initTables()
{
    typeTable.clear();
    typeTable["void"] = VOID_T;
    typeTable["int"] = INT32_T;
    typeTable["float"] = FLOAT_T;
}
antlrcpp::Any SysYIRGenerator::visitVarDecl(SysYParser::VarDeclContext *ctx)
{
    // printf("visitVarDecl\n");
    curDefType = typeTable[ctx->bType()->getText()];
    for (auto varDef : ctx->varDef()) {
        visit(varDef);
    }
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitConstDecl(SysYParser::ConstDeclContext* ctx)
{
    // printf("visitConstDecl\n");
    curDefType = typeTable[ctx->bType()->getText()];
    for (auto constDef : ctx->constDef()) {
        visit(constDef);
    }
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitConstDefSingle(SysYParser::ConstDefSingleContext* ctx)
{
    auto name = ctx->Identifier()->getText();
    visit(ctx->constInitVal());
    checkInitType();
    curScopes.addVarConstEntry(name,retValue);
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitConstDefArray(SysYParser::ConstDefArrayContext* ctx)
{
    // printf("visitConstDefArray\n");
    auto name = ctx->initLVal()->Identifier()->getText();
    if(curScopes.inGlobalScope())
    {
        std::vector<int> dimensions;
        for(auto e : ctx->initLVal()->constExp())
        {
            visit(e);
            dimensions.push_back(dynamic_cast<ConstantInt*>(retValue)->value_);
        }
        std::vector<ArrayType*> arrayTys(dimensions.size());
        for(int i = dimensions.size() - 1;i>=0;i--)
        {
            if(i == dimensions.size() - 1)
            {
                arrayTys[i] = module->get_array_type(curDefType, dimensions[i]);
            }
            else
            {
                arrayTys[i] = module->get_array_type(arrayTys[i+1], dimensions[i]);
            }
        }

        auto* constInitValArray = dynamic_cast<SysYParser::ConstInitValArrayContext*>(ctx->constInitVal());
        // printf("size: %d\n",constInitValArray->constInitVal().size());
        vector<SysYParser::ConstInitValContext*> list;
        for(auto c : constInitValArray->constInitVal())
        {
            list.push_back(c);
        }
        // list.assign(constInitValArray->constInitVal().begin(), constInitValArray->constInitVal().end());
        // printf("list.size(): %d\n",list.size());
        if(list.size() == 0)
        {
            auto init = new ConstantZero(arrayTys[0]);
            auto var = new GlobalVariable(name, module.get(), arrayTys[0], true, init);
            curScopes.addVarConstEntry(name, var);
        }
        else
        {
            // printf("Start global init, list.size(): %d\n",list.size());
            auto init = globalInit(dimensions, arrayTys, 0, list);
            // printf("End global init\n");
            auto var = new GlobalVariable(name, module.get(), arrayTys[0], true, init);
            curScopes.addVarConstEntry(name, var);
        }
    }
    else
    {
        vector<int> dimensions( ctx->initLVal()->constExp().size() ), dimensionsCnt( ctx->initLVal()->constExp().size() );
        int totalByte = 1;
        for(int i = ctx->initLVal()->constExp().size() - 1;i>=0;i--)
        {
            visit(ctx->initLVal()->constExp()[i]);
            int dimension = dynamic_cast<ConstantInt*>(retValue)->value_;
            totalByte *= dimension;
            dimensions[i] = dimension;
            dimensionsCnt[i] = totalByte;
        }
        totalByte *= 4;
        ArrayType *arrayTy;
        for(int i = dimensions.size()-1; i>=0; i--)
        {
            if(i == dimensions.size() - 1)
            {
                arrayTy = module->get_array_type(curDefType, dimensions[i]);
            }
            else
            {
                arrayTy = module->get_array_type(arrayTy, dimensions[i]);
            }
        }
        auto arrayAlloc = builder->create_alloca(arrayTy);
        curScopes.addVarConstEntry(name, arrayAlloc);
        Value* i32P = builder->create_bitcast(arrayAlloc, INT32PTR_T);
        auto memclr = curScopes.lookupFunc("memclr");//从函数符号表中找到memclr(TODO: 添加memclr等函数)
        builder->create_call(memclr, {i32P, CONST_INT(totalByte)});
        auto* constInitValArray = dynamic_cast<SysYParser::ConstInitValArrayContext*>(ctx->constInitVal());
        if(constInitValArray->constInitVal().size() == 0)
        {
            return nullptr;
        }
        vector<Value*> idxs(dimensions.size()+1);
        for(int i=0;i<dimensions.size()+1;i++)
        {
            idxs[i] = CONST_INT(0);
        }
        Value* ptr = builder->create_gep(arrayAlloc, idxs);//获取数组开头地址

        // auto* constInitValArray = dynamic_cast<SysYParser::ConstInitValArrayContext*>(ctx->constInitVal());
        vector<SysYParser::ConstInitValContext*> list;
        for(auto c : constInitValArray->constInitVal())
        {
            list.push_back(c);
        }
        // list.assign(constInitValArray->constInitVal().begin(), constInitValArray->constInitVal().end());

        localInit(ptr, list, dimensionsCnt, 1);
    }

    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitVarDefSingle(SysYParser::VarDefSingleContext* ctx)
{
    auto name = ctx->Identifier()->getText();
    if(curScopes.inGlobalScope())
    {
        GlobalVariable* var;
        if(curDefType == INT32_T)
        {
            var = new GlobalVariable(name, module.get(), curDefType, false, CONST_INT(0));
        }
        else
        {
            var = new GlobalVariable(name, module.get(), curDefType, false, CONST_FLOAT(0));
        }
        curScopes.addVarConstEntry(name, var);
    }
    else
    {
        AllocaInst *varAlloca;
        varAlloca = builder->create_alloca(curDefType);
        curScopes.addVarConstEntry(name, varAlloca);
    }
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitVarDefArray(SysYParser::VarDefArrayContext* ctx)
{
    auto name = ctx->initLVal()->Identifier()->getText();
    if(curScopes.inGlobalScope())
    {
        std::vector<int> dimensions;
        for(auto e : ctx->initLVal()->constExp())
        {
            visit(e);
            dimensions.push_back(dynamic_cast<ConstantInt*>(retValue)->value_);
        }
        std::vector<ArrayType*> arrayTys(dimensions.size());
        for(int i = dimensions.size() - 1;i>=0;i--)
        {
            if(i == dimensions.size() - 1)
            {
                arrayTys[i] = module->get_array_type(curDefType, dimensions[i]);
            }
            else
            {
                arrayTys[i] = module->get_array_type(arrayTys[i+1], dimensions[i]);
            }
        }
        auto init = new ConstantZero(arrayTys[0]);
        auto var = new GlobalVariable(name, module.get(), arrayTys[0], false, init);
        curScopes.addVarConstEntry(name, var);
    }
    else
    {
        vector<int> dimensions( ctx->initLVal()->constExp().size() ), dimensionsCnt( ctx->initLVal()->constExp().size() );
        int totalByte = 1;
        for(int i = ctx->initLVal()->constExp().size() - 1;i>=0;i--)
        {
            visit(ctx->initLVal()->constExp()[i]);
            int dimension = dynamic_cast<ConstantInt*>(retValue)->value_;
            totalByte *= dimension;
            dimensions[i] = dimension;
            dimensionsCnt[i] = totalByte;
        }
        totalByte *= 4;
        ArrayType *arrayTy;
        for(int i = dimensions.size()-1; i>=0; i--)
        {
            if(i == dimensions.size() - 1)
            {
                arrayTy = module->get_array_type(curDefType, dimensions[i]);
            }
            else
            {
                arrayTy = module->get_array_type(arrayTy, dimensions[i]);
            }
        }
        auto arrayAlloc = builder->create_alloca(arrayTy);
        curScopes.addVarConstEntry(name, arrayAlloc);
    }

    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitVarDefSingleInitVal(SysYParser::VarDefSingleInitValContext* ctx)
{
    auto name = ctx->Identifier()->getText();
    if(curScopes.inGlobalScope())
    {
        inConstExp++;//全局变量的初始值必为常量
        visit(ctx->initVal());
        inConstExp--;
        checkInitType();
        auto initalizer = static_cast<Constant *>(retValue);
        GlobalVariable* var;
        var = new GlobalVariable(name, module.get(), curDefType, false, initalizer);
        curScopes.addVarConstEntry(name, var);
    }
    else
    {
        // inConstExp++;
        visit(ctx->initVal());
        // inConstExp--;
        checkInitType();
        AllocaInst *varAlloca;
        varAlloca = builder->create_alloca(curDefType);
        curScopes.addVarConstEntry(name, varAlloca);
        builder->create_store(retValue, varAlloca);
    }
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitVarDefArrayInitVal(SysYParser::VarDefArrayInitValContext* ctx)
{
    auto name = ctx->initLVal()->Identifier()->getText();
    if(curScopes.inGlobalScope())
    {
        vector<int> dimensions;
        for(auto e : ctx->initLVal()->constExp())
        {
            visit(e);
            dimensions.push_back(dynamic_cast<ConstantInt*>(retValue)->value_);
        }
        vector<ArrayType*> arrayTys(dimensions.size());
        for(int i = dimensions.size() - 1; i>=0;i--)
        {
            if(i == dimensions.size() - 1)
            {
                arrayTys[i] = module->get_array_type(curDefType, dimensions[i]);
            }
            else
            {
                arrayTys[i] = module->get_array_type(arrayTys[i+1], dimensions[i]);
            }
        }
        auto* initValArray = dynamic_cast<SysYParser::InitValArrayContext*>(ctx->initVal());
        vector<SysYParser::InitValContext*> list;
        for(auto c : initValArray->initVal())
        {
            list.push_back(c);
        }
        // list.assign(initValArray->initVal().begin(), initValArray->initVal().end());
        if(list.size() == 0)
        {
            auto init = new ConstantZero(arrayTys[0]);
            auto var = new GlobalVariable(name, module.get(), arrayTys[0], false, init);
            curScopes.addVarConstEntry(name, var);
        }
        else
        {
            inConstExp++;//全局数组的初始值必为常量
            auto init = globalInit(dimensions, arrayTys, 0, list);
            inConstExp--;
            auto var = new GlobalVariable(name, module.get(), arrayTys[0], false, init);
            curScopes.addVarConstEntry(name, var);
        }
    }
    else
    {
        vector<int> dimensions( ctx->initLVal()->constExp().size() ), dimensionsCnt( ctx->initLVal()->constExp().size() );
        int totalByte = 1;
        for(int i = ctx->initLVal()->constExp().size() - 1;i>=0;i--)
        {
            visit(ctx->initLVal()->constExp()[i]);
            int dimension = dynamic_cast<ConstantInt*>(retValue)->value_;
            totalByte *= dimension;
            dimensions[i] = dimension;
            dimensionsCnt[i] = totalByte;
        }
        totalByte *= 4;
        ArrayType *arrayTy;
        for(int i = dimensions.size()-1; i>=0; i--)
        {
            if(i == dimensions.size() - 1)
            {
                arrayTy = module->get_array_type(curDefType, dimensions[i]);
            }
            else
            {
                arrayTy = module->get_array_type(arrayTy, dimensions[i]);
            }
        }
        auto arrayAlloc = builder->create_alloca(arrayTy);
        curScopes.addVarConstEntry(name, arrayAlloc);

        
        
        Value* i32P = builder->create_bitcast(arrayAlloc, INT32PTR_T);
        auto memclr = curScopes.lookupFunc("memclr");//从函数符号表中找到memclr(TODO: 添加memclr等函数)
        builder->create_call(memclr, {i32P, CONST_INT(totalByte)});
        
        auto* initValArray = dynamic_cast<SysYParser::InitValArrayContext*>(ctx->initVal());
        vector<SysYParser::InitValContext*> list;
        for(auto c : initValArray->initVal())
        {
            list.push_back(c);
        }
        // list.assign(initValArray->initVal().begin(), initValArray->initVal().end());
        if(list.size() == 0)
        {
            return nullptr;
        }
        vector<Value*> idxs(dimensions.size()+1);
        for(int i=0;i<dimensions.size()+1;i++)
        {
            idxs[i] = CONST_INT(0);
        }
        Value* ptr = builder->create_gep(arrayAlloc, idxs);//获取数组开头地址
        localInit(ptr, list, dimensionsCnt, 1);
        
    }

    return nullptr;
}
// antlrcpp::Any SysYIRGenerator::visitConstInitValSingle(SysYParser::ConstInitValSingleContext* ctx)
// {
//     inConstExp++;
//     visit(ctx->constExp());
//     inConstExp--;
//     return nullptr;
// }

antlrcpp::Any SysYIRGenerator::visitConstExp(SysYParser::ConstExpContext* ctx)
{
    inConstExp++;
    visit(ctx->addExp());
    inConstExp--;
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitAddExp(SysYParser::AddExpContext* ctx)
{
    
    // printf("visitAddExp\n");
    if(inConstExp)
    {
        // printf("visitConstAddExp\n");
        Value* val[2];//lVal, rVal，每次加完存到val[0]中，val[1]接受新的rVal
        int intVal[3]; //lInt, rInt, relInt;
        float floatVal[3]; // lFloat, rFloat, relFloat;
        visit(ctx->left);
        val[0] = retValue;
        
        for(int i=0;i<ctx->right.size();i++)
        {
            visit(ctx->right[i]);
            val[1] = retValue;
            bool resultIsInt = checkCalType(val, intVal, floatVal);
            if(ctx->op[i]->getText() == "+")
            {
                intVal[2] = intVal[0] + intVal[1];
                floatVal[2] = floatVal[0] + floatVal[1];
            }
            else
            {
                intVal[2] = intVal[0] - intVal[1];
                floatVal[2] = floatVal[0] - floatVal[1];
            }
            if(resultIsInt)
            {
                val[0] = CONST_INT(intVal[2]);
            }
            else
            {
                val[0] = CONST_FLOAT(floatVal[2]);
            }
        }
        retValue = val[0];
    }
    else
    {
        Value* val[2];//lVal, rVal
        visit(ctx->left);
        val[0] = retValue;
        // printf("AddExp111\n");
        for(int i=0;i<ctx->right.size();i++)
        {
            visit(ctx->right[i]);
            val[1] = retValue;
            checkCalType(val);
            if(val[0]->type_ == INT32_T)
            {
                if(ctx->op[i]->getText() == "+")
                {
                    val[0] = builder->create_iadd(val[0], val[1]);
                }
                else
                {
                    val[0] = builder->create_isub(val[0], val[1]);
                }
            }
            else
            {
                if(ctx->op[i]->getText() == "+")
                {
                    val[0] = builder->create_fadd(val[0], val[1]);
                }
                else
                {
                    val[0] = builder->create_fsub(val[0], val[1]);
                }
            }
        }
        retValue = val[0];

    }
    // printf("visitAddExp end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitMulExp(SysYParser::MulExpContext* ctx)
{
    // printf("visitMulExp\n");
    // PRINT_CURRENT_LINE_AND_COLUMN(ctx);
    if(inConstExp)
    {
        Value* val[2];//lVal, rVal，每次加完存到val[0]中，val[1]接受新的rVal
        int intVal[3]={1,1,1}; //lInt, rInt, relInt;设置初始值防止除数为0
        float floatVal[3]={1,1,1}; // lFloat, rFloat, relFloat;设置初始值防止除数为0
        visit(ctx->left);
        val[0] = retValue;
        
        for(int i=0;i<ctx->right.size();i++)
        {
            visit(ctx->right[i]);
            val[1] = retValue;
            bool resultIsInt = checkCalType(val, intVal, floatVal);
            if(ctx->op[i]->getText() == "*")
            {
                intVal[2] = intVal[0] * intVal[1];
                floatVal[2] = floatVal[0] * floatVal[1];
            }
            else if(ctx->op[i]->getText() == "/")
            {
                // printf("/\n");
                intVal[2] = intVal[0] / intVal[1];
                floatVal[2] = floatVal[0] / floatVal[1];
                // printf("resultIsInt:%d floatVal[2]: %f floatval[0]: %f floatval[1]:%f\n", resultIsInt, floatVal[2],floatVal[0], floatVal[1]);
            }
            else
            {
                intVal[2] = intVal[0] % intVal[1];
            }
            if(resultIsInt)
            {
                val[0] = CONST_INT(intVal[2]);
            }
            else
            {
                val[0] = CONST_FLOAT(floatVal[2]);
            }
        }
        retValue = val[0];
    }
    else
    {
        Value* val[2];
        visit(ctx->left);
        val[0] = retValue;
        for(int i=0;i<ctx->right.size();i++)
        {
            visit(ctx->right[i]);
            val[1] = retValue;
            checkCalType(val);
            if(val[0]->type_ == INT32_T)
            {
                if(ctx->op[i]->getText() == "*")
                {
                    val[0] = builder->create_imul(val[0], val[1]);
                }
                else if(ctx->op[i]->getText() == "/")
                {
                    val[0] = builder->create_isdiv(val[0], val[1]);
                }
                else
                {
                    val[0] = builder->create_isrem(val[0], val[1]);
                }
            }
            else
            {
                if(ctx->op[i]->getText() == "*")
                {
                    val[0] = builder->create_fmul(val[0], val[1]);
                }
                else if(ctx->op[i]->getText() == "/")
                {
                    val[0] = builder->create_fdiv(val[0], val[1]);
                }
            }
        }
        retValue = val[0];
    }
    // printf("visitMulExp end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitUnaryExpUnary(SysYParser::UnaryExpUnaryContext* ctx)
{
    if(inConstExp)
    {
        visit(ctx->unaryExp());
        if(ctx->unaryOp()->getText() == "+")
        {
            //无需改变retValue的值
        }
        else if(ctx->unaryOp()->getText() == "-")
        {
            if(dynamic_cast<ConstantInt*>(retValue))
            {
                auto temp = (ConstantInt*)retValue;
                temp->value_ = -temp->value_;
                retValue = temp;
            }
            else
            {
                auto temp = (ConstantFloat*)retValue;
                temp->value_ = -temp->value_;
                retValue = temp;
            }
        }
        else
        {
            REPORT_SEMANTIC_ERROR_AND_EXIT("Logical NOT operator cannot be applied to int/float expressions", ctx);
        }
    }
    else
    {
        visit(ctx->unaryExp());
        if(retValue->type_ == VOID_T)
        {
            return nullptr;
        }
        else if(retValue->type_ == INT1_T)
        {
            retValue = builder->create_zext(retValue, INT32_T);
        }

        if(retValue->type_ == INT32_T)
        {
            if(ctx->unaryOp()->getText() == "+")
            {
                //无需改变retValue
            }
            else if(ctx->unaryOp()->getText() == "-")
            {
                retValue = builder->create_isub(CONST_INT(0), retValue);
            }
            else if(ctx->unaryOp()->getText() == "!")
            {
                retValue = builder->create_icmp_eq(retValue, CONST_INT(0));
            }
            
        }
        else
        {
            if(ctx->unaryOp()->getText() == "+")
            {
                //无需改变retValue
            }
            else if(ctx->unaryOp()->getText() == "-")
            {
                retValue = builder->create_fsub(CONST_FLOAT(0), retValue);
            }
            else if(ctx->unaryOp()->getText() == "!")
            {
                retValue = builder->create_fcmp_eq(retValue, CONST_FLOAT(0));
            }
        }
    }
    
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitNumber(SysYParser::NumberContext* ctx)
{
    // printf("visitNumber\n");
    // if(inConstExp)
    // {
    if(ctx->intConst()!=nullptr)
    {
        // printf("text: %s\nint:%d\n",ctx->intConst()->getText().c_str(),std::stoi(ctx->intConst()->getText(), nullptr, 0));
        retValue = CONST_INT(std::stoi(ctx->intConst()->getText(), nullptr, 0));//base设置为0，根据前缀自动判断基数
    }
    else
    {
        retValue = CONST_FLOAT(std::stof(ctx->floatConst()->getText()));
        // std::cout << "retValue: " << retValue->print() << std::endl;
    }
    // }
    // printf("visitNumber end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitLValSingle(SysYParser::LValSingleContext* ctx)
{
    
    // printf("visitLValSingle\n");

    bool isTrueLVal = requireLVal; //是否真的作为左值
    requireLVal = false;
    auto name = ctx->Identifier()->getText();
    if(curScopes.inGlobalScope())
    {
        auto var = curScopes.lookupVarConst(name);
        retValue = var;
    }
    else
    {
        auto var = curScopes.lookupVarConst(name);
        if(var->type_->tid_ == Type::IntegerTyID || var->type_->tid_ == Type::FloatTyID)//是局部常量，直接返回
        {
            retValue = var;
            return nullptr;
        }
        Type* varType = static_cast<PointerType*>(var->type_)->contained_;
        if(varType->tid_ == Type::ArrayTyID)//传数组参
        {
            retValue = builder->create_gep(var,{CONST_INT(0), CONST_INT(0)});
        }
        else if(!isTrueLVal)//不是真左值，就load
        {
            retValue = builder->create_load(var);
        }
        else//是真左值，返回地址
        {
            retValue = var;
        }
    }
    // printf("visitLValSingle end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitLValArray(SysYParser::LValArrayContext* ctx)
{
    // printf("visitLValArray\n");
    bool isTrueLVal = requireLVal; //是否真的作为左值
    requireLVal = false;
    auto name = ctx->Identifier()->getText();
    if(curScopes.inGlobalScope())//在全局作用域中，左值一定是常量
    {
        vector<int> index;
        for(auto &exp : ctx->exp())
        {
            visit(exp);
            index.push_back(dynamic_cast<ConstantInt*>(retValue)->value_);
        }
        auto var = curScopes.lookupVarConst(name);
        retValue = ((GlobalVariable *)var)->init_val_; //用初始值表查找常量数组元素
        for(int i : index)
        {
            if(dynamic_cast<ConstantZero*>(retValue))
            {
                Type* arrayTy = retValue->type_;
                //找数组元素标签
                while (dynamic_cast<ArrayType*>(arrayTy)) {
                    arrayTy = dynamic_cast<ArrayType*>(arrayTy)->contained_;
                }
                if (arrayTy == INT32_T) retValue = CONST_INT(0);
                else retValue = CONST_FLOAT(0);
                return nullptr;
            }
            if(dynamic_cast<ConstantArray*>(retValue))
            {
                retValue = ((ConstantArray*)retValue)->const_array[i];
            }
        }
        // return nullptr;
    }
    else
    {
        auto var = curScopes.lookupVarConst(name);
        
        Type* varType = static_cast<PointerType*>(var->type_)->contained_;
        vector<Value *> idxs;
        for(auto &exp : ctx->exp())
        {
            visit(exp);
            idxs.push_back(retValue);
        }
        if(varType->tid_ == Type::PointerTyID)
        {
            var = builder->create_load(var);
        }
        else if(varType->tid_ == Type::ArrayTyID)
        {
            idxs.insert(idxs.begin(), CONST_INT(0));
        }
        var = builder->create_gep(var, idxs);
        varType = ((PointerType*)var->type_)->contained_;

        if(varType->tid_ == Type::ArrayTyID)//传数组参
        {
            retValue = builder->create_gep(var, {CONST_INT(0), CONST_INT(0)});
        }
        else if(!isTrueLVal)//不是真左值，就load
        {
            retValue = builder->create_load(var);
        }
        else//是真左值，返回地址
        {
            retValue = var;
        }
    }
    
    
    // printf("visitLValArray end\n");
    
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitRelExp(SysYParser::RelExpContext* ctx)
{
    // printf("visitRelExp\n");
    Value* val[2];
    visit(ctx->left);
    val[0] = retValue;
    for(int i=0;i<ctx->right.size();i++)
    {
        visit(ctx->right[i]);
        val[1] = retValue;
        checkCalType(val);
        if(val[0]->type_ == INT32_T)
        {
            if(ctx->op[i]->getText() == "<")
            {
                val[0] = builder->create_icmp_lt(val[0], val[1]);
            }
            else if(ctx->op[i]->getText() == "<=")
            {
                val[0] = builder->create_icmp_le(val[0], val[1]);
            }
            else if(ctx->op[i]->getText() == ">")
            {
                val[0] = builder->create_icmp_gt(val[0], val[1]);
            }
            else
            {
                val[0] = builder->create_icmp_ge(val[0], val[1]);
            }
        }
        else
        {
            if(ctx->op[i]->getText() == "<")
            {
                val[0] = builder->create_fcmp_lt(val[0], val[1]);
            }
            else if(ctx->op[i]->getText() == "<=")
            {
                val[0] = builder->create_fcmp_le(val[0], val[1]);
            }
            else if(ctx->op[i]->getText() == ">")
            {
                val[0] = builder->create_fcmp_gt(val[0], val[1]);
            }
            else
            {
                val[0] = builder->create_fcmp_ge(val[0], val[1]);
            }
        }
    }
    retValue = val[0];
    // printf("visitRelExp end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitEqExp(SysYParser::EqExpContext* ctx)
{
    // printf("visitEqExp\n");
    Value* val[2];
    visit(ctx->left);
    val[0] = retValue;
    for(int i=0;i<ctx->right.size();i++)
    {
        visit(ctx->right[i]);
        val[1] = retValue;
        checkCalType(val);
        if(val[0]->type_ == INT32_T)
        {
            if(ctx->op[i]->getText() == "==")
            {
                val[0] = builder->create_icmp_eq(val[0], val[1]);
            }
            else
            {
                val[0] = builder->create_icmp_ne(val[0], val[1]);
            }
        }
        else
        {
            if(ctx->op[i]->getText() == "==")
            {
                val[0] = builder->create_fcmp_eq(val[0], val[1]);
            }
            else
            {
                val[0] = builder->create_fcmp_ne(val[0], val[1]);
            }
        }
    }
    retValue = val[0];
    // printf("visitEqExp end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitLAndExp(SysYParser::LAndExpContext* ctx)
{
    // printf("visitLAndExp\n");
    auto tempTrue = trueBB;

    // trueBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    // visit(ctx->left);
    
    // // trueBB = new BasicBlock(module.get(), to_string(id++), currentFunction);
    // for(int i=0;i<ctx->right.size();i++)
    // {
    //     if(retValue->type_ == INT32_T)
    //     {
    //         retValue = builder->create_icmp_ne(retValue, CONST_INT(0));
    //     }
    //     else if(retValue->type_ == FLOAT_T)
    //     {
    //         retValue = builder->create_fcmp_ne(retValue, CONST_FLOAT(0));
    //     }
    //     // trueBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    //     builder->create_cond_br(retValue, trueBB, falseBB);
    //     builder->BB_ = trueBB;
    //     has_br = false;

    //     trueBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    //     visit(ctx->right[i]);
        
    // }

    for(int i=0;i<ctx->eqExp().size()-1;i++)
    {
        trueBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
        visit(ctx->eqExp()[i]);
        if(retValue->type_ == INT32_T)
        {
            retValue = builder->create_icmp_ne(retValue, CONST_INT(0));
        }
        else if(retValue->type_ == FLOAT_T)
        {
            retValue = builder->create_fcmp_ne(retValue, CONST_FLOAT(0));
        }
        builder->create_cond_br(retValue, trueBB, falseBB);
        builder->BB_ = trueBB;
        has_br = false;
    }

    trueBB = tempTrue;

    visit(ctx->eqExp()[ctx->eqExp().size()-1]);

    // printf("visitLAndExp end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitLOrExp(SysYParser::LOrExpContext* ctx)
{
    // printf("visitLOrExp\n");
    auto tempFalse = falseBB;

    // falseBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    // visit(ctx->left);
    // for(int i=0;i<ctx->right.size();i++)
    // {
    //     if(retValue->type_ == INT32_T)
    //     {
    //         retValue = builder->create_icmp_ne(retValue, CONST_INT(0));
    //     }
    //     else if(retValue->type_ == FLOAT_T)
    //     {
    //         retValue = builder->create_fcmp_ne(retValue, CONST_FLOAT(0));
    //     }
    //     // falseBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    //     builder->create_cond_br(retValue, trueBB, falseBB);
    //     printf("lor create_cond_br trueBB: %s  falseBB: %d\n",trueBB->name_, id-1);
    //     builder->BB_ = falseBB;
    //     has_br = false;

    //     falseBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    //     visit(ctx->right[i]);
    // }

    for(int i=0;i<ctx->lAndExp().size()-1;i++)
    {
        falseBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
        visit(ctx->lAndExp()[i]);
        if(retValue->type_ == INT32_T)
        {
            retValue = builder->create_icmp_ne(retValue, CONST_INT(0));
        }
        else if(retValue->type_ == FLOAT_T)
        {
            retValue = builder->create_fcmp_ne(retValue, CONST_FLOAT(0));
        }
        builder->create_cond_br(retValue, trueBB, falseBB);
        builder->BB_ = falseBB;
        has_br = false;
    }
    falseBB = tempFalse;
    visit(ctx->lAndExp()[ctx->lAndExp().size()-1]);

    // printf("visitLOrExp end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitFuncDef(SysYParser::FuncDefContext* ctx)
{
    // printf("visitFuncDef\n");
    params.clear();
    paramNames.clear();
    Type *retType;
    if(ctx->funcType()->getText() == "void")
    {
        retType = VOID_T;
    }
    else if(ctx->funcType()->getText() == "int")
    {
        retType = INT32_T;
    }
    else
    {
        retType = FLOAT_T;
    }
    // printf("funcdef111\n");
    if(ctx->funcFParams() != nullptr)
    {
        for(auto param : ctx->funcFParams()->funcFParam())
        {
            visit(param);
        }
    }
    // printf("finished visiting params.\n");
    auto funTy = new FunctionType(retType, params);
    auto func = new Function(funTy, ctx->Identifier()->getText(), module.get());

    currentFunction = func;
    curScopes.addFuncEntry(ctx->Identifier()->getText(), func);
    curScopes.enter();

    std::vector<Value *> args;
    for(auto arg = func->arguments_.begin(); arg != func->arguments_.end(); arg++)
    {
        args.push_back(*arg);
    }

    auto bb = new BasicBlock(module.get(), "label_entry", func);
    builder->BB_ = bb;
    for(int i=0;i < (int)(paramNames.size());i++)
    {
        auto alloc = builder->create_alloca(params[i]);  //分配形参空间
        builder->create_store(args[i], alloc);   //store形参
        curScopes.addVarConstEntry(paramNames[i], alloc);  //加入作用域
    }

    retBB = new BasicBlock(module.get(), "label_ret", func);
    if(retType == VOID_T)
    {
        builder->BB_ = retBB;
        builder->create_void_ret();
    }
    else
    {
        retAlloca = builder->create_alloca(retType); //在内存中分配返回值的位置
        builder->BB_ = retBB;
        auto retLoad = builder->create_load(retAlloca);
        builder->create_ret(retLoad);
    }
    //重新回到函数开始
    builder->BB_ = bb;
    has_br = false;
    visit(ctx->block());

    if(!builder->BB_->get_terminator())
    {
        builder->create_br(retBB);
    }

    curScopes.exit();


    return nullptr;
}
antlrcpp::Any SysYIRGenerator::visitFuncFParamSingle(SysYParser::FuncFParamSingleContext* ctx)
{
    // printf("visitFuncFParamSingle\n");
    Type *paramType;
    if(ctx->bType()->getText() == "int")
    {
        paramType = INT32_T;
    }
    else
    {
        paramType = FLOAT_T;
    }
    params.push_back(paramType);
    paramNames.push_back(ctx->Identifier()->getText());
    // printf("visitFuncFparamSingle end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitFuncFParamArray(SysYParser::FuncFParamArrayContext* ctx)
{
    // printf("visitFuncFParamArray\n");
    Type *paramType;
    if(ctx->bType()->getText() == "int")
    {
        paramType = INT32_T;
    }
    else
    {
        paramType = FLOAT_T;
    }
    for(int i = ctx->exp().size()-1; i>=0; i--)
    {
        inConstExp++;
        visit(ctx->exp()[i]);
        inConstExp--;
        paramType = module->get_array_type(paramType, ((ConstantInt *)retValue)->value_);
    }
    paramType = module->get_pointer_type(paramType);
    params.push_back(paramType);
    paramNames.push_back(ctx->Identifier()->getText());
    // printf("visitFuncFParamArray end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitUnaryExpFuncR(SysYParser::UnaryExpFuncRContext* ctx)
{
    // printf("visitUnaryExpFuncR\n");

    //处理starttime()和stoptime()，模拟sylib.h里的#define
    if(ctx->Identifier()->getText() == "starttime" || ctx->Identifier()->getText() == "stoptime")
    {
        if(ctx->Identifier()->getText() == "starttime")
        {
            auto fun = (Function *)curScopes.lookupFunc("_sysy_starttime");
            if(fun->basic_blocks_.size() && !is_single_exp)
            {
                fun->use_ret_cnt ++;
            }
            is_single_exp = false;
            vector<Value *> args;
            args.push_back(CONST_INT(CURRENT_LINE(ctx)));
            retValue = builder->create_call(fun, args);
            return nullptr;
        }
        else
        {
            auto fun = (Function *)curScopes.lookupFunc("_sysy_stoptime");
            if(fun->basic_blocks_.size() && !is_single_exp)
            {
                fun->use_ret_cnt ++;
            }
            is_single_exp = false;
            vector<Value *> args;
            args.push_back(CONST_INT(CURRENT_LINE(ctx)));
            retValue = builder->create_call(fun, args);
            return nullptr;
        }
    }
    
    auto fun = (Function *)curScopes.lookupFunc(ctx->Identifier()->getText());
    if(fun->basic_blocks_.size() && !is_single_exp)
    {
        fun->use_ret_cnt ++;
    }
    is_single_exp = false;
    vector<Value *> args;

    if(ctx->funcRParams()!= nullptr)
    {
        for(int i = 0; i < ctx->funcRParams()->funcRParam().size(); i++)
        {
            visit(ctx->funcRParams()->funcRParam()[i]);

            //在语义检查器中取消了对函数参数类型是否匹配的检查，因此此处需要做转换
            if(retValue->type_ == INT32_T && fun->arguments_[i]->type_ == FLOAT_T)
            {
                retValue = builder->create_sitofp(retValue, FLOAT_T);
            }
            else if(retValue->type_ == FLOAT_T && fun->arguments_[i]->type_ == INT32_T)
            {
                retValue = builder->create_fptosi(retValue, INT32_T);
            }
            
            args.push_back(retValue);
        }
    }
    
    retValue = builder->create_call(fun, args);
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtAssign(SysYParser::StmtAssignContext* ctx)
{
    // printf("visitStmtAssign\n");
    requireLVal = true;
    visit(ctx->lVal());
    auto lVal = retValue;
    auto lValType = static_cast<PointerType*>(lVal->type_)->contained_;
    visit(ctx->exp());
    auto rVal = retValue;

    if(lValType != retValue->type_)
    {
        if(lValType == FLOAT_T)
        {
            rVal = builder->create_sitofp(rVal, FLOAT_T);
        }
        else
        {
            rVal = builder->create_fptosi(rVal, INT32_T);
        }
    }
    //创建store指令，实现赋值
    builder->create_store(rVal, lVal);
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtExp(SysYParser::StmtExpContext* ctx)
{
    // printf("visitStmtExp\n");
    is_single_exp = true;
    if(ctx->exp() != nullptr)
    {
        visit(ctx->exp());
    }
    is_single_exp = false;
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtBreak(SysYParser::StmtBreakContext* ctx)
{
    // printf("visitStmtBreak\n");
    builder->create_br(whileFalseBB);
    has_br = true;
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtContinue(SysYParser::StmtContinueContext* ctx)
{
    // printf("visitStmtContinue\n");
    builder->create_br(whileCondBB);
    has_br = true;
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtReturn(SysYParser::StmtReturnContext* ctx)
{
    // printf("visitStmtReturn\n");
    if(ctx->exp() == nullptr)
    {
        retValue = builder->create_br(retBB);
    }
    else
    {
        visit(ctx->exp());
        // printf("return111\n");
        if(retValue->type_ == FLOAT_T && currentFunction->get_return_type() == INT32_T)
        {
            auto temp = builder->create_fptosi(retValue, INT32_T);
            builder->create_store(temp, retAlloca);
        }
        else if(retValue->type_ == INT32_T && currentFunction->get_return_type() == FLOAT_T)
        {
            auto temp = builder->create_sitofp(retValue, FLOAT_T);
            builder->create_store(temp, retAlloca);
        }
        else
        {
            builder->create_store(retValue, retAlloca);
        }
        // printf("return222\n");
        retValue = builder->create_br(retBB);
    }
    has_br = true;
    
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtCond(SysYParser::StmtCondContext* ctx)
{
    // printf("visitStmtCond\n");
    auto tempTrue = trueBB;
    auto tempFalse = falseBB;

    trueBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    falseBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);

    BasicBlock* nextIf; //if语句后的基本块
    if(ctx->stmt().size() == 1)
    {
        nextIf = falseBB;
    }
    else
    {
        nextIf = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    }
    visit(ctx->cond());
    if(retValue->type_ == INT32_T)
    {
        retValue = builder->create_icmp_ne(retValue, CONST_INT(0));
    }
    else if(retValue->type_ == FLOAT_T)
    {
        retValue = builder->create_fcmp_ne(retValue, CONST_FLOAT(0));
    }
    builder->create_cond_br(retValue, trueBB, falseBB);

    builder->BB_ = trueBB;
    has_br = false;
    visit(ctx->stmt()[0]);
    if(!builder->BB_->get_terminator())
    {
        builder->create_br(nextIf);
    }

    if(ctx->stmt().size() == 2)
    {
        builder->BB_ = falseBB;
        has_br = false;
        visit(ctx->stmt()[1]);
        if(!builder->BB_->get_terminator())
        {
            builder->create_br(nextIf);
        }
    }
    
    builder->BB_ = nextIf;
    has_br = false;
    trueBB = tempTrue;
    falseBB = tempFalse;
    
    // printf("visitStmtCond end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtWhile(SysYParser::StmtWhileContext* ctx)
{
    // printf("visitStmtWhile\n");
    auto tempTrue = trueBB;
    auto tempFalse = falseBB;
    auto tempCond = whileCondBB;
    auto tempWhileFalse = whileFalseBB;

    whileCondBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    trueBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    falseBB = new BasicBlock(module.get(), std::__cxx11::to_string(id++), currentFunction);
    whileFalseBB = falseBB;

    builder->create_br(whileCondBB);
    builder->BB_ = whileCondBB;  //条件也是一个基本块
    has_br = false;
    visit(ctx->cond());
    // printf("visitStmtWhile1111\n");
    if(retValue->type_ == INT32_T)
    {
        retValue = builder->create_icmp_ne(retValue, CONST_INT(0));
    }
    else if(retValue->type_ == FLOAT_T)
    {
        retValue = builder->create_fcmp_ne(retValue, CONST_FLOAT(0));
    }
    builder->create_cond_br(retValue, trueBB, falseBB);
    // printf("visitStmtWhile2222\n");
    builder->BB_ = trueBB;
    has_br = false;
    visit(ctx->stmt());
    
    if(!builder->BB_->get_terminator())
    {
        builder->create_br(whileCondBB);
    }

    
    builder->BB_ = whileFalseBB;
    has_br = false;


    //还原trueBB，falseBB，whileCondBB，whileFalseBB
    trueBB = tempTrue;
    falseBB = tempFalse;
    whileCondBB = tempCond;
    whileFalseBB = tempWhileFalse;
    
    // printf("visitStmtWhile end\n");
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitStmtBlock(SysYParser::StmtBlockContext* ctx)
{
    // printf("visitStmtBlock\n");
    curScopes.enter();
    visit(ctx->block());
    curScopes.exit();
    return nullptr;
}

antlrcpp::Any SysYIRGenerator::visitBlock(SysYParser::BlockContext* ctx)
{
    // printf("visitBlock\n");
    for(auto &item : ctx->blockItem())
    {
        if(has_br) break;
        visit(item);
    }
    return nullptr;
}