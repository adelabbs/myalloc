#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

extern char *optarg;
extern int optind;

void displayMemorySpace(){
  printf("TOTAL SPACE = %d\n", getMemorySize(memory));
  printf("AVAILABLE SPACE = %d\n", getMemoryAvailableSpace(memory));
  printf("Block\t|Position\t|Size\n");
  BlockList bl = memory.blocks;
  int i = 0;
  while(!isEmptyBlockList(bl)){
    printf("%d\t\t| %d\t\t\t| %d\n", i, getBlockPosition(bl), getBlockSize(bl));
    i++;
    bl = getNextBlock(bl);
  }
  printf("--------------------------\n");
}

int firstFit(int blockSize){
  if(getMemoryAvailableSpace(memory) < blockSize){
    perror("Couldn't allocate block, not enough space");
    exit(EXIT_FAILURE);
  } 
  int position = 0;
  //To set global memory attributes, use the adress and &.
  BlockList *bl = &(memory.blocks);
  if(!isEmptyBlockList(*bl)) {
    while(getNextBlock(*bl) != NULL && getSizeBetweenNextBLock(*bl) < blockSize){
      *bl = getNextBlock(*bl);
      position++;
    }
    //TODO handle no space found
  }
  addBlock(bl, position, blockSize);
  setMemoryAvailableSpace(&memory, blockSize);
  return 0;
}

/*Test*/
int main(){
  int sizeMax = 50;
  int myBloc = 25;
  initMemory(sizeMax);
  firstFit(myBloc);
  displayMemorySpace();
  return 0;
}