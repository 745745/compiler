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
};

class Type
{
public:
	typeName tName;
	explicit Type();
};


class IntType :public Type
{
public:
	IntType();
};

class FunctionType :public Type
{
public:
	explicit FunctionType(Type* returnType,vector<Type*> args);

private:
	Type* returnType;
	vector<Type*> args;
};


class ArrayType :public Type
{
public:
	explicit ArrayType(int num);
private:
	int num;
	Type* elementType;
};


class PtrType :public Type
{
public:
	explicit PtrType(Type* type);
private:
	Type* ptrType;
};