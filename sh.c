/*
	CS 3560
	HW 08
	Brian Yu
	xv8343
*/
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#include "./parse.h"

#define SIZE 128

int main (int argc, char* argv[]){
	char input[SIZE];
 	char* tokens[SIZE];
	int i;
	char currdir [SIZE];
	
	// ignore CTRL - C
	signal(SIGINT, SIG_IGN);	
			
 	do{
 		getcwd(currdir,SIZE);		
 		printf("%s$ ",currdir); 		
	 	if(fgets(input, SIZE, stdin) == NULL){
	 		perror("fgets");
	 		exit(0);
		}

		if(strcmp(input,"\n") == 0)
			continue;
	 	parse(input, tokens); 	

/*		printf("Tokens: ");
	 	for(i=0;tokens[i] != NULL;i++){	 		
	 		printf("%d: %s---  ",i, tokens[i]);	 
	 	}
	 	printf("\n");
*/
		if(strcmp(tokens[0],"exit\0") == 0 || strcmp(tokens[0],"exit") == 0)
			exit(0);
		if(strcmp(tokens[0],"cd\0") == 0){
			if(chdir(tokens[1]) != 0) {	
				if(errno == ENOENT)
					printf("%s: No such file or directory\n",tokens[1]);
				else perror("");
			}
			continue;	
		}				
 		int rv = fork();
 		
 		// Child process 	 
 		if(rv == 0){
 			execvp(tokens[0],tokens);
		}
		
		// Parent process
		else{
			wait(NULL);		
		}			
	}
 	while(1);
}
