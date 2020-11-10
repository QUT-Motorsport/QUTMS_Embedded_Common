/**
 ******************************************************************************
 * @file CC_CAN_Messages.c
 * @brief Chassis Controller CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_CC

#include "CC_CAN_Messages.h"

CC_ReadyToDrive_t Compose_CC_ReadyToDrive(void)
{
	CC_ReadyToDrive_t p;
	p.id = Compose_CANId(0x2, 0x16, 0x0, 0x0, 0x0, 0x0);
	return p;
}

CC_FatalShutdown_t Compose_CC_FatalShutdown(void)
{
	CC_FatalShutdown_t p;
	p.id = Compose_CANId(0x2, 0x16, 0x0, 0x1, 0x0, 0x0);
	return p;
}

CC_SoftShutdown_t Compose_CC_SoftShutdown(void)
{
	CC_SoftShutdown_t p;
	p.id = Compose_CANId(0x2, 0x18, 0x0, 0x1, 0x1, 0x0);
	return p;
}

#endif
