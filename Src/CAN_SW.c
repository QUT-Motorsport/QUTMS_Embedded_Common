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
	msg.data[1] = (state->flags.rawMem) & 0xFF;
	msg.data[2] = (state->flags.rawMem >> 8) & 0xFF;

	return msg;
}

void Parse_SW_Heartbeat(uint8_t data[3], SW_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->flags.rawMem = (data[1] | (data[2] << 8));
}

SW_ActivateHorn_t Compose_SW_ActivateHorn() {
	SW_ActivateHorn_t msg;
	msg.id = SW_ActivateHorn_ID;

	return msg;
}

#endif
