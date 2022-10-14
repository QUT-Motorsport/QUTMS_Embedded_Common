#ifdef QUTMS_CAN_DVL

#include "CAN_DVL.h"

DVL_Heartbeat_t Compose_DVL_Heartbeat(DVL_HeartbeatState_t *state) {
	DVL_Heartbeat_t msg;
	msg.id = DVL_Heartbeat_ID;

	// state->torque in range -100 -> 100.
	uint16_t torque_command = (uint16_t)(INT16_MAX / 100.0f * state->torque);

	msg.data[0] = state->stateID;
	msg.data[1] = state->missionID;
	msg.data[2] = (state->flags.rawMem & 0xFF);
	msg.data[3] = ((state->flags.rawMem >> 8) & 0xFF);

	msg.data[4] = *((uint8_t*)&state->wheel_speed[0]);
	msg.data[5] = *((uint8_t*)&state->wheel_speed[1]);
	msg.data[6] = *((uint8_t*)&state->wheel_speed[2]);
	msg.data[7] = *((uint8_t*)&state->wheel_speed[3]);

	return msg;
}

void Parse_DVL_Heartbeat(uint8_t *data, DVL_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->missionID = data[1];
	state->flags.rawMem = ((data[3] & 0xFF) << 8) | data[2];
	state->wheel_speed[0] = *((int8_t*)&data[4]);
	state->wheel_speed[1] = *((int8_t*)&data[5]);
	state->wheel_speed[2] = *((int8_t*)&data[6]);
	state->wheel_speed[3] = *((int8_t*)&data[7]);
}

#endif
