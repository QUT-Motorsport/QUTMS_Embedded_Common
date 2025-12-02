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
	msg.data[4] = (state->flags.rawMem >> 24) & 0xFF;
	msg.data[5] = (state->packState) & 0xFF;
	msg.data[6] = state->SOC;

	return msg;
}

void Parse_BMU_Heartbeat(uint8_t *data, BMU_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->flags.rawMem = data[1] | (data[2] << 8) | (data[3] << 16) | (data[4] << 24);
	state->packState = data[5];
	state->SOC = data[6];
}

void Parse_BMU_TransmitVoltage(uint8_t *data, uint16_t voltages[3], uint16_t *age);

BMU_TransmitVoltage_t Compose_BMU_TransmitVoltage(uint8_t cmuId, uint8_t packId,
		uint16_t voltages[3], uint16_t age) {
	BMU_TransmitVoltage_t msg;

	// apply cmu id and packet id
	msg.id = BMU_TransmitVoltage_Node_0_ID | ((cmuId & 0x3FF ) << 4)  | (packId & 0xF);

	msg.data[0] = voltages[0] & 0xFF;
	msg.data[1] = (voltages[0] >> 8) & 0xFF;
	msg.data[2] = voltages[1] & 0xFF;
	msg.data[3] = (voltages[1] >> 8) & 0xFF;
	msg.data[4] = voltages[2] & 0xFF;
	msg.data[5] = (voltages[2] >> 8) & 0xFF;
	msg.data[6] = age & 0xFF;
	msg.data[7] = (age >> 8) & 0xFF;

	return msg;
}

void Parse_BMU_TransmitVoltage(uint8_t *data, uint16_t voltages[3], uint16_t *age) {
	voltages[0] = data[0] | (data[1] << 8);
	voltages[1] = data[2] | (data[3] << 8);
	voltages[2] = data[4] | (data[5] << 8);
	*age = data[6] | (data[7] << 8);
}

BMU_TransmitTemperature_t Compose_BMU_TransmitTemperature(uint8_t cmuId, uint8_t packId,
		uint8_t temps[6], uint16_t age) {
	BMU_TransmitTemperature_t msg;
	msg.id = BMU_TransmitTemperature_Node_0_ID  | ((cmuId & 0x3FF ) << 4) | (packId & 0xF);

	msg.data[0] = temps[0];
	msg.data[1] = temps[1];
	msg.data[2] = temps[2];
	msg.data[3] = temps[3];
	msg.data[4] = temps[4];
	msg.data[5] = temps[5];

	msg.data[6] = age & 0xFF;
	msg.data[7] = (age >> 8) & 0xFF;

	return msg;
}

void Parse_BMU_TransmitTemperatures(uint8_t *data, uint8_t temps[6], uint16_t *age) {
	temps[0] = data[0];
	temps[1] = data[1];
	temps[2] = data[2];
	temps[3] = data[3];
	temps[4] = data[4];
	temps[5] = data[5];

	*age = data[6] | (data[7] << 8);
}

BMU_TransmitBalancing_t Compose_BMU_TransmitBalancing(uint8_t cmuId, uint16_t balanceState, uint8_t dieTemp) {
	BMU_TransmitBalancing_t msg;
	msg.id = BMU_TransmitBalancing_Node_0_ID | ((cmuId & 0x3FF ) << 4);

	msg.data[0] = balanceState & 0xFF;
	msg.data[1] = (balanceState >> 8) & 0xFF;
	msg.data[2] = dieTemp;

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

BMU_TransmitPackInfo_t Compose_BMU_TransmitPackInfo(int32_t current, int32_t voltage_pack) {
	BMU_TransmitPackInfo_t msg;
	msg.id = BMU_TransmitPackInfo_ID;

	msg.data[0] = current & 0xFF;
	msg.data[1] = (current >> 8) & 0xFF;
	msg.data[2] = (current >> 16) & 0xFF;
	msg.data[3] = (current >> 24) & 0xFF;
	msg.data[4] = voltage_pack & 0xFF;
	msg.data[5] = (voltage_pack >> 8) & 0xFF;
	msg.data[6] = (voltage_pack >> 16) & 0xFF;
	msg.data[7] = (voltage_pack >> 24) & 0xFF;

	return msg;
}

BMU_TransmitPower_t Compose_BMU_TransmitPower(int32_t power) {
	BMU_TransmitPower_t msg;
	msg.id = BMU_TransmitPower_ID;
	msg.data[0] = power & 0xFF;
	msg.data[1] = (power >> 8) & 0xFF;
	msg.data[2] = (power >> 16) & 0xFF;
	msg.data[3] = (power >> 24) & 0xFF;

	return msg;
}

BMU_TransmitSOC_t Compose_BMU_TransmitSOC(uint8_t soc_percent, uint8_t flags, int32_t coulomb_uAh) {
	BMU_TransmitSOC_t msg;
	msg.id = BMU_TransmitSOC_ID;

	// data[0] = SOC percent (0..100)
	msg.data[0] = soc_percent;
	// data[1] = flags (bit0 = valid, bit1 = calibrated)
	msg.data[1] = flags;
	// data[2..5] = signed int32 coulomb accumulation in microamp-hours (µAh), little-endian
	msg.data[2] = (uint8_t)(coulomb_uAh & 0xFF);
	msg.data[3] = (uint8_t)((coulomb_uAh >> 8) & 0xFF);
	msg.data[4] = (uint8_t)((coulomb_uAh >> 16) & 0xFF);
	msg.data[5] = (uint8_t)((coulomb_uAh >> 24) & 0xFF);
	// reserved
	msg.data[6] = 0;
	msg.data[7] = 0;

	return msg;
}

BMU_TransmitPackSummary_t Compose_BMU_TransmitPackSummary(uint16_t min_cell_mv, uint32_t pack_total_mv,
														   uint8_t total_valid_cells, uint8_t max_temp) {
	BMU_TransmitPackSummary_t msg;

	msg.id = BMU_TransmitPackSummary_ID;

	// New payload layout (8 bytes):
	// data[0..1] = min_cell_mv (uint16 little-endian)
	// data[2..5] = pack_total_mv (uint32 little-endian)
	// data[6] = total_valid_cells (uint8)
	// data[7] = max_temp (uint8)
	msg.data[0] = min_cell_mv & 0xFF;
	msg.data[1] = (min_cell_mv >> 8) & 0xFF;

	msg.data[2] = (pack_total_mv >> 0) & 0xFF;
	msg.data[3] = (pack_total_mv >> 8) & 0xFF;
	msg.data[4] = (pack_total_mv >> 16) & 0xFF;
	msg.data[5] = (pack_total_mv >> 24) & 0xFF;

	msg.data[6] = total_valid_cells;
	msg.data[7] = max_temp;

	return msg;
}

#endif
