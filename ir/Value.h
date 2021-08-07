#pragma once
#include<list>
#include"Type.h"

using std::list;

class Use;
class Value
{
public:
	Value(Type* type) :type(type) { isConstant = false; };
	Value(typeName tName) { type = new Type(tName); isConstant = false;	};
	Value() { isConstant = false; };
	list<Use>& getUseList() { return useList; };
	void addUse(Value* val, int useNo);
	
	//if a value changed,use this function to replace all value using this value
	void replaceAllUseWith(Value* newVal);
	
	void removeUse(Value* val, int useNo);

	//just for debug
	virtual void debugPrint() {}

	bool isArray() { return type->tName == arrayType; }

	bool isInt() { return type->tName == intType; }

	bool isInstr() { return type->tName == instrType; }
	bool isConstant;
	Type* type;
private:
	list<Use> useList;
};

class Use
{
public:
	Value* val;
	int useNo;//like a=b+c.  for this use, b is 0, c is 1
	Use(Value* val, int useNo) : val(val), useNo(useNo) {};
};


