#pragma once

#include "Block.h"
#include "Module.h"
#include "Value.h"

namespace ZIR
{
    class Block;
    class Value;
    class Module;
    class Function;
    class Instruction;
    typedef std::shared_ptr<Block> BlockPtr;
    typedef std::shared_ptr<Value> ValuePtr;
    typedef std::shared_ptr<Module> ModulePtr;
    typedef std::shared_ptr<Function> FuncPtr;
    typedef std::shared_ptr<Instruction> InstrPtr;
    enum class ValueType;

    class Function
    {
    public:
        Function(const std::string &name, ValueType retType) :
            name(name), retType(retType) {}

        void generate(NFuncDecl *decl);
        void print();

    public:
        std::string name;
        ValueType retType;
        ModulePtr parent;

        std::vector<ValuePtr> params;

        std::vector<InstrPtr> instrs;
        std::vector<BlockPtr> blocks;
        BlockPtr entry, exit;

        std::vector<FuncPtr> callees;
        std::vector<ValuePtr> values;
    };
}