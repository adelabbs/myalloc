#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

extern char *optarg;
extern int optind;
extern MemorySpace memory;

void displayMemorySpace(){
  printf("TOTAL SPACE = %d\n", getMemorySize(memory));
  printf("AVAILABLE SPACE = %d\n", getMemoryAvailableSpace(memory));
  printf("Block\t|Position\t|Size");
  BlockList bl = getBlockList(memory);
  int i = 0;
  while(!isEmptyBlockList(bl)){
    printf("%d\t%d\t%d\t", i, getBlockPosition(bl), getBlockSize(bl));
    i++;
  }
  printf("--------------\n");
}

int firstFit(int blockSize){
  if(getMemoryAvailableSpace(memory) < blockSize){
    perror("Couldn't allocate block, not enough space");
    exit(EXIT_FAILURE);
  } 
  int position = 0;
  BlockList bl = getBlockList(memory);
  if(!isEmptyBlockList(bl)) {
    while(getNextBlock(bl) != NULL && getSizeBetweenNextBLock(bl) < blockSize){
      bl = getNextBlock(bl);
      position++;
    }
    //TODO traiter no space found
  }
  printf("YEP\n");
  addBlock(&bl, position, blockSize);
  printf("%d\n", getBlockPosition(bl));
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