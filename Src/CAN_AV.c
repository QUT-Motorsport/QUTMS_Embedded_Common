#ifdef QUTMS_CAN_AV

#include "CAN_AV.h"

AV_Heartbeat_t Compose_AV_Heartbeat(AV_Status_t *state)
{
	AV_Heartbeat_t msg = {};
	msg.id = AV_Heartbeat_ID;

	msg.data[0] = state->modeID;
	msg.data[1] = state->missionID;
	msg.data[2] = state->stateID;

	return msg;
}

void Parse_AV_Heartbeat(uint8_t *data, AV_Status_t *state)
{
	state->modeID = data[0];
	state->missionID = data[1];
	state->stateID = data[2];
}

ROS_Heartbeat_t Compose_ROS_Heartbeat(ROS_Status_t *state)
{
	ROS_Heartbeat_t msg = {};
	msg.id = ROS_Heartbeat_ID;

	msg.data[0] = (state->rosFlags.rawMem & 0xFF);
	msg.data[1] = state->identifiedCones;
	msg.data[2] = state->mappedCones;
	msg.data[3] = state->lap;

	return msg;
}

void Parse_ROS_Heartbeat(uint8_t *data, ROS_Status_t *state)
{
	state->rosFlags.rawMem = data[0];
	state->identifiedCones = data[1];
	state->mappedCones = data[2];
	state->lap = data[3];
}

Request_Heartbeat_t Compose_Request_Heartbeat(Request_t *state)
{
	Request_Heartbeat_t msg;
	msg.id = Request_ID;

	// state->torque in range -100 -> 100.
	int16_t torqueCommand = (int16_t)(INT16_MAX / 100.0f * state->torque);
	int16_t steeringCommand = (int16_t)(INT16_MAX / 100.0f * state->steering);
	int16_t speedCommand = (int16_t)(INT16_MAX / 100.0f * state->speed);

	msg.data[0] = torqueCommand & 0xFF;
	msg.data[1] = (torqueCommand >> 8) & 0xFF;
	msg.data[2] = steeringCommand & 0xFF;
	msg.data[3] = (steeringCommand >> 8) & 0xFF;
	msg.data[4] = speedCommand & 0xFF;
	msg.data[5] = (speedCommand >> 8) & 0xFF;

	return msg;
}

void Parse_Request_Heartbeat(uint8_t *data, Request_t *state)
{
	int16_t torqueCommand = data[0] | (data[1] << 8);
	state->torque= torqueCommand * 100.0f / INT16_MAX;
	int16_t steeringCommand = data[2] | (data[3] << 8);
	state->torque= steeringCommand * 100.0f / INT16_MAX;
	int16_t speedCommand = data[4] | (data[5] << 8);
	state->torque= speedCommand * 100.0f / INT16_MAX;
}

#endif
