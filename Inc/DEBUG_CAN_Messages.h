/*
 * DEBUG_CAN_Messages.h
 *
 *  Created on: Oct 12, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_DEBUG_CAN_MESSAGES_H_
#define COMMON_INC_DEBUG_CAN_MESSAGES_H_

#include "QUTMS_can.h"

typedef struct DEBUG_EnterState
{
	uint32_t id;
	uint8_t data[3];
} DEBUG_EnterState_t;

DEBUG_EnterState_t Compose_DEBUG_EnterState(uint8_t boardID, uint8_t boardIndex, uint8_t stateID);

typedef struct DEBUG_ExitState
{
	uint32_t id;
	uint8_t data[3];
} DEBUG_ExitState_t;

DEBUG_ExitState_t Compose_DEBUG_ExitState(uint8_t boardID, uint8_t boardIndex, uint8_t stateID);

#endif /* COMMON_INC_DEBUG_CAN_MESSAGES_H_ */
