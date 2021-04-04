all : cli gui doc

doc :
	doxygen doxygen.conf

util.o : util.c util.h types.h
	gcc -c util.c

types.o : types.c types.h
	gcc -c types.c

command.o : command.c command.h core.h util.h types.h
	gcc -c command.c

batch.o : batch.c batch.h command.h
	gcc -c batch.c

cli.o : cli.c cli.h command.h
	gcc -c cli.c

interactive.o : interactive.c interactive.h
	gcc -c interactive.c

memory.o : memory.c memory.h
	gcc -c memory.c

memory_internal.o : memory_internal.c memory_internal.h memory_interface.h 
	gcc -c memory_internal.c

default_strategies.o : default_strategies.c default_strategies.h memory_internal.h 
	gcc -c  default_strategies.c

core.o : core.c core.h default_strategies.h memory_internal.h
	gcc -c  core.c

main.o : main.c cli.h batch.h interactive.h util.h
	gcc -c main.c

gui.o : memory_internal.h batch.h command.h util.h types.h
	gcc -c gui.c `pkg-config --cflags --libs gtk+-3.0`

cli : main.o core.o default_strategies.o memory_internal.o cli.o batch.o types.o util.o command.o interactive.o 
	gcc main.o core.o default_strategies.o memory_internal.o batch.o cli.o types.o util.o command.o interactive.o -o cli

gui : gui.o batch.o command.o util.o  core.o default_strategies.o memory_internal.o types.o
	gcc -o gui gui.o batch.o command.o util.o  core.o default_strategies.o memory_internal.o types.o -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

clean :
	rm -f cli gui latex html *.o