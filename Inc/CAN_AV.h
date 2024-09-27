#ifndef INC_CAN_AV_H_
#define INC_CAN_AV_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum  {
	AV_STATE_MODE_MANUAL = 0x00,
	AV_STATE_MODE_DRIVERLESS = 0x01
} AV_STATE_MODE;

typedef enum {
	AV_STATE_MISSION_NONE = 0x00,
	AV_STATE_MISSION_INSPECTION = 0x01,
	AV_STATE_MISSION_EBS = 0x02,
	AV_STATE_MISSION_TRACKDRIVE = 0x03
} AV_STATE_MISSION;

typedef enum {
	AV_STATE_NOT_READY = 0x00,
	AV_STATE_START_MISSION = 0x01,
	AV_STATE_DRIVING = 0x02,
	AV_STATE_END = 0x03,
} AV_STATE;

typedef struct AV_STATE_HeartbeatState {
	uint8_t modeID;
	uint8_t missionID;
	uint8_t stateID;
} AV_STATE_HeartbeatState_t;

typedef struct AV_STATE_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} AV_STATE_Heartbeat_t;

AV_STATE_Heartbeat_t Compose_AV_STATE_Heartbeat(AV_STATE_HeartbeatState_t *state);
void Parse_AV_STATE_Heartbeat(uint8_t *data, AV_STATE_HeartbeatState_t *state);

#endif
