#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "quad.h"
#include "TS.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern qdr quad[1000];
extern int qc;

void extraire_tableau(char* operande, char* nom_tab, char* index) {
    char* start = strchr(operande, '[');
    char* end = strchr(operande, ']');
    if (start && end) {
        strncpy(nom_tab, operande, start - operande);
        nom_tab[start - operande] = '\0';
        strncpy(index, start + 1, end - start - 1);
        index[end - start - 1] = '\0';
    } else {
        strcpy(nom_tab, operande);
        strcpy(index, "");
    }
}

int est_nombre(char* str) {
    if (!str || strlen(str) == 0) return 0;
    int i = 0;
    if (str[0] == '-' || str[0] == '+') i++;
    for (; str[i]; i++) {
        if (!isdigit(str[i]) && str[i] != '.') return 0;
    }
    return 1;
}

void generer_assembleur(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Erreur lors de la creation du fichier assembleur.\n");
        return;
    }

    fprintf(f, "TITLE code.asm\n");
    fprintf(f, "PILE SEGMENT STACK\n");
    fprintf(f, "    DW 100 DUP(?)\n");
    fprintf(f, "base_pile EQU $\n");
    fprintf(f, "PILE ENDS\n\n");

    fprintf(f, "DATA SEGMENT\n");
    // Extraire les variables de la table des symboles
    for (int i = 0; i < HASH_SIZE; i++) {
        NodeTS* courant = TS[i];
        while (courant != NULL) {
            if (strcmp(courant->nature, "VAR") == 0 || strcmp(courant->nature, "CONST") == 0) {
                fprintf(f, "    %s DW ?\n", courant->name);
            } else if (strcmp(courant->nature, "TAB") == 0) {
                fprintf(f, "    %s DW %d DUP(?)\n", courant->name, courant->taille);
            }
            courant = courant->suivant;
        }
    }

    // Extraire les temporaires (t1, t2...) et les variables de chaines generes
    char temporaires_declarer[1000][100];
    int nb_temps = 0;
    
    // Pour OUT on a besoin d'afficher des chaines
    // On va generer des variables pour les chaines
    int str_count = 0;
    
    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0) continue;
        
        // Verifier res pour temporaires
        if (quad[i].res[0] == 't' || quad[i].res[0] == 'T') {
            int trouve = 0;
            for (int j = 0; j < nb_temps; j++) {
                if (strcmp(temporaires_declarer[j], quad[i].res) == 0) {
                    trouve = 1; break;
                }
            }
            if (!trouve && strchr(quad[i].res, '[') == NULL) { // Pas un tableau
                strcpy(temporaires_declarer[nb_temps++], quad[i].res);
                fprintf(f, "    %s DW ?\n", quad[i].res);
            }
        }
        
        // Verifier OUT avec chaines
        if (strcmp(quad[i].oper, "OUT") == 0 && quad[i].op1[0] == '"') {
            fprintf(f, "    msg%d DB %s, '$'\n", str_count++, quad[i].op1);
        }
    }
    
    // Variables pour l'affichage (I/O)
    fprintf(f, "    newline DB 10, 13, '$'\n");
    fprintf(f, "DATA ENDS\n\n");

    fprintf(f, "CODE SEGMENT\n");
    fprintf(f, "MAIN:\n");
    fprintf(f, "    ASSUME CS:CODE, DS:DATA, SS:PILE\n");
    fprintf(f, "    MOV AX, DATA\n");
    fprintf(f, "    MOV DS, AX\n");
    fprintf(f, "    MOV AX, PILE\n");
    fprintf(f, "    MOV SS, AX\n");
    fprintf(f, "    MOV SP, base_pile\n\n");

    int str_index = 0;
    int bool_label = 0;

    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0) continue;
        
        fprintf(f, "QUAD_%d:\n", i);
        
        if (strcmp(quad[i].oper, "<-") == 0 || strcmp(quad[i].oper, "=") == 0) {
            char op1_tab[50], op1_idx[50];
            char res_tab[50], res_idx[50];
            extraire_tableau(quad[i].op1, op1_tab, op1_idx);
            extraire_tableau(quad[i].res, res_tab, res_idx);
            
            // Source :
            if (strlen(op1_idx) > 0) { // Lecture de tableau: res = op1_tab[op1_idx]
                if (est_nombre(op1_idx)) {
                    fprintf(f, "    MOV SI, %s\n", op1_idx);
                } else {
                    fprintf(f, "    MOV SI, %s\n", op1_idx);
                }
                fprintf(f, "    ADD SI, SI\n");
                fprintf(f, "    MOV AX, %s[SI]\n", op1_tab);
            } else { // Lecture simple
                if (est_nombre(op1_tab)) {
                    // C'est potentiellement un float, on prend l'entier pour simplifier
                    int val = atoi(op1_tab);
                    fprintf(f, "    MOV AX, %d\n", val);
                } else {
                    fprintf(f, "    MOV AX, %s\n", op1_tab);
                }
            }
            
            // Destination :
            if (strlen(res_idx) > 0) { // Ecriture de tableau
                if (est_nombre(res_idx)) {
                    fprintf(f, "    MOV DI, %s\n", res_idx);
                } else {
                    fprintf(f, "    MOV DI, %s\n", res_idx);
                }
                fprintf(f, "    ADD DI, DI\n");
                fprintf(f, "    MOV %s[DI], AX\n", res_tab);
            } else { // Ecriture simple
                fprintf(f, "    MOV %s, AX\n", res_tab);
            }
        }
        else if (strcmp(quad[i].oper, "+") == 0 || strcmp(quad[i].oper, "-") == 0) {
            if (est_nombre(quad[i].op1)) fprintf(f, "    MOV AX, %d\n", atoi(quad[i].op1));
            else fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            
            if (strcmp(quad[i].oper, "+") == 0) {
                if (est_nombre(quad[i].op2)) fprintf(f, "    ADD AX, %d\n", atoi(quad[i].op2));
                else fprintf(f, "    ADD AX, %s\n", quad[i].op2);
            } else {
                if (est_nombre(quad[i].op2)) fprintf(f, "    SUB AX, %d\n", atoi(quad[i].op2));
                else fprintf(f, "    SUB AX, %s\n", quad[i].op2);
            }
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "*") == 0) {
            if (est_nombre(quad[i].op1)) fprintf(f, "    MOV AX, %d\n", atoi(quad[i].op1));
            else fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            
            if (est_nombre(quad[i].op2)) {
                fprintf(f, "    MOV BX, %d\n", atoi(quad[i].op2));
                fprintf(f, "    IMUL BX\n");
            } else {
                fprintf(f, "    IMUL %s\n", quad[i].op2);
            }
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "/") == 0) {
            if (est_nombre(quad[i].op1)) fprintf(f, "    MOV AX, %d\n", atoi(quad[i].op1));
            else fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            fprintf(f, "    CWD\n");
            if (est_nombre(quad[i].op2)) {
                fprintf(f, "    MOV BX, %d\n", atoi(quad[i].op2));
                fprintf(f, "    IDIV BX\n");
            } else {
                fprintf(f, "    IDIV %s\n", quad[i].op2);
            }
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "<") == 0 || strcmp(quad[i].oper, ">") == 0 ||
                 strcmp(quad[i].oper, "<=") == 0 || strcmp(quad[i].oper, ">=") == 0 ||
                 strcmp(quad[i].oper, "==") == 0 || strcmp(quad[i].oper, "!=") == 0) {
            
            if (est_nombre(quad[i].op1)) fprintf(f, "    MOV AX, %d\n", atoi(quad[i].op1));
            else fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            
            if (est_nombre(quad[i].op2)) fprintf(f, "    CMP AX, %d\n", atoi(quad[i].op2));
            else fprintf(f, "    CMP AX, %s\n", quad[i].op2);
            
            fprintf(f, "    MOV AX, 1\n");
            if (strcmp(quad[i].oper, "<") == 0) fprintf(f, "    JL TRUE_%d\n", bool_label);
            else if (strcmp(quad[i].oper, ">") == 0) fprintf(f, "    JG TRUE_%d\n", bool_label);
            else if (strcmp(quad[i].oper, "<=") == 0) fprintf(f, "    JLE TRUE_%d\n", bool_label);
            else if (strcmp(quad[i].oper, ">=") == 0) fprintf(f, "    JGE TRUE_%d\n", bool_label);
            else if (strcmp(quad[i].oper, "==") == 0) fprintf(f, "    JE TRUE_%d\n", bool_label);
            else if (strcmp(quad[i].oper, "!=") == 0) fprintf(f, "    JNE TRUE_%d\n", bool_label);
            
            fprintf(f, "    MOV AX, 0\n");
            fprintf(f, "TRUE_%d:\n", bool_label++);
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "AND") == 0) {
            fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            fprintf(f, "    AND AX, %s\n", quad[i].op2);
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "OR") == 0) {
            fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            fprintf(f, "    OR AX, %s\n", quad[i].op2);
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "NOT") == 0) {
            fprintf(f, "    MOV AX, %s\n", quad[i].op1);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JE IS_ZERO_%d\n", bool_label);
            fprintf(f, "    MOV AX, 0\n");
            fprintf(f, "    JMP DONE_NOT_%d\n", bool_label);
            fprintf(f, "IS_ZERO_%d:\n", bool_label);
            fprintf(f, "    MOV AX, 1\n");
            fprintf(f, "DONE_NOT_%d:\n", bool_label);
            fprintf(f, "    MOV %s, AX\n", quad[i].res);
            bool_label++;
        }
        else if (strcmp(quad[i].oper, "BR") == 0) {
            fprintf(f, "    JMP QUAD_%s\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "BZ") == 0) {
            fprintf(f, "    MOV AX, %s\n", quad[i].op2); // Op2 contient la condition pour BZ dans notre compilo
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JE QUAD_%s\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "BNZ") == 0) {
            fprintf(f, "    MOV AX, %s\n", quad[i].op2);
            fprintf(f, "    CMP AX, 0\n");
            fprintf(f, "    JNE QUAD_%s\n", quad[i].res);
        }
        else if (strcmp(quad[i].oper, "OUT") == 0) {
            if (quad[i].op1[0] == '"') {
                fprintf(f, "    MOV DX, OFFSET msg%d\n", str_index++);
                fprintf(f, "    MOV AH, 09h\n");
                fprintf(f, "    INT 21h\n");
            }
            if (strcmp(quad[i].res, "vide") != 0 && strcmp(quad[i].res, "") != 0) {
                // Afficher la variable (routine simple d'affichage)
                // En realite on devrait avoir une routine PRINT_NUM, on met un commentaire
                fprintf(f, "    ; TODO: Print value of %s (omitted for brevity)\n", quad[i].res);
            }
            // Afficher Nouvelle ligne
            fprintf(f, "    MOV DX, OFFSET newline\n");
            fprintf(f, "    MOV AH, 09h\n");
            fprintf(f, "    INT 21h\n");
        }
    }
    
    // Label de fin
    fprintf(f, "QUAD_%d:\n", qc);

    fprintf(f, "    MOV AH, 4Ch\n");
    fprintf(f, "    INT 21h\n");
    fprintf(f, "CODE ENDS\n");
    fprintf(f, "END MAIN\n");

    fclose(f);
    printf("\n>> Code machine genere dans le fichier '%s' !\n", filename);
}

#endif
