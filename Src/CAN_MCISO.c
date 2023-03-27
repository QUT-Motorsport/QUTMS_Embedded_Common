/*
 * MCISO_CAN.c
 *
 *  Created on: 23 Dec. 2021
 *      Author: Calvin J
 */

#include <CAN_MCISO.h>

#ifdef QUTMS_CAN_MCISO

MCISO_Heartbeat_t Compose_MCISO_Heartbeat(uint8_t id, MCISO_HeartbeatState_t *state) {
	MCISO_Heartbeat_t msg;
	msg.id = MCISO_Heartbeat_ID | id;
	msg.data[0] = state->stateID;
	msg.data[1] = state->errorFlags.rawMem;

	// set unused to 0
	msg.data[2] = 0;
	msg.data[3] = 0;
	msg.data[4] = 0;
	msg.data[5] = 0;
	msg.data[6] = 0;
	msg.data[7] = 0;

	return msg;
}

void Parse_MCISO_Heartbeat(uint8_t *data, MCISO_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->errorFlags.rawMem = data[1];
}

#endif
