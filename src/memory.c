#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void removeBlockHead(BlockList *bl);

int initMemory(int nBytes) {

}

void *myalloc(int nBytes) {

}

int myfree(void *p) {


}

int freeMemory() {

}


int getMemorySize(MemorySpace *m) {
    return m->size;
}
int getMemoryAvailableSpace(MemorySpace *m) {
    return m->availableSpace;
}

void *getMemoryBlock(MemorySpace *m) {
    return m->block;
}

BlockList getBlockList(MemorySpace *m) {
    return m->blocks;
}

int isEmptyBlockList(BlockList bl) {
    return bl == NULL;
}

BlockList initBlockList() {
    return NULL;
}

BlockList getNextBlock(BlockList bl) {
    return bl->next;
}

int getBlockPosition(BlockList bl) {
    return bl->position;
}

int getBlockSize(BlockList bl) {
    return bl->size;
}

int getSizeBetweenNextBLock(BlockList bl) {
    return getBlockPosition(getNextBlock(bl)) - (getBlockPosition(bl) + getBlockSize(bl));
}

void addBlock(BlockList *bl, int position, int size) {
    BlockList block;
    block = (BlockList)malloc(sizeof(struct block));
    block->position = position;
    block->size = size;
    block->next = *bl;
    *bl = block;
}


void removeBlockHead(BlockList *bl) {
    BlockList tmp;
    tmp = *bl;
    *bl = getNextBlock(*bl);
    free(tmp);
}

void removeBlock(BlockList *bl, int position) {
    if (!isEmptyBlockList(*bl)) {
        if (getBlockPosition(*bl) == position) {
            removeBlockHead(bl);
        }
        else {
            removeBlock(&((*bl)->next), position);
        }
    }
}