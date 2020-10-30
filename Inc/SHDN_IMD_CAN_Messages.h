/**
 ******************************************************************************
 * @file SHDN_IMD_Messages.h
 * @brief Shutdown IMD CAN Messages
 ******************************************************************************
 */

#ifndef INC_SHDN_IMD_CAN_MESSAGES_H_
#define INC_SHDN_IMD_CAN_MESSAGES_H_

#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>
#include "QUTMS_can.h"

/**
 * @brief Shutdown IMD Heartbeat Request Message
 */
typedef struct SHDN_IMD_HeartbeatRequest_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_IMD_HeartbeatRequest_t;

/**
 * @brief Shutdown IMD Heartbeat Request Message Composer
 * @return The composed SHDN_IMD_HeartbeatRequest_t packet
 */
SHDN_IMD_HeartbeatRequest_t Compose_SHDN_IMD_HeartbeatRequest(void);

/**
 * @brief Shutdown IMD Heartbeat Response Message
 */
typedef struct SHDN_IMD_HeartbeatResponse_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data; /**< Data */
} SHDN_IMD_HeartbeatResponse_t;

/**
 * @brief Shutdown IMD Heartbeat Response Composer
 * @param pwmState Represents the PWM State of the Shutdown IMD
 * @return The composed SHDN_IMD_HeartbeatResponse_t packet
 */
SHDN_IMD_HeartbeatResponse_t Compose_SHDN_IMD_HeartbeatResponse(uint8_t pwmState);

/**
 * @brief Shutdown IMD Heartbeat Response Parser
 * @param pwmState Parses the PWM State of the Shutdown IMD
 */
void Parse_SHDN_IMD_HeartbeatResponse(SHDN_IMD_HeartbeatResponse_t packet, uint8_t* pwmState);


#endif /* INC_SHDN_IMD_CAN_MESSAGES_H_ */
