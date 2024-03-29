/**
 ******************************************************************************
 * @file BMS_CAN_Messages.c
 * @brief BMS CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_BMS

#include <CAN_BMS.h>

BMS_BadCellVoltage_t Compose_BMS_BadCellVoltage(uint8_t BMSId, uint8_t cellNumber, uint8_t voltage) {
	BMS_BadCellVoltage_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_ERROR, 0x0, BMSId);
	packet.data[0] = (BMSId & 0xF) | (cellNumber & 0xF) << 4;
	packet.data[1] = voltage;

	return packet;
}

void Parse_BMS_BadCellVoltage(uint8_t *data, uint8_t *BMSId, uint8_t *cellNumber, uint8_t *voltage) {
	*BMSId = (data[0] & 0xF);
	*cellNumber = (data[0] >> 4) & 0xF;
	*voltage = data[1];
}

BMS_BadCellTemperature_t Compose_BMS_BadCellTemperature(uint8_t BMSId, uint8_t cellNumber, uint8_t temperature) {
	BMS_BadCellTemperature_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_ERROR, 0x01, BMSId);
	packet.data[0] = (BMSId & 0xF) | (cellNumber & 0xF) << 4;
	packet.data[1] = temperature;

	return packet;
}

void Parse_BMS_BadCellTemperature(uint8_t *data, uint8_t *BMSId, uint8_t *cellNumber, uint8_t *temperature) {
	*BMSId = (data[0] & 0xF);
	*cellNumber = (data[0] >> 4) & 0xF;
	*temperature = data[1];
}

BMS_TransmitVoltage_t Compose_BMS_TransmitVoltage(uint8_t BMSId, uint8_t vMsgId, uint16_t voltages[BMS_VOLT_PACK_COUNT]) {
	BMS_TransmitVoltage_t packet;
	packet.id = BMS_TransmitVoltage_ID | BMSId;

	packet.data[0] = (vMsgId << 6) | (voltages[0] & 0x3F);
	packet.data[1] = (voltages[0] >> 6) & 0x3F;

	packet.data[2] = voltages[1] & 0x3F;
	packet.data[3] = (voltages[1] >> 6) & 0x3F;

	packet.data[4] = voltages[2] & 0x3F;
	packet.data[5] = (voltages[2] >> 6) & 0x3F;

	packet.data[6] = voltages[3] & 0x3F;
	packet.data[7] = (voltages[3] >> 6) & 0x3F;

	return packet;
}

void Parse_BMS_TransmitVoltage(uint8_t *data, uint8_t *vMsgId, uint16_t voltages[BMS_VOLT_PACK_COUNT]) {
	*vMsgId = (data[0] >> 6) & 0x3;
	voltages[0] = ((data[1] & 0x3F) << 6) | (data[0] & 0x3F);
	voltages[1] = ((data[3] & 0x3F) << 6) | (data[2] & 0x3F);
	voltages[2] = ((data[5] & 0x3F) << 6) | (data[4] & 0x3F);
	voltages[3] = ((data[7] & 0x3F) << 6) | (data[6] & 0x3F);
}

BMS_TransmitTemperature_t Compose_BMS_TransmitTemperature(uint8_t BMSId, uint8_t tMsgId,
		uint8_t temperatures[BMS_TEMP_PACK_COUNT]) {
	BMS_TransmitTemperature_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x3, BMSId);
	packet.data[0] = tMsgId;
	for (int i = 0; i < BMS_TEMP_PACK_COUNT; i++) {
		packet.data[i + 1] = temperatures[i];
	}

	return packet;
}

void Parse_BMS_TransmitTemperature(uint8_t *data, uint8_t *tMsgId, uint8_t temperatures[BMS_TEMP_PACK_COUNT]) {
	*tMsgId = data[0];
	for (int i = 0; i < BMS_TEMP_PACK_COUNT; i++) {
		temperatures[i] = data[i + 1];
	}
}

BMS_ChargeEnabled_t Compose_BMS_ChargeEnabled(uint8_t bms_count) {
	BMS_ChargeEnabled_t packet;
	packet.id = BMS_ChargeEnabled_ID; //Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, 0x0, CAN_TYPE_RECEIVE, 0x0, 0);
	packet.data[0] = (bms_count & 0b1111);

	return packet;
}

void Parse_ChargeEnabled(uint32_t canId, uint8_t *data, uint8_t *bms_count) {
	*bms_count = (data[0] & 0b1111);
}

BMS_Shutdown_t Compose_BMS_Shutdown() {
	BMS_Shutdown_t packet;
	packet.id = BMS_Shutdown_ID;

	return packet;
}

BMS_ShutdownAck_t Compose_BMS_ShutdownAck(uint8_t bmsId) {
	BMS_ShutdownAck_t packet;
	packet.id = BMS_ShutdownAck_ID | (bmsId & 0xF);
	packet.data[0] = bmsId;

	return packet;
}

void Parse_BMS_ShutdownAck(uint32_t canId, uint8_t *data, uint8_t *bmsId) {
	*bmsId = data[0];
}

BMS_TransmitBalancing_t Compose_BMS_TransmitBalancing(uint8_t BMSId, uint16_t balancing_voltage,
		uint16_t balancing_state) {
	BMS_TransmitBalancing_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x04, BMSId);
	packet.data[0] = balancing_voltage & 0xff;
	packet.data[1] = (balancing_voltage >> 8) & 0xff;

	packet.data[2] = balancing_state & 0xff;
	packet.data[3] = (balancing_state >> 8) & 0xff;

	return packet;
}

void Parse_TransmitBalancing(uint32_t canId, uint8_t *data, uint8_t *BMSId, uint16_t *balancing_voltage,
		uint16_t *balancing_state) {
	*BMSId = canId & 0xF;
	*balancing_voltage = (data[1] << 8) | data[0];
	*balancing_state = (data[3] << 8) | data[2];
}

#endif
