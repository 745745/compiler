#pragma once

#include <iostream>

#include "AsmInstruction.h"
#include "../ir/Module.h"

namespace Assembly
{
    enum class AssemblyType
    {
        Arm, Thumb
    };

    const std::string EndLine = "\n";
    const std::string TabSpace = "\t";

    const Register Sp(Register::Sp);
    const Register Fp(Register::Fp);
    const Register Lr(Register::Lr);
    const Register Pc(Register::Pc);

    const std::set<Register> AvailableRegs =
    {
        Register(0), Register(1), Register(2), Register(3), Register(4), Register(5), Register(6),
        Register(8), Register(9), Register(10), Register(11), Register(12)
    };

    template <typename T, typename... Args>
    void appendLine(std::vector<std::shared_ptr<Line>> &tar, Args &&...args)
    {
        tar.push_back(std::make_shared<T>(args...));
    }

    template<char Prefix1, char Prefix2, char Suffix, Line::Type _Type>
    class LineString : public Line
    {
    public:
        LineString(const std::string &content) :
            content(content), Line(_Type) {}

        std::string toString() const
        {
            std::stringstream ss;
            ss << Prefix1 << Prefix2 << content << Suffix;
            return ss.str();
        }

        std::string getContent() const { return content; }

    private:
        std::string content;
    };

    typedef LineString<'\0', '\0', ':', Line::Type::Label> Label;
    typedef LineString<'\t', '@', '\0', Line::Type::Others> Comment;
    typedef LineString<'@', '\0', '\0', Line::Type::Others> CommentL;
    typedef LineString<'\0', '\0', '\0', Line::Type::Others> NonCode;

    struct GlobalVal
    {
        GlobalVal() = default;
        GlobalVal(const std::string &name, int size) :
            name(name), data(size, 0) {}
        GlobalVal(const std::string &name, const std::vector<int> &data) :
            name(name), data(data) {}
        std::vector<LinePtr> toLines();

        std::string name;
        std::vector<int> data;
        int align = 2;
    };

    class FuncBlock;
    typedef std::shared_ptr<FuncBlock> FuncBlockPtr;

    class FuncBlock
    {
    public:
        FuncBlock() = default;
        FuncBlock(Function *func, AssemblyType asmType, int align = 2) :
            func(func), asmType(asmType), align(align) {}

        template <typename T, typename... Args>
        void append(Args &&...args) { lines.push_back(std::make_shared<T>(args...)); }

        template <typename T>
        void append(std::shared_ptr<T> line) { lines.push_back(line); }

        void generate();
        void genHead();
        void genBasicBlock(BaseBlock *block);
        void genInstruction(Instruction *instr);

        void loadReg(Register reg, ::Value *val);
        void storeReg(Register reg, ::Value *val);
        void getPtr(Register reg, ::Value *val);
        void readAtPtr(Register ptr, Register reg);
        void writeAtPtr(Register ptr, Register reg);

        int getFpOffset(::Value *val);

        bool isImm(::Value *val);
        int getImm(::Value *val);

        MemType valueType(::Value *val);

        void move(Register reg, int val);

        std::string getGlobalVarLabel(::Value *val);

        std::vector<LinePtr> getLines() { return lines; }
        std::string name() const { return func->name; }

        void printInfo();

    public:
        Function *func;
        std::vector<LinePtr> lines;

        std::vector<FuncBlockPtr> callees;
        std::vector<FuncBlockPtr> callers;

        std::set<Register> available = AvailableRegs;
        std::map<::Value*, Register> alloc;
        std::map<Register, ::Value*> regMap;

        std::map<BaseBlock*, std::shared_ptr<Label>> labelMap;

        AssemblyType asmType;
        int stackSize = 0;
        bool isLeaf = false;
        int align = 2;
        int nSaveParams;
        int nMaxSpillArgs;
        int offsetSavedParam;
        int offsetLocalData;
        int offsetTempVar;
    };

    class AsmTranslator
    {
    public:
        AsmTranslator(const Module &module, const std::string fileName) :
            module(module), fileName(fileName) {}

        void translate();
        std::string getCode();
        
        void setAsmType(AssemblyType type) { asmType = type; }
        void setAlignment(int align) { alignment = align; }
        void setArchitecture(const std::string &arch) { architecture = arch; }

    private:
        static std::string getBasicBlockLabel(int id) { return "B_" + std::to_string(id); }

        template <typename T, typename... Args>
        void append(Args &&...args) { lines.push_back(std::make_shared<T>(args...)); }

        void genTargetPlatformInfo();
        void loadGlobalVals();

    private:
        AssemblyType asmType = AssemblyType::Arm;
        int alignment = 2;
        std::string architecture = "armv7-a";

        bool rewriteSymbolName = true;
        bool useParsedImm8m = false;
        bool dynamicSpWithMultiCallee = false;
        //std::map<std::string, std::vector<int>> globalData;
        
        std::vector<GlobalVal> globalValues;
        std::vector<FuncBlockPtr> funcBlocks;
        std::vector<LinePtr> lines;

        Module module;
        std::string fileName;

        int storedImmCount = 0;
    };
}