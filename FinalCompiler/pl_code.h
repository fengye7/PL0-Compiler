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
// ���ű��ֽ�����м��������

#pragma once

#include <cstring>
#include <sstream>
#include <list>
#include <vector>

// ����������ö��
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

// ����������ö��
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

// ��������ö��
enum SymbolType
{
    SYM_VAR = 1,
    SYM_CONST,
    SYM_PROC
};

// ���Žṹ��
struct Symbol
{
    std::string name;
    int type;
    int number;
    int procedureArgSize;

    // ���캯��
    Symbol(int t = SYM_VAR, int num = 0, std::string n = "", int arg = 0)
    {
        type = t;
        number = num;
        name = n;
        procedureArgSize = arg;
    }

    // �������캯��
    Symbol(const Symbol &tmp)
    {
        name = tmp.name;
        number = tmp.number;
        type = tmp.type;
        procedureArgSize = tmp.procedureArgSize;
    }
};

// �ֽ���ṹ��
struct Bytecode
{
    unsigned char opcode;
    unsigned char level;
    int opnum;

    // ���캯��
    Bytecode(unsigned char oc, unsigned char lvl, int num)
    {
        opcode = oc;
        level = lvl;
        opnum = num;
    }

    // �������캯��
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

    // ���ø�����parser
    void SetParentParser(Parser *_parser)
    {
        parser = _parser;
    }

    // �����ֽ���
    void Emit(unsigned char opcode = OP_NOP, unsigned char level = 0, int opnum = 0);

    // ���������
    void AddScope();

    // ����·���
    void AddNewSymbol(int type = SYM_VAR, int constNumber = 0, std::string symbolName = "");

    // ���ù��̲�����С
    void SetProcedureArgSize(std::string symbolName, int argSize);

    // ��ȡ����λ��
    int GetSymbolPlace(std::string symbolName);

    // ��ȡ������С
    int GetArgSize(std::string symbolName);

    // ��ȡ����
    Symbol GetSymbol(std::string symbolName);

    // ���ַ���ת��Ϊ����
    int ToNumber(std::string num);

    // ɾ��������
    void DelScope();
};
