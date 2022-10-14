#ifndef INC_CAN_DVL_H_
#define INC_CAN_DVL_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef union DVL_Flags {
	uint16_t rawMem;
	struct {
		uint8_t DVL_OK : 1;
		uint8_t DVL_ESTOP : 1;
	} _DVL_Flags;
} DVL_Flags_u;

typedef struct DVL_HeartbeatState {
	uint8_t stateID;
	uint8_t missionID;
	DVL_Flags_u flags;
	int8_t wheel_speed[4];
} DVL_HeartbeatState_t;

typedef struct DVL_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} DVL_Heartbeat_t;

DVL_Heartbeat_t Compose_DVL_Heartbeat(DVL_HeartbeatState_t *state);
void Parse_DVL_Heartbeat(uint8_t *data, DVL_HeartbeatState_t *state);

#endif
