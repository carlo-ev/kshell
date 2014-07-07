#ifndef _SYSTEMCALLS_H_
#define _SYSTEMCALLS_H_

//List all directories and files or the current or specified directory
    extern void listDirectory(char* directory);
    extern char* listDirectory(char* directory);
//Move a file from the specified directory to the specified destination
    extern void moveFile(char* filename, char* destination);
//Create a file on the specified directory
    extern void createFile(char* filename);

#endif