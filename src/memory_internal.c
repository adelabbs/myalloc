#include <stdio.h>
#include <stdlib.h>
#include "memory_internal.h"

/********* Memory functions ******/

int getMemorySize(MemoryPtr memory) {
    return memory->size;
}

int getMemoryAvailableSpace(MemoryPtr memory) {
    return memory->availableSpace;
}

void setMemoryAvailableSpace(MemoryPtr memory, int availableSpace) {
    if (availableSpace >= 0 && availableSpace <= getMemorySize(memory)) {
        memory->availableSpace = availableSpace;
    }
}

void *getMemoryAddress(MemoryPtr memory) {
    return memory->address;
}

BlockListPtr getMemoryBlockList(MemoryPtr memory) {
    return memory->blockList;
}

MemoryAllocationStrategy allocationStrategy(MemoryPtr memory) {
    return memory->allocationStrategy;
}

MemoryFreeStrategy freeStrategy(MemoryPtr memory) {
    return memory->freeStrategy;
}

/**
 * @brief Create a Memory object
 * 
 * @param size 
 * @param allocationStrategy 
 * @param freeStrategy 
 * @return MemoryPtr 
 */
MemoryPtr createMemory(int size, MemoryAllocationStrategy allocationStrategy, MemoryFreeStrategy freeStrategy) {
    MemoryPtr memory = (MemoryPtr)malloc(sizeof * memory);
    if (memory != NULL) {
        memory->size = size;
        memory->availableSpace = size;
        void *address = malloc(size);
        if (address == NULL) {
            perror("Couldn't allocate memory in function createMemory");
            exit(EXIT_FAILURE);
        }
        memory->address = address;
        memory->blockList = NULL;
        memory->allocationStrategy = allocationStrategy;
        memory->freeStrategy = freeStrategy;
    }
    return memory;
}

/**
 * @brief Destroy the Memory object
 * 
 * @param memory 
 */
void destroyMemory(MemoryPtr memory) {
    BlockListPtr blockList = getMemoryBlockList(memory);
    destroyBlockList(&blockList);
    free(memory);
}

void displayMemory(MemoryPtr memory) {
    printf("TOTAL SPACE = %d\n", getMemorySize(memory));
    printf("AVAILABLE SPACE = %d\n", getMemoryAvailableSpace(memory));
    printf("Block\t|Position\t|Size\n");
    BlockListPtr bl = getMemoryBlockList(memory);
    int i = 0;
    while (!isEmptyBlockList(bl)) {
        printf("%d\t| %d\t\t| %d\n", i, getBlockPosition(bl), getBlockSize(bl));
        i++;
        bl = getNextBlock(bl);
    }
    printf("--------------------------\n");
}

/********BlockList functions *******/


int getBlockPosition(BlockListPtr blockList) {
    return blockList->position;
}

int getBlockSize(BlockListPtr blockList) {
    return blockList->size;
}

BlockListPtr getNextBlock(BlockListPtr blockList) {
    return blockList->next;
}

/**
 * @brief Create a Block List object
 * 
 * @return BlockListPtr 
 */
BlockListPtr createBlockList(void) {
    BlockListPtr blocklist = (BlockListPtr)malloc(sizeof(*blocklist));
    if (blocklist == NULL) {
        perror("Couldn't allocate memory in function createBlockList()");
        exit(EXIT_FAILURE);
    }
    return blocklist;
}

int isEmptyBlockList(BlockListPtr blockList) {
    return blockList == NULL;
}

int getSizeBetweenNextBLock(BlockListPtr bl) {
    return getBlockPosition(getNextBlock(bl)) - (getBlockPosition(bl) + getBlockSize(bl));
}

/**
 * @brief Insert a block after the current block
 * 
 * @param blockList 
 * @param size 
 * @param position 
 */
void addBlock(BlockListPtr blockList, int size, int position) {
    BlockListPtr block = createBlockList();
    if (block == NULL) {
        perror("Couldn't allocate memory in function addBlockAfter()");
        exit(EXIT_FAILURE);
    }
    block->position = position;
    block->size = size;
    block->next = getNextBlock(blockList);
    blockList->next = block;
}

/**
 * @brief tries to find the address of a block that has the given position 
 * 
 * @param blockList
 * @param position 
 * @return BlockListPtr* NULL if no match found 
 */
BlockListPtr *searchBlock(BlockListPtr *blockList, int position) {
    if (isEmptyBlockList(*blockList)) {
        return blockList;
    }
    else if (getBlockPosition(*blockList) == position) {
        return blockList;
    }
    else {
        searchBlock(&((*blockList)->next), position);
    }
}

int removeBlock(BlockListPtr *blockList, int position, MemoryPtr memory) {
    BlockListPtr *block;
    int r = -1;
    if ((block = searchBlock(blockList, position)) != NULL) {
        int blockSize = getBlockSize(*block);
        r = blockSize;
        removeBlockHead(block);
        setMemoryAvailableSpace(memory, getMemoryAvailableSpace(memory) + blockSize);
    }
    return r;
}

void removeBlockHead(BlockListPtr *blockList) {
    BlockListPtr tmp;
    tmp = *blockList;
    *blockList = getNextBlock(*blockList);
    free(tmp);
}

void destroyBlockList(BlockListPtr *blockList) {
    while (!isEmptyBlockList(*blockList)) {
        removeBlockHead(blockList);
    }
}


int countBlocks(BlockListPtr bl) {
    int blocks = 0;
    while (bl != NULL) {
        bl = getNextBlock(bl);
        blocks++;
    }
    return blocks;
}