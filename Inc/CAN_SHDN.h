#ifndef COMMON_INC_SHDN_H_
#define COMMON_INC_SHDN_H_

#include <QUTMS_can.h>
#include "stdbool.h"
#include <stdint.h>

typedef struct SHDN_SHUTDOWN_TRIGGERED_t {
    uint32_t id;
} SHDN_SHUTDOWN_TRIGGERED_t;

SHDN_SHUTDOWN_TRIGGERED_t Compose_SHDN_SHUTDOWN_TRIGGERED() {
    SHDN_SHUTDOWN_TRIGGERED_t p;
    p.id = QUTMS_SHDN_SHUTDOW_TRIGGERED;
    return p;
}

#endif