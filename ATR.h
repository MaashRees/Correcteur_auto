#ifndef __ATR__
#define __ATR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ntr{
    char racine;
    struct ntr * fils;
    struct ntr * fg;
    struct ntr * fd;
} NTR, * ATR;



ATR creer_ATR_vide(void);

void liberer_ATR(ATR * A);

int est_vide_ATR(ATR A);
int ajout(ATR * A, char * mot, int cmp);
int inserer_aux(ATR * A, char * mot, int cmp);
int inserer_dans_ATR(ATR * A, char * mot);

void supprimer_dans_ATR(ATR * A, char * mot);

void afficher_ATR(ATR A);

#endif