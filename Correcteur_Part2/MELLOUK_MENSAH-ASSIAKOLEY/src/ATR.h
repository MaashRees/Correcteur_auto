/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 04-03-2022
* Modification(s) : 20-03-2022
                    10-03-2022*/


#ifndef __ATR__
#define __ATR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Listes.h"
#include "fichier.h"

typedef struct ntr{
    char racine; /* Caractère n-ieme d'un mot */
    struct ntr * fils; /* Arbre contenant les (n + 1)-ieme caracteres du mot */
    struct ntr * gauche; /* Arbre contenant les mots dont le caractere n-ieme est inferieur au caractère racine */
    struct ntr * droite; /* Arbre contenant les mots dont le caractere n-ieme est superieur au caractère racine */
} NTR, * ATR;


/*=====================Déclarations==========================*/

/*crée un arbre vide donc la racine est le caractère nul*/
ATR creer_ATR_vide(void);


/*==============================================================*/
/*===============================================================*/

/*Libère les noeuds de l'arbre "arbre"*/
void liberer_ATR(ATR * arbre);


/*==============================================================*/
/*==============================================================*/

/*Vérifie si l'arbre "arbre" est vide *
 *c'est à dire à sa racine on a le caractère vide *
 *et ces autres champs sont à NULL */
int est_vide_ATR(ATR arbre);


/*==============================================================*/
/*==============================================================*/

/*Se charge d'ajouter les lettres de "mot" *
 *dans l'arbre "arbre" à partir de la (cmp)-ième lettre */
int ajout(ATR * arbre, char * mot, int cmp);


/*Se charge de gérer l'insertion de "mot" dans l'arbre "arbre" *
 * à la bonne position selon l'ordre lexicographique en s'aidant *
 * de la fonction ajout */
int inserer_aux(ATR * arbre, char * mot, int cmp);


/*Fonction d'insertion générale d'un mot dans un dictionnaire "arbre"*/
int inserer_dans_ATR(ATR * arbre, char * mot);


/*==============================================================*/
/*===============================================================*/


/*Recherche "mot" dans "arbre"*/
int recherche(ATR arbre, char * mot, int cmp);


/*==============================================================*/
/*===============================================================*/

/*Raccorde l'arbre "droite" à l'arbre "arbre" pour empecher la perte *
 * non désirable de certains mots du dictionnaire */
int inserer_arbre(ATR * arbre, ATR droite);


/*Gère la suppression de "mot" dans l'arbre "arbre" : *
 *supprime les caractères juste nécessaires pour conserver *
 *les autres mots du dictionnaire*/
int supprimer_dans_ATR_aux(ATR * arbre, char * mot, int cmp);


/*Fonction de suppression générale de "mot" dans un dictionnaire "arbre"*/
void supprimer_dans_ATR(ATR * arbre, char * mot);


/*================================================================ */
/*==============================================================*/

/*Ecrit caractère par caractère dans "mot" les caractères contenues dans *
 *la "racine" de l'arbre puis affiche 'mot' quand il rencontre un caractère nul*
 *ainsi de suite jusqu'à avoir afficher tous les mots de l'arbre*/
void affiche_atr_aux(ATR arbre, char * mot, int cmp);


/*Fonction d'affichage générale des mots du dictionnaire "arbre"*/
void afficher_ATR(ATR arbre);


/*=================================================================*/
/*==============================================================*/


/*Gere la construction d'un arbre à partir d'un "fichier" contenant un dictionnaire*/
ATR remplis_arbre(FILE * fichier);


/*Implémentation de l'algorithme de recherche des mots mal orthographiées *
 * dans un fichier texte "a_corriger" selon le dictionnaire "arbre"*/
Liste correction(ATR arbre,FILE * a_corriger);

/*=================================================================*/


void correction1(ATR dico, Liste a_corriger);


#endif
