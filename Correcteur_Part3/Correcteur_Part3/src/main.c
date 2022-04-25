#include "correcteur_0.h"
#include "correcteur_1.h"
#include "correcteur_2.h"
#include "gestion_erreur.h"

int main(int argc, char * argv[]){

    int param;

    if(argc < 4){
        affiche_argv();
        return 0;

    } else {

        param_correcte(&param, argv);

        if(param >= 0){

            switch(param){

                case 0 : _correcteur_0(argc, argv); break ;

                case 1 : _correcteur_1(argc, argv); break ;

                default : _correcteur_2(argc, argv); break ;

            }

        } else{

            fprintf(stderr,"\nLe 1er argument est non conforme!!\n");
            affiche_argv();
            
            return 0;
        }

    }

    return 0;

}
