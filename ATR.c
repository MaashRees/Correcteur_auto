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
        if(cmp == strlen(mot)){
            printf("\n");
            return 1;
        }
        (*A)->racine = mot[cmp];
        printf("%c", (*A)->racine);
        return ajout(&((*A)->fils), mot, cmp + 1);
    }
    return 0;
}

int inserer_aux(ATR * A, char * mot, int cmp){
    if(cmp == strlen(mot)){
        return 0;
    }
    if((*A) == NULL){
        return ajout(A, mot, cmp);
    }
    if((*A)->racine == '\0'){
        return ajout(&((*A)->fd), mot, cmp);
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


void supprimer_dans_ATR(ATR * A, char * mot){
    
}

void afficher_ATR(ATR A);


int main(int argc, char * argv[]){

    ATR arbre;
    int insert;
    arbre = creer_ATR_vide();
    

    if(arbre){
        
        insert = inserer_dans_ATR(&arbre, "le");
        fprintf(stderr, "insertion 1 : %d\n", insert);
        
        insert = inserer_dans_ATR(&arbre, "dla");
        fprintf(stderr, "insertion 2 : %d\n", insert);

        insert = inserer_dans_ATR(&arbre, "le");
        fprintf(stderr, "insertion 2 : %d\n", insert);

        insert = inserer_dans_ATR(&arbre, "la");
        fprintf(stderr, "insertion 2 : %d\n", insert);

        liberer_ATR(&arbre);
    }
    return 0;   
}
