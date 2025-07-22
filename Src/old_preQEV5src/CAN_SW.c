/*
 * CAN_SW.c
 *
 *  Created on: Mar 17, 2022
 *      Author: Calvin J
 */

#include "CAN_SW.h"
#include <QUTMS_can.h>

#ifdef QUTMS_CAN_SW

SW_Heartbeat_t Compose_SW_Heartbeat(SW_HeartbeatState_t *state) {
	SW_Heartbeat_t msg;

	msg.id = SW_Heartbeat_ID;

	msg.data[0] = state->stateID;
	msg.data[1] = state->missionID;
	msg.data[2] = (state->flags.rawMem) & 0xFF;
	msg.data[3] = (state->flags.rawMem >> 8) & 0xFF;

	// clear unused bytes
	msg.data[4] = 0;
	msg.data[5] = 0;
	msg.data[6] = 0;
	msg.data[7] = 0;

	return msg;
}

void Parse_SW_Heartbeat(uint8_t data[4], SW_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->missionID = data[1];
	state->flags.rawMem = (data[2] | (data[3] << 8));
}

SW_ActivateHorn_t Compose_SW_ActivateHorn() {
	SW_ActivateHorn_t msg;
	msg.id = SW_ActivateHorn_ID;

	return msg;
}

#endif
