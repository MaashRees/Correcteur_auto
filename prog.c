#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define INFINI 10000000


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
        free(tmp->mot);
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

void ecrireDebut(FILE *f){
    fprintf(f, "digraph  arbre {\n");
    fprintf(f, "\tnode [shape=record , height=.1 ]\n");
    fprintf(f, "\tedge [tailclip=false , arrowtail = dot , dir=both];\n\n");
}

void ecrireArbre(FILE *f, ArbreBK arbre){
    if(!arbre)
        return ;
    if(arbre->mot == "\0")
        fprintf(f,"\tn%p [label=\"<filsG> | <valeur> %c | <frereD> \"];\n", (void *) arbre, '0');
    else
        fprintf(f,"\tn%p [label=\"<filsG> | <valeur> %s | <valeur> %d | <frereD> \"];\n", (void *) arbre, arbre->mot,arbre->valeur);
    if(arbre->filsG){
        fprintf(f, "\tn%p:filsG:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->filsG);
        ecrireArbre(f,arbre->filsG);
    }

    if(arbre->frereD){
        fprintf(f, "\tn%p:frereD:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->frereD);
        ecrireArbre(f,arbre->frereD);
    }
}

void ecrireFin(FILE *f){
    fprintf(f, "}\n");
}

void  dessine(FILE *f, ArbreBK arbre) {
    ecrireDebut(f);
    ecrireArbre(f , arbre);
    ecrireFin(f);
}



void  creePDF(ArbreBK arbre) {
    FILE *out=fopen("arbre.dot" ,"w");
    if (out){
        dessine(out ,arbre);
        fclose(out);
        system("dot -Tpdf arbre.dot -o arbre.pdf");
    }
    else
        fprintf(stderr, "fichier non trouvé\n");
}



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


void Propose_correction_aux(ArbreBK arbre, Liste * lstmot, char * mot_a_corriger, int * dmin){
    
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
        
         Propose_correction_aux(arbre->filsG, lstmot, mot_a_corriger, dmin);
        
        Propose_correction_aux(arbre->frereD, lstmot, mot_a_corriger, dmin);
    }
    }



Liste Propose_correction(ArbreBK arbre, char * mot_a_corriger, int *dmin){

    assert(strlen(mot_a_corriger) > 0);
     char mot[26]; /* Chaine de caractères contenant les mots de l'arbre un par un*/
    int cmp;
    Liste lstmot;
    lstmot = NULL;

    cmp = 0;
    if(arbre == NULL){
        return NULL;
    } else {
             Propose_correction_aux(arbre->filsG, &lstmot, mot_a_corriger, dmin);
        Propose_correction_aux(arbre->frereD, &lstmot, mot_a_corriger, dmin);

    }

    return lstmot;
}


int main(int argc, char * argv[]){


    ArbreBK arbre = NULL;

    FILE * dico;
    FILE * text;


    int dmin;

    
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

    if(dico){
        arbre = creer_ArbreBK(dico);
        creePDF(arbre);
    }

    
    Liste erreurs;

      afficher_ArbreBK(arbre);
    // =====================recuperation des mots a corriger 
    erreurs = correctionBK(arbre,text);

    afficher_Liste(erreurs);

   
   
    printf("\n====================================================================\n\n");
    printf("======================Entrée de correction ===========================\n\n");
       

    Liste tmp, lstcorrections;
     
    tmp = erreurs;
    
    while(tmp){
        dmin = INFINI;
                 lstcorrections = Propose_correction(arbre, tmp->mot, &dmin);

        printf("\n==========================================================\n\n");
        printf("Propositions de correction de  : %s\n\n", tmp->mot);
        afficher_Liste(lstcorrections);

        tmp = tmp->suivant;
        
        liberer_Liste(&lstcorrections);
    }
    printf("====================== Sortie de correction =====================\n\n");


    liberer_ArbreBK(&arbre);

    return 0;
}