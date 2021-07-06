/*
 * VESC_CAN_Messages.h
 *
 *  Created on: 5 Jul 2021
 *      Author: Thomas Fraser
 */

#include "main.h"
#include "VESC_CAN_Messages.h"

void * sb(void *inp, size_t len)
{
	unsigned int i;
	unsigned char *in=(unsigned char *)inp,tmp;

	for(i=0;i<len/2;i++) {
		tmp=*(in+i);
		*(in+i)=*(in+len-i-1);
		*(in+len-i-1)=tmp;
	}

	return inp;
}

// Flip Byte Order for VESC
void * sbo(void *inp, void *out, size_t len)
{
	unsigned int i;
	unsigned char *o=(unsigned char *)out;
	unsigned char *in=(unsigned char *)inp;

	for(i=0;i<len;i++) {
		*(o+len-i-1)=*(in+i);
	}

	return out;
}

VESC_SetDuty_t Compose_VESC_SetDuty(VESC_ID id, float duty)
{
	VESC_SetDuty_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_DUTY, id);

	duty *= 100000.f; // VESC Scaling

	p.data[0] = ((uint32_t)(duty)) & 0xFF;
	p.data[1] = ((uint32_t)(duty) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(duty) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(duty) >> 24) & 0xFF;

	sb(p.data, 4); // Swap Byte Order for VESC.

	return p;
}

void Parse_VESC_SetDuty(uint8_t* data, VESC_ID* id, float* duty)
{
	*duty = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(duty, 4);
	*duty /= 100000.f; // Undo VESC Scaling
}

VESC_SetCurrent_t Compose_VESC_SetCurrent(VESC_ID id, float current)
{
	VESC_SetCurrent_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT, id);

	current *= 1000.f; // VESC Scaling

	p.data[0] = ((uint32_t)(current)) & 0xFF;
	p.data[1] = ((uint32_t)(current) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(current) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(current) >> 24) & 0xFF;

	// Flipper da bytes
	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetCurrent(uint8_t* data, VESC_ID* id, float* current)
{
	*current = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(current, 4);
	*current /= 1000.f;
}

VESC_SetCurrentBrake_t Compose_VESC_SetCurrentBrake(VESC_ID id, float currentBrake)
{
	VESC_SetCurrentBrake_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_BRAKE, id);

	currentBrake *= 1000.f;

	p.data[0] = ((uint32_t)(currentBrake)) & 0xFF;
	p.data[1] = ((uint32_t)(currentBrake) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(currentBrake) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(currentBrake) >> 24) & 0xFF;

	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetCurrentBrake(uint8_t* data, VESC_ID* id, float* currentBrake)
{
	*currentBrake = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(currentBrake, 4);
	*currentBrake /= 1000.f;
}

VESC_SetRPM_t Compose_VESC_SetRPM(VESC_ID id, int32_t rpm)
{
	VESC_SetRPM_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_RPM, id);

	p.data[0] = rpm & 0xFF;
	p.data[1] = (rpm >> 8) & 0xFF;
	p.data[2] = (rpm >> 16) & 0xFF;
	p.data[3] = (rpm >> 24) & 0xFF;

	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetRPM(uint8_t* data, VESC_ID* id, int32_t* rpm)
{
	*rpm = (int32_t)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(rpm, 4);
}

VESC_CANPacketStatus_t Compose_VESC_CANPacketStatus(VESC_ID id)
{
	VESC_CANPacketStatus_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_STATUS, id);

	return p;
}

void Parse_VESC_CANPacketStatus(uint8_t* data, VESC_ID* id, int32_t* rpm, float* current, float* duty)
{
//	sb(data, 8);

	*rpm = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
	*current = (float)((data[4] << 8) | data[5]);
	*current /= 100.f;
	*duty = (float)((data[6] << 8) | data[7]);
	*duty /= 1000.f;
}

