#ifndef __ATR__
#define __ATR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listes.h"

typedef struct ntr{
    char racine;
    struct ntr * fils;
    struct ntr * fg;
    struct ntr * fd;
} NTR, * ATR;


/*==============================================================*/

ATR creer_ATR_vide(void);

/*===============================================================*/

void liberer_ATR(ATR * A);

/*==============================================================*/

int est_vide_ATR(ATR A);

/*==============================================================*/

int ajout(ATR * A, char * mot, int cmp);

int inserer_aux(ATR * A, char * mot, int cmp);

int inserer_dans_ATR(ATR * A, char * mot);

/*===============================================================*/

int recherche(ATR A, char * mot, int cmp);

/*===============================================================*/

int inserer_arbre(ATR * A, ATR droite);

int supprimer_dans_ATR_aux(ATR * A, char * mot, int cmp);

void supprimer_dans_ATR(ATR * A, char * mot);

/*================================================================*/

void affiche_atr_aux(ATR A, char * mot, int cmp);

void afficher_ATR(ATR A);

/*=================================================================*/

ATR remplis_arbre(FILE * fichier);

Liste correction(ATR A,FILE * file);

/*=================================================================*/

#endif