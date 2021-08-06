#include "../include/BasicBlock.h"

void BaseBlock::debugPrint()
{
	cout << "    BlockType ";
	cout << blockType << " ";
	Instruction * inst;
	cout << "InstructionListLength = "<<insrList.size() << endl;
	for (auto inst : insrList)
	{
		cout << "         InstructionCount ";
		//inst->debugPrint(); //现在inst屁也没得测
		cout << endl;
	}
}
