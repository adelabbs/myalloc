#ifndef _DEFAULT_STRATEGIES_H_
#define _DEFAULT_STRATEGIES_H_
#include "memory_interface.h"

void *firstFit(MemoryPtr memory, int nBytes);
int freeMemoryBlock(MemoryPtr memory, void *p);

#endif /* _DEFAULT_STRATEGIES_H_ */