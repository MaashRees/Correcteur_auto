/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 03-04-2022*/

#include "ATR.h"
#include "Visualise.h"
#include "Levenshtein.h"
#include "ArbreBK.h"


    
int main(int argc, char * argv[]){


    ArbreBK arbre = NULL;

    Liste erreurs, tmp , lstcorrections;

    FILE * dico;
    FILE * text;


    int dmin;

    
    text = fopen(argv[1], "r");
    if(text == NULL){
        fprintf(stderr,"ta fail ouverture du text\n");
        return 0;
    }

    
    dico = fopen(argv[2], "r");
    if(dico == NULL){
        fprintf(stderr,"ta fail ouverture du dico\n");
        return 0;
    }

    if(dico){
        arbre = creer_ArbreBK(dico);
        //creePDF(arbre);
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
