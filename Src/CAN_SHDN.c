/**
 ******************************************************************************
 * @file SHDN_CAN_Messages.c
 * @brief Shutdown CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_SHDN

#include "CAN_SHDN.h"

SHDN_Heartbeat_t Compose_SHDN_Heartbeat(SHDN_HeartbeatState_t *state) {
	SHDN_Heartbeat_t msg;

	msg.id = SHDN_Heartbeat_ID;

	msg.data[0] = state->firstFault;
	msg.data[1] = (state->flags.rawMem) & 0xFF;
	msg.data[2] = (state->flags.rawMem >> 8) & 0xFF;

	// clear unused bytes
	msg.data[3] = 0;
	msg.data[4] = 0;
	msg.data[5] = 0;
	msg.data[6] = 0;
	msg.data[7] = 0;

	return msg;
}

void Parse_SW_Heartbeat(uint8_t data[3], SHDN_HeartbeatState_t *state) {
	state->firstFault = data[0];
	state->flags.rawMem = (data[1] | (data[2] << 8));
}

SHDN_ShutdownTriggered_t Compose_SHDN_ShutdownTriggered()
{
	SHDN_ShutdownTriggered_t p;
	p.id = SHDN_ShutdownTriggered_ID;
	return p;
}

#endif
