#pragma once
#include"Function.h"
#include<list>
#include<map>
#include<string>
#include<iostream>

#include"Value.h"
#include"ConstantValue.h"
#include"node.h"

using std::list;
using std::map;
using std::string;

class Function;

class Module
{
public:
	static void addFunction(Function* f) { funcList.push_back(f); };
	static void removeFunction(Function* f){};
	Function* getFunction(string funcName);
	vector<Function*> getFunctionList(){
		return funcList;
	};

	Value* getGlobalValue(string name) 
	{
		auto iter = globalVar.find(name);
		if (iter != globalVar.end())
		{
			return iter->second;
		}
		else return nullptr;
	}

	ConstantValue* getConstantValue(Value* val)
	{
		auto iter = valueTable.find(val);
		if (iter != valueTable.end())
		{
			return iter->second;
		}
		else return nullptr;
	}
	void regValueTable(Value* var, ConstantValue* val);

	void debugPrint();

	void addGlobalVar(string name, Value* val) { globalVar.insert(make_pair(name, val)); }
	void addConstantValue(Value* val, ConstantValue* cVal) { valueTable.insert(make_pair(val, cVal)); };
	void ASTTranslate(NCompUnit* cu);

	static void addName(Value* val,string name);
	static string getName(Value*);

	void addAddress(Value* p, int add) { addressTable.insert(make_pair(p, add)); };

	int getAddress(Value* p) 
	{ 
		auto iter = addressTable.find(p);
		if (iter != addressTable.end())
			return iter->second;
		else return 0;
	}
	int address = 0;
private:
	map<string, Value*>globalVar;
	static vector<Function*> funcList;
	map<Value*, ConstantValue*> valueTable;
	map<Value*, int> addressTable;
	static map<Value*, string> nameTable;
};
