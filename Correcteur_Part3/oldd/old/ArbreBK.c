#include "ArbreBK.h"


NoeudBK * alloue_ArbreBK(char * mot){
    NoeudBK * n;

    n = (NoeudBK *)malloc(sizeof(NoeudBK));

    if(n != NULL){
        n->mot = (char *) malloc(sizeof(char) * (strlen(mot) + 1));
        if(n->mot != NULL){
            strcpy(n->mot, mot);
        }
        n->filsG = NULL;
        n->frereD = NULL;
        n->valeur = 0;
    }
    return n;
}

int inserer_dans_ArbreBK_aux(ArbreBK *A, char * mot, int dist){
    
    if(*A == NULL){
        (*A) = alloue_ArbreBK(mot);
        if(*A == NULL){
            return 0;
        } else{
            (*A)->valeur = dist;
            return 1;
        }
    }

    if(strcmp((*A)->mot, mot) == 0){
        printf("mot existe deja aux\n");
        return 0;
    }
    if((*A)->valeur == dist){
        dist = Levenshtein((*A)->mot, mot);
        if((*A)->filsG){
            if (dist < ((*A)->filsG)->valeur){
                NoeudBK * new = alloue_ArbreBK(mot);
                if(new != NULL){
                    new->frereD = (*A)->filsG;
                    (*A)->filsG = new;
                    new->valeur = dist;
                    return 1;
                }
                return 0;
            }
        }
        
        return inserer_dans_ArbreBK_aux(&((*A)->filsG), mot, dist);
    }
    if((*A)->valeur < dist){
        return inserer_dans_ArbreBK_aux(&((*A)->frereD), mot, dist);
    }
    if((*A)->valeur > dist){ /*corrige 16 avril : derniere est un fils de dans et non de marchande*/
        NoeudBK * new = alloue_ArbreBK(mot);
        if(new != NULL){
            new->frereD = (*A);
            (*A) = new;
            new->valeur = dist;
            return 1;
        }
        return 0;
    
    }
    return 0;
}

int inserer_dans_ArbreBK(ArbreBK * A, char * mot){
    if(*A == NULL){
        *A = alloue_ArbreBK(mot);
        if(*A == NULL){
            return 0;
        } else{
            (*A)->valeur = 0;
            return 1;
        }
    }
    int L;
    if((*A)->mot && strcmp((*A)->mot, mot) == 0){
        printf("mot existe deja\n");
        return 0;
    }
    L = Levenshtein((*A)->mot, mot);
    if((*A)->valeur == 0){
        if((*A)->filsG && (*A)->filsG->valeur > L){
            NoeudBK * new = alloue_ArbreBK(mot);
            if(new != NULL){
                new->frereD = (*A)->filsG;
                (*A)->filsG = new;
                new->valeur = L;
                return 1;
            }
            return 0;
        }
        return inserer_dans_ArbreBK_aux(&((*A)->filsG), mot, L);
    }
    return 0;
}

Liste rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, int dist){
    if(A == NULL){
        return NULL;
    }

    if(A->valeur ==dist){ /* mot est dans cette partie de l'arbre*/
        if(strcmp(A->mot, mot) == 0){
            printf("Mot trouvé\n");
            Liste new = allouer_Cellule(mot);
            return new;
        } else{
            dist = Levenshtein(A->mot, mot);
            return rechercher_dans_ArbreBK_aux(A->filsG, mot, dist);
        }
    } else if(A->valeur > dist){
        return NULL;
    } else{
        return rechercher_dans_ArbreBK_aux(A->frereD, mot, dist);
    }
    return NULL;
}

Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot){
    if(A == NULL){
        return NULL;
    }
    if(strcmp(A->mot, mot) == 0){ /*strcmp a utilisé ceci ne compare que les premiers caracteres*/
        Liste new = allouer_Cellule(mot);
        return new;
    }
    int L = Levenshtein(A->mot, mot);
    if(A->valeur == 0 && A->filsG == NULL){ /*On a que la racine*/
        return NULL;
    }
    return rechercher_dans_ArbreBK_aux(A->filsG, mot, L);
}

