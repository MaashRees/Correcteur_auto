#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void retire_caractere_spec(char * mot,char * dest){

  int i;
  for(i = 0; i<strlen(mot); i++){
      if(isalpha(mot[i])){
        dest[i]=mot[i];
      }
      else{
          dest[i]=' ';
      }

  }

  printf("mot = %s, %d\n",mot,strlen(mot));
  printf("dest = %s, %d\n",dest,strlen(dest));

}



void retire_maj(char * mot, char *dest){
    int i;


    for(i = 0; i < strlen(mot); i++) {
      dest[i] = tolower(mot[i]);
    }

    printf("mot = %s, %d\n",mot,strlen(mot));
    printf("dest = %s, %d\n",dest,strlen(dest));
}

int main()
{
  //  printf("%s\n",retire_maj("essAAi"));
char dest[255];
char dest2[255];
retire_maj("Saint", dest2);
retire_caractere_spec("saint-lazare.",dest);
    return 0;
}
