/*
 * @Author: fengye7 zcj2518529668@163.com
 * @Date: 2023-12-16 23:05:26
 * @LastEditors: fengye7 zcj2518529668@163.com
 * @LastEditTime: 2023-12-16 23:11:07
 * @FilePath: \PL-0_compiler\FinalCompiler\pl_ast.cpp
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
// �����﷨����һЩ������ʵ��
#include "./pl_ast.h"

AST::AST(int default_line, int default_type, std::string default_content)
{
    line = default_line;
    type = default_type;
    content = default_content;
    return;
}

AST::AST(const AST &tmp)
{
    line = tmp.line;
    type = tmp.type;
    content = tmp.content;
    child = tmp.child;
    return;
}

AST::~AST()
{
    content = "";
    child.clear();
    return;
}

// ������ -------------------------
// ����ӽڵ�
void AST::AddChild(AST tmp)
{
    child.push_back(tmp);
    return;
}
// �����к�
void AST::SetLine(int l)
{
    line = l;
    return;
}
// ���ýڵ�����
void AST::SetType(int t)
{
    type = t;
    return;
}
void AST::SetStr(std::string &s)
{
    content = s;
    return;
}

// ��ȡ����Ϣ ---------------------------
// ��ȡ�ӽڵ�
std::vector<AST> &AST::GetChild()
{
    return child;
}
int AST::GetLine()
{
    return line;
}
int AST::GetType()
{
    return type;
}
std::string AST::GetStr()
{
    return content;
}

// ����� = ������
AST &AST::operator=(const AST &tmp)
{
    line = tmp.line;
    type = tmp.type;
    content = tmp.content;
    child = tmp.child;
    return *this;
}

// ��ӡ�����ų����﷨��
void AST::Print(int depth = 0)
{
    std::string s = "";
    for (int i = 0; i < depth; ++i)
        s += "|  ";
    std::cout << s << ast_table[type].ast_content;
    if (type == AST_ID || type == AST_NUM || type == AST_PROG || type == AST_PROC || type == AST_CALL || type == AST_ASSIGN)
        std::cout << ": " << content;
    std::cout << "\n";
    for (std::vector<AST>::iterator i = child.begin(); i != child.end(); ++i)
        i->Print(depth + 1);
    return;
}
