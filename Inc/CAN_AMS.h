/**
 ******************************************************************************
 * @file CAN_AMS.h
 * @brief AMS CAN Messages
 ******************************************************************************
 */

#ifndef INC_AMS_CAN_MESSAGES_H_
#define INC_AMS_CAN_MESSAGES_H_

#include <QUTMS_CAN.h>
#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>

enum AMS_STATES {
	AMS_STATE_START = 0x00,
	AMS_STATE_INIT_PERIPHERAL = 0x01,
	AMS_STATE_INIT_BMS = 0x02,
	AMS_STATE_INIT_CAN4 = 0x03,
	AMS_STATE_CHECK_BMS = 0x04,
	AMS_STATE_CHECK_SENDYNE = 0x05,
	AMS_STATE_READY = 0x06,
	AMS_STATE_PRECHARGE = 0x07,
	AMS_STATE_TS_ACTIVE = 0x08,
	AMS_STATE_SHUTDOWN = 0x0F,
	AMS_STATE_ERROR = 0xFF
};

typedef union AMS_Flags {
	uint16_t rawMem;
	//
	struct {
		uint8_t HB_BMS : 1;
		uint8_t HB_SENDYNE0 : 1;
		uint8_t HB_SENDYNE1 : 1;
		uint8_t HB_CC : 1;
		uint8_t C_HVAn : 1;
		uint8_t C_HVBn : 1;
		uint8_t C_HVAp : 1;
		uint8_t C_HVBp : 1;
		uint8_t C_Precharge : 1;
		uint8_t PCHRG_TIMEOUT : 1;
	};
} AMS_Flags_u;

typedef struct AMS_HeartbeatState {
	uint8_t stateID;
	AMS_Flags_u flags;
	uint16_t bmsStatus;
	uint16_t voltage;
	uint8_t SOC;
} AMS_HeartbeatState_t;

typedef struct AMS_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} AMS_Heartbeat_t;

AMS_Heartbeat_t Compose_AMS_Heartbeat(AMS_HeartbeatState_t *state);
void Parse_AMS_Heartbeat(uint8_t *data, AMS_HeartbeatState_t *state);

typedef struct AMS_ShutdownTriggered {
	uint32_t id;
} AMS_ShutdownTriggered_t;

AMS_ShutdownTriggered_t Compose_AMS_ShutdownTriggered();

// Object Dictionary

typedef struct AMS_OBJ_DICT {
	uint32_t id;
	uint8_t data[8];
} AMS_OBJ_DICT_t;

AMS_OBJ_DICT_t Compose_AMS_OBJ_DICT(uint8_t data[8]);
void Parse_AMS_OBJ_DICT(uint8_t *data, uint8_t *type, uint8_t *data_size, uint8_t *index, uint32_t *value);

/**
 * @brief AMS Cell Voltage Shutdown Message
 */
typedef struct AMS_CellVoltageShutdown_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[2]; /**< Data */
} AMS_CellVoltageShutdown_t;

/**
 * @brief AMS Cell Voltage Shutdown Message Composer
 * @param cellNum The cell number relating to the voltage
 * @param bmsID The BMS ID
 * @param voltage The voltage of said cell
 * @return The composed AMS_CellVoltageShutdown_t packet
 */
AMS_CellVoltageShutdown_t Compose_AMS_CellVoltageShutdown(uint8_t cellNum, uint8_t bmsID, uint8_t voltage);

/**
 * @brief AMS Cell Voltage Shutdown Message Parser
 * @param packet The AMS_CellVoltageShutdown_t packet to parse
 * @param cellNum The cell number relating to the voltage
 * @param bmsID The BMS ID
 * @param voltage The voltage of said cell
 */
void Parse_AMS_CellVoltageShutdown(uint8_t* data, uint8_t* cellNum, uint8_t* bmsID, uint8_t* voltage);

/**
 * @brief AMS Cell Temperature Shutdown Message
 */
typedef struct AMS_CellTemperatureShutdown_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[2]; /**< Data */
} AMS_CellTemperatureShutdown_t;

/**
 * @brief AMS Cell Temperature Shutdown Composer
 * @param cellNum The cell number relating to the temperature
 * @param bmsID The BMS ID
 * @param temperature The temperature of said cell
 * @return
 */
AMS_CellTemperatureShutdown_t Compose_AMS_CellTemperatureShutdown(uint8_t cellNum, uint8_t bmsID, uint8_t temperature);

/**
 * @brief AMS Cell Temperature Shutdown Parser
 * @param packet The AMS_CellTemperatureShutdown_t packet to parse
 * @param cellNum The cell number relating to the temperature
 * @param bmsID The BMS ID
 * @param temperature The temperature of said cell
 */
void Parse_AMS_CellTemperatureShutdown(uint8_t* data, uint8_t* cellNum, uint8_t* bmsID, uint8_t* temperature);

/**
 * @brief AMS Missing BMS Message
 */
typedef struct AMS_MissingBMS_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[2]; /**< Data */
} AMS_MissingBMS_t;

/**
 * @brief AMS Missing BMS Message Composer
 * @param data Array of bools denoting if each BMS is present
 * @return The composed AMS_MissingBMS_t packet
 */
AMS_MissingBMS_t Compose_AMS_MissingBMS(bool data[12]);

/**
 * @brief AMS Missing BMS Message Composer
 * @param packet The AMS_MissingBMS_t packet to parse
 * @param data The array containing the bools denoting if each BMS is present
 */
void Parse_AMS_MissingBMS(uint8_t *pdata, bool* data[12]);

/**
 * @brief AMS Heartbeat Request Message
 */
typedef struct AMS_HeartbeatRequest_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_HeartbeatRequest_t;

