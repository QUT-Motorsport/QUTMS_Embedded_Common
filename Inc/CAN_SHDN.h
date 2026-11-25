/*
 * @file CAN_SHDN.h
 * @brief CAN message definitions for the Shutdown board
 *
 * Defines all Shutdown CAN message structures and compose functions used
 * for communications between the shutdown board and other boards
 */
#ifndef COMMON_INC_SHDN_H_
#define COMMON_INC_SHDN_H_

#include <QUTMS_can.h>
#include "stdbool.h"
#include <stdint.h>

/*
 * @brief Encoded Shutdown triggered message 
 *
 * Stores the CAN identifier used for transmission of the CAN message
 */
typedef struct SHDN_SHUTDOWN_TRIGGERED_t {
    uint32_t id;
} SHDN_SHUTDOWN_TRIGGERED_t;

SHDN_SHUTDOWN_TRIGGERED_t Compose_SHDN_SHUTDOWN_TRIGGERED();

#endif /* INC_CAN_SHDN_H_ */