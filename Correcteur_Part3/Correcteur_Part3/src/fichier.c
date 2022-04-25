/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 17-03-2022
* Modification(s) : 20-03-2022 
                    19-03-2022*/

#include "fichier.h"

void retire_caractere_spec(char * mot,char * dest){
    assert(strlen(mot) > 0);

    int i;
    for(i = 0; i < strlen(mot); i++){

        /*isalpha issue du module ctype, verifie si le caractère*/
        /* fait partit de l'alphabet*/
        if(isalpha(mot[i])){
              dest[i] = mot[i];
        }
        else{
            dest[i] = ' ';/*remplace le caractère par un espace*/
        }
    } 
}



void retire_maj(char * mot, char *dest){
    assert(strlen(mot) > 0);

    int i;

    for(i = 0; i < strlen(mot); i++) {
        /*tolower issue du module string.h met en miniscule le*/
        /*caractère passé en paramètre*/
        dest[i] = tolower(mot[i]);
    }

}


void traitement_fichier(FILE * file){

    char mot[20];
    char *dest;
    char *dest2;

    FILE * traite = NULL;
    traite = fopen("traite.txt","w");
    
    /*parcours et récupération de tout les mots du fichier file*/
    while(fscanf(file,"%s",mot)!=EOF){

        dest = (char *)malloc(sizeof(char)*(strlen(mot)+1));

        retire_maj(mot, dest);

        dest2 = (char *)malloc(sizeof(char)*(strlen(mot)+1));

        retire_caractere_spec(dest,dest2);

        /*écriture du mot sans majuscule ni ponctuaction dans le fichier traite*/
        fprintf(traite,"%s ",dest2);

    }
    fclose(traite);
}
