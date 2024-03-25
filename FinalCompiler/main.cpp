/*
 * @Author: fengye7 zcj2518529668@163.com
 * @Date: 2023-12-16 20:37:55
 * @LastEditors: fengye7 zcj2518529668@163.com
 * @LastEditTime: 2023-12-18 18:37:35
 * @FilePath: \PL-0_compiler\FinalCompiler\main.cpp
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
// �����г���
#include "pl.h"

// �Զ�����м����Ĳ�����
const char *OpcodeName[] = {"nop", "lit", "opr", "lod", "sto", "cal", "int", "jmp", "jpc", "red", "wrt", NULL};

void help()
{
    std::cout << "usage:\n";
    std::cout << "  pl0 -file [filename].\n";
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        help();
        return 0;
    }

    if (argc != 3)
    {
        std::cout << "û��������ļ�.\n";
        help();
        exit(-1);
    }

    Parser parser = Parser(argv[2]);
    parser.lexer.ReadFile();
    AST result = parser.Analyse();
    parser.lexer.CloseFile();

    if (!parser.is_error)
    {
        result.Print(0);
        for (int i = 0; i < parser.coder.execCode.size(); ++i)
            printf("0x%.8x %s 0x%.8x 0x%.8x\n", i, OpcodeName[parser.coder.execCode[i].opcode], parser.coder.execCode[i].level, parser.coder.execCode[i].opnum);
    }
}