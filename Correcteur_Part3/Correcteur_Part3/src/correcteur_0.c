/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 20-04-2022
* Modification(s) : 23-04-2022*/

#include "correcteur_0.h"


/*main pour lançer le correcteur_0 du projet

param argc: int (nombre d'arguments donné au programme)
param argv : char ** (tableau des arguments)

return value : int (0) 

*/
int _correcteur_0(int argc, char * argv[]){

    ATR arbre;
    Liste erreurs;

    FILE * text;
    FILE * dico;

    arbre = creer_ATR_vide();

    text = fopen(argv[2], "r");
    dico = fopen(argv[3], "r");
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
