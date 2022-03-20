#include "Visualise.h"


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

