/*
 * CAN_ACM.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Calvin
 */

#ifdef QUTMS_CAN_ACM

#include <CAN_ACM.h>

ACM_Heartbeat_t Compose_ACM_Heartbeat(ACM_HeartbeatState_t *state)
{
	ACM_Heartbeat_t msg = {};
	msg.id = ACM_Heartbeat_ID;

	msg.data[0] = state->stateID;
	msg.data[1] = (state->flags.rawMem & 0xFF);
	msg.data[2] = ((state->flags.rawMem >> 8) & 0xFF);

	return msg;
}

void Parse_ACM_Heartbeat(uint8_t *data, ACM_HeartbeatState_t *state)
{
	state->stateID = data[0];
	state->flags.rawMem = ((data[2] & 0xFF) << 8) | data[1];
}

#endif
