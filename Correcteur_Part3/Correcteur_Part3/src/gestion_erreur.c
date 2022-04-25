/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 23/04/2022
* Modification(s) : 23/04/2022
                    */


#include "gestion_erreur.h"

/*
Fonction qui affiche les arguments tels qu'il devrait être entrée.
Cette fonction d'affichage est appelé en cas de non conformité du 1er argument
*/
void affiche_argv(){

    fprintf(stderr,"\nIl faut entrer 3 arguments correcte\n");
    fprintf(stderr,"\t1er arg -> 0 ou 1 ou 2\n");
    fprintf(stderr,"\t2eme arg -> ressources/[texte à corriger]\n");
    fprintf(stderr,"\t3eme arg -> ressources/[dico de ref]\n");

}

/*
Fonction qui attribue a param l'entier servant d'option pour choisir le correcteur
que l'on veut executer. param vaut -1 si l'argument est différent de 0,1,2

param param : int*
param argv : char **
*/
void param_correcte(int *param,char * argv[]){

    if(strcmp(argv[1], "1")==0){
        *param = 1;

    }else if(strcmp(argv[1], "2")==0){
        *param = 2;

    }else if(strcmp(argv[1], "0")==0){
        *param = 0;

    }else {
        *param = -1;
    }

}
