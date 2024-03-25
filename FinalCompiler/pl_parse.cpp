// 语法分析的一些函数的实现
// #include "pl_lex.h"
// #include "pl_ast.h"
// #include "pl_code.h"
#include <iostream>
#include "pl_parse.h"

void Parser::Die(std::string error_info, int l)
{
    is_error = true;
    if (l < 0)
        std::cout << "line " << current_line << ",column " << current_lcode.length() << ":" << error_info << '\n';
    else
        std::cout << "line " << l << ":" << error_info << '\n';
    return;
}
void Parser::Hunger()
{
    while (token.tok_type != SEMIC && token.tok_type != BEGIN && token.tok_type != END && token.tok_type != DO && token.tok_type != THEN)
    {
        lexer.GetNextChar();
        if (token.tok_type == TOK_EOF)
            break;
    }
    return;
}

// 分析程序
AST Parser::Analyse()
{
    lexer.GetNextChar();
    AST root(current_line, AST_ROOT);
    root.AddChild(Prog());
    return root;
}

// 检查匹配函数
void Parser::Match(int tok_type)
{
    if (token.tok_type != tok_type)
    {
        std::string expect;
        if (tok_type == SYM)
            expect = "identifier";
        else if (tok_type == CONSTNUM)
            expect = "number";
        else
            for (int i = 0; token_table[i].content; ++i)
                if (tok_type == token_table[i].type)
                {
                    expect = token_table[i].content;
                    break;
                }
        Die("[" + current_lcode + "] 不在预期中的符号 \"" + expect + "\".");
        // hunger: 如果没有匹配的类型，获取token直到匹配
        Hunger();
    }
    lexer.GetNextChar();
    return;
}

