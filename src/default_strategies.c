#include <stdio.h>
#include <stdlib.h>
#include "memory_internal.h"
#include "util.h"

extern int log_fd;

/**
 * @brief First fit allocation algorithm
 *
 * @param memory MemoryPtr A pointer the the implementation of the memory space
 * @param nBytes the number of bytes to allocate
 * @return void* NULL if error | the address allocated
 */
void *firstFit(MemoryPtr memory, int nBytes) {
    void *address = NULL;
    if (getMemoryAvailableSpace(memory) >= nBytes) {
        int position = 0;
        BlockListPtr bl = getMemoryBlockList(memory);
        if (isEmptyBlockList(bl)) {
            BlockListPtr block = (BlockListPtr)malloc(sizeof(*block));
            if (block == NULL) {
                perror("Couldn't allocate memory in function createBlockList()");
                exit(EXIT_FAILURE);
            }
            block->position = position;
            block->size = nBytes;
            block->next = NULL;
            memory->blockList = block;
        }
        else {
            int stop = 0;
            position += getBlockSize(bl);
            while (getNextBlock(bl) != NULL && !stop) {
                if (getSizeBetweenNextBLock(bl) >= nBytes) {
                    stop = 1;
                }
                else {
                    bl = getNextBlock(bl);
                    position += getBlockSize(bl);
                }
            }
            addBlock(bl, nBytes, position);
        }
        setMemoryAvailableSpace(memory, getMemoryAvailableSpace(memory) - nBytes);
        displayMemory(memory);
        address = getMemoryAddress(memory) + position;
    }
    else {
        writeLog("Couldn't allocate block, not enough space", SEVERITY_ERROR, log_fd);
    }
    return address;
}

/**
 * @brief Frees the memory block at the address p from the memory
 *
 * @param memory MemoryPtr
 * @param p Address of the block to be freed
 * @return int -1 if error | size of freed space
 */
int freeMemoryBlock(MemoryPtr memory, void *p) {
    int r = -1;
    /* Check if the pointer is valid*/
    if (p != NULL) {
        int position = p - getMemoryAddress(memory);
        /* Partial search of the block in the blockList*/
        r = removeBlock(&(memory->blockList), position, memory);
        char log[100];
        sprintf(log, "removeBlock() = %d", r);
        writeLog(log, SEVERITY_DEBUG, log_fd);
        displayMemory(memory);
    }
    else {
        writeLog("Invalid block address", SEVERITY_ERROR, log_fd);
    }
    return r;
}

/*

int nextFit(int blockSize) {
    if (getMemoryAvailableSpace(memory) < blockSize) {
        perror("Couldn't allocate block, not enough space");
        exit(EXIT_FAILURE);
    }
    int position = countBlocks(getBlockList(memory));
    //To set global memory attributes, use the adress and &.
    BlockList *bl = &(memory.blocks);
    if (!isEmptyBlockList(*bl)) {
        while (getNextBlock(*bl) != NULL && getSizeBetweenNextBLock(*bl) < blockSize) {
            *bl = getNextBlock(*bl);
            position--;
        }
        //TODO handle no space found
    }
    addBlock(bl, position, blockSize);
    setMemoryAvailableSpace(&memory, getMemoryAvailableSpace(memory) - blockSize);
    return position;
}

int bestFit(int blockSize) {
    if (getMemoryAvailableSpace(memory) < blockSize) {
        perror("Couldn't allocate block, not enough space");
        exit(EXIT_FAILURE);
    }
    int temp, lowest = getMemoryAvailableSpace(memory);
    int position = 0;
    int inserPos = 0;
    BlockList *bl = &(memory.blocks);
    if (!isEmptyBlockList(*bl)) {
        while (getNextBlock(*bl) != NULL) {
            temp = getSizeBetweenNextBLock(*bl) - blockSize;
            if (lowest > temp) {
                lowest = temp;
                inserPos = position;
            }
            *bl = getNextBlock(*bl);
            position++;
        }
    }
    addBlock(bl, inserPos, blockSize);
    setMemoryAvailableSpace(&memory, getMemoryAvailableSpace(memory) - blockSize);
    return position;
}

int worstFit(int blockSize) {
    if (getMemoryAvailableSpace(memory) < blockSize) {
        perror("Couldn't allocate block, not enough space");
        exit(EXIT_FAILURE);
    }
    int temp, highest = getMemoryAvailableSpace(memory);
    int position = 0;
    int inserPos = 0;
    BlockList *bl = &(memory.blocks);
    if (!isEmptyBlockList(*bl)) {
        while (getNextBlock(*bl) != NULL) {
            temp = getSizeBetweenNextBLock(*bl) - blockSize;
            if (highest < temp) {
                highest = temp;
                inserPos = position;
            }
            *bl = getNextBlock(*bl);
            position++;
        }
    }
    addBlock(bl, inserPos, blockSize);
    setMemoryAvailableSpace(&memory, getMemoryAvailableSpace(memory) - blockSize);
    return position;
}

*/