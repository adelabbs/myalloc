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
  void *block = malloc(nBytes);
  if (block == NULL) {
    perror("Couldn't allocate memory in function initMemory()");
    exit(EXIT_FAILURE);
  }
  memory.generalBlock = block;
  memory.blocks = initBlockList();
  return 0;
}

void *myalloc(int nBytes) {
  firstFit(nBytes);
  displayMemorySpace();
}

int myfree(void *p) {
  /* Check if the pointer is valid*/
  if(&p == NULL) {
    perror("Couldn't find the block in function myfree()");
    exit(EXIT_FAILURE);
  }
  /* Partial search of the block in the blockList*/
  BlockList bl = getBlockList(memory);
  int cpt = 0;
  while(p != bl && cpt < getBlockSize(bl)) {
    bl = getNextBlock(bl);
    cpt++;
  }
  
  if(getNextBlock(bl) != NULL) {
    /* Modifiy chain  and partial research of the previous block*/
    BlockList previousBlock = getBlockList(memory);
    while(getNextBlock(previousBlock) != bl) {
      previousBlock = getNextBlock(previousBlock);      
    }
    previousBlock->next = getNextBlock(bl);
  }
  /* Set the block to null */
  bl = NULL;
}

int freeMemory() {
  BlockList *bl = &(memory.blocks);
  freeBlockList(bl);
  free(memory.generalBlock);
  //memory = NULL; //?
}

int getMemorySize(MemorySpace m) {
  return m.size;
}

int getMemoryAvailableSpace(MemorySpace m) {
  return m.availableSpace;
}

void setMemoryAvailableSpace(MemorySpace *m, int size) {
  m->availableSpace = getMemoryAvailableSpace(*m) - size;
}

void *getMemoryBlock(MemorySpace m) {
  return m.generalBlock;
}

BlockList getBlockList(MemorySpace m) {
  return m.blocks;
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
  if (block == NULL) {
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

void freeBlockList(BlockList *bl) {
  while (!isEmptyBlockList(*bl)) {
    removeBlockHead(bl);
  }
}


void displayMemorySpace() {
  printf("TOTAL SPACE = %d\n", getMemorySize(memory));
  printf("AVAILABLE SPACE = %d\n", getMemoryAvailableSpace(memory));
  printf("Block\t|Position\t|Size\n");
  BlockList bl = getBlockList(memory);
  int i = 0;
  while (!isEmptyBlockList(bl)) {
    printf("%d\t\t| %d\t\t\t| %d\n", i, getBlockPosition(bl), getBlockSize(bl));
    i++;
    bl = getNextBlock(bl);
  }
  printf("--------------------------\n");
}

int firstFit(int blockSize) {
  if (getMemoryAvailableSpace(memory) < blockSize) {
    perror("Couldn't allocate block, not enough space");
    exit(EXIT_FAILURE);
  }
  int position = 0;
  //To set global memory attributes, use the adress and &.
  BlockList *bl = &(memory.blocks);
  if (!isEmptyBlockList(*bl)) {
    while (getNextBlock(*bl) != NULL && getSizeBetweenNextBLock(*bl) < blockSize) {
      *bl = getNextBlock(*bl);
      position++;
    }
    //TODO handle no space found
  }
  addBlock(bl, position, blockSize);
  setMemoryAvailableSpace(&memory, blockSize);
  return 0;
}
