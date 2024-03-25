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
// 使用词法分析子程序的递归下降子程序的语法制导翻译
#pragma once
#include <iostream>
#include <fstream>
#include "pl_lex.h"
#include "pl_ast.h"
#include "pl_code.h"

class Parser
{
public:
    std::ifstream infile;           // 输入的文件
    std::string current_lcode = ""; // 当前读到的行
    int current_line = 1;           // 当前行号
    char c;                         // 读到的字符
    bool is_error = false;          // 是否编译错误

    Token token; // 定义的全局的临时token对象

    LexicalAnalysis lexer;
    Code coder;

    Parser(std::string _filename)
    {
        lexer.SetFile(_filename);
        lexer.SetParentParser(this);

        coder.SetParentParser(this);
    }

    void Die(std::string error_info, int l = -1); // 打印错误信息

    // 总分析函数
    AST Analyse();

    // 检查匹配函数
    void Match(int);
    void Hunger();

    // 下面是递归下降程序列表
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