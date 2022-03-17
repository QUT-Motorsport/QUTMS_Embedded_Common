/*
 * DEBUG_CAN_Messages.c
 *
 *  Created on: Oct 12, 2021
 *      Author: Calvin
 */

#include <CAN_Debug.h>


DEBUG_EnterState_t Compose_DEBUG_EnterState(uint8_t boardID, uint8_t boardIndex, uint8_t stateID) {
	DEBUG_EnterState_t msg;

	msg.id = DEBUG_EnterState_ID;
	msg.data[0] = boardID;
	msg.data[1] = boardIndex;

	msg.data[2] = stateID;

	return msg;
}

DEBUG_ExitState_t Compose_DEBUG_ExitState(uint8_t boardID, uint8_t boardIndex, uint8_t stateID) {
	DEBUG_ExitState_t msg;

	msg.id = DEBUG_ExitState_ID;
	msg.data[0] = boardID;
	msg.data[1] = boardIndex;

	msg.data[2] = stateID;

	return msg;
}

DEBUG_ErrorPresent_t Compose_DEBUG_ErrorPresent(uint8_t boardID, uint8_t boardIndex, uint16_t errorCode) {
	DEBUG_ErrorPresent_t msg;

	msg.id = DEBUG_ErrorPresent_ID;
	msg.data[0] = boardID;
	msg.data[1] = boardIndex;

	msg.data[2] = errorCode & 0xFF;
	msg.data[3] = (errorCode >> 8) & 0xFF;

	return msg;
}
