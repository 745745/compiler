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
	constantValueType type;
};


class ConstantInt :public ConstantValue
{
public:
	ConstantInt(int val) :value(val) { type = typeInt; };

private:
	int value;
};


class ConstantArray : public ConstantValue
{
public:
	ConstantArray(vector<int> val) :value(val) { type = typeArray; };
private:
	vector<int> value;
};