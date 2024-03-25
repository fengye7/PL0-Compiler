// 中间代码生成的一些函数实现
#include "pl_code.h"
#include "pl_parse.h"

// 发出字节码
void Code::Emit(unsigned char opcode, unsigned char level, int opnum)
{
    Bytecode newCode(opcode, level, opnum);
    execCode.push_back(newCode);
}

// 添加作用域
void Code::AddScope()
{
    std::vector<Symbol> newScope;
    symbolTable.push_front(newScope);
}

// 删除作用域
void Code::DelScope()
{
    symbolTable.pop_front();
}

// 添加新符号
void Code::AddNewSymbol(int type, int constNumber, std::string symbolName)
{
    int size = symbolTable.front().size();
    for (int i = 0; i < size; ++i)
    {
        if (symbolTable.front()[i].name == symbolName)
        {
            parser->Die("符号重定义: " + symbolName);
            return;
        }
    }
    Symbol newSymbol(type, constNumber, symbolName);
    symbolTable.front().push_back(newSymbol);
}

// 设置过程参数大小
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

// 获取符号位置
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
    parser->Die("未定义的符号: " + symbolName);
    return -1;
}

// 获取参数大小
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

// 获取符号
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
    parser->Die("未定义的符号: " + symbolName);
    Symbol errorSym(-1);
    return errorSym;
}

// 将字符串转换为数字
int Code::ToNumber(std::string num)
{
    int sum = 0;
    for (int i = 0; i < num.length(); ++i)
    {
        sum = sum * 10 + (num[i] - '0');
    }
    return sum;
}
