%{
#include <stdio.h>
int nb_ligne=1;
%}


IDF     [a-zA-Z]([a-zA-Z0-9_]{0,12}[a-zA-Z0-9])?
ENTIER  [0-9]+
FLOAT   [0-9]+"."[0-9]+
CHAINE  \"[^\"]*\"

%%


"BeginProject"   {printf("Mot Cle: %s\n",yytext);}
"EndProject"     {printf("Mot Cle: %s\n",yytext);}
"Setup"          {printf("Mot Cle: %s\n",yytext);}
"Run"            {printf("Mot Cle: %s\n",yytext);}


"define"         {printf("Mot Cle: %s\n",yytext);}
"const"          {printf("Mot Cle: %s\n",yytext);}


"integer"        {printf("Mot Cle: %s\n",yytext);}
"float"          {printf("Mot Cle: %s\n",yytext);}


"if"             {printf("Mot Cle: %s\n",yytext);}
"then"           {printf("Mot Cle: %s\n",yytext);}
"else"           {printf("Mot Cle: %s\n",yytext);}
"endIf"          {printf("Mot Cle: %s\n",yytext);}


"loop"           {printf("Mot Cle: %s\n",yytext);}
"while"          {printf("Mot Cle: %s\n",yytext);}
"endloop"        {printf("Mot Cle: %s\n",yytext);}
"for"            {printf("Mot Cle: %s\n",yytext);}
"in"             {printf("Mot Cle: %s\n",yytext);}
"to"             {printf("Mot Cle: %s\n",yytext);}
"endfor"         {printf("Mot Cle: %s\n",yytext);}


"in"             {printf("Mot Cle: %s\n",yytext);}
"out"            {printf("Mot Cle: %s\n",yytext);}


"AND"            {printf("Operateur logique: %s\n",yytext);}
"OR"             {printf("Operateur logique: %s\n",yytext);}
"NON"            {printf("Operateur logique: %s\n",yytext);}


"<-"             {printf("Operateur affectation: %s\n",yytext);}

">="             {printf("Operateur comparaison: %s\n",yytext);}
"="              {printf("Operateur: %s\n",yytext);}
"<="             {printf("Operateur comparaison: %s\n",yytext);}
"=="             {printf("Operateur comparaison: %s\n",yytext);}
"!="             {printf("Operateur comparaison: %s\n",yytext);}
">"              {printf("Operateur comparaison: %s\n",yytext);}
"<"              {printf("Operateur comparaison: %s\n",yytext);}

"+"              {printf("Operateur arithmetique: %s\n",yytext);}
"-"              {printf("Operateur arithmetique: %s\n",yytext);}
"*"              {printf("Operateur arithmetique: %s\n",yytext);}
"/"              {printf("Operateur arithmetique: %s\n",yytext);}


";"              {printf("Separateur: %s\n",yytext);}
":"              {printf("Separateur: %s\n",yytext);}
","              {printf("Separateur: %s\n",yytext);}
"|"              {printf("Separateur: %s\n",yytext);}

"("              {printf("Separateur: %s\n",yytext);}
")"              {printf("Separateur: %s\n",yytext);}
"{"              {printf("Separateur: %s\n",yytext);}
"}"              {printf("Separateur: %s\n",yytext);}
"["              {printf("Separateur: %s\n",yytext);}
"]"              {printf("Separateur: %s\n",yytext);}


{FLOAT}          {printf("Float: %s\n",yytext);}
{ENTIER}         {printf("Entier: %s\n",yytext);}


{IDF}            {printf("IDF: %s\n",yytext);}


{CHAINE}         {printf("Chaine: %s\n",yytext);}


"%%".*           ;   /* commentaire ligne */

"//*"([^*]|\*+[^*/])*\*+/   ;  /* commentaire bloc */


[ \t]            ;
\n               {nb_ligne++;}


. {printf("Erreur lexicale a la ligne %d: %s\n",nb_ligne,yytext);}

%%

int main()
{
    yylex();
    return 0;
}