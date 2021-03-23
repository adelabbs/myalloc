all : firstfit cli

memory.o : memory.c memory.h
	gcc -c memory.c

util.o : util.c util.h
	gcc -c util.c

options.o : options.c options.h
	gcc -c options.c

testFirstFit.o : testFirstFit.c
	gcc -c testFirstFit.c

batch.o : batch.c batch.h memory.h options.h
	gcc -c batch.c

clmode.o : clmode.c batch.h memory.h options.h
	gcc -c clmode.c

firstfit : memory.o testFirstFit.o
	gcc memory.o testFirstFit.o -o firstfit

cli : memory.o clmode.o batch.o options.o util.o
	gcc memory.o clmode.o batch.o options.o util.o -o cli

clean :
	rm -f firstfit cli *.o