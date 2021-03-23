all : firstfit cli

memory.o : memory.c memory.h
	gcc -c memory.c

testFirstFit.o : testFirstFit.c
	gcc -c testFirstFit.c

clmode.o : clmode.c memory.h options.h
	gcc -c clmode.c

firstfit : memory.o testFirstFit.o
	gcc memory.o testFirstFit.o -o firstfit

cli : memory.o clmode.o
	gcc memory.o clmode.o -o cli

clean :
	rm -f firstfit cli *.o