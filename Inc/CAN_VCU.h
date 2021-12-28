/*
 * CAN_VCU.h
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_CAN_VCU_H_
#define COMMON_INC_CAN_VCU_H_

#include <QUTMS_CAN.h>
#include <stdbool.h>

typedef struct VCU_MotorTemp
{
	uint32_t id;
	uint8_t data[8];
} VCU_MotorTemp_t;

VCU_MotorTemp_t Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0, uint32_t temp1);

typedef struct VCU_IMU_Accel
{
	uint32_t id;
	uint8_t data[8];
} VCU_IMU_Accel_t;

VCU_IMU_Accel_t Compose_VCU_IMU_Accel(uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z);

typedef struct VCU_IMU_Gyro
{
	uint32_t id;
	uint8_t data[8];
} VCU_IMU_Gyro_t;

VCU_IMU_Gyro_t Compose_VCU_IMU_Gyro(uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z);

typedef struct VCU_LinearTravel
{
	uint32_t id;
	uint8_t data[5];
} VCU_LinearTravel_t;

VCU_LinearTravel_t Compose_VCU_LinearTravel(uint8_t VCU_ID, bool front, uint16_t t0, uint16_t t1);

typedef struct VCU_AirPressure
{
	uint32_t id;
	uint8_t data[4];
} VCU_AirPressure_t;

VCU_AirPressure_t Compose_VCU_AirPressure(uint8_t VCU_ID, uint16_t pressure_raw, int16_t pressure);

typedef struct VCU_ShutdownStatus_t
{
	uint32_t id;
	uint8_t data[3];
} VCU_ShutdownStatus_t;

VCU_ShutdownStatus_t Compose_VCU_ShutdownStatus(uint8_t line0, uint8_t line1, uint8_t line2, uint8_t line3, bool status);
void Parse_VCU_ShutdownStatus(uint8_t *data, uint8_t *line0, uint8_t *line1, uint8_t *line2, uint8_t *line3, bool *status);

#endif /* COMMON_INC_CAN_VCU_H_ */
