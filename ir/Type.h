#pragma once

#include<vector>
using std::vector;
enum typeName
{
	voidType,
	intType,
	functionType,
	arrayType,
	ptrType,
	instrType
};

const std::string TypeStr[] = 
{
	"Void", "Int", "Func", "Arr", "Ptr", "Instr"
};

static std::string getTypeStr(typeName type)
{
	return TypeStr[type];
}

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
	explicit FunctionType(Type* returnType, vector<Type*> args) :Type(functionType) { this->returnType = returnType; this->args = args; };
	Type* returnType;
	vector<Type*> args;
};


class ArrayType :public Type
{
public:
	explicit ArrayType(int num, bool ptr = false) :
		num(num), ptr(ptr), Type(arrayType) { tName = arrayType;  };
	bool ptr;
	int num;
};

class ptrType
{

};

class instrType
{};