#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "command.h"
#include "batch.h"

#define BUF_SIZE 13
#define FIELDS 3
#define SEPARATOR ":"

int batch(char *filepath) {
  FILE *file;
  char buffer[BUF_SIZE];
  bzero(buffer, BUF_SIZE);

  if ((file = fopen(filepath, "r")) == NULL) {
    //TODO log
    perror("file not found !");
    exit(EXIT_FAILURE);
  }
  else {
    InputHandler handler;
    initInputHandler(&handler);
    while (fgets(buffer, BUF_SIZE - 1, file) != NULL) {
      handleInput(&handler, buffer, BUF_SIZE);
      bzero(buffer, BUF_SIZE);
    }
    destroyInputHandler(&handler);
  }
  return 0;
}