#ifndef INC_CAN_AV_H_
#define INC_CAN_AV_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum  {
	AV_STATE_MODE_MANUAL = 0x00,
	AV_STATE_MODE_DRIVERLESS = 0x01
} AV_MODE;

typedef enum {
	AV_STATE_MISSION_NONE = 0x00,
	AV_STATE_MISSION_MANUAL = 0x01,
	AV_STATE_MISSION_INSPECTION = 0x02,
	AV_STATE_MISSION_EBS = 0x03,
	AV_STATE_MISSION_TRACKDRIVE = 0x04
} AV_MISSION;

typedef enum {
	AV_STATE_NOT_READY = 0x00,
	AV_STATE_START_MISSION = 0x01,
	AV_STATE_DRIVING = 0x02,
	AV_STATE_END = 0x03,
} AV_STATE;

typedef struct AV_HeartbeatState {
	uint8_t modeID;
	uint8_t missionID;
	uint8_t stateID;
} AV_Status_t;

typedef struct AV_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} AV_Heartbeat_t;

typedef union ROS_Flags
{
    uint8_t rawMem;
    struct
    {
        uint8_t STEERING_CTRL : 1;
        uint8_t SBG_OPERATIONAL : 1;
        uint8_t LIDAR_OPERATIONAL : 1;
        uint8_t PLANNING : 1;
        uint8_t GOOD_TO_GO : 1;
        uint8_t FINISHED : 1;
    } _ROS_Flags;
} ROS_Flags_u;

typedef struct ROS_HeartbeatState {
	ROS_Flags_u rosFlags;
	uint8_t identifiedCones;
	uint8_t mappedCones;
	uint8_t lap;
} ROS_Status_t;

typedef struct ROS_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} ROS_Heartbeat_t;

typedef struct Request_Heartbeat{
	uint32_t id;
	uint8_t data[8];
} Request_Heartbeat_t;

typedef struct Request{
	float torque;
	float steering;
	float speed;
} Request_t;

AV_Heartbeat_t Compose_AV_Heartbeat(AV_Status_t *state);
void Parse_AV_Heartbeat(uint8_t *data, AV_Status_t *state);

ROS_Heartbeat_t Compose_ROS_Heartbeat(ROS_Status_t *state);
void Parse_ROS_Heartbeat(uint8_t *data, ROS_Status_t *state);

Request_Heartbeat_t Compose_Request_Heartbeat(Request_t *state);
void Parse_Request_Heartbeat(uint8_t *data, Request_t *state);

#endif
