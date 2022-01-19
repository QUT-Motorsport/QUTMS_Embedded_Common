/*
 * VESC_CAN_Messages.h
 *
 *  Created on: 5 Jul 2021
 *      Author: Thomas Fraser
 */

#ifndef COMMON_INC_CAN_VESC_H_
#define COMMON_INC_CAN_VESC_H_

#include <QUTMS_can.h>
#include "VESC_CAN_Datatypes.h"
#include <stdint.h>
#include <stddef.h>

void * sb(void *inp, size_t len);
void * sbo(void *inp, void *out, size_t len);

typedef struct VESC_SetDuty_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetDuty_t;

VESC_SetDuty_t Compose_VESC_SetDuty(VESC_ID id, float duty);

void Parse_VESC_SetDuty(uint8_t* data, float* duty);

typedef struct VESC_SetCurrent_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetCurrent_t;

VESC_SetCurrent_t Compose_VESC_SetCurrent(VESC_ID id, float current);

void Parse_VESC_SetCurrent(uint8_t* data, float* current);

typedef struct VESC_SetCurrentBrake_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetCurrentBrake_t;

VESC_SetCurrentBrake_t Compose_VESC_SetCurrentBrake(VESC_ID id, float currentBrake);

void Parse_VESC_SetCurrentBrake(uint8_t* data, float* currentBrake);

typedef struct VESC_SetRPM_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetRPM_t;

VESC_SetRPM_t Compose_VESC_SetRPM(VESC_ID id, int32_t rpm);

void Parse_VESC_SetRPM(uint8_t* data, int32_t* rpm);

typedef struct VESC_CANPacketStatus_t
{
	uint32_t id;
	uint8_t data[8];
} VESC_CANPacketStatus_t;

VESC_CANPacketStatus_t Compose_VESC_CANPacketStatus(VESC_ID id);

void Parse_VESC_CANPacketStatus(uint8_t* data, int32_t* rpm, float* current, float* duty);

typedef struct VESC_SetCurrentRel_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetCurrentRel_t;

VESC_SetCurrentRel_t Compose_VESC_SetCurrentRel(VESC_ID id, float currentRel);

void Parse_VESC_SetCurrentRel(uint8_t* data, float* currentRel);

typedef struct VESC_SetCurrentBrakeRel_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetCurrentBrakeRel_t;

VESC_SetCurrentBrakeRel_t Compose_VESC_SetCurrentBrakeRel(VESC_ID id, float currentBrakeRel);

void Parse_VESC_SetCurrentBrakeRel(uint8_t* data, float* currentBrakeRel);

typedef struct VESC_SetCurrentHandbrake_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetCurrentHandbrake_t;

VESC_SetCurrentHandbrake_t Compose_VESC_SetCurrentHandbrake(VESC_ID id, float currentHandbrake);

void Parse_VESC_SetCurrentHandbrake(uint8_t* data, float* currentHandbrake);

typedef struct VESC_SetCurrentHandbrakeRel_t
{
	uint32_t id;
	uint8_t data[4];
} VESC_SetCurrentHandbrakeRel_t;

VESC_SetCurrentHandbrakeRel_t Compose_VESC_SetCurrentHandbrakeRel(VESC_ID id, float currentHandbrakeRel);

void Parse_VESC_SetCurrentHandbrakeRel(uint8_t* data, float* currentHandbrakeRel);

typedef struct VESC_CANPacketStatus2_t
{
	uint32_t id;
	uint8_t data[8];
} VESC_CANPacketStatus2_t;

VESC_CANPacketStatus2_t Compose_VESC_CANPacketStatus2(VESC_ID id);

void Parse_VESC_CANPacketStatus2(uint8_t* data, float* ampHoursDrive, float* ampHoursRegen);

typedef struct VESC_CANPacketStatus3_t
{
	uint32_t id;
	int32_t wattHoursDrive;
	int32_t wattHoursRegen;
} VESC_CANPacketStatus3_t;

VESC_CANPacketStatus3_t Compose_VESC_CANPacketStatus3(VESC_ID id);

void Parse_VESC_CANPacketStatus3(uint8_t* data, float* wattHoursDrive, float* wattHoursRegen);

