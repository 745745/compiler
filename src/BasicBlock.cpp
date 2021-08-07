#include "../include/BasicBlock.h"

void BaseBlock::debugPrint()
{
	cout << "    BlockType ";
	cout << name.at(blockType) << " ";
	Instruction* inst;
	cout << "InstructionListLength = " << insrList.size() << endl;
	for (auto inst : insrList)
	{
		inst->debugPrint(); 
		cout << endl;
	}
}