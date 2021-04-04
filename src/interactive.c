#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

#define QUIT "quit"
#define INPUT_SIZE 15
void interactiveMode() {
  int stop = 0;
  InputHandler handler;
  initInputHandler(&handler);
  while (!stop) {
    printf("TO ALLOCATE MEMORY, PLEASE TYPE: 's:i', WITH I THE SIZE OF YOUR BLOCK");
    printf("--------------------------\n");
    printf("TO DELETE A BLOCK, PLEASE TYPE: 'a:i', WITH I THE POSITION OF YOUR BLOCK");
    printf("--------------------------\n");
    printf("TO FREE THE MEMORY SPACE, PLEASE TYPE: 'r'");
    printf("--------------------------\n");
    printf("TO QUIT, PLEASE TYPE: 'quit'");
    printf("--------------------------\n");
    char input[INPUT_SIZE];
    scanf("%s", input);
    if (strcmp(QUIT, input) == 0) {
      stop = 1;
    }
    else {
      int fieldsCount;
      char **fields = parseData(input, FIELDS_COUNT, " ", &fieldsCount);
      handleInput(&handler, input, strlen(input));
    }
  }
  destroyInputHandler(&handler);
}