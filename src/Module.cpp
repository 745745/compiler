#include"../include/Module.h"
#include"../include/node.h"
#include<vector>

using std::vector;
int address = 0;

void Module::ASTTranslate(NCompUnit* cu)
{
	vector<NDecl*> decl;
	for (int i = 0; i < decl.size(); i++)
	{
		NVarDecl* p = dynamic_cast<NVarDecl*>(decl[i]);
		if (p == NULL)//Func decl
		{
			NFuncDecl* p = dynamic_cast<NFuncDecl*>(decl[i]);
			string name = p->function_name.name;
			string type = p->type;
			Type* t = new Type();
			if (type == "int")
			{
				t->tName = intType;
			}
			else
			{
				t->tName = voidType;
			}

			vector<Type*>arg;
			NVarDeclList para = p->parameters;
			for (int i = 0; para.size(); i++)
			{
				//这部分用于添加函数的参数，前端还没有最终版，先留着

			}

			Function* func = Function::makeFunction(t, arg);
			func->setName(name);
			func->setParent(this);
			NStmtList stmt = p->statements;
			BaseBlock* block = getFromStatment(stmt);
			func->addBasicBlock(block);
			addFunction(func);
		}

		else //var decl
		{
			int len = p->lengths.size();
			if (len == 1) //int
			{
				Type* type = new Type();
				type->tName == intType;
				Value* val = new Value(type);

				addSymbol(p->identifier.name, nullptr, val);
				addGlobalVar(val);
				if (p->init == true) //if init,add value to map
				{
					int intVal = (*(p->finalInitValue))[0];
					ConstantInt* constInt = new ConstantInt(intVal);
					addConstantValue(val, constInt);
				}
			}

			else //int array
			{
				Type* type = new ArrayType(p->lengths.size());
				Value* val = new Value(type);

				addSymbol(p->identifier.name, nullptr, val);
				addGlobalVar(val);

				if (p->init == true)
				{
					vector<int> arrayValue;
					for (int i = 0; i < len; i++)
					{
						int intVal = (*(p->finalInitValue))[i];
						arrayValue.push_back(intVal);
					}
					ConstantArray* array = new ConstantArray(arrayValue);
					addConstantValue(val, array);
				}
			}
		}
	}
}




BaseBlock* Module::getFromStatment(NStmtList stmtList)
{

	BaseBlock* now = new BaseBlock();
	now->parent = nullptr;
	BaseBlock* entry = now;
	BaseBlock* tail = now;
	NStmt* stmt;
	for (int i = 0; i < stmtList.size(); i++)
	{
		stmt = dynamic_cast<NStmt*>(stmtList[i]);
		switch (judgeStmt(stmt))
		{
		case 1:
			NReturnStmt * ret = dynamic_cast<NReturnStmt*>(stmt);
			Instruction* instr = getInstFromExp(ret->return_value);
			now->insrList.push_back(instr);
			now = new BaseBlock();
			tail->succ_bbs_.push_back(now);
			now->pre_bbs_.push_back(tail);
			tail = now;
			break;

		case 2:
			BaseBlock * p = getFromIf(dynamic_cast<NIfStmt*>(stmt));
			now->succ_bbs_.push_back(p);
			now = p;
			tail = p;
			break;

		case 3:
		{
			NDeclList declList = dynamic_cast<NDeclStmt*>(stmt)->declarations;
			for (auto decl : declList)
			{
				auto dec = dynamic_cast<NVarDecl*>(decl);
				if (dec->size == 0)
				{
					Type* p = new IntType();
					Instruction* instr = AllocaInst::createAlloca(p);
					Value* newVal = new Value(p);
					string name = dec->identifier.name;
					addAddress(newVal, address);
					address += 4;
					now->addInst(instr);
					if (dec->init)
					{
						int val = (*dec->finalInitValue)[0];
						ConstantInt* constInt = new ConstantInt(val);

						auto iter = this->addressTable.find(newVal);
						int address = iter->second;
						Instruction* instr = StoreInst::createStore(constInt, address - 4);
					}
				}

				else //array
				{
					Type* p = new IntType();
					Instruction* instr = AllocaInst::createAlloca(p, dec->size);
					Value* newVal = new Value(p);
					string name = dec->identifier.name;
					addAddress(newVal, address);
					address += 4 * dec->size;
					now->addInst(instr);
					if (dec->init)
					{
						for (int i = 0; i < dec->size; i++)
						{
							int val = (*dec->finalInitValue)[i];
							ConstantInt* constInt = new ConstantInt(val);
							auto iter = this->addressTable.find(newVal);
							int address = iter->second;
							Instruction* instr = StoreInst::createStore(constInt, address - 4 * (dec->size - i));
						}
					}
				}
			}
		}

		case 4:
			BaseBlock * p = getFromWhile(dynamic_cast<NWhileStmt*>(stmt));
			now->succ_bbs_.push_back(p);
			now = p;
			tail = p;
			break;
		case 5:
			BaseBlock * p = getFromBlock(dynamic_cast<NBlockStmt*>(stmt));
			now->succ_bbs_.push_back(p);
			now = p;
			tail = p;
			break;

		case 6:
			//break 只会在while里面出现，在这里可以不管
			break;

		case 7:
		{
			NAssignStmt* assign = dynamic_cast<NAssignStmt*>(stmt);
			string name = assign->name.name;
			Value* var = findValue(name, now);
			int address = getAddress(var);
			int offset = ((NInteger*)(assign->lengths[0]))->value;
			if (var->isArray())
			{							
				if (p==nullptr) //如果就是常数值，不需要计算
				{					
					NInteger* integer = dynamic_cast<NInteger*>(&(assign->rhs));
					ConstantInt* constInt = new ConstantInt(integer->value);					
					Instruction* instr = StoreInst::createStore(constInt, address,offset);
				}
				else
				{


				}
			}

			if (var->isInt())
			{
			}

		}
		case 8:
		default:	break;
		}


	}

	return entry;
}


BaseBlock* getFromBlock(NBlockStmt* block)
{



}



BaseBlock* getFromIf(NIfStmt* ifstmt)
{}

BaseBlock* getFromWhile(NWhileStmt* whileStmt)
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

Instruction* getInstFromExp(NExp* p)
{


}

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
