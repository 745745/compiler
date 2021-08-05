#include"../include/Function.h"


map<string, Value*> Function::symbolTable;
map<string, Value*> Function::recoverTable;
SymbolTable Node::symboltb;

bool isReturnStmt(NStmt* p)
{
	if (dynamic_cast<NReturnStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isIfStmt(NStmt* p)
{
	if (dynamic_cast<NIfStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isDeclStmt(NStmt* p)
{
	if (dynamic_cast<NDeclStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isWhileStmt(NStmt* p)
{
	if (dynamic_cast<NWhileStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isBlockStmt(NStmt* p)
{
	if (dynamic_cast<NBlockStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isBreakStmt(NStmt* p)
{
	if (dynamic_cast<NBreakStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isAssignStmt(NStmt* p)
{
	if (dynamic_cast<NAssignStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool iscontinueStmt(NStmt* p)
{
	if (dynamic_cast<NContinueStmt*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isIdentifierExp(NExp* p)
{
	if (dynamic_cast<NIdentifierExp*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isBinaryExp(NExp* p)
{
	if (dynamic_cast<NBinaryExp*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isUnaryExp(NExp* p)
{
	if (dynamic_cast<NUnaryExp*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

bool isCallExp(NExp* p)
{
	if (dynamic_cast<NCallExp*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}

Instruction::OpID getOpId(int op)
{}


int judgeExp(NExp* exp)
{
	if (isIdentifierExp(exp))
		return 1;
	if (isBinaryExp(exp))
		return 2;
	if (isUnaryExp(exp))
		return 3;
	if (isCallExp(exp))
		return 4;
}

Instruction* Function::getInstFromExp(NExp* p)
{
	switch (judgeExp(p))
	{
	case 1:
	{
		NIdentifierExp* ident = dynamic_cast<NIdentifierExp*>(p);
		string name = ident->name.name;
		if (ident->array_def.size() != 0)//array
		{

		}
		else //int
		{
			Value* val = findValue(name, last);
			int address = parent->getAddress(val);
			Instruction* instr = LoadInst::createLoad(new Type(intType), address);
			return instr;
		}
	}
	case 2:
	{
		NBinaryExp* bi = dynamic_cast<NBinaryExp*>(p);
		Instruction* left = getInstFromExp(&(bi->lhs));
		Instruction* right = getInstFromExp(&(bi->rhs));
		Instruction* instr = BinaryInst::createBinary(left, right, getOpId(bi->op));
		return instr;
	}
	case 3:
	{
		NUnaryExp* bi = dynamic_cast<NUnaryExp*>(p);
		Instruction* left = getInstFromExp(&(bi->rhs));
		Instruction* instr = UnaryInst::createUnary(left, nullptr, getOpId(bi->op));
		return instr;
	}
	case 4:
	{
		NCallExp* bi = dynamic_cast<NCallExp*>(p);
		string funcName = bi->function_name.name;
		Function* func = parent->getFunction(funcName);
		vector<Value*> para; //写的是Value*，实际上里面都是Instruction*
		for (int i = 0; i < bi->parameters.size(); i++)
		{
			para.push_back(getInstFromExp(bi->parameters[i]));
		}
		Instruction* instr = CallInst::createCall(func, para, nullptr);
		return instr;
	}
	}

}


void Function::getFromIf(NIfStmt* ifstmt)
{
	
}

void Function::getFromWhile(NWhileStmt* whileStmt)
{}


void Function::getFromBlock(NBlockStmt* block)
{}



int judgeStmt(NStmt* p)
{
	if (isReturnStmt(p))
		return 1;
	if (isIfStmt(p))
		return 2;
	if (isDeclStmt(p))
		return 3;
	if (isWhileStmt(p))
		return 4;
	if (isBlockStmt(p))
		return 5;
	if (isBreakStmt(p))
		return 6;
	if (isAssignStmt(p))
		return 7;
	if (iscontinueStmt(p))
		return 8;
}

void Function::getFromStatment(NStmtList stmtList)
{
	BaseBlock* now =last;
	now->parent = nullptr;
	NStmt* stmt;
	for (int i = 0; i < stmtList.size(); i++)
	{
		stmt = dynamic_cast<NStmt*>(stmtList[i]);
		switch (judgeStmt(stmt))
		{
		case 1:
		{
			NReturnStmt* ret = dynamic_cast<NReturnStmt*>(stmt);
			Instruction* instr = getInstFromExp(ret->return_value);
			now->insrList.push_back(instr);
			break;
		}
		case 2:
		{	
			getFromIf(dynamic_cast<NIfStmt*>(stmt));
			break;
		}
		case 3:
		{
			NDeclList declList = dynamic_cast<NDeclStmt*>(stmt)->declarations;
			for (auto decl : declList)
			{
				auto dec = dynamic_cast<NVarDecl*>(decl);
				if (dec->size == 0)  //int
				{
					Type* p = new IntType();
					Instruction* instr = AllocaInst::createAlloca(p);
					Value* newVal = new Value(p);
					string name = dec->identifier.name;
					parent->addAddress(newVal, parent->address);
					parent->address += 4;
					now->addInst(instr);
					addSymbol(name, newVal);
					int val = 0;
					if (dec->init)
					{
						val = dec->initvalue->GetValue();
						newVal->isConstant = true;
					}
					ConstantInt* constInt = new ConstantInt(val);
					int address = this->parent->getAddress(newVal);
					instr = StoreInst::createStore(constInt, address - 4);		
					now->addInst(instr);
				}

				else //array
				{
					Type* p = new ArrayType(dec->size);
					Instruction* instr = AllocaInst::createAlloca(p, dec->size);
					Value* newVal = new Value(p);
					string name = dec->identifier.name;
					parent->addAddress(newVal, parent->address);
					parent->address += 4 * dec->size;
					now->addInst(instr);
					addSymbol(name, newVal);
					if (dec->init)
					{
						newVal->isConstant = true;
						for (int i = 0; i < dec->size; i++)
						{
							int val = (*dec->finalInitValue)[i];
							ConstantInt* constInt = new ConstantInt(val);
							int address = this->parent->getAddress(newVal);
							Instruction* instr = StoreInst::createStore(constInt, address - 4 * (dec->size - i));
						}
					}
				}
			}
		}

		case 4:
		{
			getFromWhile(dynamic_cast<NWhileStmt*>(stmt));
			break;
		}
		case 5:
		{	
			getFromBlock(dynamic_cast<NBlockStmt*>(stmt));
			break;
		}
		case 6:
			//break 只会在while里面出现，在这里可以不管
			break;

		case 7:
		{
			NAssignStmt* assign = dynamic_cast<NAssignStmt*>(stmt);
			string name = assign->name.name;
			Value* var = findValue(name, now);
			int address = parent->getAddress(var);
			if (var->isArray())
			{
				IntList dim = (*assign->GetDimensions());
				vector<int>mult;//记录数组各维度的乘积，方便将高维访问转化为低维访问
				int init = 1;
				mult.push_back(init);
				Instruction* rhs = getInstFromExp(&assign->rhs);
				now->addInst(rhs);
				for (int i=1;i<dim.size();i++)
				{
					init *= dim[i];
					mult.push_back(init);
				}

				//数组定义为a[3][2][2],访问a[2][1][1],转化为a[3*2*2]访问a[2*4+1*2+1*1]
				//2*4+1*2+1*1需要多条指令来计算 
				vector<Instruction*> computeOffset;
				int size = assign->lengths.size();
				for (int i=0;i<size;i++)
				{
					ConstantInt* constInt = new ConstantInt(mult[size-1-i]);
					Instruction* val2 = getInstFromExp(assign->lengths[i]);
					Instruction* instr = BinaryInst::createMul(constInt, val2, now);
					computeOffset.push_back(instr);
									
				}
				Instruction* instr = vectorInst::createVectorInst(computeOffset);
				Instruction* store = StoreInst::createStore(rhs, address, (Value*)instr);
				now->addInst(store);
			}

			if (var->isInt())
			{
				Instruction* rhs = getInstFromExp(&assign->rhs);
				Instruction* store = StoreInst::createStore(rhs, address);
				now->addInst(store);
			}

		}
		case 8: break;
		default:	break;
		}
	}
	return;
}

Function* Function::makeFunction(Type* returnVal, vector<Type*>arg, vector<std::string> paraName)
{
	FunctionType* type = new FunctionType(returnVal, arg);
	Function* p = new Function(type);
	BaseBlock* first = new BaseBlock();
	p->entry = first;
	p->last = first;
	for (int i = 0; i < type->args.size(); i++)
	{
		auto para = type->args[i];
		if (para->tName == intType)
		{
			Type* type = new IntType;
			Instruction* p = AllocaInst::createAlloca(type);
			first->addInst(p);
			Value* val = new Value(type);
			addSymbol(paraName[i], val);
		}
		else
		{
			Type* type = new ArrayType(((ArrayType*)para)->num);
			Instruction* p = AllocaInst::createAlloca(type);
			first->addInst(p);
			Value* val = new Value(type);
			addSymbol(paraName[i], val);
		}
	}
	return p;
}



void Function::debugPrint()
{
	cout << "Function: " << name;
	BaseBlock* p = entry;
	while (p->succ_bbs_.size()!=0)
	{
		p->debugPrint();
		p = p->succ_bbs_[0];
	}
	cout << endl;


}