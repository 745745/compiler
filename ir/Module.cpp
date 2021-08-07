#include"Module.h"
#include"../parser/node.h"
#include <vector>

using std::vector;
map<Value*, string> Module::nameTable;

void Module::ASTTranslate(NCompUnit* cu)
{
	vector<NDecl*> decl=cu->declarations;
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
			vector<std::string> paraName;
			NVarDeclList para = p->parameters;
			for (auto decl : para)
			{
				paraName.push_back(decl->identifier.name);
				if (!decl->is_array)
				{
					Type* paraType = new IntType();
					arg.push_back(paraType);
				}
				else
				{
					int arrStride = 1;
					for (auto i : decl->lengths)
						arrStride *= i->GetValue();
					Type* paraType = new ArrayType(arrStride);
					arg.push_back(paraType);
				}
			}
			Function* func = Function::makeFunction(t, arg, paraName);
			func->setName(name);
			func->setParent(this);
			
			NStmtList stmt = p->statements;
			func->getFromStatment(stmt);

			addFunction(func);
		}

		else //var decl
		{
			int len = p->lengths.size();
			string name = p->identifier.name;
			if (len == 0) //int
			{
				Value* val = new Value(intType);
				
				//addAddress(val, address);
				//address += 1;
				addGlobalVar(name,val);
				addName(val, name);

				if (p->init == true) //if init,add value to map
				{
					int intVal = p->initvalue->GetValue();
					ConstantInt* constInt = new ConstantInt(intVal);
					addConstantValue(val, constInt);
					nameTable[constInt] = name;
					val->isConstant = true;
				}
			}
			else //int array
			{
				// BugFix by Zlek
				Type* type = new ArrayType(p->lengths[0]->GetValue());
				Value* val = new Value(type);

				//addAddress(val, address);
				//address += ((p->lengths[0])->GetValue());
				addGlobalVar(name,val);
				addName(val, name);

				if (p->init == true)
				{
					vector<int> arrayValue;
					for (int i = 0; i < p->finalInitValue->size(); i++)
					{
						int intVal = (*(p->finalInitValue))[i];
						arrayValue.push_back(intVal);
					}
					ConstantArray* array = new ConstantArray(arrayValue);
					addConstantValue(val, array);
					nameTable[array] = name;
					val->isConstant = true;
				}
			}
		}
	}
}

void Module::addName(Value* val,string name)
{
	nameTable.insert(make_pair(val, name));
}

string Module::getName(Value* val)
{
	auto iter = nameTable.find(val);
	if (iter != nameTable.end())
	{
		return iter->second;
	}
	return string();
}

void Module::debugPrint()
{
	std::cout << "@ Global Values\n";
	for (auto [name, val] : globalVar)
	{
		std::cout << "\t[" << name;
		if (val->isArray())
		{
			std::cout << " Arr";
			auto v = dynamic_cast<ConstantArray*>(getConstantValue(val));
			std::cout << "[" << reinterpret_cast<ArrayType *>(val->type)->num << "]";
			if (v != nullptr)
			{
				std::cout << " = {";
				for (auto i : v->value)
					std::cout << " " << i;
				std::cout << " }";
			}
		}
		else
		{
			std::cout << " Int";
			auto v = dynamic_cast<ConstantInt*>(getConstantValue(val));
			if (v != nullptr)
				std::cout << " = " << v->value;
		}
		std::cout << "]\n";
	}

	std::cout << "\n@ Functions\n";
	for (auto i : funcList)
	{
		i->debugPrint();
	}
};


Function* Module::getFunction(string funcName)
{
	for (auto i : funcList)
	{
		if (i->name == funcName)
			return i;
	}
	return nullptr;
}