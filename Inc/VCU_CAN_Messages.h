/*
 * VCU_CAN_Messages.h
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_VCU_CAN_MESSAGES_H_
#define COMMON_INC_VCU_CAN_MESSAGES_H_

#include "QUTMS_can.h"

typedef struct VCU_MotorTemp
{
	uint32_t id;
	uint8_t data[8];
} VCU_MotorTemp_t;

VCU_MotorTemp_t Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0, uint32_t temp1);

#endif /* COMMON_INC_VCU_CAN_MESSAGES_H_ */
