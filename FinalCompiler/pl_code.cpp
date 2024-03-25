// �м�������ɵ�һЩ����ʵ��
#include "pl_code.h"
#include "pl_parse.h"

// �����ֽ���
void Code::Emit(unsigned char opcode, unsigned char level, int opnum)
{
    Bytecode newCode(opcode, level, opnum);
    execCode.push_back(newCode);
}

// ���������
void Code::AddScope()
{
    std::vector<Symbol> newScope;
    symbolTable.push_front(newScope);
}

// ɾ��������
void Code::DelScope()
{
    symbolTable.pop_front();
}

// ����·���
void Code::AddNewSymbol(int type, int constNumber, std::string symbolName)
{
    int size = symbolTable.front().size();
    for (int i = 0; i < size; ++i)
    {
        if (symbolTable.front()[i].name == symbolName)
        {
            parser->Die("�����ض���: " + symbolName);
            return;
        }
    }
    Symbol newSymbol(type, constNumber, symbolName);
    symbolTable.front().push_back(newSymbol);
}

// ���ù��̲�����С
void Code::SetProcedureArgSize(std::string symbolName, int argSize)
{
    for (std::list<std::vector<Symbol>>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
    {
        int size = i->size();
        for (int j = 0; j < size; ++j)
        {
            if ((*i)[j].name == symbolName)
            {
                (*i)[j].procedureArgSize = argSize;
                return;
            }
        }
    }
}

// ��ȡ����λ��
int Code::GetSymbolPlace(std::string symbolName)
{
    int level = 0;
    for (std::list<std::vector<Symbol>>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
    {
        int size = i->size();
        int cnt = 0;
        for (int j = 0; j < size; ++j)
        {
            if ((*i)[j].type == SYM_VAR)
            {
                ++cnt;
            }
            if ((*i)[j].name == symbolName)
            {
                return ((level << 16) + cnt - 1);
            }
        }
        ++level;
    }
    parser->Die("δ����ķ���: " + symbolName);
    return -1;
}

// ��ȡ������С
int Code::GetArgSize(std::string symbolName)
{
    for (std::list<std::vector<Symbol>>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
    {
        int size = i->size();
        for (int j = 0; j < size; ++j)
        {
            if ((*i)[j].name == symbolName)
            {
                return (*i)[j].procedureArgSize;
            }
        }
    }
    return 0;
}

// ��ȡ����
Symbol Code::GetSymbol(std::string symbolName)
{
    for (std::list<std::vector<Symbol>>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
    {
        int size = i->size();
        for (int j = 0; j < size; ++j)
        {
            if ((*i)[j].name == symbolName)
            {
                return (*i)[j];
            }
        }
    }
    parser->Die("δ����ķ���: " + symbolName);
    Symbol errorSym(-1);
    return errorSym;
}

// ���ַ���ת��Ϊ����
int Code::ToNumber(std::string num)
{
    int sum = 0;
    for (int i = 0; i < num.length(); ++i)
    {
        sum = sum * 10 + (num[i] - '0');
    }
    return sum;
}
