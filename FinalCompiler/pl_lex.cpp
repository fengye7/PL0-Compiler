// 词法分析的一些函数的实现
#include <iostream>
#include "./pl_lex.h"
#include "./pl_parse.h"

// 设置文件源
void LexicalAnalysis::SetFile(std::string _filename)
{
    filename = _filename;
}

// 设置父对象parser
void LexicalAnalysis::SetParentParser(Parser *_parser)
{
    parser = _parser;
}

// 读文件
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

// 关闭文件
void LexicalAnalysis::CloseFile()
{
    parser->infile.close();
    return;
}

// 获取下一个字符
void LexicalAnalysis::GetNextChar()
{
    // 文件到末尾
    if (parser->infile.eof())
    {
        parser->token.content = "";
        parser->token.tok_type = TOK_EOF;
        return;
    }
    // 分析字符
    if (parser->c)
        parser->current_lcode += parser->c;
    if (parser->c != '\n' && parser->c != '\r' && parser->c != '\t' && parser->c != ' ' && !IS_ID(parser->c) && !IS_DIGIT(parser->c) && !IS_OPR(parser->c) && !IS_MOPR(parser->c))
        parser->Die("【" + parser->current_lcode + "】不能识别的字符");

    // 处理异常和空白字符
    while (!parser->infile.eof() && !IS_ID(parser->c) && !IS_DIGIT(parser->c) && !IS_OPR(parser->c) && !IS_MOPR(parser->c))
    {
        parser->c = parser->infile.get(); // 不断地读取字符，直到字符为有效字符
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
            parser->Die("【" + parser->current_lcode + "】不能识别的字符");
    }
    // 读到的字符是数字
    if (IS_DIGIT(parser->c))
    {
        parser->token.content = parser->c;
        bool error_number = false;
        while (!parser->infile.eof())
        { // 将数字读完
            parser->c = parser->infile.get();
            if (parser->infile.eof())
                break;
            if (IS_DIGIT(parser->c))
            {
                parser->current_lcode += parser->c;
                parser->token.content += parser->c;
            }
            else if (IS_ID(parser->c))
            { // 非法的数字
                parser->current_lcode += parser->c;
                error_number = true;
            }
            else
                break;
        }
        parser->token.tok_type = CONSTNUM;
        if (error_number)
            parser->Die("【" + parser->current_lcode + "】非法的数字");
    }

    // 读到的字符是字母
    else if (IS_ID(parser->c))
    {
        parser->token.content = parser->c;
        while (!parser->infile.eof())
        { // 将整个变量名读出来
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
            { // 是保留字
                parser->token.tok_type = token_table[i].type;
                break;
            }
        if (parser->token.tok_type < 0)
            parser->token.tok_type = SYM;
    }

    // 读到的是单字符操作符
    else if (IS_OPR(parser->c))
    {
        parser->token.content = parser->c;
        parser->c = parser->infile.get();
        for (int i = 0; token_table[i].content; ++i)
            if (parser->token.content == token_table[i].content)
            { // 单字符操作符的一种
                parser->token.tok_type = token_table[i].type;
                break;
            }
    }

    // 可能是多字符操作符
    else if (IS_MOPR(parser->c))
    {
        parser->token.content = parser->c;
        parser->c = parser->infile.get();
        if (!parser->infile.eof())
        {
            parser->current_lcode += parser->c;
            if (parser->c == '=')
            { // 赋值号
                parser->token.content += parser->c;
                parser->c = parser->infile.get();
            }
            else if (parser->c == '>' && parser->token.content == "<")
            { // 不等号
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
            parser->Die("【" + parser->current_lcode + "】非法操作符");
    }
}