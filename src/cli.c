#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "command.h"

extern char *optarg;
extern int optind;

int cli(int argc, char *argv[]) {
    /**
     * We start at optind -1 because the cli option requires at least one argument 
     * 
     */
    for (optind = optind - 1; optind < argc; optind++) {
        inputHandler(argv[optind], strlen(argv[optind]));
    }
}