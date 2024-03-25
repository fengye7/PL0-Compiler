bison -d parse.y
flex lex.l
gcc -o out lex.yy.c parse.tab.c