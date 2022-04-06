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



void Propose_correction_aux(ATR arbre, char * mot, int cmp, Liste * lstmot, char * mot_a_corriger, int * dmin){

    assert(cmp >= 0);
    assert(cmp <= strlen(mot));
    assert(strlen(mot_a_corriger) > 0);
    assert(*dmin >= 0);


    int d;

    if(arbre){
        if(arbre->gauche){
            Propose_correction_aux(arbre->gauche, mot, cmp, lstmot, mot_a_corriger, dmin);
        }
        if(arbre->racine != '\0'){
            /*extraction du cmp-ieme caractère du mot de l'arbre*/
            mot[cmp] = arbre->racine;
            Propose_correction_aux(arbre->fils, mot, cmp + 1, lstmot, mot_a_corriger, dmin);
        } else {
            /*Mot complet - on est à la fin de mot*/
            mot[cmp] = '\0';

            /*Algorithme de recupération des propositions de corrections*/

            d = Levenshtein(mot, mot_a_corriger);

            if(d <= *dmin){
                if(d < *dmin ){
                    *dmin = d;
                    /*vider corrections*/
                    liberer_Liste(lstmot);
                    *lstmot = NULL;
                }
                /*insertion de la proposition de correction */
                inserer_en_tete(lstmot, mot);

            }

        }
        Propose_correction_aux(arbre->droite, mot, cmp, lstmot, mot_a_corriger, dmin);
    }
}

Liste Propose_correction(ATR arbre, char * mot_a_corriger, int *dmin){

    assert(strlen(mot_a_corriger) > 0);

    char mot[26]; /* Chaine de caractères contenant les mots de l'arbre un par un*/
    int cmp;
    Liste lstmot;
    lstmot = NULL;

    cmp = 0;
    if(arbre == NULL){
        return NULL;
    } else {
        
        Propose_correction_aux(arbre, mot, cmp, &lstmot, mot_a_corriger, dmin);

    }

    return lstmot;
}
