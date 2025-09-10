/**
 ******************************************************************************
 * @file SHDN_Messages.h
 * @brief Shutdown CAN Messages
 ******************************************************************************
 */

#ifndef INC_SHDN_CAN_MESSAGES_H_
#define INC_SHDN_CAN_MESSAGES_H_

#include <QUTMS_can.h>
#include "stdbool.h"
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Shutdown Heartbeat Request Message
 */
typedef struct SHDN_ShutdownTriggered_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_ShutdownTriggered_t;

typedef struct SHDN_flags {
	uint16_t rawMem;
	struct {
		uint8_t F_Harness : 1;
		uint8_t Junct_Box : 1;
		uint8_t L_Upright : 1;
		uint8_t R_Upright : 1;
		uint8_t Accu : 1;
		uint8_t Roll_Hoop : 1;
		uint8_t HVD : 1;
		uint8_t DVL : 1;
		uint8_t SPARE : 1;
		uint8_t TS_KEY : 1;
	} _SHDN_Flags;
} SHDN_Flags_u;

typedef struct SHDN_HeartbeatState {
	uint8_t firstFault;
	SHDN_Flags_u flags;
} SHDN_HeartbeatState_t;

typedef struct SHDN_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} SHDN_Heartbeat_t;

SHDN_Heartbeat_t Compose_SHDN_Heartbeat(SHDN_HeartbeatState_t* state);
void Parse_SHDN_Heartbeat(uint8_t data[3], SHDN_HeartbeatState_t* state);

/**
 * @brief Shutdown Heartbeat Request Message Composer
 * @return The composed SHDN_HeartbeatRequest_t packet
 */
SHDN_ShutdownTriggered_t Compose_SHDN_ShutdownTriggered();

#endif /* INC_SHDN_CAN_MESSAGES_H_ */
