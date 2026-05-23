#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "quad.h"
#include "TS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generer_assembleur(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier %s\n", filename);
        return;
    }

    fprintf(file, "TITLE  Code_Assembleur\n");
    fprintf(file, "DATA SEGMENT\n");

    // Déclaration des variables à partir de la table des symboles
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
    
    // Déclaration des temporaires (t1, t2...)
    char temp_list[1000][20];
    int nb_temps = 0;
    for(int i = 0; i < qc; i++) {
        if(quad[i].res[0] == 't' && quad[i].res[1] >= '0' && quad[i].res[1] <= '9') {
            int exists = 0;
            for(int j = 0; j < nb_temps; j++) {
                if(strcmp(temp_list[j], quad[i].res) == 0) {
                    exists = 1; break;
                }
            }
            if(!exists) {
                strcpy(temp_list[nb_temps++], quad[i].res);
                fprintf(file, "    %s DW ?\n", quad[i].res);
            }
        }
    }

    fprintf(file, "DATA ENDS\n\n");
    fprintf(file, "CODE SEGMENT\n");
    fprintf(file, "ASSUME CS:CODE, DS:DATA\n");
    fprintf(file, "MAIN:\n");
    fprintf(file, "    MOV AX, DATA\n");
    fprintf(file, "    MOV DS, AX\n\n");

    // Helper buffer for float truncation
    char op1_buf[50], op2_buf[50];

    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0) continue;
        
        fprintf(file, "etiq_%d:\n", i);
        
        if (strcmp(quad[i].oper, "<-") == 0) {
            strcpy(op1_buf, quad[i].op1);
            if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
            
            if (strchr(quad[i].res, '[') != NULL) {
                char tab_name[50], index[50];
                sscanf(quad[i].res, "%[^[][%[^]]", tab_name, index);
                fprintf(file, "    MOV BX, %s\n", index);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    MOV AX, %s\n", op1_buf);
                fprintf(file, "    MOV %s[BX], AX\n", tab_name);
            } else {
                fprintf(file, "    MOV AX, %s\n", op1_buf);
                fprintf(file, "    MOV %s, AX\n", quad[i].res);
            }
        } else if (strcmp(quad[i].oper, "=") == 0) {
            if (strchr(quad[i].op1, '[') != NULL) {
                char tab_name[50], index[50];
                sscanf(quad[i].op1, "%[^[][%[^]]", tab_name, index);
                fprintf(file, "    MOV BX, %s\n", index);
                fprintf(file, "    SHL BX, 1\n");
                fprintf(file, "    MOV AX, %s[BX]\n", tab_name);
                fprintf(file, "    MOV %s, AX\n", quad[i].res);
            } else {
                strcpy(op1_buf, quad[i].op1);
                if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
                fprintf(file, "    MOV AX, %s\n", op1_buf);
                fprintf(file, "    MOV %s, AX\n", quad[i].res);
            }
        } else if (strcmp(quad[i].oper, "+") == 0) {
            strcpy(op1_buf, quad[i].op1); if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
            strcpy(op2_buf, quad[i].op2); if (strchr(op2_buf, '.') != NULL) *strchr(op2_buf, '.') = '\0';
            fprintf(file, "    MOV AX, %s\n", op1_buf);
            fprintf(file, "    ADD AX, %s\n", op2_buf);
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "-") == 0) {
            strcpy(op1_buf, quad[i].op1); if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
            strcpy(op2_buf, quad[i].op2); if (strchr(op2_buf, '.') != NULL) *strchr(op2_buf, '.') = '\0';
            fprintf(file, "    MOV AX, %s\n", op1_buf);
            fprintf(file, "    SUB AX, %s\n", op2_buf);
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "*") == 0) {
            strcpy(op1_buf, quad[i].op1); if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
            strcpy(op2_buf, quad[i].op2); if (strchr(op2_buf, '.') != NULL) *strchr(op2_buf, '.') = '\0';
            fprintf(file, "    MOV AX, %s\n", op1_buf);
            fprintf(file, "    MOV BX, %s\n", op2_buf);
            fprintf(file, "    MUL BX\n");
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "/") == 0) {
            strcpy(op1_buf, quad[i].op1); if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
            strcpy(op2_buf, quad[i].op2); if (strchr(op2_buf, '.') != NULL) *strchr(op2_buf, '.') = '\0';
            fprintf(file, "    MOV AX, %s\n", op1_buf);
            fprintf(file, "    XOR DX, DX\n");
            fprintf(file, "    MOV BX, %s\n", op2_buf);
            fprintf(file, "    DIV BX\n");
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "BR") == 0) {
            fprintf(file, "    JMP etiq_%s\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "BZ") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op2);
            fprintf(file, "    CMP AX, 0\n");
            fprintf(file, "    JNE skip_jmp_%d\n", i);
            fprintf(file, "    JMP etiq_%s\n", quad[i].res);
            fprintf(file, "skip_jmp_%d:\n", i);
        } else if (strcmp(quad[i].oper, "BNZ") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op2);
            fprintf(file, "    CMP AX, 0\n");
            fprintf(file, "    JE skip_jmp_%d\n", i);
            fprintf(file, "    JMP etiq_%s\n", quad[i].res);
            fprintf(file, "skip_jmp_%d:\n", i);
        } else if (strcmp(quad[i].oper, "==") == 0 || strcmp(quad[i].oper, "<=") == 0 || strcmp(quad[i].oper, "<") == 0 || strcmp(quad[i].oper, ">") == 0 || strcmp(quad[i].oper, ">=") == 0 || strcmp(quad[i].oper, "!=") == 0) {
            strcpy(op1_buf, quad[i].op1); if (strchr(op1_buf, '.') != NULL) *strchr(op1_buf, '.') = '\0';
            strcpy(op2_buf, quad[i].op2); if (strchr(op2_buf, '.') != NULL) *strchr(op2_buf, '.') = '\0';
            fprintf(file, "    MOV AX, %s\n", op1_buf);
            fprintf(file, "    CMP AX, %s\n", op2_buf);
            if(strcmp(quad[i].oper, "==") == 0) fprintf(file, "    JE ");
            else if(strcmp(quad[i].oper, "<=") == 0) fprintf(file, "    JLE ");
            else if(strcmp(quad[i].oper, "<") == 0) fprintf(file, "    JL ");
            else if(strcmp(quad[i].oper, ">") == 0) fprintf(file, "    JG ");
            else if(strcmp(quad[i].oper, ">=") == 0) fprintf(file, "    JGE ");
            else if(strcmp(quad[i].oper, "!=") == 0) fprintf(file, "    JNE ");
            
            fprintf(file, "true_%d\n", i);
            fprintf(file, "    MOV AX, 0\n");
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
            fprintf(file, "    JMP end_cmp_%d\n", i);
            fprintf(file, "true_%d:\n", i);
            fprintf(file, "    MOV AX, 1\n");
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
            fprintf(file, "end_cmp_%d:\n", i);
        } else if (strcmp(quad[i].oper, "AND") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op1);
            fprintf(file, "    AND AX, %s\n", quad[i].op2);
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "OR") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op1);
            fprintf(file, "    OR AX, %s\n", quad[i].op2);
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "NOT") == 0) {
            fprintf(file, "    MOV AX, %s\n", quad[i].op1);
            fprintf(file, "    XOR AX, 1\n"); // Assuming boolean is 0 or 1
            fprintf(file, "    MOV %s, AX\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "IN") == 0) {
            fprintf(file, "    ; Code pour lecture de %s\n", quad[i].res);
        } else if (strcmp(quad[i].oper, "OUT") == 0) {
            fprintf(file, "    ; Code pour ecriture de %s\n", quad[i].res);
        }
    }
    
    // Ajout de l'étiquette de fin
    fprintf(file, "etiq_%d:\n", qc);

    fprintf(file, "    MOV AH, 4CH\n");
    fprintf(file, "    INT 21H\n");
    fprintf(file, "CODE ENDS\n");
    fprintf(file, "END MAIN\n");

    fclose(file);
    printf(">> Code machine genere dans le fichier '%s' !\n", filename);
}

#endif
