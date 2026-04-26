%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TS.h" 
#include "quad.h" /* <-- AJOUT: Inclusion des quadruplets */

int nb_temp = 1;
char temp_nom[20]; // Buffer pour stocker le nom du temporaire

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
    char* str;      /* Champ pour les noms d'IDF et temporaires */
}

%type <str> expression condition

%token BEGIN_PROJECT END_PROJECT SETUP RUN
%token DEFINE CONST INTEGER FLOAT
%token IF THEN ELSE ENDIF
%token LOOP WHILE ENDLOOP FOR IN TO ENDFOR
%token OUT AND OR NON
%token AFFECT COMP_GE EXPECT COMP_LE COMP_EQ COMP_NEQ COMP_GT COMP_LT COMP_AFFECT
%token PLUS MINUS MULT DIV
%token SEMI COLON COMMA PIPE
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token <str> T_IDF T_ENTIER T_FLOAT T_CHAINE

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
    | error SEMI declarations { yyerrok; }
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
                if (atoi($7) <= 0) {
                    printf("Erreur Semantique, ligne %d, colonne %d : La taille du tableau '%s' doit etre > 0\n", nb_ligne, col, idf_tab[0]);
                } else {
                    inserer_type_nature(idf_tab[0], sauvType, "TAB", atoi($7));
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
    | error SEMI instructions { yyerrok; }
    | error RBRACE instructions { yyerrok; }
    | /* vide */
;

/* ================================================================= */
/* SEMANTIQUE : INSTRUCTIONS                        */
/* ================================================================= */
instruction:
    /* CAS 1 : Affectation simple (ex: x <- 10;) */
    T_IDF COMP_AFFECT expression SEMI {
        if (!est_declare($1)) {
            printf("Erreur Semantique, ligne %d : Variable '%s' non declaree\n", nb_ligne, $1);
        } else if (strcmp(get_nature($1), "VAR") != 0) {
            printf("Erreur Semantique, ligne %d : '%s' n'est pas une variable simple\n", nb_ligne, $1);
        } else if (est_constante($1)) {
            printf("Erreur Semantique, ligne %d : Modification de la constante '%s' interdite\n", nb_ligne, $1);
        } else {
            // Génération du quadruplet d'affectation simple
            quadr("<-", $3, "vide", $1);
        }
    }

    /* CAS 2 : Affectation dans un tableau (ex: tab[i] <- 10;) */
    | T_IDF LBRACKET expression RBRACKET COMP_AFFECT expression SEMI {
        if (!est_declare($1)) {
            printf("Erreur Semantique, ligne %d : Tableau '%s' non declare\n", nb_ligne, $1);
        } else if (strcmp(get_nature($1), "TAB") != 0) {
            printf("Erreur Semantique, ligne %d : '%s' n'est pas un tableau\n", nb_ligne, $1);
        } else {
            // Génération du quadruplet pour tableau
            char dest[50];
            sprintf(dest, "%s[%s]", $1, $3);
            quadr("<-", $6, "vide", dest);
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
        quadr("IN", "vide", "vide", $3);
    }
    | OUT LPAREN T_CHAINE COMMA T_IDF RPAREN SEMI {
        if (!est_declare($5)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable '%s' non declaree (Output)\n", nb_ligne, col, $5);
        }
        quadr("OUT", $3, "vide", $5);
    }
;

/* ================================================================= */
/* SEMANTIQUE : EXPRESSIONS                         */
/* ================================================================= */
expression:
    T_ENTIER { 
        $$ = strdup($1); // On transmet la valeur brute (ex: "5")
    }
    | T_FLOAT { 
        $$ = strdup($1); 
    }
    | T_IDF {
        if (!est_declare($1)) {
            printf("Erreur Semantique, ligne %d : '%s' non declaree\n", nb_ligne, $1);
        }
        $$ = strdup($1); // On transmet le nom de l'IDF
    }
    /* AJOUT : LECTURE TABLEAU (ex: tab[i]) */
    | T_IDF LBRACKET expression RBRACKET {
        if (!est_declare($1)) {
            printf("Erreur Semantique : %s non declare\n", $1);
        } else if (strcmp(get_nature($1), "TAB") != 0) {
            printf("Erreur Semantique : %s n'est pas un tableau\n", $1);
        } else {
            // Création du temporaire
            sprintf(temp_nom, "t%d", nb_temp++);
            
            // Génération : (= [], NomTableau, Indice, Temporaire)
            char src[50];
            sprintf(src, "%s[%s]", $1, $3);
            quadr("=", src, "vide", temp_nom);
            
            // On remonte le nom du temporaire vers le parent
            $$ = strdup(temp_nom);
        }
    }
    /* CALCULS AVEC GENERATION */
    | expression PLUS expression {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("+", $1, $3, temp_nom);
        $$ = strdup(temp_nom);
    }
    | expression MINUS expression {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("-", $1, $3, temp_nom);
        $$ = strdup(temp_nom);
    }
    | expression MULT expression {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("*", $1, $3, temp_nom);
        $$ = strdup(temp_nom);
    }
    | expression DIV expression {
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("/", $1, $3, temp_nom);
        $$ = strdup(temp_nom);
    }
    | LPAREN expression RPAREN {
        $$ = strdup($2);
    }
;

/* --- RÈGLES POUR LE IF-THEN-ELSE --- */

construct_if:
    IF LPAREN condition RPAREN THEN COLON LBRACE {
        $<entier>$ = qc;
        quadr("BZ", "vide", $3, "vide");
    } instructions RBRACE {
        $<entier>$ = qc;
        quadr("BR", "vide", "vide", "vide");
        sprintf(tmp, "%d", qc);
        updateQuad($<entier>8, 3, tmp);
    } else_block ENDIF SEMI {
        sprintf(tmp, "%d", qc);
        updateQuad($<entier>11, 3, tmp);
    }
;

else_block:
    ELSE LBRACE instructions RBRACE
    | /* vide */
;

construct_while:
    LOOP WHILE LPAREN { 
        $<entier>$ = qc; /* $4: Sauvegarde de la position de la condition */
    } condition RPAREN LBRACE {
        $<entier>$ = qc; /* $8: Sauvegarde de la position du BZ */
        quadr("BZ", "vide", $5, "vide"); /* Saut si condition fausse */
    } instructions RBRACE ENDLOOP SEMI {
        /* Fin de la boucle, remonter à la condition */
        sprintf(tmp, "%d", $<entier>4);
        quadr("BR", "vide", "vide", tmp);
        
        /* Mettre à jour le BZ pour pointer APRES la boucle */
        sprintf(tmp, "%d", qc);
        updateQuad($<entier>8, 3, tmp);
    }
;

construct_for:
    FOR T_IDF IN T_ENTIER {
        if (!est_declare($2)) {
            printf("Erreur Semantique, ligne %d, colonne %d : Variable de boucle '%s' non declaree\n", nb_ligne, col, $2);
        } else {
            /* 1. Initialisation : iterateur <- T_ENTIER (début) */
            char valDebut[20];
            strcpy(valDebut, $4);
            quadr("<-", valDebut, "vide", $2);
            strcpy(iter_for, $2); /* On sauvegarde le nom de la variable pour l'incrémentation */
        }
        $<entier>$ = qc; /* $5: Début de condition */
        
    } TO T_ENTIER LBRACE {
        /* 2. Condition : iterateur <= T_ENTIER (fin) */
        char valFin[20];
        strcpy(valFin, $7);
        sprintf(temp_nom, "t%d", nb_temp++);     
        quadr("<=", iter_for, valFin, temp_nom);
        
        $<entier>$ = qc; /* $9: Position du BZ */
        quadr("BZ", "vide", temp_nom, "vide"); /* Sortir si faux */
        
    } instructions RBRACE ENDFOR SEMI {
        /* 3. Incrémentation : iter_for <- iter_for + 1 */
        sprintf(temp_nom, "t%d", nb_temp++);
        quadr("+", iter_for, "1", temp_nom);
        quadr("<-", temp_nom, "vide", iter_for);
        
        /* 4. Remonter à l'évaluation de la condition */
        sprintf(tmp, "%d", $<entier>5);
        quadr("BR", "vide", "vide", tmp);
        
        /* 5. Mettre à jour le BZ pour sortir complètement de la boucle */
        sprintf(tmp, "%d", qc);
        updateQuad($<entier>9, 3, tmp);
    }
;
condition:
    expression EXPECT expression { sprintf(temp_nom, "t%d", nb_temp++); quadr("=", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | expression COMP_EQ expression { sprintf(temp_nom, "t%d", nb_temp++); quadr("==", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | expression COMP_NEQ expression { sprintf(temp_nom, "t%d", nb_temp++); quadr("!=", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | expression COMP_GT expression { sprintf(temp_nom, "t%d", nb_temp++); quadr(">", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | expression COMP_LT expression { sprintf(temp_nom, "t%d", nb_temp++); quadr("<", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | expression COMP_GE expression { sprintf(temp_nom, "t%d", nb_temp++); quadr(">=", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | expression COMP_LE expression { sprintf(temp_nom, "t%d", nb_temp++); quadr("<=", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | condition AND condition { sprintf(temp_nom, "t%d", nb_temp++); quadr("AND", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | condition OR condition { sprintf(temp_nom, "t%d", nb_temp++); quadr("OR", $1, $3, temp_nom); $$ = strdup(temp_nom); }
    | NON condition { sprintf(temp_nom, "t%d", nb_temp++); quadr("NOT", $2, "vide", temp_nom); $$ = strdup(temp_nom); }
    | LPAREN condition RPAREN { $$ = strdup($2); }
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