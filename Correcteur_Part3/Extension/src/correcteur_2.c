/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 03-04-2022*/


#include "Levenshtein.h"
#include "ArbreBK.h"
#include "Ext.h"
    
int main(int argc, char * argv[]){



    FILE * dico;
    FILE * text;



    
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

    int a;

    a = correction_tmp_reel(text, dico);

    (a != 0)?printf("It is ok\n") : printf("Error\n");

    fclose(text);
    fclose(dico);

    return 0;
}
