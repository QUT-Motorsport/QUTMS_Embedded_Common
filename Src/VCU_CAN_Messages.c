/*
 * VCU_CAN_Messages.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */


#ifdef QUTMS_VCU

#include "VCU_CAN_Messages.h"

VCU_MotorTemp_t Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0, uint32_t temp1) {
	VCU_MotorTemp_t msg;
	msg.id = VCU_MotorTemp_ID | VCU_ID;

	msg.data[0] = (temp0 >> 0) & 0xFF;
	msg.data[1] = (temp0 >> 8) & 0xFF;
	msg.data[2] = (temp0 >> 16) & 0xFF;
	msg.data[3] = (temp0 >> 24) & 0xFF;
	msg.data[4] = (temp1 >> 0) & 0xFF;
	msg.data[5] = (temp1 >> 8) & 0xFF;
	msg.data[6] = (temp1 >> 16) & 0xFF;
	msg.data[7] = (temp1 >> 24) & 0xFF;

	return msg;
}

#endif
