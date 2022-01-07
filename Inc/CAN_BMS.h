/**
 ******************************************************************************
 * @file BMS_CAN_Messages.h
 * @brief BMS CAN Messages
 ******************************************************************************
 */

#ifndef INC_BMS_CAN_MESSAGES_H_
#define INC_BMS_CAN_MESSAGES_H_

#include <QUTMS_CAN.h>
#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>

// 4 temperatures per BMS temperature CAN message
#define BMS_TEMP_PACK_COUNT 6

#define BMS_TEMP_COUNT 12

#define BMS_VOLT_PACK_COUNT 4
#define BMS_VOLT_COUNT 10

/**
 * @brief BMS Bad Cell Voltage Message
 */
typedef struct BMS_BadCellVoltage
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[2]; /**< Data */
} BMS_BadCellVoltage_t;

/**
 * @brief BMS Bad Cell Voltage Message Composer
 * @param BMSId The BMS ID
 * @param cellNumber The cell number relating to the voltage
 * @param voltage The voltage of said cell
 * @return The generated BMS_BadCellVoltage_t packet
 */
BMS_BadCellVoltage_t Compose_BMS_BadCellVoltage(uint8_t BMSId, uint8_t cellNumber, uint8_t voltage);

/**
 * @brief BMS Bad Cell Voltage Message Parser
 * @param packet The BMS_BadCellVoltage_t packet to parse
 * @param BMSId The BMS ID
 * @param cellNumber The cell number relating to the voltage
 * @param voltage The voltage of said cell
 */
void Parse_BMS_BadCellVoltage(uint8_t* data, uint8_t* BMSId, uint8_t* cellNumber, uint8_t* voltage);

/**
 * @brief BMS Bad Cell Temperature Message
 */
typedef struct BMS_BadCellTemperature
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[2]; /**< Data */
} BMS_BadCellTemperature_t;

/**
 * @brief BMS Bad Cell Temperature Message Composer
 * @param BMSId The BMS ID
 * @param cellNumber The Cell number relating to the temperature
 * @param temperature The temperature of said cell
 * @return The composed BadCellTemperature_t packet
 */
BMS_BadCellTemperature_t Compose_BMS_BadCellTemperature(uint8_t BMSId, uint8_t cellNumber, uint8_t temperature);

/**
 * @brief BMD Bad Cell Temperature Message Parser
 * @param packet The BMS_BadCellTemperature_t packet to parse
 * @param BMSId The BMS ID
 * @param cellNumber The Cell number relating to the temperature
 * @param temperature The temperature of said cell
 */
void Parse_BMS_BadCellTemperature(uint8_t* data, uint8_t* BMSId, uint8_t* cellNumber, uint8_t* temperature);

/**
 * @brief BMS Transmit Voltage Message
 */
typedef struct BMS_TransmitVoltage
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[8]; /**< Data */
} BMS_TransmitVoltage_t;

/**
 * @brief BMS Transmit Voltage Message Composer
 * @param BMSId The BMS ID
 * @param vMsgId The voltage message ID (0 or 1) as we send 2 packets with all voltages
 * @param voltages The voltages to send
 * @return The composed BMS_TransmitVoltage_t packet
 */
BMS_TransmitVoltage_t Compose_BMS_TransmitVoltage(uint8_t BMSId, uint8_t vMsgId, uint16_t voltages[BMS_VOLT_PACK_COUNT]);

/**
 * @brief BMS Transmit Voltage Message Parser
 * @param packet The BMS_TransmitVoltage_t packet to parse
 * @param BMSId The BMS ID
 * @param vMsgId The voltage message ID (0 or 1) as we send 2 packets with all voltages
 * @param voltages The voltages parsed from the packet
 */
void Parse_BMS_TransmitVoltage(uint8_t* data, uint8_t* vMsgId, uint16_t voltages[BMS_VOLT_PACK_COUNT]);

/**
 * @brief BMS Transmit Temperature Message
 */
typedef struct BMS_TransmitTemperature
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[7]; /**< Data */
} BMS_TransmitTemperature_t;

/**
 * @brief BMS Transmit Temperature Message Composer
 * @param BMSId The BMS ID
 * @param tMsgId The temperature message ID (0 or 1) as we send 2 packets with all temperatures
 * @param temperatures THe temperatures to send
 * @return The composed BMS_TransmitTemperatues_t packet
 */
BMS_TransmitTemperature_t Compose_BMS_TransmitTemperature(uint8_t BMSId, uint8_t tMsgId, uint8_t temperatures[BMS_TEMP_PACK_COUNT]);

/**
 * @brief BMS Transmit Temperature Message Parser
 * @param packet The BMS_TransmitTemperature_t packet to parse
 * @param BMSId The BMS ID
 * @param tMsgId The temperature message ID (0 or 1) as we send 2 packets with all temperatures
 * @param temperatures The temperatures parsed from the packet
 */
void Parse_BMS_TransmitTemperature(uint8_t* data, uint8_t* tMsgId, uint8_t temperatures[BMS_TEMP_PACK_COUNT]);

/**
 * @brief BMS Charge Enabled Message
 */
typedef struct BMS_ChargeEnabled
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[1];
} BMS_ChargeEnabled_t;

/**
 * @brief BMS Charge Enabled Message Composer
 * @param BMSId The BMS ID
 * @return The composed BMS_ChargeEnabled_t packet
 */
BMS_ChargeEnabled_t Compose_BMS_ChargeEnabled(uint8_t bms_count);

/**
 * @brief BMS Charge Enabled Message Parser
 * @param packet The BMS_ChargeEnabled_t packet to parse
 * @param BMSId The BMS ID
 */
void Parse_ChargeEnabled(uint32_t canId, uint8_t *data, uint8_t *bms_count);

/**
 * @brief BMS Shutdown Message
 */
typedef struct BMS_Shutdown
{
	uint32_t id;
} BMS_Shutdown_t;

/**
 * @brief BMS Shutdown Message Composer
 * @return The composed BMS_Shutdown_t packet
 */
BMS_Shutdown_t Compose_BMS_Shutdown();

/**
 * @brief BMS Shutdown Message
 */
typedef struct BMS_ShutdownAck
{
	uint32_t id;
	uint8_t data[1];
} BMS_ShutdownAck_t;

/**
 * @brief BMS Shutdown Acknowledged Message Composer
 * @param bmsId the ID of the BMS
 * @return The composed BMS_ShutdownAck_t packet
 */
BMS_ShutdownAck_t Compose_BMS_ShutdownAck(uint8_t bmsId);

/**
 * @brief BMS Shutdown Acknowledged Message Parser
 * @param packet The BMS_ShutdownAck_t packet to parse
 * @param BMSId The BMS ID
 */
void Parse_BMS_ShutdownAck(uint32_t canId, uint8_t *data, uint8_t *bmsId);




/**
 * @brief BMS Charge Enabled Message
 */
typedef struct BMS_TransmitBalancing
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[4];
} BMS_TransmitBalancing_t;

/**
 * @brief
 * @param BMSId The BMS ID
 * @return
 */
BMS_TransmitBalancing_t Compose_BMS_TransmitBalancing(uint8_t BMSId, uint16_t balancing_voltage, uint16_t balancing_state);

/**
 * @brief
 * @param packet
 * @param BMSId The BMS ID
 */
void Parse_TransmitBalancing(uint32_t canId, uint8_t* data, uint8_t* BMSId, uint16_t *balancing_voltage, uint16_t *balancing_state);

#endif /* INC_BMS_CAN_MESSAGES_H_ */
