/**
 ******************************************************************************
 * @file PDM_CAN_Messages.c
 * @brief PDM CAN Messages
 ******************************************************************************
 */

#include "PDM_CAN_Messages.h"

PDM_InitiateStartup_t Compose_PDM_InitiateStartup(void)
{
	PDM_InitiateStartup_t p;
	p.id = Compose_CANId(0x2, 0x14, 0x0, 0x2, 0x00, 0x0);
	return p;
}

PDM_StartupOk_t Compose_PDM_StartupOk(uint32_t powerChannels)
{
	PDM_StartupOk_t packet;
	packet.id = Compose_CANId(0x2, 0x14, 0x0, 0x3, 0x00, 0x0);

	uint8_t d[4] = {0};
	for (int i=0; i<4 ;++i)
		d[i] = ((uint8_t*)&powerChannels)[3-i];

	for (int i=0; i<4 ;++i)
		packet.data[i] = (uint8_t)(d[i] & 0xFF);

	return packet;
}

void Parse_PDM_StartupOk(PDM_StartupOk_t packet, uint32_t* powerChannels)
{
	*powerChannels = (packet.data[0] << 24) + (packet.data[1] << 16) + (packet.data[2] << 8) + packet.data[3];
}

PDM_SelectStartup_t Compose_PDM_SelectStartup(uint32_t powerChannels)
{
	PDM_SelectStartup_t packet;
	packet.id = Compose_CANId(0x2, 0x14, 0x0, 0x2, 0x01, 0x0);

	uint8_t d[4] = {0};
	for (int i=0; i<4 ;++i)
		d[i] = ((uint8_t*)&powerChannels)[3-i];

	for (int i=0; i<4 ;++i)
		packet.data[i] = (uint8_t)(d[i] & 0xFF);

	return packet;
}

void Parse_PDM_SelectStartup(PDM_SelectStartup_t packet, uint32_t* powerChannels)
{
	*powerChannels = (packet.data[0] << 24) + (packet.data[1] << 16) + (packet.data[2] << 8) + packet.data[3];
}

PDM_SetChannelStates_t Compose_PDM_SetChannelStates(uint32_t powerChannels)
{
	PDM_SetChannelStates_t packet;
	packet.id = Compose_CANId(0x2, 0x14, 0x0, 0x2, 0x02, 0x0);

	uint8_t d[4] = {0};
	for (int i=0; i<4 ;++i)
		d[i] = ((uint8_t*)&powerChannels)[3-i];

	for (int i=0; i<4 ;++i)
		packet.data[i] = (uint8_t)(d[i] & 0xFF);

	return packet;
}

void Parse_PDM_SetChannelStates(PDM_SetChannelStates_t packet, uint32_t* powerChannels)
{
	*powerChannels = (packet.data[0] << 24) + (packet.data[1] << 16) + (packet.data[2] << 8) + packet.data[3];
}
