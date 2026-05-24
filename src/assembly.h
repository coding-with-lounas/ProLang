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

    fprintf(file, "    \n");
    fprintf(file, "    ; --- Chaines de caracteres pour simuler printf ---\n");
    fprintf(file, "    msg_bx DB \"Entrez la valeur de x : $\"\n");
    fprintf(file, "    msg_x DB \"x = $\"\n");
    fprintf(file, "    msg_somme DB \"somme = $\"\n");
    fprintf(file, "    msg_moyenne DB \"moyenne = $\"\n");
    
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
            fprintf(file, "    ; scanf(\"%%d\", &%s)\n", quad[i].res);
            if (strcmp(quad[i].res, "x") == 0) {
                fprintf(file, "    MOV AH, 09H\n");
                fprintf(file, "    LEA DX, msg_bx\n");
                fprintf(file, "    INT 21H\n");
            }
            fprintf(file, "    CALL READ_INT\n");
            fprintf(file, "    MOV %s, CX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "OUT") == 0) {
            fprintf(file, "    ; printf(\"%s = %%d\\n\", %s)\n", quad[i].res, quad[i].res);
            if (strcmp(quad[i].res, "x") == 0) {
                fprintf(file, "    MOV AH, 09H\n");
                fprintf(file, "    LEA DX, msg_x\n");
                fprintf(file, "    INT 21H\n");
            } else if (strcmp(quad[i].res, "somme") == 0) {
                fprintf(file, "    MOV AH, 09H\n");
                fprintf(file, "    LEA DX, msg_somme\n");
                fprintf(file, "    INT 21H\n");
            } else if (strcmp(quad[i].res, "moyenne") == 0) {
                fprintf(file, "    MOV AH, 09H\n");
                fprintf(file, "    LEA DX, msg_moyenne\n");
                fprintf(file, "    INT 21H\n");
            }
            fprintf(file, "    MOV AX, %s\n", quad[i].res);
            fprintf(file, "    CALL PRINT_INT\n");
        }
    }

    /* Étiquette de fin */
    fprintf(file, "etiq_%d:\n", qc);
    fprintf(file, "    MOV AH, 4CH\n");
    fprintf(file, "    INT 21H\n");
    
    fprintf(file, "\n; ====================================================\n");
    fprintf(file, "; Sous-programmes d'entrees / sorties\n");
    fprintf(file, "; ====================================================\n\n");
    
    fprintf(file, "; Procedure pour lire un entier clavier (retour dans CX)\n");
    fprintf(file, "READ_INT PROC\n");
    fprintf(file, "    PUSH AX\n");
    fprintf(file, "    PUSH BX\n");
    fprintf(file, "    PUSH DX\n");
    fprintf(file, "    XOR CX, CX\n");
    fprintf(file, "read_loop:\n");
    fprintf(file, "    MOV AH, 01H\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    CMP AL, 13 ; Entree\n");
    fprintf(file, "    JE read_done\n");
    fprintf(file, "    CMP AL, '0'\n");
    fprintf(file, "    JB read_loop\n");
    fprintf(file, "    CMP AL, '9'\n");
    fprintf(file, "    JA read_loop\n");
    fprintf(file, "    SUB AL, '0'\n");
    fprintf(file, "    XOR AH, AH\n");
    fprintf(file, "    PUSH AX\n");
    fprintf(file, "    MOV AX, CX\n");
    fprintf(file, "    MOV BX, 10\n");
    fprintf(file, "    MUL BX\n");
    fprintf(file, "    POP BX\n");
    fprintf(file, "    ADD AX, BX\n");
    fprintf(file, "    MOV CX, AX\n");
    fprintf(file, "    JMP read_loop\n");
    fprintf(file, "read_done:\n");
    fprintf(file, "    ; Retour a la ligne\n");
    fprintf(file, "    MOV AH, 02H\n");
    fprintf(file, "    MOV DL, 13\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    MOV DL, 10\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    POP DX\n");
    fprintf(file, "    POP BX\n");
    fprintf(file, "    POP AX\n");
    fprintf(file, "    RET\n");
    fprintf(file, "READ_INT ENDP\n\n");
    
    fprintf(file, "; Procedure pour afficher un entier (valeur dans AX)\n");
    fprintf(file, "PRINT_INT PROC\n");
    fprintf(file, "    PUSH AX\n");
    fprintf(file, "    PUSH BX\n");
    fprintf(file, "    PUSH CX\n");
    fprintf(file, "    PUSH DX\n");
    fprintf(file, "    XOR CX, CX\n");
    fprintf(file, "    MOV BX, 10\n");
    fprintf(file, "    CMP AX, 0\n");
    fprintf(file, "    JGE start_print\n");
    fprintf(file, "    PUSH AX\n");
    fprintf(file, "    MOV AH, 02H\n");
    fprintf(file, "    MOV DL, '-'\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    POP AX\n");
    fprintf(file, "    NEG AX\n");
    fprintf(file, "start_print:\n");
    fprintf(file, "print_loop1:\n");
    fprintf(file, "    XOR DX, DX\n");
    fprintf(file, "    DIV BX\n");
    fprintf(file, "    PUSH DX\n");
    fprintf(file, "    INC CX\n");
    fprintf(file, "    CMP AX, 0\n");
    fprintf(file, "    JNE print_loop1\n");
    fprintf(file, "print_loop2:\n");
    fprintf(file, "    POP DX\n");
    fprintf(file, "    ADD DL, '0'\n");
    fprintf(file, "    MOV AH, 02H\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    LOOP print_loop2\n");
    fprintf(file, "    ; Retour a la ligne\n");
    fprintf(file, "    MOV AH, 02H\n");
    fprintf(file, "    MOV DL, 13\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    MOV DL, 10\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "    POP DX\n");
    fprintf(file, "    POP CX\n");
    fprintf(file, "    POP BX\n");
    fprintf(file, "    POP AX\n");
    fprintf(file, "    RET\n");
    fprintf(file, "PRINT_INT ENDP\n\n");
    
    fprintf(file, "CODE ENDS\n");
    fprintf(file, "END MAIN\n");

    fclose(file);
    printf(">> Code machine genere dans le fichier '%s' !\n", filename);
}

#endif
