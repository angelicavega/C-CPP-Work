//This code provides direct translation of the given word list between Engligh, Spanish, and French

# include <ctype.h>
# include <stdio.h>
# include <string.h>

//Here we convert all given words to lower case
void smallcase(char word[]){
                int index = 0;
                while(word[index]!='\0') {
                                word[index] = tolower(word[index]);
                                index+=1;

                }

}

int getIndex (char* sourceword[], char nameofword[], int sizeofword) {
                int i;
                for(i = 0 ; i < sizeofword; i++) {
                        if(strcmp(sourceword[i],nameofword)==0) {
                                return i;                  

                }               

                }

                return -1;

}

int main(){

                int SizeWORD = 8;
                char* english[] ={"cat","dog","bird","mouse","cow","tiger","horse","monkey"} ;
                char* spanish[] ={"gato","perro","pajaro","raton","vaca","tigre","caballo","mono"}  ;
                char* french[] ={"chat","chien","oiseau","souris","vache","tigre","cheval","singe"}   ;
                char animal[20] ; char sourceword[20]; char destinationLANG[20];
                char repeat[2]   ; int index;

                do{

                               
                                printf("Please enter a word to translate:\n");
                                scanf("%19s", &animal);
                                printf("Please enter the source language:\n");
                                scanf("%19s", &sourceword);
                                printf("Please enter the destionation langugage:\n");
                                scanf("%19s", &destinationLANG);
                                smallcase(animal);
                                smallcase(sourceword);
                                smallcase(destinationLANG);

                                if(strcmp(sourceword,"english")==0 && strcmp(destinationLANG,"spanish")==0) {

                                                index = getIndex(english,animal,SizeWORD);

                                                if(index!=-1) {

                                                printf("%s is a English word that translates as %s in Spanish\n",animal,spanish[index]);

                                                }
                                               

                                }else if(strcmp(sourceword,"english")==0 && strcmp(destinationLANG,"french")==0) {

                                                index = getIndex(english,animal,SizeWORD);

                                                if(index!=-1) {

                                                                printf("%s is a English word that translates as %s in French\n",animal,french[index]);

                                                }

                                }


                                else if(strcmp(sourceword,"french")==0 && strcmp(destinationLANG,"spanish")==0) {
                                                index = getIndex(french,animal,SizeWORD);
                                                if(index!=-1) {
                                                                printf("%s is a French word that translates as %s in Spanish\n",animal,spanish[index]);

                                                }

                                }

                                else if(strcmp(sourceword,"french")==0 && strcmp(destinationLANG,"english")==0) {
                                                index = getIndex(french,animal,SizeWORD);
                                                if(index!=-1) {

                                                                printf("%s is a French word that translates as %s in English\n",animal,english[index]);

                                                }

                                }
                                else if(strcmp(sourceword,"spanish")==0 && strcmp(destinationLANG,"french")==0) {
                                                index = getIndex(spanish,animal,SizeWORD);
                                                if(index!=-1) {
                                                                printf("%s is a Spanish word that translates as %s in French\n",animal,french[index]);
                                                }

                                }

                                else if(strcmp(sourceword,"spanish")==0 && strcmp(destinationLANG,"english")==0) {
                                                index = getIndex(spanish,animal,SizeWORD);
                                                if(index!=-1) {
                                                                printf("%s is a Spanish word that translates as %s in English\n",animal,english[index]);

                                                }

                                }

                                else{
                                                printf("Error: The source or the destination languge was incorrect\n")                                     ;

                                }

                                if(index==-1) printf("Sorry the %s is not found in the dictionary\n", animal);

                                printf("Do you want to translate a new word? (Y/N):\n");
                                scanf("%1s", &repeat);
                                smallcase(repeat);

                } while(strcmp(repeat,"y")==0);

                printf("\n\nByeBye!");


}