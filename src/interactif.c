#include <stdio.h>
#include <stdlib.h>
#include "command.h"

void interactiveMode(){	 
 	 printf("TO ALLOCATE MEMORY, PLEASE TYPE: '-a -i', WITH I THE SIZE OF YOUR BLOCK");
 	 printf("--------------------------\n");
 	 printf("TO DELETE A BLOCK, PLEASE TYPE: '-f -i', WITH I THE POSITION OF YOUR BLOCK");
   printf("--------------------------\n");
   char *input;
   scanf("%s", &input);
   char **fields = parseData(input, FIELDS_COUNT, " ");
   inputHandler(input, strlen(input));
}
