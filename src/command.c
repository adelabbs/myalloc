#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "command.h"
#include "core.h"
#include "util.h"
#include "types.h"

int readPositiveInt(char *field);
extern int log_fd;

void initInputHandler(InputHandler *inputHandler) {
    inputHandler->addresses = NULL;
}

void createInputHandler(InputHandler *inputHandler, int addressesCount) {
    if (inputHandler != NULL) {
        void **addresses = (void **)malloc(addressesCount * sizeof(void *));
        if (addresses == NULL) {
            perror("Couldn't create commandHandler");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < addressesCount; i++) {
            addresses[i] = NULL;
        }
        inputHandler->addresses = addresses;
    }
}

void destroyInputHandler(InputHandler *inputHandler) {
    if (inputHandler != NULL) {
        if (inputHandler->addresses != NULL) {
            free(inputHandler->addresses);
        }
    }
}

/**
 * @brief
 *
 * @param inputHandler
 * @param buffer
 * @param maxBufferSize
 */
void handleInput(InputHandler *inputHandler, char *buffer, int maxBufferSize) {
    char *log = (char *)malloc(100 * sizeof(char));

    if (snprintf(log, 99, "Read '%s'", buffer) != -1) {
        writeLog(log, SEVERITY_DEBUG, log_fd);
    }
    int fieldsCount;
    char **fields = parseData(buffer, FIELDS_COUNT, SEPARATOR, &fieldsCount);
    if (fields == NULL) {
        writeLog("Couldn't parse input", SEVERITY_ERROR, log_fd);
        exit(EXIT_FAILURE);
    }

    CommandType command = detectCommand(fields, fieldsCount);

    switch (command) {
    case COMMAND_INIT:
        initCommandHandler(inputHandler, fields, fieldsCount);
        break;
    case COMMAND_ALLOC:
        allocCommandHandler(inputHandler, fields, fieldsCount);
        break;
    case COMMAND_FREE:
        freeCommandHandler(inputHandler, fields, fieldsCount);
        break;
    }
}

/**
 * @brief
 *
 * @param inputHandler
 * @param fields
 * @param n
 */
void initCommandHandler(InputHandler *inputHandler, char **fields, int n) {
    if (n == 2) {
        char *sizeField = fields[1];
        int size, r;
        if ((size = readPositiveInt(sizeField)) >= 0) {
            if ((r = initMemory(size)) == 0) {
                writeLog("Memory initialization failed", SEVERITY_ERROR, log_fd);
                exit(EXIT_FAILURE);
            }
            createInputHandler(inputHandler, size);
            if (inputHandler->addresses == NULL) {
                writeLog("Couldn't allocate memory", SEVERITY_ERROR, log_fd);
                exit(EXIT_FAILURE);
            }
        }
        else {
            writeLog("Invalid command format", SEVERITY_ERROR, log_fd);
        }
    }
    else {
        writeLog("Invalid command format", SEVERITY_ERROR, log_fd);
    }
}

/**
 * @brief
 *
 * @param inputHandler
 * @param fields
 * @param n
 */
void allocCommandHandler(InputHandler *inputHandler, char **fields, int n) {
    if (n == 3) {
        if (inputHandler->addresses != NULL) {
            char *sizeField = fields[1];
            char *idField = fields[2];
            int size, id;
            if (((size = readPositiveInt(sizeField)) >= 0) && ((id = readPositiveInt(idField)) >= 0)) {
                void *address = myalloc(size);
                if (address == NULL) {
                    writeLog("Didn't allocate block", SEVERITY_ERROR, log_fd);
                    exit(EXIT_FAILURE);
                }
                inputHandler->addresses[id] = address;
            }
            else {
                writeLog("Invalid command format", SEVERITY_ERROR, log_fd);
            }
        }
        else {
            writeLog("Memory not initialized", SEVERITY_ERROR, log_fd);

        }
    }
    else {
        writeLog("Invalid command format", SEVERITY_ERROR, log_fd);
    }
}

/**
 * @brief
 *
 * @param inputHandler
 * @param fields
 * @param n
 */
void freeCommandHandler(InputHandler *inputHandler, char **fields, int n) {
    if (n == 2) {
        if (inputHandler->addresses != NULL) {
            char *idField = fields[1];
            int id;
            int r;
            if ((id = readPositiveInt(idField)) >= 0) {
                if ((r = myfree(inputHandler->addresses[id])) == -1) {
                    writeLog("Didn't free block", SEVERITY_ERROR, log_fd);
                    exit(EXIT_FAILURE);
                }
            }
            else {
                writeLog("Invalid command format : not positive int", SEVERITY_ERROR, log_fd);
            }
        }
        else {
            writeLog("Memory not initialized", SEVERITY_ERROR, log_fd);
        }
    }
    else {
        writeLog("Invalid command format", SEVERITY_ERROR, log_fd);
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
char **parseData(char *data, int count, char *separator, int *fieldsCount) {
    int correct = 0;
    *fieldsCount = 0;
    char **fields = (char **)malloc(count * sizeof(char *));
    if (fields == NULL) {
        perror("Couldn't allocate memory");
        exit(EXIT_FAILURE);
    }
    char *field = strtok(data, separator);
    while (field != NULL && *fieldsCount < count) {
        fields[*fieldsCount] = field;
        (*fieldsCount)++;
        field = strtok(NULL, separator);
    }
    //Check data
    if ((field == NULL) && (*fieldsCount <= count)) {
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
    else {
        writeLog("Invalid command format", SEVERITY_ERROR, log_fd);
    }
    return command;
}

int readPositiveInt(char *field) {
    int n = atoi(field);
    return (n > 0) ? n : -1;
}