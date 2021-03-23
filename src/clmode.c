#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memory.h"
#include "options.h"

extern char *optarg;
extern int optind;

void display_options();

void interactiveModeHandler();
void batchModeHandler();
void cliModeHandler();

int main(int argc, char *argv[]) {
    char format[] = "hib:c:";
    int mode = RUN_INTERACTIVE;
    int option;
    while ((option = getopt(argc, argv, format)) != -1) {
        switch (option) {
        case 'h':
            display_options(argv[0]);
            break;
        case 'i':
            interactiveModeHandler();
            break;
        case 'b':
            batchModeHandler();
            break;
        case 'c':
            cliModeHandler();
            break;
        default:			// All the other options are considered invalid.
            printf("Invalid command-line options. Please run using -h to list the available options.\n");
            return 1;
        }
    }
    //TODO Call run
}

void display_options(char *usage) {
    printf("Usage:\n%s [-hi] or[-b filePath] or [-c] [s:size] ([a:blockSize:blockId] || [f:blockId])^n \n", usage);
    printf("   -h : display this help\n");
    printf("   -i : interactive mode\n");
    printf("   -b : batch mode\n");
    printf("   -c : command-line mode\n");
}

void interactiveModeHandler() {
    printf("running interactive mode\n");
}

void batchModeHandler() {
    printf("running batch mode\n");
    printf("Interpreted file as %s\n", optarg);
}

void cliModeHandler() {
    printf("running cli mode\n");
}