#include <stdio.h>
#include <stdlib.h>
#include "memory2.h"

struct Memory {
    int size;
    int availableSpace;
    void *address;
    BlockListPtr blockList;
    MemoryAllocationStrategy allocationStrategy;
    MemoryFreeStrategy freeStrategy;
};

struct BlockList {
    int position;
    int size;
    struct BlockList *next;
};

MemoryPtr memory;

int getMemorySize(MemoryPtr memory);
int getMemoryAvailableSpace(MemoryPtr memory);
void setMemoryAvailableSpace(MemoryPtr memory, int availableSpace);
void *getMemoryAddress(MemoryPtr memory);
BlockListPtr getMemoryBlockList(MemoryPtr memory);

int getBlockPosition(BlockListPtr blockList);
int getBlockPosition(BlockListPtr blockList);
int getBlockSize(BlockListPtr blockList);
BlockListPtr getNextBlock(BlockListPtr blockList);
int getSizeBetweenNextBLock(BlockListPtr bl);

int isEmptyBlockList(BlockListPtr blockList);
void removeBlockHead(BlockListPtr *blockList);

int firstFit(MemoryPtr memory, int nBytes);


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

void destroyMemory(MemoryPtr memory) {
    BlockListPtr blockList = getMemoryBlockList(memory);
    destroyBlockList(blockList);
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

/***********ALLOCATION STRATEGY*********/

int firstFit(MemoryPtr memory, int nBytes) {
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
    return position;
}

void *allocMemory(int nBytes, MemoryPtr memory) {
    int position = firstFit(memory, nBytes);
    displayMemory(memory);
    return getMemoryAddress(memory) + position;
}

int freeMemoryBlock(void *p, MemoryPtr m) {
    /* Check if the pointer is valid*/
    if (p == NULL) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    BlockListPtr bl = getMemoryBlockList(m);
    int position = p - getMemoryAddress(m);
    /* Partial search of the block in the blockList*/
    removeBlock(bl, position, m);
    displayMemory(m);
    return 0;
}

/********** BlockList ********/


int getBlockPosition(BlockListPtr blockList) {
    return blockList->position;
}

int getBlockSize(BlockListPtr blockList) {
    return blockList->size;
}

BlockListPtr getNextBlock(BlockListPtr blockList) {
    return blockList->next;
}

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

void displayBlockList(BlockListPtr blockList) {
    while (!isEmptyBlockList(blockList)) {
        printf("%d\t\t| %d\n", getBlockPosition(blockList), getBlockSize(blockList));
        blockList = getNextBlock(blockList);
    }
}

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

BlockListPtr *searchBlock(BlockListPtr *blockList, int position) {
    if (isEmptyBlockList(*blockList)) {
        return blockList;
    }
    else if (getBlockPosition(*blockList) == position) {
        return blockList;
    }
    else {
        searchBlock(&(*blockList)->next, position);
    }
}

void removeBlock(BlockListPtr blockList, int position, MemoryPtr memory) {
    BlockListPtr *block;
    if ((block = searchBlock(&blockList, position)) != NULL) {
        int blockSize = getBlockSize(*block);
        removeBlockHead(block);
        setMemoryAvailableSpace(memory, getMemoryAvailableSpace(memory) + blockSize);
    }
}

void removeBlockHead(BlockListPtr *blockList) {
    BlockListPtr tmp;
    tmp = *blockList;
    *blockList = getNextBlock(*blockList);
    free(tmp);
}

void destroyBlockList(BlockListPtr blockList) {
    while (!isEmptyBlockList(blockList)) {
        removeBlockHead(&blockList);
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