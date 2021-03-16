all : myalloc

memory.o : memory.c memory.h
	gcc -c memory.c

main.o : main.c
	gcc -c main.c

myalloc : memory.o main.o
	gcc memory.o main.o -o myalloc
    
clean :
	rm -f myalloc *.o