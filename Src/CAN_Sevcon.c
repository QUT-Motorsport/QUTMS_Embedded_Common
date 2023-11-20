/*
 * CAN_Sevcon.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Calvin
 */

#include <CAN_Sevcon.h>

uint32_t sevcon_hc_msg_id(sevcon_pgn_t pgn, uint32_t dest, uint32_t source) {
	uint32_t id = (((((uint32_t)pgn) & 0x1FFFF) + (dest & 0xFF)) << 8) | (source & 0xFF);
	return id;
}
