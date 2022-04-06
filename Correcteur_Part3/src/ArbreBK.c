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

int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot);

ArbreBK creer_ArbreBK(File * dico);

void liberer_ArbreBK(ArbreBK * A);

void afficher_ArbreBK(ArbreBK A);
