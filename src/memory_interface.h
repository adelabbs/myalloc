#ifndef _MEMORY_INTERFACE_H_
#define _MEMORY_INTERFACE_H_

/**
 * @brief A pointer to the incomplete BlockList type (hides the implementation details, to make future extensions easier).
 *
 */
typedef struct BlockList *BlockListPtr;

/**
 * @brief A pointer to the incomplete Memory type (hides the implementation details)
 *
 */
typedef struct Memory *MemoryPtr;

typedef void *(*MemoryAllocationStrategy)(MemoryPtr memory, int nBytes);
typedef int (*MemoryFreeStrategy)(MemoryPtr memory, void *p);

extern MemoryPtr memory;

BlockListPtr createBlockList(void);
void destroyBlockList(BlockListPtr blockList);
void addBlock(BlockListPtr blockList, int size, int position);
int removeBlock(BlockListPtr blockList, int position, MemoryPtr memory);
int countBlocks(BlockListPtr bl);


MemoryPtr createMemory(int size, MemoryAllocationStrategy allocationStrategy, MemoryFreeStrategy freeStrategy);
void destroyMemory(MemoryPtr memory);
void displayMemory(MemoryPtr memory);
MemoryAllocationStrategy allocationStrategy(MemoryPtr memory);
MemoryFreeStrategy freeStrategy(MemoryPtr memory);

#endif /* _MEMORY_INTERFACE_H_ */