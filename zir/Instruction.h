#pragma once

#include <iostream>
#include <memory>

#include "Value.h"
#include "Block.h"
#include "Function.h"

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

    enum class InstrType
    {
        Op = 0, Brc, Jmp, Call, Ret, Phi, Mem
    };

    enum class OpType
    {
        Add = 0, Sub, Mul, Div, Neg, And, Or, Xor, Not,
        Shl, Lsr, Asr
    };

    enum class CmpOp
    {
        Eq = 0, Ne, Gt, Ls, Ge, Le
    };

    std::string opTypeToString(OpType type);
    std::string cmpOpToString(CmpOp op);

    class Instruction
    {
    public:
        Instruction(InstrType type) :
            type(type) {}
        virtual std::string toString() const = 0;

    public:
        BlockPtr parent;
        InstrType type;
    };

    typedef std::shared_ptr<Instruction> InstrPtr;

    class OpInstr : public Instruction
    {
    public:
        OpInstr(ValuePtr dest, const std::vector<ValuePtr> &params, OpType opType) :
            dest(dest), params(params), opType(opType), Instruction(InstrType::Op) {}
        std::string toString() const;

    public:
        ValuePtr dest;
        std::vector<ValuePtr> params;
        OpType opType;
    };

    class BranchInstr : public Instruction
    {
    public:
        BranchInstr(ValuePtr a, ValuePtr b, CmpOp cmpOp, BlockPtr dTrue, BlockPtr dFalse) :
            a(a), b(b), cmpOp(cmpOp), dTrue(dTrue), dFalse(dFalse), Instruction(InstrType::Brc) {}
        std::string toString() const;

    public:
        ValuePtr a, b;
        CmpOp cmpOp;
        BlockPtr dTrue, dFalse;
    };

    class JmpInstr : public Instruction
    {
    public:
        JmpInstr(BlockPtr dest) :
            dest(dest), Instruction(InstrType::Jmp) {}
        std::string toString() const;

    public:
        BlockPtr dest;
    };

    class CallInstr : public Instruction
    {
    public:
        CallInstr(ValuePtr ret, FuncPtr callee, const std::vector<ValuePtr> &params) :
            ret(ret), callee(callee), params(params), Instruction(InstrType::Call) {}
        std::string toString() const;

    public:
        ValuePtr ret;
        FuncPtr callee;
        std::vector<ValuePtr> params;
    };

    class RetInstr : public Instruction
    {
    public:
        RetInstr(ValuePtr ret) :
            ret(ret), Instruction(InstrType::Ret) {}
        std::string toString() const;

    public:
        ValuePtr ret;
    };

    class PhiInstr : public Instruction
    {
    public:
        PhiInstr(ValuePtr dest, const std::vector<ValuePtr> &params) :
            dest(dest), params(params), Instruction(InstrType::Phi) {}
        std::string toString() const;

    public:
        ValuePtr dest;
        std::vector<ValuePtr> params;
    };

    class MemInstr : public Instruction
    {
    public:
        MemInstr(ValuePtr reg, ValuePtr mem, int offset, bool isLoad) :
            reg(reg), mem(mem), offset(offset), isLoad(isLoad), Instruction(InstrType::Mem) {}
        std::string toString() const;

    public:
        ValuePtr reg, mem;
        // by word
        int offset;
        bool isLoad;
    };
}