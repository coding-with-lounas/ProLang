#include "TS.h"

/* Allocation globale mémoire de vos tables */
NodeTS* TS[HASH_SIZE];
TypeSM tabs[50], tabM[50];

/* ================================================================= */
/* FONCTION DE HACHAGE                                               */
/* ================================================================= */

/* Transforme une chaîne de caractères en un indice entre 0 et HASH_SIZE-1 */
int hash_function(char* name) {
    int somme = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        somme += name[i]; /* Somme des codes ASCII */
    }
    return somme % HASH_SIZE;
}

/* ================================================================= */
/* INITIALISATION ET INSERTION                                       */
/* ================================================================= */

void initialization() {
    int i;
    /* Initialiser la table de hachage avec des listes vides (NULL) */
    for (i = 0; i < HASH_SIZE; i++) { 
        TS[i] = NULL; 
    }
    /* Initialiser les autres tables */
    for (i = 0; i < 50; i++) { 
        tabs[i].state = 0; 
        tabM[i].state = 0; 
    }
}

void inserer(char entite[], char code[], int y) {
    int i;
    switch (y) {
        case 1: { 
            /* INSERTION DANS LA TABLE DE HACHAGE (Résolution par chaînage LIFO) */
            int index = hash_function(entite);
            
            /* Création du nouvel élément dynamique */
            NodeTS* nouveau = (NodeTS*)malloc(sizeof(NodeTS));
            strncpy(nouveau->name, entite, 255);
            nouveau->name[255] = '\0';
            strncpy(nouveau->code, code, 19);
            nouveau->code[19] = '\0';
            strcpy(nouveau->type, "");
            strcpy(nouveau->nature, "");
            nouveau->taille = 0;
            
            /* Insertion en LIFO : le nouveau pointe vers l'ancien début de liste, 
               et devient le nouveau début de liste dans le tableau. */
            nouveau->suivant = TS[index];
            TS[index] = nouveau;
            break;
        }
        case 2: /* Mots clés */
            for (i = 0; i < 50; i++) {
                if (tabM[i].state == 0) {
                    tabM[i].state = 1;
                    strncpy(tabM[i].nomEntite, entite, 255);
                    tabM[i].nomEntite[255] = '\0';
                    strncpy(tabM[i].Code, code, 19);
                    tabM[i].Code[19] = '\0';
                    return;
                }
            }
            break;
        case 3: /* Séparateurs */
            for (i = 0; i < 50; i++) {
                if (tabs[i].state == 0) {
                    tabs[i].state = 1;
                    strncpy(tabs[i].nomEntite, entite, 255);
                    tabs[i].nomEntite[255] = '\0';
                    strncpy(tabs[i].Code, code, 19);
                    tabs[i].Code[19] = '\0';
                    return;
                }
            }
            break;
    }
}

void rechercher(char entite[], char code[], int y) {
    int i;
    switch(y) {
        case 1: {
            /* RECHERCHE DANS LA TABLE DE HACHAGE */
            int index = hash_function(entite);
            NodeTS* courant = TS[index];
            
            /* Parcourir la liste chaînée à cet indice */
            while (courant != NULL) {
                if (strcmp(courant->name, entite) == 0) {
                    return; /* L'entité existe déjà */
                }
                courant = courant->suivant;
            }
            /* Si on arrive ici, l'entité n'existe pas -> on l'insère */
            inserer(entite, code, 1);
            break;
        }
        case 2:
            for (i = 0; i < 50 && tabM[i].state == 1; i++) {
                if (strcmp(entite, tabM[i].nomEntite) == 0) return;
            }
            inserer(entite, code, 2);
            break;
        case 3:
            for (i = 0; i < 50 && tabs[i].state == 1; i++) {
                if (strcmp(entite, tabs[i].nomEntite) == 0) return;
            }
            inserer(entite, code, 3);
            break;
    }
}

/* ================================================================= */
/* ROUTINES SEMANTIQUES (Adaptées pour la Table de Hachage)          */
/* ================================================================= */

int est_declare(char entite[]) {
    int index = hash_function(entite);
    NodeTS* courant = TS[index];
    
    while (courant != NULL) {
        if (strcmp(courant->name, entite) == 0) {
            if (strcmp(courant->type, "") != 0) return 1; /* Type rempli = Déclarée */
            else return 0; /* Existe mais pas encore typée */
        }
        courant = courant->suivant;
    }
    return 0;
}

void inserer_type_nature(char entite[], char type[], char nature[], int taille) {
    int index = hash_function(entite);
    NodeTS* courant = TS[index];
    
    while (courant != NULL) {
        if (strcmp(courant->name, entite) == 0) {
            strcpy(courant->type, type);
            strcpy(courant->nature, nature);
            courant->taille = taille;
            return;
        }
        courant = courant->suivant;
    }
}

int est_constante(char entite[]) {
    int index = hash_function(entite);
    NodeTS* courant = TS[index];
    
    while (courant != NULL) {
        if (strcmp(courant->name, entite) == 0) {
            if (strcmp(courant->nature, "CONST") == 0) return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

/* ================================================================= */
/* AFFICHAGE                                                         */
/* ================================================================= */

void afficher() {
    printf("\n/*********************** Table des symboles (Hachage Chaînage) ***********************/\n");
    printf("\t| %-5s | %-15s | %-12s | %-10s | %-10s | %-6s\n", "Index", "Nom", "Code", "Type", "Nature", "Taille");
    printf("\t----------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < HASH_SIZE; i++) {
        NodeTS* courant = TS[i];
        while (courant != NULL) {
            printf("\t| [%02d]  | %-15s | %-12s | %-10s | %-10s | %-6d\n", 
                   i, courant->name, courant->code, courant->type, courant->nature, courant->taille);
            courant = courant->suivant;
        }
    }
    
    printf("\n/******************** Table des symboles Mots cles ****************************/\n");
    printf("\t| %-15s | %-12s |\n", "NomEntite", "CodeEntite");
    printf("\t----------------------------------\n");
    for(int i = 0; i < 50; i++) {
        if(tabM[i].state == 1) {
            printf("\t| %-15s | %-12s |\n", tabM[i].nomEntite, tabM[i].Code);
        }
    }

    printf("\n/******************** Table des symboles Separateurs **************************/\n");
    printf("\t| %-15s | %-12s |\n", "NomEntite", "CodeEntite");
    printf("\t----------------------------------\n");
    for(int i = 0; i < 50; i++) {
        if(tabs[i].state == 1) {
            printf("\t| %-15s | %-12s |\n", tabs[i].nomEntite, tabs[i].Code);
        }
    }
}

/* ================================================================= */
/* NOUVELLE FONCTION : GET_NATURE                                    */
/* ================================================================= */

char* get_nature(char entite[]) {
    int index = hash_function(entite);
    NodeTS* courant = TS[index];
    
    /* On parcourt la liste chaînée à l'indice trouvé par le hachage */
    while (courant != NULL) {
        if (strcmp(courant->name, entite) == 0) {
            /* Retourne "VAR", "TAB" ou "CONST" stocké dans la table */
            return courant->nature; 
        }
        courant = courant->suivant;
    }
    return "NON_DECLARE"; /* Si l'entité n'existe pas */
}
