#pragma once

#include<map>
#include<list>
#include<set>

#include"Value.h"
#include"Function.h"
using std::map;
using std::list;
using std::set;



class BaseBlock :public Value
{
	enum BlockType 
	{
		Basic,
		If,
		While,
	};

	BlockType blockType;
	BaseBlock* parent;
	Function* func;

};





class BasicBlock:public BaseBlock
{
public:
	void addInst(Instruction* inst);



private:
	std::map<Value*, std::set<Value*>> reach_assign_in_; // data flow
	std::map<Value*, std::set<Value*>> reach_assign_out_;

	std::list<BasicBlock*> pre_bbs_;
	std::list<BasicBlock*> succ_bbs_;

	std::set<BasicBlock*> doms_;        // dominance set
	BasicBlock* idom_ = nullptr;         // immediate dominance
	std::set<BasicBlock*> domFrontier_; // dominance frontier set
	std::set<BasicBlock*> domTreeSuccBlocks_;

	//后端应该只会用下面的指令列表，前面是做SSA用的
	std::list<Instruction*> insrList;
};