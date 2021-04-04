all : firstfit cli gui

memory.o : memory.c memory.h
	gcc -c memory.c

util.o : util.c util.h types.h
	gcc -c util.c

types.o : types.c types.h
	gcc -c types.c

command.o : command.c command.h memory.h util.h types.h
	gcc -c command.c

testFirstFit.o : testFirstFit.c
	gcc -c testFirstFit.c

batch.o : batch.c batch.h command.h
	gcc -c batch.c

cli.o : cli.c cli.h command.h
	gcc -c cli.c

interactive.o : interactive.c interactive.h
	gcc -c interactive.c

main.o : main.c cli.h batch.h interactive.h util.h
	gcc -c main.c

gui.o : memory.h batch.h command.h util.h types.h
	gcc -c gui.c `pkg-config --cflags --libs gtk+-3.0`

firstfit : memory.o testFirstFit.o
	gcc memory.o testFirstFit.o -o firstfit

cli : main.o memory.o cli.o batch.o types.o util.o command.o interactive.o 
	gcc main.o memory.o batch.o cli.o types.o util.o command.o interactive.o -o cli

gui : gui.o batch.o command.o util.o memory.o types.o
	gcc -o gui gui.o batch.o command.o util.o memory.o types.o -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

clean :
	rm -f firstfit cli gui *.o