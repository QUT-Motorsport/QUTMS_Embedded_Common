/*
 * CAN_EBS_CTRL.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Calvin
 */

#ifdef QUTMS_CAN_EBS

#include <CAN_EBS_CTRL.h>

EBS_CTRL_Heartbeat_t Compose_EBS_CTRL_Heartbeat(EBS_CTRL_HeartbeatState_t *state)
{
	EBS_CTRL_Heartbeat_t msg = {};
	msg.id = EBS_CTRL_Heartbeat_ID;

	msg.data[0] = state->stateID;
	msg.data[1] = (state->flags.rawMem & 0xFF);
	msg.data[2] = ((state->flags.rawMem >> 8) & 0xFF);

	return msg;
}

void Parse_EBS_CTRL_Heartbeat(uint8_t *data, EBS_CTRL_HeartbeatState_t *state)
{
	state->stateID = data[0];
	state->flags.rawMem = ((data[2] & 0xFF) << 8) | data[1];
}

#endif
