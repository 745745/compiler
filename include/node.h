#include <iostream>
#include <vector>
#include <string>
#include <map>

class Node;
class NDecl;
class NExp;
class NStmt;
class NIdentifier;
class NVarDecl;
class Symbol;
class SymbolTable;

using namespace std;

typedef vector<NDecl*> NDeclList;
typedef vector<NStmt*> NStmtList;
typedef vector<NVarDecl*> NVarDeclList;
typedef vector<NExp*> NExpList;

typedef vector<int> IntList;

struct Index
{
	int scope;
	string name;
	bool operator<(const Index& x) const
	{
		if (scope < x.scope)
		{
			return true;
		}
		else if (name < x.name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class Symbol
{
public:
	NIdentifier& ident;
	int scope;
	NExpList lengths;
	NExp* value;
	bool isconst;
	NVarDecl* parent;

public:
	Symbol(NIdentifier& ident, int scope, NExpList lengths, NExp* initvalue, bool isconst, NVarDecl* parent) : ident(ident), scope(scope), lengths(lengths), value(initvalue), isconst(isconst), parent(parent) {}
	void Print();
	int GetValue(NExpList array_def);
};

class SymbolTable
{
public:
	map<Index, Symbol*> valueTable;
	map<int, string> functionTable;

public:
	SymbolTable()
	{
		functionTable[0] = "Global"; // ��ʼ�����ű�ʱ�Զ���ʼ����һ��ȫ�ֵĻ���
	}

	void AddSymbol(NIdentifier& ident, int scope, NExpList lengths, NExp* initvalue, bool isconst, NVarDecl* parent);

	int AddFunction(string functionName);

	void visit()
	{
		cout << "this is the symbol table:" << endl;
		for (auto Symbol : valueTable)
		{
			Symbol.second->Print();
		}
	}
	int GetSymbolValue(NIdentifier& ident, NExpList& array_def, int scope, Node* parent);
	void SetValue(NIdentifier& name, NExpList& lengths, NExp& rhs, int scope);
	Symbol* GetSymbol(NIdentifier& ident, int scope);
};

class Node
{
public:
	static SymbolTable symboltb;
	Node* parent;
	int scope = 0;

public:
	virtual void Print() {}
	virtual ~Node() {}

	virtual void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
	}
	// ��ʱΪÿһ�����������ϵ�ָ���������

public:
	virtual void GenSymbolTable() {}
};

class NStmt : public Node
{
public:
	virtual void SetValue() {}
	// Ŀǰ��ʵ����AssignStmt
	virtual void ReFormatforArray() {}
};

class NDecl : public Node
{
public:
	virtual void ReFormatforArray() {}
};

class NExp : public Node
{
public:
	NExp() {}
	virtual int GetValue()
	{
		return 0;
	}

	virtual int ExpandInitList(IntList* initValue, int index, int length)
	{
		// ���麯�����ڶԳ�ʼ���б���мӹ�������б��е�Ԫ��Ϊ�б�ʱ�������ٵ��ô˺��������ǵ���NInitlistExp�е�expand����
		auto iterator = initValue->begin();
		*(iterator + index) = this->GetValue(); // �޸�indexλ�õ�ֵ
		return ++index;
	}
};

class NCompUnit : public Node
{
public:
	NDeclList declarations;

public:
	NCompUnit(NDeclList& declarations) : declarations(declarations)
	{
		this->scope = 0;
		for (auto NDecl : declarations)
		{
			NDecl->SetParentAndScope(this, this->scope); // Ϊÿһ��FuncDecl����VarDecl����parent��scope
			NDecl->GenSymbolTable();					 // ������ϵ���,ͬʱҪ���Ǹ�ֵ���
		}
		for (auto NDecl : declarations)
		{
			NDecl->ReFormatforArray();
		}
	}
	void Print();
};

class NIdentifier : public NExp
{
public:
	string name;

public:
	NIdentifier(const string& name) : name(name) {}
	void Print();
};

class NInteger : public NExp
{
public:
	int value;

public:
	NInteger(int value) : value(value) {}
	void Print();
	int GetValue()
	{
		return this->value;
	}
};

class NInitListExp : public NExp
{
public:
	NExpList NInitList;

public:
	NInitListExp() {}
	NInitListExp(NExpList& NInitList) : NInitList(NInitList) {}
	void Print();
	int ExpandInitList(IntList* initValue, int index, int length)
	{
		// NInitListExp��һ������Ľṹ��������Ҫ��������
		int beforeindex = index;
		int endindex = index;

		for (auto NInit : NInitList)
		{
			endindex = NInit->ExpandInitList(initValue, beforeindex, length);
			beforeindex = endindex;
		}
		if (endindex - index < length)
		{
			return index + length;
		}
		return endindex;
	}

	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		for (auto NExp : NInitList)
		{
			NExp->SetParentAndScope(this, scope);
		}
	}
};

class NVarDecl : public NDecl
{
public:
	bool isconst = false;
	string type = "int";
	bool init = true;
	NIdentifier& identifier;
	NExpList lengths;
	NExp* initvalue;
	IntList* finalInitValue;
	// �洢����ĳ�ʼ���б�
	IntList* dimensionLength;
	// �洢����ĸ�ά����Ϣ���������������size�������ĳ���
	int size;

public:
	NVarDecl(NIdentifier& identifier, NExpList& lengths, NExp* initvalue) : identifier(identifier), lengths(lengths), initvalue(initvalue)
	{
		init = true;
	}
	NVarDecl(NIdentifier& identifier, NExpList& lengths) : identifier(identifier), lengths(lengths)
	{
		init = false;
		initvalue = NULL;
	}

