#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "memory_internal.h"
#include "default_strategies.h"

extern MemoryPtr memory;

/**
 * @brief initialization of the work area
 *
 * @param nBytes
 * @return int
 */
int initMemory(int nBytes) {
    memory = createMemory(nBytes, firstFit, freeMemoryBlock);
    displayMemory(memory);
    return (memory != NULL) ? 0 : -1;
}

/**
 * @brief dynamic memory allocation in the area
 *
 * @param nBytes
 * @return void*
 */
void *myalloc(int nBytes) {
    return allocationStrategy(memory)(memory, nBytes);
}

/**
 * @brief deallocation of a zone addressed by a pointer
 *
 * @param p
 * @return int
 */
int myfree(void *p) {
    return freeStrategy(memory)(memory, p);
}

/**
 * @brief free of the area initially reserved
 *
 * @return int
 */
int freeMemory() {
    destroyMemory(memory);
}