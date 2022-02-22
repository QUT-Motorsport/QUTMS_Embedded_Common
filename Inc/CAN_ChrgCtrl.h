/*
 * CAN_ChgCtrl.h
 *
 *  Created on: 22 Feb. 2022
 *      Author: Calvin J
 */

#ifndef COMMON_INC_CAN_CHGCTRL_H_
#define COMMON_INC_CAN_CHGCTRL_H_

#include <QUTMS_can.h>
#include <stdint.h>

enum CHRGCTRL_STATES {
	CHRGCTRL_STATE_IDLE = 0x00,
	CHRGCTRL_STATE_PRECHARGE_REQUEST = 0x01,
	CHRGCTRL_STATE_PRECHARGE = 0x02,
	CHRGCTRL_STATE_CHARGING = 0x03,
	CHRGCTRL_STATE_STOP_CHARGE = 0x0F
};

typedef union CHRGCTRL_Flags {
	uint8_t rawMem;
	struct {
		uint8_t HB_AMS;
	};
} CHRGCTRL_Flags_u;

typedef struct CHRGCTRL_HeartbeatState {
	uint8_t stateID;
	CHRGCTRL_Flags_u flags;
} CHRGCTRL_HeartbeatState_t;

typedef struct CHRGCTRL_Heartbeat {
	uint32_t id;
	uint8_t data[2];
} CHRGCTRL_Heartbeat_t;

CHRGCTRL_Heartbeat_t Compose_CHRG_CTRL_Hearbeat(CHRGCTRL_HeartbeatState_t *state);
void Parse_CHRG_CTRL_Hearbeat(uint8_t *data, CHRGCTRL_HeartbeatState_t *state);

#endif /* COMMON_INC_CAN_CHGCTRL_H_ */
