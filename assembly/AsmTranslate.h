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
        FuncBlock(const std::string &name, AssemblyType asmType, int align = 2) :
            name(name), asmType(asmType), align(align) {}

        template <typename T, typename... Args>
        void append(Args &&...args) { body.push_back(std::make_shared<T>(args...)); }

        std::vector<LinePtr> genHead();
        std::vector<LinePtr> toLines();

    public:
        std::string name;
        std::vector<LinePtr> body;

        std::vector<FuncBlockPtr> callees;
        std::vector<FuncBlockPtr> callers;

        AssemblyType asmType;
        int stackSize = 0;
        bool isLeaf = false;
        int align = 2;
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

        FuncBlockPtr genFuncBlock(Function *func);
        void genBasicBlock(BasicBlock *block);

        void genInstruction(AsmInstruction *instr);

    private:
        AssemblyType asmType = AssemblyType::Arm;
        int alignment = 2;
        std::string architecture = "armv7-a";

        bool rewriteSymbolName = true;
        bool useParsedImm8m = false;
        bool dynamicSpWithMultiCallee = false;

        std::map<::Value*, int> regMapping;
        //std::map<std::string, std::vector<int>> globalData;
        
        std::vector<GlobalVal> globalValues;
        std::vector<FuncBlockPtr> funcBlocks;
        std::vector<LinePtr> lines;

        Module module;
        std::string fileName;

        int storedImmCount = 0;
    };
}