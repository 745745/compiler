#include "../include/BasicBlock.h"

void BaseBlock::debugPrint()
{
	cout << blockType;
	Instruction * inst;
	for (auto inst : insrList)
	{
		inst->debugPrint();
		cout << " ";
	}
	cout << endl;
}