VESC_SetCurrentRel_t Compose_VESC_SetCurrentRel(VESC_ID id, float currentRel)
{
	VESC_SetCurrentRel_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_REL, id);

	currentRel *= 100000.f;

	p.data[0] = ((uint32_t)(currentRel)) & 0xFF;
	p.data[1] = ((uint32_t)(currentRel) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(currentRel) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(currentRel) >> 24) & 0xFF;

	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetCurrentRel(uint8_t* data, VESC_ID* id, float* currentRel)
{
	*currentRel = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(currentRel, 4);
}

VESC_SetCurrentBrakeRel_t Compose_VESC_SetCurrentBrakeRel(VESC_ID id, float currentBrakeRel)
{
	VESC_SetCurrentBrakeRel_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_BRAKE_REL, id);

	currentBrakeRel *= 100000.f;

	p.data[0] = ((uint32_t)(currentBrakeRel)) & 0xFF;
	p.data[1] = ((uint32_t)(currentBrakeRel) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(currentBrakeRel) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(currentBrakeRel) >> 24) & 0xFF;

	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetCurrentBrakeRel(uint8_t* data, VESC_ID* id, float* currentBrakeRel)
{
	*currentBrakeRel = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(currentBrakeRel, 4);
}

VESC_SetCurrentHandbrake_t Compose_VESC_SetCurrentHandbrake(VESC_ID id, float currentHandbrake)
{
	VESC_SetCurrentHandbrake_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_HANDBRAKE, id);

	currentHandbrake *= 1000.f;

	p.data[0] = ((uint32_t)(currentHandbrake)) & 0xFF;
	p.data[1] = ((uint32_t)(currentHandbrake) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(currentHandbrake) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(currentHandbrake) >> 24) & 0xFF;

	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetCurrentHandbrake(uint8_t* data, VESC_ID* id, float* currentHandbrake)
{
	*currentHandbrake = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(currentHandbrake, 4);
}

VESC_SetCurrentHandbrakeRel_t Compose_VESC_SetCurrentHandbrakeRel(VESC_ID id, float currentHandbrakeRel)
{
	VESC_SetCurrentHandbrakeRel_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_HANDBRAKE_REL, id);

	currentHandbrakeRel *= 100000.f;

	p.data[0] = ((uint32_t)(currentHandbrakeRel)) & 0xFF;
	p.data[1] = ((uint32_t)(currentHandbrakeRel) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(currentHandbrakeRel) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(currentHandbrakeRel) >> 24) & 0xFF;

	sb(p.data, 4);

	return p;
}

void Parse_VESC_SetCurrentHandbrakeRel(uint8_t* data, VESC_ID* id, float* currentHandbrakeRel)
{
	*currentHandbrakeRel = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
//	sb(currentHandbrakeRel, 4);
}

VESC_CANPacketStatus2_t Compose_VESC_CANPacketStatus2(VESC_ID id)
{
	VESC_CANPacketStatus2_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_STATUS_2, id);

	return p;
}

void Parse_VESC_CANPacketStatus2(uint8_t* data, VESC_ID* id, float* ampHoursDrive, float* ampHoursRegen)
{
//	sb(data, 8);

	*ampHoursDrive = (float)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
	*ampHoursDrive /= 10000.f;
	*ampHoursRegen = (float)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]);
	*ampHoursRegen /= 10000.f;
}

VESC_CANPacketStatus3_t Compose_VESC_CANPacketStatus3(VESC_ID id)
{
	VESC_CANPacketStatus3_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_STATUS_3, id);

	return p;
}

void Parse_VESC_CANPacketStatus3(uint8_t* data, VESC_ID* id, float* wattHoursDrive, float* wattHoursRegen)
{
//	sb(data, 8);

	*wattHoursDrive = (float)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
	*wattHoursDrive /= 10000.f;
	*wattHoursRegen = (float)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7]);
	*wattHoursRegen /= 10000.f;
}

