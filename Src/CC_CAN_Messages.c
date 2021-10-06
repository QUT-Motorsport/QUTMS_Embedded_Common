/**
 ******************************************************************************
 * @file CC_CAN_Messages.c
 * @brief Chassis Controller CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_CC

#include "CC_CAN_Messages.h"

CC_ReadyToDrive_t Compose_CC_ReadyToDrive(void)
{
	CC_ReadyToDrive_t p;
	p.id = CC_ReadyToDrive_ID;
	return p;
}

CC_FatalShutdown_t Compose_CC_FatalShutdown(void)
{
	CC_FatalShutdown_t p;
	p.id = CC_FatalShutdown_ID;
	return p;
}

CC_SoftShutdown_t Compose_CC_SoftShutdown(void)
{
	CC_SoftShutdown_t p;
	p.id = CC_SoftShutdown_ID;
	return p;
}

CC_TransmitPedals_t Compose_CC_TransmitPedals(uint16_t accel0, uint16_t accel1, uint16_t brake) {
	CC_TransmitPedals_t msg;
	msg.id = CC_TransmitPedals_ID;
	msg.data[0] = accel0 & 0xff;
	msg.data[1] = (accel0 >> 8) & 0xff;
	msg.data[2] = accel1 & 0xff;
	msg.data[3] = (accel1 >> 8) & 0xff;
	msg.data[4] = brake & 0xff;
	msg.data[5] = (brake >> 8) & 0xff;

	return msg;
}
void Parse_CC_TransmitPedals(uint8_t* data, uint16_t *accel0, uint16_t *accel1, uint16_t *brake) {
	*accel0 = (data[1]) << 8 | data[0];
	*accel1 = (data[3]) << 8 | data[2];
	*brake = (data[5]) << 8 | data[4];
}

CC_TransmitSteering_t Compose_CC_TransmitSteering(uint16_t steering0, uint16_t steering1) {
	CC_TransmitSteering_t msg;
	msg.id = CC_TransmitSteering_ID;
	msg.data[0] = steering0 & 0xff;
	msg.data[1] = (steering0 >> 8) & 0xff;
	msg.data[2] = steering1 & 0xff;
	msg.data[3] = (steering1 >> 8) & 0xff;

	return msg;
}
void Parse_CC_TransmitSteering(uint8_t *data, uint16_t *steering0, uint16_t *steering1) {
	*steering0 = (data[1]) << 8 | data[0];
	*steering1 = (data[3]) << 8 | data[2];
}

CC_OBJ_DICT_t Compose_CC_OBJ_DICT(uint8_t data[8]) {
	CC_OBJ_DICT_t msg;
	msg.id = CC_OBJ_DICT_ID;

	for (int i = 0; i < 8; i++) {
		msg.data[i] = data[i];
	}

	return msg;
}
void Parse_CC_OBJ_DICT(uint8_t *data, uint8_t *type, uint8_t *data_size, uint8_t *index, uint32_t *value) {
	*type = data[0];
	*data_size = data[1];
	*index = data[2];

	uint32_t output_value = 0;
	for (int i = 0; i < 4; i++) {
		output_value |= (data[3] << (i*8));
	}

	*value = output_value;
}

CC_RequestRPM_t Compose_CC_RequestRPM(uint16_t nodeId)
{
	CC_RequestRPM_t p;
	uint16_t index = 0x210A;
	p.id = 0x600 + nodeId; // 0x600 for Query + Node ID Specifier
	p.data[0] = 0b01001100; // Client Command Specifier + Number of Bytes + xx
	p.data[1] = (uint8_t)index & 0xFF; // Index
	p.data[2] = (uint8_t)(index >> 8) & 0xFF; // Index
	p.data[3] = 0x01; // Subindex
	p.data[4] = 0x00; // Data
	p.data[5] = 0x00; // Data
	p.data[6] = 0x00; // Data
	p.data[7] = 0x00; // Data
	return p;
}

void Parse_CC_RequestRPM(uint8_t* data, int16_t* motorRPM)
{
	*motorRPM = data[5] << 8 | data[4];
}

CC_RunMicroBasic_t Compose_CC_RunMicroBasic(uint16_t nodeId)
{
	CC_RunMicroBasic_t p;
	uint16_t index = 0x2018;
	p.id = 0x600 + nodeId; // 0x600 for Query + Node ID Specifier
	p.data[0] = 0x2C; // Client Command Specifier + Number of Bytes + xx
	p.data[1] = (uint8_t)index & 0xFF; // Index
	p.data[2] = (uint8_t)(index >> 8) & 0xFF; // Index
	p.data[3] = 0x00; // Subindex
	p.data[4] = 0x00; // Data
	p.data[5] = 0x00; // Data
	p.data[6] = 0x00; // Data
	p.data[7] = 0x00; // Data
	return p;
}

void Parse_CC_RunMicroBasic(uint8_t* data)
{
	return;
}

CC_MotorCommand_t Compose_CC_MotorCommand(uint16_t nodeId, int32_t motorCommand, uint8_t motorId)
{
	CC_MotorCommand_t p;
	uint16_t index = 0x2000;
	p.id = 0x600 + nodeId; // 0x600 for Query + Node ID Specifier
	p.data[0] = 0b00100000; // Client Command Specifier + Number of Bytes + xx
	p.data[1] = (uint8_t)index & 0xFF; // Index
	p.data[2] = (uint8_t)(index >> 8) & 0xFF; // Index
	p.data[3] = motorId; // Subindex
	p.data[4] = (uint8_t)motorCommand & 0xFF; // Data
	p.data[5] = (uint8_t)(motorCommand >> 8) & 0xFF; // Data
	p.data[6] = (uint8_t)(motorCommand >> 16) & 0xFF; // Data
	p.data[7] = (uint8_t)(motorCommand >> 24) & 0xFF; // Data
	return p;
}

void Parse_CC_RequestCommand(uint8_t* data, int32_t* motorCommand)
{
	return;
}

CC_ShutdownInverter_t Compose_CC_ShutdownInverter(uint16_t nodeId)
{
	CC_ShutdownInverter_t p;
	uint16_t index = 0x200C;

	p.id = 0x600 + nodeId; // 0x600 for Query + Node ID Specifier
	p.data[0] = 0b00101100; // Client Command Specifier + Number of Bytes + xx
	p.data[1] = (uint8_t)index & 0xFF; // Index
	p.data[2] = (uint8_t)(index >> 8) & 0xFF; // Index
	p.data[3] = 0x00; // Subindex
	p.data[4] = 0x00; // Data
	p.data[5] = 0x00; // Data
	p.data[6] = 0x00; // Data
	p.data[7] = 0x00; // Data
	return p;
}

void Parse_CC_ShutdownInverter(uint8_t* data){
	return;
}

CC_SetVariable_t Compose_CC_SetVariable(uint16_t nodeId, uint8_t userVariable, int32_t userCommand)
{
	CC_SetVariable_t p;
	uint16_t index = 0x2005;
	p.id = 0x600 + nodeId; // 0x600 for Query + Node ID Specifier
	p.data[0] = 0b00100000; // Client Command Specifier + Number of Bytes + xx
	p.data[1] = (uint8_t)index & 0xFF; // Index
	p.data[2] = (uint8_t)(index >> 8) & 0xFF; // Index
	p.data[3] = userVariable; // Subindex
	p.data[4] = (uint8_t)userCommand & 0xFF; // Data
	p.data[5] = (uint8_t)(userCommand >> 8) & 0xFF; // Data
	p.data[6] = (uint8_t)(userCommand >> 16) & 0xFF; // Data
	p.data[7] = (uint8_t)(userCommand >> 24) & 0xFF; // Data
	return p;
}

void Parse_CC_SetVariable(uint8_t* data, int32_t* userCommand)
{
	return;
}

CC_SetBool_t Compose_CC_SetBool(uint16_t nodeId, uint8_t boolNum, uint32_t userBool)
{
	CC_SetBool_t p;
	uint16_t index = 0x2015;
	p.id = 0x600 + nodeId; // 0x600 for Query + Node ID Specifier
	p.data[0] = 0b00100000; // Client Command Specifier + Number of Bytes + xx
	p.data[1] = (uint8_t)index & 0xFF; // Index
	p.data[2] = (uint8_t)(index >> 8) & 0xFF; // Index
	p.data[3] = boolNum; // Subindex
	p.data[4] = (uint8_t)userBool & 0xFF; // Data
	p.data[5] = (uint8_t)(userBool >> 8) & 0xFF; // Data
	p.data[6] = (uint8_t)(userBool >> 16) & 0xFF; // Data
	p.data[7] = (uint8_t)(userBool >> 24) & 0xFF; // Data
	return p;
}

void Parse_CC_SetBool(uint8_t* data, int32_t* userBool)
{
	return;
}

CC_CanadaInverter_t Compose_CC_CanadaInverter(uint16_t DACValue)
{
	CC_CanadaInverter_t p;
	p.id = 0x01;
	p.data[0] = DACValue >> 8 & 0xFF;
	p.data[1] = DACValue & 0xFF;

	return p;
}

void Parse_CC_CanadaInverter(uint8_t* data, uint16_t* DACValue)
{
	*DACValue = (data[0] & 0xFF) << 8 | data[1];
}


CC_Roboteq_t Compose_Roboteq_CAN(uint16_t nodeID, uint8_t css, uint8_t n, uint16_t index, uint8_t subindex, uint32_t data) {
	CC_Roboteq_t msg;

	// 0x600 for command / query to inverter
	msg.id = 0x600 + nodeID;

	msg.data[0] = ((css & 0b111) << 4) | ((n & 0b11) << 2);
	msg.data[1] = (index & 0xFF);
	msg.data[2] = (index >> 8) & 0xFF;
	msg.data[3] = subindex;
	msg.data[4] = data & 0xff;
	msg.data[5] = (data >> 8) & 0xff;
	msg.data[6] = (data >> 16) & 0xff;
	msg.data[7] = (data >> 24) & 0xff;

	return msg;
}



#endif
