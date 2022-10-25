#ifndef INC_CAN_DVL_H_
#define INC_CAN_DVL_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum AS_STATE {
	AS_state_off = 0,
	AS_state_ready = 1,
	AS_state_driving = 2,
	AS_state_emergency_brake = 3,
	AS_state_finish = 4
};

enum DVL_STATES {
	DVL_STATE_START = 0x00,
	DVL_STATE_SELECT_MISSION = 0x01,
	DVL_STATE_CHECK_EBS = 0x02,
	DVL_STATE_READY = 0x03,
	DVL_STATE_DRIVING = 0x04,
	DVL_STATE_ACTIVATE_EBS = 0x0A,
	DVL_STATE_FINISHED = 0x0F,
	DVL_STATE_EMERGENCY = 0xFF
};

enum DVL_MISSION {
	DVL_MISSION_NONE = 0x00,
	DVL_MISSION_MANUAL = 0x01,
	DVL_MISSION_SELECTED = 0x02
};

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
	float torqueRequest;
} DVL_HeartbeatState_t;

typedef struct DVL_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} DVL_Heartbeat_t;

DVL_Heartbeat_t Compose_DVL_Heartbeat(DVL_HeartbeatState_t *state);
void Parse_DVL_Heartbeat(uint8_t *data, DVL_HeartbeatState_t *state);

#endif
