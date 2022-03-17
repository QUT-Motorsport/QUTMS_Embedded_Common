/**
 ******************************************************************************
 * @file CAN_AMS.c
 * @brief AMS CAN Messages
 ******************************************************************************
 */

#include <CAN_AMS.h>

#ifdef QUTMS_CAN_AMS

AMS_Heartbeat_t Compose_AMS_Heartbeat(AMS_HeartbeatState_t *state) {
	AMS_Heartbeat_t msg;
	msg.id = AMS_Heartbeat_ID;

	msg.data[0] = state->stateID;
	msg.data[1] = (state->flags.rawMem) & 0xFF;
	msg.data[2] = (state->flags.rawMem >> 8) & 0xFF;
	msg.data[3] = (state->bmsStatus) & 0xFF;
	msg.data[4] = (state->bmsStatus >> 8) & 0xFF;
	msg.data[5] = (state->voltage) & 0xFF;
	msg.data[6] = (state->voltage >> 8) & 0xFF;
	msg.data[7] = state->SOC;

	return msg;
}

void Parse_AMS_Heartbeat(uint8_t *data, AMS_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->flags.rawMem = (data[1] | (data[2] << 8));
	state->bmsStatus = (data[3] | (data[4] << 8));
	state->voltage = (data[5] | (data[6] << 8));
	state->SOC = data[7];
}

AMS_ShutdownTriggered_t Compose_AMS_ShutdownTriggered() {
	AMS_ShutdownTriggered_t msg;
	msg.id = AMS_ShutdownTriggered_ID;

	return msg;
}

AMS_StartCharging_t Compose_AMS_StartCharging() {
	AMS_StartCharging_t msg;
	msg.id = AMS_StartCharging_ID;

	return msg;
}

AMS_OBJ_DICT_t Compose_AMS_OBJ_DICT(uint8_t data[8]) {
	AMS_OBJ_DICT_t msg;
	msg.id = AMS_OBJ_DICT_ID;

	for (int i = 0; i < 8; i++) {
		msg.data[i] = data[i];
	}

	return msg;
}

void Parse_AMS_OBJ_DICT(uint8_t *data, uint8_t *type, uint8_t *data_size,
		uint8_t *index, uint32_t *value) {
	*type = data[0];
	*data_size = data[1];
	*index = data[2];

	uint32_t output_value = 0;
	for (int i = 0; i < 4; i++) {
		output_value |= (data[3] << (i * 8));
	}

	*value = output_value;
}

AMS_CellVoltageShutdown_t Compose_AMS_CellVoltageShutdown(uint8_t cellNum,
		uint8_t bmsID, uint8_t voltage) {
	AMS_CellVoltageShutdown_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x0, 0x0, 0x0);
	p.data[0] = (cellNum & 0xF) << 4 | (bmsID & 0xF);
	p.data[1] = (voltage & 0xFF);

	return p;
}

void Parse_AMS_CellVoltageShutdown(uint8_t *data, uint8_t *cellNum,
		uint8_t *bmsID, uint8_t *voltage) {
	*cellNum = (uint8_t) (data[0] >> 4);
	*bmsID = (uint8_t) (data[0] & 0xF);
	*voltage = (uint8_t) (data[1] & 0xFF);
}

AMS_CellTemperatureShutdown_t Compose_AMS_CellTemperatureShutdown(
		uint8_t cellNum, uint8_t bmsID, uint8_t temperature) {
	AMS_CellTemperatureShutdown_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x0, 0x1, 0x0);
	p.data[0] = (cellNum & 0xF) << 4 | (bmsID & 0xF);
	p.data[1] = (temperature & 0xFF);

	return p;
}

void Parse_AMS_CellTemperatureShutdown(uint8_t *data, uint8_t *cellNum,
		uint8_t *bmsID, uint8_t *temperature) {
	*cellNum = (uint8_t) (data[0] >> 4);
	*bmsID = (uint8_t) (data[0] & 0xF);
	*temperature = (uint8_t) (data[1] & 0xFF);
}

