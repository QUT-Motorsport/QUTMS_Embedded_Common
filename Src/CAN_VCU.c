/*
 * CAN_VCU.c
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#include <CAN_VCU.h>

#ifdef QUTMS_CAN_VCU

VCU_Heartbeat_t Compose_VCU_Heartbeat(uint8_t id, VCU_HeartbeatState_t *state)
{
    VCU_Heartbeat_t msg;
    msg.id = VCU_Heartbeat_ID | id;

    msg.data[0] = state->stateID;
    msg.data[1] = state->coreFlags.rawMem;
    msg.data[2] = (state->otherFlags.rawMem) & 0xFF;
    msg.data[3] = (state->otherFlags.rawMem >> 8) & 0xFF;
    msg.data[4] = (state->VCU) & 0xFF;
    msg.data[5] = (state->VCU >> 8) & 0xFF;

    return msg;
}

VCU_GIT_Hash_t Compose_VCU_GIT_Hash(uint8_t id, char *hash, uint8_t dirty_flag)
{
    VCU_GIT_Hash_t msg;
    msg.id = VCU_GIT_Hash_ID | id;

    for (int i = 0; i < 8; i++)
    {
        msg.data[i] = hash[i];
    }

    msg.data[8] = dirty_flag;

    return msg;
}



void Parse_VCU_Heartbeat(const uint8_t *data, VCU_HeartbeatState_t *state)
{
    state->stateID = data[0];
    state->coreFlags.rawMem = data[1];
    state->otherFlags.rawMem = (data[2] | (data[3] << 8));
    state->VCU = (data[4] | (data[5] << 8));
}

VCU_RTD_t Compose_VCU_RTD()
{
    VCU_RTD_t msg;
    msg.id = VCU_RTD_ID;

    return msg;
}

VCU_MotorTemp_t
Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0, uint32_t temp1)
{
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

VCU_IMU_Accel_t Compose_VCU_IMU_Accel(
    uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z
)
{
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

VCU_IMU_Gyro_t Compose_VCU_IMU_Gyro(
    uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z
)
{
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

VCU_LinearTravel_t
Compose_VCU_LinearTravel(uint8_t VCU_ID, bool front, uint16_t t0, uint16_t t1)
{
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

VCU_AirPressure_t Compose_VCU_AirPressure(uint8_t VCU_ID, uint16_t pressure_raw)
{
    VCU_AirPressure_t msg;
    msg.id = VCU_AirPressure_ID | VCU_ID;

    msg.data[0] = (pressure_raw >> 8) & 0xFF;
    msg.data[1] = (pressure_raw >> 0) & 0xFF;

    return msg;
}

VCU_TransmitSteering_t Compose_VCU_TransmitSteering(
    int16_t steering0, int16_t steering1, uint16_t adc0, uint16_t adc1
)
{
    VCU_TransmitSteering_t msg;
    msg.id = VCU_TransmitSteering_ID;

    msg.data[0] = steering0 & 0xff;
    msg.data[1] = (steering0 >> 8) & 0xff;
    msg.data[2] = steering1 & 0xff;
    msg.data[3] = (steering1 >> 8) & 0xff;
    msg.data[4] = adc0 & 0xff;
    msg.data[5] = (adc0 >> 8) & 0xff;
    msg.data[6] = adc1 & 0xff;
    msg.data[7] = (adc1 >> 8) & 0xff;

    return msg;
}

void Parse_VCU_TransmitSteering(
    const uint8_t *data, int16_t *steering0, int16_t *steering1, uint16_t *adc0,
    uint16_t *adc1
)
{
    *steering0 = (data[1]) << 8 | data[0];
    *steering1 = (data[3]) << 8 | data[2];
    *adc0 = (data[5] << 8) | data[4];
    *adc1 = (data[7] << 8) | data[6];
}

VCU_ShutdownStatus_t Compose_VCU_ShutdownStatus(
    uint8_t line0, uint8_t line1, uint8_t line2, uint8_t line3, bool status
)
{
    VCU_ShutdownStatus_t msg;
    msg.id = VCU_ShutdownStatus_ID;

    msg.data[0] = (line0 & 0xF) | ((line1 & 0xF) << 4);
    msg.data[1] = (line2 & 0xF) | ((line3 & 0xF) << 4);
    msg.data[2] = status ? 1 : 0;

    return msg;
}

void Parse_VCU_ShutdownStatus(
    const uint8_t *data, uint8_t *line0, uint8_t *line1, uint8_t *line2,
    uint8_t *line3, bool *status
)
{
    *line0 = data[0] & 0xF;
    *line1 = (data[0] >> 4) & 0xF;
    *line2 = data[1] & 0xF;
    *line3 = (data[1] >> 4) & 0xF;
    *status = (data[2] == 1) ? true : false;
}

VCU_Pedal_Accel_t Compose_VCU_Pedal_Accel(
    uint16_t accel0, uint16_t accel1, uint16_t accel_adc0, uint16_t accel_adc1
)
{
    VCU_Pedal_Accel_t msg;
    msg.id = VCU_Pedal_Accel_ID;

    msg.data[0] = (accel0 >> 8) & 0xFF;
    msg.data[1] = (accel0 >> 0) & 0xFF;
    msg.data[2] = (accel1 >> 8) & 0xFF;
    msg.data[3] = (accel1 >> 0) & 0xFF;
    msg.data[4] = (accel_adc0 >> 8) & 0xFF;
    msg.data[5] = (accel_adc0 >> 0) & 0xFF;
    msg.data[6] = (accel_adc1 >> 8) & 0xFF;
    msg.data[7] = (accel_adc1 >> 0) & 0xFF;

    return msg;
}

void Parse_VCU_Pedal_Accel(
    const uint8_t *data, uint16_t *accel0, uint16_t *accel1
)
{
    *accel0 = (data[0] << 8) | data[1];
    *accel1 = (data[2] << 8) | data[3];
}

VCU_Pedal_Brake_t Compose_VCU_Pedal_Brake(
    uint16_t brake_adc0, uint16_t brake_adc1, int16_t brake_psi0,
    int16_t brake_psi1
)
{
    VCU_Pedal_Brake_t msg;
    msg.id = VCU_Pedal_Brake_ID;

    msg.data[0] = (brake_adc0 >> 8) & 0xFF;
    msg.data[1] = (brake_adc0 >> 0) & 0xFF;
    msg.data[2] = (brake_adc1 >> 8) & 0xFF;
    msg.data[3] = (brake_adc1 >> 0) & 0xFF;
    msg.data[4] = (brake_psi0 >> 8) & 0xFF;
    msg.data[5] = (brake_psi0 >> 0) & 0xFF;
    msg.data[6] = (brake_psi1 >> 8) & 0xFF;
    msg.data[7] = (brake_psi1 >> 0) & 0xFF;

    return msg;
}

void Parse_VCU_Pedal_Brake(
    const uint8_t *data, uint16_t *brake_adc0, uint16_t *brake_adc1,
    int16_t *brake_psi0, int16_t *brake_psi1
)
{
    *brake_adc0 = (data[0] << 8) | data[1];
    *brake_adc1 = (data[2] << 8) | data[3];
    *brake_psi0 = (data[4] << 8) | data[5];
    *brake_psi1 = (data[6] << 8) | data[7];
}

VCU_Temp_Gearbox_t Compose_VCU_Temp_Gearbox(
    uint8_t VCU_ID, uint16_t adc, uint16_t R, uint16_t temp
)
{
    VCU_Temp_Gearbox_t msg;
    msg.id = VCU_GearboxTemp_ID | VCU_ID;

    msg.data[0] = (adc >> 8) & 0xFF;
    msg.data[1] = (adc >> 0) & 0xFF;
    msg.data[2] = (R >> 8) & 0xFF;
    msg.data[3] = (R >> 0) & 0xFF;
    msg.data[4] = (temp >> 8) & 0xFF;
    msg.data[5] = (temp >> 0) & 0xFF;

    return msg;
}

VCU_Suspension_Rot_t Compose_VCU_Suspension_Rot(
    uint8_t VCU_ID, uint16_t adcL, uint16_t adcR, int16_t degL, int16_t degR
)
{
    VCU_Suspension_Rot_t msg;
    msg.id = VCU_Suspension_Rot_ID | VCU_ID;

    msg.data[0] = (adcL >> 8) & 0xFF;
    msg.data[1] = (adcL >> 0) & 0xFF;
    msg.data[2] = (adcR >> 8) & 0xFF;
    msg.data[3] = (adcR >> 0) & 0xFF;
    msg.data[4] = (degL >> 8) & 0xFF;
    msg.data[5] = (degL >> 0) & 0xFF;
    msg.data[6] = (degR >> 8) & 0xFF;
    msg.data[7] = (degR >> 0) & 0xFF;

    return msg;
}

VCU_Flow_Rate_t Compose_VCU_Flow_Rate(uint8_t VCU_ID, uint16_t lpm, uint16_t freq) {
	VCU_Flow_Rate_t msg;
	msg.id = VCU_Flow_Rate_ID | VCU_ID;

	msg.data[0] = (lpm >> 8) & 0xFF;
	msg.data[1] = (lpm >> 0) & 0xFF;
	msg.data[2] = (freq >> 8) & 0xFF;
	msg.data[3] = (freq >> 0) & 0xFF;
	msg.data[4] = 0;
	msg.data[5] = 0;
	msg.data[6] = 0;
	msg.data[7] = 0;

	return msg;
}

VCU_Wheel_Speed_t Compose_VCU_Wheel_Speed(uint16_t freq_fl, uint16_t freq_fr, uint16_t rpm_fl, uint16_t rpm_fr) {
	VCU_Wheel_Speed_t msg;
	msg.id = VCU_Wheel_Speed_ID;

	msg.data[0] = (freq_fl >> 8) & 0xFF;
	msg.data[1] = (freq_fl >> 0) & 0xFF;
	msg.data[2] = (freq_fr >> 8) & 0xFF;
	msg.data[3] = (freq_fr >> 0) & 0xFF;
	msg.data[4] = (rpm_fl >> 8) & 0xFF;
	msg.data[5] = (rpm_fl >> 0) & 0xFF;
	msg.data[6] = (rpm_fr >> 8) & 0xFF;
	msg.data[7] = (rpm_fr >> 0) & 0xFF;

	return msg;
}

VCU_OBJ_DICT_t Compose_VCU_OBJ_DICT(uint8_t VCU_ID, uint8_t data[8]) {
	VCU_OBJ_DICT_t msg;
	msg.id = VCU_OBJ_DICT_ID | VCU_ID;

    for (int i = 0; i < 8; i++)
    {
        msg.data[i] = data[i];
    }

    return msg;
}

void Parse_VCU_OBJ_DICT(
    const uint8_t *data, uint8_t *type, uint8_t *data_size, uint8_t *index,
    uint32_t *value
)
{
    *type = data[0];
    *data_size = data[1];
    *index = data[2];

    uint32_t output_value = 0;
    for (int i = 0; i < 4; i++)
    {
        output_value |= (data[3] << (i * 8));
    }

    *value = output_value;
}

#endif
