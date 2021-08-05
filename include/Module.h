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

void Module::debugPrint()
{
	cout << "Module " << endl;
	cout << "Value " << endl;
	for (auto value : globalVar)
	{
		value->debugPrint();
		cout << " " << endl;
	}
	cout << "Function " << endl;
	for (auto function : funcList)
	{
		function->debugPrint();
	}
	cout << "symbolTable " <<endl;
	map<std::pair<string,BaseBlock*>, Value*>::iterator iter1;
	for (iter1 = symbolTable.begin(); iter1 != symbolTable.end(); iter1++)
	{
		cout << iter1->first.first;
		cout << " " ;
		cout << iter1->first.second->blockType;
		cout << " " ;
		iter1->second->debugPrint();
		cout << " " <<endl;
	}
	cout << "valueTable " <<endl;
	map<Value*, ConstantValue*>::iterator iter2;
	for (iter2 = valueTable.begin(); iter2 != valueTable.end(); iter2++)
	{
		iter2->first->debugPrint();
		cout << " " ;
		iter2->second->debugPrint();
		cout << " " << endl;
	}
	cout << "addressTable " <<endl;
	map<Value*, int>::iterator iter3;
	for (iter3 = addressTable.begin(); iter3 != addressTable.end(); iter3++)
	{
		iter3->first->debugPrint();
		cout << " " << iter3->second << endl;
	}
	
}