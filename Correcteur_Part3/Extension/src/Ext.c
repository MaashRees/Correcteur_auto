/* Auteurs : Imân MELLOUK
             Ako Seer Harley MENSAH-ASSIAKOLEYASSIAKOLEY
* Creation : 02-04-2022
* Modification(s) : 03-04-2022*/
#include "Ext.h"



static char cor[12] = "corriger.txt";/*Nom du fichier corrigé*/

/*Fonction demandant à l'utilisateur de choisir une proposition de correction ou encore si il ne veut pas le corriger

param mot : char * (mot a corriger)

param propositions : Liste (Liste de propositions de correction

return Value : char * (correction du mot ou NULL si l'utilisateur ne veut pas de correction)
*/
char * fonction_corrige_ou_non(char * mot, const Liste propositions){
    Liste tmp, tmp2;
    int num, choix;
    tmp = propositions;
    tmp2 = propositions;
    num = 0;
    printf("Propositions de corrections du mot : %s\n==================================================\n", mot);
    while(tmp){
        printf("%d : %s\n",num, tmp->mot); /*affichage du mot contenu dans la cellule pointée*/
        tmp = tmp->suivant;
        num ++;
    }
    printf("\n%d : Ignorer(Pas de corrections)\n", num);
    printf("\nVeuillez faire un choix de propositions : ");
    scanf("%d", &choix);
    if(choix == num){
        return NULL;
    } else if(choix > num){
        printf("\nMauvais choix, mot non corriger\n");
        return NULL;
    } else{
        num = 0;
        while(num < choix){
            tmp2 = tmp2->suivant;
            num++;
        }
        return tmp2->mot;
    }
}


/*Fonction se chargeant de réécrir un fichier in  en
 le corrigeant par rapport a un dictionnaire donné et le réécrit dans un fichier 'corriger.txt"

 param in : FILE * (flux d'octet désignant le texte à corriger)
 param dico : FILE * (ficchier contenant un dictionnaire )

 retun value : int (1 si tout s'est bien passé ou 0 si non);
 */
int correction_tmp_reel(FILE * in, FILE * dico){
    ArbreBK arbre;

    int dmin;
    FILE * corriger; /*fichier ou sera enregistré le texte corrigé*/
    char mot[26]; 
    char  * dest; /*chaine contenant le mot formé sans majuscule*/
    char * dest2; /*chaine contenant le mot formé sans caractere special*/
    char c;
    int cmp; /*entier servant d'indice pour 'mot'*/
    Liste mot_trouve; /*liste contenant le mot si il se trouve dans le dictionnaire choisi*/
    
    char * correction; /* chaine contenant le mot choisi comme correction pour 'mot' lorsqu'il ne se trouve pas dans le dictionnaire*/
    Liste propos; /*Liste des propositions de correction pour un 'mot' donné*/


    corriger = fopen(cor, "w");
    if(corriger == NULL){
        return 0;
    }
    correction = NULL;
    
    arbre = NULL;
    if(dico){
        arbre = creer_ArbreBK(dico);
        afficher_ArbreBK(arbre);
    }


    cmp = 0;
    
    while(fscanf(in, "%c", &c) != EOF){
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){ /*Construction du mot*/
            mot[cmp] = c;
            cmp++;
        } else {
            mot[cmp] = '\0';
            if(cmp == 0 && c == ' '){/* cas on  eu 'foix, ' et qu'on vient recuperer le ' '*/
                continue;
            }
            cmp = 0; /*remise à zero pour reecrire un nouveau mot apres le traitement*/

            dest = (char *)malloc(sizeof(char)*(strlen(mot)+1));
            if(dest){
                retire_maj(mot, dest); /*chaine que en minuscules*/
                dest2 = (char *)malloc(sizeof(char)*(strlen(mot)+1));
                if(dest2){
                    retire_caractere_spec(dest,dest2); /*chaine sans caracteres spéciaux*/
                    mot_trouve = rechercher_dans_ArbreBK(arbre, dest2); 
                    if(mot_trouve == NULL){
                        dmin = INFINI;
                        propos = Propose_correctionBK(arbre, dest2, &dmin);

                        correction = (char *)malloc(sizeof(char) * (26));
                        if(correction == NULL){
                            return 0;
                        }
                        correction = fonction_corrige_ou_non(mot, propos);
                        if(correction != NULL)
                            correction = (char * ) realloc(correction, sizeof(char) *strlen(correction));
                        if(correction){             
                            int indice;
                            int fin_mot;
                            fin_mot = strlen(mot);
                            indice = 0;
                            int len = strlen(correction);
                            while(indice < len){
                                if(indice >= fin_mot){ /*mot plus court que sa proposition de correction*/
                                    mot[indice] = correction[indice];
                                } else {
                                    if(mot[indice] >= 65 && mot[indice] <= 90 && (mot[indice] - 'A' + 'a' == correction[indice])){ /*meme lettre sauf en majuscule*/
                                        indice++;
                                        continue;
                                    } else if(mot[indice] == correction[indice]){ /* meme caractere*/
                                        indice++;
                                        continue;
                                    } else{
                                        mot[indice] = correction[indice];
                                        indice++;
                                    }
                                }
                            }
                            mot[indice] = '\0';
                            /*ecriture du mot corrige*/
                            fprintf(corriger, "%s", mot);
                            if(c == ' '){
                                fprintf(corriger, "%c", c);
                            } else if(c == '\n'){
                                fprintf(corriger, "%c", c);
                            } else{
                                fprintf(corriger, "%c ", c);
                            }
                            free(correction);
                        } else{ /*Pas de corrections*/
                            fprintf(corriger, "%s", mot);
                            if(c == ' '){
                                fprintf(corriger, "%c", c);
                            } else if(c == '\n'){
                                fprintf(corriger, "%c", c);
                            } else{
                                fprintf(corriger, "%c ", c);
                            }
                        }
                        
                    } else { /*Mot dans le dico pas besoin de corrections*/
                        
                        
                        fprintf(corriger, "%s", mot);
                        if(c == ' '){
                            fprintf(corriger, "%c", c);
                        } else if(c == '\n'){
                            fprintf(corriger, "%c", c);
                        } else{
                            fprintf(corriger, "%c ", c);
                        }
                        free(mot_trouve);
                        mot_trouve = NULL;
                    }

                    free(dest2);
                    dest2 = NULL;
                }
                free(dest);
                dest = NULL;
                
            }
            
        }
        
    }
    rewind(dico);
    rewind(in);
    fclose(corriger);

    liberer_ArbreBK(&arbre);
    liberer_Liste(&propos);
    return 1;
}
