/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 20-04-2022
* Modification(s) : 23-04-2022*/

#include "correcteur_2.h"


/*main pour lançer le correcteur_2 du projet

param argc: int (nombre d'arguments donné au programme)
param argv : char ** (tableau des arguments)

return value : int (0) 

*/
int _correcteur_2(int argc, char * argv[]){


    ArbreBK arbre = NULL;

    Liste erreurs, tmp , lstcorrections;

    FILE * dico;
    FILE * text;


    int dmin;


    text = fopen(argv[2], "r");
    if(text == NULL){
        fprintf(stderr,"Le texte à corriger n'a pas été ouvert\n");
        return 0;
    }



    dico = fopen(argv[3], "r");
    if(dico == NULL){
        fprintf(stderr,"Le dico n'a pas été ouvert\n");
        return 0;
    }

    if(dico){

        arbre = creer_ArbreBK(dico);
        creePDF_ArbreBK(arbre);
    }




    afficher_ArbreBK(arbre);
    

    printf("====================== Mots mal orthographiés ===========================\n\n");

    erreurs = correctionBK(arbre,text);

    afficher_Liste(erreurs);

    printf("\n====================================================================\n\n");
    printf("======================Entrée de correction ===========================\n\n");


    tmp = erreurs;

    while(tmp){
        dmin = INFINI;
                 lstcorrections = Propose_correctionBK(arbre, tmp->mot, &dmin);

        printf("\n==========================================================\n\n");
        printf("Propositions de correction de  : %s\n\n", tmp->mot);
        afficher_Liste(lstcorrections);

        tmp = tmp->suivant;

        liberer_Liste(&lstcorrections);
    }
    printf("====================== Sortie de correction =====================\n\n");

    liberer_Liste(&erreurs);


    liberer_ArbreBK(&arbre);
    fclose(text);
    fclose(dico);


    return 0;
}
