#include "TS.h"

// Allocation globale mémoire de vos 3 tables
TypeTS TS[200];
TypeSM tabs[50], tabM[50];

// Fonction d'initialisation : met l'état de toutes les cases à 0
void initialization() {
    int i;
    for (i = 0; i < 200; i++) TS[i].state = 0;
    for (i = 0; i < 50; i++) {
        tabs[i].state = 0;
        tabM[i].state = 0;
    }
}

// Fonction d'insertion
void inserer(char entite[], char code[], char type[], char val[], int i, int y) {
    switch (y) {
        case 1: /* Insertion dans la table des IDF et CONST */
            TS[i].state = 1;
            strcpy(TS[i].name, entite);
            strcpy(TS[i].code, code);
            strcpy(TS[i].type, type);
            strcpy(TS[i].val, val);
            break;
        case 2: /* Insertion dans la table des mots clés */
            tabM[i].state = 1;
            strcpy(tabM[i].nomEntite, entite);
            strcpy(tabM[i].Code, code);
            break;
        case 3: /* Insertion dans la table des séparateurs */
            tabs[i].state = 1;
            strcpy(tabs[i].nomEntite, entite);
            strcpy(tabs[i].Code, code);
            break;
    }
}

// Fonction de recherche et appel à l'insertion si non trouvé
void rechercher(char entite[], char code[], char type[], char val[], int y) {
    int i;
    switch(y) {
        case 1: /* Recherche dans la table des IDFs et Constantes */
            for (i = 0; ((i < 200) && (TS[i].state == 1) && (strcmp(entite, TS[i].name) != 0)); i++);
            if(i < 200 && strcmp(entite, TS[i].name) != 0) {
                inserer(entite, code, type, val, i, 1);
            }
            break;

        case 2: /* Recherche dans la table des mots clés */
            for (i = 0; ((i < 50) && (tabM[i].state == 1) && (strcmp(entite, tabM[i].nomEntite) != 0)); i++);
            if(i < 50 && strcmp(entite, tabM[i].nomEntite) != 0) {
                inserer(entite, code, type, val, i, 2);
            }
            break;

        case 3: /* Recherche dans la table des séparateurs */
            for (i = 0; ((i < 50) && (tabs[i].state == 1) && (strcmp(entite, tabs[i].nomEntite) != 0)); i++);
            if(i < 50 && strcmp(entite, tabs[i].nomEntite) != 0) {
                inserer(entite, code, type, val, i, 3);
            }
            break;
    }
}

// Fonction d'affichage des 3 tables
void afficher() {
    int i;
    printf("\n/******************** Table des symboles IDF et Constantes ********************/\n");
    printf("\t| %-15s | %-12s | %-12s | %-12s \n", "Nom_Entite", "Code_Entite", "Type_Entite", "Val_Entite");
    printf("\t-----------------------------------------------------------------------------\n");
    for(i = 0; i < 200; i++) {
        if(TS[i].state == 1) {
            printf("\t| %-15s | %-12s | %-12s | %-12s \n", TS[i].name, TS[i].code, TS[i].type, TS[i].val);
        }
    }

    printf("\n/******************** Table des symboles Mots cles ****************************/\n");
    printf("\t| %-15s | %-12s |\n", "NomEntite", "CodeEntite");
    printf("\t----------------------------------\n");
    for(i = 0; i < 50; i++) {
        if(tabM[i].state == 1) {
            printf("\t| %-15s | %-12s |\n", tabM[i].nomEntite, tabM[i].Code);
        }
    }

    printf("\n/******************** Table des symboles Separateurs **************************/\n");
    printf("\t| %-15s | %-12s |\n", "NomEntite", "CodeEntite");
    printf("\t----------------------------------\n");
    for(i = 0; i < 50; i++) {
        if(tabs[i].state == 1) {
            printf("\t| %-15s | %-12s |\n", tabs[i].nomEntite, tabs[i].Code);
        }
    }
}