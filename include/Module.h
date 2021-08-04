#pragma once

#include<list>
#include<map>
#include<string>
#include"Value.h"
#include"Function.h"
#include"ConstantValue.h"
#include"node.h"

using std::list;
using std::map;
using std::string;

class Module
{
public:
	void addFunction(Function* f);
	void removeFunction(Function* f);
	void getFunction(string funcName);
	Value* getValue(string name);
	ConstantValue* getConstantValue(Value*);
	void regValueTable(Value* var, ConstantValue* val);
	void debugPrint();

	void addGlobalVar(Value*);
	void addSymbol(string name,BaseBlock*, Value*); //if baseblock ==nullptr ,Value is a global variable
	void addConstantValue(Value*, ConstantValue*);
	void ASTTranslate(NCompUnit* cu);

	void addAddress(Value*, int);
	BaseBlock* getFromStatment(NStmtList stmtList);

	Value* findValue(string name, BaseBlock* p);
	int getAddress(Value*);

private:
	vector<Value*> globalVar;
	vector<Function*> funcList;
	map<std::pair<string,BaseBlock*>, Value*> symbolTable;
	map<Value*, ConstantValue*> valueTable;
	map<Value*, int> addressTable;
};