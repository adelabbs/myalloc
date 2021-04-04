#include <stdio.h>
#include <stdlib.h>
#include "memory_internal.h"
#include "util.h"

extern int log_fd;

void *firstFit(MemoryPtr memory, int nBytes) {
    if (getMemoryAvailableSpace(memory) < nBytes) {
        perror("Couldn't allocate block, not enough space");
        exit(EXIT_FAILURE);
    }
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
    return getMemoryAddress(memory) + position;
}

int freeMemoryBlock(MemoryPtr memory, void *p) {
    /* Check if the pointer is valid*/
    if (p == NULL) {
        writeLog("Invalid block address",  SEVERITY_ERROR, log_fd);
        exit(EXIT_FAILURE);
    }
    BlockListPtr bl = getMemoryBlockList(memory);
    int position = p - getMemoryAddress(memory);
    /* Partial search of the block in the blockList*/
    removeBlock(bl, position, memory);
    displayMemory(memory);
    return 0;
}