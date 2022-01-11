/**
 ******************************************************************************
 * @file SHDN_Messages.h
 * @brief Shutdown CAN Messages
 ******************************************************************************
 */

#ifndef INC_SHDN_CAN_MESSAGES_H_
#define INC_SHDN_CAN_MESSAGES_H_

#include <QUTMS_CAN.h>
#include "stdbool.h"
#include <stdlib.h>

/**
 * @brief Shutdown Heartbeat Request Message
 */
typedef struct SHDN_ShutdownTriggered_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_ShutdownTriggered_t;

/**
 * @brief Shutdown Heartbeat Request Message Composer
 * @return The composed SHDN_HeartbeatRequest_t packet
 */
SHDN_ShutdownTriggered_t Compose_SHDN_ShutdownTriggered();

#endif /* INC_SHDN_CAN_MESSAGES_H_ */
