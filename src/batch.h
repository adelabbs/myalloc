#ifndef _BATCH_H_
#define _BATCH_H_
#include "options.h"
int batch(char *filepath);

void sizeCommandHandler(char **fields, int n);
void allocCommandHandler(char **fields, int n);
void freeCommandHandler(char **fields, int n);

CommandType commandHandler(char **fields, int n);

#endif /*_BATCH_H_*/