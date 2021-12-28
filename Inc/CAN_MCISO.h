/*
 * MCISO_CAN.h
 *
 *  Created on: 23 Dec. 2021
 *      Author: Calvin J
 */

#ifndef COMMON_INC_CAN_MCISO_H_
#define COMMON_INC_CAN_MCISO_H_

#include <QUTMS_CAN.h>
#include <stdint.h>


typedef union MCISO_Flags {
	uint8_t rawMem;
	struct {
		uint8_t CAN_INV : 1;
		uint8_t HB_CC : 1;
		uint8_t HB_INV0 : 1;
		uint8_t HB_INV1 : 1;
	};
} MCISO_Flags_u;

typedef struct MCISO_HeartbeatState {
	uint8_t stateID;
	MCISO_Flags_u errorFlags;
} MCISO_HeartbeatState_t;

// Heartbeat

typedef struct MCISO_Heartbeat {
	uint32_t id;
	uint8_t data[2];
} MCISO_Heartbeat_t;

MCISO_Heartbeat_t Compose_MCISO_Heartbeat(uint8_t id, MCISO_HeartbeatState_t *state);
void Parse_MCISO_Heartbeat(uint8_t *data, MCISO_HeartbeatState_t *state);


#endif /* COMMON_INC_CAN_MCISO_H_ */
