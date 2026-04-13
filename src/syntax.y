%{
#include <stdio.h>
#include <stdlib.h>

extern int nb_ligne;
int yylex();
void yyerror(const char *s);
%}

%union {
    int entier;
    float reel;
    char* str;
}

/* Déclaration des tokens (ceux qui seront renvoyés par lexical.l) */
%token BEGIN_PROJECT END_PROJECT SETUP RUN
%token DEFINE CONST INTEGER FLOAT
%token IF THEN ELSE ENDIF
%token LOOP WHILE ENDLOOP FOR IN TO ENDFOR
%token OUT AND OR NON
%token AFFECT COMP_GE EXPECT COMP_LE COMP_EQ COMP_NEQ COMP_GT COMP_LT COMP_AFFECT
%token PLUS MINUS MULT DIV
%token SEMI COLON COMMA PIPE
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <entier> T_ENTIER
%token <reel> T_FLOAT
%token <str> T_IDF T_CHAINE


/* Déclaration des priorités (du plus faible au plus fort) */
%left AND
%left OR
%right NON
%nonassoc COMP_EQ COMP_NEQ COMP_GT COMP_LT COMP_GE COMP_LE
%left PLUS MINUS
%left MULT DIV


%start programme

%%

/* -------------------------------- */
/* Règles de la grammaire           */
/* -------------------------------- */

programme:
    BEGIN_PROJECT T_IDF SEMI contenu END_PROJECT SEMI { printf("Programme compilé avec succès (syntaxe correcte) !\n"); };

contenu:
    SETUP_BLOCK RUN_BLOCK
    | RUN_BLOCK
;

SETUP_BLOCK:
    SETUP COLON declarations
;

RUN_BLOCK:
    RUN COLON LBRACE instructions RBRACE
;

declarations:
    declaration declarations
    | /* vide */
;

declaration:
    DEFINE idfs COLON type SEMI
    | DEFINE idfs COLON type EXPECT expression SEMI
    | DEFINE idfs COLON LBRACKET type SEMI T_ENTIER RBRACKET SEMI
    | CONST T_IDF COLON type EXPECT expression SEMI
;

idfs:
    T_IDF
    | T_IDF PIPE idfs
;

type:
    INTEGER
    | FLOAT
;

instructions:
    instruction instructions
    | /* vide */
;

instruction:
    T_IDF COMP_AFFECT expression SEMI
    | construct_if
    | construct_while
    | construct_for
    | in_out
;

in_out:
    IN LPAREN T_IDF RPAREN SEMI
    | OUT LPAREN T_CHAINE COMMA T_IDF RPAREN SEMI
;

expression:
    T_ENTIER
    | T_FLOAT
    | T_IDF
    | expression PLUS expression
    | expression MINUS expression
    | expression MULT expression
    | expression DIV expression
;

construct_if:
    IF LPAREN condition RPAREN THEN COLON LBRACE instructions RBRACE else_block ENDIF SEMI
;

else_block:
    ELSE LBRACE instructions RBRACE
    | /* vide */
;

construct_while:
    LOOP WHILE LPAREN condition RPAREN LBRACE instructions RBRACE ENDLOOP SEMI
;

construct_for:
    FOR T_IDF IN T_ENTIER TO T_ENTIER LBRACE instructions RBRACE ENDFOR SEMI
;

condition:
    expression EXPECT expression
    | expression COMP_EQ expression
    | expression COMP_NEQ expression
    | expression COMP_GT expression
    | expression COMP_LT expression
    | expression COMP_GE expression
    | expression COMP_LE expression
;

%%

/* Gestion des erreurs syntaxiques */
void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique a la ligne %d.\n", nb_ligne);
}

int main(void) {
    /* Lancer l'analyseur syntaxique */
    yyparse();
    return 0;
}