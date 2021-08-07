#include "AsmTranslate.h"

namespace Assembly
{
    std::vector<LinePtr> GlobalVal::toLines()
    {
        std::vector<LinePtr> ret;
        appendLine<NonCode>(ret, TabSpace + ".align" + TabSpace + std::to_string(align));
        appendLine<Label>(ret, name);
        
        std::stringstream ss;
        ss << ".word" << TabSpace;
        for (int i = 0; i < data.size(); i++)
        {
            ss << data[i];
            if (i != data.size() - 1)
                ss << ", ";
        }
        appendLine<NonCode>(ret, TabSpace + ss.str());
        return ret;
    }

    std::vector<LinePtr> FuncBlock::genHead()
    {
        std::vector<LinePtr> ret;
        appendLine<NonCode>(ret, ".global" + TabSpace + name);
        appendLine<NonCode>(ret, TabSpace + ".align" + TabSpace + std::to_string(align));
        appendLine<NonCode>(ret, TabSpace + (asmType == AssemblyType::Arm ? ".arm" : ".thumb"));
        appendLine<Comment>(ret, "stackSize " + std::to_string(stackSize));
        appendLine<Label>(ret, name);
        return ret;
    }

    std::vector<LinePtr> FuncBlock::toLines()
    {
        std::vector<LinePtr> ret = genHead();

        std::vector<Register> toSave;
        if (!isLeaf)
            toSave.push_back(Lr);
        toSave.push_back(Fp);

        appendLine<MultiMemInstr>(ret, toSave, MultiMemInstr::StackType::Push);

        if (isLeaf)
            appendLine<BinOpInstr>(ret, Fp, Sp, 4, BinOpInstr::Type::Sub);
        else
            appendLine<MovInstr>(ret, Fp, Sp, MovInstr::Type::Mov);

        if (Imm8m::isValid(stackSize))
            appendLine<BinOpInstr>(ret, Sp, Sp, stackSize, BinOpInstr::Type::Sub);
        else
        {
            auto imms = Imm8m::exclusiveSplit(stackSize);
            for (auto i : imms)
                appendLine<BinOpInstr>(ret, Sp, Sp, i, BinOpInstr::Type::Sub);
        }

        ret.insert(ret.end(), body.begin(), body.end());

        if (isLeaf)
            appendLine<BinOpInstr>(ret, Sp, Fp, 4, BinOpInstr::Type::Add);
        else
            appendLine<MovInstr>(ret, Sp, Fp, MovInstr::Type::Mov);

        appendLine<MultiMemInstr>(ret, toSave, MultiMemInstr::StackType::Pop);
        appendLine<BrcInstr>(ret, Lr, BrcInstr::RegType::Bx);

        return ret;
    }

    void AsmTranslator::translate()
    {
        loadGlobalVals();

        for (auto func : module.funcList)
            funcBlocks.push_back(genFuncBlock(func));
    }

    std::string AsmTranslator::getCode()
    {
        genTargetPlatformInfo();
        append<CommentL>("[global data]");

        for (auto v : globalValues)
        {
            auto vl = v.toLines();
            lines.insert(lines.end(), vl.begin(), vl.end());
        }
        append<NonCode>("");
        append<CommentL>("[functions]");

        for (auto fb : funcBlocks)
        {
            auto fl = fb->toLines();
            lines.insert(lines.end(), fl.begin(), fl.end());
        }

        std::stringstream ss;
        for (auto line : lines)
        {
            if (line->type() == Line::Type::Instr)
            {
                auto ins = dynamic_cast<AsmInstruction*>(line.get());
                auto alter = ins->alternative();
                if (alter != nullptr)
                {
                    if (alter->type() == InstrType::Nop) continue;
                    line = alter;
                }
                ss << TabSpace;
            }
            ss << line->toString() << "\n";
        }
        return ss.str();
    }

    void AsmTranslator::genTargetPlatformInfo()
    {
        append<Comment>("file " + fileName);
        append<CommentL>("[head section]");
        append<NonCode>(".arch" + TabSpace + architecture);
        append<NonCode>(".text");
        append<NonCode>("");
    }

    void AsmTranslator::loadGlobalVals()
    {
        auto valueTable = module.valueTable;

        for (auto [name, val] : module.globalVar)
        {
            auto nameString = "V_" + name;
            if (val->isArray())
            {
                auto v = dynamic_cast<ConstantArray*>(module.getConstantValue(val));
                if (v != nullptr)
                    globalValues.push_back({ nameString, v->value });
                else
                    globalValues.push_back({ nameString, reinterpret_cast<ArrayType*>(val->type)->num });
            }
            else
            {
                auto v = dynamic_cast<ConstantInt*>(module.getConstantValue(val));
                if (v != nullptr)
                    globalValues.push_back({ nameString, v->value });
                else
                    globalValues.push_back({ nameString, 1 });
            }
        }
    }

    FuncBlockPtr AsmTranslator::genFuncBlock(Function *func)
    {
        auto funcBlock = std::make_shared<FuncBlock>(func->name, asmType, alignment);

        std::set<Value*> valueSet;

        bool isLeaf = true;
        uint64_t maxCallArgs = 0;

        for (auto block : func->blocks)
        {
            for (auto instr : block->insrList)
            {
                if (instr->id == Instruction::Call)
                {
                    isLeaf = false;
                    auto ins = dynamic_cast<CallInst*>(instr);
                    maxCallArgs = std::max(maxCallArgs, ins->args.size() - 1);
                }
            }
        }
        funcBlock->isLeaf = isLeaf;
        funcBlock->stackSize = 4 * (func->nTempVars + func->params.size() - MaxParamsPassedByReg);

        for (int i = 0; i < func->params.size(); i++)
        {
            if (i == MaxParamsPassedByReg)
                break;
            auto instr = std::make_shared<MonoMemInstr>(Fp, Register(i), Imm12u(i), MonoMemInstr::Type::Str);
            instr->setOffsetDir(false);
            //funcBlock->append<MonoMemInstr>(instr);
            funcBlock->body.push_back(instr);
        }

        std::set<Register> available = AvailableRegs;

        int blockId = 0;
        for (auto block : func->blocks)
        {
            funcBlock->append<Label>(".L_" + func->name + "_"  + std::to_string(blockId));
            for (auto instr : block->insrList)
            {
                if (typeid(*instr) == typeid(StoreInst))
                {
                }
                else if (typeid(*instr) == typeid(ConstInst))
                {
                }
                else if (typeid(*instr) == typeid(UnaryInst))
                {
                }
                else if (typeid(*instr) == typeid(BinaryInst))
                {
                }
            }
            blockId++;
        }

        return funcBlock;
    }
}