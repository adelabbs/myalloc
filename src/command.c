#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "command.h"
#include "memory.h"
#include "util.h"
#include "types.h"

int readPositiveInt(char *field);
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
    void **addresses;
    switch (command) {
    case COMMAND_INIT:
        addresses = initCommandHandler(fields, FIELDS_COUNT);
        break;
    case COMMAND_ALLOC:
        allocCommandHandler(fields, FIELDS_COUNT, addresses);
        break;
    case COMMAND_FREE:
        freeCommandHandler(fields, FIELDS_COUNT, addresses);
        break;
    }
}

void **initCommandHandler(char **fields, int n) {
    char *sizeField = fields[1];
    int size;
    void **addresses = NULL;
    if ((size = readPositiveInt(sizeField)) >= 0) {
        initMemory(size);
        addresses = (void **)malloc(size * sizeof(void *));
        if (addresses == NULL) {
            writeLog("Couldn't allocate memory", SEVERITY_ERROR, log_fd);
            exit(EXIT_FAILURE);
        }
    }
    return addresses;
}

void allocCommandHandler(char **fields, int n, void **addresses) {
    char *sizeField = fields[1];
    char *idField = fields[2];
    int size, id;
    if (((size = readPositiveInt(sizeField)) >= 0) && ((id = readPositiveInt(idField)) >= 0)) {
        void *address = myalloc(size);
        addresses[id] = address;
    }
}

void freeCommandHandler(char **fields, int n, void **addresses) {
    char *idField = fields[1];
    int id;
    if ((id = readPositiveInt(idField)) >= 0) {
        myfree(addresses[id]);
    }
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

int readPositiveInt(char *field) {
    int n = atoi(field);
    return (n > 0) ? n : -1;
}