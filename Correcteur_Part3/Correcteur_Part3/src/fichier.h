/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 17-03-2022
* Modification(s) : 20-03-2022*/

#ifndef __FICHIER__
#define __FICHIER__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


/*
Fonction qui écrit le contenue de mot dans dest en enlevant la ponctuaction présente
param values : char *, char *
return values : void
*/
void retire_caractere_spec(char * mot,char * dest);


/*
Fonction qui écrit le contenue de mot dans dest en enlevant les majuscules présente
param values : char *, char *
return values : void
*/
void retire_maj(char * mot, char *dest);

/*
Fonction qui à partir du fichier passé en argument, réecrit les mots qu'il contient dans
le fichier traite.txt. Les mots réecrit ne contiennent plus aucune majuscules ni ponctuaction
param values : File *
return values : void 
*/
void traitement_fichier(FILE*file);

#endif
