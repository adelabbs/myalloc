#ifndef _UTIL_H_
#define _UTIL_H_

#include "types.h"

extern int log_fd;

void initLog(int *fd, char *file);
void writeLog(char *message, LogSeverityType severity, int fd);

#endif /*_UTIL_H_*/