#ifndef __ARBREBK__
#define __ARBREBK__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Liste.h"
#include "Levenshtein.h"


typedef struct noeudBK {
    char * mot;
    int valeur;
    struct areteBK * filsG;
    struct areteBK * frereD;
} NoeudBK, * ArbreBK;


NoeudBK * alloue_ArbreBK(char * mot);

int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot);

ArbreBK creer_ArbreBK(File * dico);

void liberer_ArbreBK(ArbreBK * A);

void afficher_ArbreBK(ArbreBK A);



#endif