typedef struct VESC_CANPacketStatus4_t
{
	uint32_t id;
	int16_t mosfetTemperature;
	int16_t motorTemperature;
	int16_t inputCurrent;
	int16_t pidPos;
} VESC_CANPacketStatus4_t;

VESC_CANPacketStatus4_t Compose_VESC_CANPacketStatus4(VESC_ID id);

void Parse_VESC_CANPacketStatus4(uint8_t* data, float* mosfetTemperature, float* motorTemperature, float* inputCurrent, float* pidPos);

typedef struct VESC_Ping_t
{
	uint32_t id;
} VESC_Ping_t;

VESC_Ping_t Compose_VESC_Ping(VESC_ID id);

void Parse_VESC_Ping();

typedef struct VESC_Pong_t
{
	uint32_t id;
} VESC_Pong_t;

VESC_Pong_t Compose_VESC_Pong(VESC_ID id);

void Parse_VESC_Pong(uint8_t* data, VESC_ID* id);

typedef struct VESC_SetCurrentLimits_t
{
	uint32_t id;
	uint8_t data[8];
} VESC_SetCurrentLimits_t;

VESC_SetCurrentLimits_t Compose_VESC_SetCurrentLimits(VESC_ID id, float minCurrentLimit, float maxCurrentLimit);

void Parse_VESC_SetCurrentLimits(uint8_t* data, float* minCurrentLimit, float* maxCurrentLimit);

typedef struct VESC_SetCurrentLimitsEEPROM_t
{
	uint32_t id;
	uint8_t data[8];
} VESC_SetCurrentLimitsEEPROM_t;

VESC_SetCurrentLimitsEEPROM_t Compose_VESC_SetCurrentLimitsEEPROM(VESC_ID id, float minCurrentLimit, float maxCurrentLimit);

void Parse_VESC_SetCurrentLimitsEEPROM(uint8_t* data,float* minCurrentLimit, float* maxCurrentLimit);

typedef struct VESC_SetCurrentInLimits_t
{
	uint32_t id;
	uint8_t data[8];
} VESC_SetCurrentInLimits_t;

VESC_SetCurrentInLimits_t Compose_VESC_SetCurrentInLimits(VESC_ID id, float minCurrentInLimit, float maxCurrentInLimit);

void Parse_VESC_SetCurrentInLimits(uint8_t* data, float* minCurrentInLimit, float* maxCurrentInLimit);

typedef struct VESC_SetCurrentInLimitsEEPROM_t
{
	uint32_t id;
	uint8_t data[8];
} VESC_SetCurrentInLimitsEEPROM_t;

VESC_SetCurrentInLimitsEEPROM_t Compose_VESC_SetCurrentInLimitsEEPROM(VESC_ID id, float minCurrentInLimit, float maxCurrentInLimit);

void Parse_VESC_SetCurrentInLimitsEEPROM(uint8_t* data, float* minCurrentInLimit, float* maxCurrentInLimit);

typedef struct VESC_CANPacketStatus5_t
{
	uint32_t id;
	uint8_t data[8];

} VESC_CANPacketStatus5_t;

VESC_CANPacketStatus5_t Compose_VESC_CANPacketStatus5(VESC_ID id);

void Parse_VESC_CANPacketStatus5(uint8_t* data, int32_t* tachoRPM, float* inputVoltage, float* reserved);

typedef struct VESC_Shutdown_t
{
	uint32_t id;
} VESC_Shutdown_t;

VESC_Shutdown_t Compose_VESC_Shutdown(VESC_ID id);

typedef struct VESC_DetectApplyAllFOC_t
{
	uint32_t id;
	uint8_t data[6];
} VESC_DetectApplyAllFOC_t;

VESC_DetectApplyAllFOC_t Compose_VESC_DetectApplyAllFOC(VESC_ID id, uint8_t activeStatus, float maxPowerLoss);

void Parse_VESC_DetectApplyAllFOC(uint8_t* data);

typedef struct VESC_DetectApplyAllFOCRes_t
{
	uint32_t id;
	uint8_t data[1];
} VESC_DetectApplyAllFOCRes_t;

VESC_DetectApplyAllFOCRes_t Compose_VESC_DetectApplyAllFOCRes(VESC_ID id);

void Parse_VESC_DetectApplyAllFOCRes(uint8_t* data, int8_t* result);


#endif /* COMMON_INC_CAN_VESC_H_ */
