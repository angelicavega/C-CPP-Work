#include <stdio.h>

#include <ctype.h>

#include <stdlib.h>

#include<sys/wait.h>

#include <sys/types.h>

#include <string.h>

#include <unistd.h>

char word[20];

char *pWord;


char *English_French[16][2];

char *English_Spanish[16][2];

void init()
{
    // Here it translates from English to Spanish
    English_Spanish[0][0] = "Cat";
    English_Spanish[6][1] = "Caballo";
    English_Spanish[7][0] = "Monkey";
    English_Spanish[7][1] = "Mono";
    English_Spanish[0][1] = "Gato";
    English_Spanish[1][0] = "Dog";
    English_Spanish[1][1] = "Perro";
    English_Spanish[2][0] = "Bird";
    English_Spanish[2][1] = "Pajaro";
    English_Spanish[3][0] = "Mouse";
    English_Spanish[3][1] = "Raton";
    English_Spanish[4][0] = "Cow";
    English_Spanish[4][1] = "Vaca";
    English_Spanish[5][0] = "Tiger";
    English_Spanish[5][1] = "Tigre";
    English_Spanish[6][0] = "Horse";
    

    // Here it translates from English to French
    
    English_French[4][1] = "Vache";
    English_French[5][0] = "Tiger";
    English_French[5][1] = "Tigre";
    English_French[6][0] = "Horse";
    English_French[1][0] = "Dog";
    English_French[1][1] = "Chien";
    English_French[2][0] = "Bird";
    English_French[2][1] = "Oiseau";
    English_French[3][0] = "Mouse";
    English_French[3][1] = "Souris";
    English_French[4][0] = "Cow";
    English_French[6][1] = "Cheval";
    English_French[0][0] = "Cat";
    English_French[0][1] = "Chat";
    English_French[7][0] = "Monkey";
    English_French[7][1] = "Singe";
}

char* trans(char* src, int op)
{
    char *defining1, *defining2;
    for(int i = 0;i<15;i++) {
        if(0 == op) { // Goes from English to Spanish
            if(0 == strcmp(English_Spanish[i][0],src)){
                pWord = English_Spanish[i][1];
                defining1 = "English";
                defining2 = "Spanish";
                break;
            }
        }
        else if(1 == op) { // Goes from Spanish to English
            if(0 == strcmp(English_Spanish[i][1],src)){
                pWord = English_Spanish[i][0];
                defining1 = "Spanish";
                defining2 = "English";
                break;
            }
        }
        else if(2 == op) { // Goes from English to French
            if(0 == strcmp(English_French[i][0],src)){
                pWord = English_French[i][1];
                defining1 = "English";
                defining2 = "French";
                break;
            }
        }
        else if(3 == op) { // Goes from French to English
            if(0 == strcmp(English_French[i][1],src)){
                pWord = English_French[i][0];
                defining1 = "French";
                defining2 = "English";
                break;
            }
        }
    }
    return pWord;
}

// Here it translates from English to Spanish 
char *trans_ES(char* src) {
    return trans(src, 0);
}
	// Here it translates from  Spanish to English 
	char *trans_SE(char* src) {
    		return trans(src, 1);
}
		// Here it translates from  English to French 
		char *trans_EF(char* src) {
   			 return trans(src, 2);
}

			// Here it translates from French to English
				char *trans_FE(char* src) {
    					return trans(src, 3);
}



int piping(int choice, char* argument)
{
    int p1[2]; // Storage of first pipe
    int p2[2]; // Storage of second pipe

    if(-1 == pipe(p1))
    {
        fprintf(stderr, "Pipe1 Failed" );
        return 1;
    }
    		if(-1 == pipe(p2))
    {
       			 fprintf(stderr, "Pipe2 Failed" );
       				 return 1;
    }

    pid_t p = fork();

   		 if(p < 0)
    {
       		 fprintf(stderr, "fork Failed" );
       			 return 1;
    }
   			 else if (p > 0) // Here begins the parent process
    {
       				char *string; 
       				 char translated[16];

        close(p1[0]);
        if(4 == choice) 
            string = trans(argument, 1);
        else if(5 == choice) 
            string = trans(argument, 3);

     
        write(p1[1], string, strlen(string)+1);
        close(p1[1]);
        wait(NULL);
        close(p2[1]);
        read(p2[0], translated, 16);
        printf("%s\n", translated);
        close(p2[0]);
    }
    else // Here begins the child process
    {
        close(p1[1]);

        char english[16];
        char* translated = NULL;
        read(p1[0], english, 16);

        // Here we translate to destination language
        if(4 == choice) 
            translated = trans(english,2);
        else if(5 == choice) 
            translated = trans(english,0);
        close(p1[0]);
        close(p2[0]);

        write(p2[1], translated, strlen(translated)+1);
        close(p2[1]);

        exit(0);
    }
    return 0;
}

void forking(int choice, char* argument)
{
    if(choice > 3)
    {
        piping(choice, argument);
        return;
    }
    if(0 == fork()) {
        printf("%s\n",trans(argument, choice));
        exit(0);
    }

}
int main()
{
    char *commanding = "None";
    char *argument = NULL;
    init();
    do {
        char pos[32];
        printf("Translator> ");

        fgets(pos, 32, stdin);

        pos[strcspn(pos, "\n")] = '\0';

        commanding = strtok(pos, " ");

        argument = strtok(NULL, " ");
        int choice = -1;
        if(0 == strcmp(commanding,"trans_ES")) choice = 0;
        else if(0 == strcmp(commanding,"trans_SE")) choice = 1;

       	 else if(0 == strcmp(commanding,"trans_EF")) choice = 2;
        
		else if(0 == strcmp(commanding,"trans_FE")) choice = 3;
       
		 else if(0 == strcmp(commanding,"trans_SF")) choice = 4;
        else if(0 == strcmp(commanding,"trans_FS")) choice = 5;
        if(choice >= 0)
            forking(choice,argument);
    } while(0 != strcmp(commanding, "exit"));
    return 0;
}


