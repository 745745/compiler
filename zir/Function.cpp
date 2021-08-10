#include "Function.h"

namespace ZIR
{
    void Function::generate(NFuncDecl *decl)
    {
        for (auto param : decl->parameters)
        {
            std::cout << param->lengths.size() << " " << param->isArray << " " << param->size << "\n";
            auto name = param->identifier.name;

            ValuePtr p;
            if (param->isArray)
                p = makePtr<ArrValue>(name, getArrDimProduct(param));
            else
                p = makePtr<IntValue>(name);

            params.push_back(p);
        }

        for (auto st : decl->statements)
        {
        }
    }

    void Function::print()
    {
        std::cout << "[Function " << name << "]\n";
        std::cout << "\t[RetType " << (retType == ValueType::Int ? "int" : "void") << "]\n";
        std::cout << "\t[Params]\n";
        for (auto i : params)
            std::cout << "\t\t" << i->toStr() << "\n";
    }
}