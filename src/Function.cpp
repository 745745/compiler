#include"../include/Function.h"
#include<stack>
using std::stack;


SymbolTable Node::symboltb;

stack<BaseBlock*> whileIn;
stack<BaseBlock*> whileOut;


extern vector<string> t;
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

bool isExpStmt(NStmt* p)
{
	if (dynamic_cast<NExpStmt*>(p) == nullptr)
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

bool isInteger(NExp* p)
{
	if (dynamic_cast<NInteger*>(p) == nullptr)
	{
		return false;
	}
	else return true;
}


Instruction::OpID getOpId(int op)
{
	switch (op)
	{
	case 267:
		return Instruction::EQ; break;
	case 268:
		return Instruction::NE; break;
	case 269:
		return Instruction::LE; break;
	case 270:
		return Instruction::GE; break;
	case 271:
		return Instruction::LT; break;
	case 272:
		return Instruction::GT; break;
	case 273:
		return Instruction::Not; break;
	case 274:
		return Instruction::And; break;
	case 275:
		return Instruction::Or; break;
	case 276:
		return Instruction::Add; break;
	case 277:
		return Instruction::Sub; break;
	case 278:
		return Instruction::Mul; break;
	case 279:
		return Instruction::Div; break;
	case 280:
		return Instruction::Mod; break;
	case 281:
		return Instruction::Div; break;
	}
}

bool isPreDefinedFunc(string name)
{
	for (auto i : t)
	{
		if (name == i)
			return true;
	}
	return false;
}

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
	if (isInteger(exp))
		return 5;
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
			IntList dim = *(ident->GetDimensions());
			vector<int>mult;//记录数组各维度的乘积，方便将高维访问转化为低维访问
			int init = 1;
			mult.push_back(init);
			for (int i = 1; i < dim.size(); i++)
			{
				init *= dim[i];
				mult.push_back(init);
			}

			//数组定义为a[3][2][2],访问a[2][1][1],转化为a[3*2*2]访问a[2*4+1*2+1*1]
			//2*4+1*2+1*1需要多条指令来计算 
			vector<Instruction*> computeOffset;
			int size = ident->array_def.size();
			for (int i = 0; i < size; i++)
			{
				Value* val1 = new ConstantInt(mult[size-1-i]);
				Instruction* val2 = getInstFromExp(ident->array_def[i]);
				Instruction* instr = BinaryInst::createMul(val1, val2,last);
				computeOffset.push_back(instr);
			}
			Instruction* instr = vectorInst::createVectorInst(computeOffset);
			return instr;
		}
		else //int
		{
			Value* val = findValue(name);
			int address = parent->getAddress(val);
			Instruction* instr = LoadInst::createLoad(address);
			return instr;
		}
	}
	case 2:
	{
		NBinaryExp* bi = dynamic_cast<NBinaryExp*>(p);
		Instruction* left = getInstFromExp(&(bi->lhs));
		Instruction* right = getInstFromExp(&(bi->rhs));
		Instruction* instr;
		if (bi->op <= 272)
			instr = CmpInst::createCMP(getOpId(bi->op),left,right,nullptr);
		else instr = BinaryInst::createBinary(left, right, getOpId(bi->op));
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
		Function* func;
		func = parent->getFunction(funcName);
		vector<Value*> para; //写的是Value*，实际上里面都是Instruction*
		for (int i = 0; i < bi->parameters.size(); i++)
		{
			para.push_back(getInstFromExp(bi->parameters[i]));
		}
		Instruction* instr = CallInst::createCall(func, para, nullptr);
		return instr;
	}

	case 5:
	{
		NInteger* Int= dynamic_cast<NInteger*>(p);
		ConstantInt* constint = new ConstantInt(Int->GetValue());
		Instruction* instr = ConstInst::createConst(constint);
		instr->isConstant = true;
		instr->isconst = true;
		return instr;
	}
	}

}

Function::Function(Type* type):User(type)
{
	entry = last = new BaseBlock();
}


