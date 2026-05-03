#ifndef OPTIMISATION_H
#define OPTIMISATION_H

#include "quad.h"
#include <stdbool.h>
#include <string.h>

// Fonction pour vérifier si une variable est modifiée entre l'index start et end
bool is_modified(char *var, int start, int end) {
    if (strcmp(var, "") == 0 || strcmp(var, "vide") == 0) return false;
    for (int i = start; i < end; i++) {
        if (strcmp(quad[i].oper, "vide") != 0 && strcmp(quad[i].res, var) == 0) {
            return true;
        }
    }
    return false;
}

// Fonction pour vérifier si une variable est un temporaire généré par le compilateur (t1, t2...)
bool is_temp(char *var) {
    if (var[0] == 't' && var[1] >= '0' && var[1] <= '9') {
        return true;
    }
    return false;
}

// Fonction pour vérifier si une variable est utilisée comme indice de tableau (ex: Tab[t1])
bool is_used_in_array(char *op, char *var) {
    char *start = strchr(op, '[');
    char *end = strchr(op, ']');
    if (start != NULL && end != NULL && end > start) {
        char index[100];
        strncpy(index, start + 1, end - start - 1);
        index[end - start - 1] = '\0';
        if (strcmp(index, var) == 0) return true;
    }
    return false;
}

// Fonction pour identifier les cibles de saut (débuts de blocs de base)
void compute_jump_targets(bool targets[]) {
    for (int i = 0; i < qc; i++) {
        targets[i] = false;
    }
    for (int i = 0; i < qc; i++) {
        if (quad[i].oper[0] == 'B') {
            int target = -1;
            if (strcmp(quad[i].oper, "BR") == 0) target = atoi(quad[i].res);
            else target = atoi(quad[i].res); // BZ, BNZ etc. target is also in res
            
            if (target >= 0 && target < qc) {
                targets[target] = true;
            }
        }
    }
}

// 4. Simplification algébrique
void simplification_algebrique() {
    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0) continue;

        // X = Y * 2 => X = Y + Y
        if (strcmp(quad[i].oper, "*") == 0) {
            if (strcmp(quad[i].op2, "2") == 0) {
                strcpy(quad[i].oper, "+");
                strcpy(quad[i].op2, quad[i].op1); // Y + Y
            } else if (strcmp(quad[i].op1, "2") == 0) {
                strcpy(quad[i].oper, "+");
                strcpy(quad[i].op1, quad[i].op2);
                strcpy(quad[i].op2, quad[i].op2);
            }
            // X = Y * 1 => X = Y
            else if (strcmp(quad[i].op2, "1") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op2, "vide");
            } else if (strcmp(quad[i].op1, "1") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op1, quad[i].op2);
                strcpy(quad[i].op2, "vide");
            }
            // X = Y * 0 => X = 0
            else if (strcmp(quad[i].op2, "0") == 0 || strcmp(quad[i].op1, "0") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op1, "0");
                strcpy(quad[i].op2, "vide");
            }
        }
        // X = Y + 0 => X = Y
        else if (strcmp(quad[i].oper, "+") == 0) {
            if (strcmp(quad[i].op2, "0") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op2, "vide");
            } else if (strcmp(quad[i].op1, "0") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op1, quad[i].op2);
                strcpy(quad[i].op2, "vide");
            }
        }
        // X = Y - 0 => X = Y
        else if (strcmp(quad[i].oper, "-") == 0) {
            if (strcmp(quad[i].op2, "0") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op2, "vide");
            }
        }
        // X = Y / 1 => X = Y
        else if (strcmp(quad[i].oper, "/") == 0) {
            if (strcmp(quad[i].op2, "1") == 0) {
                strcpy(quad[i].oper, "<-");
                strcpy(quad[i].op2, "vide");
            }
        }
    }
}

// 3. Élimination des expressions redondantes
void elimination_redondance() {
    bool targets[1000];
    compute_jump_targets(targets);

    for (int i = 0; i < qc; i++) {
        if (strcmp(quad[i].oper, "vide") == 0 || strcmp(quad[i].oper, "<-") == 0 || 
            quad[i].oper[0] == 'B') continue;

        for (int j = i + 1; j < qc; j++) {
            if (targets[j]) break; // On s'arrête à la frontière d'un bloc de base
            if (strcmp(quad[j].oper, "vide") == 0) continue;

            if (strcmp(quad[i].oper, quad[j].oper) == 0 && 
                strcmp(quad[i].op1, quad[j].op1) == 0 && 
                strcmp(quad[i].op2, quad[j].op2) == 0) {
                
                // Vérifier que op1 et op2 n'ont pas été modifiés entre i et j
                if (!is_modified(quad[i].op1, i, j) && !is_modified(quad[i].op2, i, j)) {
                    // Remplacer l'opération de j par une affectation : res_j = res_i
                    strcpy(quad[j].oper, "<-");
                    strcpy(quad[j].op1, quad[i].res);
                    strcpy(quad[j].op2, "vide");
                }
            }
            
            // Si res_i est modifié entre temps, on ne peut plus utiliser res_i
            if (strcmp(quad[j].res, quad[i].op1) == 0 || strcmp(quad[j].res, quad[i].op2) == 0) {
                break; // Plus valide de réutiliser op1 ou op2 passé ce point s'il est redéfini
            }
        }
    }
}

