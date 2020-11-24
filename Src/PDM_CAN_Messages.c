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
	p.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_RECEIVE, 0x00, 0x0);
	return p;
}

PDM_StartupOk_t Compose_PDM_StartupOk(uint32_t powerChannels) {
	PDM_StartupOk_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_TRANSMIT, 0x00, 0x0);

	for (int i = 0; i < 4; i++) {
		packet.data[i] = (powerChannels >> (i * 8)) & 0xFF;
	}

	return packet;
}

void Parse_PDM_StartupOk(uint8_t data[4], uint32_t *powerChannels) {
	*powerChannels = 0;
	for (int i = 0; i < 4; i++) {
		*powerChannels |= data[i] << (i * 8);
	}
}

PDM_SelectStartup_t Compose_PDM_SelectStartup(uint32_t powerChannels) {
	PDM_SelectStartup_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_TRANSMIT, 0x01, 0x0);

	for (int i = 0; i < 4; i++) {
		packet.data[i] = (powerChannels >> (i * 8)) & 0xFF;
	}

	return packet;
}

void Parse_PDM_SelectStartup(uint8_t data[4], uint32_t *powerChannels) {
	*powerChannels = 0;
	for (int i = 0; i < 4; i++) {
		*powerChannels |= data[i] << (i * 8);
	}
}

PDM_SetChannelStates_t Compose_PDM_SetChannelStates(uint32_t powerChannels) {
	PDM_SetChannelStates_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_RECEIVE, 0x02, 0x0);

	for (int i = 0; i < 4; i++) {
		packet.data[i] = (powerChannels >> (i * 8)) & 0xFF;
	}

	return packet;
}

void Parse_PDM_SetChannelStates(uint8_t data[4], uint32_t *powerChannels) {
	*powerChannels = 0;
	for (int i = 0; i < 4; i++) {
		*powerChannels |= data[i] << (i * 8);
	}
}

PDM_Heartbeat_t Compose_PDM_Heartbeat(uint32_t powerChannels) {
	PDM_Heartbeat_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_HEARTBEAT, 0x0, 0x0);

	for (int i = 0; i < 4; i++) {
		packet.data[i] = (powerChannels >> (i * 8)) & 0xFF;
	}

	return packet;
}

void Parse_PDM_Heartbeat(uint8_t data[4], uint32_t *powerChannels) {
	*powerChannels = 0;
	for (int i = 0; i < 4; i++) {
		*powerChannels |= data[i] << (i * 8);
	}
}

PDM_RequestDutyCycle_t Compose_PDM_RequestDutyCycle(uint8_t channel) {
	PDM_RequestDutyCycle_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_RECEIVE, 0x3, 0x0);

	packet.data[0] = (channel & 0b11111);

	return packet;
}

void Parse_PDM_RequestDutyCycle(uint8_t data[1], uint8_t *channel) {
	*channel = (data[0] & 0b11111);
}

PDM_SetDutyCycle_t Compose_PDM_SetDutyCycle(uint8_t channel, uint8_t duty_cycle) {
	PDM_SetDutyCycle_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_RECEIVE, 0x4, 0x0);

	packet.data[0] = (channel & 0b11111);
	packet.data[1] = duty_cycle;

	return packet;
}

void Parse_PDM_SetDutyCycle(uint8_t data[2], uint8_t *channel, uint8_t *duty_cycle) {
	*channel = (data[0] & 0b11111);
	*duty_cycle = data[1];
}

PDM_TransmitDutyCycle_t Compose_PDM_TransmitDutyCycle(uint8_t channel, uint8_t duty_cycle) {

	PDM_TransmitDutyCycle_t packet;
	packet.id = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, 0x0, CAN_TYPE_TRANSMIT, 0x4, 0x0);

	packet.data[0] = (channel & 0b11111);
	packet.data[1] = duty_cycle;

	return packet;

}

void Parse_PDM_TransmitDutyCycle(uint8_t data[2], uint8_t *channel, uint8_t *duty_cycle) {
	*channel = (data[0] & 0b11111);
	*duty_cycle = data[1];
}

#endif
