#ifndef QUAD_H
#define QUAD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Déclaration de la structure d'un quadruplet
typedef struct {
    char oper[100];
    char op1[100];
    char op2[100];
    char res[100];
} qdr;

qdr quad[1000];

// Compteur de quadruplet global
int qc = 0;

// Fonction d'ajout d'un quadruplet
void quadr(char opr[], char op1[], char op2[], char res[]) {
    strcpy(quad[qc].oper, opr);
    strcpy(quad[qc].op1, op1);
    strcpy(quad[qc].op2, op2);
    strcpy(quad[qc].res, res);
    qc++;
}

// Fonction de mise à jour d'un quadruplet (pour les branchements BZ, BR)
void updateQuad(int num_quad, int colon_quad, char val[]) {
    if (colon_quad == 0) strcpy(quad[num_quad].oper, val);
    else if (colon_quad == 1) strcpy(quad[num_quad].op1, val);
    else if (colon_quad == 2) strcpy(quad[num_quad].op2, val);
    else if (colon_quad == 3) strcpy(quad[num_quad].res, val);
}

// Fonction d'affichage des quadruplets
void afficher_qdr() {
    printf("\n=================== QUADRUPLETS ===================\n");
    int num = 0;
    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0) continue; // NE PAS AFFICHER LES QUADS VIDES (OPTIMISÉS)
        
        char op1_str[100], op2_str[100], res_str[100];
        strcpy(op1_str, strcmp(quad[i].op1, "vide") == 0 ? "" : quad[i].op1);
        strcpy(op2_str, strcmp(quad[i].op2, "vide") == 0 ? "" : quad[i].op2);
        strcpy(res_str, strcmp(quad[i].res, "vide") == 0 ? "" : quad[i].res);
        printf("%03d: ( %-4s , %-10s , %-10s , %-15s )\n", num++, quad[i].oper, op1_str, op2_str, res_str);
    }
}

#endif
