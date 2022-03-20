/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 19-03-2022
* Modification(s) : 20-03-2022*/

#include "ATR.h"
#include   "Visualise.h"

int main(int argc, char * argv[]){

    ATR arbre;
    Liste erreurs;

    FILE * text;
    FILE * dico;

    arbre = creer_ATR_vide();

    text = fopen(argv[1], "r");
    dico = fopen(argv[2], "r");
    if(dico)
        arbre = remplis_arbre(dico);

    afficher_ATR(arbre);
    creePDF(arbre);

    if(text && arbre)
        erreurs = correction(arbre, text);

    if(erreurs){
        afficher_Liste(erreurs);
        printf("\n");
    }
    
    liberer_Liste(&erreurs);
    liberer_ATR(&arbre);
    fclose(dico);
    fclose(text);
    return 0;
}
