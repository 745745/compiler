#include "AsmInstruction.h"

namespace Assembly
{
    std::string getRegName(int reg)
    {
        if (reg < 0 || reg > 15)
        {
            Error::exit("Assembly::getRegName: Reg id out of range");
        }
        return REG_NAME[reg];
    }

    std::string getCondCode(Condition cond)
    {
        return COND_CODE[static_cast<int>(cond)];
    }

    std::string getShiftCode(ShiftType shft)
    {
        return INSTR_CODE[static_cast<int>(shft)];
    }

    std::string getInstrCode(InstrType instr)
    {
        return INSTR_CODE[static_cast<int>(instr)];
    }

    std::string getAutoIncCode(AutoIncType inc)
    {
        return AUTO_INC_CODE[static_cast<int>(inc)];
    }

    Imm8m::Imm8m(uint32_t val) : val(val)
    {
        testValid(val);
    }

    bool Imm8m::isValid(uint32_t val)
    {
        int lZeros = 0;
        int rZeros = 0;
        int mZeros = 0;

        for (int i = 0; i < 32; i++)
        {
            if (val & (1 << i)) break;
            lZeros++;
        }

        for (int i = 31; i >= 0; i--)
        {
            if (val & (1 << i)) break;
            rZeros++;
        }

        int tmp = 0;
        for (int i = 0; i < 32; i++)
        {
            if (val & (1 << i))
            {
                mZeros = std::max(mZeros, tmp);
                tmp = 0;
                continue;
            }
            tmp++;
        }
        return std::max(mZeros, lZeros + rZeros) >= 24;
    }

    void Imm8m::testValid(uint32_t val)
    {
        if (!isValid(val))
        {
            Error::exit("Assembly::Imm8m: invalid value");
        }
    }

    std::string Imm8m::toString() const
    {
        return "#" + std::to_string(val);
    }

    std::vector<Imm8m> Imm8m::exclusiveSplit(uint32_t val)
    {
        // TODO: find the best split
        uint64_t extVal = static_cast<uint64_t>(val) << 32 | val;
        std::vector<Imm8m> ret;
        ret.push_back(val & 0x000000ff);
        ret.push_back(val & 0x0000ff00);
        ret.push_back(val & 0x00ff0000);
        ret.push_back(val & 0xff000000);
        return ret;
    }

    std::vector<Imm8m> Imm8m::inclusiveSplit(uint32_t val)
    {
        std::vector<Imm8m> ret;
        ret.push_back(val & 0x000000ff | 0xffffff00);
        ret.push_back(val & 0x0000ff00 | 0xffff00ff);
        ret.push_back(val & 0x00ff0000 | 0xff00ffff);
        ret.push_back(val & 0xff000000 | 0x00ffffff);
        return ret;
    }

    Register::Register(int id) : id(id)
    {
        if (id < 0 || id > 15)
        {
            Error::exit("Assembly::Register: reg id out of range");
        }
    }

    std::string Register::toString() const
    {
        return REG_NAME[id];
    }

    RegShift::RegShift(Register reg, ShiftType sftType, int bits) :
        reg(reg), sftType(sftType), shift(bits)
    {
        if ((sftType == ShiftType::Lsl && (bits < 0 || bits > 31)) ||
            (sftType == ShiftType::Lsr && (bits < 1 || bits > 32)) ||
            (sftType == ShiftType::Asr && (bits < 1 || bits > 32)))
        {
            Error::exit("Assembly::RegShift: shift bits out of range");
        }
    }

    std::string RegShift::toString() const
    {
        if (shift.index() == 1)
        {
            return reg.toString() + ", " + getShiftCode(sftType) + " " + std::get<1>(shift).toString();
        }

        int bits = std::get<0>(shift);
        if (sftType == ShiftType::Lsl && bits == 0)
        {
            return reg.toString();
        }
        return reg.toString() + ", " + getShiftCode(sftType) + " #" + std::to_string(bits);
    }

    bool RegShift::operator == (const RegShift &rhs) const
    {
        return (sftType == rhs.sftType) && (shift == rhs.shift);
    }

    std::string Operand2::toString() const
    {
        return (val.index() == 0) ?
            std::get<0>(val).toString() :
            std::get<1>(val).toString();
    }

