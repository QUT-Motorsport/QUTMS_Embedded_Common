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
	msg.data[3] = (state->flags.rawMem >> 16) & 0xFF;
	msg.data[4] = (state->cmuStatus) & 0xFF;
	msg.data[5] = (state->cmuStatus >> 8) & 0xFF;
	msg.data[6] = state->SOC;

	return msg;
}

void Parse_BMU_Heartbeat(uint8_t *data, BMU_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->flags.rawMem = data[1] | (data[2] << 8) | (data[3] << 16);
	state->cmuStatus = data[4] | (data[5] << 8);
	state->SOC = data[6];
}

BMU_TransmitVoltage_t Compose_BMU_TransmitVoltage(uint8_t cmuId, uint8_t packId,
		uint16_t voltages[3]) {
	BMU_TransmitVoltage_t msg;
	msg.id = BMU_TransmitVoltage_ID;

	msg.data[0] = cmuId;
	msg.data[1] = packId;
	msg.data[2] = voltages[0] & 0xFF;
	msg.data[3] = (voltages[0] >> 8) & 0xFF;
	msg.data[4] = voltages[1] & 0xFF;
	msg.data[5] = (voltages[1] >> 8) & 0xFF;
	msg.data[6] = voltages[2] & 0xFF;
	msg.data[7] = (voltages[2] >> 8) & 0xFF;

	return msg;
}

void Parse_BMU_TransmitVoltage(uint8_t *data, uint8_t *cmuId, uint8_t *packId,
		uint16_t voltages[3]) {

}

#endif
