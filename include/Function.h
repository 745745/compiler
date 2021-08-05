#pragma once
#include<list>
#include<vector>
#include<string>
#include"BasicBlock.h"
#include"User.h"
#include"Module.h"
#include"node.h"
using std::list;
using std::vector;

class BaseBlock;
class Module;

class Function :public User
{
public:
	void addBasicBlock(BaseBlock* p);

	void removeBasicBlock(BaseBlock* p);

	void getFromStatment(NStmtList stmtList);
	
	void getFromBlock(NBlockStmt* block);

	void getFromWhile(NWhileStmt* whileStmt);

	void getFromIf(NIfStmt* ifstmt);

	static void addSymbol(string name, Value* val) { symbolTable.insert(make_pair(name, val)); };

	Value* findValue(string name, BaseBlock* p) { return (symbolTable.find(name))->second; };

	Instruction* getInstFromExp(NExp* p);

	Function(Type* type) :User(type) {};

	static Function* makeFunction(Type* returnVal, vector<Type*>arg, vector<std::string> paraName);



	void debugPrint();

	void setName(string name)
	{
		this->name = name;
	}

	void setParent(Module* p)
	{
		this->parent = p;
	}

	static map<string, Value*> symbolTable;
	static map<string, Value*> recoverTable;
	string name;
	BaseBlock* entry;
	BaseBlock* last;
	Module* parent;

};
