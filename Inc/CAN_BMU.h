/*
 * CAN_BMU.h
 *
 *  Created on: 21 Jul. 2022
 *      Author: Calvin Johnson
 */

#ifndef INC_CAN_BMU_H_
#define INC_CAN_BMU_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum BMU_STATES {
	BMU_STATE_START = 0x00,
	BMU_STATE_INIT_PERIPHERAL = 0x01,
	BMU_STATE_INIT_CMU = 0x02,
	BMU_STATE_CHECK_CMU_CELL = 0x03,
	BMU_STATE_CHECK_CMU_TEMP = 0x04,
	BMU_STATE_CHECK_SENDYNE = 0x05,
	BMU_STATE_CHECK_BOARD = 0x06,
	BMU_STATE_READY = 0x07,
	BMU_STATE_PRECHARGE = 0x08,
	BMU_STATE_TS_ACTIVE = 0x09,
	BMU_STATE_CHRG_CHECK_BOARD = 0x16,
	BMU_STATE_CHRG_READY = 0x17,
	BMU_STATE_CHRG_PRECHARGE = 0x18,
	BMU_STATE_CHRG_TS_ACTIVE = 0x19,
	BMU_STATE_TRIG_SHDN = 0x0D,
	BMU_STATE_SHUTDOWN = 0xFE,
	BMU_STATE_ERROR = 0xFF
};

typedef union BMU_Flags {
	uint16_t rawMem;
	// 14 bits
	struct {
		uint8_t HB_CMU :1;
		uint8_t HB_SENDYNE1 :1;
		uint8_t HB_SENDYNE2 :1;
		uint8_t HB_VCU_CTRL :1;
		uint8_t HB_CHRG_CTRL :1;
		uint8_t P_CAN1 : 1;
		uint8_t P_CAN2 : 1;
		uint8_t C_POS : 1;
		uint8_t C_NEG : 1;
		uint8_t C_PCHRG : 1;
		uint8_t PCHRG_TIMEOUT : 1;
		uint8_t BMS_OVER_VOLT : 1;
		uint8_t BMS_UNDER_VOLT : 1;
		uint8_t BMS_BAD_TEMP : 1;
	};
} BMU_Flags_u;

typedef struct BMU_HeartbeatState {
	uint8_t stateID;
	BMU_Flags_u flags;
	uint16_t cmuStatus;
	uint16_t voltage;
	uint8_t SOC;
} BMU_HeartbeatState_t;

typedef struct BMU_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} BMU_Heartbeat_t;

BMU_Heartbeat_t Compose_BMU_Heartbeat(BMU_HeartbeatState_t *state);
void Parse_BMU_Heartbeat(uint8_t *data, BMU_HeartbeatState_t *state);

#endif /* INC_CAN_BMU_H_ */