#ifndef _CORE_H_
#define _CORE_H_

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

#endif /* _CORE_H_ */