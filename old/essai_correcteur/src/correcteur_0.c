#include "ATR.h"
#include   "Visualise.h"

int main(int argc, char * argv[]){

    ATR arbre;
    Liste erreurs;
    /*int insert;*/

    FILE * text;
    FILE * dico;

    arbre = creer_ATR_vide();

    text = fopen(argv[1], "r");
    dico = fopen(argv[2], "r");
    if(dico)
        arbre = remplis_arbre(dico);

    printf("Dictionnaire %s\n", argv[2]);

    afficher_ATR(arbre);
    creePDF(arbre);
    printf("====================================\n\n");

    if(text && arbre)
        erreurs = correction(arbre, text);
    
    if(erreurs){
        printf("Mots mal orthographiés : \n");
        afficher_Liste(erreurs);
        printf("\n");
    }
    return 0;   
}
