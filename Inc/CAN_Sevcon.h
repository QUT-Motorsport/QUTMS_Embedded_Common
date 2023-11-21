/*
 * CAN_Sevcon.h
 *
 *  Created on: Nov 18, 2023
 *      Author: Calvin
 */

#ifndef INC_CAN_SEVCON_H_
#define INC_CAN_SEVCON_H_

#include <stdint.h>

typedef enum {
	SEVCON_STATE_NOT_READY = 0x01,
	SEVCON_STATE_SHUTDOWN = 0x02,
	SEVCON_STATE_PRECHARGE = 0x04,
	SEVCON_STATE_ENERGISED = 0x07,
	SEVCON_STATE_ENABLED = 0x08,
	SEVCON_STATE_FAULT_ACTIVE = 0x0B,
	SEVCON_STATE_FAULT_OFF = 0x0D
} sevcon_state_t;

typedef enum {
	SEVCON_CMD_NONE = 0x00,
	SEVCON_CMD_ENERGISE = 0x03,
	SEVCON_CMD_ENABLE = 0x05,
	SEVCON_CMD_SHUTDOWN = 0x06,
	SEVCON_CMD_FAULT_RESET = 0x09,
	SEVCON_CMD_ACTIVE_SHORT = 0x0A
} sevcon_cmd_t;

typedef enum {
	SEVCON_PGN_HC1 = 0x11000U,
	SEVCON_PGN_HC2 = 0x11100U,
	SEVCON_PGN_HC3 = 0x11200U,
	SEVCON_PGN_HS1 = 0x11800U,
	SEVCON_PGN_HS2 = 0x11900U,
	SEVCON_PGN_HS3 = 0x11A00U,
	SEVCON_PGN_HS4 = 0x11B00U,
	SEVCON_PGN_HS5 = 0x11C00U,
} sevcon_pgn_t;

uint32_t sevcon_hc_msg_id(sevcon_pgn_t pgn, uint32_t dest, uint32_t source);

typedef struct {
	uint32_t id;
	uint8_t data[8];
} sevcon_hs_t;

sevcon_hs_t Compose_Sevcon_HC1(uint8_t dest, uint8_t source,
		int16_t torqueDemand, sevcon_cmd_t controlWord,
		int16_t torqueLimitDrive);
sevcon_hs_t Compose_Sevcon_HC2(uint8_t dest, uint8_t source,
		int16_t torqueLimitRegen, int16_t speedLimitForward,
		int16_t speedLimitBackward);
sevcon_hs_t Compose_Sevcon_HC3(uint8_t dest, uint8_t source,
		int16_t currentLimitDischarge, int16_t currentLimitCharge,
		int16_t targetCapVoltage);

#endif /* INC_CAN_SEVCON_H_ */
