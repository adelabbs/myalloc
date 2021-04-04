#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "util.h"
#include "memory_internal.h"
#include "default_strategies.h"

extern MemoryPtr memory;
extern int log_fd;

/**
 * @brief initialization of the work area
 *
 * @param nBytes number of bytes to allocate
 * @return int 0 if error | number of allocated bytes
 */
int initMemory(int nBytes) {
    memory = createMemory(nBytes, firstFit, freeMemoryBlock);
    if(memory != NULL) displayMemory(memory);
    return (memory != NULL) ? nBytes : 0;
}

/**
 * @brief dynamic memory allocation in the area
 *
 * @param nBytes
 * @return void* NULL if error | address allocated
 */
void *myalloc(int nBytes) {
    void *address = 0;
    if (memory != NULL) {
        address = allocationStrategy(memory)(memory, nBytes);
    }
    else {
        writeLog("Memory is not initialized", SEVERITY_ERROR, log_fd);
    }
    return address;
}

/**
 * @brief deallocation of a zone addressed by a pointer
 *
 * @param p
 * @return int -1 if error | size of the freed space 
 */
int myfree(void *p) {
    if (memory == NULL) {
        writeLog("Memory is not initialized", SEVERITY_ERROR, log_fd);
        return -1;
    }
    return freeStrategy(memory)(memory, p);
}

/**
 * @brief free of the area initially reserved
 *
 * @return int -1 if error | total freed space
 */
int freeMemory() {
    int size;
    char *log;
    if (memory == NULL) {
        log = "Memory already free";
        size = -1;
    }
    else {
        getMemorySize(memory);
        destroyMemory(memory);
        log = "Freed memory";
    }
    writeLog(log, SEVERITY_DEBUG, log_fd);
    return size;
}