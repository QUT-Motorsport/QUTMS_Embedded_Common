/*
 * CAN_Sendyne.c
 *
 *  Created on: Jan 2, 2022
 *      Author: Calvin
 */


#include "CAN_Sendyne.h"

Sendyne_RequestData_t Compose_Sendyne_RequestData(uint8_t sendyneID, uint8_t addr) {
	Sendyne_RequestData_t msg;
	msg.id = SENDYNE_CAN_REQUEST_ID | ((addr & 0xF) << 4);

	msg.data[0] = addr;

	return msg;
}
