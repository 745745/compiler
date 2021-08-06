#include"../include/Instruction.h"

void Instruction::debugPrint()
{
	cout << name.at(id) << " ";
	cout << argNum << " ";
	for (Value* arg : args)
	{
		if (arg->isArray())
		{
			cout << "array: ";
			if (arg->isConstant)
			{
				ConstantArray *constantArray = dynamic_cast<ConstantArray*>(arg);
				for (int i = 0; i < constantArray->value.size(); i++)
				{
					cout << constantArray->value[i] << " ";
				}
			}
			cout << endl;
		}
		else if (arg->isInt())
		{
			cout << "int: ";
			if (arg->isConstant)
			{
				ConstantInt *constantInt = dynamic_cast<ConstantInt*>(arg);
				cout << constantInt->value;
			}
			cout << endl;
		}
		else
		{
			cout << "Instruction: ";
			Instruction *instruction = dynamic_cast<Instruction*>(arg);
			instruction->debugPrint();
			cout << endl;
		}
		
	}
	
}