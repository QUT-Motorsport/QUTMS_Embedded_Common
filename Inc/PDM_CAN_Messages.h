/**
 ******************************************************************************
 * @file PDM_CAN_Messages.h
 * @brief Power Distribution Module CAN Messages
 ******************************************************************************
 */

#ifndef INC_PDM_CAN_MESSAGES_H_
#define INC_PDM_CAN_MESSAGES_H_

#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>
#include <stdio.h>
#include "QUTMS_can.h"

/**
 * @brief PDM Initiate Startup Message
 */
typedef struct PDM_InitiateStartup_t
{
	uint32_t id; /**< CAN Packet ID */
} PDM_InitiateStartup_t;

/**
 * @brief PDM Initiate Startup Message Composer
 * @param void
 * @return The composed PDM_InitiateStartup_t packet
 */
PDM_InitiateStartup_t Compose_PDM_InitiateStartup(void);

/**
 * @brief PDM Startup Ok Message
 */
typedef struct PDM_StartupOk_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[4]; /**< Data */
} PDM_StartupOk_t;

/**
 * @brief PDM Startup Ok Message Composer
 * @param 32 bit string containing Boolean-like values of active power status at startup
 * @return The generated PDM_StartupOk_t packet
 */
PDM_StartupOk_t Compose_PDM_StartupOk(uint32_t powerChannels);

/**
 * @brief PDM Startup Ok Message Parser
 * @param packet The PDM_StartupOk_t packet to parse
 * @param 32 bit string containing Boolean-like values of active power status at startup
 */
void Parse_PDM_StartupOk(PDM_StartupOk_t packet, uint32_t* powerChannels);

/**
 * @brief PDM Select Channels for Startup Message
 */
typedef struct PDM_SelectStartup_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[4]; /**< Data */
} PDM_SelectStartup_t;

/**
 * @brief PDM Select Channels for Startup Message Composer
 * @param 32 bit string containing Boolean-like values to set power status to
 * @return The generated PDM_SelectStartup_t packet
 */
PDM_SelectStartup_t Compose_PDM_SelectStartup(uint32_t powerChannels);

/**
 * @brief PDM Select Channels for Startup Message Parser
 * @param packet The PDM_SelectStartup_t packet to parse
 * @param 32 bit string containing Boolean-like values power channels toggled to
 */
void Parse_PDM_SelectStartup(PDM_SelectStartup_t packet, uint32_t* powerChannels);

/**
 * @brief PDM Set Channel States Message
 */
typedef struct PDM_SetChannelStates_t
{
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[4]; /**< Data */
} PDM_SetChannelStates_t;

/**
 * @brief PDM Set Channel States Message Composer
 * @param 32 bit string containing Boolean-like values to set power status to
 * @return The generated PDM_SetChannelStates_t packet
 */
PDM_SetChannelStates_t Compose_PDM_SetChannelStates(uint32_t powerChannels);

/**
 * @brief PDM Set Channel States Message Parser
 * @param packet The PDM_SelectStartup_t packet to parse
 * @param 32 bit string containing Boolean-like values power channels toggled to
 */
void Parse_PDM_SetChannelStates(PDM_SetChannelStates_t packet, uint32_t* powerChannels);

#endif /* INC_PDM_CAN_MESSAGES_H_ */
