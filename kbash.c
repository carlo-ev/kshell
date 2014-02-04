#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

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
	char kill[4];
	strcpy(kill,"kill");
	char cat[3];
	strcpy(cat, "cat");
	while(1){	
		printf("k~# ");
		commands = getInput(commands);
		if(stringCmp(ps, commands[0]) == 0){
			if(commands[1] != 0 )
				system( strcat( strcat(ps, " "), commands[1]) );
			else
				system(ps);
		}else if (stringCmp(kill, commands[0]) == 0){
			if(commands[1] == 0)
				printf("%s\n", "No Process ID supplied, suiciding..." );
			else{
				const char* comh = "kill"; 
				commands[1][4] = '\0';
				char* helper[3] = {commands[0], commands[1], (char *) 0};
				execvp( comh, helper);
			}
		}else if(stringCmp(cat, commands[0]) == 0 ){
			if(commands[1] == 0){
				printf("%s\n", "Sorry no file nor option specified, exiting bruv.");
			}else if(stringCmp(">", commands[1])==0 && commands[2] != 0){
				FILE* doc;
				doc = fopen(commands[2], "w+");
				printf("%s\n", "This version of cat online support documents saving on ENTER or EOF, pls take note!!");
				char chars[256];
				int line = 0;
				printf("%d| ", line);
				while(fgets(chars, 256, stdin) != NULL){
					if(feof(stdin)){
						break;
					}
					line++;
					printf("%d| ",line);
					fprintf(doc, "%s\n", chars);
				} 
				printf("%s\n", "EOF");
				fclose(doc);
			}else if(stringCmp("|", commands[2]) == 0){
				if(commands[1] != 0){
					FILE* in;
					FILE* out;
					char buff[512];
			
					if(!(in = popen(strcat("cat ", commands[1]), "r"))){
						return 1;
					}
					if(!(out = popen("more", "w"))){
						return 1;
					}
					while(fgets(buff, sizeof(buff), in) != NULL){
						fputs(buff, out);
					}
					pclose(in);
					pclose(out);
				}else{
					printf("%s\n", "Sorry specified file could not be opened.");
				}
			}else{
				FILE* doc;
				doc = fopen(commands[1], "r");
				if(doc != NULL){
					char line[512];
					int li = 0;
					while(fgets(line, 512, doc) != NULL){
						printf("%d| %s\n", li, line);
					}
					fclose(doc);
				}else{
					printf("%s\n", "Sorry Couldnt Open File.");
				}
			}
		}else if (stringCmp(ext, commands[0]) == 0 ){
			exit(0);
		}else{
			if(commands[0] == 0 ){
				if(commands[1] == 0){
					char* helper[3] = {commands[0], "&", (char *) 0};
					execvp(commands[0], helper);
				}else{
					char* helper[3] = {commands[0], commands[1],(char *) 0 };
					execvp(commands[0], helper);
				}
			}
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





