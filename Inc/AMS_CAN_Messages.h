/**
 ******************************************************************************
 * @file AMS_CAN_Messages.h
 * @brief AMS CAN Messages
 ******************************************************************************
 */

#ifndef INC_AMS_CAN_MESSAGES_H_
#define INC_AMS_CAN_MESSAGES_H_

#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>

/**
 * @brief AMS Cell Voltage Shutdown Message
 */
typedef struct
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
void Parse_AMS_CellVoltageShutdown(AMS_CellVoltageShutdown_t packet, uint8_t* cellNum, uint8_t* bmsID, uint8_t* voltage);

/**
 * @brief AMS Cell Temperature Shutdown Message
 */
typedef struct
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
void Parse_AMS_CellTemperatureShutdown(AMS_CellTemperatureShutdown_t packet, uint8_t* cellNum, uint8_t* bmsID, uint8_t* temperature);

/**
 * @brief AMS Missing BMS Message
 */
typedef struct
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
void Parse_AMS_MissingBMS(AMS_MissingBMS_t packet, bool* data[12]);

/**
 * @brief AMS Heartbeat Request Message
 */
typedef struct
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
typedef struct
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
AMS_HeartbeatResponse_t Compose_AMS_HeartbeatResponse(bool HVAn, bool HVBn, bool precharge, bool HVAp, bool HVBp, uint16_t averageVoltage, uint16_t runtime);

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
void Parse_AMS_HeartbeatResponse(AMS_HeartbeatResponse_t packet, bool* HVAn, bool* HVBn, bool* precharge, bool* HVAp, bool* HVBp, uint16_t* averageVoltage, uint16_t* runtime);

/**
 * @brief AMS Start Up Message
 */
typedef struct
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
typedef struct
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
typedef struct
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
typedef struct
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
typedef struct
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
void Parse_AMS_TransmitTemperature(AMS_TransmitTemperature_t packet, uint8_t* temperature);

/**
 * @brief AMS Request Charge State
 */
typedef struct
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
typedef struct
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
void Parse_AMS_TransmitChargeState(AMS_TransmitChargeState_t packet, uint16_t* chargeState);

/**
 * @brief AMS Ready Message
 */
typedef struct
{
	uint32_t id; /**< CAN Packet ID */
} AMS_Ready_t;

/**
 * @brief AMS Ready Message Composer
 * @return The composed AMS_Ready_t packet
 */
AMS_Ready_t Compose_AMS_Ready();

#endif /* INC_AMS_CAN_MESSAGES_H_ */
