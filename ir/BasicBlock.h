#pragma once

#include <iostream>
#include<map>
#include<list>
#include<set>

#include"Value.h"
#include"Instruction.h"
#include"Function.h"
using std::map;
using std::list;
using std::set;

class Function;
class Instruction;

class BaseBlock :public Value
{
public:
	enum BlockType 
	{
		Basic,
		If,
		While,
	};

	void addInst(Instruction* inst);
	void linearizeInstrs();

	BlockType blockType;
	BaseBlock* parent; 
	Function* func;
	std::vector<Instruction*> insrList;
	std::vector<BaseBlock*> pre_bbs_;
	std::vector<BaseBlock*> succ_bbs_;
	int idx;

	void debugPrint();

	BaseBlock():Value(voidType)
	{
		parent = nullptr;
		blockType = Basic;
	}
};



class BasicBlock:public BaseBlock
{
public:
	
private:
	std::map<Value*, std::set<Value*>> reach_assign_in_; // data flow
	std::map<Value*, std::set<Value*>> reach_assign_out_;

	std::set<BasicBlock*> doms_;        // dominance set
	BasicBlock* idom_ = nullptr;         // immediate dominance
	std::set<BasicBlock*> domFrontier_; // dominance frontier set
	std::set<BasicBlock*> domTreeSuccBlocks_;

};


class IfBlock :public BaseBlock
{
	Instruction* judge;
	BaseBlock* trueBlock;
	BaseBlock* falseBlock;
};


class WhileBlock :public BaseBlock
{
public:
	Instruction* judge;
	vector<Instruction*> allInst;
};