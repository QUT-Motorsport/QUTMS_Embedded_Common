/*
 * VCU_CAN_Messages.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */


#ifdef QUTMS_VCU

#include "VCU_CAN_Messages.h"

VCU_MotorTemp_t Compose_VCU_MotorTemp(uint8_t VCU_ID, uint16_t temp0, uint16_t temp1) {
	VCU_MotorTemp_t msg;
	msg.id = VCU_MotorTemp_ID | VCU_ID;

	msg.data[0] = temp0 & 0xFF;
	msg.data[1] = (temp0 >> 8) & 0xFF;
	msg.data[2] = temp1 & 0xFF;
	msg.data[3] = (temp1 >> 8) & 0xFF;

	return msg;
}

#endif
