#ifndef _COMMAND_H_
#define _COMMAND_H_
#include "types.h"

#define MAX 6
#define FIELDS_COUNT 3
#define SEPARATOR ":"

void inputHandler(char *buffer, int maxBufferSize);

void freeCommandHandler(char **fields, int n);
void allocCommandHandler(char **fields, int n);
void initCommandHandler(char **fields, int n);

CommandType detectCommand(char **fields, int n);
char **parseData(char *data, int count, char *separator) ;

#endif /*_COMMAND_H_*/