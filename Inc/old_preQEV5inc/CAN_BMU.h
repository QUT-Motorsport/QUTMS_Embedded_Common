/*
 * CAN_BMU.h
 *
 *  Created on: 21 Jul. 2022
 *      Author: Calvin Johnson
 */

#ifndef INC_CAN_BMU_H_
#define INC_CAN_BMU_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum  {
	BMU_STATE_START = 0x00,
	BMU_STATE_INIT_PERIPHERAL = 0x01,
	BMU_STATE_INIT_CMU = 0x02,
	BMU_STATE_CHECK_CMU_GPIO = 0x03,
	BMU_STATE_CHECK_SENDYNE = 0x04,
	BMU_STATE_CHECK_BOARD = 0x05,
	BMU_STATE_READY = 0x06,
	BMU_STATE_PRECHARGE = 0x07,
	BMU_STATE_TS_ACTIVE = 0x08,
	BMU_STATE_CHRG_CHECK_BOARD = 0x16,
	BMU_STATE_CHRG_READY = 0x17,
	BMU_STATE_CHRG_PRECHARGE = 0x18,
	BMU_STATE_CHRG_TS_ACTIVE = 0x19,
	BMU_STATE_CHRG_FAIL = 0x1A,
	BMU_STATE_TRIG_SHDN = 0x0D,
	BMU_STATE_SHUTDOWN = 0x0F,
	BMU_STATE_ERROR = 0xFF
} bmu_state_t;

typedef union BMU_Flags {
	uint32_t rawMem;
	// 28 bits
	struct {
		uint8_t HB_CMU :1;
		uint8_t HB_SENDYNE1 :1;
		uint8_t HB_SENDYNE2 :1;
		uint8_t HB_VCU_CTRL :1;

		uint8_t HB_CHRG_CTRL :1;
		uint8_t P_WATCHDOG :1;
		uint8_t P_CAN1 :1;
		uint8_t P_CAN2 :1;

		uint8_t C_POS :1;
		uint8_t C_NEG :1;
		uint8_t C_PCHRG :1;
		uint8_t PCHRG_TIMEOUT :1;

		uint8_t CMU_OVER_VOLT :1;
		uint8_t CMU_UNDER_VOLT :1;
		uint8_t CMU_BAD_TEMP :1;
		uint8_t CMU_OPEN_VOLT : 1;

		uint8_t CMU_OPEN_TEMP : 1;
		uint8_t CMU_MISSING_VOLT : 1;
		uint8_t CMU_MISSING_TEMP : 1;
		uint8_t SHDN_BMU :1;

		uint8_t SHDN_PDOC :1;
		uint8_t SHDN_IMD :1;
		uint8_t SHDN_INTERLOCK :1;
		uint8_t BALANCING : 1;

		uint8_t DIE_TEMPS : 1;
		uint8_t HV_KEY : 1;
		uint8_t CHRG_DET : 1;
		uint8_t CHRG_CTRL : 1;
	} _BMU_Flags;
} BMU_Flags_u;

typedef struct BMU_HeartbeatState {
	uint8_t stateID;
	BMU_Flags_u flags;
	uint8_t packState;
	uint8_t SOC;
} BMU_HeartbeatState_t;

typedef struct BMU_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} BMU_Heartbeat_t;

BMU_Heartbeat_t Compose_BMU_Heartbeat(BMU_HeartbeatState_t *state);
void Parse_BMU_Heartbeat(uint8_t *data, BMU_HeartbeatState_t *state);

typedef struct BMU_TransmitVoltage {
	uint32_t id;
	uint8_t data[8];
} BMU_TransmitVoltage_t;

BMU_TransmitVoltage_t Compose_BMU_TransmitVoltage(uint8_t cmuId, uint8_t packId,
		uint16_t voltages[3], uint16_t age);
void Parse_BMU_TransmitVoltage(uint8_t *data, uint16_t voltages[3], uint16_t *age);

typedef struct BMU_TransmitTemperature {
	uint32_t id;
	uint8_t data[8];
} BMU_TransmitTemperature_t;

BMU_TransmitTemperature_t Compose_BMU_TransmitTemperature(uint8_t cmuId,
		uint8_t packId, uint8_t temps[6], uint16_t age);
void Parse_BMU_TransmitTemperatures(uint8_t *data, uint8_t temps[6], uint16_t *age);

typedef struct BMU_TransmitBalancing {
	uint32_t id;
	uint8_t data[8];
} BMU_TransmitBalancing_t;

BMU_TransmitBalancing_t Compose_BMU_TransmitBalancing(uint8_t cmuId, uint16_t balanceState, uint8_t dieTemp);

typedef struct BMU_TransmitDieTemps {
	uint32_t id;
	uint8_t data[8];
} BMU_TransmitDieTemps_t;

BMU_TransmitDieTemps_t Compose_BMU_TransmitDieTemps(uint8_t packId, uint8_t temps[8]);

typedef struct BMU_TransmitPackInfo {
	uint32_t id;
	uint8_t data[8];
} BMU_TransmitPackInfo_t;

BMU_TransmitPackInfo_t Compose_BMU_TransmitPackInfo(int32_t current, int32_t voltage_pack);

typedef struct BMU_TransmitPower {
	uint32_t id;
	uint8_t data[8];
} BMU_TransmitPower_t;

BMU_TransmitPower_t Compose_BMU_TransmitPower(int32_t power);

#endif /* INC_CAN_BMU_H_ */
