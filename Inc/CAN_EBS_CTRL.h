/*
 * CAN_EBS_CTRL.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Calvin
 */

#ifndef INC_CAN_EBS_CTRL_H_
#define INC_CAN_EBS_CTRL_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum  {
	EBS_CTRL_STATE_START = 0x00,
	EBS_CTRL_STATE_GAS_CHECK = 0x01,
	EBS_CTRL_STATE_BOARD_CHECK = 0x02,
	EBS_CTRL_STATE_ASMS_KEY = 0x03,
	EBS_CTRL_STATE_BRAKE_CHECK = 0x04,
	EBS_CTRL_STATE_BRAKE_TEST = 0x05,
	EBS_CTRL_STATE_BRAKE_LOW = 0x06,
	EBS_CTRL_STATE_BRAKE_HIGH = 0x07,
	EBS_CTRL_STATE_CTRL_ACK = 0x08,
	EBS_CTRL_STATE_IDLE = 0x10,
	EBS_CTRL_STATE_PCHRG_PRESSED = 0x11,
	EBS_CTRL_STATE_CHECK_TS = 0x12,
	EBS_CTRL_STATE_CHECK_COMPUTE = 0x13,
	EBS_CTRL_STATE_READY = 0x14,
	EBS_CTRL_STATE_BRAKE_RELEASE = 0x15,
	EBS_CTRL_STATE_DRIVE = 0x16,
	EBS_CTRL_STATE_BRAKE_ACTIVATE = 0x17,
	EBS_CTRL_STATE_SHUTDOWN = 0x0F,
	EBS_CTRL_STATE_ERROR = 0xFF
} EBS_CTRL_STATE;

typedef union EBS_CTRL_Flags {
	uint16_t rawMem;
	struct {
		uint8_t HB_VCU_CTRL : 1;
		uint8_t HB_DVL : 1;
		uint8_t WATCHDOG : 1;
		uint8_t SOL_A : 1;
		uint8_t SOL_B : 1;
		uint8_t GAS_A : 1;
		uint8_t GAS_B : 1;
		uint8_t GAS_C : 1;
		uint8_t GAS_D : 1;
		uint8_t SHDN_DET : 1;
		uint8_t ASMS : 1;
		uint8_t RES : 1;
	} _EBS_CTRL_Flags;
} EBS_CTRL_Flags_u;

typedef struct EBS_CTRL_HeartbeatState {
	uint8_t stateID;
	EBS_CTRL_Flags_u flags;
} EBS_CTRL_HeartbeatState_t;

typedef struct EBS_CTRL_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} EBS_CTRL_Heartbeat_t;

EBS_CTRL_Heartbeat_t Compose_EBS_CTRL_Heartbeat(EBS_CTRL_HeartbeatState_t *state);
void Parse_EBS_CTRL_Heartbeat(uint8_t *data, EBS_CTRL_HeartbeatState_t *state);

typedef struct EBS_CTRL_Voltages {
	uint32_t id;
	uint8_t data[8];
} EBS_CTRL_Voltages_t;

EBS_CTRL_Voltages_t Compose_EBS_CTRL_Voltages(uint16_t asms, uint16_t battery24V);

#endif /* INC_CAN_EBS_CTRL_H_ */
