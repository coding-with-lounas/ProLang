flex lexical.l
bison -d syntax.y
gcc lex.yy.c syntax.tab.c -o compilateur -lfl
./compilateur < source.txt