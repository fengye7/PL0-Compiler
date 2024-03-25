bison -d parse.y
flex lex.l
gcc -o out lex.yy.c parse.tab.c
./out

gcc interpret.c
./a.out

if You use macos
chmod +x for 2 .sh
then
./complier.sh
./interpret.sh
