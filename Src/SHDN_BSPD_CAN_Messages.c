/**
 ******************************************************************************
 * @file SHDN_BSPD_CAN_Messages.c
 * @brief Shutdown BSPD CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_SHDN_BSPD

#include "SHDN_BSPD_CAN_Messages.h"

SHDN_BSPD_Fault_t Compose_SHDN_BSPD_Fault(void)
{
	SHDN_BSPD_Fault_t p;
	p.id = Compose_CANId(0x0, 0x0A, 0x0, 0x0, 0x00, 0x0);
	return p;
}

SHDN_BSPD_HeartbeatRequest_t Compose_SHDN_BSPD_HeartbeatRequest(void)
{
	SHDN_BSPD_HeartbeatRequest_t p;
	p.id = Compose_CANId(0x1, 0x0A, 0x0, 0x1, 0x00, 0x0);
	return p;
}

SHDN_BSPD_HeartbeatResponse_t Compose_SHDN_BSPD_HeartbeatResponse(bool isShutdown, uint8_t bspdError, uint8_t brakeError, bool brakePedal, bool fivekW, bool trig)
{
	SHDN_BSPD_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x0A, 0x0, 0x1, 0x01, 0x0);
	p.data = isShutdown | (bspdError & 0x3) << 1 | (brakeError & 0x3) << 3 | (brakePedal << 5) | (fivekW << 6) | (trig << 7);
	return p;
}

void Parse_SHDN_BSPD_HeartbeatResponse(SHDN_BSPD_HeartbeatResponse_t packet, bool* isShutdown, uint8_t* bspdError, uint8_t* brakeError, bool* brakePedal, bool* fivekW, bool* trig)
{
	*isShutdown = (bool)(packet.data & 0x1);
	*bspdError = (uint8_t)((packet.data & 0x6) >> 1);
	*brakeError = (uint8_t)((packet.data & 0x18) >> 3);
	*brakePedal = (bool)(packet.data & 0x20);
	*fivekW = (bool)(packet.data & 0x40);
	*trig = (bool)(packet.data & 0x80);
}

SHDN_BSPD_RequestCalibration_t Compose_SHDN_BSPD_RequestCalibration(uint8_t calibration, bool min, bool max)
{
	SHDN_BSPD_RequestCalibration_t p;
	p.id = Compose_CANId(0x1, 0x0A, 0x0, 0x1, 0x01, 0x0);
	p.data = (calibration & 0x7) | (min << 3) | (max << 4);
	return p;
}

void Parse_SHDN_BSPD_RequestCalibration(SHDN_BSPD_RequestCalibration_t packet, uint8_t* calibration, bool* min, bool* max)
{
	*calibration = (uint8_t)(packet.data & 0x7);
	*min = (bool)(packet.data & 0x4);
	*max = (bool)(packet.data & 0x8);
}

SHDN_BSPD_SetCalibration_t Compose_SHDN_BSPD_SetCalibration(uint8_t calibration, bool min, bool max, uint16_t calibrationMin, uint16_t calibrationMax)
{
	SHDN_BSPD_SetCalibration_t p;
	p.id = Compose_CANId(0x1, 0x0A, 0x0, 0x2, 0x01, 0x0);
	p.data[0] = (calibration & 0x7) | (min << 3) | (max << 4);
	p.data[1] = (calibrationMin & 0xFF);
	p.data[2] = (calibrationMin >> 8);
	p.data[3] = (calibrationMax & 0xFF);
	p.data[4] = (calibrationMax >> 8);
	return p;
}

void Parse_SHDN_BSPD_SetCalibration(SHDN_BSPD_SetCalibration_t packet, uint8_t* calibration, bool* min, bool* max, uint16_t* calibrationMin, uint16_t* calibrationMax)
{
	*calibration = (uint8_t)(packet.data[0] & 0x7);
	*min = (bool)(packet.data[0] & 0x4);
	*max = (bool)(packet.data[0] & 0x8);
	*calibrationMin = (uint16_t)((packet.data[2] & 0x7) | (packet.data[1]));
	*calibrationMax = (uint16_t)((packet.data[4] & 0x7) | (packet.data[3]));
}


SHDN_BSPD_TransmitCalibration_t Compose_SHDN_BSPD_TransmitCalibration(uint8_t calibration, bool min, bool max, uint16_t calibrationMin, uint16_t calibrationMax)
{
	SHDN_BSPD_TransmitCalibration_t p;
	p.id = Compose_CANId(0x1, 0x0A, 0x0, 0x3, 0x01, 0x0);
	p.data[0] = (calibration & 0x7) | (min << 3) | (max << 4);
	p.data[1] = (calibrationMin & 0xFF);
	p.data[2] = (calibrationMin >> 8);
	p.data[3] = (calibrationMax & 0xFF);
	p.data[4] = (calibrationMax >> 8);
	return p;
}

void Parse_SHDN_BSPD_TransmitCalibration(SHDN_BSPD_TransmitCalibration_t packet, uint8_t* calibration, bool* min, bool* max, uint16_t* calibrationMin, uint16_t* calibrationMax)
{
	*calibration = (uint8_t)(packet.data[0] & 0x7);
	*min = (bool)(packet.data[0] & 0x4);
	*max = (bool)(packet.data[0] & 0x8);
	*calibrationMin = (uint16_t)((packet.data[2] & 0x7) | (packet.data[1]));
	*calibrationMax = (uint16_t)((packet.data[4] & 0x7) | (packet.data[3]));
}

SHDN_BSPD_RequestValues_t Compose_SHDN_BSPD_RequestValues(uint8_t value)
{
	SHDN_BSPD_RequestValues_t p;
	p.id = Compose_CANId(0x2, 0x0A, 0x0, 0x2, 0x02, 0x0);
	p.data = (value & 0x7);
	return p;
}

void Parse_SHDN_BSPD_RequestValues(SHDN_BSPD_RequestValues_t packet, uint8_t* value)
{
	*value = (uint8_t)(packet.data & 0x7);
}

SHDN_BSPD_TransmitValues_t Compose_SHDN_BSPD_TransmitValues(uint8_t selectValue, uint16_t outputValue)
{
	SHDN_BSPD_TransmitValues_t p;
	p.id = Compose_CANId(0x2, 0x0A, 0x0, 0x3, 0x02, 0x0);
	p.data[0] = (selectValue & 0x7);
	p.data[1] = (outputValue & 0xFF);
	p.data[2] = (outputValue >> 8);
	return p;
}

void Parse_SHDN_BSPD_TransmitValues(SHDN_BSPD_TransmitValues_t packet, uint8_t* selectValue, uint16_t* outputValue)
{
	*selectValue = (uint8_t)(packet.data[0] & 0x7);
	*outputValue = (uint16_t)(packet.data[2] << 8 | packet.data[1]);
}

SHDN_BSPD_StartupOk_t Compose_SHDN_BSPD_StartupOk(void)
{
	SHDN_BSPD_StartupOk_t p;
	p.id = Compose_CANId(0x2, 0x0A, 0x0, 0x3, 0x04, 0x0);
	return p;
}

SHDN_BSPD_Reset_t Compose_SHDN_BSPD_Reset(void)
{
	SHDN_BSPD_Reset_t p;
	p.id = Compose_CANId(0x2, 0x0A, 0x0, 0x2, 0x04, 0x0);
	return p;
}

#endif
