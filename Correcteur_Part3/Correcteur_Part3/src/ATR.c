/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 17-04-2022
*                   03-04-2022*/

#include "ATR.h"


ATR creer_ATR_vide(void){
    ATR lexique;
    lexique = (NTR *) malloc(sizeof(NTR));
    if(lexique){
        lexique->racine = '\0';
        lexique->fils = NULL;
        lexique->gauche = NULL;
        lexique->droite = NULL;
    }
    return lexique;
}


void liberer_ATR(ATR * arbre){
    ATR tmpg, tmpf, tmpd;

    if(*arbre){
        tmpg = (*arbre)->gauche;
        tmpf = (*arbre)->fils;
        tmpd = (*arbre)->droite;

        liberer_ATR(&tmpg);
        liberer_ATR(&tmpf);
        liberer_ATR(&tmpd);

        free(*arbre);

        *arbre = NULL;
    }
}

/*=============================================================================*/

int est_vide_ATR(ATR arbre){
    assert(arbre != NULL);

    if(arbre->racine == '\0' && arbre->droite == NULL) /*arbre vide*/
        return 1;

    return 0;
}

/*=============================================================================*/


int ajout(ATR * arbre, char * mot, int cmp){

    assert(cmp >= 0);
    assert(cmp <= strlen(mot));

    if(*arbre == NULL){
        *arbre = creer_ATR_vide();
        if((*arbre) == NULL) /* Allocation non effectuee */
            return 0;
    }
    if(cmp == strlen(mot)) /* On a insere le mot */
            return 1;

    /* ajout du cmp-ieme caractère dans l'arbre */
    (*arbre)->racine = mot[cmp];

    return ajout(&((*arbre)->fils), mot, cmp + 1);
}


int inserer_aux(ATR * arbre, char * mot, int cmp){
    assert(cmp >= 0);
    assert(cmp <= strlen(mot));

    ATR tmp;
    if(cmp == strlen(mot)){
        /*si le dictionnaire n'est pas dans l'ordre lexicographique*/
        if((*arbre)->racine != '\0'){
            tmp = creer_ATR_vide();
            tmp->droite = (*arbre);
            (*arbre) = tmp;
            return 1;
        }

        /*Mot déjà dans le dictionnaire*/
        return 0;
    }

    /* arbre vide mais on n'a pas commencer d'insérer le mot */
    if(*arbre == NULL){
        return ajout(arbre, mot, cmp);
    }

    /* le mot n'existe pas en totalité dans l'arbre */
    if((*arbre)->racine == '\0'){
        return inserer_aux(&((*arbre)->droite), mot, cmp);
    } else {

        if((*arbre)->racine == mot[cmp]){
            return inserer_aux(&((*arbre)->fils), mot, cmp  + 1);
        } else if((*arbre)->racine < mot[cmp]){ /*mot supérieur*/
            return inserer_aux(&((*arbre)->droite), mot, cmp);
        } else { /*mot inferieur*/
            return inserer_aux(&((*arbre)->gauche), mot, cmp);
        }
    }

    return 0;
}

int inserer_dans_ATR(ATR * arbre, char * mot){

    assert(strlen(mot) > 0);
    int cmp;

    cmp = 0;
    if(*arbre){

        if((*arbre)->racine == '\0'){
            /*Insertion du premier mot*/
            (*arbre)->racine = mot[cmp];
            if((*arbre)->fils == NULL && strlen(mot) == 1){ /*pour eviter la segmentation*/
                (*arbre)->fils = creer_ATR_vide();
            }
            return inserer_aux(&((*arbre)->fils), mot, cmp+1);
        }

        return inserer_aux(&((*arbre)), mot, cmp);
    }

    return 0;
}

/*======================================================================*/

int recherche(ATR arbre, char * mot, int cmp){

    assert(cmp >= 0);
    assert(cmp <= strlen(mot));

    if(arbre == NULL){
        return 0;
    }

    if((cmp == strlen(mot))){
        if(arbre->racine == '\0'){
            /*Mot trouvé*/
            return 1;
        }
        return 0;
    }

    /*Mot non trouvé à partir du cmp-ieme caractère*/
    if(est_vide_ATR(arbre)){
        return 0;
    }

    if((arbre->racine) == mot[cmp]){
        return recherche(arbre->fils, mot, cmp + 1);
    } else if((arbre->racine) > mot[cmp]){
        return recherche(arbre->gauche, mot, cmp);
    } else {
        return recherche(arbre->droite, mot, cmp);
    }
    return 0;
}

/*=========================================================================*/

