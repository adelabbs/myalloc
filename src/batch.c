#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "memory.h"
#include "options.h"
#include "batch.h"
#include "util.h"

#define MAX 6
#define FIELDS 3
#define SEPARATOR ":"

FILE * file;
char buffer[MAX];

int batch(char *filepath) {

    int counter = 0;
    char * functionType;
    char * bytes;
    char * id;


    if((file = fopen(filepath, "r")) != NULL) {
        //TODO log 
        char **fields;
        while(fgets(buffer, MAX, file) != NULL) {
            functionType = strtok(buffer, ":");
            bytes = strtok(NULL, ":");
            printf("%s", functionType);
            int cpt = parse_data(buffer, FIELDS, SEPARATOR, fields);
            CommandType command = commandHandler(fields, cpt); //detecter
            switch(command){
              case COMMAND_SIZE:
                sizeCommandHandler(fields, cpt);
                break;
              case COMMAND_ALLOC:
                allocCommandHandler(fields, cpt);
                break;
              case COMMAND_FREE:
                freeCommandHandler(fields, cpt);
                break;
                //TODO add default
            }
        }
            
            if(functionType[0] == 's') {
                initMemory(atoi(bytes));
            } else if (functionType[0] == 'a') {
                id = strtok(NULL, ":");
                if (id = NULL) {
                    perror("missing id");
                    //TODO log line error
                    exit(EXIT_FAILURE);
                }
                myalloc(atoi(bytes));
                //TODO bind id with adress

            } else if (functionType[0] == 'f') {
                //TODO myfree();
            } else {
                perror("input error, please check file");
                exit(EXIT_FAILURE);
            }
            counter++;
        
    }
    else {
        //TODO log
        perror("file not found !");
        exit(EXIT_FAILURE);
    }
}


void sizeCommandHandler(char **fields, int n){

}

void allocCommandHandler(char **fields, int n){

}

void freeCommandHandler(char **fields, int n){

}

CommandType commandHandler(char **fields, int n){
  CommandType command = COMMAND_UKN;
  if(n > 0){
    char *command_slug = fields[0];
    if(strcmp(command_slug, command_codes[COMMAND_SIZE]) == 0){
      command = COMMAND_SIZE;
    }else if(strcmp(command_slug,  command_codes[COMMAND_ALLOC]) == 0){
      command = COMMAND_ALLOC;
    }else if(strcmp(command_slug,  command_codes[COMMAND_FREE]) == 0){
      command = COMMAND_FREE;
    }
  }
  return command;
}