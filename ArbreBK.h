/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation :
* Modification(s) : 17-04-2022
                    */


#ifndef __ARBREBK__
#define __ARBREBK__

#include "Listes.h"
#include "fichier.h"
#include "Levenshtein.h"

typedef struct noeudBK {
    char * mot; /* mot que contient un noeud de l'arbre */
    int valeur; /* distance de Levenshtein entre ce mot et son noeud parent */
    struct noeudBK * filsG;
    struct noeudBK * frereD;
} NoeudBK, * ArbreBK;

/* Fonction d'allocation d'un noeud d'un arbreBK */
NoeudBK * alloue_ArbreBK(char * mot);

/* Fonction auxiliaire d'insertion */
int inserer_dans_ArbreBK_aux(ArbreBK *A, char * mot, int dist);

/* Fonction d'insertion permettant l'insertion d'un mot dans un abreBK  */
int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

/* Fonction auxiliaire de recherche */
Liste rechercher_dans_ArbreBK_aux(ArbreBK A, char * mot, int dist);

/* Fonction de recherche d'un mot dans un arbreBK */
Liste rechercher_dans_ArbreBK(ArbreBK A, char * mot);

/* Fonction qui remplit un arbreBK à partir d'un dictionnaire */
ArbreBK creer_ArbreBK(FILE * dico);

/* Fonction de libération de l'abreBK */
void liberer_ArbreBK(ArbreBK * A);

/* Fonction auxiliaire d'affichage */
void afficher_ArbreBK_aux(ArbreBK A, int rang);

/* Fonction qui affiche les mots composant un arbreBK */
void afficher_ArbreBK(ArbreBK A);

/* Fonction qui recherche les mots dit mal orthographiés */
Liste correctionBK(ArbreBK dico, FILE * a_corriger);

/* Fonction auxiliaire de proposion de correction */
void Propose_correction_auxBK(ArbreBK arbre, Liste * lstmot, char * mot_a_corriger, int * dmin);

/* Fonction qui propose des mots proches comme correction d'un mot */
Liste Propose_correctionBK(ArbreBK arbre, char * mot_a_corriger, int *dmin);



#endif
