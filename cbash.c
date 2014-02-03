#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CMD 5

char** getInput();
char* trimwhitespace(char* str);
bool isSpace(char x);
bool stringCmp(char* a, char*b);

int main(){
	char** commands;
	int x;
	char ext[4];
	strcpy(ext,"exit");
	char ps[2];
	strcpy(ps,"ps");
	char* helper;
	while(1){	
		printf("k-+ ");
		commands = getInput(commands);
		if(stringCmp(ps, commands[0]) == 0){
			if(commands[1] != 0 )
				system( strcat( strcat(ps, " "), commands[1]) );
			else
				system(ps);
		}
		
		if (stringCmp(ext, commands[0]) == 0 ){
			exit(0);
		}
	}
	return 0;
}

bool stringCmp(char* a, char* b){
	int size = strlen(a) <= strlen(b) ? strlen(a) : strlen(b);
	return strncmp(a, b, size);
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





