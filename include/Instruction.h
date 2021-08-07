#pragma once
#include <iostream>
#include <map>
#include"User.h"
#include"Value.h"
#include"BasicBlock.h"
#include"ConstantValue.h"
#include"Module.h"

using namespace std;
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
		Cmp,
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

	const std::map<OpID, const char* > name = {
	{constant,"constant"},
	// High IR
	{Break,"Break"},
	{Continue, "Continue"},
	// Terminator Instructions
	{Ret, "Ret"},
	{Br, "Br"},
	{Jmp, "Jmp"},
	// Standard unary operators
	{Neg, "Neg"},
	// Standard binary operators
	{Add, "Add"},
	{Sub, "Sub"},
	{RSub, "RSub"}, // Reverse Subtract
	{Mul, "Mul"},
	{Div, "Div"},
	{Rem, "Rem"},
	{AddAddr, "AddAddr"}, // deprecated
	// Logical operators
	{And, "And"},
	{Or, "Or"},
	{Not, "Not"},
	// Memory operators
	{Alloca, "Alloca"},
	{Load, "Load"},
	{Store, "Store"},
	// Shift operators
	{Shl, "Shl"},  // <<
	{AShr, "Ashr"}, // arithmetic >>
	{LShr, "LShr"}, // logical >>
	// Other operators
	{Cmp, "Cmp"},
	{PHI, "PHI"},
	{Call, "Call"},
	{GEP, "GEP"},     // GetElementPtr
	{ZExt, "ZExt"},    // zero extend
	{MulAdd, "MulAdd"},  // a*b+c
	//多条指令的结果求和
	{VectorAdd, "VectorAdd"},
	{EQ,"EQ"}, //==
	{NE,"NE"}, //!=
	{GT,"GT"}, //>
	{GE,"GE"}, //>=
	{LT,"LT"}, //<
	{LE,"LE"},  //<=
	};


	Instruction(OpID id, int argNum):id(id),User(instrType) {};
	Instruction() :User(instrType) {};
	void setarg(int num, vector<Value*> arg) ;
	void setParent(BaseBlock*); 
	OpID id;
	void debugPrint();
	bool isconst = false;
private:
	BaseBlock* parent;
};

class ConstInst :public Instruction
{
public:
	ConstInst(Value* val) { args.push_back(val); id = constant; };
	static ConstInst* createConst(Value* val) { return new ConstInst(val); };
};


class UnaryInst :public Instruction
{
public:
	UnaryInst(Type* type, Value* val, BaseBlock* block, OpID opid) 
	{ 
		id = opid;
		args.push_back(val);
	};
	static UnaryInst* createNeg(Value* val, BaseBlock* block) { return new UnaryInst(new Type(intType), val, block, Neg); };
	static UnaryInst* createNot(Value* val, BaseBlock* block){ return new UnaryInst(new Type(intType), val, block, Not); };
	static UnaryInst* createUnary(Value* val, BaseBlock* block,OpID id) { return new UnaryInst(new Type(intType), val, block, id); };
};

class AllocaInst :public Instruction
{
	AllocaInst(Type* ty) { id = Alloca; }
	AllocaInst(Type* ty, int num) 
	{
		id = Alloca;
		ConstantInt* constInt = new ConstantInt(num);
		args.push_back(constInt);
	}

public:
	static AllocaInst* createAlloca(Type* ty) {return new  AllocaInst(ty); }
	static AllocaInst* createAlloca(Type* ty,int num) { return new AllocaInst(ty,num); }
};

class StoreInst :public Instruction
{
	Value* offset;
	int address;
public:
	StoreInst(Value* val, int address) :address(address) 
	{ 
		id = Store; 
		args.push_back(val);
		ConstantInt* constInt = new ConstantInt(address);
		args.push_back(constInt);
	}
	StoreInst(Value* val, int address, Value* offset) :address(address),offset(offset) //offset可能需要计算才能得到
	{
		id = Store;
		args.push_back(val);
		ConstantInt* constInt = new ConstantInt(address);
		args.push_back(constInt);
		args.push_back(offset);
	}
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
		if(if_false!=nullptr)
			args.push_back((Value*)if_false);
	}
	BranchInst(BaseBlock* if_true, BaseBlock* bb) 
	{
		id = Jmp;
		args.push_back((Value*)if_true);
	}

	static BranchInst* createCondBr(Value* cond, BaseBlock* if_true,
		BaseBlock* if_false, BaseBlock* bb) {
		return new BranchInst(cond, if_true, if_false, bb);
	};

	static BranchInst* createBr(BaseBlock* if_true, BaseBlock* bb) { return new BranchInst(if_true, bb); };


};

class ReturnInst : public Instruction
{
public:
	ReturnInst(Value* val, BaseBlock* bb) { id = Ret; args.push_back(val); }
	ReturnInst(BaseBlock* bb) { id = Ret; }
	static ReturnInst* createRet(Value* val, BaseBlock* bb) { return new ReturnInst(val, bb); }
	static ReturnInst* createVoidRet(BaseBlock* bb) { return new ReturnInst(bb); }
};



class CallInst :public Instruction
{
public:
	CallInst(Function* func, std::vector<Value*> args, BaseBlock* bb) 
	{
		id = Call;
		args.push_back((Value*)func);
		for (int i = 0; i < args.size(); i++)
		{
			this->args.push_back(args[i]);
		}
	}

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
	vectorInst(vector<Instruction*> vals, BaseBlock* bb):vec(vals) 
	{
		id = VectorAdd;
		for (int i = 0; i < vals.size(); i++)
		{
			args.push_back(vals[i]);
		}
	}
	static vectorInst* createVectorInst(vector<Instruction*> vec) { return new vectorInst(vec,nullptr); };
};