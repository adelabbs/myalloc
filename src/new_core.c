#include "core.h"
#include "memory_internal.h"
#include "default_strategies.h"
#include "new_strategy.h"

extern MemoryPtr memory;
/**
 * @brief initialization of the work area
 *
 * @param nBytes
 * @return int
 */
int initMemory(int nBytes){
    memory = createMemory(nBytes, bestFit, freeMemory);
}

/**
 * @brief dynamic memory allocation in the area
 *
 * @param nBytes
 * @return void*
 */
void *myalloc(int nBytes){

}

/**
 * @brief deallocation of a zone addressed by a pointer
 *
 * @param p
 * @return int
 */
int myfree(void *p){

}

/**
 * @brief free of the area initially reserved
 *
 * @return int
 */
int freeMemory(){

}