	NVarDecl(const string& type, NIdentifier& identifier) : type(type), identifier(identifier)
	{
		init = false;
	}
	NVarDecl(const string& type, NIdentifier& identifier, NExpList& lengths) : type(type), identifier(identifier), lengths(lengths)
	{
		init = false;
		initvalue = NULL;
	}

	void setTypeforConst()
	{
		isconst = true;
	}

	void Print();

	void GenSymbolTable()
	{
		this->symboltb.AddSymbol(identifier, this->scope, lengths, initvalue, isconst, this);

		for (auto NExp : lengths)
		{
			NExp->SetParentAndScope(this, this->scope);
		}
	}

	void ReFormatforArray()
	{
		if (lengths.size() != 0)
		{
			// ������ĸ���ά�Ƚ��е���
			this->dimensionLength = new IntList();
			this->size = 1;
			for (auto NExp : lengths)
			{
				this->size *= NExp->GetValue();
				dimensionLength->push_back(NExp->GetValue());
			}

			// ������ĳ�ʼ���б���е���;
			if (this->init)
			{
				this->finalInitValue = new IntList(this->size, 0);
				int index = 0;
				this->initvalue->ExpandInitList(finalInitValue, index, this->dimensionLength->back());
			}
		}
	}

	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		this->identifier.SetParentAndScope(this, scope);
		for (auto NExp : lengths)
		{
			NExp->SetParentAndScope(this, scope);
		}
		if (init)
		{
			initvalue->SetParentAndScope(this, scope);
		}
	}
};

class NFuncDecl : public NDecl
{
public:
	string type;
	NIdentifier& function_name;
	NVarDeclList parameters;
	NStmtList statements;

public:
	NFuncDecl(const string& type, NIdentifier& function_name, NVarDeclList& parameters, NStmtList& statements) : type(type), function_name(function_name), parameters(parameters), statements(statements)
	{
		// ������������ʱ�ͽ�������ά������ ��ͬ
		int index = this->symboltb.AddFunction(function_name.name);
		for (auto param : parameters)
		{
			param->SetParentAndScope(this, index);
			param->GenSymbolTable();
		}
		for (auto statement : statements)
		{
			statement->SetParentAndScope(this, index);
			statement->GenSymbolTable();
		}
	}
	NFuncDecl(const string& type, NIdentifier& function_name, NStmtList& statements) : type(type), function_name(function_name), statements(statements)
	{
		int index = this->symboltb.AddFunction(function_name.name);
		// no parameters
		for (auto statement : statements)
		{
			statement->SetParentAndScope(this, index);
			statement->GenSymbolTable();
		}
	}
	void Print();

	void GenSymbolTable()
	{
		// �����ڲ��ı����ں�������֮�������˴������������ڲ��ĸ�ֵ�����ܲ���ȫ�ֵı��������Ҫ��NCompUnit����ɴ���
		// for (auto stmt : statements)
		// {
		// 	stmt->SetValue();
		// }
	}

	void ReFormatforArray()
	{
		for (auto stmt : statements)
		{
			stmt->ReFormatforArray();
		}
	}
};

class NReturnStmt : public NStmt
{
public:
	NExp* return_value;

public:
	NReturnStmt(NExp* return_value) : return_value(return_value) {}
	NReturnStmt() { return_value = NULL; }
	void Print();
	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		if (return_value != NULL)
		{
			return_value->SetParentAndScope(this, scope);
		}
	}
};

