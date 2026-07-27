#ifndef COMMON_INC_SHDN_H_
#define COMMON_INC_SHDN_H_

#include <QUTMS_can.h>
#include "stdbool.h"
#include <stdint.h>

typedef struct SHDN_SHUTDOWN_TRIGGERED_t {
    uint32_t id;
} SHDN_SHUTDOWN_TRIGGERED_t;

SHDN_TRIGGERED_TRIGGERED_t Compose_SHDN_SHUTDOWN_TRIGGERED();

#endif