//#include <Levenshtein.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct cellule{
  char *mot; /*mot contenue dans une cellule*/
  struct cellule *suivant; /*pointeur permettant de relié les cellules entre elles*/
}Cellule, *Liste ;



typedef struct ntr{
    char racine; /* Caractère n-ieme d'un mot */
    struct ntr * fils; /* Arbre contenant les (n + 1)-ieme caracteres du mot */
    struct ntr * gauche; /* Arbre contenant les mots dont le caractere n-ieme est inferieur au caractère racine */
    struct ntr * droite; /* Arbre contenant les mots dont le caractere n-ieme est superieur au caractère racine */
} NTR, * ATR;








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

int inserer_en_fin(Liste * L, char * mot){
    assert(strlen(mot) > 0);

    Liste tmp;
    Cellule * new;
    
    new = allouer_Cellule(mot);

    if(new == NULL){/* l'allocation de la nouvelle cellule a échoué*/
        return 0;
    }

    if(!*L){/* La liste est vide*/
        *L = new;
        return 1;
    }
    tmp = *L;
    while(tmp->suivant != NULL){
        tmp = tmp->suivant;
        
    }
    tmp->suivant = new;
    
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

    printf("\tMot(s) mal orthographié(s)\n");
    while(L){
        printf("%s\n",L->mot); /*affichage du mot contenu dans la cellule pointée*/
        L = L->suivant;
    }
}


















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







































#ifndef MIN
#define MIN(x,y) (((x)<(y))? (x) : (y))
#endif // MIN

#define INFINI 1000000000




int Levensthein(char *un, char *deux){

    int tab[strlen(un)][strlen(deux)];

    int i,j, cout;

    /*remplissage colonne*/
    for(i = 0; i < strlen(un); i++){
        tab[i][0] = i;
    }

    /*remplissage ligne*/
    for(j = 0; j < strlen(deux); j++){
        tab[0][j] = j;
    }

    /*remplissage du tableau*/

    for(i = 1; i < strlen(un); i++){
        for(j = 1; j < strlen(deux); j++){

        /*si meme cunractère*/
        if(un[i-1] == deux[j-1]){
            cout = 0;
        }else{
            cout = 1;
        }

        tab[i][j] =  MIN(MIN(tab[i-1][j] + 1, tab[i][j-1] + 1), tab[i-1][j-1] + cout);
        }
    }

    /*affichge du tableau*/
    for(i = 0; i < strlen(un); i++){
        for(j = 0; j < strlen(deux); j++){
        //printf("%d ",tab[i][j]);
        }
        //printf("\n");
        }

    return tab[strlen(un)-1][strlen(deux)-1];

}



void recup_dico_in_liste_aux(ATR arbre, char * mot, int cmp, Liste * lstmot){

    assert(cmp >= 0);
    assert(cmp <= strlen(mot));

    if(arbre){
        if(arbre->gauche){
            recup_dico_in_liste_aux(arbre->gauche, mot, cmp, lstmot);
        }
        if(arbre->racine != '\0'){
            /*extraction du cmp-ieme caractère du mot de l'arbre*/
            mot[cmp] = arbre->racine;
            recup_dico_in_liste_aux(arbre->fils, mot, cmp + 1, lstmot);
        } else {
            /*Mot complet - on est à la fin de mot*/
            mot[cmp] = '\0';
            printf("%s\n", mot);
            if(*lstmot == NULL){
                *lstmot = allouer_Cellule(mot);
            }else{
                if(inserer_en_fin(lstmot, mot) == 0)
                    printf("insertion de %s non éffectué\n", mot);
            }
            
        }
        recup_dico_in_liste_aux(arbre->droite, mot, cmp, lstmot);
    }
}

Liste recup_dico_in_liste(ATR arbre){

    char mot[26]; /* Chaine de caractères contenant les mots de l'arbre un par un*/
    int cmp;
    Liste lstmot;

    lstmot = NULL;

    cmp = 0;
    if(arbre == NULL){
        return NULL;
    } else {
        printf("\n============================================\n");
        printf("Recuperer dico dans liste :\n\n");
        recup_dico_in_liste_aux(arbre, mot, cmp, &lstmot);
        afficher_Liste(lstmot);
        printf("\n=============================================\n\n");
    }
    
    return lstmot;
}


Liste algo2(FILE * dico, char * mot){
    Liste corrections;
    int dmin;
    int d;

    char m[20];
    Liste tmp;

    dmin = INFINI;
    corrections = allouer_Cellule(" ");

    while(fscanf(dico,"%s",m)!=EOF){
        /*insertion du mot recupere dans l'arbre*/
        d = Levensthein(m, mot);
        printf("Levenshtein : %s -> %s  : %d\n", mot, m, d);
        
        
        if(d <= dmin){
            if(d < dmin ){
                dmin = d;
                /*vider corrections*/
                liberer_Liste(&corrections);
                corrections = NULL;
            }
            if(corrections == NULL){
                corrections = allouer_Cellule(m);
            } else{
                inserer_en_tete(&corrections, m);
            }
            
        } 
        
        /*pour regler Lazare dans laz
        else {
            int lettre;
            int ok;
            lettre = 0;
            
            while(mot[lettre] && m[lettre] && mot[lettre] == m[lettre]){
                lettre += 1;
            }
            ok = (strlen(mot) - strlen(m) <= 0)? (strlen(m) - lettre) : (lettre - strlen(mot));
            printf("lettre : %d ok : %d\n", lettre, ok);
            if(ok <= 3 && (strlen(mot) - strlen(m) >= -3 || strlen(mot) - strlen(m) <= 3)){
                if(lettre != 0){
                    if(corrections == NULL){
                        corrections = allouer_Cellule(m);
                    } else{
                        inserer_en_tete(&corrections, m);
                    }
                }
            
            }
        }*/
    }
    rewind(dico);
    return corrections;
    
    
}


int main(int argc, char * argv[]){

    ATR arbre;
    Liste lstmot;
    /*Liste corrections;*/
    Liste erreurs; 

    FILE * text;
    FILE * dico;

    arbre = creer_ATR_vide();

    text = fopen(argv[1], "r");
    dico = fopen(argv[2], "r");
    if(dico)
        arbre = remplis_arbre(dico);

    afficher_ATR(arbre);
    
    lstmot = recup_dico_in_liste(arbre);

    printf("======================entree de correction ===========================\n\n");

    erreurs = correction(arbre, text);
    
    printf("Mots mal ortho :\n\n");

    afficher_Liste(erreurs);

    printf("======================sortie de correction ===========================\n\n");
    Liste tmp = erreurs;
    while(tmp){
        Liste corrections = algo2(dico, tmp->mot);
        printf("\n==========================================================\n\n");
        printf("Propositions de corrections de  :%s\n\n", tmp->mot);
        afficher_Liste(corrections);
        
        tmp = tmp->suivant;
        printf("======================fin poropo==============\n\n");
        liberer_Liste(&corrections);
    }

    liberer_Liste(&erreurs);
    liberer_Liste(&lstmot);
    liberer_ATR(&arbre);

    fclose(text);
    fclose(dico);
    
    return 0;
}
