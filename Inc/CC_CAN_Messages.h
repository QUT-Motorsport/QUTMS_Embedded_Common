/**
 ******************************************************************************
 * @file CC_CAN_Messages.h
 * @brief Chassis Controller CAN Messages
 ******************************************************************************
 */

#ifndef INC_CC_CAN_MESSAGES_H_
#define INC_CC_CAN_MESSAGES_H_

#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>
#include "QUTMS_can.h"

/**
 * @brief Chassis Controller RTD Message
 */
typedef struct CC_ReadyToDrive_t
{
	uint32_t id; /**< CAN Packet ID */
} CC_ReadyToDrive_t;

/**
 * @brief Chassis Controller RTD Message Composer
 * @param void
 * @return The composed CC_ReadyToDrive_t packet
 */
CC_ReadyToDrive_t Compose_CC_ReadyToDrive(void);

/**
 * @brief Chassis Controller Fatal Shutdown Message
 */
typedef struct CC_FatalShutdown_t
{
	uint32_t id; /**< CAN Packet ID */
} CC_FatalShutdown_t;

/**
 * @brief Chassis Controller Fatal Shutdown Message Composer
 * @param void
 * @return The composed CC_FatalShutdown_t packet
 */
CC_FatalShutdown_t Compose_CC_FatalShutdown(void);

/**
 * @brief Chassis Controller Fatal Shutdown Message
 */
typedef struct CC_SoftShutdown_t
{
	uint32_t id; /**< CAN Packet ID */
} CC_SoftShutdown_t;

/**
 * @brief Chassis Controller Soft Shutdown Message Composer
 * @param void
 * @return The composed CC_SoftShutdown_t packet
 */
CC_SoftShutdown_t Compose_CC_SoftShutdown(void);


/**
 * @brief Chassis Controller Inverter Motor RPM Request Message
 */
typedef struct CC_RequestRPM_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[8]; /**< Data */
} CC_RequestRPM_t;

/**
 * @brief Chassis Controller Inverter Motor RPM Request Message Composer
 * @return The generated CC_RequestRPM_t packet
 */
CC_RequestRPM_t Compose_CC_RequestRPM(uint16_t nodeId);

/**
 * @brief Chassis Controller Inverter Motor RPM Request Message Parser
 * @param data The CC_RequestRPM_t packet data to parse
 * @param motorRPM Address of where MotorRPM can be stored
 */
void Parse_CC_RequestRPM(uint8_t* data, int16_t* motorRPM);

/**
 * @brief Chassis Controller Inverter Motor Command Message
 */
typedef struct CC_MotorCommand_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[8]; /**< Data */
} CC_MotorCommand_t;

/**
 * @brief Chassis Controller Inverter Motor Command Message Composer
 * @return The generated CC_MotorCommand_t packet
 */
CC_MotorCommand_t Compose_CC_MotorCommand(uint16_t nodeId, int32_t motorCommand, uint8_t motorId);

/**
 * @brief Chassis Controller Inverter Motor Command Message Parser
 * @param data The CC_MotorCommand_t packet data to parse
 * @param motorCommand The desired duty cycle
 */
void Parse_CC_MotorCommand(uint8_t* data, int32_t* motorCommand);


/**
 * @brief Chassis Controller Inverter Set Variable Command Message
 */
typedef struct CC_SetVariable_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[8]; /**< Data */
} CC_SetVariable_t;

/**
 * @brief Chassis Controller Inverter Set Variable Message Composer
 * @return The generated CC_SetVariable_t packet
 */
CC_SetVariable_t Compose_CC_SetVariable(uint16_t nodeId, uint8_t userVariable, int32_t userCommand);

/**
 * @brief Chassis Controller Inverter Set Variable Message Parser
 * @param data The CC_SetVariable_t packet data to parse
 * @param userCommand The desired user variable output pointer
 */
void Parse_CC_SetVariable(uint8_t* data, int32_t* userCommand);


/**
 * @brief Chassis Controller Inverter Set Bool Command Message
 */
typedef struct CC_SetBool_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[8]; /**< Data */
} CC_SetBool_t;

/**
 * @brief Chassis Controller Inverter Set Bool Message Composer
 * @return The generated CC_SetBool_t packet
 */
CC_SetBool_t Compose_CC_SetBool(uint16_t nodeId, uint8_t boolNum, uint32_t userBool);

/**
 * @brief Chassis Controller Inverter Set Bool Message Parser
 * @param data The CC_SetBool_t packet data to parse
 * @param userBool The desired user bool variable output pointer
 */
void Parse_CC_SetBool(uint8_t* data, int32_t* userBool);

/**
 * @brief Chassis Controller Inverter Emergency Shutdown Command Message
 */
typedef struct CC_ShutdownInverter_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[8]; /**< Data */
} CC_ShutdownInverter_t;

/**
 * @brief Chassis Controller Inverter Emergency Shutdown Command Message Composer
 * @return The generated CC_ShutdownInverter_t packet
 */
CC_ShutdownInverter_t Compose_CC_ShutdownInverter(uint16_t nodeId);


/**
 * @brief Chassis Controller Inverter Run Micro Basic Script Command Message
 */
typedef struct CC_RunMicroBasic_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[8]; /**< Data */
} CC_RunMicroBasic_t;

/**
 * @brief Chassis Controller Inverter Run Micro Basic Script Message Composer
 * @return The generated CC_SetBool_t packet
 */
CC_RunMicroBasic_t Compose_CC_RunMicroBasic(uint16_t nodeId);

/**
 * @brief Chassis Controller Inverter Run Micro Basic Script Message Parser
 * @param data The CC_RunMicroBasic_t packet data to parse
 */
void Parse_CC_RunMicroBasic(uint8_t* data);

/**
 * @brief Chassis Controller Inverter Emergency Shutdown Command Message Parser
 * @param data The CC_ShutdownInverter_t packet data to parse
 */
void Parse_CC_ShutdownInverter(uint8_t* data);

typedef struct CC_CanadaInverter /**< TODO Rename */
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[2];
} CC_CanadaInverter_t;

/**
 * @brief Chassis Controller Inverter 2 Compose DAC Value
 * @param DACValue A 0-4096 Value dictating brake and throttle values
 * @return The CC_CanadaInverter_t packet
 */
CC_CanadaInverter_t Compose_CC_CanadaInverter(uint16_t DACValue);

/**
 * @brief Chassis Controller Inverter 2 DAC Value Parser
 * @param data The CC_CanadaInverter_t packet data to parse
 */
void Parse_CC_CanadaInverter(uint8_t* data, uint16_t* DACValue);


#endif /* INC_CC_CAN_MESSAGES_H_ */
