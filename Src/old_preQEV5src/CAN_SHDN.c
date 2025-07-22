/**
 ******************************************************************************
 * @file SHDN_CAN_Messages.c
 * @brief Shutdown CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_SHDN

#include "CAN_SHDN.h"

SHDN_ShutdownTriggered_t Compose_SHDN_ShutdownTriggered()
{
	SHDN_ShutdownTriggered_t p;
	p.id = SHDN_ShutdownTriggered_ID;
	return p;
}

#endif
