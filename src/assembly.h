#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "quad.h"
#include "TS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------
 * Helpers
 * --------------------------------------------------------------- */

/* Tronque la partie décimale d'un float littéral (ex: "2.0" -> "2") */
static void trunc_float(const char* src, char* dst) {
    strcpy(dst, src);
    char* dot = strchr(dst, '.');
    if (dot) *dot = '\0';
}

/* Retourne 1 si la chaîne est un littéral entier (chiffres uniquement) */
static int is_literal(const char* s) {
    if (!s || !*s) return 0;
    const char* p = s;
    if (*p == '-') p++;          /* signe négatif optionnel */
    if (!*p) return 0;
    while (*p) { if (*p < '0' || *p > '9') return 0; p++; }
    return 1;
}

/* Émet le code pour charger op dans AX.
   Si op est de la forme Tab[idx], utilise BX comme registre d'index.
   Tronque les flottants littéraux. */
static void emit_load_ax(FILE* f, const char* op) {
    char buf[100];
    trunc_float(op, buf);

    if (strchr(buf, '[') != NULL) {
        /* Tableau : Tab[idx] */
        char tab_name[50], index[50];
        sscanf(buf, "%[^[][%[^]]", tab_name, index);
        /* Charger l'index dans BX */
        if (is_literal(index)) {
            fprintf(f, "    MOV BX, %s\n", index);
        } else {
            fprintf(f, "    MOV BX, %s\n", index);
        }
        fprintf(f, "    SHL BX, 1\n");          /* BX *= 2 (taille word) */
        fprintf(f, "    MOV AX, %s[BX]\n", tab_name);
    } else {
        /* Variable simple ou littéral */
        fprintf(f, "    MOV AX, %s\n", buf);
    }
}

/* Émet le code pour stocker AX dans dst (variable simple ou Tab[idx]).
   Utilise SI comme registre d'index pour ne pas écraser BX. */
static void emit_store_ax(FILE* f, const char* dst) {
    char buf[100];
    strcpy(buf, dst);

    if (strchr(buf, '[') != NULL) {
        /* Tableau : Tab[idx] */
        char tab_name[50], index[50];
        sscanf(buf, "%[^[][%[^]]", tab_name, index);
        fprintf(f, "    PUSH AX\n");             /* sauvegarder AX */
        if (is_literal(index)) {
            fprintf(f, "    MOV SI, %s\n", index);
        } else {
            fprintf(f, "    MOV SI, %s\n", index);
        }
        fprintf(f, "    SHL SI, 1\n");           /* SI *= 2 */
        fprintf(f, "    POP AX\n");
        fprintf(f, "    MOV %s[SI], AX\n", tab_name);
    } else {
        /* Variable simple */
        fprintf(f, "    MOV %s, AX\n", buf);
    }
}

/* ---------------------------------------------------------------
 * Générateur principal
 * --------------------------------------------------------------- */
