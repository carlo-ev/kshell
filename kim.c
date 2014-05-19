#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

char* getInput();
void clean(char* full);
char** parseCommands(char* inp);
int countCommands(char* in);
void listFiles(char* directory, int option);
void moveFile(char* filename, char* destination);
void createFile(char* filename);

int main(){
	static char* input;
	static char** commands;
	static char cDir[256];
	if(getcwd(cDir, sizeof(cDir)) != NULL)  
		printf("Current Directory: %s\n", cDir);
	else{
		printf("Sorry couldn't get working directory\n");
		return 1;
	}
	write(1, "\33[H\33[2J", 7);
	while(1){
		printf("kim~%s$ ", cDir);
		input = getInput();
		commands = parseCommands(input);
		printf("Command: %s\n", commands[0]);
		if(!strcmp(commands[0], "exit")){
			printf("kIM - K shell Improved. cmev\n");
			free(input);
			free(commands);
			break;
		}else if(!strcmp(commands[0], "ls")){
			int opcion = 0;
			if(commands[1] != NULL){
				if(!strcmp(commands[1], "-a")){
					opcion = 1;
				}else if(!strcmp(commands[1], "-i")){
					opcion = 2;
				}else if(!strcmp(commands[1], "-h")){
					opcion = 3;
				}else if(!strcmp(commands[1], "-l")){
					opcion = 4;
				}
			}
			listFiles(cDir, opcion);
		}else if(!strcmp(commands[0], "cd")){
			if(commands[1] != NULL){
				strcat(cDir, "/");
				strcat(cDir, commands[1]);
				if(chdir(cDir))
					printf("Sorry Specified parameter is not a folder, or we couldn't change dir at the moment\n");
				memset(cDir, 0, 255);
				getcwd(cDir, sizeof(cDir));
				printf("New Directory: %s\n", cDir);
			}else
				printf("No Directory Specified\n");
		}else if(!strcmp(commands[0], "mkdir")){
			if(commands[1] != NULL){
				if(mkdir(commands[1], 0777))
					printf("Sorry couldn't create folder at the moment\n");
				else
					printf("Created Directory: %s\n", commands[1]);		
			}else
				printf("No Directory Specified\n");
		}else if(!strcmp(commands[0], "rm")){
			if(commands[1] != NULL){
				if(!remove(commands[1]))
					printf("File/Folder %s succesfully deleted.\n", commands[1]);
				else
					printf("Couldn't Remove file at the moment.\n");
			}else
				printf("No File/Directory Specified\n");	
		}else if(!strcmp(commands[0], "clear")){
			write(1, "\33[H\33[2J", 7);
		}else if(!strcmp(commands[0], "chmod")){
			if(commands[1] != NULL){
				strcat(cDir, commands[0]);
				if(chmod(cDir, atoi(commands[1])))
					printf("File/Folder protected succesfully.\n");
				else	
					printf("Couldn't protect file/folder at the moment.\n");
				memset(cDir, 0, 255);
				getcwd(cDir, sizeof(cDir));
			}else
				printf("No File/Folder specified.\n");
		}else if(!strcmp(commands[0], "mv")){
			if(commands[1]!=NULL && commands[2]!=NULL)
				moveFile(commands[1], commands[2]);
			else
				printf("Destination folder or Filename not specified\n");
		}else if(!strcmp(commands[0], "touch")){
			if(commands[1] != NULL)
				createFile(commands[1]);
			else
				printf("File name not specified.\n");
		}else{
			printf("Sorry command not supported by the shell.\n");
		}
		free(commands);
		memset(input, 0, sizeof(input));
	}
}

void createFile(char* filename){
	FILE* file;
	fopen(filename, "wb");
	if(file!= NULL){
		fclose(file);
		printf("Sorry couldn't create file.\n");
	} 
}

void moveFile(char* filename, char* destination){
	char temp[256];
	strcpy(temp, destination);
	strcat(temp, "/");
	strcat(temp, filename);
	FILE *file, *dest;
	file = fopen(filename, "rb");
	dest = fopen(temp, "wb");

	int buf;
	if(file==NULL || dest==NULL){
		fclose(file);
		fclose(dest);
		printf("Error opening one/both of the files.\n");
	}else{
		while(1){
			buf = fgetc(file);
			if(!feof(file))
				fputc(buf, dest);
			else
				break;
		}
		fclose(file);
		fclose(dest);
		printf("File copied succesfully.\n");
		if(!remove(filename))
			printf("But we couldn't delete the original file.\n");
	}
	
}

void listFiles(char* directory, int option){
	DIR *dir = opendir(directory);
	char name[256];
	
	if(dir){
		struct dirent* stats_dir;
		struct stat stats_file;
		while((stats_dir = readdir(dir)) != NULL){
			strcpy(name, stats_dir->d_name);
			char file[256];
			strcpy(file, directory);
			strcat(file, "/");
			strcat(file, stats_dir->d_name);
			switch(option){
				default:
				case 0: 
					if(!(name[0]=='.'))
						printf("%s	", name);
					break;
				case 1:
					printf("%s	", name);
					break;
				case 2:
					printf("%s	", name);
					break;
				case 3:
					if(!(name[0]=='.')){
						stat(file, &stats_file);
						printf("%ld	%s", (long)stats_dir->d_ino, name);
					}
					break;
				case 4:
					if(!(name[0]=='.')){
						stat(file, &stats_file);
						printf("%lo %ld %s %s %lld %s %s\n", (unsigned long)stats_file.st_mode, (long)stats_file.st_nlink, (getpwuid(stats_file.st_uid))->pw_name, (getgrgid(stats_file.st_gid))->gr_name, (long long)stats_file.st_size, ctime(&stats_file.st_mtime), name);
					}
					break;

			}
		}
		printf("\n");
	}
	closedir(dir);
	//glib double list error of corruption no idea why, dir stays open
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
