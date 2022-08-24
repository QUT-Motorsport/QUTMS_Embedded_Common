/*
 * CAN_VCU.h
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_CAN_VCU_H_
#define COMMON_INC_CAN_VCU_H_

#include <QUTMS_can.h>
#include <stdbool.h>

#define VCU_ID_SHDN 0
#define VCU_ID_CTRL 1
#define VCU_ID_DASH 2

#define VCU_OD_ID_CTRL_REGEN_MAX_CURRENT 0x00
#define VCU_OD_ID_CTRL_REGEN_DEADZONE 0x01

enum VCU_STATES {
	VCU_STATE_START = 0x00,
	VCU_STATE_PERIPHERAL_INIT = 0x01,
	VCU_STATE_SENSOR_INIT = 0x02,
	VCU_STATE_BOARD_CHECK = 0x03,
	VCU_STATE_BMU_CHECK = 0x04,
	VCU_STATE_IDLE = 0x05,
	VCU_STATE_PRECHARGE_REQUEST = 0x06,
	VCU_STATE_PRECHARGE = 0x07,
	VCU_STATE_INVERTER_CHECK = 0x08,
	VCU_STATE_RTD_RDY = 0x09,
	VCU_STATE_RTD_BTN = 0x10,
	VCU_STATE_DRIVING = 0x11,
	VCU_STATE_DASH = 0x12,
	VCU_STATE_SHDN = 0x13,
	VCU_STATE_SHUTDOWN = 0x0F,
	VCU_STATE_TS_ERROR = 0xFE,
	VCU_STATE_ERROR = 0xFF,

	// A0 for Autonomous
	VCU_STATE_IDLE_DVL = 0xA0 + VCU_STATE_IDLE,
	VCU_STATE_PRECHARGE_REQUEST_DVL =  0xA0 + VCU_STATE_PRECHARGE_REQUEST,
	VCU_STATE_PRECHARGE_DVL = 0xA0 + VCU_STATE_PRECHARGE,
	VCU_STATE_INVERTER_CHECK_DVL = 0xA0 + VCU_STATE_INVERTER_CHECK,
	VCU_STATE_RTD_RDY_DVL = 0xA0 + VCU_STATE_RTD_RDY,
	VCU_STATE_RTD_BTN_DVL = 0xA0 + VCU_STATE_RTD_BTN,
	VCU_STATE_DRIVING_DVL = 0xA0 + VCU_STATE_DRIVING,
};

typedef union VCU_Flags_Core {
	uint8_t rawMem;
	struct {
		uint8_t P_CAN : 1;
		uint8_t P_ADC : 1;
		uint8_t P_ISRC : 1;
		uint8_t P_IMU : 1;
		uint8_t P_Watchdog : 1;
	} _VCU_Flags_Core;
} VCU_Flags_Core_u;

typedef union VCU_Flags_Ctrl {
	uint16_t rawMem;
	// 12 bits
	struct {
		uint8_t HB_BMU : 1;
		uint8_t HB_MCISO : 1;
		uint8_t HB_INV : 1;
		uint8_t S_Accel0 : 1;
		uint8_t S_Accel1 : 1;
		uint8_t S_Brake0 : 1;
		uint8_t S_Brake1 : 1;
		uint8_t PCHRG_Failed : 1;
		uint8_t SHDN : 1;
		uint8_t IMP_APPS : 1;	// T.4.2.5
		uint8_t IMP_BSE : 1;	// T.4.3.3
		uint8_t IMP_Pedal : 1;	// EV.5.7
	} _VCU_Flags_Ctrl;
} VCU_Flags_Ctrl_u;

typedef union VCU_Flags_Dash {
	uint16_t rawMem;
	// 11 bits
	struct {
		uint8_t HB_BMU : 1;
		uint8_t HB_VCU_SHDN : 1;
		uint8_t S_Sus_L : 1;
		uint8_t S_Sus_R : 1;
		uint8_t S_Steer0 : 1;
		uint8_t S_Steer1 : 1;
		uint8_t IMP_Steer : 1;
		uint8_t LED_AMS : 1;
		uint8_t LED_IMD : 1;
		uint8_t LED_BSPD : 1;
		uint8_t LED_PDOC : 1;
	} _VCU_Flags_Dash;
} VCU_Flags_Dash_u;

typedef union VCU_Flags_SHDN {
	uint16_t rawMem;
	struct {
		uint8_t S_Sus_L : 1;
		uint8_t S_Sus_R : 1;
		uint8_t SHDN_Status : 1;
		uint8_t DVL_RTD_BTN : 1;
	} _VCU_Flags_SHDN;
} VCU_Flags_SHDN_u;

typedef union VCU_Flags_Other {
	uint16_t rawMem;
	VCU_Flags_Ctrl_u ctrl;
	VCU_Flags_Dash_u dash;
	VCU_Flags_SHDN_u shdn;
} VCU_Flags_Other_u;

typedef struct VCU_HeartbeatState {
	uint8_t stateID;
	VCU_Flags_Core_u coreFlags;
	VCU_Flags_Other_u otherFlags;
	uint16_t VCU;
} VCU_HeartbeatState_t;

typedef struct VCU_Heartbeat {
	uint32_t id;
	uint8_t data[5];
} VCU_Heartbeat_t;

VCU_Heartbeat_t Compose_VCU_Heartbeat(uint8_t id, VCU_HeartbeatState_t *state);
void Parse_VCU_Heartbeat(uint8_t *data, VCU_HeartbeatState_t *state);

typedef struct VCU_RTD {
	uint32_t id;
} VCU_RTD_t;

VCU_RTD_t Compose_VCU_RTD();

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

typedef struct VCU_TransmitSteering {
	uint32_t id;
	uint8_t data[4];
} VCU_TransmitSteering_t;

VCU_TransmitSteering_t Compose_VCU_TransmitSteering(int16_t steering0, int16_t steering1);
void Parse_VCU_TransmitSteering(uint8_t *data, int16_t *steering0, int16_t *steering1);

typedef struct VCU_ShutdownStatus_t {
	uint32_t id;
	uint8_t data[3];
} VCU_ShutdownStatus_t;

VCU_ShutdownStatus_t Compose_VCU_ShutdownStatus(uint8_t line0, uint8_t line1, uint8_t line2, uint8_t line3,
												bool status);
void Parse_VCU_ShutdownStatus(uint8_t *data, uint8_t *line0, uint8_t *line1, uint8_t *line2, uint8_t *line3,
							  bool *status);

typedef struct VCU_Pedal_Accel {
	uint32_t id;
	uint8_t data[4];
} VCU_Pedal_Accel_t;

VCU_Pedal_Accel_t Compose_VCU_Pedal_Accel(uint16_t accel0, uint16_t accel1);
void Parse_VCU_Pedal_Accel(uint8_t *data, uint16_t *accel0, uint16_t *accel1);

typedef struct VCU_Pedal_Brake {
	uint32_t id;
	uint8_t data[6];
} VCU_Pedal_Brake_t;

VCU_Pedal_Brake_t Compose_VCU_Pedal_Brake(uint16_t brake, uint16_t brake_adc0, uint16_t brake_adc1);
void Parse_VCU_Pedal_Brake(uint8_t *data, uint16_t *brake, uint16_t *brake_adc0, uint16_t *brake_adc1);

// Object Dictionary

typedef struct VCU_OBJ_DICT {
	uint32_t id;
	uint8_t data[8];
} VCU_OBJ_DICT_t;

VCU_OBJ_DICT_t Compose_VCU_OBJ_DICT(uint8_t VCU_ID, uint8_t data[8]);
void Parse_VCU_OBJ_DICT(uint8_t *data, uint8_t *type, uint8_t *data_size, uint8_t *index, uint32_t *value);

#endif /* COMMON_INC_CAN_VCU_H_ */
