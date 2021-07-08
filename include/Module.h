#pragma once

#include<list>
#include<map>
#include<string>
#include"Value.h"
#include"Function.h"
#include"ConstantValue.h"

using std::list;
using std::map;
using std::string;

class Module
{
public:
	void addFunction(Function* f);
	void removeFunction(Function* f);

	void debugPrint();


private:
	list<Value*> globalVar;
	list<Function*> funcList;
	map<string, Value*> symbolTable;
	map<string, ConstantValue> valueTable;
	vector<int> regTable;
};