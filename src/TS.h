#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Taille de la table de hachage (un nombre premier réduit les collisions) */
#define HASH_SIZE 97 

/* ================================================================= */
/* STRUCTURES DE DONNEES                                             */
/* ================================================================= */

/* 1. Structure pour la Table de Hachage (IDFs et Constantes) */
/* Chaque case sera une liste chainee pour gerer les collisions */
typedef struct NodeTS {
    char name[256];
    char code[20];
    char type[20];   // integer, float
    char nature[20]; // VAR, CONST, TAB
    int taille;      // Taille pour les tableaux
    struct NodeTS* suivant; /* Pointeur pour le chainage (LIFO) */
} NodeTS;

/* 2. Structures pour les Mots cles et Separateurs (Restent en tableaux simples) */
typedef struct {
    int state;
    char nomEntite[256];
    char Code[20];
} TypeSM;

/* Declarations EXTERN pour eviter les erreurs "multiple definition" */
extern NodeTS* TS[HASH_SIZE]; 
extern TypeSM tabs[50], tabM[50];

/* ================================================================= */
/* PROTOTYPES DES FONCTIONS                                          */
/* ================================================================= */
int hash_function(char* name);
void initialization();
void inserer(char entite[], char code[], int y);
void rechercher(char entite[], char code[], int y);
void afficher();
int est_declare(char entite[]);
void inserer_type_nature(char entite[], char type[], char nature[], int taille);
int est_constante(char entite[]);

char* get_nature(char entite[]);

#endif
