// 词法分析
#pragma once

#define IS_ID(c) (('a' <= (c) && (c) <= 'z') || ('A' <= (c) && (c) <= 'Z'))
#define IS_DIGIT(c) ('0' <= (c) && (c) <= '9')
#define IS_OPR(c) ((c) == '+' || (c) == '-' || (c) == '*' || (c) == '/' || (c) == '=' || (c) == ',' || (c) == ';' || (c) == '(' || (c) == ')')
#define IS_MOPR(c) ((c) == ':' || (c) == '<' || (c) == '>')

#include <cstring>
#include <sstream>

// 定义token类型
typedef enum
{
    /*
    保留字："program","begin","end","if","then","else","const","procedure","var","do","while","call","read","write","repeat","until","odd"
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
    算符和界符：+、-、*、/、:=、=、<>、>、>=、<、<=、（、）、；、，、 .
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

    SYM,      // 标识符
    CONSTNUM, // 常量

    TOK_EOF, // 文件末尾

} LexicalType;

// 定义Token列表
struct
{
    int type;
    const char *content;
} token_table[] = {
    /*
        保留字："program","begin","end","if","then","else","const","procedure","var","do","while","call","read","write","repeat","until","odd"
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
    算符和界符：+、-、*、/、:=、=、<>、>、>=、<、<=、（、）、；、，、 .
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

// 定义词法分析器
class LexicalAnalysis
{
private:
    std::string filename; // 读取的程序文件的路径名称
    Parser *parser;

public:
    void SetFile(std::string _filename);   // 设置文件源
    void SetParentParser(Parser *_parser); // 设置父对象语法分析器

    void ReadFile();    // 读文件
    void CloseFile();   // 关闭文件
    void GetNextChar(); // 获取下一个字符
};