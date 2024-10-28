/*
 * CAN_ACM.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Calvin
 */

#ifndef INC_CAN_ACM_H_
#define INC_CAN_ACM_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum  {
	ACM_STATE_START = 0x00,
	ACM_STATE_ASMS_KEY = 0x01,
	ACM_STATE_BOARD_CHECK = 0x02,
	ACM_STATE_MISSION_CHECK = 0x03,
	ACM_STATE_GAS_CHECK = 0x04,
	ACM_STATE_BRAKE_CHECK = 0x05,
	ACM_STATE_BRAKE_TEST = 0x06,
	ACM_STATE_BRAKE_LOW = 0x07,
	ACM_STATE_BRAKE_HIGH = 0x08,
	ACM_STATE_CTRL_ACK = 0x09,
	ACM_STATE_CHECK_TS = 0x10,
	ACM_STATE_TS_READY = 0x11,
	ACM_STATE_READY = 0x12,
	ACM_STATE_BRAKE_RELEASE = 0x13,
	ACM_STATE_DRIVE = 0x14,
	ACM_STATE_FINISHED = 0x15,
	ACM_STATE_SHUTDOWN = 0x0F,
	ACM_STATE_ERROR = 0xFF
} ACM_STATE;

typedef union ACM_Flags {
	uint16_t rawMem;
	struct {
		uint8_t HB_RES : 1;
		uint8_t HB_VCU_CTRL : 1;
		uint8_t HB_ROS : 1;
		uint8_t WATCHDOG : 1;
		uint8_t SOL_A : 1;
		uint8_t SOL_B : 1;
		uint8_t GAS_A : 1;
		uint8_t GAS_B : 1;
		uint8_t GAS_C : 1;
		uint8_t GAS_D : 1;
		uint8_t SHDN_DET : 1;
		uint8_t ASMS : 1;
		uint8_t AV_BTN : 1;
		uint8_t RES : 1;
	} _ACM_Flags;
} ACM_Flags_u;

typedef struct ACM_HeartbeatState {
	uint8_t stateID;
	ACM_Flags_u flags;
} ACM_HeartbeatState_t;

typedef struct ACM_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} ACM_Heartbeat_t;

ACM_Heartbeat_t Compose_ACM_Heartbeat(ACM_HeartbeatState_t *state);
void Parse_ACM_Heartbeat(uint8_t *data, ACM_HeartbeatState_t *state);

#endif /* INC_CAN_ACM_H_ */