void generer_assembleur(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }

    /* ---- Segment de données ---- */
    fprintf(file, "TITLE  Code_Assembleur\n");
    fprintf(file, "DATA SEGMENT\n");

    /* Variables et constantes de la table des symboles */
    for (int i = 0; i < HASH_SIZE; i++) {
        NodeTS* curr = TS[i];
        while (curr != NULL) {
            if (strcmp(curr->nature, "VAR") == 0 || strcmp(curr->nature, "CONST") == 0) {
                fprintf(file, "    %s DW ?\n", curr->name);
            } else if (strcmp(curr->nature, "TAB") == 0) {
                fprintf(file, "    %s DW %d DUP(?)\n", curr->name, curr->taille);
            }
            curr = curr->suivant;
        }
    }

    /* Temporaires générés par le compilateur */
    char temp_list[1000][20];
    int nb_temps = 0;
    for (int i = 0; i < qc; i++) {
        if (quad[i].res[0] == 't' && quad[i].res[1] >= '0' && quad[i].res[1] <= '9') {
            int exists = 0;
            for (int j = 0; j < nb_temps; j++) {
                if (strcmp(temp_list[j], quad[i].res) == 0) { exists = 1; break; }
            }
            if (!exists) {
                strcpy(temp_list[nb_temps++], quad[i].res);
                fprintf(file, "    %s DW ?\n", quad[i].res);
            }
        }
    }

    fprintf(file, "DATA ENDS\n\n");

    /* ---- Segment de code ---- */
    fprintf(file, "CODE SEGMENT\n");
    fprintf(file, "ASSUME CS:CODE, DS:DATA\n");
    fprintf(file, "MAIN:\n");
    fprintf(file, "    MOV AX, DATA\n");
    fprintf(file, "    MOV DS, AX\n\n");

    char op1_buf[100], op2_buf[100];

    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0) continue;

        fprintf(file, "etiq_%d:\n", i);

        /* ---- AFFECTATION SIMPLE : res <- op1 ---- */
        if (strcmp(quad[i].oper, "<-") == 0) {
            trunc_float(quad[i].op1, op1_buf);
            emit_load_ax(file, op1_buf);
            emit_store_ax(file, quad[i].res);

        /* ---- LECTURE TABLEAU : res = Tab[idx] ---- */
        } else if (strcmp(quad[i].oper, "=") == 0) {
            emit_load_ax(file, quad[i].op1);
            emit_store_ax(file, quad[i].res);

        /* ---- ADDITION ---- */
        } else if (strcmp(quad[i].oper, "+") == 0) {
            trunc_float(quad[i].op1, op1_buf);
            trunc_float(quad[i].op2, op2_buf);
            emit_load_ax(file, op1_buf);
            /* op2 peut aussi être un tableau */
            if (strchr(op2_buf, '[') != NULL) {
                char tab2[50], idx2[50];
                sscanf(op2_buf, "%[^[][%[^]]", tab2, idx2);
                fprintf(file, "    MOV BX, %s\n", idx2);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    ADD AX, %s[BX]\n", tab2);
            } else {
                fprintf(file, "    ADD AX, %s\n", op2_buf);
            }
            emit_store_ax(file, quad[i].res);

        /* ---- SOUSTRACTION ---- */
        } else if (strcmp(quad[i].oper, "-") == 0) {
            trunc_float(quad[i].op1, op1_buf);
            trunc_float(quad[i].op2, op2_buf);
            emit_load_ax(file, op1_buf);
            if (strchr(op2_buf, '[') != NULL) {
                char tab2[50], idx2[50];
                sscanf(op2_buf, "%[^[][%[^]]", tab2, idx2);
                fprintf(file, "    MOV BX, %s\n", idx2);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    SUB AX, %s[BX]\n", tab2);
            } else {
                fprintf(file, "    SUB AX, %s\n", op2_buf);
            }
            emit_store_ax(file, quad[i].res);

        /* ---- MULTIPLICATION ---- */
        } else if (strcmp(quad[i].oper, "*") == 0) {
            trunc_float(quad[i].op1, op1_buf);
            trunc_float(quad[i].op2, op2_buf);
            emit_load_ax(file, op1_buf);
            if (strchr(op2_buf, '[') != NULL) {
                char tab2[50], idx2[50];
                sscanf(op2_buf, "%[^[][%[^]]", tab2, idx2);
                fprintf(file, "    MOV BX, %s\n", idx2);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    MOV BX, %s[BX]\n", tab2);
            } else {
                fprintf(file, "    MOV BX, %s\n", op2_buf);
            }
            fprintf(file, "    MUL BX\n");
            emit_store_ax(file, quad[i].res);

        /* ---- DIVISION ---- */
        } else if (strcmp(quad[i].oper, "/") == 0) {
            trunc_float(quad[i].op1, op1_buf);
            trunc_float(quad[i].op2, op2_buf);
            emit_load_ax(file, op1_buf);
            fprintf(file, "    XOR DX, DX\n");
            if (strchr(op2_buf, '[') != NULL) {
                char tab2[50], idx2[50];
                sscanf(op2_buf, "%[^[][%[^]]", tab2, idx2);
                fprintf(file, "    MOV BX, %s\n", idx2);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    MOV BX, %s[BX]\n", tab2);
            } else {
                fprintf(file, "    MOV BX, %s\n", op2_buf);
            }
            fprintf(file, "    DIV BX\n");
            emit_store_ax(file, quad[i].res);

        /* ---- SAUT INCONDITIONNEL ---- */
        } else if (strcmp(quad[i].oper, "BR") == 0) {
            fprintf(file, "    JMP etiq_%s\n", quad[i].res);

        /* ---- SAUT SI ZERO (BZ) ---- */
        } else if (strcmp(quad[i].oper, "BZ") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op2);
            fprintf(file, "    CMP AX, 0\n");
            fprintf(file, "    JNE skip_jmp_%d\n", i);
            fprintf(file, "    JMP etiq_%s\n", quad[i].res);
            fprintf(file, "skip_jmp_%d:\n", i);

        /* ---- SAUT SI NON-ZERO (BNZ) ---- */
        } else if (strcmp(quad[i].oper, "BNZ") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op2);
            fprintf(file, "    CMP AX, 0\n");
            fprintf(file, "    JE skip_jmp_%d\n", i);
            fprintf(file, "    JMP etiq_%s\n", quad[i].res);
            fprintf(file, "skip_jmp_%d:\n", i);

        /* ---- COMPARAISONS ---- */
        } else if (strcmp(quad[i].oper, "==") == 0 || strcmp(quad[i].oper, "<=") == 0 ||
                   strcmp(quad[i].oper, "<")  == 0 || strcmp(quad[i].oper, ">")  == 0 ||
                   strcmp(quad[i].oper, ">=") == 0 || strcmp(quad[i].oper, "!=") == 0) {
            trunc_float(quad[i].op1, op1_buf);
            trunc_float(quad[i].op2, op2_buf);
            emit_load_ax(file, op1_buf);
            /* op2 peut être un tableau */
            if (strchr(op2_buf, '[') != NULL) {
                char tab2[50], idx2[50];
                sscanf(op2_buf, "%[^[][%[^]]", tab2, idx2);
                fprintf(file, "    MOV BX, %s\n", idx2);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    CMP AX, %s[BX]\n", tab2);
            } else {
                fprintf(file, "    CMP AX, %s\n", op2_buf);
            }
            /* Jump conditionnel */
            if      (strcmp(quad[i].oper, "==") == 0) fprintf(file, "    JE  true_%d\n", i);
            else if (strcmp(quad[i].oper, "<=") == 0) fprintf(file, "    JLE true_%d\n", i);
            else if (strcmp(quad[i].oper, "<")  == 0) fprintf(file, "    JL  true_%d\n", i);
            else if (strcmp(quad[i].oper, ">")  == 0) fprintf(file, "    JG  true_%d\n", i);
            else if (strcmp(quad[i].oper, ">=") == 0) fprintf(file, "    JGE true_%d\n", i);
            else if (strcmp(quad[i].oper, "!=") == 0) fprintf(file, "    JNE true_%d\n", i);
            /* Faux (0) */
            fprintf(file, "    MOV AX, 0\n");
            emit_store_ax(file, quad[i].res);
            fprintf(file, "    JMP end_cmp_%d\n", i);
            /* Vrai (1) */
            fprintf(file, "true_%d:\n", i);
            fprintf(file, "    MOV AX, 1\n");
            emit_store_ax(file, quad[i].res);
            fprintf(file, "end_cmp_%d:\n", i);

        /* ---- AND LOGIQUE ---- */
        } else if (strcmp(quad[i].oper, "AND") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op1);
            fprintf(file, "    AND AX, %s\n", quad[i].op2);
            emit_store_ax(file, quad[i].res);

        /* ---- OR LOGIQUE ---- */
        } else if (strcmp(quad[i].oper, "OR") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op1);
            fprintf(file, "    OR AX, %s\n", quad[i].op2);
            emit_store_ax(file, quad[i].res);

        /* ---- NOT LOGIQUE ---- */
        } else if (strcmp(quad[i].oper, "NOT") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op1);
            fprintf(file, "    XOR AX, 1\n");
            emit_store_ax(file, quad[i].res);

        /* ---- ENTREE / SORTIE ---- */
        } else if (strcmp(quad[i].oper, "IN") == 0) {
            fprintf(file, "    ; IN : lecture de %s\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "OUT") == 0) {
            fprintf(file, "    ; OUT : ecriture de %s\n", quad[i].res);
        }
    }

    /* Étiquette de fin */
    fprintf(file, "etiq_%d:\n", qc);
    fprintf(file, "    MOV AH, 4CH\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "CODE ENDS\n");
    fprintf(file, "END MAIN\n");

    fclose(file);
    printf(">> Code machine genere dans le fichier '%s' !\n", filename);
}

#endif
