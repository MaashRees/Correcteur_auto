/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 20-04-2022
* Modification(s) : 24-04-2022*/

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



void ecrireArbre_BK(FILE *f, ArbreBK arbre){
    if(!arbre)
        return ;
    fprintf(f,"\tn%p [label=\"<filsG> |{ <valeur> %s | <Levenshtein> %d }| <frereD> \"];\n", (void *) arbre, arbre->mot,arbre->valeur);
    if(arbre->filsG){
        fprintf(f, "\tn%p:filsG:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->filsG);
        ecrireArbre_BK(f,arbre->filsG);
    }

    if(arbre->frereD){
        fprintf(f, "\tn%p:frereD:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->frereD);
        ecrireArbre_BK(f,arbre->frereD);
    }
}


void  dessine_BK(FILE *f, ArbreBK arbre) {
    ecrireDebut(f);
    ecrireArbre_BK(f , arbre);
    ecrireFin(f);
}

void  creePDF_ArbreBK(ArbreBK arbre) {
    FILE *out=fopen("arbre.dot" ,"w");
    if (out){
        dessine_BK(out ,arbre);
        fclose(out);
        system("dot -Tpdf arbre.dot -o arbre.pdf");
    }
    else
        fprintf(stderr, "fichier non trouvé\n");
}
