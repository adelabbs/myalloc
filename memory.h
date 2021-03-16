#ifndef _MEMORY_H_
#define _MEMORY_H_

/* initialization of the work area */
int initMemory(int nBytes);
/* dynamic memory allocation in the area */
int myalloc(int nBytes);
/* deallocation of a zone addressed by a pointer */
int myfree(void* p);
/* free of the area initially reserved */
int freeMemory();

#endif /* _MEMORY_H_ */