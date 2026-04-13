#ifndef TS_H
#define TS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Structure pour la table des IDFs et Constantes
typedef struct {
    int state;
    char name[30];
    char code[20];
    char type[20];
    char val[30];
} TypeTS;

// 2. Structure pour la table des Mots clés et Séparateurs
typedef struct {
    int state;
    char nomEntite[30];
    char Code[20];
} TypeSM;

// Déclaration EXTERN des tableaux (partagés dans tout le projet)
extern TypeTS TS[200];
extern TypeSM tabs[50], tabM[50];

// Prototypes des fonctions
void initialization();
void inserer(char entite[], char code[], char type[], char val[], int i, int y);
void rechercher(char entite[], char code[], char type[], char val[], int y);
void afficher();

#endif