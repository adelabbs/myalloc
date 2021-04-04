#include <stdio.h>
#include "memory2.h"

int main(void) {
    MemoryPtr m = createMemory(100);
    displayMemory(m);
    allocMemory(15, m);
    allocMemory(15, m);
    void *p = allocMemory(15, m);
    freeMemory(p, m);
    return 0;
}