#pragma once

#include <iostream>
#include <variant>
#include <sstream>
#include <vector>
#include <memory>

#include "../utils/Error.h"

namespace Assembly
{
    const std::string REG_NAME[] =
    {
        "r0", "r1", "r2", "r3", "r4", "r5", "r6", "fp",
        "r8", "r9", "r10", "r11", "r12", "sp", "lr", "pc"
    };

    const std::string COND_CODE[] =
    {
        "", "eq", "ne", "gt", "lt", "ge", "le"
    };

    const std::string INSTR_CODE[] =
    {
        "nop",
        "add", "adc", "sub", "sbc", "rsb", "rsc",
        "and", "eor", "orr", "orn", "bic",
        "mul", "mla", "mls", "smull", "smlal", "sdiv",
        "mov", "mvn",
        "asr", "lsr", "lsl",
        "cmp", "cmn", "tst", "teq",
        "b", "bl", "blx", "bx",
        "ldr", "str", "ldrd", "strd", "ldm", "stm", "push", "pop",
        "pld", "pli",
    };

    const std::string AUTO_INC_CODE[] =
    {
        "", "ia", "ib", "da", "db"
    };

    enum class Condition
    {
        None = 0, Eq, Ne, Gt, Lt, Ge, Le
    };

    enum class InstrType
    {
        Nop = 0,
        Add, Adc, Sub, Sbc, Rsb, Rsc,
        And, Eor, Orr, Orn, Bic,
        Mul, Mla, Mls, Smull, Smlal, Sdiv,
        Mov, Mvn,
        Asr, Lsr, Lsl,
        Cmp, Cmn, Tst, Teq,
        B, Bl, Blx, Bx,
        Ldr, Str, Ldrd, Strd, Ldm, Stm, Push, Pop,
        Pld, Pli,
    };

    enum class ShiftType
    {
        Asr = int(InstrType::Asr), Lsr, Lsl
    };

    enum class ValueType
    {
        Reg, RegShift, Imm, Imm8m, Offset12, Op2, Mem, Addr
    };

    enum class AutoIncType
    {
        None = 0, Ia, Ib, Da, Db
    };

    std::string getRegName(int reg);
    std::string getCondCode(Condition cond);
    std::string getShiftCode(ShiftType shft);
    std::string getInstrCode(InstrType instr);
    std::string getAutoIncCode(AutoIncType inc);

    class Line
    {
    public:
        enum class Type { Label, Instr, Others };

        Line(Type type) : _type(type) {}
        Type type() const { return _type; }
        virtual std::string toString() const = 0;

    private:
        Type _type;
    };

    typedef std::shared_ptr<Line> LinePtr;

    class Value
    {
    public:
        virtual ValueType type() const = 0;
        virtual std::string toString() const = 0;
    };

    template<int Bits, bool Signed>
    class Immediate : public Value
    {
    public:
        Immediate(int val) : val(val)
        {
            constexpr const int lo = Signed ? -(1 << (Bits - 1)) : 0;
            constexpr const int hi = Signed ? (1 << (Bits - 1)) : (1 << Bits);
            if (val < lo || val >= hi)
            {
                Error::exit("Assembly::Immediate<" + std::to_string(Bits) + ", " + std::to_string(Signed) + ">: value out of range");
            }
        }
        ValueType type() const { return ValueType::Imm; }

        std::string toString() const
        {
            return "#" + std::to_string(val);
        }

        bool operator == (const Immediate &rhs) const { return val == rhs.val; }

    private:
        int val;
    };

    typedef Immediate<12, false> Imm12u;
    typedef Immediate<12, true> Imm12;

    class Imm8m : public Value
    {
    public:
        Imm8m(uint32_t val);
        Imm8m(uint8_t val, int rol);
        ValueType type() const { return ValueType::Imm8m; }
        std::string toString() const;

        bool operator == (const Imm8m &rhs) const { return val == rhs.val; }

        static bool isValid(uint32_t val);
        static void testValid(uint32_t val);
        // Split an integer into several valid Imm8ms that satisfy:
        // XorSum imm8m[i] = imm32, imm8m[i] & imm8m[j] = 0
        // Can be used for Add/Sub, Or/Xor
        static std::vector<Imm8m> exclusiveSplit(uint32_t val);
        // Split an integer into several valid Imm8ms that satisfy:
        // AndSum imm8m[i] = imm32
        // Can be used for And
        static std::vector<Imm8m> inclusiveSplit(uint32_t val);

    private:
        uint32_t val;
    };

