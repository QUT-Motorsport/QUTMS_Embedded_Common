/*
 * CAN_VCU.h
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_CAN_VCU_H_
#define COMMON_INC_CAN_VCU_H_

#include <QUTMS_CAN.h>
#include <stdbool.h>

enum VCU_STATES {
	VCU_STATE_START = 0x00,
	VCU_STATE_PERIPHERAL_INIT = 0x01,
	VCU_STATE_SENSOR_INIT = 0x02,
	VCU_STATE_BOARD_CHECK = 0x03,
	VCU_STATE_ERROR = 0xFF,
};

typedef union VCU_Flags_Dave {
	uint16_t rawMem;
	// 16 bits
	struct {
		uint8_t HB_AMS :1;
		uint8_t HB_MCISO :1;
		uint8_t HB_INV :1;
		uint8_t P_CAN :1;
		uint8_t P_ADC :1;
		uint8_t S_Accel0 :1;
		uint8_t S_Accel1 :1;
		uint8_t S_Brake :1;
		uint8_t PCHRG_Failed :1;
		uint8_t SHDN :1;
		uint8_t IMP_APPS :1; 		// T.4.2.5
		uint8_t IMP_BSE :1; 		// T.4.3.3
		uint8_t IMP_Pedal :1; 		// EV.5.7

	};
} VCU_Flags_Dave_u;

typedef struct VCU_HeartbeatState {
	uint8_t stateID;
	uint16_t flags;
	uint16_t VCU;
} VCU_HeartbeatState_t;

typedef struct VCU_Heartbeat {
	uint32_t id;
	uint8_t data[5];
} VCU_Heartbeat_t;

VCU_Heartbeat_t Compose_VCU_Heartbeat(uint8_t id, VCU_HeartbeatState_t *state);
void Parse_VCU_Heartbeat(uint8_t *data, VCU_HeartbeatState_t *state);

typedef struct VCU_MotorTemp {
	uint32_t id;
	uint8_t data[8];
} VCU_MotorTemp_t;

VCU_MotorTemp_t Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0, uint32_t temp1);

typedef struct VCU_IMU_Accel {
	uint32_t id;
	uint8_t data[8];
} VCU_IMU_Accel_t;

VCU_IMU_Accel_t Compose_VCU_IMU_Accel(uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z);

typedef struct VCU_IMU_Gyro {
	uint32_t id;
	uint8_t data[8];
} VCU_IMU_Gyro_t;

VCU_IMU_Gyro_t Compose_VCU_IMU_Gyro(uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z);

typedef struct VCU_LinearTravel {
	uint32_t id;
	uint8_t data[5];
} VCU_LinearTravel_t;

VCU_LinearTravel_t Compose_VCU_LinearTravel(uint8_t VCU_ID, bool front, uint16_t t0, uint16_t t1);

typedef struct VCU_AirPressure {
	uint32_t id;
	uint8_t data[4];
} VCU_AirPressure_t;

VCU_AirPressure_t Compose_VCU_AirPressure(uint8_t VCU_ID, uint16_t pressure_raw, int16_t pressure);

typedef struct VCU_ShutdownStatus_t {
	uint32_t id;
	uint8_t data[3];
} VCU_ShutdownStatus_t;

VCU_ShutdownStatus_t Compose_VCU_ShutdownStatus(uint8_t line0, uint8_t line1, uint8_t line2, uint8_t line3, bool status);
void Parse_VCU_ShutdownStatus(uint8_t *data, uint8_t *line0, uint8_t *line1, uint8_t *line2, uint8_t *line3,
bool *status);

#endif /* COMMON_INC_CAN_VCU_H_ */
