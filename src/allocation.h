#ifndef _ALLOCATION_H_
#define _ALLOCATION_H_

#include "memory2.h"

typedef int (*MemoryAllocationStrategy)(MemoryPtr memory,
    int nBytes);

#endif /*_ALLOCATION_H_*/