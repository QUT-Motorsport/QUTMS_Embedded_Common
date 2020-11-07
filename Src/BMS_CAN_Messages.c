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
	packet.id = Compose_CANId(0x0, 0x12, 0x0, 0x0, 0x00, BMSId);
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
	packet.id = Compose_CANId(0x0, 0x12, 0x0, 0x0, 0x01, BMSId);
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
	packet.id = Compose_CANId(0x2, 0x12, 0x0, 0x3, 0x02, BMSId);
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
	Parse_CANId(canId, NULL, NULL, NULL, NULL, NULL, BMSId); // We dont care about any packet info except the BMSId.
	*vMsgId = data[0] >> 6 & 0x3;
	*(voltages) = data[1] << 6 | (data[0] & 0x3F);
	*(voltages+1) = data[3] << 6 | (data[2] & 0x3F);
	*(voltages+2) = data[5] << 6 | (data[4] & 0x3F);
	*(voltages+3) = data[7] << 6 | (data[6] & 0x3F);
}

BMS_TransmitTemperature_t Compose_BMS_TransmitTemperature(uint8_t BMSId, uint8_t tMsgId, uint8_t temperatures[6])
{
	BMS_TransmitTemperature_t packet;
	packet.id = Compose_CANId(0x0, 0x12, 0x0, 0x3, 0x3, BMSId);
	packet.data[0] = tMsgId > 0 ? 1 : 0;
	for(int i = 1; i < 7; i++)
	{
		packet.data[i] = temperatures[i-1];
	}

	return packet;
}

void Parse_BMS_TransmitTemperature(uint32_t canId, uint8_t* data, uint8_t* BMSId, uint8_t* tMsgId, uint8_t* temperatures)
{
	Parse_CANId(canId, NULL, NULL, NULL, NULL, NULL, BMSId);
	*tMsgId = data[0];
	for(int i = 1; i < 7; i++)
	{
		*(temperatures+i-1) = data[i];
	}
}

BMS_ChargeEnabled_t Compose_BMS_ChargeEnabled(uint8_t BMSId)
{
	BMS_ChargeEnabled_t packet;
	packet.id = Compose_CANId(0x2, 0x12, 0x0, 0x2, 0x0, BMSId);

	return packet;
}

void Parse_ChargeEnabled(uint32_t canId, uint8_t* BMSId)
{
	Parse_CANId(canId, NULL, NULL, NULL, NULL, NULL, BMSId);
}

BMS_TransmitDeviceId_t Compose_BMS_TransmitDeviceId(uint8_t BMSId, uint32_t uid)
{
	BMS_TransmitDeviceId_t packet;
	BMSId = 0x0; // We don't use BMSId here, as we don't know our ID assigned by AMS yet.
	packet.id = Compose_CANId(0x2, 0x12, 0x0, 0x3, 0x1, BMSId);
	packet.data[0] = (uid & 0xFF);
	packet.data[1] = ((uid >> 8) & 0xFF);
	packet.data[2] = ((uid >> 16) & 0xFF);
	packet.data[3] = ((uid >> 24) & 0xFF);

	return packet;
}

void Parse_BMS_TransmitDeviceId(uint32_t canId, uint8_t* data, uint8_t* BMSId, uint32_t* uid)
{
	Parse_CANId(canId, NULL, NULL, NULL, NULL, NULL, BMSId); // BMSId from CANId will be 0x0 as we haven't assigned one yet.
	*uid = (data[3] << 24 | data[2] << 16 | data[1] << 8 | (data[0] & 0xFF));
}

BMS_SetBMSId_t Compose_BMS_SetBMSId(uint8_t BMSId, uint32_t uid)
{
	BMS_SetBMSId_t packet;
	packet.id = Compose_CANId(0x2, 0x12, 0x0, 0x2, 0x01, 0x0); // BMS not looking for its ID, so we won't put it in the CAN id.
	packet.data[0] = (uid & 0xFF);
	packet.data[1] = ((uid >> 8) & 0xFF);
	packet.data[2] = ((uid >> 16) & 0xFF);
	packet.data[3] = ((uid >> 24) & 0xFF);
	packet.data[4] = BMSId;

	return packet;
}

void Parse_BMS_SetBMSId(uint32_t canId, uint8_t* data, uint8_t* BMSId, uint32_t* uid)
{
	Parse_CANId(canId, NULL, NULL, NULL, NULL, NULL, BMSId); // BMSId from CANId will be 0x0 as we haven't assigned one yet.
	*uid = (data[3] << 24 | data[2] << 16 | data[1] << 8 | (data[0] & 0xFF));
	*BMSId = data[4];
}

#endif