ArbreBK creer_ArbreBK(FILE * dico){

    assert(dico != NULL);

    char mot[20];
    ArbreBK arbre;
    arbre = NULL;

    while(fscanf(dico,"%s",mot)!=EOF){
        /*insertion du mot recupere dans l'arbre*/
        inserer_dans_ArbreBK(&arbre, mot);
    }
    rewind(dico);
    return arbre;
}

void liberer_ArbreBK(ArbreBK * A){
    if(*A != NULL){
        if((*A)->filsG == NULL && (*A)->frereD == NULL){
            free((*A)->mot);
            free(*A);
            *A = NULL;
            return;
        }
        if((*A)->filsG != NULL){
            liberer_ArbreBK(&((*A)->filsG));
        }
        if((*A)->frereD != NULL){
            liberer_ArbreBK(&((*A)->frereD));
        }
        free((*A)->mot);
        free(*A);
        *A = NULL;
        return;
    }
}


void afficher_ArbreBK_aux(ArbreBK A, int rang){

    int i, j;
    if(A){

        for(i = 0; i < rang; i++){
            
                printf("\t");
            
        }
        printf("|--%d-->\t%s\n", A->valeur, A->mot);
        afficher_ArbreBK_aux(A->filsG, rang + 1);
        afficher_ArbreBK_aux(A->frereD, rang);
    }
}
void afficher_ArbreBK(ArbreBK A){
    int rang;

    rang = 0;
    if(A){
        printf("\n\nReprésentation du dictionnaire en arbreBK\n\n");
        
        printf("%s\n", A->mot);
        
        afficher_ArbreBK_aux(A->filsG, rang);
        
        afficher_ArbreBK_aux(A->frereD, rang);
    }
}


Liste correctionBK(ArbreBK dico, FILE * a_corriger){
    assert(dico != NULL);
    assert(a_corriger != NULL);

    Liste erreur;
    char mot[20];
    FILE *file;

    traitement_fichier(a_corriger);

    erreur = NULL;
    file = fopen("traite.txt","r");

    if(file == NULL){
        fprintf(stderr, "fichier non ouvert");
        exit(1);
    }

    /* for chaque mot m present dans a_corriger do*/
    while(fscanf(file,"%s", mot) != EOF){
        /* if m est pas dans dico then*/

        if(rechercher_dans_ArbreBK(dico, mot) == NULL){
            /*inserer m en tete de la liste chainee erreurs*/
            inserer_en_tete(&erreur, mot);
        }

    }
    rewind(file);
    return erreur;
}


void Propose_correction_auxBK(ArbreBK arbre, Liste * lstmot, char * mot_a_corriger, int * dmin){
    
    assert(strlen(mot_a_corriger) > 0);
    assert(*dmin >= 0);

    int d;
    if(!arbre) return ;
    if(arbre){
       
           
            /*Algorithme de recupération des propositions de corrections*/

            d = Levenshtein(arbre->mot, mot_a_corriger);

            if(d <= *dmin){
                if(d < *dmin ){
                    *dmin = d;
                    /*vider corrections*/
                    liberer_Liste(lstmot);
                    *lstmot = NULL;
                }
                /*insertion de la proposition de correction */
                inserer_en_tete(lstmot, arbre->mot);
            
            }
        
         Propose_correction_auxBK(arbre->filsG, lstmot, mot_a_corriger, dmin);
        
        Propose_correction_auxBK(arbre->frereD, lstmot, mot_a_corriger, dmin);
    }
    }



Liste Propose_correctionBK(ArbreBK arbre, char * mot_a_corriger, int *dmin){

    assert(strlen(mot_a_corriger) > 0);
     char mot[26]; /* Chaine de caractères contenant les mots de l'arbre un par un*/
    int cmp;
    Liste lstmot;
    lstmot = NULL;

    cmp = 0;
    if(arbre == NULL){
        return NULL;
    } else {
             Propose_correction_auxBK(arbre->filsG, &lstmot, mot_a_corriger, dmin);
        Propose_correction_auxBK(arbre->frereD, &lstmot, mot_a_corriger, dmin);

    }

    return lstmot;
}