VESC_CANPacketStatus4_t Compose_VESC_CANPacketStatus4(VESC_ID id)
{
	VESC_CANPacketStatus4_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_STATUS_4, id);

	return p;
}

void Parse_VESC_CANPacketStatus4(uint8_t* data, VESC_ID* id, float* mosfetTemperature, float* motorTemperature, float* inputCurrent, float* pidPos)
{
//	sb(data, 8);

	*mosfetTemperature = (float)((data[0] << 8) | data[1]);
	*mosfetTemperature /= 10;
	*motorTemperature = (float)((data[2] << 8) | data[3]);
	*motorTemperature /= 10;
	*inputCurrent = (float)((data[4] << 8) | data[5]);
	*inputCurrent /= 10;
	*pidPos = (float)((data[6] << 8) | data[7]);
	*pidPos /= 50;
}

VESC_Ping_t Compose_VESC_Ping(VESC_ID id)
{
	VESC_Ping_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_PING, id);

	return p;
}

void Parse_VESC_Ping(VESC_ID* id)
{
	return; //Hmm how I get ID?
}

VESC_Pong_t Compose_VESC_Pong(VESC_ID id)
{
	VESC_Pong_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_PONG, id);

	return p;
}

void Parse_VESC_Pong(uint8_t* data, VESC_ID* id)
{
	*id = data[0];
}

VESC_SetCurrentLimits_t Compose_VESC_SetCurrentLimits(VESC_ID id, float minCurrentLimit, float maxCurrentLimit)
{
	VESC_SetCurrentLimits_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_CONF_CURRENT_LIMITS, id);

	minCurrentLimit *= 1000.f;
	maxCurrentLimit *= 1000.f;

	p.data[0] = ((uint32_t)(minCurrentLimit)) & 0xFF;
	p.data[1] = ((uint32_t)(minCurrentLimit) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(minCurrentLimit) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(minCurrentLimit) >> 24) & 0xFF;

	p.data[4] = ((uint32_t)(maxCurrentLimit)) & 0xFF;
	p.data[5] = ((uint32_t)(maxCurrentLimit) >> 8) & 0xFF;
	p.data[6] = ((uint32_t)(maxCurrentLimit) >> 16) & 0xFF;
	p.data[7] = ((uint32_t)(maxCurrentLimit) >> 24) & 0xFF;

	sb(p.data, 8);

	return p;
}

void Parse_VESC_SetCurrentLimits(uint8_t* data, VESC_ID* id, float* minCurrentLimit, float* maxCurrentLimit)
{
//	sb(data, 8);
	*minCurrentLimit = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
	*maxCurrentLimit = (float)((data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4]);

}

VESC_SetCurrentLimitsEEPROM_t Compose_VESC_SetCurrentLimitsEEPROM(VESC_ID id, float minCurrentLimit, float maxCurrentLimit)
{
	VESC_SetCurrentLimitsEEPROM_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_CONF_STORE_CURRENT_LIMITS, id);

	minCurrentLimit *= 1000.f;
	maxCurrentLimit *= 1000.f;

	p.data[0] = ((uint32_t)(minCurrentLimit)) & 0xFF;
	p.data[1] = ((uint32_t)(minCurrentLimit) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(minCurrentLimit) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(minCurrentLimit) >> 24) & 0xFF;

	p.data[4] = ((uint32_t)(maxCurrentLimit)) & 0xFF;
	p.data[5] = ((uint32_t)(maxCurrentLimit) >> 8) & 0xFF;
	p.data[6] = ((uint32_t)(maxCurrentLimit) >> 16) & 0xFF;
	p.data[7] = ((uint32_t)(maxCurrentLimit) >> 24) & 0xFF;

	sb(p.data, 8);

	return p;
}

void Parse_VESC_SetCurrentLimitsEEPROM(uint8_t* data, VESC_ID* id, float* minCurrentLimit, float* maxCurrentLimit)
{
//	sb(data, 8);
	*minCurrentLimit = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
	*maxCurrentLimit = (float)((data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4]);
}

