#ifndef _OPTIONS_H_
#define _OPTIONS_H_

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

#endif /*_OPTIONS_H_*/