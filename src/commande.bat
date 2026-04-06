@REM bison -d syntax.y
flex lexical.l
gcc lex.yy.c -o lexical_analyzer -lfl
@REM gcc lex.yy.c syntax.tab.c -o compilateur -lfl -ly
./lexical_analyzer < source.txt
@REM ./compilateur < source.txt