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
	SW_STATE_READY = 0x02,
	SW_STATE_SELECT_MISSION = 0x03,
	SW_MISSION_ACK = 0x04,
	SW_STATE_IN_MISSION = 0x05
};

enum DRIVERLESS_MISSIONS {
	MISSION_NONE = 0x00,
	MISSION_MANUAL = 0x01,
	MISSION_INSPECTION = 0x02,
	MISSION_EBS = 0x03,
	MISSION_TRACK = 0x04
};

typedef union SW_Flags {
	uint16_t rawMem;
	struct {
		uint8_t HB_VCU_CTRL : 1;
		uint8_t HB_VCU_SHDN : 1;
		uint8_t P_CAN1 : 1;
		uint8_t P_ADC : 1;
		uint8_t FAN_ENABLE : 1;
		uint8_t MISSION_SELECTED : 1;
	} _SW_Flags;
} SW_Flags_u;

typedef struct SW_HeartbeatState {
	uint8_t stateID;
	uint8_t missionID;
	SW_Flags_u flags;
} SW_HeartbeatState_t;

typedef struct SW_Heartbeat {
	uint32_t id;
	uint8_t data[4];
} SW_Heartbeat_t;

SW_Heartbeat_t Compose_SW_Heartbeat(SW_HeartbeatState_t *state);
void Parse_SW_Heartbeat(uint8_t data[3], SW_HeartbeatState_t *state);

typedef struct SW_ActivateHorn {
	uint32_t id;
} SW_ActivateHorn_t;

SW_ActivateHorn_t Compose_SW_ActivateHorn();

#endif /* COMMON_INC_CAN_SW_H_ */
