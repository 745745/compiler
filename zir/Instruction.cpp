#include "Instruction.h"

namespace ZIR
{
    const std::string OpTypeStrings[] =
    {
        "add", "sub", "mul", "div", "neg", "and", "or", "xor", "not",
        "shl", "lsr", "asr"
    };

    const std::string CmpOpStrings[] =
    {
        "eq", "ne", "gt", "ls", "ge", "le"
    };

    std::string opTypeToString(OpType type)
    {
        return OpTypeStrings[static_cast<int>(type)];
    }

    std::string cmpOpToString(CmpOp op)
    {
        return CmpOpStrings[static_cast<int>(op)];
    }

    std::string OpInstr::toString() const
    {
        std::stringstream ss;
        ss << dest->ident() << " = " << opTypeToString(opType);
        for (auto i : params)
            ss << " " << i->ident();
        return ss.str();
    }

    std::string BranchInstr::toString() const
    {
        return "brc(" + a->ident() + " " +
            cmpOpToString(cmpOp) + " " + b->ident() + ") ? " +
            dTrue->name() + " : " + dFalse->name();
    }

    std::string JmpInstr::toString() const
    {
        return "jmp " + dest->name();
    }

    std::string CallInstr::toString() const
    {
        std::stringstream ss;
        ss << ret->ident() << " = call " << callee->name << " ";
        for (auto i : params)
            ss << " " << i->ident();
        return ss.str();
    }

    std::string RetInstr::toString() const
    {
        return "ret " + ret->ident();
    }

    std::string PhiInstr::toString() const
    {
        std::stringstream ss;
        ss << dest->ident() << " = phi";
        for (auto i : params)
            ss << " " << i->ident();
        return ss.str();
    }

    std::string MemInstr::toString() const
    {
        std::stringstream ss;
        if (isLoad)
            ss << reg->ident() << " = " << mem->ident() << "[" << offset << "]";
        else
            ss << mem->ident() << "[" << offset << "] = " << reg->ident();
        return ss.str();
    }
}