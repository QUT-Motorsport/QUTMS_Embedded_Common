/*
 * CAN_Sendyne.h
 *
 *  Created on: Jan 2, 2022
 *      Author: Calvin
 */

#ifndef COMMON_INC_CAN_SENDYNE_H_
#define COMMON_INC_CAN_SENDYNE_H_

#include <stdint.h>

#define SENDYNE_CAN_REQUEST_ID 0xA100201
#define SENDYNE_CAN_RESPONSE_ID 0xA100200

typedef struct Sendyne_RequestData {
	uint32_t id;
	uint8_t data[1];
} Sendyne_RequestData_t;

Sendyne_RequestData_t Compose_Sendyne_RequestData(uint8_t sendyneID, uint8_t addr);

#endif /* COMMON_INC_CAN_SENDYNE_H_ */
