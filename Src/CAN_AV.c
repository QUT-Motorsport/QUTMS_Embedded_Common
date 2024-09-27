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

#endif
