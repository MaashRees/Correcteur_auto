#include "ATR.h"


ATR creer_ATR_vide(void){
    ATR lexique;
    lexique = (NTR *) malloc(sizeof(NTR));
    if(lexique){
        lexique->racine = '\0';
        lexique->fils = NULL;
        lexique->fg = NULL;
        lexique->fd = NULL;
    }
    return lexique;
}


void liberer_ATR(ATR * A){
    ATR * tmp;
    if(*A){
        
        liberer_ATR(&((*A)->fg));
        liberer_ATR(&((*A)->fils));
        liberer_ATR(&((*A)->fd));

        free(*A);
    }
}

int est_vide_ATR(ATR A){
    if(A->racine == '\0' && A->fd){
        return 1;
    }
    if(A->racine != '\0' && A->fils){
        return 2;
    }
    return 0;
}

int ajout(ATR * A, char * mot, int cmp){
    if((*A) == NULL){
        *A = creer_ATR_vide();
        if((*A) == NULL){
            return 0;
        }
    }
    if(cmp == strlen(mot)){
            printf("\n");
            return 1;
    }
    (*A)->racine = mot[cmp];
    printf("%c", (*A)->racine);
    return ajout(&((*A)->fils), mot, cmp + 1);
    
}

int inserer_aux(ATR * A, char * mot, int cmp){
    if(cmp == strlen(mot)){
        return 0;
    }
    if((*A) == NULL){
        return ajout(A, mot, cmp);
    }
    if((*A)->racine == '\0'){
        return inserer_aux(&((*A)->fd), mot, cmp);
    } else {
        if((*A)->racine == mot[cmp]){
            return inserer_aux(&((*A)->fils), mot, cmp  + 1);
        }
        if((*A)->racine < mot[cmp]){
            return inserer_aux(&((*A)->fd), mot, cmp);
        }
        if((*A)->racine > mot[cmp]){
            return inserer_aux(&((*A)->fg), mot, cmp);
        }
    }
    return 0;
}


int inserer_dans_ATR(ATR * A, char * mot){
    int cmp;
    if(*A){
        cmp =0;
        return inserer_aux(&((*A)->fd), mot, cmp);
    }
    
    return 0;
}

int recherche(ATR A, char * mot, int cmp){

    if(A == NULL){
        return 0;
    }
    printf("le compteur %d , A->racine = %c\n", cmp, A->racine);
    if((cmp == strlen(mot))){
        if(A->racine == '\0'){
            return 1;
        } else{
            return 0;
        }
    }

    if(A->racine == '\0' && A->fd == NULL){
        return 0;
    }
    if(A->racine == mot[cmp]){
        return recherche(A->fils, mot, cmp + 1);
    }if(A->racine > mot[cmp]){
        return recherche(A->fg, mot, cmp);
    }
    if(A->racine < mot[cmp]){
        return recherche(A->fd, mot, cmp);
    }
    return 0;
}


void supprimer_dans_ATR(ATR * A, char * mot){

}

void afficher_ATR(ATR A){

}

ATR remplis_arbre(FILE * fichier){

  char mot[20];
  ATR arbre;
  arbre = creer_ATR_vide();

  while(fscanf(fichier,"%s",mot)!=EOF){
    inserer_dans_ATR(&arbre, mot);
  }
  rewind(fichier);
  return arbre;

}

Liste correction(ATR A,FILE * file){


   
    Liste erreur = NULL;
    char mot[20];


      /*file = fopen("text","r");*/
    if(file == NULL){fprintf(stderr," fichier non ouvert");return;}

        /* for chauqe mot m presnet dans a_cooriger do*/
    while(fscanf(file,"%s",mot)!=EOF){
          /* if m est pas dans dico then*/

        if(!recherche(A, mot,0)){
            printf("%s\n", mot);
          /*inserer m en tete de la liste chainee erreurs*/
            inserer_en_tete(&erreur, mot);
        }

    }
    rewind(file);
    return erreur;
}