AMS_MissingBMS_t Compose_AMS_MissingBMS(bool data[12]) {
	//TODO Check
	AMS_MissingBMS_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x0, 0x2, 0x0);
	p.data[0] = 0
			| (data[0] | (data[1] << 1) | (data[2] << 2) | (data[3] << 3)
					| (data[4] << 4) | (data[5] << 5) | (data[6] << 6)
					| (data[7] << 7));
	p.data[1] = 0
			| (data[8] | (data[9] << 1) | (data[10] << 2) | (data[11] << 3)
					| data[12] << 4);

	return p;
}

void Parse_AMS_MissingBMS(uint8_t *pdata, bool *data[12]) {
	return;
}

AMS_HeartbeatRequest_t Compose_AMS_HeartbeatRequest() {
	AMS_HeartbeatRequest_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x1, 0x0, 0x0);

	return p;
}

AMS_HeartbeatResponse_t Compose_AMS_HeartbeatResponse(bool initialised,
bool HVAn, bool HVBn, bool precharge, bool HVAp, bool HVBp,
		uint16_t averageVoltage, uint16_t runtime) {

	AMS_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x10, 0x0, 0x1, 0x01, 0x0);

	p.data[0] = HVAn | (HVBn << 1) | (precharge << 2) | (HVAp << 4)
			| (HVBp << 5) | (initialised << 7);
	p.data[1] = (averageVoltage & 0x3F);
	p.data[2] = (averageVoltage >> 6) & 0x3F;
	p.data[3] = (runtime & 0xFF);
	p.data[4] = (runtime >> 8);

	return p;
}

void Parse_AMS_HeartbeatResponse(uint8_t *data, bool *initialised, bool *HVAn,
bool *HVBn, bool *precharge, bool *HVAp, bool *HVBp, uint16_t *averageVoltage,
		uint16_t *runtime) {
	*HVAn = (bool) (data[0] & 0x1);
	*HVBn = (bool) (data[0] & 0x2);
	*precharge = (bool) (data[0] & 0x4);

	*HVAp = (bool) (data[0] & 0x10);
	*HVBp = (bool) (data[0] & 0x20);

	*initialised = (bool) (data[0] & 0x80);

	*averageVoltage = (uint16_t) ((data[1] & 0x3F) << 6 | (data[0]));
	*runtime = (uint16_t) (data[3] << 8 | data[2]);
}

AMS_StartUp_t Compose_AMS_StartUp() {
	AMS_StartUp_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x0, 0x0);

	return p;
}

AMS_ResetTractive_t Compose_AMS_ResetTractive() {
	AMS_ResetTractive_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x1, 0x0);

	return p;
}

AMS_Shutdown_t Compose_AMS_Shutdown() {
	AMS_Shutdown_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x2, 0x0);

	return p;
}

AMS_RequestTemperature_t Compose_AMS_RequestTemperature() {
	AMS_RequestTemperature_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x3, 0x0);

	return p;
}

AMS_TransmitTemperature_t Compose_AMS_TransmitTemperature(uint8_t temperature) {
	AMS_TransmitTemperature_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x3, 0x3, 0x0);
	p.data[0] = temperature;

	return p;
}

void Parse_AMS_TransmitTemperature(uint8_t *data, uint8_t *temperature) {
	*temperature = data[0];
}

AMS_RequestChargeState_t Compose_AMS_RequestChargeState() {
	AMS_RequestChargeState_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x4, 0x0);

	return p;
}

AMS_TransmitChargeState_t Compose_AMS_TransmitChargeState(uint16_t chargeState) {
	AMS_TransmitChargeState_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x3, 0x4, 0x0);
	p.data[0] = chargeState >> 8;
	p.data[1] = (chargeState & 0xFF);

	return p;
}

void Parse_AMS_TransmitChargeState(uint8_t *data, uint16_t *chargeState) {
	*chargeState = (data[0] << 8 | data[1]);
}

AMS_Ready_t Compose_AMS_Ready() {
	AMS_Ready_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x3, 0x0, 0x0);

	return p;
}

AMS_ShutdownState_t Compose_AMS_ShutdownState(uint8_t status) {
	AMS_ShutdownState_t msg;
	msg.id = AMS_ShutdownStatus_ID;
	msg.data[0] = status & 0x1;

	return msg;
}

void Parse_AMS_ShutdownState(uint8_t *data, uint8_t *status) {
	*status = data[0] & 0x1;
}

#endif
