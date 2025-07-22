/**
 ******************************************************************************
 * @file CC_CAN_Messages.c
 * @brief Chassis Controller CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_CC

#include <CAN_CC.h>

CC_Heartbeat_t Compose_CC_Heartbeat(CC_HeartbeatState_t *state) {
	CC_Heartbeat_t msg;
	msg.id = CC_Heartbeat_ID;
	msg.data[0] = state->stateID;
	msg.data[1] = (state->errorFlags.rawMem) & 0xFF;
	msg.data[2] = (state->errorFlags.rawMem >> 8) & 0xFF;

	return msg;
}

void Parse_CC_Heartbeat(uint8_t *data, CC_HeartbeatState_t *state) {
	state->stateID = data[0];
	state->errorFlags.rawMem = (data[1] | (data[2] << 8));
}

CC_RTD_t Compose_CC_RTD() {
	CC_RTD_t msg;
	msg.id = CC_RTD_ID;
	return msg;
}

CC_Shutdown_t Compose_CC_Shutdown() {
	CC_Shutdown_t msg;
	msg.id = CC_Shutdown_ID;
	return msg;
}

CC_TransmitPedals_t Compose_CC_TransmitPedals(uint16_t accel0, uint16_t accel1,
		uint16_t brake, uint16_t brake_pressure_adc) {
	CC_TransmitPedals_t msg;
	msg.id = CC_TransmitPedals_ID;
	msg.data[0] = accel0 & 0xff;
	msg.data[1] = (accel0 >> 8) & 0xff;
	msg.data[2] = accel1 & 0xff;
	msg.data[3] = (accel1 >> 8) & 0xff;
	msg.data[4] = brake & 0xff;
	msg.data[5] = (brake >> 8) & 0xff;
	msg.data[6] = brake_pressure_adc & 0xff;
	msg.data[7] = (brake_pressure_adc >> 8) & 0xff;

	return msg;
}
void Parse_CC_TransmitPedals(uint8_t *data, uint16_t *accel0, uint16_t *accel1,
		uint16_t *brake, uint16_t *brake_pressure_adc) {
	*accel0 = (data[1]) << 8 | data[0];
	*accel1 = (data[3]) << 8 | data[2];
	*brake = (data[5]) << 8 | data[4];
	*brake_pressure_adc = (data[7]) << 8 | data[6];
}

CC_TransmitSteering_t Compose_CC_TransmitSteering(int16_t steering0,
		int16_t steering1) {
	CC_TransmitSteering_t msg;
	msg.id = CC_TransmitSteering_ID;

	msg.data[0] = steering0 & 0xff;
	msg.data[1] = (steering0 >> 8) & 0xff;
	msg.data[2] = steering1 & 0xff;
	msg.data[3] = (steering1 >> 8) & 0xff;

	return msg;
}
void Parse_CC_TransmitSteering(uint8_t *data, int16_t *steering0,
		int16_t *steering1) {
	*steering0 = (data[1]) << 8 | data[0];
	*steering1 = (data[3]) << 8 | data[2];
}

CC_OBJ_DICT_t Compose_CC_OBJ_DICT(uint8_t data[8]) {
	CC_OBJ_DICT_t msg;
	msg.id = CC_OBJ_DICT_ID;

	for (int i = 0; i < 8; i++) {
		msg.data[i] = data[i];
	}

	return msg;
}
void Parse_CC_OBJ_DICT(uint8_t *data, uint8_t *type, uint8_t *data_size,
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

#endif
