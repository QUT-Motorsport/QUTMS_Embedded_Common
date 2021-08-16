/*
 * General_Sensor_CAN_Messages.c
 *
 *  Created on: 27 Jul 2021
 *      Author: Calvin
 */

#ifdef QUTMS_CAN_GENERAL_SENSOR

#include "General_Sensor_CAN_Messages.h"


General_Sensor_LinearPot_t Compose_General_Sensor_Travel (uint8_t boardNum, uint16_t travel1, uint16_t travel2) {
	General_Sensor_LinearPot_t packet;
	packet.id = GENERAL_SENSOR_LinearPot_ID;
	packet.data[0] = boardNum;
	packet.data[1] = (travel1 >> 8) & 0xFF;
	packet.data[2] = travel1 & 0xFF;
	packet.data[3] = (travel2 >> 8) & 0xFF;
	packet.data[4] = travel2 & 0xFF;

	return packet;
}

void Parse_General_Sensor_Travel(uint8_t *data, uint8_t *boardNum, uint16_t *travel1, uint16_t *travel2) {
	*boardNum = data[0];
	*travel1 = (data[1] << 8) | data[2];
	*travel2 = (data[3] << 8) | data[4];
}

#endif