class NDeclStmt : public NStmt
{
public:
	NDeclList declarations;

public:
	NDeclStmt(NDeclList declarations) : declarations(declarations)
	{
	}
	void GenSymbolTable()
	{
		for (auto NDecl : declarations)
		{
			NDecl->parent = this;
			NDecl->GenSymbolTable();
		}
	}
	void Print();
	void ReFormatforArray()
	{
		for (auto NDecl : declarations)
		{
			NDecl->ReFormatforArray();
		}
	}

	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;

		for (auto NDecl : declarations)
		{
			NDecl->SetParentAndScope(this, scope);
		}
	}
};

class NBlockStmt : public NStmt
{
public:
	NStmtList& block;

public:
	NBlockStmt(NStmtList& block) : block(block) {}
	void Print();
	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		for (auto stmt : block)
		{
			stmt->SetParentAndScope(this, scope);
		}
	}
};

class NAssignStmt : public NStmt
{
public:
	NIdentifier& name;
	NExpList lengths;
	NExp& rhs;

public:
	NAssignStmt(NIdentifier& name, NExpList& lengths, NExp& rhs) : name(name), lengths(lengths), rhs(rhs)
	{
	}
	void SetValue()
	{
		this->symboltb.SetValue(name, lengths, rhs, scope);
	}
	void Print();
	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		name.SetParentAndScope(this, scope);
		for (auto NExp : lengths)
		{
			NExp->SetParentAndScope(this, scope);
		}
		rhs.SetParentAndScope(this, scope);
	}

	IntList* GetDimensions()
	{
		IntList* dimensions = new IntList();
		if (lengths.size() != 0)
		{
			// array
			return this->symboltb.GetSymbol(this->name, this->scope)->parent->dimensionLength;
		}
		return dimensions;
	}
};

class NNullStmt : public NStmt
{
public:
	void Print();
};

class NExpStmt : public NStmt
{
public:
	NExp& expression;

public:
	NExpStmt(NExp& expression) : expression(expression) {}
	void Print();
};

class NIfStmt : public NStmt
{
public:
	NExp& condition;
	NStmt& true_statement;
	NStmt* false_statement;

public:
	NIfStmt(NExp& condition, NStmt& true_statement) : condition(condition), true_statement(true_statement) { false_statement = NULL; }
	NIfStmt(NExp& condition, NStmt& true_statement, NStmt* false_statement) : condition(condition), true_statement(true_statement), false_statement(false_statement) {}
	void Print();
};

class NWhileStmt : public NStmt
{
public:
	NExp& condition;
	NStmt& statement;

public:
	NWhileStmt(NExp& condition, NStmt& statement) : condition(condition), statement(statement) {}
	void Print();
};

class NBreakStmt : public NStmt
{
public:
	void Print();
};

class NContinueStmt : public NStmt
{
public:
	void Print();
};

class NBinaryExp : public NExp
{
public:
	NExp& lhs;
	int op;
	NExp& rhs;

public:
	NBinaryExp(NExp& lhs, int op, NExp& rhs) : lhs(lhs), op(op), rhs(rhs) {}
	void Print();
	int GetValue(); // ����parser.hpp�����ƣ�������ʵ��ֻ�ܷ��������ļ���
	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		lhs.SetParentAndScope(parent, scope);
		rhs.SetParentAndScope(parent, scope);
	}
};

class NUnaryExp : public NExp
{
public:
	int op;
	NExp& rhs;

public:
	NUnaryExp(int op, NExp& rhs) : op(op), rhs(rhs) {}
	void Print();
	int GetValue();
	void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
		rhs.SetParentAndScope(parent, scope);
	}
};

class NCallExp : public NExp
{
public:
	NIdentifier& function_name;
	NExpList parameters;

public:
	NCallExp(NIdentifier& function_name) : function_name(function_name) {}
	NCallExp(NIdentifier& function_name, NExpList parameters) : function_name(function_name), parameters(parameters) {}
	void Print();
};

class NIdentifierExp : public NExp
{
public:
	NIdentifier& name;
	NExpList& array_def;

public:
	NIdentifierExp(NIdentifier& name, NExpList& array_def) : name(name), array_def(array_def) {}
	void Print();

	int GetValue()
	{
		return this->symboltb.GetSymbolValue(name, array_def, this->scope, this->parent);
	}

	virtual void SetParentAndScope(Node* parent, int scope)
	{
		this->parent = parent;
		this->scope = scope;
	}
};
