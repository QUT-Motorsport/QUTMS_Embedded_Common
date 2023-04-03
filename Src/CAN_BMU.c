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
		uint16_t voltages[4]) {
	BMU_TransmitVoltage_t msg;

	// apply cmu id and packet id
	msg.id = BMU_TransmitVoltage_Node_0_ID | ((cmuId & 0x3FF ) << 4)  | (packId & 0xF);

	msg.data[0] = voltages[0] & 0xFF;
	msg.data[1] = (voltages[0] >> 8) & 0xFF;
	msg.data[2] = voltages[1] & 0xFF;
	msg.data[3] = (voltages[1] >> 8) & 0xFF;
	msg.data[4] = voltages[2] & 0xFF;
	msg.data[5] = (voltages[2] >> 8) & 0xFF;
	msg.data[6] = voltages[3] & 0xFF;
	msg.data[7] = (voltages[3] >> 8) & 0xFF;

	return msg;
}

void Parse_BMU_TransmitVoltage(uint8_t *data, uint16_t voltages[4]) {
	voltages[0] = data[0] | (data[1] << 8);
	voltages[1] = data[2] | (data[3] << 8);
	voltages[2] = data[4] | (data[5] << 8);
	voltages[3] = data[6] | (data[7] << 8);
}

BMU_TransmitTemperature_t Compose_BMU_TransmitTemperature(uint8_t cmuId, uint8_t packId,
		uint8_t temps[8]) {
	BMU_TransmitTemperature_t msg;
	msg.id = BMU_TransmitTemperature_Node_0_ID  | ((cmuId & 0x3FF ) << 4) | (packId & 0xF);

	msg.data[0] = temps[0];
	msg.data[1] = temps[1];
	msg.data[2] = temps[2];
	msg.data[3] = temps[3];
	msg.data[4] = temps[4];
	msg.data[5] = temps[5];
	msg.data[6] = temps[6];
	msg.data[7] = temps[7];

	return msg;
}

void Parse_BMU_TransmitTemperatures(uint8_t *data, uint8_t temps[8]) {
	temps[0] = data[0];
	temps[1] = data[1];
	temps[2] = data[2];
	temps[3] = data[3];
	temps[4] = data[4];
	temps[5] = data[5];
	temps[6] = data[6];
	temps[7] = data[7];
}

BMU_TransmitBalancing_t Compose_BMU_TransmitBalancing(uint8_t cmuId, uint16_t balanceState) {
	BMU_TransmitBalancing_t msg;
	msg.id = BMU_TransmitBalancing_Node_0_ID | ((cmuId & 0x3FF ) << 4);

	msg.data[0] = balanceState & 0xFF;
	msg.data[1] = (balanceState >> 8) & 0xFF;

	return msg;
}

BMU_TransmitDieTemps_t Compose_BMU_TransmitDieTemps(uint8_t packId, uint8_t temps[8]) {
	BMU_TransmitDieTemps_t msg;
	msg.id = BMU_TransmitDieTemps_ID | (packId & 0xF);

	for (int i = 0; i < 8; i++) {
		msg.data[i] = temps[i];
	}

	return msg;
}

#endif
