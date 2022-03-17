#ifndef __LISTE__
#define __LISTE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cellule{
  char *mot;
  struct cellule *suivant;
}Cellule, *Liste ;

Cellule * allouer_Cellule(char*mot);

int inserer_en_tete(Liste * L, char * mot);

void liberer_Liste(Liste * L);

void afficher_Liste(Liste L);


#endif