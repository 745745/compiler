#pragma once

#include<vector>
using std::vector;
enum typeName
{
	voidType,
	intType,
	functionType,
	arrayType,
};

class Type
{
public:
	typeName tName;
	Type(typeName tName) { this->tName = tName; };
	Type() {};
};


class IntType :public Type
{
public:
	IntType():Type(intType) { tName = intType; };
};

class FunctionType :public Type
{
public:
	explicit FunctionType(Type* returnType, vector<Type*> args):Type(functionType) {};
	Type* returnType;
	vector<Type*> args;
};


class ArrayType :public Type
{
public:
	explicit ArrayType(int num):num(num), Type(arrayType) { tName = arrayType;  };
	int num;
};

