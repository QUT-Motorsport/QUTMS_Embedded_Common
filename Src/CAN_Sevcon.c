/*
 * CAN_Sevcon.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Calvin
 */

#include <CAN_Sevcon.h>

#ifdef QUTMS_CAN_SEVCON

uint32_t sevcon_hc_msg_id(sevcon_pgn_t pgn, uint32_t dest, uint32_t source) {
	uint32_t id = (((((uint32_t)pgn) & 0x1FFFF) + (dest & 0xFF)) << 8) | (source & 0xFF);
	return id;
}

sevcon_hs_t Compose_Sevcon_HC1(uint8_t dest, uint8_t source, int16_t torqueDemand, sevcon_cmd_t controlWord, int16_t torqueLimitDrive)
{
	sevcon_hs_t msg;
	msg.id = sevcon_hc_msg_id(SEVCON_PGN_HC1, dest, source);

	msg.data[0] = torqueDemand & 0xFF;
	msg.data[1] = (torqueDemand >> 8) & 0xFF;
	msg.data[2] = controlWord & 0xFF;
	msg.data[3] = 0;
	msg.data[4] = torqueLimitDrive & 0xFF;
	msg.data[5] = (torqueLimitDrive >> 8) & 0xFF;
	msg.data[6] = 0;
	msg.data[7] = 0;

	return msg;
}

#endif
