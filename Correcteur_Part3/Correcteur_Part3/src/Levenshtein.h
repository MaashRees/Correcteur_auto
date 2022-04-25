/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 30-03-2022
* Modification(s) : 30-03-2022*/


#ifndef __LEVENSHTEIN__
#define __LEVENSHTEIN__

#include "ATR.h"
#ifndef MIN
#define MIN(x,y) (((x)<(y))? (x) : (y))
#endif

#define INFINI 1000000000

/*===============================Déclarations=====================================*/

/* Fonction de calcul de la distance de Levenshtein entre deux mots 'un' et 'deux' *
 * mis en paramètre. Cette fonction est tirée de l'algorithme de wikipédia que nous *
 * nous nous sommes permis d'utiliser (https://fr.wikipedia.org/wiki/Distance_de_Levenshtein) */

int Levenshtein(char *m1, char *m2);


/*==================================================================================*/
/*==================================================================================*/


/* Fonction auxiliaire de construction de la liste de propositions de *
 * correction d'un mot donné 'mot_a_corriger'. On s'est aidé *
 * de notre fonction afficher_ATR  en y incorporant la fonction *
 * de Levenshtein et l'algorithme d'ajout dans la liste de *
 * propositions selon la distance obtenue */

void Propose_correction_aux(ATR arbre, char * mot, int cmp, Liste * lstmot, char * mot_a_corriger, int * dmin);



/*==================================================================================*/
/*==================================================================================*/

/* Fonction de construction de la liste de propositions de *
 * correction d'un mot donné 'mot_a_corriger' */

Liste Propose_correction(ATR arbre, char * mot_a_corriger, int * dmin);


/*===================================================================================*/

#endif
