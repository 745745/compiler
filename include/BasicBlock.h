#pragma once

#include<map>
#include<list>
#include<set>

#include"Value.h"
#include"Instruction.h"
#include"Function.h"
using std::map;
using std::list;
using std::set;


class BaseBlock 
{
public:
	enum BlockType 
	{
		Basic,
		If,
		While,
	};

	void addInst(Instruction* inst);

	BlockType blockType;
	BaseBlock* parent; //依据parent来查找符号表
	Function* func;
	std::vector<Instruction*> insrList;
	std::vector<BaseBlock*> pre_bbs_;
	std::vector<BaseBlock*> succ_bbs_;


	BaseBlock()
	{
		parent = nullptr;
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

//ifblock,最后都会转化成BasicBlock,作为中间类方便AST翻译
class IfBlock :public BaseBlock
{
	Instruction* judge;
	BaseBlock* trueBlock;
	BaseBlock* falseBlock;
};

//whileblock同上
class WhileBlock :public BaseBlock
{
public:
	Instruction* judge;
	vector<Instruction*> allInst;
};