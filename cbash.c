#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getInput(char* com[5]);

int main(){
	char s[256];
	strcpy(s, "one two three");
	char* token = strtok(s, " ");
	while(token){
		printf("token: %s\n", token);
		token = strtok(NULL, " ");
	}
	//char command[5];
	/* while(1){	
		printf("c >");
		fgets(command, 5, stdin);
		printf("%s\n", command);
		if (strcmp("exit", command) == 0 ){
			printf("exit");
			exit(EXIT_SUCCESS);
		}
	}
	*/
	return 0;
}

void getInput(char* com[5]){
	char* commands;
	int i = 0;
	fgets(commands, 50, stdin);
	commands = strdup(commands);
	char* past;
	past = strtok(commands, ",");
	printf("%s\n", commands);
	while(past != NULL){
		past = strtok(commands, " ");
		com[i] = past;
		printf("%s\n",past);
	}
}




