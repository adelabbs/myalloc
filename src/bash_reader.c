#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MAX 6

FILE * file;
char buffer[MAX];

int batch(char *filepath) {

    int counter = 0;
    char * functionType;
    char * bytes;
    char * id;

    if(file = fopen(filepath, "r") != NULL) {
        //TODO log 
        while(! feof(file)) {
            fgets(buffer, MAX, file);
            functionType = strtok(buffer, ":");
            bytes = strtok(NULL, ":");
            
            if(functionType == 's') {
                initMemory(atoi(bytes));
            } else if (functionType == 'a') {
                id = strtok(NULL, ":");
                if (id = NULL) {
                    perror("missing id");
                    //TODO log line error
                    exit(EXIT_FAILURE);
                }
                myalloc(atoi(bytes));
                //TODO bind id with adress

            } else if (functionType == 'f') {
                //TODO myfree();
            } else {
                perror("input error, please check file");
                exit(EXIT_FAILURE);
            }
            counter++;
        }
    }
    else {
        //TODO log
        perror("file not found !");
        exit(EXIT_FAILURE);
    }
}