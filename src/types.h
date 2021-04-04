#ifndef _TYPES_H_
#define _TYPES_H_

enum MyAllocModeType {
    RUN_EXIT = 0, /*exit*/
#define RUN_EXIT RUN_EXIT
    RUN_INTERACTIVE = 1, /*Interactive mode*/
#define RUN_INTERACTIVE RUN_INTERACTIVE
    RUN_CLI = 2, /*Command-line mode*/
#define RUN_CLI RUN_CLI
    RUN_BATCH = 3/*Batch mode*/
#define RUN_BATCH RUN_BATCH
};

/**
 * @brief Supported command types
 * 
 */
typedef enum {
  COMMAND_INIT,
  COMMAND_ALLOC,
  COMMAND_FREE,
  COMMAND_UKN 
}  CommandType;

#define COMMAND_CODES_COUNT 3
extern const char *commandCodes[COMMAND_CODES_COUNT];

/**
 * @brief Log Severity Types
 * 
 */
typedef enum {
    SEVERITY_EMERGENCY,
    SEVERITY_ALERT,
    SEVERITY_CRITICAL,
    SEVERITY_ERROR,
    SEVERITY_WARNING,
    SEVERITY_INFO,
    SEVERITY_DEBUG
}LogSeverityType;

#define SEVERITY_TYPES_COUNT 7
extern const char *severity_types[SEVERITY_TYPES_COUNT];
#define LOG_PATH_DEFAULT "./myalloc.log"

#endif /*_TYPES_H_*/