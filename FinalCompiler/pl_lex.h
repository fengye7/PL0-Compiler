// �ʷ�����
#pragma once

#define IS_ID(c) (('a' <= (c) && (c) <= 'z') || ('A' <= (c) && (c) <= 'Z'))
#define IS_DIGIT(c) ('0' <= (c) && (c) <= '9')
#define IS_OPR(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/' || (c) == '=' || (c) == ',' || (c) == ';' || (c) == '(' || (c) == ')')
#define IS_MOPR(c) ((c) == ':' || (c) == '<' || (c) == '>')

#include <cstring>
#include <sstream>

// ����token����
typedef enum
{
    /*
    �����֣�"program","begin","end","if","then","else","const","procedure","var","do","while","call","read","write","repeat","until","odd"
    */
    PROG,
    BEGIN,
    END,
    IF,
    THEN,
    ELSE,
    CONST,
    PROC,
    VAR,
    DO,
    WHILE,
    CALL,
    READ,
    WRITE,
    REPEAT,
    UNTIL,
    ODD,

    /*
    ����ͽ����+��-��*��/��:=��=��<>��>��>=��<��<=������������������ .
    */
    ADD, //"+"
    SUB, //"-"
    MUL, //"*"
    DIV, //"/"

    ASSIGN, //":="

    EQU,  //"="
    NEQU, //"<>"
    LARE, //">="
    LAR,  //">"
    LES,  //"<"
    LESE, //"<="

    LBR,   //"("
    RBR,   //")"
    SEMIC, //";"
    COMMA, //","
    POI,   //"."

    SYM,      // ��ʶ��
    CONSTNUM, // ����

    TOK_EOF, // �ļ�ĩβ

} LexicalType;

// ����Token�б�
struct
{
    int type;
    const char *content;
} token_table[] = {
    /*
        �����֣�"program","begin","end","if","then","else","const","procedure","var","do","while","call","read","write","repeat","until","odd"
        */
    {PROG, "program"},
    {BEGIN, "begin"},
    {END, "end"},
    {IF, "if"},
    {THEN, "then"},
    {ELSE, "else"},
    {CONST, "const"},
    {PROC, "procedure"},
    {VAR, "var"},
    {DO, "do"},
    {WHILE, "while"},
    {CALL, "call"},
    {READ, "read"},
    {WRITE, "write"},
    {REPEAT, "repeat"},
    {UNTIL, "until"},
    {ODD, "odd"},
    /*
    ����ͽ����+��-��*��/��:=��=��<>��>��>=��<��<=������������������ .
    */
    {ADD, "+"},
    {SUB, "-"},
    {MUL, "*"},
    {DIV, "/"},
    {ASSIGN, ":="},
    {EQU, "="},
    {NEQU, "<>"},
    {LAR, ">"},
    {LARE, ">="},
    {LES, "<"},
    {LESE, "<="},
    {LBR, "("},
    {RBR, ")"},
    {SEMIC, ";"},
    {COMMA, ","},
    {POI, "."},
    {-1, NULL},
};

struct Token
{
    std::string content;
    int tok_type;
}; 

class Parser;

// ����ʷ�������
class LexicalAnalysis
{
private:
    std::string filename; // ��ȡ�ĳ����ļ���·������
    Parser *parser;

public:
    void SetFile(std::string _filename);   // �����ļ�Դ
    void SetParentParser(Parser *_parser); // ���ø������﷨������

    void ReadFile();    // ���ļ�
    void CloseFile();   // �ر��ļ�
    void GetNextChar(); // ��ȡ��һ���ַ�
};