// 下面是递归下降程序列表
AST Parser::Prog()
{
    Match(PROG);
    AST node(current_line, AST_PROG, token.content);
    Match(SYM);
    Match(SEMIC);
    coder.AddScope();

    node.AddChild(Block(0));
    coder.DelScope();
    return node;
}
AST Parser::Block(int var_size)
{
    AST node(current_line, AST_BLOCK);
    if (token.tok_type == CONST)
        node.AddChild(ConDecl());
    if (token.tok_type == VAR)
    {
        node.AddChild(VarDecl());
        var_size += node.GetChild().back().GetChild().size();
    }
    int entry_label = coder.execCode.size();
    coder.Emit(OP_JMP, 0, 0);
    if (token.tok_type == PROC)
        Proc(node);
    coder.execCode[entry_label].opnum = coder.execCode.size();
    coder.Emit(OP_INT, 0, var_size);
    node.AddChild(Body());
    return node;
}
AST Parser::ConDecl()
{
    AST node(current_line, AST_CONDECL);
    Match(CONST);
    node.AddChild(Const());
    while (token.tok_type == COMMA)
    {
        Match(COMMA);
        node.AddChild(Const());
    }
    Match(SEMIC);
    return node;
}
AST Parser::Const()
{
    AST node(current_line, AST_ID, token.content);
    std::string const_symbol = token.content;

    Match(SYM);
    Match(ASSIGN);

    AST num(current_line, AST_NUM, token.content);
    coder.AddNewSymbol(SYM_CONST, coder.ToNumber(token.content), const_symbol);
    node.AddChild(num);

    Match(CONSTNUM);
    return node;
}
AST Parser::VarDecl()
{
    AST node(current_line, AST_VARDECL);

    Match(VAR);

    AST id(current_line, AST_ID, token.content);
    coder.AddNewSymbol(SYM_VAR, 0, token.content);
    node.AddChild(id);

    Match(SYM);
    while (token.tok_type == COMMA)
    {
        Match(COMMA);

        AST id(current_line, AST_ID, token.content);
        coder.AddNewSymbol(SYM_VAR, 0, token.content);
        node.AddChild(id);

        Match(SYM);
    }
    Match(SEMIC);
    return node;
}
void Parser::Proc(AST &root)
{
    AST node(current_line, AST_PROC);

    Match(PROC);

    node.SetStr(token.content);
    std::string proc_name = token.content;
    coder.AddNewSymbol(SYM_PROC, coder.execCode.size(), proc_name);

    Match(SYM);

    AST para(current_line, AST_PARAMETER);

    coder.AddScope();
    Match(LBR);
    if (token.tok_type == SYM)
    {
        AST id(current_line, AST_ID, token.content);
        coder.AddNewSymbol(SYM_VAR, 0, token.content);
        para.AddChild(id);

        Match(SYM);
        while (token.tok_type == COMMA)
        {
            Match(COMMA);

            AST id(current_line, AST_ID, token.content);
            coder.AddNewSymbol(SYM_VAR, 0, token.content);
            para.AddChild(id);

            Match(SYM);
        }
    }

    node.AddChild(para);
    coder.SetProcedureArgSize(proc_name, para.GetChild().size());
    Match(RBR);
    Match(SEMIC);

    node.AddChild(Block(para.GetChild().size()));
    root.AddChild(node);
    coder.Emit(OP_OPR, 0, CALC_RET);
    coder.DelScope();
    while (token.tok_type == SEMIC)
    {
        Match(SEMIC);
        Proc(root);
    }
    return;
}
AST Parser::Body()
{
    AST node(current_line, AST_BLOCK);

    Match(BEGIN);
    node.AddChild(Statement());
    while (token.tok_type == SEMIC)
    {
        Match(SEMIC);
        node.AddChild(Statement());
    }
    Match(END);
    return node;
}
AST Parser::Statement()
{
    AST node(current_line);
    if (token.tok_type == SYM)
    {
        node.SetType(ASSIGN);
        node.SetStr(token.content);
        Symbol sym = coder.GetSymbol(token.content);

        Match(SYM);
        Match(ASSIGN);
        node.AddChild(Exp());

        if (sym.type == SYM_VAR)
        {
            int data = coder.GetSymbolPlace(sym.name);
            coder.Emit(OP_STO, data >> 16, data & 0xffff);
        }
        else
            Die("不能更改的变量: " + sym.name);
    }
    else if (token.tok_type == IF)
    {
        node.SetType(AST_CONDITION);

        AST _if(current_line, AST_IF);
        Match(IF);
        _if.AddChild(Lexp());
        int jmp_false_label = coder.execCode.size();
        coder.Emit(OP_JPC, 0, 0);
        Match(THEN);
        _if.AddChild(Statement());
        int jmp_out = coder.execCode.size();
        coder.Emit(OP_JMP, 0, 0);
        node.AddChild(_if);
        coder.execCode[jmp_false_label].opnum = coder.execCode.size();
        if (token.tok_type == ELSE)
        {
            AST _else(current_line, AST_ELSE);
            Match(ELSE);
            _else.AddChild(Statement());
            node.AddChild(_else);
        }
        coder.execCode[jmp_out].opnum = coder.execCode.size();
    }
    else if (token.tok_type == WHILE)
    {
        int while_jmp_label = coder.execCode.size();
        node.SetType(AST_WHILE);
        Match(WHILE);
        node.AddChild(Lexp());
        Match(DO);
        int while_check_label = coder.execCode.size();
        coder.Emit(OP_JPC, 0, 0);
        node.AddChild(Statement());
        coder.Emit(OP_JMP, 0, while_jmp_label);
        coder.execCode[while_check_label].opnum = coder.execCode.size();
    }
    else if (token.tok_type == CALL)
    {
        node.SetType(AST_CALL);

        Match(CALL);
        node.SetStr(token.content);
        Symbol sym = coder.GetSymbol(token.content);
        if (sym.type != SYM_PROC)
            Die(token.content + " 不是一个过程");

        Match(SYM);
        Match(LBR);
        if (token.tok_type != RBR)
        {
            node.AddChild(Exp());
            while (token.tok_type == COMMA)
            {
                Match(COMMA);
                node.AddChild(Exp());
            }
        }
        Match(RBR);
        coder.Emit(OP_CAL, coder.GetSymbolPlace(sym.name) >> 16, sym.number);
        if (sym.type == SYM_PROC)
        {
            if (node.GetChild().size() > sym.procedureArgSize)
                Die("太多参数", node.GetLine());
            else if (node.GetChild().size() < sym.procedureArgSize)
                Die("缺乏参数", node.GetLine());
        }
    }
    else if (token.tok_type == BEGIN)
        node = Body();
    else if (token.tok_type == READ)
    {
        node.SetType(AST_READ);
        Match(READ);
        Match(LBR);

        AST id(current_line, AST_ID, token.content);
        Symbol sym = coder.GetSymbol(token.content);
        if (sym.type == SYM_VAR)
        {
            int data = coder.GetSymbolPlace(token.content);
            coder.Emit(OP_RED, data >> 16, data & 0xffff);
        }
        else
            Die("不可修改的符号: " + token.content);
        node.AddChild(id);

        Match(SYM);
        while (token.tok_type == COMMA)
        {
            Match(COMMA);

            AST id(current_line, AST_ID, token.content);
            Symbol sym = coder.GetSymbol(token.content);
            if (sym.type == SYM_VAR)
            {
                int data = coder.GetSymbolPlace(token.content);
                coder.Emit(OP_RED, data >> 16, data & 0xffff);
            }
            else
                Die("不可修改的符号: " + token.content);
            node.AddChild(id);

            Match(SYM);
        }
        Match(RBR);
    }
    else if (token.tok_type == WRITE)
    {
        node.SetType(AST_WRITE);

        Match(WRITE);
        Match(LBR);
        node.AddChild(Exp());
        coder.Emit(OP_WRT, 0, 0);
        while (token.tok_type == COMMA)
        {
            Match(COMMA);
            node.AddChild(Exp());
            coder.Emit(OP_WRT, 0, 0);
        }
        Match(RBR);
    }
    else
    {
        Die("[" + current_lcode + "] 期望一个句子 \";\".");
        Hunger();
    }
    return node;
}
AST Parser::Lexp()
{
    AST node;
    node.SetLine(current_line);
    if (token.tok_type == ODD)
    {
        node.SetType(AST_ODD);
        Match(ODD);
        node.AddChild(Exp());
        coder.Emit(OP_OPR, 0, CALC_ODD);
    }
    else
    {
        AST tmp1, tmp2;
        tmp1 = Exp();
        node = Lop();
        tmp2 = Exp();
        switch (node.GetType())
        {
        case AST_EQU:
            coder.Emit(OP_OPR, 0, CALC_EQ);
            break;
        case AST_NEQU:
            coder.Emit(OP_OPR, 0, CALC_NEQ);
            break;
        case AST_LES:
            coder.Emit(OP_OPR, 0, CALC_LES);
            break;
        case AST_LESE:
            coder.Emit(OP_OPR, 0, CALC_LEQ);
            break;
        case AST_LAR:
            coder.Emit(OP_OPR, 0, CALC_GRT);
            break;
        case AST_LARE:
            coder.Emit(OP_OPR, 0, CALC_GEQ);
            break;
        }
        node.AddChild(tmp1);
        node.AddChild(tmp2);
    }
    return node;
}
AST Parser::Exp()
{
    AST node;
    node.SetLine(current_line);

    int unary_type = token.tok_type;
    if (token.tok_type == ADD || token.tok_type == SUB)
    {
        node.SetType(token.tok_type == ADD ? AST_ADD : AST_SUB);
        Match(token.tok_type);
    }
    if (node.GetType() != AST_ROOT)
        node.AddChild(Term());
    else
        node = Term();
    if (unary_type == SUB)
        coder.Emit(OP_OPR, 0, CALC_NEGA);

    while (token.tok_type == ADD || token.tok_type == SUB)
    {
        int type = token.tok_type;
        AST tmp(current_line, token.tok_type == ADD ? AST_ADD : AST_SUB);
        tmp.AddChild(node);
        Match(token.tok_type);
        tmp.AddChild(Term());
        coder.Emit(OP_OPR, 0, type == ADD ? CALC_PLUS : CALC_MINUS);
        node = tmp;
    }
    return node;
}
AST Parser::Term()
{
    AST node;
    node = Factor();
    while (token.tok_type == MUL || token.tok_type == DIV)
    {
        int type = token.tok_type;
        AST tmp(current_line, token.tok_type == MUL ? AST_MUL : AST_DIV);
        tmp.AddChild(node);
        Match(token.tok_type);
        tmp.AddChild(Factor());
        coder.Emit(OP_OPR, 0, type == MUL ? CALC_MULT : CALC_DIV);
        node = tmp;
    }
    return node;
}
AST Parser::Factor()
{
    AST node;
    if (token.tok_type == SYM)
    {
        node.SetLine(current_line);
        node.SetType(AST_ID);
        node.SetStr(token.content);

        Symbol sym = coder.GetSymbol(token.content);
        int type = sym.type;
        int const_num = sym.number;
        if (type == SYM_VAR)
        {
            int data = coder.GetSymbolPlace(token.content);
            coder.Emit(OP_LOD, data >> 16, data & 0xffff);
        }
        else if (type == SYM_CONST)
            coder.Emit(OP_LIT, 0, const_num);
        else
            Die("不是变量或者常量: " + token.content);

        Match(SYM);
    }
    else if (token.tok_type == CONSTNUM)
    {
        node.SetLine(current_line);
        node.SetType(AST_NUM);
        node.SetStr(token.content);
        coder.Emit(OP_LIT, 0, coder.ToNumber(token.content));
        Match(CONSTNUM);
    }
    else if (token.tok_type == LBR)
    {
        Match(LBR);
        node = Exp();
        Match(RBR);
    }
    else
    {
        Die("[" + current_lcode + "] 这里期望一个参数.");
        Hunger();
    }
    return node;
}
AST Parser::Lop()
{
    AST node(current_line);
    if (token.tok_type == EQU || token.tok_type == NEQU || token.tok_type == LES || token.tok_type == LESE || token.tok_type == LAR || token.tok_type == LARE)
    {
        int atype;
        switch (token.tok_type)
        {
        case EQU:
            atype = AST_EQU;
            break;
        case NEQU:
            atype = AST_NEQU;
            break;
        case LES:
            atype = AST_LES;
            break;
        case LESE:
            atype = AST_LESE;
            break;
        case LAR:
            atype = AST_LAR;
            break;
        case LARE:
            atype = AST_LARE;
            break;
        }
        node.SetType(atype);
        Match(token.tok_type);
    }
    else
    {
        Die("[" + current_lcode + "] 期望比较运算符.");
        Hunger();
    }
    return node;
}