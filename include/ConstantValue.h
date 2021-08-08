#pragma once

#include<vector>
using std::vector;

class ConstantValue:public Value
{
public:
	enum constantValueType
	{
		typeInt,
		typeArray,
	};
	constantValueType ctype;
	virtual std::vector<int> getValue() const = 0;
};


class ConstantInt :public ConstantValue
{
public:
	ConstantInt(int val) :value(val) { ctype = typeInt; type = new Type(intType); isConstant = true; }
	int value;
	std::vector<int> getValue() const override { return { value }; }
};


class ConstantArray : public ConstantValue
{
public:
	ConstantArray(vector<int> val) :value(val) { ctype = typeArray; type = new Type(arrayType); isConstant = true;}
	vector<int> value;
	std::vector<int> getValue() const override { return value; }
};