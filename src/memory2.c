#include <stdio.h>
#include <stdlib.h>
#include "memory2.h"

struct Memory {
    int size;
    int availableSpace;
    void *address;
    BlockListPr blockList;
};

struct BlockList {
    int position;
    int size;
    struct BlockList *next;
};

MemoryPtr createMemory(int size);
void destroyMemory(MemoryPtr memory);
void displayMemory(MemoryPtr memory);

int getMemorySize(MemoryPtr memory);
int getMemoryAvailableSpace(MemoryPtr memory);
void setMemoryAvailableSpace(MemoryPtr memory, int availableSpace);
void *getMemoryAddress(MemoryPtr memory);
BlockListPr getMemoryBlockList(MemoryPtr memory);

int firstFit(int blockSize, MemoryPtr memory);
void *allocMemory(int nBytes, MemoryPtr memory);

BlockListPr createBlockList(void);
void addBlock(BlockListPr blockList, int size, int position);
void removeBlock(BlockListPr blockList, int position);
void destroyBlockList(BlockListPr blockList);

int getBlockPosition(BlockListPr blockList);
int getBlockPosition(BlockListPr blockList);
int getBlockSize(BlockListPr blockList);
BlockListPr getNextBlock(BlockListPr blockList);

int isEmptyBlockList(BlockListPr blockList);
int getSizeBetweenNextBLock(BlockListPr bl);
void removeBlockHead(BlockListPr blockList, MemoryPtr memory);


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

BlockListPr getMemoryBlockList(MemoryPtr memory) {
    return memory->blockList;
}

MemoryPtr createMemory(int size) {
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
        memory->blockList = createBlockList();
    }
    return memory;
}

void destroyMemory(MemoryPtr memory) {
    BlockListPr blockList = getMemoryBlockList(memory);
    destroyBlockList(blockList);
    free(memory);
}

void displayMemory(MemoryPtr memory) {
    printf("TOTAL SPACE = %d\n", getMemorySize(memory));
    printf("AVAILABLE SPACE = %d\n", getMemoryAvailableSpace(memory));
    printf("Block\t|Position\t|Size\n");
    BlockListPr bl = getMemoryBlockList(memory);
    int i = 0;
    while (!isEmptyBlockList(bl)) {
        printf("%d\t| %d\t\t| %d\n", i, getBlockPosition(bl), getBlockSize(bl));
        i++;
        bl = getNextBlock(bl);
    }
    printf("--------------------------\n");
}

int firstFit(int blockSize, MemoryPtr memory) {
    if (getMemoryAvailableSpace(memory) < blockSize) {
        perror("Couldn't allocate block, not enough space");
        exit(EXIT_FAILURE);
    }
    int position = 0;
    //To set global memory attributes, use the adress and &.
    BlockListPr bl = getMemoryBlockList(memory);
    if (!isEmptyBlockList(bl)) {
        while (getNextBlock(bl) != NULL && getSizeBetweenNextBLock(bl) < blockSize) {
            bl = getNextBlock(bl);
            position++;
        }
        //TODO handle no space found
    }
    addBlock(bl, position, blockSize);
    setMemoryAvailableSpace(memory, getMemoryAvailableSpace(memory) - blockSize);
    return position;
}

void *allocMemory(int nBytes, MemoryPtr memory) {
    int position = firstFit(nBytes, memory);
    displayMemory(memory);
    return getMemoryAddress(memory) + position;
}

/********** BlockList ********/


int getBlockPosition(BlockListPr blockList) {
    return blockList->position;
}

int getBlockSize(BlockListPr blockList) {
    return blockList->size;
}

BlockListPr getNextBlock(BlockListPr blockList) {
    return blockList->next;
}

BlockListPr createBlockList(void) {
    BlockListPr blocklist = (BlockListPr)malloc(sizeof(*blocklist));
    if (blocklist == NULL) {
        perror("Couldn't allocate memory in function createBlockList()");
        exit(EXIT_FAILURE);
    }
    return blocklist;
}

int isEmptyBlockList(BlockListPr blockList) {
    return blockList == NULL;
}

int getSizeBetweenNextBLock(BlockListPr bl) {
    return getBlockPosition(getNextBlock(bl)) - (getBlockPosition(bl) + getBlockSize(bl));
}

void addBlock(BlockListPr blockList, int size, int position) {
    BlockListPr block = createBlockList();
    if (block == NULL) {
        perror("Couldn't allocate memory in function addBlock()");
        exit(EXIT_FAILURE);
    }
    block->position = position;
    block->size = size;
    block->next = blockList;
    blockList = block;
}

void removeBlock(BlockListPr blockList, int position) {

}

void removeBlockHead(BlockListPr blockList, MemoryPtr memory) {
    BlockListPr tmp;
    tmp = blockList;
    int size = getBlockSize(blockList);
    blockList = getNextBlock(blockList);
    free(tmp);
    setMemoryAvailableSpace(memory, getMemoryAvailableSpace(memory) + size);
}

void destroyBlockList(BlockListPr blockList) {

}