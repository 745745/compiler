#pragma once

#include"User.h"
#include"Value.h"
#include"BasicBlock.h"
#include"ConstantValue.h"

class BaseBlock;
class BaseBlock;
class Function;
class ConstantInt;

class Instruction :public User
{
public:
	enum OpID {
		constant,
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
		Mod,
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
		
		//Cmp
		EQ, //==
		NE, //!=
		GT, //>
		GE, //>=
		LT, //<
		LE,  //<=
		// Other operators
		PHI,
		Call,
		GEP,     // GetElementPtr
		ZExt,    // zero extend
		MulAdd,  // a*b+c
		//多条指令的结果求和
		VectorAdd
	};

	Instruction(OpID id, int argNum):id(id),User(intType) {};
	Instruction() :User(intType) {};
	void setarg(int num, vector<Value*> arg) ;
	void setParent(BaseBlock*); 
	OpID id;
	void debugPrint();
private:
	BaseBlock* parent;
};

class ConstInst :public Instruction
{
public:
	ConstInst(Value* val) { args.push_back(val); };
	static ConstInst* createConst(Value* val) { return new ConstInst(val); };
};


class UnaryInst :public Instruction
{
public:
	UnaryInst(Type* type, Value* val, BaseBlock* block, int OpID) {};
	static UnaryInst* createNeg(Value* val, BaseBlock* block) { return new UnaryInst(new Type(intType), val, block, Neg); };
	static UnaryInst* createNot(Value* val, BaseBlock* block){ return new UnaryInst(new Type(intType), val, block, Not); };
	static UnaryInst* createUnary(Value* val, BaseBlock* block,OpID id) { return new UnaryInst(new Type(intType), val, block, id); };
};

class AllocaInst :public Instruction
{
	AllocaInst(Type* ty) {};
	AllocaInst(Type* ty, int num) {};

public:
	static AllocaInst* createAlloca(Type* ty) {return new  AllocaInst(ty); }
	static AllocaInst* createAlloca(Type* ty,int num) { return new AllocaInst(ty,num); }
};

class StoreInst :public Instruction
{
	Value* offset;
	int address;
public:
	StoreInst(Value* val, int address):address(address){};
	StoreInst(Value* val, int address, Value* offset) :address(address),offset(offset) {}; //offset可能需要计算才能得到
	static StoreInst* createStore(Value* val, int address)
	{
		return new StoreInst(val, address);	
	}
	static StoreInst* createStore(Value* val, int address, Value* offset)
	{
		return new StoreInst(val, address,offset);
	};
};

//arg第一个是地址，第二个是偏移量
class LoadInst :public Instruction
{
	LoadInst(int address)
	{ 
		id = Load; 
		args.push_back(new ConstantInt(address));
	};
	LoadInst(int address, Value* offset) 
	{ 
		id = Load; 
		args.push_back(new ConstantInt(address));
		args.push_back(offset);
	};
public:
	static LoadInst* createLoad(int address)
	{
		return new LoadInst(address);
	}
	static LoadInst* createLoad(int address, Value* offset) 
	{
		return  new LoadInst(address,offset);

	}

};




class BinaryInst :public Instruction
{
public:
	BinaryInst(Value* val1, Value* val2, OpID OpID)
	{
		this->id = OpID;
		args.push_back(val1);
		args.push_back(val2);
	}

	BinaryInst(Value* val1, Value* val2, BaseBlock* block, OpID OpID)
	{
		this->id = OpID;
		args.push_back(val1);
		args.push_back(val2);
	};
	void setVal(Value* val, int pos) { setArg(val, pos); };
	static BinaryInst* createAdd(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, Add); };
	static BinaryInst* createSub(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, Sub); };
	static BinaryInst* createMul(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, Mul); };
	static BinaryInst* createDiv(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, Div); };
	static BinaryInst* createRem(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, Rem); };
	static BinaryInst* createAnd(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, And); };
	static BinaryInst* createOr(Value* val1, Value* val2, BaseBlock* block) { return new BinaryInst(val1, val2, block, Or); };
	static BinaryInst* createBinary(Value* val1, Value* val2,OpID id) { return new BinaryInst(val1, val2, id); };
};

class CmpInst :public Instruction
{
public:

	CmpInst(Type* type, Value* lhs, Value* rhs, BaseBlock* block, OpID cmp) 
	{ 
		id = cmp;
		args.push_back(lhs);
		args.push_back(rhs);
	}
	static CmpInst* createCMP(OpID op, Value* lhs, Value* rhs, BaseBlock* bb) { return new CmpInst(new Type(intType), lhs, rhs, bb, op); };
};

class BranchInst : public Instruction
{
public:
	BranchInst(Value* cond, BaseBlock* if_true, BaseBlock* if_false,
		BaseBlock* bb) 
	{
		id = Br;
		args.push_back(cond);
		args.push_back((Value*)if_true);
	}
	BranchInst(BaseBlock* if_true, BaseBlock* bb) 
	{
		id = Jmp;

	}
	BranchInst(CmpInst::OpID op, Value* lhs, Value* rhs, BaseBlock* if_true,
		BaseBlock* if_false, BaseBlock* bb) {};

	static BranchInst* createCondBr(Value* cond, BaseBlock* if_true,
		BaseBlock* if_false, BaseBlock* bb) {
		return new BranchInst(cond, if_true, if_false, bb);
	};
	static BranchInst* createBr(BaseBlock* if_true, BaseBlock* bb) { return new BranchInst(if_true, bb); };
	static BranchInst* createCmpBr(OpID op, Value* lhs, Value* rhs,
		BaseBlock* if_true, BaseBlock* if_false,
		BaseBlock* bb)
	{
		return new BranchInst(op, lhs, rhs, if_true, if_false, bb);
	}

};

class ReturnInst : public Instruction
{
public:
	ReturnInst(Value* val, BaseBlock* bb) {}
	ReturnInst(BaseBlock* bb) {}
	static ReturnInst* createRet(Value* val, BaseBlock* bb) { return new ReturnInst(val, bb); }
	static ReturnInst* createVoidRet(BaseBlock* bb) { return new ReturnInst(bb); }
};



class CallInst :public Instruction
{
public:
	CallInst(Function* func, std::vector<Value*> args, BaseBlock* bb) {}

	static CallInst* createCall(Function* func, std::vector<Value*> args,
		BaseBlock* bb)
	{
		return new CallInst(func, args, bb);
	}
};

class PhiInst :public Instruction
{
public:
	PhiInst(OpID op, std::vector<Value*> vals, std::vector<BaseBlock*> val_bbs,
		Type* ty, BaseBlock* bb);
	Value* val;
};


class vectorInst :public Instruction
{
public:
	vector<Instruction*> vec;
	vectorInst(vector<Instruction*> vals, BaseBlock* bb):vec(vals) {};
	static vectorInst* createVectorInst(vector<Instruction*> vec) { return new vectorInst(vec,nullptr); };
};