int inserer_arbre(ATR * arbre, ATR droite){

    assert(*arbre != NULL);

    if(droite == NULL){
        return 1;
    }
    if((*arbre)->droite == NULL){
        (*arbre)->droite = droite;
        return 1;
    }
    return inserer_arbre(&((*arbre)->droite), droite);
}

int supprimer_dans_ATR_aux(ATR * arbre, char * mot, int cmp){

    assert(cmp >= 0);
    assert(cmp <= strlen(mot));

    int sup_l;
    ATR tmp;

    if(*arbre == NULL){
        return 0;
    }

    if(cmp == strlen(mot)){
        if((*arbre)->racine == '\0'){
            /*Mot trouvé et Suppression caractere vide*/
            tmp = (*arbre)->droite;
            free((*arbre));
            (*arbre) = tmp;
            return 1;
        }
        /*Mot non trouvé*/
        return 0;
    }

    /* le mot n'existe pas en totalité dans l'arbre -> Mot non trouvé*/
    if((*arbre)->racine == '\0' && (*arbre)->droite == NULL)
        return 0;

    if((*arbre)->racine == mot[cmp]){
        /*Suppression du (cmp+1)-ieme du mot*/
        sup_l = supprimer_dans_ATR_aux(&(*arbre)->fils, mot, cmp + 1);

        if(sup_l){
            if((*arbre)->fils){
                /*on a restructuré l'arbre apres le mot à supprimer *
                 *exemple de la suppression de "de" du dico_1 alors qu'on a dans l'arbre *
                 *"denise" on a fait remonter "n" au lieu de mettre à null*/

                return 1;
            }

            tmp = *arbre;

            if((*arbre)->gauche){
                /*Reconstitution de l'arbre en branchant les mots de gauche et de droite *
                 *inserer de droite dans gauche*/
                inserer_arbre(&((*arbre)->gauche), (*arbre)->droite);
                (*arbre) = (*arbre)->gauche;

            } else{
                (*arbre) = (*arbre)->droite;
            }

            tmp->gauche = tmp->droite = tmp->fils= NULL;
            free(tmp);
            tmp = NULL;
        }
        return sup_l;

    } else if((*arbre)->racine > mot[cmp]){
        return supprimer_dans_ATR_aux(&((*arbre)->gauche), mot, cmp);

    } else{
        return supprimer_dans_ATR_aux(&((*arbre)->droite), mot, cmp);
    }

    return 0;

}

void supprimer_dans_ATR(ATR * arbre, char * mot){

    assert(strlen(mot) > 0);
    int cmp, sup;
    cmp = 0;
    if(*arbre){
        printf("mot à supprimer : %s\n\n", mot);
        sup = supprimer_dans_ATR_aux(arbre, mot, cmp);
        if(sup){
            printf("\nMot trouvé et supprimé\n\n\n");
        } else{
            printf("\nMot non trouvé\n\n\n");
        }
    }
}

/*=======================================================================*/


void affiche_atr_aux(ATR arbre, char * mot, int cmp){

    assert(cmp >= 0);
    assert(cmp <= strlen(mot));

    if(arbre){
        if(arbre->gauche){
            affiche_atr_aux(arbre->gauche, mot, cmp);
        }
        if(arbre->racine != '\0'){
            /*extraction du cmp-ieme caractère du mot de l'arbre*/
            mot[cmp] = arbre->racine;
            affiche_atr_aux(arbre->fils, mot, cmp + 1);
        } else {
            /*Mot complet - on est à la fin de mot*/
            mot[cmp] = '\0';
            printf("%s\n", mot);
        }
        affiche_atr_aux(arbre->droite, mot, cmp);
    }
}

void afficher_ATR(ATR arbre){

    char mot[26]; /* Chaine de caractères contenant les mots de l'arbre un par un*/
    int cmp;

    cmp = 0;
    if(arbre == NULL){
        return ;
    } else {
        printf("\n============================================\n");
        printf("Affichage du dictionnaire choisi :\n\n");
        affiche_atr_aux(arbre, mot, cmp);
        printf("\n=============================================\n\n");
    }
}

/*====================================================================*/

ATR remplis_arbre(FILE * fichier){

    assert(fichier != NULL);

    char mot[20];
    ATR arbre;
    arbre = creer_ATR_vide();

    while(fscanf(fichier,"%s",mot)!=EOF){
        /*insertion du mot recupere dans l'arbre*/
        inserer_dans_ATR(&arbre, mot);
    }
    rewind(fichier);
    return arbre;
}

/*=====================================================================*/


Liste correction(ATR dico, FILE * a_corriger){
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

        if(recherche(dico, mot, 0) == 0){
            /*inserer m en tete de la liste chainee erreurs*/
            inserer_en_tete(&erreur, mot);
        }

    }
    rewind(file);
    return erreur;
}