    class Register : public Value
    {
    public:
        enum { Fp = 7, Sp = 13, Lr = 14, Pc = 15 };

        Register() : id(Pc) {}
        Register(int id);
        ValueType type() const { return ValueType::Reg; }
        std::string toString() const;

        bool operator == (const Register &rhs) const { return id == rhs.id; }
        bool operator < (const Register &rhs) const { return id < rhs.id; }

    private:
        int id;
    };

    const Register R0(0);
    const Register R1(1);
    const Register R2(2);
    const Register R3(3);
    const Register R4(4);
    const Register R5(5);
    const Register R6(6);
    const Register R7(7);
    const Register R8(8);
    const Register R9(9);
    const Register R10(10);
    const Register R11(11);
    const Register R12(12);
    const Register R13(13);
    const Register R14(14);
    const Register R15(15);

    class RegShift : public Value
    {
    public:
        RegShift(Register reg) :
            reg(reg), sftType(ShiftType::Lsl), shift(0) {}
        RegShift(Register reg, ShiftType sftType, int bits);
        RegShift(Register reg, ShiftType sftType, Register rs) :
            reg(reg), sftType(sftType), shift(rs) {}
        ValueType type() const { return ValueType::RegShift; }
        ShiftType shiftType() const { return sftType; }
        std::string toString() const;

        bool operator == (const RegShift &rhs) const;

    private:
        Register reg;
        ShiftType sftType;
        std::variant<int, Register> shift;
    };

    class Operand2 : public Value
    {
    public:
        Operand2(uint32_t imm8m) : val(imm8m) {}
        Operand2(Imm8m imm) : val(imm) {};
        Operand2(Register reg) : val(RegShift(reg)) {}
        Operand2(RegShift regShift) : val(regShift) {}
        ValueType type() const { return ValueType::Op2; }
        std::string toString() const;

        bool operator == (const Operand2 &rhs) const { return val == rhs.val; }

    private:
        std::variant<Imm8m, RegShift> val;
    };

    class AsmInstruction : public Line
    {
    public:
        AsmInstruction(InstrType type) :
            func(type), Line(Type::Instr) {}

        virtual bool canSetFlags() const = 0;

        void setModifyFlags(bool modifyFlags);
        void setCondition(Condition condCode) { cond = condCode; }
        void setSuffix(Condition condCode, bool modifyFlags = false);

        InstrType type() const { return func; }
        std::string getFuncCode() const { return getInstrCode(func); }
        std::string getFuncSuffix() const ;
        std::string getFuncFullCode() const { return getFuncCode() + getFuncSuffix(); }
        // Returns a faster and more simplified alternative of current instruction if exists, otherwise nullptr
        virtual std::shared_ptr<AsmInstruction> alternative() const { return nullptr; }

    protected:
        InstrType func;
        Condition cond = Condition::None;
        bool setFlags = false;
    };

    typedef std::shared_ptr<AsmInstruction> AsmInstrPtr;

    class NopInstr : public AsmInstruction
    {
    public:
        NopInstr() : AsmInstruction(InstrType::Nop) {}
        bool canSetFlags() const override { return false; }
        std::string toString() const override { return "nop"; }
    };

    class BinOpInstr : public AsmInstruction
    {
    public:
        enum class Type { Add = int(InstrType::Add), Adc, Sub, Sbc, Rsb, Rsc, And, Eor, Orr, Orn, Bic };

        BinOpInstr(Register rd, Register rn, Operand2 op2, Type func) :
            rd(rd), rn(rn), op2(op2), AsmInstruction(InstrType(func)) {}
        bool canSetFlags() const override { return true; }
        std::string toString() const override;
        std::shared_ptr<AsmInstruction> alternative() const override;

    private:
        Register rd, rn;
        Operand2 op2;
    };

    class MulInstr : public AsmInstruction
    {
    public:
        MulInstr(Register rd, Register rm, Register rs) :
            rd(rd), rm(rm), rs(rs), AsmInstruction(InstrType::Mul) {}
        bool canSetFlags() const override { return true; }
        std::string toString() const override;
        //std::shared_ptr<Instruction> alternative() const override;

    private:
        Register rd, rm, rs;
    };

    class MulAddInstr : public AsmInstruction
    {
    public:
        enum class Type { Mla = int(InstrType::Mla), Mls };

        MulAddInstr(Register rd, Register rm, Register rs, Register rn) :
            rd(rd), rm(rm), rs(rs), rn(rn), AsmInstruction(InstrType::Mla) {}
        bool canSetFlags() const override;
        std::string toString() const override;

