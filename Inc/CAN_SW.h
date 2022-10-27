/*
 * CAN_SW.h
 *
 *  Created on: Mar 17, 2022
 *      Author: Calvin J
 */

#ifndef COMMON_INC_CAN_SW_H_
#define COMMON_INC_CAN_SW_H_

#include <stdint.h>

enum SW_STATES {
	SW_STATE_START = 0x00,
	SW_STATE_INIT_PERIPHERAL = 0x01,
	SW_STATE_READY = 0x02
};

typedef union SW_Flags {
	uint16_t rawMem;
	struct {
		uint8_t HB_VCU_CTRL : 1;
		uint8_t HB_VCU_SHDN : 1;
		uint8_t P_CAN1 : 1;
		uint8_t P_ADC : 1;
		uint8_t FAN_ENABLE : 1;

		// DVL Mission Selection Bits
		uint8_t DVL_MISSION_SKIDPAD : 1;
		uint8_t DVL_MISSION_AUTOCROSS : 1;
		uint8_t DVL_MISSION_ACCELERATION : 1;
		uint8_t DVL_MISSION_TRACKDRIVE : 1;
		uint8_t DVL_MISSION_SCRUIT : 1;
		uint8_t DVL_MISSION_MANUAL : 1;
	} _SW_Flags;
} SW_Flags_u;

typedef struct SW_HeartbeatState {
	uint8_t stateID;
	SW_Flags_u flags;
} SW_HeartbeatState_t;

typedef struct SW_Heartbeat {
	uint32_t id;
	uint8_t data[3];
} SW_Heartbeat_t;

SW_Heartbeat_t Compose_SW_Heartbeat(SW_HeartbeatState_t *state);
void Parse_SW_Heartbeat(uint8_t data[3], SW_HeartbeatState_t *state);

typedef struct SW_ActivateHorn {
	uint32_t id;
} SW_ActivateHorn_t;

SW_ActivateHorn_t Compose_SW_ActivateHorn();

#endif /* COMMON_INC_CAN_SW_H_ */
