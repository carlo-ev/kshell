#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

char* getInput();
void clean(char* full);
char** parseCommands(char* inp);
int countCommands(char* in);
char** getDirectoryFiles(char* directory);

int main(){
	static char* input;
	static char** commands;
	static char cDir[256];
	static char** filesInD;
	if(getcwd(cDir, sizeof(cDir)) != NULL)  
		printf("Current Directory: %s\n", cDir);
	else{
		printf("Sorry couldn't get working directory\n");
		return 1;
	}
	while(1){
		getDirectoryFiles(cDir);
		printf("kim#~ ");
		input = getInput();
		commands = parseCommands(input);
		printf("Command: %s\n", commands[0]);
		if(!strcmp(commands[0], "exit")){
			printf("Adios!\n");
			free(input);
			free(commands);
			break;
		}else if(!strcmp(commands[0], "ls")){
			execvp(commands[0], commands);
		}
	}

}

char** getDirectoryFiles(char* directory){
	DIR *dir = opendir(directory);
	char** files;
	if(dir){
		struct dirent* stats_dir;
		int fileCount = 0;
		while((stats_dir = readdir(dir)) != NULL) fileCount++;
		rewinddir(dir);
		files = (char**)malloc(fileCount);
		fileCount = 0;
		while((stats_dir = readdir(dir)) != NULL){
			files[fileCount] = (char*)malloc(strlen(stats_dir->d_name));	
		 	strcpy(files[fileCount], stats_dir->d_name);
			printf("File name: %s\n", files[fileCount]);
			fileCount++;	
		}
		
	}
	//closedir(dir);
	//glib double list error of corruption no idea why, dir stays open
	return files;
}

char** parseCommands(char* inp){
	char* inputCpy = (char*)malloc(strlen(inp));
	strcpy(inputCpy, inp);
	int count = countCommands(inputCpy);
	free(inputCpy);
	char** com = (char **)malloc(count);
	int ind = 0;
	char* token = strtok(inp, " ");
	while(token){
		com[ind] = (char*)malloc(strlen(token)+1);
		strcpy(com[ind], token);
		token = strtok(NULL, " ");
		ind++;
	}
	return com;
}

int countCommands(char* in){
	int counter = 0;
	char* words = strtok(in, " ");
	while(words){
		words = strtok(NULL, " ");
		counter++;
	}
	return counter;
}

char* getInput(){
	char cons[256];
	fgets(cons, 256, stdin);
	clean(cons);
	char* input = (char*)malloc(strlen(cons)+1);
	strcpy(input, cons);
	return input;
}

void clean(char* full){
	int index;
	for(index=0; index < strlen(full)-1; index++){
		if(full[index+1]=='\n')
			full[index+1] = '\0';
		if(full[index]==' ' && full[index+1]==' '){
			full[index]='\0';
			break;
		}
	}
}
