/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 24-04-2022*/


#ifndef __LEVENSHTEIN__
#define __LEVENSHTEIN__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef MIN
#define MIN(x,y) (((x)<(y))? (x) : (y))
#endif

#define INFINI 1000000000

/*===============================Déclarations=====================================*/

/* Fonction de calcul de la distance de Levenshtein entre deux mots 'un' et 'deux' *
 * mis en paramètre. Cette fonction est tirée de l'algorithme de wikipédia que nous *
 * nous nous sommes permis d'utiliser (https://fr.wikipedia.org/wiki/Distance_de_Levenshtein) */

int Levenshtein(char *m1, char *m2);



/*===================================================================================*/

#endif
