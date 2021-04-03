#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

void removeBlockHead(BlockList *bl);
void freeBlockList(BlockList *bl);
int countBlocks(BlockList bl);

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
  int position = firstFit(nBytes);
  displayMemorySpace();
  return getMemoryBlock(memory) + position;
}

int myfree(void *p) {
  /* Check if the pointer is valid*/
  if (p == NULL) {
    perror("Couldn't find the block in function myfree()");
    exit(EXIT_FAILURE);
  }
  BlockList *bl = &(memory.blocks);
  int position = p - getMemoryBlock(memory);
  /* Partial search of the block in the blockList*/
  removeBlock(bl, position);
  displayMemorySpace();
  return 0;
}

int freeMemory() {
  BlockList *bl = &(memory.blocks);
  freeBlockList(bl);
  free(memory.generalBlock);
  //memory = NULL; //?
  return 0;
}

int getMemorySize(MemorySpace m) {
  return m.size;
}

int getMemoryAvailableSpace(MemorySpace m) {
  return m.availableSpace;
}

void setMemoryAvailableSpace(MemorySpace *m, int size) {
  m->availableSpace = size;
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
  int size = getBlockSize(*bl);
  *bl = getNextBlock(*bl);
  free(tmp);
  setMemoryAvailableSpace(&memory, getMemoryAvailableSpace(memory) + size);
}

BlockList *searchBlock(BlockList *bl, int position) {
  if (isEmptyBlockList(*bl) || position == 0) {
    return bl;
  }
  else {
    searchBlock(&((*bl)->next), position - getBlockSize(*bl));
  }
}

void removeBlock(BlockList *bl, int position) {
  BlockList *block;
  if ((block = searchBlock(bl, position)) != NULL) {
    removeBlockHead(block);
  }
}

void freeBlockList(BlockList *bl) {
  while (!isEmptyBlockList(*bl)) {
    removeBlockHead(bl);
  }
}

int countBlocks(BlockList bl) {
  int blocks = 0;
  while (bl != NULL) {
    bl = getNextBlock(bl);
    blocks++;
  }
  return blocks;
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
  setMemoryAvailableSpace(&memory, getMemoryAvailableSpace(memory) - blockSize);
  return position;
}

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