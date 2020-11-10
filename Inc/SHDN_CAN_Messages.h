/**
 ******************************************************************************
 * @file SHDN_Messages.h
 * @brief Shutdown CAN Messages
 ******************************************************************************
 */

#ifndef INC_SHDN_CAN_MESSAGES_H_
#define INC_SHDN_CAN_MESSAGES_H_

#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>
#include "QUTMS_can.h"

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
SHDN_ShutdownTriggered_t Compose_SHDN_ShudownTriggered(void);

/**
 * @brief Shutdown Heartbeat Response Message
 */
typedef struct SHDN_HeartbeatResponse_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data; /**< Data */
} SHDN_HeartbeatResponse_t;

/**
 * @brief Shutdown Heartbeat Response Composer
 * @param segmentState
 * @return The composed SHDN_HeartbeatResponse_t packet
 */
SHDN_HeartbeatResponse_t Compose_SHDN_One_HeartbeatResponse(uint8_t segmentState);

/**
 * @brief Shutdown Heartbeat Response Composer
 * @param segmentState
 * @return The composed SHDN_HeartbeatResponse_t packet
 */
SHDN_HeartbeatResponse_t Compose_SHDN_Two_HeartbeatResponse(uint8_t segmentState);

/**
 * @brief Shutdown Heartbeat Response Composer
 * @param segmentState
 * @return The composed SHDN_HeartbeatResponse_t packet
 */
SHDN_HeartbeatResponse_t Compose_SHDN_Three_HeartbeatResponse(uint8_t segmentState);

/**
 * @brief Shutdown Heartbeat Response Parser
 * @param segmentState
 */
void Parse_SHDN_HeartbeatResponse(SHDN_HeartbeatResponse_t packet, uint8_t* segmentState);

#endif /* INC_SHDN_CAN_MESSAGES_H_ */
