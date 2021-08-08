#include"../include/Instruction.h"

#include <sstream>

std::string Instruction::argToStr(Value* arg)
{
	if (arg == nullptr) return "";

	const auto& paramSet = parent->func->paramSet;
	auto& symTable = parent->func->revSymbolTable;

	if (arg->isArray())
	{
		if (paramSet.find(arg) != paramSet.end())
			return "&[]" + Module::getName(arg);

		if (symTable[arg] != "")
			return "&[]" + symTable[arg];

		return "~[]" + Module::getName(arg);

		// auto globalVal = parent->func->parent->getConstantValue(arg);
		// if (globalVal != nullptr)
		// 	return "~[]" + Module::getName(globalVal);

		// return "[]??";
	}
	if (arg->isInt())
	{
		auto v = dynamic_cast<ConstantInt*>(arg);
		if (v != nullptr)
			return "#" + std::to_string(v->value);

		if (paramSet.find(arg) != paramSet.end())
			return "&" + Module::getName(arg);

		if (symTable[arg] != "")
			return "&" + symTable[arg];

		return "~" + Module::getName(arg);
		// auto globalVal = parent->func->parent->getConstantValue(arg);
		// if (globalVal != nullptr)
		// 	return "~" + Module::getName(globalVal);

		// return "#??";
	}
	if (arg->isInstr())
	{
		auto ins = dynamic_cast<Instruction*>(arg);
		if (ins->id == Instruction::Constant)
		{
			return ins->argToStr(ins->args[0]);
		}
		return "%" + std::to_string(ins->number);
	}
	if (typeid(*arg) == typeid(Function))
	{
		auto f = dynamic_cast<Function*>(arg);
		return "@" + f->name;
	}
	if (typeid(*arg) == typeid(BaseBlock))
	{
		std::stringstream ss;
		ss << arg;
		return ss.str();
	}
	return "???";
}

void Instruction::debugPrint()
{
	std::cout << "\t" << getOpStr() << "\t";
	if (typeid(*this) != typeid(StoreInst) &&
		typeid(*this) != typeid(ReturnInst) &&
		typeid(*this) != typeid(BranchInst))
		std::cout << argToStr(this) << ", ";

	for (auto arg : args)
		std::cout << argToStr(arg) << " ";

	std::cout << "\n";
}