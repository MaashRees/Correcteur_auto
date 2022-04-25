/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 03-04-2022*/

#include "ATR.h"
#include   "Visualise.h"
#include "Levenshtein.h"


int main(int argc, char * argv[]){

    ATR arbre;

    /*Liste d'erreurs*/
    Liste erreurs, tmp;

    /*Liste contenant les corrections d'un mot*/
    Liste lstcorrections;

    FILE * text;
    FILE * dico;

    int dmin;

    arbre = creer_ATR_vide();

    text = fopen(argv[1], "r");
    dico = fopen(argv[2], "r");
    if(dico)
        arbre = remplis_arbre(dico);
    

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
