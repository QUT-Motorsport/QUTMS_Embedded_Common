/*
 * VCU_CAN_Messages.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#ifdef QUTMS_VCU

#include "VCU_CAN_Messages.h"

VCU_MotorTemp_t Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0,
		uint32_t temp1) {
	VCU_MotorTemp_t msg;
	msg.id = VCU_MotorTemp_ID | VCU_ID;

	msg.data[0] = (temp0 >> 0) & 0xFF;
	msg.data[1] = (temp0 >> 8) & 0xFF;
	msg.data[2] = (temp0 >> 16) & 0xFF;
	msg.data[3] = (temp0 >> 24) & 0xFF;
	msg.data[4] = (temp1 >> 0) & 0xFF;
	msg.data[5] = (temp1 >> 8) & 0xFF;
	msg.data[6] = (temp1 >> 16) & 0xFF;
	msg.data[7] = (temp1 >> 24) & 0xFF;

	return msg;
}

VCU_IMU_Accel_t Compose_VCU_IMU_Accel(uint8_t VCU_ID, uint16_t scale, int16_t x,
		int16_t y, int16_t z) {
	VCU_IMU_Accel_t msg;
	msg.id = VCU_IMU_Accel_ID | VCU_ID;

	msg.data[0] = (scale >> 8) & 0xFF;
	msg.data[1] = (scale >> 0) & 0xFF;
	msg.data[2] = (x >> 8) & 0xFF;
	msg.data[3] = (x >> 0) & 0xFF;
	msg.data[4] = (y >> 8) & 0xFF;
	msg.data[5] = (y >> 0) & 0xFF;
	msg.data[6] = (z >> 8) & 0xFF;
	msg.data[7] = (z >> 0) & 0xFF;

	return msg;
}

VCU_IMU_Gyro_t Compose_VCU_IMU_Gyro(uint8_t VCU_ID, uint16_t scale, int16_t x,
		int16_t y, int16_t z) {
	VCU_IMU_Gyro_t msg;
	msg.id = VCU_IMU_Gyro_ID | VCU_ID;

	msg.data[0] = (scale >> 8) & 0xFF;
	msg.data[1] = (scale >> 0) & 0xFF;
	msg.data[2] = (x >> 8) & 0xFF;
	msg.data[3] = (x >> 0) & 0xFF;
	msg.data[4] = (y >> 8) & 0xFF;
	msg.data[5] = (y >> 0) & 0xFF;
	msg.data[6] = (z >> 8) & 0xFF;
	msg.data[7] = (z >> 0) & 0xFF;

	return msg;
}

VCU_LinearTravel_t Compose_VCU_LinearTravel(uint8_t VCU_ID, bool front,
		uint16_t t0, uint16_t t1) {
	VCU_LinearTravel_t msg;
	msg.id = VCU_LinearTravel_ID | VCU_ID;

	// position
	msg.data[0] = front ? 0 : 1;

	// left
	msg.data[1] = (t0 >> 8) & 0xFF;
	msg.data[2] = (t0 >> 0) & 0xFF;

	// right
	msg.data[3] = (t1 >> 8) & 0xFF;
	msg.data[4] = (t1 >> 0) & 0xFF;

	return msg;
}

VCU_AirPressure_t Compose_VCU_AirPressure(uint8_t VCU_ID, uint16_t pressure_raw,
		int16_t pressure) {
	VCU_AirPressure_t msg;
	msg.id = VCU_AirPressure_ID | VCU_ID;

	msg.data[0] = (pressure_raw >> 8) & 0xFF;
	msg.data[1] = (pressure_raw >> 0) & 0xFF;
	msg.data[2] = (pressure >> 8) & 0xFF;
	msg.data[3] = (pressure >> 0) & 0xFF;

	return msg;
}

VCU_ShutdownSegments_t Compose_VCU_ShutdownSegments(uint8_t line0,
		uint8_t line1, uint8_t line2, uint8_t line3) {
	VCU_ShutdownSegments_t msg;
	msg.id = VCU_ShutdownSegments_ID;

	msg.data[0] = (line0 & 0xF) | ((line1 & 0xF) << 4);
	msg.data[1] = (line2 & 0xF) | ((line3 & 0xF) << 4);

	return msg;
}

void Parse_VCU_ShutdownSegments(uint8_t *data, uint8_t *line0, uint8_t *line1, uint8_t *line2, uint8_t *line3) {

	*line0 = data[0] & 0xF;
	*line1 = (data[0] >> 4) & 0xF;
	*line2 = data[1] & 0xF;
	*line3 = (data[1] >> 4) & 0xF;
}

#endif
