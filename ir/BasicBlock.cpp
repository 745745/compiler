#include "BasicBlock.h"

#include <queue>
#include <stack>

const std::string BlockTypeStr[] =
{
	"Basic", "If", "While"
};

void BaseBlock::addInst(Instruction *inst)
{
	inst->parent = this;
	insrList.push_back(inst);
}

void BaseBlock::debugPrint()
{
	std::cout << "    [Block " << idx << ", type " << BlockTypeStr[blockType] << "]\n";
	for (auto inst : insrList)
	{
		if (inst->id != Instruction::Constant)
			inst->debugPrint();
	}
}

void BaseBlock::linearizeInstrs()
{
	std::vector<Instruction*> newInstrList;

	std::set<Instruction *> vis;
	std::queue<Instruction *> q;

	for (auto instr : insrList)
	{
		std::vector<Instruction*> expInstrs;

		q.push(instr);
		while (!q.empty())
		{
			auto ins = q.front();
			q.pop();
			vis.insert(ins);
			ins->parent = this;
			expInstrs.push_back(ins);

			for (auto arg : ins->args)
			{
				auto a = dynamic_cast<Instruction*>(arg);
				if (a == nullptr)
					continue;
				if (vis.find(a) == vis.end())
					q.push(a);
			}
		}
		newInstrList.insert(newInstrList.end(), expInstrs.rbegin(), expInstrs.rend());
	}
	insrList = newInstrList;

	// std::vector<Instruction *> newInstrList;

	// std::set<Instruction *> vis;
	// std::stack<Instruction *> st;

	// for (auto instr : insrList)
	// {
	// 	std::vector<Instruction *> expInstrs;

	// 	st.push(instr);
	// 	while (!st.empty())
	// 	{
	// 		auto ins = st.top();
	// 		if (vis.find(ins) != vis.end())
	// 		{
	// 			st.pop();
	// 			if (ins == nullptr)
	// 				continue;
	// 			ins->parent = this;
	// 			expInstrs.push_back(ins);
	// 			continue;
	// 		}
	// 		vis.insert(ins);
	// 		for (auto arg : ins->args)
	// 		{
	// 			auto a = dynamic_cast<Instruction *>(arg);
	// 			if (a == nullptr)
	// 				continue;
	// 			if (vis.find(a) == vis.end())
	// 				st.push(a);
	// 		}
	// 	}
	// 	//newInstrList.insert(newInstrList.end(), expInstrs.rbegin(), expInstrs.rend());
	// 	newInstrList.insert(newInstrList.end(), expInstrs.begin(), expInstrs.end());
	// }
	// insrList = newInstrList;
}