VESC_SetCurrentInLimits_t Compose_VESC_SetCurrentInLimits(VESC_ID id, float minCurrentInLimit, float maxCurrentInLimit)
{
	VESC_SetCurrentInLimits_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_CONF_CURRENT_LIMITS_IN, id);

	minCurrentInLimit *= 1000.f;
	maxCurrentInLimit *= 1000.f;

	p.data[0] = ((uint32_t)(minCurrentInLimit)) & 0xFF;
	p.data[1] = ((uint32_t)(minCurrentInLimit) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(minCurrentInLimit) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(minCurrentInLimit) >> 24) & 0xFF;

	p.data[4] = ((uint32_t)(maxCurrentInLimit)) & 0xFF;
	p.data[5] = ((uint32_t)(maxCurrentInLimit) >> 8) & 0xFF;
	p.data[6] = ((uint32_t)(maxCurrentInLimit) >> 16) & 0xFF;
	p.data[7] = ((uint32_t)(maxCurrentInLimit) >> 24) & 0xFF;

	sb(p.data, 8);

	return p;
}

void Parse_VESC_SetCurrentInLimits(uint8_t* data, VESC_ID* id, float* minCurrentInLimit, float* maxCurrentInLimit)
{
//	sb(data, 8);
	*minCurrentInLimit = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
	*maxCurrentInLimit = (float)((data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4]);
}

VESC_SetCurrentInLimitsEEPROM_t Compose_VESC_SetCurrentInLimitsEEPROM(VESC_ID id, float minCurrentInLimit, float maxCurrentInLimit)
{
	VESC_SetCurrentInLimitsEEPROM_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN, id);

	minCurrentInLimit *= 1000.f;
	maxCurrentInLimit *= 1000.f;

	p.data[0] = ((uint32_t)(minCurrentInLimit)) & 0xFF;
	p.data[1] = ((uint32_t)(minCurrentInLimit) >> 8) & 0xFF;
	p.data[2] = ((uint32_t)(minCurrentInLimit) >> 16) & 0xFF;
	p.data[3] = ((uint32_t)(minCurrentInLimit) >> 24) & 0xFF;

	p.data[4] = ((uint32_t)(maxCurrentInLimit)) & 0xFF;
	p.data[5] = ((uint32_t)(maxCurrentInLimit) >> 8) & 0xFF;
	p.data[6] = ((uint32_t)(maxCurrentInLimit) >> 16) & 0xFF;
	p.data[7] = ((uint32_t)(maxCurrentInLimit) >> 24) & 0xFF;

	sb(p.data, 8);

	return p;
}

void Parse_VESC_SetCurrentInLimitsEEPROM(uint8_t* data, VESC_ID* id, float* minCurrentInLimit, float* maxCurrentInLimit)
{
//	sb(data, 8);
	*minCurrentInLimit = (float)((data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0]);
	*maxCurrentInLimit = (float)((data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4]);
}

VESC_CANPacketStatus5_t Compose_VESC_CANPacketStatus5(VESC_ID id)
{
	VESC_CANPacketStatus5_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_STATUS_5, id);

	return p;
}

void Parse_VESC_CANPacketStatus5(uint8_t* data, VESC_ID* id, int32_t* tachoRPM, float* inputVoltage, float* reserved)
{
//	sb(data, 8);
	*tachoRPM = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
	*inputVoltage = (float)((data[4] << 8) | data[5]);
	*inputVoltage /= 10;
	*reserved = (float)((data[6] << 8) | data[7]);
}

VESC_Shutdown_t Compose_VESC_Shutdown(VESC_ID id)
{
	VESC_Shutdown_t p;
	p.id = Compose_VESCCANId(VESC_CAN_PACKET_SHUTDOWN, id);

	return p;
}

void Parse_VESC_Shutdown(VESC_ID* id)
{
	return; //Hmm how get ID?
}
