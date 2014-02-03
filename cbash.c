#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CMD 5

char** getInput();
char* trimwhitespace(char* str);
bool isSpace(char x);

int main(){
	char** commands;
	int x;
	char tt[256];
	while(1){	
		printf("k-+ ");
		commands = getInput(commands);
		strcpy(tt, "exit0");
		if (strcmp(tt, commands[0]) == 0 ){
			printf("exit");
			break;
		}
	}
	return 0;
}

char** getInput(){
	static char* com[MAX_CMD];
	char input[256];
	fgets(input, 256, stdin);
	char* clean = trimwhitespace(input);
	char* token = strtok(clean, " ");
	int num = 0;
	while(token){
		com[num] = token;
		printf("command: %s\n", token);
		token = strtok(NULL, " ");
		num++;
	}
	if(num < MAX_CMD-1)
		com[num+1] = 0;
	return com;
}

char* trimwhitespace(char *str){
	char* end;

	while(isSpace(*str)) str++;

	end = str + strlen(str) - 1;
	while(end > str && isSpace(*end)) end--;
	end++;

	*(end+1) = 0;

	return str;
}

bool isSpace(char x){
	return x == ' ';
}





