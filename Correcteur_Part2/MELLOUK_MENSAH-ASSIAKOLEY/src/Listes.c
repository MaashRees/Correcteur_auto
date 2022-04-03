/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 28-02-2022
* Modification(s) : 20-03-2022 
                    01-03-2022*/

#include "Listes.h"

Cellule * allouer_Cellule(char*mot){

    assert(strlen(mot) > 0);

    Cellule * new = (Cellule *) malloc(sizeof(Cellule));

    if(new){ /* l'allocation a réussi*/
        new->mot = (char *) malloc(sizeof(char)*strlen(mot)+1);

        if(!new->mot) /* l'allocation de l'emplacement qui sera dédié au "mot"a echoué*/
            return NULL;

        strcpy(new->mot, mot); /*copie du mot dans la champs mot de la nouvelle cellule*/
        new->suivant = NULL;
    }
    return new;
}

int inserer_en_tete(Liste * L, char * mot){
    assert(strlen(mot) > 0);

    Liste tmp;
    Cellule * new = allouer_Cellule(mot);

    if(new == NULL){/* l'allocation de la nouvelle cellule a échoué*/
        return 0;
    }

    if(!*L){/* La liste est vide*/
        *L = new;
    } else{
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
        free(tmp); /*liberation de la cellule*/
    }
    free(*L);/*liberation de la liste*/
}



void afficher_Liste(Liste L){

    assert(L != NULL);

    while(L){
        printf("%s\n",L->mot); /*affichage du mot contenu dans la cellule pointée*/
        L = L->suivant;
    }
}
