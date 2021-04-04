#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "types.h"

#define MAX 6
#define FIELDS_COUNT 3
#define SEPARATOR ":"

typedef struct {
    void **addresses;
}InputHandler;

void initInputHandler(InputHandler *inputHandler);
void createInputHandler(InputHandler *inputHandler, int addressesCount);
void destroyInputHandler(InputHandler *inputHandler);

void handleInput(InputHandler *inputHandler, char *buffer, int maxBufferSize);

void freeCommandHandler(InputHandler *inputHandler, char **fields, int n);
void allocCommandHandler(InputHandler *inputHandler, char **fields, int n);
void initCommandHandler(InputHandler *inputHandler, char **fields, int n);
void removeMemoryHandler(InputHandler *inputHandler);

CommandType detectCommand(char **fields, int n);
char **parseData(char *data, int count, char *separator, int *fieldsCount);

#endif /*_COMMAND_H_*/