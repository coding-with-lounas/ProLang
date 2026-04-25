%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS.h" 
#include "quad.h" /* <-- AJOUT: Inclusion des quadruplets */

extern int nb_ligne;
extern int col;
int yylex();
void yyerror(const char *s);

/* Variables globales pour l'analyse sémantique */
char sauvType[20];
char idf_tab[50][30]; /* Tableau pour stocker "a | b | c" avant de savoir le type */
int nb_idfs = 0;

/* Variables pour les quadruplets du IF */
int Fin_if = 0, deb_else = 0;
char tmp[20];

/* Variables pour les quadruplets des boucles */
int deb_while = 0, fin_while = 0;
int deb_for = 0, fin_for = 0;
char iter_for[30]; /* Pour sauvegarder l'itérateur du FOR */
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
        /* Sémantique */
        if (!est_declare($1)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree\n", nb_ligne, col, $1);
        } else if (est_constante($1)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Modification de la constante '%s' interdite\n", nb_ligne, col, $1);
        }
        
        /* Génération du Quadruplet d'affectation */
      /*  quadr("<-", "valeur_expr", "vide", $1); */
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

/* --- RÈGLES ÉCLATÉES POUR LE IF-THEN-ELSE --- */

/* Règle R3 finale : Met à jour le BR (Saut inconditionnel) de la fin du THEN */
construct_if:
    B_if else_block ENDIF SEMI {
        sprintf(tmp, "%d", qc);
        updateQuad(Fin_if, 1, tmp);
    }
;

/* Règle R2 : Fin du bloc THEN. On génère le BR pour sauter le ELSE, et on met à jour le BZ du IF */
B_if:
    A_if instructions RBRACE {
        Fin_if = qc;
        quadr("BR", "", "vide", "vide");
        
        sprintf(tmp, "%d", qc);
        updateQuad(deb_else, 1, tmp);
    }
;

/* Règle R1 : Évaluation de la condition. On génère le BZ (Saut si Zéro/Faux) vers le ELSE */
A_if:
    IF LPAREN condition RPAREN THEN COLON LBRACE {
        deb_else = qc;
        quadr("BZ", "", "temp_cond", "vide");
    }
;

else_block:
    ELSE LBRACE instructions RBRACE
    | /* vide */
;

construct_while:
    LOOP WHILE LPAREN { 
        deb_while = qc; /* Sauvegarde de la position de la condition */
    } condition RPAREN LBRACE {
        fin_while = qc;
        quadr("BZ", "", "temp_cond", "vide"); /* Saut si condition fausse */
    } instructions RBRACE ENDLOOP SEMI {
        /* Fin de la boucle, remonter à la condition */
        sprintf(tmp, "%d", deb_while);
        quadr("BR", tmp, "vide", "vide");
        
        /* Mettre à jour le BZ pour pointer APRES la boucle */
        sprintf(tmp, "%d", qc);
        updateQuad(fin_while, 1, tmp);
    }
;

construct_for:
    FOR T_IDF IN T_ENTIER {
        if (!est_declare($2)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable de boucle '%s' non declaree\n", nb_ligne, col, $2);
        } else {
            /* 1. Initialisation : iterateur <- T_ENTIER (début) */
            char valDebut[20];
            sprintf(valDebut, "%d", $4);
            quadr("<-", valDebut, "vide", $2);
            strcpy(iter_for, $2); /* On sauvegarde le nom de la variable pour l'incrémentation */
        }
        deb_for = qc; /* Début de condition */
        
    } TO T_ENTIER LBRACE {
        /* 2. Condition : iterateur <= T_ENTIER (fin) */
        char valFin[20];
        sprintf(valFin, "%d", $7);     
        quadr("<=", iter_for, valFin, "temp_cond");
        
        fin_for = qc;
        quadr("BZ", "", "temp_cond", "vide"); /* Sortir si faux */
        
    } instructions RBRACE ENDFOR SEMI {
        /* 3. Incrémentation : iter_for <- iter_for + 1 */
        quadr("+", iter_for, "1", "temp_iter");
        quadr("<-", "temp_iter", "vide", iter_for);
        
        /* 4. Remonter à l'évaluation de la condition */
        sprintf(tmp, "%d", deb_for);
        quadr("BR", tmp, "vide", "vide");
        
        /* 5. Mettre à jour le BZ pour sortir complètement de la boucle */
        sprintf(tmp, "%d", qc);
        updateQuad(fin_for, 1, tmp);
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
    
    // yyparse() returns 0 on success, 1 on syntax error
    if (yyparse() == 0) {
        afficher();
        afficher_qdr();
    } else {
        printf("\n>> Echec de la compilation : tables et quadruplets non generes.\n");
    }
    
    return 0;
}