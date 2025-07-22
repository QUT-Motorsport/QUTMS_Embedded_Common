/*
 * MCISO_CAN.h
 *
 *  Created on: 23 Dec. 2021
 *      Author: Calvin J
 */

#ifndef COMMON_INC_CAN_MCISO_H_
#define COMMON_INC_CAN_MCISO_H_

#include <QUTMS_can.h>
#include <stdint.h>

#define MCISO_COUNT 2

enum MCISO_STATES {
	MCISO_STATE_START = 0x00,
	MCISO_STATE_FORWARD = 0x01
};


typedef union MCISO_Flags {
	uint8_t rawMem;
	struct {
		uint8_t CAN_INV : 1;
		uint8_t HB_VCU_CTRL : 1;
		uint8_t HB_INV0 : 1;
		uint8_t HB_INV1 : 1;
		uint8_t HB_BMU : 1;
		uint8_t WATCHDOG : 1;
	};
} MCISO_Flags_u;

typedef struct MCISO_HeartbeatState {
	uint8_t stateID;
	MCISO_Flags_u errorFlags;
} MCISO_HeartbeatState_t;

// Heartbeat

typedef struct MCISO_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} MCISO_Heartbeat_t;

MCISO_Heartbeat_t Compose_MCISO_Heartbeat(uint8_t id, MCISO_HeartbeatState_t *state);
void Parse_MCISO_Heartbeat(uint8_t *data, MCISO_HeartbeatState_t *state);


#endif /* COMMON_INC_CAN_MCISO_H_ */
