#pragma once
#include<list>
#include"Type.h"

using std::list;
class Use
{
public:
	Value *val;
	int useNo;//like a=b+c.  for this use, b is 0, c is 1
	Use(Value* val, int useNo) : val(val), useNo(useNo) {};
};

class Value
{
public:
	Value(Type* type) :type(type) {};
	Value();
	list<Use>& getUseList() { return useList; };
	void addUse(Value* val, int useNo);
	
	//if a value changed,use this function to replace all value using this value
	void replaceAllUseWith(Value* newVal);
	
	void removeUse(Value* val, int useNo);

	//just for debug
	void debugPrint();
private:
	bool isConstant;//常量传播的时候用
	Type* type;
	list<Use> useList;
};