/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 24-04-2022*/

#ifndef __LISTES__
#define __LISTES__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct cellule{
  char *mot; /*mot contenue dans une cellule*/
  struct cellule *suivant; /*pointeur permettant de relié les cellules entre elles*/
}Cellule, *Liste ;


/*=================Declaration=======================*/


/*
Fonction d'allocation permettant de crée la place nécessaire dans la memoire pour stocké une cellule
associant a son champs mot, mot(passé en paramètre). Renvoie l'adresse de la cellule crée.
param value : char *
return value : Cellule *
*/
Cellule * allouer_Cellule(char*mot);


/*======================================================*/
/*====================================================*/

/*
Fonction qui insere en tête ces nouvelles cellules, renvoie 1 si l'insertion c'est correctement passé, 0 sinon.
param value : Liste *, char *
return value : int
*/
int inserer_en_tete(Liste * L, char * mot);

/*====================================================*/
/*====================================================*/

/*
Fonction qui permet de libérer entièrement l'espace mémoire occupé par la Liste L
param value : Liste *
return value : void
*/
void liberer_Liste(Liste * L);

/*=====================================================*/
/*====================================================*/

/*
Fonction qui affiche tout les mots que contient la liste chainée L
param value : Liste
return value : void
*/
void afficher_Liste(Liste L);

/*====================================================*/

#endif