/**
 * @brief AMS Heartbeat Request Message Composer
 * @return The composed AMS_HeartbeatRequest_t packet
 */
AMS_HeartbeatRequest_t Compose_AMS_HeartbeatRequest();

/**
 * @brief AMS Heartbeat Response Message
 */
typedef struct AMS_HeartbeatResponse_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[5]; /**< Data */
} AMS_HeartbeatResponse_t;

/**
 * @brief AMS Heartbeat Response Composer
 * @param HVAn HVAn boolean state (0 = open, 1 = closed)
 * @param HVBn HVBn boolean state (0 = open, 1 = closed)
 * @param precharge precharge boolean state (0 = open, 1 = closed)
 * @param HVAp HVAp boolean state (0 = open, 1 = closed)
 * @param HVBp HVBp boolean state (0 = open, 1 = closed)
 * @param averageVoltage The average voltage across all BMSs
 * @param runtime The runtime of the AMS micro-controller
 * @return The composed AMS_HeartbeatResponse_t packet
 */
AMS_HeartbeatResponse_t Compose_AMS_HeartbeatResponse(bool initialised, bool HVAn, bool HVBn, bool precharge, bool HVAp, bool HVBp, uint16_t averageVoltage, uint16_t runtime);

/**
 * @brief AMS Heartbeat Response Parser
 * @param packet The AMS_HeatbeatResponse_t packet to parse
 * @param HVAn HVAn boolean state (0 = open, 1 = closed)
 * @param HVBn HVBn boolean state (0 = open, 1 = closed)
 * @param precharge precharge boolean state (0 = open, 1 = closed)
 * @param HVAp HVAp HVAp boolean state (0 = open, 1 = closed)
 * @param HVBp HVBp HVBp boolean state (0 = open, 1 = closed)
 * @param averageVoltage The average voltage across all BMSs
 * @param runtime The runtime of the AMS micro-controller
 */
void Parse_AMS_HeartbeatResponse(uint8_t* data, bool *initialised, bool* HVAn, bool* HVBn, bool* precharge, bool* HVAp, bool* HVBp, uint16_t* averageVoltage, uint16_t* runtime);

/**
 * @brief AMS Start Up Message
 */
typedef struct AMS_StartUp_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_StartUp_t;

/**
 * @brief AMS Start Up Message Composer
 * @return The composed AMS_StartUp_t packet
 */
AMS_StartUp_t Compose_AMS_StartUp();

/**
 * @brief AMS Reset Tractive Message
 */
typedef struct AMS_ResetTractive_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_ResetTractive_t;

/**
 * @brief AMS Reset Tractive Message Composer
 * @return The composed AMS_ResetTractive_t packet
 */
AMS_ResetTractive_t Compose_AMS_ResetTractive();

/**
 * @brief AMS Shutdown Message
 */
typedef struct AMS_Shutdown_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_Shutdown_t;

/**
 * @brief AMS Shutdown Message Composer
 * @return The composed AMS_Shutdown_t packet
 */
AMS_Shutdown_t Compose_AMS_Shutdown();

/**
 * @brief AMS Request Temperature Message
 */
typedef struct AMS_RequestTemperature_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_RequestTemperature_t;

/**
 * @brief AMS Request Temperature Message Composer
 * @return The composed AMS_RequestTemperature_t packet
 */
AMS_RequestTemperature_t Compose_AMS_RequestTemperature();

/**
 * @brief AMS Transmit Temperature Message
 */
typedef struct AMS_TransmitTemperature_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[1]; /**< Data */
} AMS_TransmitTemperature_t;

/**
 * @brief AMS Transmit Temperature Message Composer
 * @param temperature The temperature to transmit
 * @return The composed AMS_TransmitTemperature_t packet
 */
AMS_TransmitTemperature_t Compose_AMS_TransmitTemperature(uint8_t temperature);

/**
 * @brief AMS Transmit Temperature Message Parser
 * @param packet The AMS_TransmitTemperature_t packet to parse
 * @param temperature The temperature
 */
void Parse_AMS_TransmitTemperature(uint8_t* data, uint8_t* temperature);

/**
 * @brief AMS Request Charge State
 */
typedef struct AMS_RequestChargeState_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_RequestChargeState_t;

/**
 * @brief AMS Request Charge State Message Composer
 * @return The composed AMS_RequestChargeState_t packet
 */
AMS_RequestChargeState_t Compose_AMS_RequestChargeState();

/**
 * @brief AMS Transmit Charge State
 */
typedef struct AMS_TransmitChargeState_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[2]; /**< Data */
} AMS_TransmitChargeState_t;

/**
 * @brief AMS Transmit Charge State Message Composer
 * @param chargeState The charge state
 * @return The composed AMS_TransmitChargeState_t packet
 */
AMS_TransmitChargeState_t Compose_AMS_TransmitChargeState(uint16_t chargeState);

/**
 * @brief AMS Transmit Charge State Parser
 * @param packet The AMS_TransmitCHargeState_t packet to parse
 * @param chargeState The charge state
 */
void Parse_AMS_TransmitChargeState(uint8_t* data, uint16_t* chargeState);

/**
 * @brief AMS Ready Message
 */
typedef struct AMS_Ready_t
{
	uint32_t id; /**< CAN Packet ID */
} AMS_Ready_t;

/**
 * @brief AMS Ready Message Composer
 * @return The composed AMS_Ready_t packet
 */
AMS_Ready_t Compose_AMS_Ready();

typedef struct AMS_ShutdownState {
	uint32_t id;
	uint8_t data[1];
} AMS_ShutdownState_t;

AMS_ShutdownState_t Compose_AMS_ShutdownState(uint8_t status);
void Parse_AMS_ShutdownState(uint8_t *data, uint8_t *status);

#endif /* INC_AMS_CAN_MESSAGES_H_ */
