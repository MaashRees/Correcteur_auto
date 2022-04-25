/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 03-04-2022*/

#include "ArbreBK.h"

/*
 Fonction d'allocation qui renvoie l'adresse d'un NoeudBK en lui ajoutant
le mot passé en paramètre dans son champ mot.

param value : char *

return value : NULL ou NoeudBK *

*/
NoeudBK * alloue_ArbreBK(char * mot){

    NoeudBK * n;

    /* le mot à recherché contient au moins une lettre */
    assert(strlen(mot) > 0);

    n = (NoeudBK *)malloc(sizeof(NoeudBK));


    if(n != NULL){/* si l'allocation réussi */

        n->mot = (char *) malloc(sizeof(char) * (strlen(mot) + 1));

        if(n->mot != NULL){ /* si l'allocation réussi */

            strcpy(n->mot, mot);
        }

        n->filsG = NULL;
        n->frereD = NULL;
        n->valeur = 0;
    }
    return n;
}


/*
Fonction d'insertion auxiliaire, qui parcours l'arbre et selon la distance de
Levenshtein calculé, descend dans le filsG ou bien dans le frereD. Une fois la
bonne position trouvé insère un nouveau noeud contenant le mot passé en paramètre.
Renvoie 1 si l'insertion c'est correctement passé, 0 sinon.

param A : ArbrebK *
param mot : char *
param dist : int

return value : 0 ou 1 (int)

*/
int inserer_dans_ArbreBK_aux(ArbreBK *A, char * mot, int dist){

    /* cas ou le noeud rencontré est vide */
    if(*A == NULL){

        (*A) = alloue_ArbreBK(mot);

        if(*A == NULL){

            return 0;

        } else{

            (*A)->valeur = dist;

            return 1;
        }
    }

    /* le mot à insérer est déjà dans l'arbre */
    if(Levenshtein((*A)->mot, mot) == 0){

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
    if((*A)->valeur > dist){

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



/*
Fonction d'insertion qui traite plusieurs cas de base, comme l'arbre est vide,
le mot à insérer est la racine etc... Si ces cas de base ne sont pas rencontré
alors on appel récursivement la fonction d'insertion auxiliaire pour placer
le mot au bon endroit dans l'arbre. Renvoie 1 si l'insertion c'est correctement
passé, 0 sinon.

param A : ArbrebK *
param mot : char *
param dist : int

return value : 0 ou 1 (int)

*/
int inserer_dans_ArbreBK(ArbreBK * A, char * mot){

    int L;

    /* le mot qu'on insère contient au moins une lettre */
    assert(strlen(mot) > 0);

    /* cas où l'abreBK est vide, on insère la racine */
    if(*A == NULL){

        *A = alloue_ArbreBK(mot);

        if(*A == NULL){

            return 0;

        } else{

            (*A)->valeur = 0;

            return 1;
        }
    }

    /* cas où le mot à insérer est enfaite la racine de l'abre */
    if((*A)->mot && Levenshtein((*A)->mot, mot) == 0){

        printf("mot existe deja\n");

        return 0;
    }

    /* calcule de la distance de Levenshtei entre la racine et le mot à insérer */
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


/*
Fonction de recherche auxiliaire qui parcours l'arbreBK selon la distance de
Levenshtein calculé. Renvoie une liste contenant le mot recherché
si trouvé, NULL sinon.

param A : ArbrebK *
param mot : char *
param dist : int

return value : Liste ou NULL

*/
Liste rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, int dist){

    if(A == NULL){
        return NULL;
    }

    if(A->valeur == dist){ /* mot est dans cette partie de l'arbre*/

        /* on rencontre le mot, on le renvoie */
        if(Levenshtein(A->mot, mot) == 0){

            Liste new = allouer_Cellule(mot);

            return new;

        /* sinon on parcours le filsG */
        } else{

            dist = Levenshtein(A->mot, mot);

            return rechercher_dans_ArbreBK_aux(A->filsG, mot, dist);
        }

    } else if(A->valeur > dist){

        return NULL;

    /* parcours le frereD */
    } else{

        return rechercher_dans_ArbreBK_aux(A->frereD, mot, dist);
    }

    return NULL;
}


/*
Fonction de recherche qui traite plusieurs cas de base, comme l'arbre est vide,
le mot à trouvé est la racine etc... Si ces cas de base ne sont pas rencontré
alors on appel récursivement la fonction de recherche auxiliaire pour parcourir
le reste de l'arbre. Renvoie une liste contenant le mot recherché si trouvé,
NULL sinon.

param A : ArbrebK *
param mot : char *


return value : Liste ou NULL

*/
Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot){

    /* le mot à recherché contient au moins une lettre */
    assert(strlen(mot) > 0);

    /* cas où l'arbre est vide */
    if(A == NULL){

        return NULL;
    }

    /* cas où le mot recherché se trouve à la racine */
    if(strcmp(A->mot, mot) == 0){

        Liste new = allouer_Cellule(mot);

        return new;
    }

    int L = Levenshtein(A->mot, mot);

    /* cas où l'arbres est uniquement composé de la racine */
    if(A->valeur == 0 && A->filsG == NULL){

        return NULL;
    }

    return rechercher_dans_ArbreBK_aux(A->filsG, mot, L);
}


/*
Fonction qui creer et remplis un arbreBK. Elle parcours un dictionnaire,
puis pour chaque mot rencontré, l'insère dans celui-ci puis le renvoie.

param dico : FILE *

return value : ArbreBK

*/
ArbreBK creer_ArbreBK(FILE * dico){

    assert(dico != NULL);

    char mot[20];
    ArbreBK arbre;

    arbre = NULL;

    while(fscanf(dico,"%s",mot)!=EOF){

        /*insertion du mot recupere dans l'arbre*/
        inserer_dans_ArbreBK(&arbre, mot);
    }

    /* remet au départ la tête de lecture */
    rewind(dico);

    return arbre;
}


/*
Fonction de libération, qui effectue un parcours de l'arbre et libère
chacun de ces noeuds.

param A : ArbreBK *

*/
void liberer_ArbreBK(ArbreBK * A){

    if(*A != NULL){

        /* on rencontre une feuille */
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


/*
Fonction auxiliaire d'affichage qui effectue un parcours préfixe des sous-arbres
de A.

param A :  ArbreBK
param rang : int

*/
void afficher_ArbreBK_aux(ArbreBK A, int rang){

    int i;

    if(A){

        for(i = 0; i < rang; i++){

                printf("\t");

        }
        printf("|--%d-->\t%s\n", A->valeur, A->mot);
        afficher_ArbreBK_aux(A->filsG, rang + 1);
        afficher_ArbreBK_aux(A->frereD, rang);
    }
}


/*
Fonction qui effectue un parcours prefixe de l'arbreBK et l'affiche
sur la sortie standart

param A : ArbreBK

return value : ArbreBK

*/
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



/*
Fonction qui effectue un parcours du texte a_corriger, qui pour chacun des
mots rencontrés effectue une recherche dans l'arbreBK. Si la recherche renvoie
NULL, le mot n'existe pas dans l'arbre, on l'insère dans la liste correction.
Elle renvoie une liste contenant tous les mots du texte a_corriger non présent
dans l'arbre.

param A : ArbreBK
param a_corriger : FILE *

return value : Liste

*/
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

/*
Fonction qui remplie la liste lstmot de tout les mots considérer comme proche
du mot_a_corriger selon le calcul de la distance de Levenshtein

param arbre : ArbreBK
param lstmot : Liste *
param mot_a_corriger : char *
param dmin : int *


*/
void Propose_correction_auxBK(ArbreBK arbre, Liste * lstmot, char * mot_a_corriger, int * dmin){

    assert(strlen(mot_a_corriger) > 0);
    assert(*dmin >= 0);

    int d;

    if(!arbre) return ;

    if(arbre){


            /* Algorithme de recupération des propositions de corrections */

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


/*
Fonction qui renvoie une liste contenant tous les mots qui sont
susceptibles d'être une correction pour le mot_a_corriger passé en argument.
Elle appel la fonction auxiliaire Propose_correction_auxBK
qui permet cette recherche.

param arbre : ArbreBK
param mot_a_corriger : char *
param dmin : int *

return value : Liste

*/
Liste Propose_correctionBK(ArbreBK arbre, char * mot_a_corriger, int *dmin){

    assert(strlen(mot_a_corriger) > 0);


    Liste lstmot;

    lstmot = NULL;


    if(arbre == NULL){

        return NULL;

    } else {

        Propose_correction_auxBK(arbre->filsG, &lstmot, mot_a_corriger, dmin);

        Propose_correction_auxBK(arbre->frereD, &lstmot, mot_a_corriger, dmin);

    }

    return lstmot;
}
