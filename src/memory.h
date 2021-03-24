#ifndef _MEMORY_H_
#define _MEMORY_H_

typedef struct block {
    int position;
    int size;
    struct block *next;
} *BlockList;

typedef struct {
    int size;
    int availableSpace;
    void *block;
    BlockList blocks;
    /*
    pthread_mutex_t lock;
    pthread_cond_t cond;
    */
} MemorySpace;

extern MemorySpace memory;

/* MemorySpace functions */
int getMemorySize(MemorySpace m);
int getMemoryAvailableSpace(MemorySpace m);
void setMemoryAvailableSpace(MemorySpace *m, int size);
void *getMemoryBlock(MemorySpace m);
BlockList getBlockList(MemorySpace m);
void displayMemorySpace();
int firstFit(int blockSize);

/* BlockList functions */
/**
 * @brief
 *
 * @param bl
 * @return int 0 if the list is empty
 */
int isEmptyBlockList(BlockList bl);
BlockList initBlockList();

BlockList getNextBlock(BlockList bl);
/**
 * @brief Get the Position object
 *
 * @param bl
 * @return int
 */
int getBlockPosition(BlockList bl);

/**
 * @brief Get the Size object
 *
 * @param bl
 * @return int
 */
int getBlockSize(BlockList bl);

/**
 * @brief Get the Size Between Next B Lock object
 *
 * @param bl
 * @return int
 */
int getSizeBetweenNextBLock(BlockList bl);

/**
 * @brief
 *
 * @param bl
 * @param position
 * @param size
 */
void addBlock(BlockList *bl, int position, int size);

/**
 * @brief
 *
 * @param bl
 * @param position
 */
void removeBlock(BlockList *bl, int position);

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