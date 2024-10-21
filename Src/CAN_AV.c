#ifdef QUTMS_CAN_AV

#include "CAN_AV.h"

AV_STATE_Heartbeat_t Compose_AV_STATE_Heartbeat(AV_STATE_HeartbeatState_t *state)
{
	AV_STATE_Heartbeat_t msg = {};
	msg.id = AV_STATE_Heartbeat_ID;

	msg.data[0] = state->modeID;
	msg.data[1] = state->missionID;
	msg.data[2] = state->stateID;

	return msg;
}

void Parse_AV_STATE_Heartbeat(uint8_t *data, AV_STATE_HeartbeatState_t *state)
{
	state->modeID = data[0];
	state->missionID = data[1];
	state->stateID = data[2];
}

ROS_STATE_Heartbeat_t Compose_ROS_STATE_Heartbeat(ROS_STATE_HeartbeatState_t *state)
{
	ROS_STATE_Heartbeat_t msg = {};
	msg.id = ROS_STATE_Heartbeat_ID;

	msg.data[0] = (state->rosFlags.rawMem & 0xFF);
	msg.data[1] = state->identifiedCones;
	msg.data[2] = state->mappedCones;
	msg.data[3] = state->lap;

	return msg;
}

void Parse_ROS_STATE_Heartbeat(uint8_t *data, ROS_STATE_HeartbeatState_t *state)
{
	state->rosFlags.rawMem = data[0];
	state->identifiedCones = data[1];
	state->mappedCones = data[2];
	state->lap = data[3];
}

Torque_Request_Heartbeat_t Compose_Torque_Request_Heartbeat(Torque_Request_t *state)
{
	Torque_Request_Heartbeat_t msg;
	msg.id = Torque_Request_ID;

	// state->torque in range -100 -> 100.
	int16_t torqueCommand = (int16_t)(INT16_MAX / 100.0f * state->torque);

	msg.data[0] = torqueCommand & 0xFF;
	msg.data[1] = (torqueCommand >> 8) & 0xFF;

	return msg;
}

void Parse_Torque_Request_Heartbeat(uint8_t *data, Torque_Request_t *state)
{
	int16_t torqueCommand = data[0] | (data[1] << 8);
	state->torque= torqueCommand * 100.0f / INT16_MAX;
}

#endif
