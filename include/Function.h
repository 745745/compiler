#pragma once
#include <sstream>
#include <stack>
#include <set>
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

const int MaxParamsPassedByReg = 4;

static std::string getTypeType(Type* type)
{
	if (type->tName == typeName::arrayType)
	{
		auto t = reinterpret_cast<ArrayType*>(type);
		std::stringstream ss;
		ss << getTypeStr(t->tName) + "[" + std::to_string(t->num) + "]";
		if (t->ptr)
			ss << "*";
		return ss.str();
	}
	return getTypeStr(type->tName);
}

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
	std::vector<BaseBlock*> getAllBlocks();
	void linearizeInstrTrees();
	vector<int>* getArrayParamDefine(string name);
	void addArrayParamDefine(string name, vector<int> dim);

	map<string, Value*> symbolTable;
	map<string, Value*> recoverTable;
	string name;
	BaseBlock* entry;
	BaseBlock* last;
	Module* parent;
	std::vector<BaseBlock*> blocks;
	std::map<Value*, std::string> revSymbolTable;

	std::map<Value*, int> addressTable;
	
	std::map<string, vector<int>> arrayDefine;


	std::vector<Value*> params;
	std::set<Value*> paramSet;
	int nTempVars;
};
