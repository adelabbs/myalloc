#include "memory2.h"

#include <stdio.h>
#include <stdlib.h>
#include "memory2.h"

struct Memory {
    int size;
    int space;
    int requests;
    //autant de nouveaux attributs
};

MemoryPtr createMemory(int size) {
    MemoryPtr memory = (MemoryPtr)malloc(sizeof(*memory));

    if (memory != NULL) {
        memory->size = size;
        //remplir les autres éléments

    }
    //remplir les éléments de la structure
    return memory;
}