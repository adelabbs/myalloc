#include <stdio.h>
#include "core.h"

int main(void) {
    initMemory(100);
    void *p = myalloc(15);
    //myfree(p);
    return 0;
}