void Function::getFromIf(NIfStmt* ifstmt)
{
	Instruction* instr = getInstFromExp(&ifstmt->condition);	
	BaseBlock* now = last;
	BaseBlock* next = new BaseBlock();
	

	BaseBlock* trueLast;
	BaseBlock* falseLast;
	BaseBlock* falseStart;
	BaseBlock* trueStart=new BaseBlock;

	last->succ_bbs_.push_back(trueStart);
	last->succ_bbs_.push_back(next);



	bool False = (ifstmt->false_statement != nullptr);
	Instruction* branch;
	if (False) //False存在
	{
		falseStart = new BaseBlock();
		last->succ_bbs_[1] = falseStart;
		branch = BranchInst::createCondBr(instr, trueStart, falseStart,nullptr);
	}
	else branch = BranchInst::createCondBr(instr, trueStart, next, nullptr);

	last->addInst(branch);

	//处理True分支
	trueStart->pre_bbs_.push_back(now);
	last = trueStart;
	NStmt* trueStmt = &(ifstmt->true_statement);
	NBlockStmt* b = dynamic_cast<NBlockStmt*>(trueStmt);
	if (b!=nullptr)
	{
		getFromBlock(b);
		last->succ_bbs_.push_back(next);
		trueLast = last;
	}
	else
	{
		//单条指令仍然要新开一个block放
		trueStart->pre_bbs_.push_back(now);
		NStmtList p;
		p.push_back(trueStmt);
		getFromStatment(p);
		trueStart->succ_bbs_.push_back(next);
		trueLast = last;
	}

	RecoverSymBol();

	if (False)
	{
		falseStart->pre_bbs_.push_back(now);
		last = falseStart;
		NStmt* trueStmt = ifstmt->false_statement;
		NBlockStmt* b = dynamic_cast<NBlockStmt*>(trueStmt);
		if (b != nullptr)
		{
			getFromBlock(b);
			last->succ_bbs_.push_back(next);
			falseLast = last;
		}
		else
		{
			//单条指令
			NStmtList p;
			p.push_back(trueStmt);
			getFromStatment(p);
			falseStart->succ_bbs_.push_back(next);
			falseLast = last;
		}
		RecoverSymBol();
		
	}

	if (False)
	{
		next->pre_bbs_.push_back(trueLast);
		next->pre_bbs_.push_back(falseStart);
	}
	else
	{
		next->pre_bbs_.push_back(trueLast);
		next->pre_bbs_.push_back(now);
	}
	last = next;
}

void Function::getFromWhile(NWhileStmt* whileStmt)
{
	Instruction* condition = getInstFromExp(&whileStmt->condition);
	Instruction* p = UnaryInst::createNot(condition, nullptr); //条件为假时，p为真，跳到out执行
	BaseBlock* out = new BaseBlock();//while结束后下一个block
	BaseBlock* next = new BaseBlock();//while内容block
	Instruction* branch = BranchInst::createCondBr(p, out, nullptr, nullptr);//满足条件
	Instruction* jmp = BranchInst::createBr(next, nullptr);//结束后跳回

	last->succ_bbs_.push_back(next);
	next->pre_bbs_.push_back(last);
	next->addInst(branch);
	last = next;
	whileIn.push(next);
	whileOut.push(out);
	NBlockStmt* b = dynamic_cast<NBlockStmt*>(&whileStmt->statement);
	if (b != nullptr)
	{
		getFromBlock(b);
		last->succ_bbs_.push_back(whileIn.top());
		last->addInst(jmp);
		
	}
	else
	{
		//单条指令
		NStmtList p;
		p.push_back(&whileStmt->statement);
		getFromStatment(p);
		last->succ_bbs_.push_back(whileIn.top());
		last->addInst(jmp);
		out->pre_bbs_.push_back(whileIn.top());
	}

	RecoverSymBol();
	last = out;
}


