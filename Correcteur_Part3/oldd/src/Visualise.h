/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 10-03-2022
* Modification(s) : 20-03-2022 
                    17-03-2022
                    15-03-2022*/

#ifndef __VISUALISE__
#define __VISUALISE__

#include <stdio.h>
#include "ATR.h"


/*===============Déclaration================*/

/*écrit les trois premières lignes du fichier dot *f*/
void ecrireDebut(FILE *f);


/*écrit les lignes décrivant l’arbre "a" dans le fichier dot "a"*/
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
#endif