/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 24-04-2022*/


#ifndef __ARBREBK__
#define __ARBREBK__

#include "Listes.h"
#include "fichier.h"
#include "Levenshtein.h"


typedef struct noeudBK {
    char * mot;
    int valeur;
    struct noeudBK * filsG;
    struct noeudBK * frereD;
} NoeudBK, * ArbreBK;


NoeudBK * alloue_ArbreBK(char * mot);

int inserer_dans_ArbreBK_aux(ArbreBK *A, char * mot, int dist);

int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

Liste rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, int dist);

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot);

ArbreBK creer_ArbreBK(FILE * dico);

void liberer_ArbreBK(ArbreBK * A);

void afficher_ArbreBK_aux(ArbreBK A, int rang);

void afficher_ArbreBK(ArbreBK A);

Liste correctionBK(ArbreBK dico, FILE * a_corriger);


/*==================================================================================*/
/*==================================================================================*/


/* Fonction auxiliaire de construction de la liste de propositions de *
 * correction d'un mot donné 'mot_a_corriger'. On s'est aidé *
 * de notre fonction affiche_ArbreBK  en y incorporant la fonction *
 * de Levenshtein et l'algorithme d'ajout dans la liste de *
 * propositions selon la distance obtenue */

void Propose_correction_auxBK(ArbreBK arbre, Liste * lstmot, char * mot_a_corriger, int * dmin);


/*==================================================================================*/
/*==================================================================================*/

/* Fonction de construction de la liste de propositions de *
 * correction d'un mot donné 'mot_a_corriger' */

Liste Propose_correctionBK(ArbreBK arbre, char * mot_a_corriger, int *dmin);



#endif 