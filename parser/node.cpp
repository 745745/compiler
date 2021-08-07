#include "node.h"
#include "parser.hpp"
// node.h ��ǰ�� parser.hpp �ں� ��

int NBinaryExp::GetValue()
{
    switch (op)
    {
    case ADD:
        return lhs.GetValue() + rhs.GetValue();
        break;
    case SUB:
        return lhs.GetValue() - rhs.GetValue();
        break;
    case MUL:
        return lhs.GetValue() * rhs.GetValue();
        break;
    case DIV:
        return lhs.GetValue() / rhs.GetValue();
        break;
    case MOD:
        return lhs.GetValue() % rhs.GetValue();
        break;

    default:
        return 0;
        break;
    }
}

int NUnaryExp::GetValue()
{
    switch (op)
    {
    case ADD:
        return rhs.GetValue();
        break;
    case SUB:
        return 0 - rhs.GetValue();

    default:
        return 0;
        break;
    }
}

void SymbolTable::AddSymbol(NIdentifier& ident, int scope, NExpList lengths, NExp* initvalue, bool isconst, NVarDecl* parent)
{
    Symbol* newsymbol = new Symbol(ident, scope, lengths, initvalue, isconst, parent);
    Index newindex;
    newindex.scope = scope;
    newindex.name = ident.name;
    valueTable[newindex] = newsymbol;
}

int SymbolTable::GetSymbolValue(NIdentifier& ident, NExpList& array_def, int scope, Node* parent)
{
    // �ӷ��ű��в���һ�����ŵ�ֵ
    auto result = this->valueTable.find({ scope, ident.name });

    if (result != valueTable.end())
    {
        return (result->second->GetValue(array_def));
    }
    else if (scope != 0)
    {
        // ����Ǿֲ��������ں�����δ���ض���
        auto result = this->valueTable.find({ 0, ident.name });
        if (result != valueTable.end())
        {
            return (result->second->GetValue(array_def));
        }
        else
        {
            cout << endl
                << "undefind partial identifier" << endl;
            exit(-1);
        }
    }
    else
    {
        cout << endl
            << "undefind global identifier" << endl;
        exit(-1);
    }
}

Symbol* SymbolTable::GetSymbol(NIdentifier& ident, int scope)
{
    // �ӷ��ű��в���һ�����ŵ�ֵ
    auto result = this->valueTable.find({ scope, ident.name });

    if (result != valueTable.end())
    {
        return (result->second);
    }
    else if (scope != 0)
    {
        // ����Ǿֲ��������ں�����δ���ض���
        auto result = this->valueTable.find({ 0, ident.name });
        if (result != valueTable.end())
        {
            return (result->second);
        }
        else
        {
            cout << endl
                << "undefind partial identifier" << endl;
            exit(-1);
        }
    }
    else
    {
        cout << endl
            << "undefind global identifier" << endl;
        exit(-1);
    }
}

int Symbol::GetValue(NExpList array_def)
{
    if (array_def.size() != 0)
    {
        // array
        int index = 0;
        int i = 0;
        int nowsize = this->parent->size;
        // ����һ������a[4][2][3], ��������a[2][1][1]�ϵ�����ʱ��2 * size / 4 + 1 * size / 4 / 2 + 1 * size / 4 / 2 / 3
        for (auto dimension : array_def)
        {
            auto iterator = this->parent->dimensionLength->begin();
            nowsize = nowsize / *(iterator + i);
            index += dimension->GetValue() * nowsize;
            i++;
        }
        auto iterator = this->parent->finalInitValue->begin();
        return *(iterator + index);
    }
    else
    {
        return value->GetValue();
    }
}

void SymbolTable::SetValue(NIdentifier& name, NExpList& lengths, NExp& rhs, int scope)
{
    auto result = valueTable.find({ scope, name.name });
    if (result != valueTable.end())
    {
        result->second->value = &rhs;
    }
    else if (scope != 0)
    {
        // �ֲ����� ������ȥȫ�ֱ����в���
        auto result = valueTable.find({ 0, name.name });
        if (result != valueTable.end())
        {
            result->second->value = &rhs;
        }
        else
        {
            cout << "undefind" << endl;

            exit(-1);
        }
    }
    else
    {
        cout << "undefind" << endl;
        exit(-1);
    }
}

int SymbolTable::AddFunction(string functionName)
{
    int index = this->functionTable.size();
    functionTable[index] = functionName;
    return index;
}