/**
 ******************************************************************************
 * @file AMS_CAN_Messages.c
 * @brief AMS CAN Messages
 ******************************************************************************
 */


#include "AMS_CAN_Messages.h"

AMS_CellVoltageShutdown_t Compose_AMS_CellVoltageShutdown(uint8_t cellNum, uint8_t bmsID, uint8_t voltage)
{
	AMS_CellVoltageShutdown_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x0, 0x0, 0x0);
	p.data[0] = (cellNum & 0xF) << 4 | (bmsID & 0xF);
	p.data[1] = (voltage & 0xFF);

	return p;
}

void Parse_AMS_CellVoltageShutdown(AMS_CellVoltageShutdown_t packet, uint8_t* cellNum, uint8_t* bmsID, uint8_t* voltage)
{
	*cellNum = (uint8_t)(packet.data[0] >> 4);
	*bmsID = (uint8_t)(packet.data[0] & 0xF);
	*voltage = (uint8_t)(packet.data[1] & 0xFF);
}

AMS_CellTemperatureShutdown_t Compose_AMS_CellTemperatureShutdown(uint8_t cellNum, uint8_t bmsID, uint8_t temperature)
{
	AMS_CellTemperatureShutdown_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x0, 0x1, 0x0);
	p.data[0] = (cellNum & 0xF) << 4 | (bmsID & 0xF);
	p.data[1] = (temperature & 0xFF);

	return p;
}

void Parse_AMS_CellTemperatureShutdown(AMS_CellTemperatureShutdown_t packet, uint8_t* cellNum, uint8_t* bmsID, uint8_t* temperature)
{
	*cellNum = (uint8_t)(packet.data[0] >> 4);
	*bmsID = (uint8_t)(packet.data[0] & 0xF);
	*temperature = (uint8_t)(packet.data[1] & 0xFF);
}

AMS_MissingBMS_t Compose_AMS_MissingBMS(bool data[12])
{
	//TODO Check
	AMS_MissingBMS_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x0, 0x2, 0x0);
	p.data[0] = 0 | (data[0] | (data[1] << 1) | (data[2] << 2) | (data[3] << 3) | (data[4] << 4) | (data[5] << 5) | (data[6] << 6) | (data[7] << 7));
	p.data[1] = 0 | (data[8] | (data[9] << 1) | (data[10] << 2) | (data[11] << 3) | data[12] << 4);

	return p;
}

void Parse_AMS_MissingBMS(AMS_MissingBMS_t packet, bool* data[12])
{
	return;
}

AMS_HeartbeatRequest_t Compose_AMS_HeartbeatRequest()
{
	AMS_HeartbeatRequest_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x1, 0x0, 0x0);

	return p;
}

AMS_HeartbeatResponse_t Compose_AMS_HeartbeatResponse(bool HVAn, bool HVBn, bool precharge, bool HVAp, bool HVBp, uint16_t averageVoltage, uint16_t runtime)
{

	AMS_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x10, 0x0, 0x1, 0x01, 0x0);

	p.data[0] = HVAn | (HVBn << 1) | (precharge << 2) | (HVAp << 4) | (HVBp << 5);
	p.data[1] = (averageVoltage & 0x3F);
	p.data[2] = (averageVoltage >> 6) & 0x3F;
	p.data[3] = (runtime & 0xFF);
	p.data[4] = (runtime >> 8);

	return p;
}

void Parse_AMS_HeartbeatResponse(AMS_HeartbeatResponse_t packet, bool* HVAn, bool* HVBn, bool* precharge, bool* HVAp, bool* HVBp, uint16_t* averageVoltage, uint16_t* runtime)
{
	*HVAn = (bool)(packet.data[0] & 0x1);
	*HVBn = (bool)(packet.data[0] & 0x2);
	*precharge = (bool)(packet.data[0] & 0x4);

	*HVAp = (bool)(packet.data[0] & 0x10);
	*HVBp = (bool)(packet.data[0] & 0x20);

	*averageVoltage = (uint16_t)((packet.data[1] & 0x3F) << 6 | (packet.data[0]));
	*runtime = (uint16_t)(packet.data[3] << 8 | packet.data[2]);
}

AMS_StartUp_t Compose_AMS_StartUp()
{
	AMS_StartUp_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x0, 0x0);

	return p;
}

AMS_ResetTractive_t Compose_AMS_ResetTractive()
{
	AMS_ResetTractive_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x1, 0x0);

	return p;
}

AMS_Shutdown_t Compose_AMS_Shutdown()
{
	AMS_Shutdown_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x2, 0x0);

	return p;
}

AMS_RequestTemperature_t Compose_AMS_RequestTemperature()
{
	AMS_RequestTemperature_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x3, 0x0);

	return p;
}

AMS_TransmitTemperature_t Compose_AMS_TransmitTemperature(uint8_t temperature)
{
	AMS_TransmitTemperature_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x3, 0x3, 0x0);
	p.data[0] = temperature;

	return p;
}

void Parse_AMS_TransmitTemperature(AMS_TransmitTemperature_t packet, uint8_t* temperature)
{
	*temperature = packet.data[0];
}

AMS_RequestChargeState_t Compose_AMS_RequestChargeState()
{
	AMS_RequestChargeState_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x2, 0x4, 0x0);

	return p;
}

AMS_TransmitChargeState_t Compose_AMS_TransmitChargeState(uint16_t chargeState)
{
	AMS_TransmitChargeState_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x3, 0x4, 0x0);
	p.data[0] = chargeState >> 8;
	p.data[1] = (chargeState & 0xFF);

	return p;
}

void Parse_AMS_TransmitChargeState(AMS_TransmitChargeState_t packet, uint16_t* chargeState)
{
	*chargeState = (packet.data[0] << 8 | packet.data[1]);
}

AMS_Ready_t Compose_AMS_Ready()
{
	AMS_Ready_t p;
	p.id = Compose_CANId(0x0, 0x10, 0x0, 0x3, 0x0, 0x0);

	return p;
}
