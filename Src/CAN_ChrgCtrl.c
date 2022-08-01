/*
 * CAN_ChgCtrl.c
 *
 *  Created on: 22 Feb. 2022
 *      Author: Calvin J
 */

#ifdef QUTMS_CAN_CHRG_CTRL

#include "CAN_ChrgCtrl.h"

CHRGCTRL_Heartbeat_t Compose_CHRG_CTRL_Hearbeat(CHRGCTRL_HeartbeatState_t *state) {
	CHRGCTRL_Heartbeat_t msg;

	msg.id = CHRGCTRL_Heartbeat_ID;
	msg.data[0] = state->stateID;
	msg.data[1] = state->flags.rawMem;

	return msg;
}

void Parse_CHRG_CTRL_Hearbeat(uint8_t *data, CHRGCTRL_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->flags.rawMem = data[1];
}

#endif