    void AsmInstruction::setModifyFlags(bool modifyFlags)
    {
        setFlags = modifyFlags;
        if (!canSetFlags() && modifyFlags)
        {
            Error::exit("Assembly::Instruction: instruction doesn't have 's' suffix");
        }
    }

    void AsmInstruction::setSuffix(Condition condCode, bool modifyFlags)
    {
        setCondition(condCode);
        setModifyFlags(modifyFlags);
    }

    std::string AsmInstruction::getFuncSuffix() const
    {
        if (!setFlags)
        {
            return getCondCode(cond);
        }
        return "s" + getCondCode(cond);
    }

    std::string BinOpInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rd.toString() + ", " +
            rn.toString() + ", " +
            op2.toString();
    }

    std::shared_ptr<AsmInstruction> BinOpInstr::alternative() const
    {
        switch (type())
        {
        case InstrType::Add:
        case InstrType::Adc:
        case InstrType::Sub:
            if (rd == rn && op2 == 0)
            {
                return std::make_shared<NopInstr>();
            }
            break;
        default:
            break;
        }
        return nullptr;
    }

    std::string MulInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rd.toString() + ", " +
            rm.toString() + ", " +
            rs.toString();
    }

    bool MulAddInstr::canSetFlags() const
    {
        return type() == InstrType::Mla;
    }

    std::string MulAddInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rd.toString() + ", " +
            rm.toString() + ", " +
            rs.toString() + ", " +
            rn.toString();
    }

    std::string Mul64Instr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rl.toString() + ", " +
            rh.toString() + ", " +
            rm.toString() + ", " +
            rs.toString();
    }

    std::string SdivInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rd.toString() + ", " +
            rn.toString() + ", " +
            rm.toString();
    }

    std::string MovInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rd.toString() + ", " +
            op2.toString();
    }

    std::string ShiftInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rd.toString() + ", " +
            regShift.toString();
    }

    std::string CmpInstr::toString() const
    {
        return getFuncFullCode() + "\t" +
            rn.toString() + ", " +
            op2.toString();
    }

    std::string BrcInstr::toString() const
    {
        auto addrStr = (addr.index() == 0) ?
            std::get<0>(addr) :
            std::get<1>(addr).toString();

        return getFuncFullCode() + "\t" + addrStr;
    }

    MonoMemInstr::MonoMemInstr(Register rd, Register rn, Imm12u offset, Type type, AutoIncType inc) :
        rd(rd), rn(rn), offset(offset), inc(inc), AsmInstruction(InstrType(type))
    {
        if (inc == AutoIncType::Da || inc == AutoIncType::Db)
        {
            Error::exit("Ldr|Str is not compatible with auto decrease");
        }
    }

    MonoMemInstr::MonoMemInstr(Register rd, Register rn, RegShift offset, Type type, AutoIncType inc) :
        rd(rd), rn(rn), offset(offset), inc(inc), AsmInstruction(InstrType(type))
    {
        if (inc == AutoIncType::Da || inc == AutoIncType::Db)
        {
            Error::exit("Ldr|Str is not compatible with auto decrease");
        }
    }

    std::string MonoMemInstr::toString() const
    {
        // TODO:
        // 符号问题
        std::string code;
        code += getFuncFullCode() + "\t" + rn.toString() + ", [" + rd.toString();
        std::string offStr = (offset.index() == 1) ?
            std::get<1>(offset).toString() :
            std::get<0>(offset).toString();

        if (inc == AutoIncType::Ia)
        {
            return code + "], " + offStr;
        }

        code += ", " + offStr + "]";
        return (inc == AutoIncType::Ib) ? code + "!" : code;
    }

    std::string MultiMemInstr::toString() const
    {
        std::string code = getFuncFullCode();

        if (type() == InstrType::Ldm || type() == InstrType::Stm)
        {
            code += getAutoIncCode(inc) + "\t";
            code += rn.toString();
            code += updateRn ? "!, {" : ", {";
        }
        else
        {
            code += "\t{";
        }

        for (auto it = regList.begin(); it != regList.end(); it++)
        {
            code += it->toString();
            if (it != regList.end() - 1)
            {
                code += ", ";
            }
        }
        return code + "}";
    }
}