#include "ATR.h"

int main(int argc, char * argv[]){

    ATR arbre;
    Liste erreurs;
    int insert;

    FILE * text;
    FILE * dico;

    arbre = creer_ATR_vide();

    text = fopen(argv[1]);
    dico = fopen(argv[2]);
    if(dico)
        arbre = remplis_arbre(dico);

    if(text && arbre)
        erreurs = correction(arbre, text);
    
    if(erreurs){
        printf("Mots mal orthographiés : \n");
        afficher_Liste(erreurs);
    }
    return 0;   
}