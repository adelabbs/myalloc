#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void removeBlockHead(BlockList *bl);
void freeBlockList(BlockList *bl);

MemorySpace memory;

int initMemory(int nBytes) {
  /* MemorySpace Settings*/
  memory.size = nBytes;
  memory.availableSpace = nBytes;
  /* Main memory bloc allocation*/
  void * block = malloc(nBytes);
  if(block == NULL) {
    perror("Couldn't allocate memory in function initMemory()");
    exit(EXIT_FAILURE);
  }
  memory.block  = block;
  memory.blocks = initBlockList();
  return 0; 
}

void *myalloc(int nBytes) {
  //TODO
}

int myfree(void *p) {
  //TODO

}

int freeMemory() {
  BlockList *bl = &(memory.blocks);
  freeBlockList(bl);
  free(memory.block);
  //memory = NULL; //?
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
    if(block == NULL){
      perror("Couldn't allocate memory in function addBlock()");
      exit(EXIT_FAILURE);
    }
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

void freeBlockList(BlockList *bl){
  while(!isEmptyBlockList(*bl)){
    removeBlockHead(bl);
  }
}