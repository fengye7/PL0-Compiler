// �ʷ�������һЩ������ʵ��
#include <iostream>
#include "./pl_lex.h"
#include "./pl_parse.h"

// �����ļ�Դ
void LexicalAnalysis::SetFile(std::string _filename)
{
    filename = _filename;
}

// ���ø�����parser
void LexicalAnalysis::SetParentParser(Parser *_parser)
{
    parser = _parser;
}

// ���ļ�
void LexicalAnalysis::ReadFile()
{
    parser->infile.open(filename, std::ios::binary);
    if (parser->infile.fail())
    {
        parser->infile.close();
        std::cout << ("cannot open file \"" + filename + "\".\n");
        exit(-1);
    }
    parser->c = parser->infile.get();
}

// �ر��ļ�
void LexicalAnalysis::CloseFile()
{
    parser->infile.close();
    return;
}

// ��ȡ��һ���ַ�
void LexicalAnalysis::GetNextChar()
{
    // �ļ���ĩβ
    if (parser->infile.eof())
    {
        parser->token.content = "";
        parser->token.tok_type = TOK_EOF;
        return;
    }
    // �����ַ�
    if (parser->c)
        parser->current_lcode += parser->c;
    if (parser->c != '\n' && parser->c != '\r' && parser->c != '\t' && parser->c != ' ' && !IS_ID(parser->c) && !IS_DIGIT(parser->c) && !IS_OPR(parser->c) && !IS_MOPR(parser->c))
        parser->Die("��" + parser->current_lcode + "������ʶ����ַ�");

    // �����쳣�Ϳհ��ַ�
    while (!parser->infile.eof() && !IS_ID(parser->c) && !IS_DIGIT(parser->c) && !IS_OPR(parser->c) && !IS_MOPR(parser->c))
    {
        parser->c = parser->infile.get(); // ���ϵض�ȡ�ַ���ֱ���ַ�Ϊ��Ч�ַ�
        if (parser->infile.eof())
        {
            parser->token.content = "";
            parser->token.tok_type = TOK_EOF;
            return;
        }
        parser->current_lcode += parser->c;
        if (IS_DIGIT(parser->c) || IS_ID(parser->c) || IS_OPR(parser->c) || IS_MOPR(parser->c))
            break;
        else if (parser->c == '\n')
        {
            ++parser->current_line;
            parser->current_lcode = "";
        }
        else if (parser->c != '\r' && parser->c != '\t' && parser->c != ' ')
            parser->Die("��" + parser->current_lcode + "������ʶ����ַ�");
    }
    // �������ַ�������
    if (IS_DIGIT(parser->c))
    {
        parser->token.content = parser->c;
        bool error_number = false;
        while (!parser->infile.eof())
        { // �����ֶ���
            parser->c = parser->infile.get();
            if (parser->infile.eof())
                break;
            if (IS_DIGIT(parser->c))
            {
                parser->current_lcode += parser->c;
                parser->token.content += parser->c;
            }
            else if (IS_ID(parser->c))
            { // �Ƿ�������
                parser->current_lcode += parser->c;
                error_number = true;
            }
            else
                break;
        }
        parser->token.tok_type = CONSTNUM;
        if (error_number)
            parser->Die("��" + parser->current_lcode + "���Ƿ�������");
    }

    // �������ַ�����ĸ
    else if (IS_ID(parser->c))
    {
        parser->token.content = parser->c;
        while (!parser->infile.eof())
        { // ������������������
            parser->c = parser->infile.get();
            if (parser->infile.eof())
                break;
            if (IS_ID(parser->c) || (IS_DIGIT(parser->c)))
            {
                parser->current_lcode += parser->c;
                parser->token.content += parser->c;
            }
            else
                break;
        }
        parser->token.tok_type = -1;
        for (int i = 0; token_table[i].content; ++i)
            if (parser->token.content == token_table[i].content)
            { // �Ǳ�����
                parser->token.tok_type = token_table[i].type;
                break;
            }
        if (parser->token.tok_type < 0)
            parser->token.tok_type = SYM;
    }

    // �������ǵ��ַ�������
    else if (IS_OPR(parser->c))
    {
        parser->token.content = parser->c;
        parser->c = parser->infile.get();
        for (int i = 0; token_table[i].content; ++i)
            if (parser->token.content == token_table[i].content)
            { // ���ַ���������һ��
                parser->token.tok_type = token_table[i].type;
                break;
            }
    }

    // �����Ƕ��ַ�������
    else if (IS_MOPR(parser->c))
    {
        parser->token.content = parser->c;
        parser->c = parser->infile.get();
        if (!parser->infile.eof())
        {
            parser->current_lcode += parser->c;
            if (parser->c == '=')
            { // ��ֵ��
                parser->token.content += parser->c;
                parser->c = parser->infile.get();
            }
            else if (parser->c == '>' && parser->token.content == "<")
            { // ���Ⱥ�
                parser->token.content = "<>";
                parser->c = parser->infile.get();
            }
            else
                parser->current_lcode.pop_back();
        }
        parser->token.tok_type = -1;
        for (int i = 0; token_table[i].content; ++i)
            if (parser->token.content == token_table[i].content)
            {
                parser->token.tok_type = token_table[i].type;
                break;
            }
        if (parser->token.tok_type < 0)
            parser->Die("��" + parser->current_lcode + "���Ƿ�������");
    }
}