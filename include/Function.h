#pragma once
#include<list>
#include<vector>
#include"BasicBlock.h"
#include"User.h"
#include"Module.h"
using std::list;
using std::vector;

class Function :public User
{
public:
	void addBasicBlock(BaseBlock* p);
	void removeBasicBlock(BaseBlock* p);

	Function(Type* type) :User(type) {};


	int FunctionCompute();
	static Function* makeFunction(Type* returnVal, vector<Type*>arg)
	{
		FunctionType* type = new FunctionType(returnVal, arg);
		Function* p = new Function(type);
		return p;
	}

	void debugPrint();

	void setName(string name)
	{
		this->name = name;
	}

	void setParent(Module* p)
	{
		this->parent = p;
	}


private:
	int returnValue;
	string name;
	BaseBlock* entry;
	Module* parent;
};

void Function::debugPrint()
{
	cout << name << " " << returnValue << " " << entry->blockType << " " << endl;
}
