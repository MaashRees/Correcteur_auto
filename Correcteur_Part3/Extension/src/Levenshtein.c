/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 24-04-2022*/

#include "Levenshtein.h"


int Levenshtein(char *un, char *deux){

    assert(strlen(un) > 0);
    assert(strlen(deux) > 0);

    int tab[strlen(un)+1][strlen(deux)+1];

    int i,j, cout;

    /*remplissage colonne*/
    for(i = 0; i < strlen(un)+1; i++){
        tab[i][0] = i;
    }

    /*remplissage ligne*/
    for(j = 0; j < strlen(deux)+1; j++){
        tab[0][j] = j;
    }

    /*remplissage du tableau*/

    for(i = 1; i < strlen(un)+1; i++){
        for(j = 1; j < strlen(deux)+1; j++){

        /*si meme caractere*/
        if(un[i-1] == deux[j-1]){
            cout = 0;
        }else{
            cout = 1;
        }

        tab[i][j] =  MIN(MIN((tab[i-1][j] + 1), (tab[i][j-1] + 1)),( tab[i-1][j-1] + cout));
        }
    }

    return tab[strlen(un)][strlen(deux)];

}


