/*
 * @Author: fengye7 zcj2518529668@163.com
 * @Date: 2023-12-16 20:34:16
 * @LastEditors: fengye7 zcj2518529668@163.com
 * @LastEditTime: 2023-12-18 18:27:37
 * @FilePath: \PL-0_compiler\FinalCompiler\pl_code.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
// 符号表、字节码表、中间代码生成

#pragma once

#include <cstring>
#include <sstream>
#include <list>
#include <vector>

// 操作码类型枚举
enum OpcodeType
{
    OP_NOP,
    OP_LIT,
    OP_OPR,
    OP_LOD,
    OP_STO,
    OP_CAL,
    OP_INT,
    OP_JMP,
    OP_JPC,
    OP_RED,
    OP_WRT
};

// 操作数类型枚举
enum OperatorType
{
    CALC_RET,
    CALC_NEGA,
    CALC_PLUS,
    CALC_MINUS,
    CALC_MULT,
    CALC_DIV,
    CALC_ODD,
    CALC_EQ,
    CALC_NEQ,
    CALC_LES,
    CALC_LEQ,
    CALC_GRT,
    CALC_GEQ
};

// 符号类型枚举
enum SymbolType
{
    SYM_VAR = 1,
    SYM_CONST,
    SYM_PROC
};

// 符号结构体
struct Symbol
{
    std::string name;
    int type;
    int number;
    int procedureArgSize;

    // 构造函数
    Symbol(int t = SYM_VAR, int num = 0, std::string n = "", int arg = 0)
    {
        type = t;
        number = num;
        name = n;
        procedureArgSize = arg;
    }

    // 拷贝构造函数
    Symbol(const Symbol &tmp)
    {
        name = tmp.name;
        number = tmp.number;
        type = tmp.type;
        procedureArgSize = tmp.procedureArgSize;
    }
};

// 字节码结构体
struct Bytecode
{
    unsigned char opcode;
    unsigned char level;
    int opnum;

    // 构造函数
    Bytecode(unsigned char oc, unsigned char lvl, int num)
    {
        opcode = oc;
        level = lvl;
        opnum = num;
    }

    // 拷贝构造函数
    Bytecode(const Bytecode &tmp)
    {
        opcode = tmp.opcode;
        level = tmp.level;
        opnum = tmp.opnum;
    }
};

class Parser;

class Code
{
public:
    std::list<std::vector<Symbol>> symbolTable;
    std::vector<Bytecode> execCode;

    Parser *parser;

    // 设置父对象parser
    void SetParentParser(Parser *_parser)
    {
        parser = _parser;
    }

    // 发出字节码
    void Emit(unsigned char opcode = OP_NOP, unsigned char level = 0, int opnum = 0);

    // 添加作用域
    void AddScope();

    // 添加新符号
    void AddNewSymbol(int type = SYM_VAR, int constNumber = 0, std::string symbolName = "");

    // 设置过程参数大小
    void SetProcedureArgSize(std::string symbolName, int argSize);

    // 获取符号位置
    int GetSymbolPlace(std::string symbolName);

    // 获取参数大小
    int GetArgSize(std::string symbolName);

    // 获取符号
    Symbol GetSymbol(std::string symbolName);

    // 将字符串转换为数字
    int ToNumber(std::string num);

    // 删除作用域
    void DelScope();
};
