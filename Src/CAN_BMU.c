/*
 * CAN_BMU.c
 *
 *  Created on: 21 Jul. 2022
 *      Author: Calvin Johnson
 */

#ifdef QUTMS_CAN_BMU

#include <CAN_BMU.h>

BMU_Heartbeat_t Compose_BMU_Heartbeat(BMU_HeartbeatState_t *state) {
	BMU_Heartbeat_t msg;
	msg.id = BMU_Heartbeat_ID;

	msg.data[0] = state->stateID;
	msg.data[1] = (state->flags.rawMem) & 0xFF;
	msg.data[2] = (state->flags.rawMem >> 8) & 0xFF;
	msg.data[3] = (state->cmuStatus) & 0xFF;
	msg.data[4] = (state->cmuStatus >> 8) & 0xFF;
	msg.data[5] = (state->voltage) & 0xFF;
	msg.data[6] = (state->voltage >> 8) & 0xFF;
	msg.data[7] = state->SOC;

	return msg;
}

#endif
