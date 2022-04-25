/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 20-04-2022
* Modification(s) : 23-04-2022*/

#ifndef __EXT__
#define __EXT__

#include "Levenshtein.h"
#include "ArbreBK.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*fonction de demande de choix de correction à un utilisateur du programme*/
char * fonction_corrige_ou_non(char * mot, const Liste propositions);

/*fonction implementant un algorithme de correction de texte en temps reel*/
int correction_tmp_reel(FILE * in, FILE * dico);


#endif