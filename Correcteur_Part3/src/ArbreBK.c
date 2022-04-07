#include "ArbreBK.h"



NoeudBK * alloue_ArbreBK(char * mot){
    NoeudBK * n;

    n = (NoeudBK *)malloc(sizeof(NoeudBK));

    if(n != NULL){
        n->mot = (char *) malloc(sizeof(char) * (strlen(mot) + 1));
        if(n->mot != NULL){
            strcpy(n->mot, mot);
        }
        n->filsG = NULL;
        n->frereD = NULL;
        n->valeur = 0;
    }
    return n;
}

int inserer_dans_ArbreBK_aux(ArbreBK *A, char * mot, int * dist){
    if(*A == NULL){
        *A = alloue_ArbreBK(mot);
        if(*A == NULL){
            return 0;
        } else{
            *A->valeur = *dist;
            return 1;
        }
    }
    if(*A->valeur == *dist){
        *dist = levenshtein(*A->mot, mot);
        return inserer_dans_ArbreBK_aux(&(*A->filsG), mot, dist);
    }
    if(*A->valeur < *dist){
        return inserer_dans_ArbreBK_aux(&(*A->frereD), mot, dist);
    }
    if(*A->valeur > *dist){
        NoeudBK * new = alloue_ArbreBK(mot);
        if(new != NULL){
            new->frereD = *A->filsG;
            *A->filsG = new;
            new->valeur = *dist;
            return 1;
        }
        return 0;
    
    }
    return 0;
}
int inserer_dans_ArbreBK(ArbreBK * A, char * mot){
    if(*A == NULL){
        *A = alloue_ArbreBK(mot);
        if(*A == NULL){
            return 0;
        } else{
            *A->valeur = 0;
            return 1;
        }
    }
    int L;
    L = levenshtein(*A->mot, mot);
    if(*A->valeur == 0){
        if(*A->filsG && *A->filsG->valeur > L){
            NoeudBK * new = alloue_ArbreBK(mot);
            if(new != NULL){
                new->frereD = *A->filsG;
                *A->filsG = new;
                new->valeur = L;
                return 1;
            }
            return 0;
        }
        return inserer_dans_ArbreBK_aux(&(*A->filsG), mot, &L);
    }
    return 0;
}

Liste rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, int dist){
    if(A == NULL){
        return NULL;
    }
    if(A->mot == mot){
        Liste new = alloue_liste(mot);
        return new;
    }
    if(dist < A->valeur){
        return NULL;
    }
    if(dist == A->valeur){
        return rechercher_dans_ArbreBK_aux(A->filsG, mot, levenshtein(A->mot, mot));
    }
    if(dist > A->valeur){
        return rechercher_dans_ArbreBK_aux(A->frereD, mot, dist);
    }
}

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot){
    if(A == NULL){
        return NULL;
    }
    if(A->mot == mot){ /*strcmp a utilisé ceci ne compare que les premiers caracteres*/
        Liste new = alloue_liste(mot);
        return new;
    }
    int L = levenshtein(A->mot, mot);
    if(A->valeur == 0 && A->filsG == NULL){
        return NULL;
    }
    return rechercher_dans_ArbreBK_aux(A->filsG, mot, L);
}

ArbreBK creer_ArbreBK(File * dico);

void liberer_ArbreBK(ArbreBK * A);

void afficher_ArbreBK(ArbreBK A);
