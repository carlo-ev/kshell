#include "systemCalls.h"
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

void listDirectory(char* directory){
    DIR *dir = opendir(directory);
    if(dir){
        struct dirent* directoryStruct;
        while( (directoryStruct = readdir(dir)) != NULL ){
            printf("%s\n", directoryStruct->d_name);
        }
        closedir(dir);
    }
}

char* inspectDirectory(char* directory){
    DIR *dir = opendir(directory);
    if(dir){
        char* directoryInspect;
        struct dirent* directoryStruct;
        int lineCount = 0;
        int nameSize = 0;
        char* carryingString;
        while( (directoryStruct = readdir(dir)) != NULL ){
            nameSize += ( strlen(directoryStruct->d_name)+3 );
            free(carryingString);
            carryingString = (char*)malloc(strlen(directoryInspect));
            strcpy(carryingString, directoryInspect);
            free(directoryInspect);
            directoryInspect = (char*)malloc(nameSize);
            strcpy(directoryInspect, carryingString);
            strcat(directoryInspect, directoryStruct->d_name);
            strcat(directoryInspect, "   ");
        }
        closedir(dir);
        return directoryInspect;
    }
    return NULL;
}
