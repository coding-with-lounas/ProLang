flex lexical.l
gcc lex.yy.c -o lexical_analyzer -lfl
lexical_analyzer < source.txt