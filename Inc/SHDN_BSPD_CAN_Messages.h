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
 * @brief Shutdown BSPD Heartbeat Response Parser
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
 * @brief Shutdown BSPD Request Calibration Parser
 * @param calibration[2:0]
 * @param max
 * @param min
 */
void Parse_SHDN_BSPD_RequestCalibration(SHDN_BSPD_RequestCalibration_t packet, uint8_t* calibration, bool* min, bool* max);

/**
 * @brief Shutdown BSPD Set Calibration Message
 */
typedef struct SHDN_BSPD_SetCalibration_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[5]; /**< Data */
} SHDN_BSPD_SetCalibration_t;

/**
 * @brief Shutdown BSPD Set Calibration Composer
 * @param calibration[2:0]
 * @param max
 * @param min
 * @param calibrationMin
 * @param calibrationMax
 * @return The composed SHDN_BSPD_SetCalibration_t packet
 */
SHDN_BSPD_SetCalibration_t Compose_SHDN_BSPD_SetCalibration(uint8_t calibration, bool min, bool max, uint16_t calibrationMin, uint16_t calibrationMax);

/**
 * @brief Shutdown BSPD Set Calibration Parser
 * @param calibration[2:0]
 * @param max
 * @param min
 * @param calibrationMin
 * @param calibrationMax
 */
void Parse_SHDN_BSPD_SetCalibration(SHDN_BSPD_SetCalibration_t packet, uint8_t* calibration, bool* min, bool* max, uint16_t* calibrationMin, uint16_t* calibrationMax);

/**
 * @brief Shutdown BSPD Transmit Calibration Message
 */
typedef struct SHDN_BSPD_TransmitCalibration_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[5]; /**< Data */
} SHDN_BSPD_TransmitCalibration_t;

/**
 * @brief Shutdown BSPD Transmit Calibration Composer
 * @param calibration[2:0]
 * @param max
 * @param min
 * @param calibrationMin
 * @param calibrationMax
 * @return The composed SHDN_BSPD_SetCalibration_t packet
 */
SHDN_BSPD_TransmitCalibration_t Compose_SHDN_BSPD_TransmitCalibration(uint8_t calibration, bool min, bool max, uint16_t calibrationMin, uint16_t calibrationMax);

/**
 * @brief Shutdown BSPD Transmit Calibration Parser
 * @param calibration[2:0]
 * @param max
 * @param min
 * @param calibrationMin
 * @param calibrationMax
 */
void Parse_SHDN_BSPD_TransmitCalibration(SHDN_BSPD_TransmitCalibration_t packet, uint8_t* calibration, bool* min, bool* max, uint16_t* calibrationMin, uint16_t* calibrationMax);

/**
 * @brief Shutdown BSPD Request Values Message
 */
typedef struct SHDN_BSPD_RequestValues_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data; /**< Data */
} SHDN_BSPD_RequestValues_t;

/**
 * @brief Shutdown BSPD Request Values Composer
 * @param value[2:0]
 * @return The composed SHDN_BSPD_RequestValues_t packet
 */
SHDN_BSPD_RequestValues_t Compose_SHDN_BSPD_RequestValues(uint8_t value);

/**
 * @brief Shutdown BSPD Request Values Parser
 * @param value[2:0]
 */
void Parse_SHDN_BSPD_RequestValues(SHDN_BSPD_RequestValues_t packet, uint8_t* value);

/**
 * @brief Shutdown BSPD Transmit Values Message
 */
typedef struct SHDN_BSPD_TransmitValues_t
{
	uint32_t id; /**< CAN Packet ID */
	uint8_t data[3]; /**< Data */
} SHDN_BSPD_TransmitValues_t;

/**
 * @brief Shutdown BSPD Transmit Values Composer
 * @param selectedValue[2:0]
 * @return The composed SHDN_BSPD_TransmitValues_t packet
 */
SHDN_BSPD_TransmitValues_t Compose_SHDN_BSPD_TransmitValues(uint8_t selectValue, uint16_t outputValue);

/**
 * @brief Shutdown BSPD Transmit Values Parser
 * @param selectedValue[2:0]
 */
void Parse_SHDN_BSPD_TransmitValues(SHDN_BSPD_TransmitValues_t packet, uint8_t* selectValue, uint16_t* outputValue);

/**
 * @brief Shutdown BSPD Startup Ok Message
 */
typedef struct SHDN_BSPD_StartupOk_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_BSPD_StartupOk_t;

/**
 * @brief Shutdown BSPD Startup Ok Composer
 * @return The composed SHDN_BSPD_StartupOk_t packet
 */
SHDN_BSPD_StartupOk_t Compose_SHDN_BSPD_StartupOk(void);

/**
 * @brief Shutdown BSPD Reset Message
 */
typedef struct SHDN_BSPD_Reset_t
{
	uint32_t id; /**< CAN Packet ID */
} SHDN_BSPD_Reset_t;

/**
 * @brief Shutdown BSPD Reset Composer
 * @return The composed SHDN_BSPD_Reset_t packet
 */
SHDN_BSPD_Reset_t Compose_SHDN_BSPD_Reset(void);

#endif /* INC_SHDN_BSPD_CAN_MESSAGES_H_ */
