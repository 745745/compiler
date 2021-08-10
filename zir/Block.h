#pragma once

#include <vector>
#include <set>

#include "Function.h"
#include "Instruction.h"

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

    class Block
    {
    public:
        std::string name() const { return "#" + std::to_string(num); }

    public:
        int num;
        FuncPtr parent;
        std::vector<InstrPtr> instrs;

        std::vector<BlockPtr> pred;
        std::vector<BlockPtr> succ;
        BlockPtr idom;
        std::vector<BlockPtr> domF;
        std::vector<BlockPtr> domTreeSucc;
        int postOrderNum;

        std::set<ValuePtr> ueVar;
        std::set<ValuePtr> killSet;
        std::set<ValuePtr> liveIn;
        std::set<ValuePtr> liveOut;

        std::set<ValuePtr> phiedVar;
    };
}