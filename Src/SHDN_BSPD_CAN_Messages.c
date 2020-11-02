/**
 ******************************************************************************
 * @file SHDN_BSPD_CAN_Messages.c
 * @brief Shutdown BSPD CAN Messages
 ******************************************************************************
 */

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
	p.data = (calibration & 0x3) | (min << 3) | (max << 4);
	return p;
}

void Parse_SHDN_BSPD_RequestCalibration(SHDN_BSPD_RequestCalibration_t packet, uint8_t* calibration, bool* min, bool* max)
{
	*calibration = (uint8_t)(packet.data & 0x3);
	*min = (bool)(packet.data & 0x4);
	*max = (bool)(packet.data & 0x8);

}
