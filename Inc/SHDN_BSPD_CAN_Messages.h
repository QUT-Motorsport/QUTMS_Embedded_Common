/**
 ******************************************************************************
 * @file SHDN_BSPD_Messages.h
 * @brief Shutdown BSPD CAN Messages
 ******************************************************************************
 */

#ifndef INC_SHDN_BSPD_CAN_MESSAGES_H_
#define INC_SHDN_BSPD_CAN_MESSAGES_H_

#include "stdbool.h"
#include "main.h"
#include "can.h"
#include <stdlib.h>
#include "QUTMS_can.h"

/**
 * @brief Shutdown BSPD Fault Message
 */
typedef struct SHDN_BSPD_Fault_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_BSPD_Fault_t;

/**
 * @brief Shutdown BSPD Fault Message Composer
 * @return The composed SHDN_BSPD_Fault_t packet
 */
SHDN_BSPD_Fault_t Compose_SHDN_BSPD_Fault(void);

/**
 * @brief Shutdown BSPD Heartbeat Request Message
 */
typedef struct SHDN_BSPD_HeartbeatRequest_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_BSPD_HeartbeatRequest_t;

/**
 * @brief Shutdown BSPD Heartbeat Request Message Composer
 * @return The composed SHDN_BSPD_HeartbeatRequest_t packet
 */
SHDN_BSPD_HeartbeatRequest_t Compose_SHDN_BSPD_HeartbeatRequest(void);

/**
 * @brief Shutdown BSPD Heartbeat Response Message
 */
typedef struct SHDN_BSPD_HeartbeatResponse_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data; /**< Data */
} SHDN_BSPD_HeartbeatResponse_t;

/**
 * @brief Shutdown BSPD Heartbeat Response Composer
 * @param isShutdown
 * @param bspdError reports 5kwError[1:0]
 * @param brakeError reports brakeError[1:0]
 * @param brakePedal
 * @param fivekW
 * @param trig 500ms Trigger
 * @return The composed SHDN_BSPD_HeartbeatResponse_t packet
 */
SHDN_BSPD_HeartbeatResponse_t Compose_SHDN_BSPD_HeartbeatResponse(bool isShutdown, uint8_t bspdError, uint8_t brakeError, bool brakePedal, bool fivekW, bool trig);

/**
 * @brief Shutdown IMD Heartbeat Response Parser
 * @param isShutdown
 * @param bspdError reports 5kwError[1:0]
 * @param brakeError reports brakeError[1:0]
 * @param brakePedal
 * @param fivekW
 * @param trig 500ms Trigger
 */
void Parse_SHDN_BSPD_HeartbeatResponse(SHDN_BSPD_HeartbeatResponse_t packet, bool* isShutdown, uint8_t* bspdError, uint8_t* brakeError, bool* brakePedal, bool* fivekW, bool* trig);

/**
 * @brief Shutdown BSPD Request Calibration Message
 */
typedef struct SHDN_BSPD_RequestCalibration_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data; /**< Data */
} SHDN_BSPD_RequestCalibration_t;

/**
 * @brief Shutdown BSPD Request Calibration Composer
 * @param calibration[2:0]
 * @param max
 * @param min
 * @return The composed SHDN_BSPD_RequestCalibration_t packet
 */
SHDN_BSPD_RequestCalibration_t Compose_SHDN_BSPD_RequestCalibration(uint8_t calibration, bool min, bool max);

/**
 * @brief Shutdown IMD Heartbeat Response Parser
 * @param calibration[2:0]
 * @param max
 * @param min
 */
void Parse_SHDN_BSPD_RequestCalibration(SHDN_BSPD_RequestCalibration_t packet, uint8_t* calibration, bool* min, bool* max);


#endif /* INC_SHDN_BSPD_CAN_MESSAGES_H_ */
