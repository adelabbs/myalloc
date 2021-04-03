#include <stdio.h>
#include "memory2.h"

int main(void) {
    MemoryPtr m = createMemory(100);
    displayMemory(m);
    allocMemory(15, m);
    return 0;
}