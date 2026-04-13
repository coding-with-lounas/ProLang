%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS.h" 

extern int nb_ligne;
extern int col;
int yylex();
void yyerror(const char *s);

/* Variables globales pour l'analyse sémantique */
char sauvType[20];
char idf_tab[50][30]; /* Tableau pour stocker "a | b | c" avant de savoir le type */
int nb_idfs = 0;

%}

%union {
    int entier;
    float reel;
    char* str;
}

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

%left AND
%left OR
%right NON
%nonassoc COMP_EQ COMP_NEQ COMP_GT COMP_LT COMP_GE COMP_LE
%left PLUS MINUS
%left MULT DIV

%start programme

%%

programme:
    BEGIN_PROJECT T_IDF SEMI contenu END_PROJECT SEMI { printf("\n>> Compilation terminee avec succes !\n"); };

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

/* ================================================================= */
/* SEMANTIQUE : DECLARATIONS                        */
/* ================================================================= */
declaration:
    /* 1. Declaration multiple: define a | b : integer ; */
    DEFINE idfs COLON type SEMI {
        for(int i = 0; i < nb_idfs; i++) {
            if (est_declare(idf_tab[i])) {
                printf("Erreur Semantique, ligne %d, colonne %d : Double declaration de la variable '%s'\n", nb_ligne, col, idf_tab[i]);
            } else {
                inserer_type_nature(idf_tab[i], sauvType, "VAR", 0);
            }
        }
        nb_idfs = 0; /* Reset pour la prochaine ligne */
    }
    
    /* 2. Declaration avec initialisation: define b : integer = 10 ; */
    | DEFINE idfs COLON type EXPECT expression SEMI {
        if (nb_idfs != 1) {
            printf("Erreur Syntaxe, ligne %d, colonne %d : Initialisation non permise pour de multiples identifiants.\n", nb_ligne, col);
        } else {
            if (est_declare(idf_tab[0])) {
                printf("Erreur Semantique, ligne %d, colonne %d : Double declaration de '%s'\n", nb_ligne, col, idf_tab[0]);
            } else {
                inserer_type_nature(idf_tab[0], sauvType, "VAR", 0);
            }
        }
        nb_idfs = 0;
    }
    
    /* 3. Declaration de tableau: define Tab : [integer; 20] ; */
    | DEFINE idfs COLON LBRACKET type SEMI T_ENTIER RBRACKET SEMI {
        if (nb_idfs != 1) {
            printf("Erreur Syntaxe, ligne %d, colonne %d : Declaration de tableaux multiples non supportee.\n", nb_ligne, col);
        } else {
            if (est_declare(idf_tab[0])) {
                printf("Erreur Semantique, ligne %d, colonne %d : Double declaration du tableau '%s'\n", nb_ligne, col, idf_tab[0]);
            } else {
                if ($7 <= 0) {
                    printf("Erreur Semantique, ligne %d, colonne %d : La taille du tableau '%s' doit etre > 0\n", nb_ligne, col, idf_tab[0]);
                } else {
                    inserer_type_nature(idf_tab[0], sauvType, "TAB", $7);
                }
            }
        }
        nb_idfs = 0;
    }
    
    /* 4. Declaration de Constante: const Pi : float = 3.14 ; */
    | CONST T_IDF COLON type EXPECT expression SEMI {
        if (est_declare($2)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Double declaration de la constante '%s'\n", nb_ligne, col, $2);
        } else {
            inserer_type_nature($2, sauvType, "CONST", 0);
        }
    }
;

/* Capturer tous les IDFs séparés par un PIPE '|' */
idfs:
    T_IDF { strcpy(idf_tab[nb_idfs++], $1); }
    | T_IDF { strcpy(idf_tab[nb_idfs++], $1); } PIPE idfs
;

/* Sauvegarder le type courant pour l'attribuer aux variables */
type:
    INTEGER { strcpy(sauvType, "integer"); }
    | FLOAT { strcpy(sauvType, "float"); }
;

instructions:
    instruction instructions
    | /* vide */
;

/* ================================================================= */
/* SEMANTIQUE : INSTRUCTIONS                        */
/* ================================================================= */
instruction:
    T_IDF COMP_AFFECT expression SEMI {
        if (!est_declare($1)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree\n", nb_ligne, col, $1);
        } else if (est_constante($1)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Modification de la constante '%s' interdite\n", nb_ligne, col, $1);
        }
    }
    | construct_if
    | construct_while
    | construct_for
    | in_out
;

in_out:
    IN LPAREN T_IDF RPAREN SEMI {
        if (!est_declare($3)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree (Input)\n", nb_ligne, col, $3);
        }
    }
    | OUT LPAREN T_CHAINE COMMA T_IDF RPAREN SEMI {
        if (!est_declare($5)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree (Output)\n", nb_ligne, col, $5);
        }
    }
;

/* ================================================================= */
/* SEMANTIQUE : EXPRESSIONS                         */
/* ================================================================= */
expression:
    T_ENTIER
    | T_FLOAT
    | T_IDF {
        if (!est_declare($1)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree dans l'expression\n", nb_ligne, col, $1);
        }
    }
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
    FOR T_IDF IN T_ENTIER TO T_ENTIER LBRACE instructions RBRACE ENDFOR SEMI {
        if (!est_declare($2)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable de boucle '%s' non declaree\n", nb_ligne, col, $2);
        }
    }
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

void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique, ligne %d, colonne %d\n", nb_ligne, col);
}

int main(void) {
    initialization();
    yyparse();
    afficher();
    return 0;
}