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

    void FuncBlock::generate()
    {
        genHead();

        isLeaf = true;
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

        std::vector<Register> toSave;
        if (!isLeaf)
            toSave.push_back(Lr);
        toSave.push_back(Fp);

        append<MultiMemInstr>(toSave, MultiMemInstr::StackType::Push);

        nMaxSpillArgs = std::max(int(maxCallArgs) - MaxParamsPassedByReg, 0);
        nSaveParams = std::min(int(func->paramSet.size()), MaxParamsPassedByReg);

        offsetLocalData = nSaveParams * 4 + 4;
        offsetTempVar = offsetLocalData + func->localDataSizeByByte;
        stackSize = nSaveParams * 4 + func->localDataSizeByByte + func->nTempVars * 4 + nMaxSpillArgs * 4;
        
        append<Comment>("stackSize " + std::to_string(stackSize));

        if (isLeaf)
            append<BinOpInstr>(Fp, Sp, 4, BinOpInstr::Type::Sub);
        else
            append<MovInstr>(Fp, Sp, MovInstr::Type::Mov);

        if (Imm8m::isValid(stackSize))
            append<BinOpInstr>(Sp, Sp, stackSize, BinOpInstr::Type::Sub);
        else
        {
            auto imms = Imm8m::exclusiveSplit(stackSize);
            for (auto i : imms)
                append<BinOpInstr>(Sp, Sp, i, BinOpInstr::Type::Sub);
        }

        for (int i = 0; i < nSaveParams; i++)
        {
            if (i == MaxParamsPassedByReg)
                break;
            append<MonoMemInstr>(Fp, Register(i), -(i + 1) * 4, MonoMemInstr::Type::Str);
        }

        for (auto block : func->blocks)
            genBasicBlock(block);

        if (isLeaf)
            append<BinOpInstr>(Sp, Fp, 4, BinOpInstr::Type::Add);
        else
            append<MovInstr>(Sp, Fp, MovInstr::Type::Mov);

        append<MultiMemInstr>(toSave, MultiMemInstr::StackType::Pop);
        append<BrcInstr>(Lr, BrcInstr::RegType::Bx);
        append<NonCode>("");
    }

    void FuncBlock::genHead()
    {
        append<NonCode>(".global" + TabSpace + name());
        append<NonCode>(TabSpace + ".align" + TabSpace + std::to_string(align));
        append<NonCode>(TabSpace + (asmType == AssemblyType::Arm ? ".arm" : ".thumb"));
        append<Label>(name());
    }

    void FuncBlock::genBasicBlock(BaseBlock *block)
    {
        auto label = std::make_shared<Label>(".L_" + func->name + "_" + std::to_string(block->idx));
        labelMap[block] = label;
        append<Label>(label);

        for (auto instr : block->insrList)
        {
            genInstruction(instr);
            alloc.clear();
            regMap.clear();
            available = AvailableRegs;
        }
        
        if (block->insrList.size() > 0)
        {
            auto endInstr = *block->insrList.rbegin();
            if (endInstr->id != Instruction::Ret && endInstr->id != Instruction::Br)
            {
                append<Comment>("need jump");
            }
        }
    }

    void FuncBlock::genInstruction(Instruction *instr)
    {
        if (instr->id == Instruction::Store)
        {
            auto ins = dynamic_cast<StoreInst *>(instr);
            auto save = ins->args[0];
            auto base = ins->args[1];
            auto offset = ins->args[2];

            if (isImm(save))
                move(R0, getImm(save));
            else
                loadReg(R0, save);

            if (offset == nullptr)
                storeReg(R0, base);
            else
            {
                getPtr(R1, base);
                if (isImm(offset))
                {
                    loadReg(R2, offset);
                    append<BinOpInstr>(R1, R1, R2, BinOpInstr::Type::Add);
                    append<MonoMemInstr>(R1, R0, 0, MonoMemInstr::Type::Str);
                }
                else
                {
                    loadReg(R2, offset);
                    append<MonoMemInstr>(R1, R0, R2, MonoMemInstr::Type::Str);
                }
            }
        }
        else if (instr->id == Instruction::Load)
        {
            auto ins = dynamic_cast<LoadInst*>(instr);
            auto base = ins->args[0];
            auto offset = ins->args[1];

            if (offset == nullptr)
                loadReg(R0, base);
            else
            {
                if (valueType(base) == MemType::Global)
                    loadReg(R1, base);
                else
                {
                    getPtr(R1, base);
                    if (isImm(offset))
                    {
                        loadReg(R2, offset);
                        append<BinOpInstr>(R1, R1, R2, BinOpInstr::Type::Add);
                        append<MonoMemInstr>(R1, R0, 0, MonoMemInstr::Type::Ldr);
                    }
                    else
                    {
                        loadReg(R2, offset);
                        append<MonoMemInstr>(R1, R0, R2, MonoMemInstr::Type::Ldr);
                    }
                }
            }
            storeReg(R0, ins);
        }
        else if (typeid(*instr) == typeid(UnaryInst))
        {
            auto ins = dynamic_cast<UnaryInst*>(instr);
            auto type = ins->id;
            auto arg = ins->args[0];

            loadReg(R0, arg);
            if (type == Instruction::Neg)
                append<BinOpInstr>(R0, R0, 0, BinOpInstr::Type::Rsb);
            else
            {
                append<CmpInstr>(R0, 0, CmpInstr::Type::Cmp);
                auto meq = std::make_shared<MovInstr>(R0, 1, MovInstr::Type::Mov);
                meq->setCondition(Condition::Eq);
                auto mne = std::make_shared<MovInstr>(R0, 0, MovInstr::Type::Mov);
                mne->setCondition(Condition::Ne);
                append<MovInstr>(meq);
                append<MovInstr>(mne);
            }
            storeReg(R0, ins);
        }
        else if (typeid(*instr) == typeid(BinaryInst))
        {
            auto ins = dynamic_cast<BinaryInst*>(instr);
            auto type = instr->id;

            auto s = ins->args[0];
            auto t = ins->args[1];

            loadReg(R0, s);
            loadReg(R1, t);
            if (type == Instruction::Rem)
            {
                append<SdivInstr>(R2, R0, R1);
                append<MulInstr>(R2, R2, R1);
                append<BinOpInstr>(R2, R0, R2, BinOpInstr::Type::Sub);
                storeReg(R2, ins);
            }
            else if (type == Instruction::Mul)
            {
                append<MulInstr>(R1, R0, R1);
                storeReg(R1, ins);
            }
            if (type == Instruction::Div)
            {
                append<SdivInstr>(R1, R0, R1);
                storeReg(R1, ins);
            }

            std::map<Instruction::OpID, BinOpInstr::Type> mp =
            {
                { Instruction::Add, BinOpInstr::Type::Add },
                { Instruction::Sub, BinOpInstr::Type::Sub },
                { Instruction::And, BinOpInstr::Type::And },
                { Instruction::Or, BinOpInstr::Type::Orr }
            };
            append<BinOpInstr>(R1, R0, R1, mp[type]);
            storeReg(R1, ins);
        }
        else if (instr->id == Instruction::Ret)
        {
            auto ins = dynamic_cast<ReturnInst*>(instr);
            if (ins->args.size() == 0)
                return;

            auto ret = ins->args[0];
            loadReg(R1, ret);
            append<MovInstr>(R0, R1, MovInstr::Type::Mov);
        }
        else if (instr->id == Instruction::Cmp)
        {
            auto ins = dynamic_cast<CmpInst*>(instr);
            auto lhs = ins->args[0];
            auto rhs = ins->args[1];

            loadReg(R0, lhs);
            loadReg(R1, lhs);
            append<CmpInstr>(R0, R1, CmpInstr::Type::Cmp);
        }
        else if (instr->id == Instruction::Call)
        {
            auto args = instr->args;
            if (args.size() == 0)
                Error::exit("call instruction no args");

            auto callee = dynamic_cast<Function*>(*args.rbegin());

            append<MovInstr>(R4, Sp, MovInstr::Type::Mov);
            for (int i = 0; i < args.size() - 1; i++)
            {
                if (i < 4)
                    loadReg(Register(i), args[i]);
                else
                {
                    loadReg(R5, args[i]);
                    append<MonoMemInstr>(R4, R5, 0, MonoMemInstr::Type::Str, AutoIncType::Ia);
                }
            }
            append<BrcInstr>(callee->name, BrcInstr::LabelType::Bl);
        }
    }

    void FuncBlock::loadReg(Register reg, ::Value *val)
    {
        if (isImm(val))
            move(reg, getImm(val));
        else if (valueType(val) == MemType::Global)
        {
            getPtr(reg, val);
            append<MonoMemInstr>(reg, reg, 0, MonoMemInstr::Type::Ldr);
        }
        else
        {
            int offset = getFpOffset(val);
            append<BinOpInstr>(reg, Fp, -offset, BinOpInstr::Type::Sub);
            append<MonoMemInstr>(reg, reg, 0, MonoMemInstr::Type::Ldr);
        }
    }

    void FuncBlock::storeReg(Register reg, ::Value *val)
    {
        auto type = valueType(val);
        if (type == MemType::Global)
            append<MonoMemInstr>(reg, Module::getName(val), MonoMemInstr::Type::Str);
        else
        {
            int offset = getFpOffset(val);
            append<MonoMemInstr>(Fp, reg, Imm12(offset), MonoMemInstr::Type::Str);
        }
    }

    void FuncBlock::getPtr(Register reg, ::Value *value)
    {
        if (valueType(value) == MemType::Global)
            append<MonoMemInstr>(reg, Module::getName(value), MonoMemInstr::Type::Ldr);
        else
        {
            int offset = getFpOffset(value);
            append<BinOpInstr>(reg, Fp, -offset, BinOpInstr::Type::Sub);
        }
    }

    void FuncBlock::readAtPtr(Register ptr, Register reg)
    {
        append<MonoMemInstr>(ptr, reg, 0, MonoMemInstr::Type::Ldr);
    }

    void FuncBlock::writeAtPtr(Register ptr, Register reg)
    {
        append<MonoMemInstr>(ptr, reg, 0, MonoMemInstr::Type::Str);
    }

    int FuncBlock::getFpOffset(::Value *val)
    {
        auto type = valueType(val);
        if (type == MemType::FuncParam)
        {
            int argIdx = func->paramSet[val];
            if (argIdx > 3)
                return (argIdx - 2) * 4;
            else
                return -(argIdx + 1) * 4;
        }
        else if (type == MemType::FrameLocal)
        {
            int addr = func->addressTable[val];
            return -(addr + offsetLocalData);
        }
        else if (type == MemType::CalleeParam)
        {
            int paramIdx = func->paramSet[val];
            Error::check(paramIdx >= MaxParamsPassedByReg, "impossible param index");
            return -stackSize + (MaxParamsPassedByReg - 1 - paramIdx) * 4;
        }
        else
            Error::exit("impossible Fp offset");
        return 0;
    }

    bool FuncBlock::isImm(::Value *val)
    {
        if (val->isInt())
        {
            auto v = dynamic_cast<ConstantInt*>(val);
            if (v != nullptr)
                return true;
        }
        else if (val->isInstr())
        {
            auto ins = dynamic_cast<Instruction*>(val);
            if (ins->id == Instruction::Constant)
                return isImm(ins->args[0]);
        }
        return false;
    }

    int FuncBlock::getImm(::Value *val)
    {
        if (val->isInt())
        {
            auto v = dynamic_cast<ConstantInt*>(val);
            if (v != nullptr)
                return v->value;
        }
        else if (val->isInstr())
        {
            auto ins = dynamic_cast<Instruction*>(val);
            if (ins->id == Instruction::Constant)
                return getImm(ins->args[0]);
        }
        return -1;
    }

    MemType FuncBlock::valueType(::Value *val)
    {
        if (func->paramSet.find(val) != func->paramSet.end())
            return MemType::FuncParam;
        if (func->revSymbolTable[val] != "")
            return MemType::FrameLocal;
        if (dynamic_cast<ConstantValue*>(val) != nullptr)
            return MemType::Global;

        return MemType::CalleeParam;
    }

    void FuncBlock::move(Register reg, int val)
    {
        auto type = MovInstr::Type::Mov;
        if (Imm8m::isValid(val))
            append<MovInstr>(reg, val, type);
        else
        {
            auto imms = Imm8m::exclusiveSplit(val);
            append<MovInstr>(reg, imms[0], type);
            for (int i = 1; i < imms.size(); i++)
                append<BinOpInstr>(reg, reg, imms[i], BinOpInstr::Type::Add);
        }
    }

    void FuncBlock::printInfo()
    {
    }

    void AsmTranslator::translate()
    {
        loadGlobalVals();

        for (auto func : module.funcList)
        {
            auto funcBlock = std::make_shared<FuncBlock>(func, AssemblyType::Arm, alignment);
            funcBlock->generate();
            funcBlocks.push_back(funcBlock);
            funcBlock->printInfo();
        }
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
            auto fl = fb->getLines();
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
}