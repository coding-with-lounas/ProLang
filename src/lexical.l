%{
#include <stdio.h>
#include "syntax.tab.h" 
#include "TS.h" 
int nb_ligne = 1;
int col = 1; /* Suivi de la colonne */

/* Action exécutée avant chaque token pour mettre à jour la colonne */
#define YY_USER_ACTION col += yyleng;
%}

IDF     [a-zA-Z]([a-zA-Z0-9_]{0,12}[a-zA-Z0-9])?
ENTIER  [0-9]+
FLOAT   [0-9]+"."[0-9]+
CHAINE  \"[^\"]*\"

%%

"BeginProject"   { rechercher(yytext, "Mot cle", 2); return BEGIN_PROJECT; }
"EndProject"     { rechercher(yytext, "Mot cle", 2); return END_PROJECT; }
"Setup"          { rechercher(yytext, "Mot cle", 2); return SETUP; }
"Run"            { rechercher(yytext, "Mot cle", 2); return RUN; }

"define"         { rechercher(yytext, "Mot cle", 2); return DEFINE; }
"const"          { rechercher(yytext, "Mot cle", 2); return CONST; }
"integer"        { rechercher(yytext, "Mot cle", 2); return INTEGER; }
"float"          { rechercher(yytext, "Mot cle", 2); return FLOAT; }

"if"             { rechercher(yytext, "Mot cle", 2); return IF; }
"then"           { rechercher(yytext, "Mot cle", 2); return THEN; }
"else"           { rechercher(yytext, "Mot cle", 2); return ELSE; }
"endIf"          { rechercher(yytext, "Mot cle", 2); return ENDIF; }

"loop"           { rechercher(yytext, "Mot cle", 2); return LOOP; }
"while"          { rechercher(yytext, "Mot cle", 2); return WHILE; }
"endloop"        { rechercher(yytext, "Mot cle", 2); return ENDLOOP; }
"for"            { rechercher(yytext, "Mot cle", 2); return FOR; }
"in"             { rechercher(yytext, "Mot cle", 2); return IN; }
"to"             { rechercher(yytext, "Mot cle", 2); return TO; }
"endfor"         { rechercher(yytext, "Mot cle", 2); return ENDFOR; }

"out"            { rechercher(yytext, "Mot cle", 2); return OUT; }

"AND"            { rechercher(yytext, "Mot cle", 2); return AND; }
"OR"             { rechercher(yytext, "Mot cle", 2); return OR; }
"NON"            { rechercher(yytext, "Mot cle", 2); return NON; }

"<-"             { rechercher(yytext, "Separateur", 3); return COMP_AFFECT; }
">="             { rechercher(yytext, "Separateur", 3); return COMP_GE; }
"="              { rechercher(yytext, "Separateur", 3); return EXPECT; }
"<="             { rechercher(yytext, "Separateur", 3); return COMP_LE; }
"=="             { rechercher(yytext, "Separateur", 3); return COMP_EQ; }
"!="             { rechercher(yytext, "Separateur", 3); return COMP_NEQ; }
">"              { rechercher(yytext, "Separateur", 3); return COMP_GT; }
"<"              { rechercher(yytext, "Separateur", 3); return COMP_LT; }

"+"              { rechercher(yytext, "Separateur", 3); return PLUS; }
"-"              { rechercher(yytext, "Separateur", 3); return MINUS; }
"*"              { rechercher(yytext, "Separateur", 3); return MULT; }
"/"              { rechercher(yytext, "Separateur", 3); return DIV; }

";"              { rechercher(yytext, "Separateur", 3); return SEMI; }
":"              { rechercher(yytext, "Separateur", 3); return COLON; }
","              { rechercher(yytext, "Separateur", 3); return COMMA; }
"|"              { rechercher(yytext, "Separateur", 3); return PIPE; }

"("              { rechercher(yytext, "Separateur", 3); return LPAREN; }
")"              { rechercher(yytext, "Separateur", 3); return RPAREN; }
"{"              { rechercher(yytext, "Separateur", 3); return LBRACE; }
"}"              { rechercher(yytext, "Separateur", 3); return RBRACE; }
"["              { rechercher(yytext, "Separateur", 3); return LBRACKET; }
"]"              { rechercher(yytext, "Separateur", 3); return RBRACKET; }

{FLOAT} {
   yylval.reel = atof(yytext);
   rechercher(yytext, "Cst float", 1); 
   return T_FLOAT;
}

{ENTIER} {
   yylval.entier = atoi(yytext);
   rechercher(yytext, "Cst entiere", 1);
   return T_ENTIER;
}

{IDF} {
   yylval.str = strdup(yytext);
   rechercher(yytext, "IDF", 1); 
   return T_IDF;
}

{CHAINE}  { 
    yylval.str = strdup(yytext);
    rechercher(yytext, "Chaine", 1);
    return T_CHAINE; 
}

"%%".* { /* commentaire ligne */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* commentaire bloc */ }

[ \t\r]+         { /* ignorer espaces et tabulations */ }
\n               { nb_ligne++; col = 1; } /* Reset colonne à chaque ligne */

. { printf("Erreur lexicale a la ligne %d, colonne %d: %s\n", nb_ligne, col, yytext); }

%%

int yywrap() {
    return 1;
}