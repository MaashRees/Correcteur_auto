#include "Liste.h"

Cellule * allouer_Cellule(char*mot){

  Cellule * new = (Cellule *) malloc(sizeof(Cellule));
  if(new){
      new->mot = (char *) malloc(sizeof(char)*strlen(mot)+1);
      if(!new->mot)
          return NULL;
      strcpy(new->mot, mot);
      new->suivant = NULL;
  }
  return new;
}

int inserer_en_tete(Liste * L, char * mot){
  Liste tmp;
  Cellule * new = allouer_Cellule(mot);

  if(new == NULL){/* l'allocation de la nouvelle cellule a fail*/
      return 0;
  }

  if(!*L){/* La liste est vide*/
      *L = new;
  }
  else{
    tmp = *L;
    *L = new;
    new->suivant = tmp;
  }
  return 1;
}

void liberer_Liste(Liste * L){
  Liste tmp;

  while(*L){
    tmp = *L;
    *L = (*L)->suivant;
    free(tmp);
  }
  free(*L);
}


void afficher_Liste(Liste L){
  while(L){
    printf("%s ->",L->mot);
    L = L->suivant;
  }

}

