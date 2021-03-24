#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <fcntl.h> //for file flags
#include <unistd.h> //for write function
#include "util.h"

extern int log_fd;

/**
 * @brief get the current timestamp
 *
 * @return char*
 */
char *timestamp() {
    time_t rawtime;
    struct tm *info;
    char *timestamp = (char *)malloc(30 * sizeof(char));
    if (timestamp == NULL) {
        perror("Couldn't allocate memory in function get_timestamp()");
        exit(EXIT_FAILURE);
    }
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, 30, "%Y-%m-%d %X", info);

    return timestamp;
}

void initLog(int *fd, char *file) {
    *fd = open(file, O_CREAT | O_WRONLY | O_APPEND,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (*fd == -1) {
        perror("Couldn't open log file as output");
    }
}

/**
 * @brief
 *
 * @param message
 * @param severity
 * @param fd output file descriptor
 */
void writeLog(char *message, LogSeverityType severity, int fd) {
    char *buf = (char *)malloc(150 + 1 * sizeof(char));
    if (buf == NULL) {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    snprintf(buf, 150, "[%s] %s %s\n", severity_types[severity], timestamp(), message);
    printf("%s", buf);
    if (write(fd, buf, strlen(buf)) == -1) {
        perror("Couldn't write in log file");
    }
}