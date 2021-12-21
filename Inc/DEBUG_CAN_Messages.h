/*
 * DEBUG_CAN_Messages.h
 *
 *  Created on: Oct 12, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_DEBUG_CAN_MESSAGES_H_
#define COMMON_INC_DEBUG_CAN_MESSAGES_H_

#include "QUTMS_can.h"

// ERROR CODES
#define DEBUG_ERROR_APPS_IMPLAUSIBILITY			0x10 // T.4.2.5
#define DEBUG_ERROR_BSE_IMPLAUSIBILITY			0x11 // T.4.3.3
#define DEBUG_ERROR_PEDAL_IMPLAUSIBILITY		0x12 // EV.5.7

typedef struct DEBUG_Version {
	uint32_t id;
	uint8_t data[4];
} DEBUG_Version_t;

DEBUG_Version_t Compose_DEBUG_Version (uint8_t boardID, uint8_t boardIndex, uint8_t vMajor, uint8_t vMinor);

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

typedef struct DEBUG_ErrorPresent
{
	uint32_t id;
	uint8_t data[4];
} DEBUG_ErrorPresent_t;

DEBUG_ErrorPresent_t Compose_DEBUG_ErrorPresent(uint8_t boardID, uint8_t boardIndex, uint16_t errorCode);

#endif /* COMMON_INC_DEBUG_CAN_MESSAGES_H_ */
