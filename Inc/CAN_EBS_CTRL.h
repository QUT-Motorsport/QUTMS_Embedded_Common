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
	EBS_CTRL_STATE_START = 0x00
} EBS_CTRL_STATE;

typedef union EBS_CTRL_Flags {
	uint16_t rawMem;
	struct {
		uint8_t HB_VCU_CTRL : 1;
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


#endif /* INC_CAN_EBS_CTRL_H_ */
