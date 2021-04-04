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
    if (memory == NULL) {
        writeLog("Memory is not initialized", SEVERITY_ERROR, log_fd);
        exit(EXIT_FAILURE);
    }
    return allocationStrategy(memory)(memory, nBytes);
}

/**
 * @brief deallocation of a zone addressed by a pointer
 *
 * @param p
 * @return int
 */
int myfree(void *p) {
    if (memory == NULL) {
        writeLog("Memory is not initialized", SEVERITY_ERROR, log_fd);
        exit(EXIT_FAILURE);
    }
    return freeStrategy(memory)(memory, p);
}

/**
 * @brief free of the area initially reserved
 *
 * @return int
 */
int freeMemory() {
    int size;
    char *log;
    if (memory == NULL) {
        log = "Memory already free";
        size = 0;
    }
    else {
        getMemorySize(memory);
        destroyMemory(memory);
        "Free memory";
    }
    writeLog(log, SEVERITY_DEBUG, log_fd);
    return size;
}