#include "CAN_DVL.h"

DVL_Heartbeat_t Compose_DVL_Heartbeat(DVL_HeartbeatState_t *state) {
	DVL_Heartbeat_t msg;
	msg.id = DVL_Heartbeat_ID;

	// state->torque in range -1 -> 1.
	uint16_t torque_command = (uint16_t)(INT16_MAX * state->torque);

	msg.data[0] = state->stateID;
	msg.data[1] = (state->flags.rawMem & 0xFF);
	msg.data[2] = ((state->flags.rawMem >> 8) & 0xFF);
	msg.data[3] = (torque_command & 0xFF);
	msg.data[4] = ((torque_command >> 8) & 0xFF);

	return msg;
}

void Parse_DVL_Heartbeat(uint8_t *data, DVL_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->flags.rawMem = ((data[2] & 0xFF) << 8) | data[1];
	state->torque = (float)(((data[4] & 0xFF) << 8) | data[3]) / (float)INT16_MAX;
}