// 1. Propagation de copie
void propagation_copie() {
    bool targets[1000];
    compute_jump_targets(targets);

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < qc; i++) {
            if (strcmp(quad[i].oper, "<-") == 0 && strcmp(quad[i].op2, "vide") == 0) {
                char var[100];
                strcpy(var, quad[i].res);
                char val[100];
                strcpy(val, quad[i].op1);

                if (strchr(var, '[') != NULL) continue; // Ignore arrays
                if (strcmp(var, "vide") == 0) continue;
                
                for (int j = i + 1; j < qc; j++) {
                    if (targets[j]) break; // Arrêt à la cible d'un saut
                    if (strcmp(quad[j].oper, "vide") == 0) continue;

                    // Stop if redefined
                    if (strcmp(quad[j].res, var) == 0 || strcmp(quad[j].res, val) == 0) {
                        break;
                    }

                    if (strcmp(quad[j].op1, var) == 0) {
                        strcpy(quad[j].op1, val);
                        changed = true;
                    }
                    if (strcmp(quad[j].op2, var) == 0) {
                        strcpy(quad[j].op2, val);
                        changed = true;
                    }
                }
            }
        }
    } while (changed);
}

// 5. Code inutile
void code_inutile() {
    bool targets[1000];
    compute_jump_targets(targets);

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < qc; i++) {

            if (strcmp(quad[i].oper, "vide") == 0 || strcmp(quad[i].res, "vide") == 0) continue;
            // Ne pas supprimer les sauts et I/O
            if (quad[i].oper[0] == 'B' || strcmp(quad[i].oper, "OUT") == 0 || strcmp(quad[i].oper, "IN") == 0) continue; 
            
            char res[100];
            strcpy(res, quad[i].res);
            
            // On ne s'applique qu'aux variables temporaires ou affectations sans crochets (pas de tableaux)
            if (is_temp(res) || (strcmp(quad[i].oper, "<-") == 0 && strchr(res, '[') == NULL)) {
                // On vérifie s'il est utilisé après
                bool used = false;
                bool redefined_before_use = false;
                for (int j = i + 1; j < qc; j++) {
                    if (targets[j]) {
                        if (!is_temp(res)) used = true; // Garder les variables normales incertaines, mais les temporaires meurent à la frontière
                        break;
                    }
                    if (strcmp(quad[j].oper, "vide") == 0) continue;

                    if (strcmp(quad[j].op1, res) == 0 || strcmp(quad[j].op2, res) == 0 || 
                        (strcmp(quad[j].oper, "OUT") == 0 && strcmp(quad[j].res, res) == 0) ||
                        (quad[j].oper[0] == 'B' && strcmp(quad[j].op1, res) == 0) ||
                        (quad[j].oper[0] == 'B' && strcmp(quad[j].op2, res) == 0) ||
                        is_used_in_array(quad[j].op1, res) ||
                        is_used_in_array(quad[j].op2, res) ||
                        is_used_in_array(quad[j].res, res)) {
                        used = true;
                        break;
                    }

                    // Si la variable est redéfinie avant d'être utilisée, alors l'affectation à l'étape i est inutile
                    if (strcmp(quad[j].res, res) == 0 && strchr(quad[j].res, '[') == NULL) {
                        redefined_before_use = true;
                        break;
                    }
                    
                    if (quad[j].oper[0] == 'B') {
                        if (!is_temp(res)) used = true; // Fin de bloc de base, incertain pour var normales
                        break;
                    }
                }
                
                // Si c'est un temporaire jamais utilisé (localement au bloc), ou une variable écrasée avant d'être lue dans le bloc
                if ((!used && is_temp(res)) || (!used && redefined_before_use)) {
                    strcpy(quad[i].oper, "vide");
                    strcpy(quad[i].op1, "vide");
                    strcpy(quad[i].op2, "vide");
                    strcpy(quad[i].res, "vide");
                    changed = true;
                }
            }
        }
    } while (changed);
}

void optimiser_quadruplets() {
    // Ordre suggere (Élimination redondance, simplification,  propagation, puis inutile)
    simplification_algebrique();
    elimination_redondance();
    propagation_copie();
    code_inutile();
}

#endif
