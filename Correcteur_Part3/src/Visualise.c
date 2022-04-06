/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 10-03-2022
* Modification(s) : 20-03-2022 
                    17-03-2022
                    15-03-2022*/

#include "Visualise.h"


void ecrireDebut(FILE *f){
    fprintf(f, "digraph  arbre {\n");
    fprintf(f, "\tnode [shape=record , height=.1 ]\n");
    fprintf(f, "\tedge [tailclip=false , arrowtail = dot , dir=both];\n\n");
}

void ecrireArbre(FILE *f, ATR arbre){
    if(!arbre)
        return ;
    if(arbre->racine == '\0')
        fprintf(f,"\tn%p [label=\"<gauche> | <valeur> %c | <fils> | <droit> \"];\n", (void *) arbre, '0');
    else
        fprintf(f,"\tn%p [label=\"<gauche> | <valeur> %c | <fils> | <droit> \"];\n", (void *) arbre, arbre->racine);
    if(arbre->gauche){
        fprintf(f, "\tn%p:gauche:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->gauche);
        ecrireArbre(f, arbre->gauche);
    }
    if(arbre->fils){
        fprintf(f, "\tn%p:fils:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->fils);
        ecrireArbre(f, arbre->fils);
    }
    if(arbre->droite){
        fprintf(f, "\tn%p:droit:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->droite);
        ecrireArbre(f, arbre->droite);
    }

}

void ecrireFin(FILE *f){
    fprintf(f, "}\n");
}

void  dessine(FILE *f, ATR arbre) {
    ecrireDebut(f);
    ecrireArbre(f , arbre);
    ecrireFin(f);
}



void  creePDF(ATR arbre) {
    FILE *out=fopen("arbre.dot" ,"w");
    if (out){
        dessine(out ,arbre);
        fclose(out);
        system("dot -Tpdf arbre.dot -o arbre.pdf");
    }
    else
        fprintf(stderr, "fichier non trouvé\n");
}

