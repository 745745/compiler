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
		Jmp,
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
		// NEON SIMD
		VV, // sum(vector .* vector)
		BIC
	};

	Instruction(Type* type, OpID id, int argNum);
	void setArg(int num, vector<Value*> arg);
	void setParent(BaseBlock*);
private:
	OpID id;
	BaseBlock* parent;
};

class UnaryInst :public Instruction
{
public:
	UnaryInst(Type* type,Value* val,BaseBlock* block,int OpID);
	static UnaryInst* createNeg(Value* val, BaseBlock* block);
	static UnaryInst* createNot(Value* val, BaseBlock* block);
};

class AllocaInst :public Instruction
{
	AllocaInst(Type* ty);
	AllocaInst(Type* ty, int num);

public:
	static AllocaInst* createAlloca(Type* ty) {return new  AllocaInst(ty); }
	static AllocaInst* createAlloca(Type* ty,int num) { return new AllocaInst(ty,num); }
};

class StoreInst :public Instruction
{
public:
	StoreInst(Value* val, int address);
	StoreInst(Value* val, int address, int offset);
	static StoreInst* createStore(Value* val, int address)
	{
		return new StoreInst(val, address);	
	}
	static StoreInst* createStore(Value* val, int address, int offset)
	{
		return new StoreInst(val, address,offset);
	};
};

class LoadInst :public Instruction
{
	LoadInst(Type* ty, int address);
	LoadInst(Type* ty, int address, int offset);

public:
	static LoadInst* createLoad(Type* ty, int address)
	{
		return new LoadInst(ty, address);
	};
	static LoadInst* createLoad(Type* ty, int address, int offset) {
		return new LoadInst(ty, address, offset);
	}

};




class BinaryInst :public Instruction
{
public:
	BinaryInst(Type* type, Value* val1, Value* val2, BaseBlock* block, int OpID);
	BinaryInst(BaseBlock*);
	void setVal(Value* val, int pos);
	static BinaryInst* createAdd(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createSub(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createMul(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createDiv(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createRem(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createAnd(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createOr(Value* val1, Value* val2, BasicBlock* block);
	static BinaryInst* createSub(Value* val1, Value* val2, BasicBlock* block);
};

class CmpInst :public Instruction
{
public:
	enum CmpOp
	{
		EQ, //==
		NE, //!=
		GT, //>
		GE, //>=
		LT, //<
		LE  //<=
	};

	CmpInst(Type* type, Value* lhs, Value* rhs, BaseBlock* block, CmpOp cmp);
	static CmpInst* createCMP(CmpOp op, Value* lhs, Value* rhs, BaseBlock* bb);
};

class BranchInst : public Instruction
{
public:
	BranchInst(Value* cond, BaseBlock* if_true, BaseBlock* if_false,
		BaseBlock* bb);
	BranchInst(BaseBlock* if_true, BaseBlock* bb);
	BranchInst(CmpInst::CmpOp op, Value* lhs, Value* rhs, BaseBlock* if_true,
		BaseBlock* if_false, BaseBlock* bb);

	static BranchInst* createCondBr(Value* cond, BaseBlock* if_true,
		BaseBlock* if_false, BaseBlock* bb);
	static BranchInst* createBr(BaseBlock* if_true, BaseBlock* bb);
	static BranchInst* createCmpBr(CmpInst::CmpOp op, Value* lhs, Value* rhs,
		BaseBlock* if_true, BaseBlock* if_false,
		BaseBlock* bb);

};

class ReturnInst : public Instruction
{
public:
	ReturnInst(Value* val, BaseBlock* bb);
	ReturnInst(BaseBlock* bb);
	static ReturnInst* createRet(Value* val, BaseBlock* bb);
	static ReturnInst* createVoidRet(BaseBlock* bb);
};



class CallInst :public Instruction
{
public:
	CallInst(Function* func, std::vector<Value*> args, BaseBlock* bb);

	CallInst(Function* func, BaseBlock* bb);

	static CallInst* createCall(Function* func, std::vector<Value*> args,
		BaseBlock* bb);
};

class PhiInst :public Instruction
{
public:
	PhiInst(OpID op, std::vector<Value*> vals, std::vector<BaseBlock*> val_bbs,
		Type* ty, BaseBlock* bb);
	Value* val;
};