void Function::getFromBlock(NBlockStmt* block)
{
	BaseBlock* p;
	if (last->insrList.size() == 0)
		p = last;
	else 
	{
		p = new BaseBlock();
		p->pre_bbs_.push_back(last);
		last->succ_bbs_.push_back(p);
		last = p;
	}
	getFromStatment(block->block);
	RecoverSymBol();
	BaseBlock* next;
	if (last->insrList.size() == 0)
	{
		next = last;
	}
	else
	{
		next = new BaseBlock();
		last->succ_bbs_.push_back(next);
		next->pre_bbs_.push_back(last);
	}
	
	last = next;
}



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
	if (isExpStmt(p))
		return 9;
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
			Instruction* retInstr = ReturnInst::createRet(instr, nullptr);
			last->addInst(retInstr);
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
				if (dec->is_array==false)  //int
				{
					Instruction* instr = AllocaInst::createAlloca(new Type(intType));
					Value* newVal = new Value(intType);
					string name = dec->identifier.name;
					parent->addAddress(newVal, parent->address);
					parent->address += 1;
					last->addInst(instr);
					addSymbol(name, newVal);
					parent->addName(newVal, name);
					Value* v;
					if (dec->init)
					{
						NExp* p = dec->initvalue;
						v = getInstFromExp(p);
					}
					else
					{
						v = new ConstantInt(0);
					}
					int address = this->parent->getAddress(newVal);
					instr = StoreInst::createStore(v, address);		
					last->addInst(instr);
				}

				else //array
				{
					Type* p = new ArrayType(dec->size);
					Instruction* instr = AllocaInst::createAlloca(p, dec->size);
					Value* newVal = new Value(p);
					string name = dec->identifier.name;
					parent->addAddress(newVal, parent->address);
					parent->address += dec->size;
					last->addInst(instr);
					addSymbol(name, newVal);
					parent->addName(newVal, name);
					if (dec->init)
					{
						newVal->isConstant = true;
						for (int i = 0; i < dec->size; i++)
						{
							int val = (*dec->finalInitValue)[i];
							ConstantInt* constInt = new ConstantInt(val);
							int address = this->parent->getAddress(newVal);
							Instruction* instr = StoreInst::createStore(constInt, address+i);
						}
					}
				}
			}
			break;
		}

		case 4:
		{
			getFromWhile(dynamic_cast<NWhileStmt*>(stmt));
			last = whileOut.top();
			whileIn.pop();
			whileOut.pop();
			break;
		}
		case 5:
		{	
			getFromBlock(dynamic_cast<NBlockStmt*>(stmt));
			break;
		}
		case 6:
			//跳出while，跳到WhileOut的栈顶地址
		{
			last->succ_bbs_.push_back(whileOut.top());
			Instruction* p = BranchInst::createBr(whileOut.top(), last);
			last->addInst(p);
			goto breakcontinue; //berak后续的指令不可能执行了，可以不读取直接结束
			break;
		}
		case 7:
		{
			NAssignStmt* assign = dynamic_cast<NAssignStmt*>(stmt);
			string name = assign->name.name;
			Value* var = findValue(name);
			int address = parent->getAddress(var);
			if (var->isInt())
			{
				Instruction* rhs = getInstFromExp(&assign->rhs);
				Instruction* store = StoreInst::createStore(rhs, address);
				last->addInst(store);
			}
			
			else //数组及指针
			{
				IntList dim = (*assign->GetDimensions());
				vector<int>mult;//记录数组各维度的乘积，方便将高维访问转化为低维访问
				int init = 1;
				mult.push_back(init);
				Instruction* rhs = getInstFromExp(&assign->rhs);
				last->addInst(rhs);
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
				last->addInst(store);
			}
			break;
			
		}
		case 8:			
		{
			last->succ_bbs_.push_back(whileOut.top());
			Instruction* p = BranchInst::createBr(whileOut.top(), last);
			last->addInst(p);
			goto breakcontinue; //berak后续的指令不可能执行了，可以不读取直接结束
			break;		
		}

		case 9:
		{
			Instruction* p = getInstFromExp(&((NExpStmt*)stmt)->expression);
			last->addInst(p);
		}

		default:	break;
		}
	}
	breakcontinue :return;
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
			Value* val = new Value(type);
			p->addSymbol(paraName[i], val);
			Module::addName(val, paraName[i]);
		}
		else
		{
			Type* type = new ArrayType(((ArrayType*)para)->num);
			Value* val = new Value(type);
			p->addSymbol(paraName[i], val);
			Module::addName(val, paraName[i]);
		}
	}
	return p;
}

void Function::RecoverSymBol()
{
	vector<string> earse;
	for (auto i : recoverTable)
	{
		auto iter= symbolTable.find(i.first);
		if (iter != symbolTable.end())
		{
			string name = iter->first;
			Value* val = iter->second;
			symbolTable.erase(iter);
			symbolTable.insert(make_pair(name, val));
			earse.push_back(name);
		}
	}
	for (auto i : earse)
	{
		recoverTable.erase(recoverTable.find(i));
	}

}


void Function::addSymbol(string name, Value* val)
{
	auto iter = symbolTable.find(name);
	if (iter != symbolTable.end())
	{
		recoverTable.insert(make_pair(iter->first,iter->second));
		symbolTable.erase(iter);
		symbolTable.insert(make_pair(name, val));
	}
	else
	{
		symbolTable.insert(make_pair(name, val));
	}
}

Value* Function::findValue(string name)
{
	auto iter = symbolTable.find(name);
	if (iter != symbolTable.end())
	{
		return iter->second;
	}
	else
	{
		auto global = parent->getGlobalValue(name);
		if (global != nullptr)
			return global;
		else return nullptr;
	}
}



void Function::debugPrint()
{
	vector<BaseBlock*> memberList;
	cout << "Function: " << name;
	BaseBlock* p = entry;
	cout << " entry = " << p->blockType;
	cout << " succ_bbs_= " << p->succ_bbs_.size() << " " << endl;
	bool loop = true;
	while (p->succ_bbs_.size() != 0 && p->succ_bbs_[0] != nullptr && loop)
	{
		for (auto pp : memberList)
		{
			if (pp == p)
			{
				loop = false;
				cout << "LOOP detected! Exit The LOOP!!!" << endl;
			}
		}
		memberList.push_back(p);
		p->debugPrint();
		p = p->succ_bbs_[0];
	}
	memberList.push_back(p);
	p->debugPrint();
	cout << endl;
}