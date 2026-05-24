bison -d syntax.y
flex lexical.l
gcc lex.yy.c syntax.tab.c TS.c -o compilateur -lfl
@REM ./compilateur < final_semantique.txt

./compilateur < final.txt

