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
	p.id = Compose_CANId(0x2, 0x16, 0x0, 0x0, 0x0, 0x0);
	return p;
}

CC_FatalShutdown_t Compose_CC_FatalShutdown(void)
{
	CC_FatalShutdown_t p;
	p.id = Compose_CANId(0x2, 0x16, 0x0, 0x0, 0x1, 0x0);
	return p;
}

CC_SoftShutdown_t Compose_CC_SoftShutdown(void)
{
	CC_SoftShutdown_t p;
	p.id = Compose_CANId(0x2, 0x16, 0x0, 0x0, 0x1, 0x1);
	return p;
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

#endif
