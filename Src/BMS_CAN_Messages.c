/**
 ******************************************************************************
 * @file BMS_CAN_Messages.c
 * @brief BMS CAN Messages
 ******************************************************************************
 */

#include "BMS_CAN_Messages.h"

BMS_BadCellVoltage_t Compose_BMS_BadCellVoltage(uint8_t BMSId, uint8_t cellNumber, uint8_t voltage)
{
	BMS_BadCellVoltage_t packet;
	packet.id = Compose_CANId(0x0, 0x12, 0x0, 0x0, 0x00, BMSId);
	packet.data[0] = (BMSId & 0xF) | (cellNumber & 0xF) << 4;
	packet.data[1] = voltage;

	return packet;
}

void Parse_BMS_BadCellVoltage(BMS_BadCellVoltage_t packet, uint8_t* BMSId, uint8_t* cellNumber, uint8_t* voltage)
{
	*BMSId = (packet.data[0] & 0xF);
	*cellNumber = (packet.data[0] >> 4) & 0xF;
	*voltage = packet.data[1];
}

BMS_BadCellTemperature_t Compose_BMS_BadCellTemperature(uint8_t BMSId, uint8_t cellNumber, uint8_t temperature)
{
	BMS_BadCellTemperature_t packet;
	packet.id = Compose_CANId(0x0, 0x12, 0x0, 0x0, 0x01, BMSId);
	packet.data[0] = (BMSId & 0xF) | (cellNumber & 0xF) << 4;
	packet.data[1] = temperature;

	return packet;
}

void Parse_BMS_BadCellTemperature(BMS_BadCellTemperature_t packet, uint8_t* BMSId, uint8_t* cellNumber, uint8_t* temperature)
{
	*BMSId = (packet.data[0] & 0xF);
	*cellNumber = (packet.data[0] >> 4) & 0xF;
	*temperature = packet.data[1];
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

void Parse_BMS_TransmitVoltage(BMS_TransmitVoltage_t packet, uint8_t* BMSId, uint8_t* vMsgId, uint16_t* voltages)
{
	Parse_CANId(packet.id, NULL, NULL, NULL, NULL, NULL, BMSId); // We dont care about any packet info except the BMSId.
	*vMsgId = packet.data[0] >> 6 & 0x3;
	*(voltages) = packet.data[1] << 6 | (packet.data[0] & 0x3F);
	*(voltages+1) = packet.data[3] << 6 | (packet.data[2] & 0x3F);
	*(voltages+2) = packet.data[5] << 6 | (packet.data[4] & 0x3F);
	*(voltages+3) = packet.data[7] << 6 | (packet.data[6] & 0x3F);
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

void Parse_BMS_TransmitTemperature(BMS_TransmitTemperature_t packet, uint8_t* BMSId, uint8_t* tMsgId, uint8_t* temperatures)
{
	Parse_CANId(packet.id, NULL, NULL, NULL, NULL, NULL, BMSId);
	*tMsgId = packet.data[0];
	for(int i = 1; i < 7; i++)
	{
		*(temperatures+i-1) = packet.data[i];
	}
}

BMS_ChargeEnabled_t Compose_BMS_ChargeEnabled(uint8_t BMSId)
{
	BMS_ChargeEnabled_t packet;
	packet.id = Compose_CANId(0x2, 0x12, 0x0, 0x2, 0x0, BMSId);

	return packet;
}

void Parse_ChargeEnabled(BMS_ChargeEnabled_t packet, uint8_t* BMSId)
{
	Parse_CANId(packet.id, NULL, NULL, NULL, NULL, NULL, BMSId);
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

void Parse_BMS_TransmitDeviceId(BMS_TransmitDeviceId_t packet, uint8_t* BMSId, uint32_t* uid)
{
	Parse_CANId(packet.id, NULL, NULL, NULL, NULL, NULL, BMSId); // BMSId from CANId will be 0x0 as we haven't assigned one yet.
	*uid = (packet.data[3] << 24 | packet.data[2] << 16 | packet.data[1] << 8 | (packet.data[0] & 0xFF));
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

void Parse_BMS_SetBMSId(BMS_SetBMSId_t packet, uint8_t* BMSId, uint32_t* uid)
{
	Parse_CANId(packet.id, NULL, NULL, NULL, NULL, NULL, BMSId); // BMSId from CANId will be 0x0 as we haven't assigned one yet.
	*uid = (packet.data[3] << 24 | packet.data[2] << 16 | packet.data[1] << 8 | (packet.data[0] & 0xFF));
	*BMSId = packet.data[4];
}
