#include"../include/Instruction.h"

void Instruction::debugPrint()
{
	cout << "		";
	cout << name.at(id) << " ";
	cout <<"argNum:"<< args.size() << " ";
	for (Value* arg : args)
	{
		if (arg->isArray())
		{
			cout << "array: ";
			if (arg->isConstant)
			{
				ConstantArray* constantArray = dynamic_cast<ConstantArray*>(arg);
				for (int i = 0; i < constantArray->value.size(); i++)
				{
					cout << constantArray->value[i] << " ";
				}
			}
			else
			{
				string name = Module::getName(arg);
				if (name.size() != 0)
					cout << name<<"  ";
				else cout << "no init ";
			}
			cout <<"	";
		}
		else if (arg->isInt())
		{
			cout << "int: ";
			if (arg->isConstant)
			{
				ConstantInt* constantInt = dynamic_cast<ConstantInt*>(arg);
				if(constantInt!=nullptr)
					cout << constantInt->value<<"	";
				else
				{
					ConstInst* p = dynamic_cast<ConstInst*>(arg);
					cout << ((ConstantInt*)p->args[0])->value<<"  ";
				}
			}
			else
			{
				string name = Module::getName(arg);
				if (name.size() != 0)
					cout << name<<"  ";
				else cout << "no init ";
			}
			cout << "	";
		}
		else if(arg->isInstr())
		{
			Instruction* instruction = dynamic_cast<Instruction*>(arg);
			if (instruction->isconst == true)
			{
				cout << "int:" << ((ConstantInt*)instruction->args[0])->value<<"	";
				continue;
			}
			cout << endl;
			cout << "Instruction: ";
			instruction->debugPrint();
			cout << "	";
		}
		else
		{
			cout << "Block or something";
		}

	}
}