    private:
        Register rd, rm, rs, rn;
    };

    class Mul64Instr : public AsmInstruction
    {
    public:
        enum class Type { Smull = int(InstrType::Smull), Smlal };

        Mul64Instr(Register rl, Register rh, Register rm, Register rs, Type type) :
            rl(rl), rh(rh), rm(rm), rs(rs), AsmInstruction(InstrType(type)) {}
        bool canSetFlags() const override { return true; }
        std::string toString() const override;

    private:
        Register rl, rh, rm, rs;
    };

    class SdivInstr : public AsmInstruction
    {
    public:
        SdivInstr(Register rd, Register rn, Register rm) :
            rd(rd), rn(rn), rm(rm), AsmInstruction(InstrType::Sdiv) {}
        bool canSetFlags() const override { return false; }
        std::string toString() const override;
        //std::shared_ptr<Instruction> alternative() const override;

    private:
        Register rd, rn, rm;
    };

    class MovInstr : public AsmInstruction
    {
    public:
        enum class Type { Mov = int(InstrType::Mov), Mvn };

        MovInstr(Register rd, Operand2 op2, Type type) :
            rd(rd), op2(op2), AsmInstruction(InstrType(type)) {}
        bool canSetFlags() const override { return true; }
        std::string toString() const override;

    private:
        Register rd;
        Operand2 op2;
    };

    class ShiftInstr : public AsmInstruction
    {
    public:
        ShiftInstr(Register rd, RegShift shift) :
            rd(rd), regShift(shift), AsmInstruction(InstrType(shift.shiftType())) {}
        bool canSetFlags() const override { return true; }
        std::string toString() const override;

    private:
        Register rd;
        RegShift regShift;
    };

    class CmpInstr : public AsmInstruction
    {
    public:
        enum class Type { Cmp = int(InstrType::Cmp), Cmn, Tst, Teq };

        CmpInstr(Register rn, Operand2 op2, Type type) :
            rn(rn), op2(op2), AsmInstruction(InstrType(type)) {}
        bool canSetFlags() const override { return false; }
        std::string toString() const override;

    private:
        Register rn;
        Operand2 op2;
    };

    class BrcInstr : public AsmInstruction
    {
    public:
        enum class LabelType { B = int(InstrType::B), Bl = int(InstrType::Bl), Blx = int(InstrType::Blx) };
        enum class RegType { Bx = int(InstrType::Bx), Blx = int(InstrType::Blx) };

        BrcInstr(const std::string &label, LabelType type) :
            addr(label), AsmInstruction(InstrType(type)) {}
        BrcInstr(Register reg, RegType type) :
            addr(reg), AsmInstruction(InstrType(type)) {}
        bool canSetFlags() const override { return false; }
        std::string toString() const override;

    private:
        std::variant<std::string, Register> addr;
    };

    class MonoMemInstr : public AsmInstruction
    {
    public:
        enum class Type { Ldr = int(InstrType::Ldr), Str };

        MonoMemInstr(Register rn, const std::string &label, Type type) :
            rd(rn), rn(rn), offset(label), AsmInstruction(InstrType(type)) {}
        MonoMemInstr(Register rd, Register rn, Imm12 offset, Type type, AutoIncType inc = AutoIncType::None);
        MonoMemInstr(Register rd, Register rn, RegShift offset, Type type, AutoIncType inc = AutoIncType::None);
        bool canSetFlags() const override { return false; }
        std::string toString() const override;

        void setOffsetDir(bool plus) { sub = !plus; }

    private:
        Register rd, rn;
        std::variant<Imm12, RegShift, std::string> offset;
        AutoIncType inc;
        bool sub;
    };

    class MultiMemInstr : public AsmInstruction
    {
    public:
        enum class MoveType { Ldm = int(InstrType::Ldm), Stm };
        enum class StackType { Push = int(InstrType::Push), Pop };

        MultiMemInstr(Register rn, const std::vector<Register> &regList, MoveType type, AutoIncType inc, bool updateRn) :
            rn(rn), regList(regList), AsmInstruction(InstrType(type)), inc(inc), updateRn(updateRn) {}
        MultiMemInstr(const std::vector<Register> &regList, StackType type) :
            rn(Register::Sp), regList(regList), AsmInstruction(InstrType(type)) {}
        bool canSetFlags() const override { return false; }
        std::string toString() const override;

    private:
        Register rn;
        bool updateRn;
        AutoIncType inc;
        std::vector<Register> regList;
    };
}