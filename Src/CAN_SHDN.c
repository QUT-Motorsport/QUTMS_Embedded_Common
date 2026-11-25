/*
 * @file CAN_SHDN.c
 * @brief Implementation of Shutdown CAN message compose and parse functions
 *
 * Provides functions for converting between Shutdown data structures and CAN
 * payloads for communiction between the Shutdown board and other vehicle boards
 */
#ifdef QUTMS_CAN_SHDN

#include "CAN_SHDN.h"

/*
 * @brief Compose Shutdown heartbeat message
 *
 * Packs Shutdown message indicating a shutdown condition has occured
 */
SHDN_SHUTDOWN_TRIGGERED_t Compose_SHDN_SHUTDOWN_TRIGGERED() {
    SHDN_SHUTDOWN_TRIGGERED_t msg;

    // CAN message ID
    msg.id = QUTMS_SHDN_SHUTDOWN_TRIGGERED;

    return msg;
}

#endif