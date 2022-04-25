/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 20-04-2022
* Modification(s) : 24-04-2022*/

#ifndef __VISUALISE__
#define __VISUALISE__

#include <stdio.h>
#include "ArbreBK.h"
#include "ATR.h"

/*===============Déclaration================*/

/*écrit les trois premières lignes du fichier dot *f*/
void ecrireDebut(FILE *f);


/*écrit les lignes décrivant l’arbre ternaire de recherche "a" dans le fichier dot "a"*/
void ecrireArbre(FILE *f, ATR a);


/*écrit la dernière ligne du fichier *f, c’est-à-dire qu’elle ferme l’accolade*/
void ecrireFin(FILE *f);


/*Fonction de création générale du fichier dot "f" à partir de l'arbre ternaire de recherche a*/
void  dessine(FILE *f, ATR a);

/*============================================*/
/*===========================================*/


/*Crée un fichier pdf du nom de "arbre.pdf" à partir de l'arbre ternaire de recherche "a"*/
void  creePDF(ATR a);

/*===============================================*/


/*============================================*/
/*===========================================*/


/*écrit les lignes décrivant l’arbreBK "a" dans le fichier dot "a"*/

void ecrireArbre_BK(FILE *f, ArbreBK arbre);

/*Fonction de création générale du fichier dot "f" à partir de l'arbreBK a*/
void  dessine_BK(FILE *f, ArbreBK arbre);


/*Crée un fichier pdf du nom de "arbre.pdf" à partir de l'arbreBK "a"*/

void  creePDF_ArbreBK(ArbreBK arbre);

/*===============================================*/


#endif