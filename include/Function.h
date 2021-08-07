#pragma once
#include<list>
#include<vector>
#include<string>
#include"BasicBlock.h"
#include"User.h"
#include"Module.h"
#include"node.h"
#include"Instruction.h"
using std::list;
using std::vector;

class BaseBlock;
class Module;
class NExp;
class Instruction;

class Function :public User
{
public:
	void getFromStatment(NStmtList stmtList);
	
	void getFromBlock(NBlockStmt* block);

	void getFromWhile(NWhileStmt* whileStmt);

	void getFromIf(NIfStmt* ifstmt);

	void addSymbol(string name, Value* val);

	Value* findValue(string name);

	Instruction* getInstFromExp(NExp* p);

	Function(Type* type);


	static Function* makeFunction(Type* returnVal, vector<Type*>arg, vector<std::string> paraName);

	//block结束，将recoverTable中的符号重新写回symbolTable中
	void RecoverSymBol();

	void debugPrint();

	void setName(string name)
	{
		this->name = name;
	}

	void setParent(Module* p)
	{
		this->parent = p;
	}

	map<string, Value*> symbolTable;
	map<string, Value*> recoverTable;
	string name;
	BaseBlock* entry;
	BaseBlock* last;
	Module* parent;
};
