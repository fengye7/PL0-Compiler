/*
 * @Author: fengye7 zcj2518529668@163.com
 * @Date: 2023-12-16 20:34:28
 * @LastEditors: fengye7 zcj2518529668@163.com
 * @LastEditTime: 2023-12-18 18:25:44
 * @FilePath: \PL-0_compiler\FinalCompiler\pl_parse.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
// ʹ�ôʷ������ӳ���ĵݹ��½��ӳ�����﷨�Ƶ�����
#pragma once
#include <iostream>
#include <fstream>
#include "pl_lex.h"
#include "pl_ast.h"
#include "pl_code.h"

class Parser
{
public:
    std::ifstream infile;           // ������ļ�
    std::string current_lcode = ""; // ��ǰ��������
    int current_line = 1;           // ��ǰ�к�
    char c;                         // �������ַ�
    bool is_error = false;          // �Ƿ�������

    Token token; // �����ȫ�ֵ���ʱtoken����

    LexicalAnalysis lexer;
    Code coder;

    Parser(std::string _filename)
    {
        lexer.SetFile(_filename);
        lexer.SetParentParser(this);

        coder.SetParentParser(this);
    }

    void Die(std::string error_info, int l = -1); // ��ӡ������Ϣ

    // �ܷ�������
    AST Analyse();

    // ���ƥ�亯��
    void Match(int);
    void Hunger();

    // �����ǵݹ��½������б�
    AST Prog();
    AST Block(int);
    AST ConDecl();
    AST Const();
    AST VarDecl();
    void Proc(AST &);
    AST Body();
    AST Statement();
    AST Lexp();
    AST Exp();
    AST Term();
    AST Factor();
    AST Lop();
};