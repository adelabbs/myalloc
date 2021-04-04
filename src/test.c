#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "batch.h"
#include "cli.h"
#include "interactive.h"
#include "util.h"

void display_options();
void interactiveModeHandler();
void batchModeHandler();
void cliModeHandler();

extern char *optarg;
extern int optind;

int log_fd;

int main(int argc, char *argv[]) {
    char format[] = "hif:c:";
    int mode = RUN_INTERACTIVE;
    int option;

    initLog(&log_fd, LOG_PATH_DEFAULT);
    writeLog("Launching", SEVERITY_DEBUG, log_fd);
    if (argc == 1) {
        display_options(argv[0]);
    }
    while ((option = getopt(argc, argv, format)) != -1) {
        switch (option) {
        case 'h':
            display_options(argv[0]);
            break;
        case 'i':
            interactiveModeHandler();
            break;
        case 'f':
            batchModeHandler();
            break;
        case 'c':
            cliModeHandler(argc, argv);
            break;
        default:			// All the other options are considered invalid.
            printf("Invalid command-line options. Please run using -h to list the available options.\n");
            return 1;
        }
    }
    return 0;
}

void display_options(char *usage) {
    printf("Usage:\n%s [-hi] or[-f filePath] or [-c] [s:size] ([a:blockSize:blockId] || [f:blockId])^n \n", usage);
    printf("   -h : display this help\n");
    printf("   -i : interactive mode\n");
    printf("   -f : batch mode (execute a command file)\n");
    printf("   -c : command-line mode | format example: -c s:100 a:25:1 f:1 \n");
}

void interactiveModeHandler() {
    writeLog("Running interactive mode", SEVERITY_INFO, log_fd);
    interactiveMode();
}

void batchModeHandler() {
    writeLog("Running batch mode", SEVERITY_INFO, log_fd);
    char log[100];
    sprintf(log, "Interpreted file as %s", optarg);
    writeLog(log, SEVERITY_DEBUG, log_fd);
    batch(optarg);
}

void cliModeHandler(int argc, char *argv[]) {
    writeLog("Running cli mode", SEVERITY_INFO, log_fd);
    cli(argc, argv);
}