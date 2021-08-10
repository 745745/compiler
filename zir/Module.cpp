#include "Module.h"

namespace ZIR
{
    ValueType getTypeFromStr(const std::string &type)
    {
        return (type == "int") ?
            ValueType::Int : (type == "void") ?
                ValueType::Void :
                ValueType::Array;
    }

    void Module::translate()
    {
        //ast->Print();

        for (auto decl : ast->declarations)
        {
            if (typeid(*decl) == typeid(NVarDecl))
                addGlobalValue(dynamic_cast<NVarDecl*>(decl));
            else if (typeid(*decl) == typeid(NFuncDecl))
                addFunction(dynamic_cast<NFuncDecl*>(decl));
        }
        printGlobalVars();
    }

    void Module::generateAsm()
    {
        std::ofstream file(outFilePath);

        // TODO: get asm string from AsmTranslator
        std::string asmString = "AAA\n";
        file << asmString;
        std::cout << asmString;

        file.close();
    }

    void Module::printGlobalVars()
    {
        std::cout << "Global Vars:\n";
        for (auto v : globalVars)
        {
            std::cout << "\t" << v->toStr() << "\n";
        }
    }

    void Module::addGlobalValue(NVarDecl *varDecl)
    {
        auto name = varDecl->identifier.name;
        ValuePtr val;

        if (varDecl->isArray)
        {
            int size = getArrDimProduct(varDecl);
            val = (varDecl->finalInitValue != nullptr) ?
                makePtr<ArrValue>(name, *varDecl->finalInitValue, varDecl->isconst) :
                makePtr<ArrValue>(name, size);
        }
        else
        {
            val = varDecl->init ?
                makePtr<IntValue>(name, varDecl->initvalue->GetValue(), varDecl->isconst) :
                makePtr<IntValue>(name);
        }
        globalVars.push_back(val);
    }

    void Module::addFunction(NFuncDecl *funcDecl)
    {
        auto name = funcDecl->function_name.name;
        auto retType = getTypeFromStr(funcDecl->type);

        auto func = makePtr<Function>(name, retType);
        func->generate(funcDecl);

        func->parent = makePtr<Module>(*this);
        func->print();
        functions.push_back(func);
    }
}