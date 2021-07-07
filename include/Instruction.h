#pragma once


#include"User.h"
#include"Value.h"
#include"BasicBlock.h"


class Instruction :public User
{
public:
	//先借用中科大的，后面有需要可以再改
	enum OpID {
		// High IR
		Break,
		Continue,
		// Terminator Instructions
		Ret,
		Br,
		// Standard unary operators
		Neg,
		// Standard binary operators
		Add,
		Sub,
		RSub, // Reverse Subtract
		Mul,
		Div,
		Rem,
		AddAddr, // deprecated
		// Logical operators
		And,
		Or,
		Not,
		// Memory operators
		Alloca,
		Load,
		Store,
		// Shift operators
		Shl,  // <<
		AShr, // arithmetic >>
		LShr, // logical >>
		// Other operators
		Cmp,
		PHI,
		Call,
		GEP,     // GetElementPtr
		ZExt,    // zero extend
		MulAdd,  // a*b+c
		MTSTART, // %thread_id = MTSTART
		MTEND,   // MTEND %thread_id
		// NEON SIMD
		VV, // sum(vector .* vector)
		BIC
	};

	Instruction(Type* type, OpID id, int argNum);
	void setArg(int num, vector<Value*> arg);
private:
	OpID id;
	BasicBlock* parent;
};