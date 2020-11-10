/**
 ******************************************************************************
 * @file SHDN_CAN_Messages.c
 * @brief Shutdown CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_SHDN

#include "SHDN_CAN_Messages.h"

SHDN_ShutdownTriggered_t Compose_SHDN_ShudownTriggered(void)
{
	SHDN_ShutdownTriggered_t p;
	p.id = Compose_CANId(0x0, 0x06, 0x0, 0x0, 0x0, 0x0);
	return p;
}

SHDN_HeartbeatResponse_t Compose_SHDN_One_HeartbeatResponse(uint8_t segmentState)
{
	SHDN_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x06, 0x0, 0x01, 0x01, 0x0);
	p.data = segmentState;
	return p;
}

SHDN_HeartbeatResponse_t Compose_SHDN_Two_HeartbeatResponse(uint8_t segmentState)
{
	SHDN_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x06, 0x0, 0x01, 0x02, 0x0);
	p.data = segmentState;
	return p;
}

SHDN_HeartbeatResponse_t Compose_SHDN_Three_HeartbeatResponse(uint8_t segmentState)
{
	SHDN_HeartbeatResponse_t p;
	p.id = Compose_CANId(0x1, 0x06, 0x0, 0x01, 0x03, 0x0);
	p.data = segmentState;
	return p;
}

void Parse_SHDN_HeartbeatResponse(SHDN_HeartbeatResponse_t packet, uint8_t* segmentState)
{
	*segmentState = packet.data;
}

#endif
