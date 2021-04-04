#ifndef _MEMORY2_H_
#define _MEMORY2_H_

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

BlockListPtr createBlockList(void);
void destroyBlockList(BlockListPtr blockList);
void addBlock(BlockListPtr blockList, int size, int position);
void removeBlock(BlockListPtr blockList, int position, MemoryPtr memory);


MemoryPtr createMemory(int size);
void destroyMemory(MemoryPtr memory);
void displayMemory(MemoryPtr memory);
void *allocMemory(int nBytes, MemoryPtr memory);
int freeMemory(void *p, MemoryPtr m);
/**
 * @brief initialization of the work area
 *
 * @param nBytes
 * @return int
 */
int initMemory(int nBytes);

/**
 * @brief dynamic memory allocation in the area
 *
 * @param nBytes
 * @return void*
 */
void *myalloc(int nBytes);

/**
 * @brief deallocation of a zone addressed by a pointer
 *
 * @param p
 * @return int
 */
int myfree(void *p);

/**
 * @brief free of the area initially reserved
 *
 * @return int
 */
int freeMemory();

#endif /* _MEMORY_H_ */