#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


typedef struct cellule{
  char *mot; /*mot contenue dans une cellule*/
  struct cellule *suivant; /*pointeur permettant de relié les cellules entre elles*/
}Cellule, *Liste ;


Cellule * allouer_Cellule(char*mot){

    assert(strlen(mot) > 0);

    Cellule * new = (Cellule *) malloc(sizeof(Cellule));

    if(new){ /* l'allocation a réussi*/
        new->mot = (char *) malloc(sizeof(char)*strlen(mot)+1);

        if(!new->mot) /* l'allocation de l'emplacement qui sera dédié au "mot"a echoué*/
            return NULL;

        strcpy(new->mot, mot); /*copie du mot dans la champs mot de la nouvelle cellule*/
        new->suivant = NULL;
    }
    return new;
}

int inserer_en_tete(Liste * L, char * mot){
    assert(strlen(mot) > 0);

    Liste tmp;
    Cellule * new = allouer_Cellule(mot);

    if(new == NULL){/* l'allocation de la nouvelle cellule a échoué*/
        return 0;
    }

    if(!*L){/* La liste est vide*/
        *L = new;
    } else{
        tmp = *L;
        *L = new;
        new->suivant = tmp;
    }
    return 1;
}

void liberer_Liste(Liste * L){
    Liste tmp;

    while(*L){
        tmp = *L;
        *L = (*L)->suivant;
        free(tmp); /*liberation de la cellule*/
    }
    free(*L);/*liberation de la liste*/
}



void afficher_Liste(Liste L){

    assert(L != NULL);

    while(L){
        printf("%s\n",L->mot); /*affichage du mot contenu dans la cellule pointée*/
        L = L->suivant;
    }
}

#ifndef MIN
#define MIN(x,y) (((x)<(y))? (x) : (y))
#endif

int Levenshtein(char *un, char *deux){

    assert(strlen(un) > 0);
    assert(strlen(deux) > 0);

    int tab[strlen(un)+1][strlen(deux)+1];

    int i,j, cout;

    /*remplissage colonne*/
    for(i = 0; i < strlen(un)+1; i++){
        tab[i][0] = i;
    }

    /*remplissage ligne*/
    for(j = 0; j < strlen(deux)+1; j++){
        tab[0][j] = j;
    }

    /*remplissage du tableau*/

    for(i = 1; i < strlen(un)+1; i++){
        for(j = 1; j < strlen(deux)+1; j++){

        /*si meme caractere*/
        if(un[i-1] == deux[j-1]){
            cout = 0;
        }else{
            cout = 1;
        }

        tab[i][j] =  MIN(MIN((tab[i-1][j] + 1), (tab[i][j-1] + 1)),( tab[i-1][j-1] + cout));
        }
    }

    return tab[strlen(un)][strlen(deux)];

}



typedef struct noeudBK {
    char * mot;
    int valeur;
    struct noeudBK * filsG;
    struct noeudBK * frereD;
} NoeudBK, * ArbreBK;


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
        return inserer_dans_ArbreBK_aux(&((*A)->filsG), mot, dist);
    }
    if((*A)->valeur < dist){
        return inserer_dans_ArbreBK_aux(&((*A)->frereD), mot, dist);
    }
    if((*A)->valeur > dist){
        NoeudBK * new = alloue_ArbreBK(mot);
        if(new != NULL){
            new->frereD = (*A)->filsG;
            (*A)->filsG = new;
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
    if(strcmp(A->mot, mot) == 0){
        printf("Mot trouvé\n");
        Liste new = allouer_Cellule(mot);
        return new;
    }
    if(dist < A->valeur){
        printf("distance eleve mot pas trouvé\n");
        return NULL;
    }
    if(dist == A->valeur){
        printf("mot surement dans le fils de %s\n", (A->mot));
        dist = Levenshtein(A->mot, mot);
        return rechercher_dans_ArbreBK_aux(A->filsG, mot, dist);
    }
    if(dist > A->valeur){
        printf("mot surement dans le frere de %s\n", (A->mot));
        return rechercher_dans_ArbreBK_aux(A->frereD, mot, dist);
    }
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
    if(A->valeur == 0 && A->filsG == NULL){
        return NULL;
    }
    return rechercher_dans_ArbreBK_aux(A->filsG, mot, L);
}

ArbreBK creer_ArbreBK(FILE * dico){

}

void liberer_ArbreBK(ArbreBK * A);

void afficher_ArbreBK(ArbreBK A){
    if(A){
        
        printf("Mot : %s \tdistance Levenshtein : %d\n", A->mot, A->valeur);
        printf("\nfils de %s\n", A->mot);
        afficher_ArbreBK(A->filsG);
        printf("\nfreres de %s\n", A->mot);
        afficher_ArbreBK(A->frereD);
    }
}


int main(int argc, char * argv[]){


    ArbreBK arbre = NULL;

    printf("insertion de %s : %d\n", "une", inserer_dans_ArbreBK(&arbre, "une"));
    printf("insertion de %s : %d\n", "foix", inserer_dans_ArbreBK(&arbre, "fois"));
    printf("insertion de %s : %d\n", "foie", inserer_dans_ArbreBK(&arbre, "foie"));
    printf("insertion de %s : %d\n", "qui", inserer_dans_ArbreBK(&arbre, "qui"));
    printf("insertion de %s : %d\n", "ville", inserer_dans_ArbreBK(&arbre, "ville"));
    printf("insertion de %s : %d\n", "foix", inserer_dans_ArbreBK(&arbre, "foix"));
    printf("insertion de %s : %d\n", "elle", inserer_dans_ArbreBK(&arbre, "elle"));
    printf("insertion de %s : %d\n", "foi", inserer_dans_ArbreBK(&arbre, "foi"));
    printf("insertion de %s : %d\n", "est", inserer_dans_ArbreBK(&arbre, "est"));
    printf("insertion de %s : %d\n", "que", inserer_dans_ArbreBK(&arbre, "que"));

    printf("\n\n=====================Affichage===========================\n\n");

    afficher_ArbreBK(arbre);

    printf("\n\n==================recherche==============================\n\n");

    printf("recherche de %s : %p\n", "une", rechercher_dans_ArbreBK(arbre, "une"));
    printf("recherche de %s : %p\n", "fois", rechercher_dans_ArbreBK(arbre, "fois"));
    printf("recherche de %s : %p\n", "foie", rechercher_dans_ArbreBK(arbre, "foie"));
    printf("recherche de %s : %p\n", "qui", rechercher_dans_ArbreBK(arbre, "qui"));
    printf("recherche de %s : %p\n", "esta", rechercher_dans_ArbreBK(arbre, "esta"));
    printf("recherche de %s : %p\n", "quo", rechercher_dans_ArbreBK(arbre, "quo"));
    printf("recherche de %s : %p\n", "ville", rechercher_dans_ArbreBK(arbre, "ville"));
    printf("recherche de %s : %p\n", "foix", rechercher_dans_ArbreBK(arbre, "foix"));
    printf("recherche de %s : %p\n", "elle", rechercher_dans_ArbreBK(arbre, "elle"));
    printf("recherche de %s : %p\n", "foi", rechercher_dans_ArbreBK(arbre, "foi"));
    printf("recherche de %s : %p\n", "est", rechercher_dans_ArbreBK(arbre, "est"));
    printf("recherche de %s : %p\n", "que", rechercher_dans_ArbreBK(arbre, "que"));
    return 0;
}