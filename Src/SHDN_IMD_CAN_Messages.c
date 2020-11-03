/**
 ******************************************************************************
 * @file SHDN_IMD_CAN_Messages.c
 * @brief Shutdown IMD CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_SHDN_IMD

#include "SHDN_IMD_CAN_Messages.h"

SHDN_IMD_HeartbeatRequest_t Compose_SHDN_IMD_HeartbeatRequest(void)
{
	SHDN_IMD_HeartbeatRequest_t p;
	p.id = Compose_CANId(0x1, 0x0E, 0x0, 0x1, 0x00, 0x0);
	return p;
}

SHDN_IMD_HeartbeatResponse_t Compose_SHDN_IMD_HeartbeatResponse(uint8_t pwmState)
{
	SHDN_IMD_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x0E, 0x0, 0x1, 0x01, 0x0);
	p.data = pwmState;
	return p;
}

void Parse_SHDN_IMD_HeartbeatResponse(SHDN_IMD_HeartbeatResponse_t packet, uint8_t* pwmState)
{
	*pwmState = packet.data;
}

#endif
