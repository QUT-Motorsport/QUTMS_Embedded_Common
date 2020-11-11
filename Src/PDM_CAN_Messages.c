/**
 ******************************************************************************
 * @file PDM_CAN_Messages.c
 * @brief PDM CAN Messages
 ******************************************************************************
 */

#ifdef QUTMS_CAN_PDM

#include "PDM_CAN_Messages.h"

PDM_InitiateStartup_t Compose_PDM_InitiateStartup(void) {
	PDM_InitiateStartup_t p;
	p.id = Compose_CANId(0x2, 0x14, 0x0, 0x2, 0x00, 0x0);
	return p;
}

PDM_StartupOk_t Compose_PDM_StartupOk(uint32_t powerChannels) {
	PDM_StartupOk_t packet;
	packet.id = Compose_CANId(0x2, 0x14, 0x0, 0x3, 0x00, 0x0);

	uint8_t d[4] = { 0 };
	for (int i = 0; i < 4; ++i)
		d[i] = ((uint8_t*) &powerChannels)[3 - i];

	for (int i = 0; i < 4; ++i)
		packet.data[i] = (uint8_t) (d[i] & 0xFF);

	return packet;
}

void Parse_PDM_StartupOk(PDM_StartupOk_t packet, uint32_t *powerChannels) {
	*powerChannels = (packet.data[0] << 24) + (packet.data[1] << 16)
			+ (packet.data[2] << 8) + packet.data[3];
}

PDM_SelectStartup_t Compose_PDM_SelectStartup(uint32_t powerChannels) {
	PDM_SelectStartup_t packet;
	packet.id = Compose_CANId(0x2, 0x14, 0x0, 0x2, 0x01, 0x0);

	uint8_t d[4] = { 0 };
	for (int i = 0; i < 4; ++i)
		d[i] = ((uint8_t*) &powerChannels)[3 - i];

	for (int i = 0; i < 4; ++i)
		packet.data[i] = (uint8_t) (d[i] & 0xFF);

	return packet;
}

void Parse_PDM_SelectStartup(PDM_SelectStartup_t packet,
		uint32_t *powerChannels) {
	*powerChannels = (packet.data[0] << 24) + (packet.data[1] << 16)
			+ (packet.data[2] << 8) + packet.data[3];
}

PDM_SetChannelStates_t Compose_PDM_SetChannelStates(uint32_t powerChannels) {
	PDM_SetChannelStates_t packet;
	packet.id = Compose_CANId(0x2, 0x14, 0x0, 0x2, 0x02, 0x0);

	uint8_t d[4] = { 0 };
	for (int i = 0; i < 4; ++i)
		d[i] = ((uint8_t*) &powerChannels)[3 - i];

	for (int i = 0; i < 4; ++i)
		packet.data[i] = (uint8_t) (d[i] & 0xFF);

	return packet;
}

void Parse_PDM_SetChannelStates(PDM_SetChannelStates_t packet,
		uint32_t *powerChannels) {
	*powerChannels = (packet.data[0] << 24) + (packet.data[1] << 16)
			+ (packet.data[2] << 8) + packet.data[3];
}

PDM_Heartbeat_t Compose_PDM_Heartbeat(uint8_t powerChannels[8]) {
	PDM_Heartbeat_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_PDM, 0x0,
			CAN_TYPE_HEARTBEAT, 0x0, 0x0);

	for (int i = 0; i < 4; i++) {
		packet.data[i] = powerChannels[2*i] | (powerChannels[2*i+1] << 4);
	}

	return packet;
}

void Parse_PDM_Heartbeat(PDM_Heartbeat_t packet, uint8_t powerChannels[8]) {
	for (int i = 0; i < 4; i++) {
		powerChannels[2*i] = packet.data[i] & 0xF;
		powerChannels[2*i + 1] = (packet.data[i] >> 4) & 0xF;
	}
}

#endif
