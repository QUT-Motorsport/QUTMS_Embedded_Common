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

#define PDMFLAG_INVERTER_ISO_2		0x2
#define PDMFLAG_ACU_SHDN_CHN_IN		0x4
#define PDMFLAG_AMS_PWR				0x10
#define PDMFLAG_BRAKE_LIGHT			0x20
#define PDMFLAG_ACU_SHDN_PWR		0x40
#define PDMFLAG_ACU_FAN_1			0x80
#define PDMFLAG_REAR_SHDN_PWR		0x100
#define PDMFLAG_SHDN_CURRENT_PWR	0x200
#define PDMFLAG_IMD_DAUGHTER_PWR	0x400
#define PDMFLAG_IMD_BOARD_PWR		0x800
#define PDMFLAG_INVERTER_ISO_1		0x2000
#define PDMFLAG_SENDYNE_1			0x4000
#define PDMFLAG_STEER_WHEEL_PWR		0x10000
#define PDMFLAG_SENDYNE_2			0x20000
#define PDMFLAG_FRONT_SHDN_PWR_2	0x40000
#define PDMFLAG_ACU_FAN_2			0x80000
#define PDMFLAG_LEFT_PUMP			0x100000
#define PDMFLAG_FRONT_SHDN_PWR_1	0x200000
#define PDMFLAG_CC_PWR_1			0x400000
#define PDMFLAG_LEFT_SIDEPOD_FAN	0x800000
#define PDMFLAG_RIGHT_PUMP			0x1000000
#define PDMFLAG_CC_PWR_3			0x2000000
#define PDMFLAG_CC_PWR_2			0x4000000
#define PDMFLAG_RIGHT_SIDEPOD_FAN	0x8000000
#define PDMFLAG_BSPD_PWR			0x20000000
#define PDMFLAG_TSAL_CONNECT		0x40000000
#define PDMFLAG_FRONT_SHDN_SEG		0x80000000


//#define LV_STARTUP 0xB08D1F50
#define LV_STARTUP PDMFLAG_ACU_SHDN_PWR | PDMFLAG_AMS_PWR | PDMFLAG_IMD_DAUGHTER_PWR | PDMFLAG_IMD_BOARD_PWR | PDMFLAG_REAR_SHDN_PWR | PDMFLAG_SHDN_CURRENT_PWR | PDMFLAG_SENDYNE_1 | PDMFLAG_FRONT_SHDN_PWR_2 | PDMFLAG_STEER_WHEEL_PWR | PDMFLAG_SENDYNE_2 | PDMFLAG_FRONT_SHDN_PWR_1 | PDMFLAG_TSAL_CONNECT | PDMFLAG_FRONT_SHDN_SEG | PDMFLAG_BSPD_PWR
//#define HV_STARTUP 0x06628029
#define HV_STARTUP PDMFLAG_INVERTER_ISO_2 | PDMFLAG_ACU_FAN_1 | PDMFLAG_INVERTER_ISO_1 | PDMFLAG_ACU_FAN_2 | PDMFLAG_LEFT_SIDEPOD_FAN | PDMFLAG_LEFT_PUMP | PDMFLAG_RIGHT_SIDEPOD_FAN | PDMFLAG_RIGHT_PUMP
#define BRAKE_LIGHT_MASK PDMFLAG_BRAKE_LIGHT
#define PDM_POWER_CC_MASK PDMFLAG_CC_PWR_1 | PDMFLAG_CC_PWR_2 | PDMFLAG_CC_PWR_3

/**
 * @brief PDM Initiate Startup Message
 */
typedef struct PDM_InitiateStartup {
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
typedef struct PDM_StartupOk {
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
void Parse_PDM_StartupOk(uint8_t data[4], uint32_t *powerChannels);

/**
 * @brief PDM Select Channels for Startup Message
 */
typedef struct PDM_SelectStartup {
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
void Parse_PDM_SelectStartup(uint8_t data[4], uint32_t *powerChannels);

/**
 * @brief PDM Set Channel States Message
 */
typedef struct PDM_SetChannelStates {
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
void Parse_PDM_SetChannelStates(uint8_t data[4], uint32_t *powerChannels);

typedef struct PDM_Heartbeat {
	uint32_t id; /**< CAN Packet ID*/
	uint8_t data[4]; /**< Data */
} PDM_Heartbeat_t;

/**
 * @brief PDM Heartbeat Message Composer
 * @param 32 bit string containing Boolean-like values to set power status to
 * @return The generated PDM_Heartbeat_t packet
 */
PDM_Heartbeat_t Compose_PDM_Heartbeat(uint32_t powerChannels);

/**
 * @brief PDM Heartbeat Message Parser
 * @param packet The PDM_Heartbeat_t packet to parse
 * @param 32 bit string containing Boolean-like values power channels toggled to
 */
void Parse_PDM_Heartbeat(uint8_t data[4], uint32_t *powerChannels);

#endif /* INC_PDM_CAN_MESSAGES_H_ */
