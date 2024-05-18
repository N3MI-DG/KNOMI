#ifndef TOOLCHANGER_H
#define TOOLCHANGER_H

#include <WString.h>

typedef enum {
    TC_UNINITALIZED,
    TC_INITIALIZING,
    TC_READY,
    TC_DOCKING,
    TC_SELECTING,
    TC_ERROR
} tc_state_t;

String tc_status[6] = {
    "uninitialized",
    "initializing",
    "ready",
    "docking",
    "selecting",
    "error"
};

// bool tool_init = false;
tc_state_t tc_previous_state = TC_UNINITALIZED;
int8_t previous_tool = -1;

#endif
