#ifdef QUTMS_CAN_DVL

#include "CAN_DVL.h"

DVL_Heartbeat_t Compose_DVL_Heartbeat(DVL_HeartbeatState_t *state) {
	DVL_Heartbeat_t msg;
	msg.id = DVL_Heartbeat_ID;

	// state->torque in range -100 -> 100.
	int16_t torqueCommand = (int16_t)(INT16_MAX / 100.0f * state->torqueRequest);

	msg.data[0] = state->stateID;
	msg.data[1] = state->missionID;
	msg.data[2] = (state->flags.rawMem & 0xFF);
	msg.data[3] = ((state->flags.rawMem >> 8) & 0xFF);

	msg.data[4] = torqueCommand & 0xFF;
	msg.data[5] = (torqueCommand >> 8) & 0xFF;

	return msg;
}

void Parse_DVL_Heartbeat(uint8_t *data, DVL_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->missionID = data[1];
	state->flags.rawMem = ((data[3] & 0xFF) << 8) | data[2];

	int16_t torqueCommand = data[4] | (data[5] << 8);
	state->torqueRequest = torqueCommand * 100.0f / INT16_MAX;
}

DVL_DrivingDynamics1_t Compose_DVL_DrivingDynamics1(DVL_DrivingDynamics1_Data_u *dynamics) {
	DVL_DrivingDynamics1_t msg;
	msg.id = DVL_DrivingDynamics1_ID;
	msg.data[0] = dynamics->data[0];
	msg.data[1] = dynamics->data[1];
	msg.data[2] = dynamics->data[2];
	msg.data[3] = dynamics->data[3];
	msg.data[4] = dynamics->data[4];
	msg.data[5] = dynamics->data[5];
	msg.data[6] = dynamics->data[6];
	msg.data[7] = dynamics->data[7];

	return msg;
}

DVL_SystemStatus_t Compose_DVL_SystemStatus(DVL_SystemStatus_Data_u *status) {
	DVL_SystemStatus_t msg;
	msg.id = DVL_SystemStatus_ID;
	msg.data[0] = status->data[0];
	msg.data[1] = status->data[1];
	msg.data[2] = status->data[2];
	msg.data[3] = status->data[3];
	msg.data[4] = status->data[4];

	return msg;
}

#endif
