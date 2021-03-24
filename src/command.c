#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "command.h"
#include "memory.h"
#include "util.h"
#include "types.h"

int readSize(char *sizeField);
extern int log_fd;

void inputHandler(char *buffer, int maxBufferSize) {
    char log[100];
    snprintf(log, 100, "Read '%s'", buffer);
    writeLog(log, SEVERITY_DEBUG, log_fd);

    char **fields = parseData(buffer, FIELDS_COUNT, SEPARATOR);
    if (fields == NULL) {
        writeLog("Couldn't parse input", SEVERITY_ERROR, log_fd);
        exit(EXIT_FAILURE);
    }

    CommandType command = detectCommand(fields, FIELDS_COUNT);

    switch (command) {
    case COMMAND_INIT:
        initCommandHandler(fields, FIELDS_COUNT);
        break;
    case COMMAND_ALLOC:
        allocCommandHandler(fields, FIELDS_COUNT);
        break;
    case COMMAND_FREE:
        freeCommandHandler(fields, FIELDS_COUNT);
        break;
        //TODO add default
    }
}

void initCommandHandler(char **fields, int n) {
    char *sizeField = fields[1];
    int size;
    if ((size = readSize(sizeField)) >= 0) {
        initMemory(size);
    }
}

void allocCommandHandler(char **fields, int n) {
    char *sizeField = fields[1];
    int size;
    if ((size = readSize(sizeField)) >= 0) {
        //TODO handle id field
        myalloc(size);
    }
}

void freeCommandHandler(char **fields, int n) {
    //TODO
}


/**
 * @brief This utility function can be used to parse data separated by a using string delimiter.
 *
 * @param data
 * @param fieldsCount Maximum number of fields expected
 * @param separator
 * @return NULL if the data is not in the correct format or an array of fields
 */
char **parseData(char *data, int count, char *separator) {
    int correct = 0, cpt = 0;
    char **fields = (char **)malloc(count * sizeof(char *));
    if (fields == NULL) {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    char *field = strtok(data, separator);
    while (field != NULL && cpt < count) {
        fields[cpt] = field;
        cpt++;
        field = strtok(NULL, separator);
    }
    //Check data
    if ((field == NULL) && (cpt <= count)) {
        correct = 1;
    }
    return (correct) ? fields : NULL;
}

/**
 * @brief Detects the command type
 *
 * @param fields
 * @param n
 * @return CommandType
 */
CommandType detectCommand(char **fields, int n) {
    CommandType command = COMMAND_UKN;
    if (n > 0) {
        char *commandSlug = fields[0];
        if (strcmp(commandSlug, commandCodes[COMMAND_INIT]) == 0) {
            command = COMMAND_INIT;
        }
        else if (strcmp(commandSlug, commandCodes[COMMAND_ALLOC]) == 0) {
            command = COMMAND_ALLOC;
        }
        else if (strcmp(commandSlug, commandCodes[COMMAND_FREE]) == 0) {
            command = COMMAND_FREE;
        }
    }
    return command;
}

int readSize(char *sizeField) {
    int size = atoi(sizeField);
    return (size > 0) ? size : -1;
}