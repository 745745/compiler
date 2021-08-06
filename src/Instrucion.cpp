#include"../include/Instruction.h"

void Instruction::debugPrint()
{
	cout << this->id << " ";
    cout << this->argNum << " ";
    for (auto value:this->args)
    {
        if (value->isArray())
		{
			cout << "array ";
		}
		else if (value->isInt())
		{
			cout << "int ";
		}
    }
    
}