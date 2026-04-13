%{
#include <stdio.h>
#include "syntax.tab.h" /* IMPORTANT: permet la communication avec syntax.y */
int nb_ligne=1;
%}

IDF     [a-zA-Z]([a-zA-Z0-9_]{0,12}[a-zA-Z0-9])?
ENTIER  [0-9]+
FLOAT   [0-9]+"."[0-9]+
CHAINE  \"[^\"]*\"

%%

"BeginProject"   { return BEGIN_PROJECT; }
"EndProject"     { return END_PROJECT; }
"Setup"          { return SETUP; }
"Run"            { return RUN; }

"define"         { return DEFINE; }
"const"          { return CONST; }
"integer"        { return INTEGER; }
"float"          { return FLOAT; }

"if"             { return IF; }
"then"           { return THEN; }
"else"           { return ELSE; }
"endIf"          { return ENDIF; }

"loop"           { return LOOP; }
"while"          { return WHILE; }
"endloop"        { return ENDLOOP; }
"for"            { return FOR; }
"in"             { return IN; }
"to"             { return TO; }
"endfor"         { return ENDFOR; }

"out"            { return OUT; }

"AND"            { return AND; }
"OR"             { return OR; }
"NON"            { return NON; }

"<-"             { return COMP_AFFECT; }
">="             { return COMP_GE; }
"="              { return EXPECT; }
"<="             { return COMP_LE; }
"=="             { return COMP_EQ; }
"!="             { return COMP_NEQ; }
">"              { return COMP_GT; }
"<"              { return COMP_LT; }

"+"              { return PLUS; }
"-"              { return MINUS; }
"*"              { return MULT; }
"/"              { return DIV; }

";"              { return SEMI; }
":"              { return COLON; }
","              { return COMMA; }
"|"              { return PIPE; }

"("              { return LPAREN; }
")"              { return RPAREN; }
"{"              { return LBRACE; }
"}"              { return RBRACE; }
"["              { return LBRACKET; }
"]"              { return RBRACKET; }

{FLOAT} {
   yylval.reel = atof(yytext);
   return T_FLOAT;
}

{ENTIER} {
   yylval.entier = atoi(yytext);
   return T_ENTIER;
}

{IDF} {
   yylval.str = strdup(yytext);
   return T_IDF;
}

{CHAINE}  { 
            yylval.str = strdup(yytext);
             return T_CHAINE; 
             }

"%%".*           { /* commentaire ligne */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* commentaire bloc */ }

[ \t\r]+         { /* ignorer espaces et tabulations */ }
\n               { nb_ligne++; }

. { printf("Erreur lexicale a la ligne %d: %s\n", nb_ligne, yytext); }

%%

int yywrap() {
    return 1;
}
