#pragma once

#include <iostream>
#include <sstream>
#include <variant>
#include <memory>
#include <vector>

#include "Function.h"
#include "../utils/Utils.h"

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

    enum class ValueType
    {
        Int, Array, Void
    };

    class Value
    {
    public:
        Value() :
            name("_"), type(ValueType::Void) {}
        Value(const std::string &name, ValueType type, bool isConst) :
            name(name), type(type), isConst(isConst) {}
        std::string ident() const;
        virtual std::string toStr() const { return "[Null value]"; }

    public:
        std::string name;
        ValueType type;
        bool isConst;
        FuncPtr parent;
    };

    typedef std::shared_ptr<Value> ValuePtr;

    const ValuePtr NullValue = makePtr<Value>();

    class IntValue : public Value
    {
    public:
        IntValue(const std::string &name) :
            Value(name, ValueType::Int, false) {}
        IntValue(const std::string &name, int val, bool isConst) :
            val(val), Value(name, ValueType::Int, isConst) {}
        std::string toStr() const override;

    public:
        int val = 0;
    };

    class ArrValue : public Value
    {
    public:
        ArrValue(const std::string &name, int size) :
            size(size), Value(name, ValueType::Array, false) {}
        ArrValue(const std::string &name, const std::vector<int> &val, bool isConst) :
            size(val.size()), val(val), Value(name, ValueType::Array, isConst) {}
        std::string toStr() const override;

    public:
        int size;
        std::vector<int> val;
    };
}