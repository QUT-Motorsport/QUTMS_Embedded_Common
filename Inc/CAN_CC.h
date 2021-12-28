/**
 ******************************************************************************
 * @file CAN_CC.h
 * @brief Chassis Controller CAN Messages
 ******************************************************************************
 */

#ifndef INC_CC_CAN_MESSAGES_H_
#define INC_CC_CAN_MESSAGES_H_

#include <stdbool.h>
#include <stdlib.h>
#include "QUTMS_can.h"

enum CC_STATES {
	CC_STATE_START = 0x00,
	CC_STATE_PERIPHERAL_INIT = 0x01,
	CC_STATE_SENSOR_INIT = 0x02,
	CC_STATE_BOARD_CHECK = 0x03,
	CC_STATE_AMS_CHECK = 0x04,
	CC_STATE_IDLE = 0x05,
	CC_STATE_PRECHARGE_REQUEST = 0x06,
	CC_STATE_PRECHARGE = 0x07,
	CC_STATE_INVERTER_CHECK = 0x08,
	CC_STATE_RTD_RDY = 0x09,
	CC_STATE_RTD_BTN = 0x10,
	CC_STATE_DRIVING = 0x11,
	CC_STATE_SHUTDOWN = 0x0F,
	CC_STATE_TS_ERROR = 0xFE,
	CC_STATE_ERROR = 0xFF
};

typedef union CC_Flags {
	uint16_t rawMem;
	// 16 bits
	struct {
		uint8_t HB_AMS : 1;
		uint8_t HB_MCISO : 1;
		uint8_t HB_VESC : 1;
		uint8_t P_CAN : 1;
		uint8_t P_ADC : 1;
		uint8_t S_Accel0 : 1;
		uint8_t S_Accel1 : 1;
		uint8_t S_Brake : 1;
		uint8_t S_Steering0 : 1;
		uint8_t S_Steering1 : 1;
		uint8_t PCHRG_Failed : 1;
		uint8_t SHDN : 1;
		uint8_t IMP_APPS : 1; 		// T.4.2.5
		uint8_t IMP_BSE : 1; 		// T.4.3.3
		uint8_t IMP_Pedal : 1; 		// EV.5.7
		uint8_t IMP_Steering : 1;   // for TV
	};
} CC_Flags_u;


typedef struct CC_HeartbeatState {
	uint8_t stateID;
	CC_Flags_u errorFlags;
} CC_HeartbeatState_t;


// Heartbeat

typedef struct CC_Heartbeat {
	uint32_t id;
	uint8_t data[3];
} CC_Heartbeat_t;

CC_Heartbeat_t Compose_CC_Heartbeat(CC_HeartbeatState_t *state);
void Parse_CC_Heartbeat(uint8_t *data, CC_HeartbeatState_t *state);

// RTD

typedef struct CC_RTD {
	uint32_t id;
} CC_RTD_t;

CC_RTD_t Compose_CC_RTD();

// Shutdown

typedef struct CC_Shutdown {
	uint32_t id;
} CC_Shutdown_t;

CC_Shutdown_t Compose_CC_Shutdown();

// Pedals

typedef struct CC_TransmitPedals {
	uint32_t id;
	uint8_t data[8];
} CC_TransmitPedals_t;

CC_TransmitPedals_t Compose_CC_TransmitPedals(uint16_t accel0, uint16_t accel1, uint16_t brake, uint16_t brake_pressure_adc);
void Parse_CC_TransmitPedals(uint8_t* data, uint16_t *accel0, uint16_t *accel1, uint16_t *brake, uint16_t *brake_pressure_adc);

// Steering

typedef struct CC_TransmitSteering {
	uint32_t id;
	uint8_t data[4];
} CC_TransmitSteering_t;

CC_TransmitSteering_t Compose_CC_TransmitSteering(int16_t steering0, int16_t steering1);
void Parse_CC_TransmitSteering(uint8_t *data, int16_t *steering0, int16_t *steering1);


// Object Dictionary

typedef struct CC_OBJ_DICT {
	uint32_t id;
	uint8_t data[8];
} CC_OBJ_DICT_t;

CC_OBJ_DICT_t Compose_CC_OBJ_DICT(uint8_t data[8]);
void Parse_CC_OBJ_DICT(uint8_t *data, uint8_t *type, uint8_t *data_size, uint8_t *index, uint32_t *value);










#endif /* INC_CC_CAN_MESSAGES_H_ */
