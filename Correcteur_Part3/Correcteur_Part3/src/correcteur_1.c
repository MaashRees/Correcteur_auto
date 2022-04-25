/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 20-04-2022
* Modification(s) : 23-04-2022*/


#include "correcteur_1.h"

/*main pour lançer le correcteur_1 du projet

param argc: int (nombre d'arguments donné au programme)
param argv : char ** (tableau des arguments)

return value : int (0) 

*/
int _correcteur_1(int argc, char * argv[]){

    ATR arbre;

    /*Liste d'erreurs*/
    Liste erreurs, tmp;

    /*Liste contenant les corrections d'un mot*/
    Liste lstcorrections;

    FILE * text;
    FILE * dico;

    int dmin;



    arbre = creer_ATR_vide();

    text = fopen(argv[2], "r");
    dico = fopen(argv[3], "r");
    if(dico){
        arbre = remplis_arbre(dico);
        creePDF(arbre);
    }

    printf("====================== Mots mal orthographiés ===========================\n\n");

    erreurs = correction(arbre, text);

    afficher_Liste(erreurs);

    printf("\n====================================================================\n\n");
    printf("======================Entrée de correction ===========================\n\n");
    tmp = erreurs;
    while(tmp){
        dmin = INFINI;

        lstcorrections = Propose_correction(arbre, tmp->mot, &dmin);

        printf("\n==========================================================\n\n");
        printf("Propositions de correction de  : %s\n\n", tmp->mot);
        afficher_Liste(lstcorrections);

        tmp = tmp->suivant;

        liberer_Liste(&lstcorrections);
    }
    printf("====================== Sortie de correction =====================\n\n");



    liberer_Liste(&erreurs);

    liberer_ATR(&arbre);

    fclose(text);
    fclose(dico);


    return 0;
}
