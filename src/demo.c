#include <stdio.h>
#include "core.h"
#include "util.h"

int log_fd;

int main(void) {
    initLog(&log_fd, LOG_PATH_DEFAULT);
    writeLog("Launching", SEVERITY_INFO, log_fd);

    writeLog("initMemory(100)", SEVERITY_INFO, log_fd);
    initMemory(100);

    writeLog("myalloc(15)", SEVERITY_INFO, log_fd);
    void *block1 = myalloc(15);

    writeLog("myalloc(20)", SEVERITY_INFO, log_fd);
    void *block2 = myalloc(20);

    writeLog("myalloc(15)", SEVERITY_INFO, log_fd);
    void *block3 = myalloc(15);

    writeLog("myalloc(40)", SEVERITY_INFO, log_fd);
    void *block4 = myalloc(40);

    writeLog("block4 = myfree(block4)", SEVERITY_INFO, log_fd);
    myfree(block4);

    writeLog("myalloc(40)", SEVERITY_INFO, log_fd);
    void *block5 = myalloc(40);

    writeLog("myfree(block5)", SEVERITY_INFO, log_fd);
    myfree(block5);

    writeLog("freeMemory()", SEVERITY_INFO, log_fd);
    freeMemory();

    writeLog("End of demo", SEVERITY_INFO, log_fd);
    return 0;
}