// 抽象语法树的建立
#pragma once

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

// 定义抽象语法树的节点类型
typedef enum
{
    AST_ROOT,
    AST_PROG,
    AST_BLOCK,
    AST_CONDECL,
    AST_VARDECL,
    AST_PROC,
    AST_ID,
    AST_NUM,
    AST_PARAMETER,
    AST_BODY,
    AST_ASSIGN,
    AST_CONDITION,
    AST_IF,
    AST_ELSE,
    AST_WHILE,
    AST_CALL,
    AST_ARGUMENT,
    AST_READ,
    AST_WRITE,
    AST_ODD,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_EQU,
    AST_NEQU,
    AST_LAR,
    AST_LARE,
    AST_LES,
    AST_LESE,
} AST_TYPE;

// 抽象树内容表
struct
{
    int type;
    const char *ast_content;
} ast_table[] = {
    {AST_ROOT, "root"},
    {AST_PROG, "program"},
    {AST_PROC, "procedure"},
    {AST_BLOCK, "block"},
    {AST_CONDECL, "const_declare"},
    {AST_VARDECL, "var_declare"},
    {AST_ID, "identifier"},
    {AST_NUM, "number"},
    {AST_PARAMETER, "parameter"},
    {AST_BODY, "body"},
    {AST_ASSIGN, "assignment"},
    {AST_CONDITION, "conditional"},
    {AST_IF, "if"},
    {AST_ELSE, "else"},
    {AST_WHILE, "while"},
    {AST_CALL, "call"},
    {AST_ARGUMENT, "argument"},
    {AST_READ, "read"},
    {AST_WRITE, "write"},
    {AST_ODD, "odd"},
    {AST_ADD, "+"},
    {AST_SUB, "-"},
    {AST_MUL, "*"},
    {AST_DIV, "/"},
    {AST_EQU, "="},
    {AST_NEQU, "<>"},
    {AST_LAR, ">"},
    {AST_LARE, ">="},
    {AST_LES, "<"},
    {AST_LESE, "<="},
};

class AST
{
private:
    int line;
    int type;
    std::string content;
    std::vector<AST> child;

public:
    AST(int = 0, int = AST_ROOT, std::string = "");
    AST(const AST &);
    ~AST();
    // 创建树
    void AddChild(AST);
    void SetLine(int);
    void SetType(int);
    void SetStr(std::string &);

    // 获取树信息
    std::vector<AST> &GetChild();
    int GetLine();
    int GetType();
    std::string GetStr();

    // 打印输出树
    void Print(int);

    AST &operator=(const AST &);
};