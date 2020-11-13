/**
 ******************************************************************************
 * @file BMS_CAN_Messages.c
 * @brief BMS CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_BMS

#include "BMS_CAN_Messages.h"

BMS_BadCellVoltage_t Compose_BMS_BadCellVoltage(uint8_t BMSId, uint8_t cellNumber, uint8_t voltage)
{
	BMS_BadCellVoltage_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, CAN_TYPE_ERROR, 0x0, 0x00, BMSId);
	packet.data[0] = (BMSId & 0xF) | (cellNumber & 0xF) << 4;
	packet.data[1] = voltage;

	return packet;
}

void Parse_BMS_BadCellVoltage(uint8_t* data, uint8_t* BMSId, uint8_t* cellNumber, uint8_t* voltage)
{
	*BMSId = (data[0] & 0xF);
	*cellNumber = (data[0] >> 4) & 0xF;
	*voltage = data[1];
}

BMS_BadCellTemperature_t Compose_BMS_BadCellTemperature(uint8_t BMSId, uint8_t cellNumber, uint8_t temperature)
{
	BMS_BadCellTemperature_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, CAN_TYPE_ERROR, 0x0, 0x01, BMSId);
	packet.data[0] = (BMSId & 0xF) | (cellNumber & 0xF) << 4;
	packet.data[1] = temperature;

	return packet;
}

void Parse_BMS_BadCellTemperature(uint8_t* data, uint8_t* BMSId, uint8_t* cellNumber, uint8_t* temperature)
{
	*BMSId = (data[0] & 0xF);
	*cellNumber = (data[0] >> 4) & 0xF;
	*temperature = data[1];
}

BMS_TransmitVoltage_t Compose_BMS_TransmitVoltage(uint8_t BMSId, uint8_t vMsgId, uint16_t voltages[4])
{
	BMS_TransmitVoltage_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, 0x0, CAN_TYPE_TRANSMIT, 0x02, BMSId);
	packet.data[0] = vMsgId << 6 | (voltages[0] & 0x3F);
	packet.data[1] = (voltages[0] >> 6) & 0x3F;

	packet.data[2] = voltages[1] & 0x3F;
	packet.data[3] = (voltages[1] >> 6) & 0x3F;

	packet.data[4] = voltages[2] & 0x3F;
	packet.data[5] = (voltages[2] >> 6) & 0x3F;

	packet.data[6] = voltages[3] & 0x3F;
	packet.data[7] = (voltages[3] >> 6) & 0x3F;

	return packet;
}

void Parse_BMS_TransmitVoltage(uint32_t canId, uint8_t* data, uint8_t* BMSId, uint8_t* vMsgId, uint16_t* voltages)
{
	*BMSId = canId & 0xF;
	*vMsgId = data[0] >> 6 & 0x3;
	*(voltages) = data[1] << 6 | (data[0] & 0x3F);
	*(voltages+1) = data[3] << 6 | (data[2] & 0x3F);
	*(voltages+2) = data[5] << 6 | (data[4] & 0x3F);
	*(voltages+3) = data[7] << 6 | (data[6] & 0x3F);
}

BMS_TransmitTemperature_t Compose_BMS_TransmitTemperature(uint8_t BMSId, uint8_t tMsgId, uint8_t temperatures[6])
{
	BMS_TransmitTemperature_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, 0x0, CAN_TYPE_TRANSMIT, 0x3, BMSId);
	packet.data[0] = tMsgId > 0 ? 1 : 0;
	for(int i = 1; i < 7; i++)
	{
		packet.data[i] = temperatures[i-1];
	}

	return packet;
}

void Parse_BMS_TransmitTemperature(uint32_t canId, uint8_t* data, uint8_t* BMSId, uint8_t* tMsgId, uint8_t* temperatures)
{
	*BMSId = canId & 0xF;
	*tMsgId = data[0];
	for(int i = 1; i < 7; i++)
	{
		*(temperatures+i-1) = data[i];
	}
}

BMS_ChargeEnabled_t Compose_BMS_ChargeEnabled(uint8_t BMSId)
{
	BMS_ChargeEnabled_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, 0x0, CAN_TYPE_RECEIVE, 0x0, BMSId);

	return packet;
}

void Parse_ChargeEnabled(uint32_t canId, uint8_t* BMSId)
{
	Parse_CANId(canId, NULL, NULL, NULL, NULL, NULL, BMSId);
}

#endif
