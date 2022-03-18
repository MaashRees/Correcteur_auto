#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct cellule{
  char *mot;
  struct cellule *suivant;
}Cellule, *Liste ;


typedef struct ntr{
    char racine;
    struct ntr * fils;
    struct ntr * fg;
    struct ntr * fd;
} NTR, * ATR;



Cellule * allouer_Cellule(char*mot){

  Cellule * new = (Cellule *) malloc(sizeof(Cellule));
  if(new){
      new->mot = (char *) malloc(sizeof(char)*strlen(mot)+1);
      if(!new->mot)
          return NULL;
      strcpy(new->mot, mot);
      new->suivant = NULL;
  }
  return new;
}

int inserer_en_tete(Liste * L, char * mot){
  Liste tmp;
  Cellule * new = allouer_Cellule(mot);

  if(new == NULL){/* l'allocation de la nouvelle cellule a fail*/
      return 0;
  }

  if(!*L){/* La liste est vide*/
      *L = new;
  }
  else{
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
    free(tmp);
  }
  free(*L);
}


void afficher_Liste(Liste L){
  while(L){
    printf("%s ->",L->mot);
    L = L->suivant;
  }

}


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


void supprimer_dans_ATR(ATR * A, char * mot){

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
        affiche_atr_aux(A, &mot, cmp);
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



void ecrireDebut(FILE *f){
    fprintf(f, "digraph  arbre {\n");
    fprintf(f, "\tnode [shape=record , height=.1 ]\n");
    fprintf(f, "\tedge [tailclip=false , arrowtail = dot , dir=both];\n\n");
}

void ecrireArbre(FILE *f, ATR a){
    if(!a)
        return ;
    if(a->racine == '\0')
        fprintf(f,"\tn%p [label=\"<gauche> | <valeur> %c | <fils> | <droit> \"];\n", (void *) a, '0');
    else
        fprintf(f,"\tn%p [label=\"<gauche> | <valeur> %c | <fils> | <droit> \"];\n", (void *) a, a->racine);
    if(a->fg){
        fprintf(f, "\tn%p:gauche:c -> n%p:valeur;\n", (void *) a, (void *) a->fg);
        ecrireArbre(f, a->fg);
    }
    if(a->fils){
        fprintf(f, "\tn%p:fils:c -> n%p:valeur;\n", (void *) a, (void *) a->fils);
        ecrireArbre(f, a->fils);
    }
    if(a->fd){
        fprintf(f, "\tn%p:droit:c -> n%p:valeur;\n", (void *) a, (void *) a->fd);
        ecrireArbre(f, a->fd);
    }

}

void ecrireFin(FILE *f){
    fprintf(f, "}\n");
}

void  dessine(FILE *f, ATR a) {
    ecrireDebut(f);
    ecrireArbre(f , a);
    ecrireFin(f);
}



void  creePDF(ATR a) {
    FILE *out=fopen("arbre.dot" ,"w");
    if (out){
        dessine(out ,a);
        fclose(out);
        system("dot -Tpdf arbre.dot -o arbre.pdf");
    }
    else
        fprintf(stderr, "fichier non trouvé\n");
}


int main(int argc, char * argv[]){

    ATR arbre;
    Liste erreurs;
    int insert;

    FILE * text;
    FILE * dico;

    arbre = creer_ATR_vide();

    text = fopen(argv[1], "r");
    dico = fopen(argv[2], "r");
    if(dico)
        arbre = remplis_arbre(dico);
    //afficher_ATR(arbre);
    creePDF(arbre);
    printf("____________________________________________________________\n");
    afficher_ATR(arbre);
    /*if(text && arbre)
        erreurs = correction(arbre, text);
    
    if(erreurs){
        printf("Mots mal orthographiés : \n");
        afficher_Liste(erreurs);
    }*/
    return 0;   
}