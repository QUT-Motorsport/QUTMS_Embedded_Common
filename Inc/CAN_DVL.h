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
	DVL_STATE_RELEASE_EBS = 0x0B,
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

typedef union DVL_DrivingDynamics1_Data {
	uint8_t data[8];
	struct {
		uint8_t speed_actual : 8;
		uint8_t speed_target : 8;
		int8_t steering_angle_actual : 8;
		int8_t steering_angle_target : 8;
		uint8_t brake_hydr_actual : 8;
		uint8_t brake_hydr_target : 8;
		int8_t motor_moment_actual : 8;
		int8_t motor_moment_target : 8;
	} _fields;
} DVL_DrivingDynamics1_Data_u;

typedef struct DVL_DrivingDynamics1 {
	uint32_t id;
	uint8_t data[8];
} DVL_DrivingDynamics1_t;

DVL_DrivingDynamics1_t Compose_DVL_DrivingDynamics1(DVL_DrivingDynamics1_Data_u *dynamics);

enum DVL_AS_State {
	DVL_AS_STATE_OFF = 0x1,
	DVL_AS_STATE_READY = 0x2,
	DVL_AS_STATE_DRIVING = 0x3,	
	DVL_AS_STATE_EBRAKE = 0x4,
	DVL_AS_STATE_FINISH = 0x5
};

enum DVL_EBS_State {
	DVL_EBS_STATE_UNAVAILABLE = 0x1,
	DVL_EBS_STATE_ARMED = 0x1,
	DVL_EBS_STATE_ACTIVATED = 0x2
};

enum DVL_AMI_State {
	DVL_AMI_STATE_ACCEL = 0x1,
	DVL_AMI_STATE_SKIDPAD = 0x2,
	DVL_AMI_STATE_TRACKDRIVE = 0x3,
	DVL_AMI_STATE_BRAKETEST = 0x4,
	DVL_AMI_STATE_INSPECTION = 0x5,
	DVL_AMI_STATE_AUTOCROSS = 0x6
};

enum DVL_SERVICE_BRAKE_State {
	DVL_SERVICE_BRAKE_STATE_AVAILABLE = 0x3
};

typedef union DVL_SystemStatus_Data {
	uint8_t data[5];
	struct {
		uint8_t AS_state : 3;
		uint8_t EBS_state : 2;
		uint8_t AMI_state : 3;
		uint8_t steering_state : 1;
		uint8_t service_brake_state : 2;
		uint8_t lap_counter : 4;
		uint8_t cones_count_actual : 8;
		uint32_t cones_count_all : 17;
	} _fields;
} DVL_SystemStatus_Data_u;

typedef struct DVL_SystemStatus_t {
	uint32_t id;
	uint8_t data[5];
} DVL_SystemStatus_t;

DVL_SystemStatus_t Compose_DVL_SystemStatus(DVL_SystemStatus_Data_u *status);

#endif
