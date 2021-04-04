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
        writeLog("Invalid block address", SEVERITY_ERROR, log_fd);
        exit(EXIT_FAILURE);
    }
    BlockListPtr bl = getMemoryBlockList(memory);
    int position = p - getMemoryAddress(memory);
    /* Partial search of the block in the blockList*/
    removeBlock(bl, position, memory);
    displayMemory(memory);
    return 0;
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