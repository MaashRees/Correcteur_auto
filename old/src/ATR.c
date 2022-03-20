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
    /*ATR * tmp;
    if(*A){
        
        liberer_ATR(&((*A)->fg));
        liberer_ATR(&((*A)->fils));
        liberer_ATR(&((*A)->fd));

        free(*A);
    }*/
    if(*A){
            if ((*A)->fd) != NULL){
    
            liberer_ATR(&((*A)->fd));
            
            free(*A);
        }
        if ((*A)->fg) != NULL){
    
            liberer_ATR(&((*A)->fg));
            
            free(*A);
        }
        if ((*A)->fils) != NULL){
    
            liberer_ATR(&((*A)->fils));
            
            free(*A);
        }
        *A = NULL;
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
    cmp =0;
    if(*A){
        
        if((*A)->racine == '\0'){
            (*A)->racine = mot[cmp];
            return inserer_aux(&((*A)->fils), mot, cmp+1);
        }
        return inserer_aux(&((*A)), mot, cmp);
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

int inserer_arbre(ATR * A, ATR droite){
    if(droite == NULL){
        return 2;
    }
    if((*A)->fd == NULL){
        (*A)->fd = droite;
        return 1;
    }
    return inserer_arbre(&((*A)->fd), droite);
}

int supprimer_dans_ATR_aux(ATR * A, char * mot, int cmp){
    int sup_l;
    ATR tmp;
    if(*A == NULL){
        return 0;
    } 
    if(cmp == strlen(mot)){
        if((*A)->racine == '\0'){
            printf("Mot trouvé\n");
            printf("Suppression caractere vide\n");
            tmp = (*A)->fd; // recuperation de la partie droite qu'elle soit null ou pas
            free((*A));
            (*A) = tmp;
            printf("---------------------------------------\n");
            return 1;
        } else{
            printf("Arbre trop grand - Mot non trouvé\n");
            printf("---------------------------------------\n");
            return 0;
        }
    } 

    if((*A)->racine == '\0' && (*A)->fd == NULL){
        printf("Arbre trop petit - Mot non trouvé\n");
        printf("---------------------------------------\n");
        return 0;
    }
    if((*A)->racine == mot[cmp]){
        printf("Recherche au millieu , racine : %c, car recherché : %c-\n", (*A)->racine, mot[cmp]);
        printf("---------------------------------------\n");
        sup_l = supprimer_dans_ATR_aux(&(*A)->fils, mot, cmp + 1);
        if(sup_l){
            if((*A)->fils){ //on a un mot apres le mot à supprimer, ex sup de de alors qu'on a denise t on a fait remonté n au lieu de mettre à null
                printf("on a un mot apres le mot à supprimer\n");
                printf("---------------------------------------\n");
                return 1;
            }
            fprintf(stderr, "part1\n\n");
            printf("suppression de la lettre : %c fg : %p fd : %p\n", (*A)->racine, (*A)->fg, (*A)->fd);
            printf("cmpsq = %d, mot : %s \n", cmp, mot);
            tmp = *A;
            fprintf(stderr, "part2\n\n");
            if((*A)->fg){
                fprintf(stderr, "part3\n\n");
                printf("inserer arbre droit dans gauche : %d\n", inserer_arbre(&((*A)->fg), (*A)->fd));
                (*A) = (*A)->fg;
                tmp->fg = tmp->fd = tmp->fils= NULL;
                printf("---------------------------------------\n");
            } else{
                fprintf(stderr, "part4\n\n");
                printf("Pas de fils gauche\n");
                (*A) = (*A)->fd;
                tmp->fg = tmp->fd = tmp->fils= NULL;
                printf("---------------------------------------\n");
            }
            fprintf(stderr, "part5\n\n");
            //printf("new_caractere : %c\n", (*A)->racine);
            fprintf(stderr, "part6\n\n");
        }
        return sup_l;
    }
    if((*A)->racine > mot[cmp]){
        printf("Recherche a gauche , racine : %c, car recherché : %c-\n", (*A)->racine, mot[cmp]);
        printf("---------------------------------------\n");
        return supprimer_dans_ATR_aux(&((*A)->fg), mot, cmp);
    }
    if((*A)->racine < mot[cmp]){
        printf("Recherche à droite, racine : %c, car recherché : %c-\n", (*A)->racine, mot[cmp]);
        printf("---------------------------------------\n");
        return supprimer_dans_ATR_aux(&((*A)->fd), mot, cmp);
    }
    return 0;

}

void supprimer_dans_ATR(ATR * A, char * mot){
    int cmp, sup;
    cmp = 0;
    if(*A){
        printf("mot à supprimer : %s\n\n", mot);
        sup = supprimer_dans_ATR_aux(A, mot, cmp);
        if(sup){
            printf("\nMot trouvé et supprimé normalement\n\n\n");
        }
    }
}

void affiche_atr_aux(ATR A, char * mot, int cmp){
    if(A){
        if(A->fg){
            affiche_atr_aux(A->fg, mot, cmp);
        }
        /*if(A->racine == '\0'){
            mot[cmp] = '\0';
            printf("%s\n", mot);
            affiche_atr_aux(A->fd, mot, cmp);
        } else {
            mot[cmp] = A->racine;
            affiche_atr_aux(A->fils, mot, cmp + 1);
        }*/
        if(A->racine != '\0'){
            mot[cmp] = A->racine;
            affiche_atr_aux(A->fils, mot, cmp + 1);
        } else {
            mot[cmp] = '\0';
            printf("%s\n", mot);
        }
        affiche_atr_aux(A->fd, mot, cmp);
    }
}
void afficher_ATR(ATR A){
    char mot[26];
    int cmp;

    cmp = 0;
    if(A == NULL){
        return ;
    } else {
        affiche_atr_aux(A, mot, cmp);
    }
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
