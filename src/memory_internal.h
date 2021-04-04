#ifndef _MEMORY_INTERNAL_H_
#define _MEMORY_INTERNAL_H_
#include "memory_interface.h"

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


#endif /* _MEMORY_INTERNAL_H_ */