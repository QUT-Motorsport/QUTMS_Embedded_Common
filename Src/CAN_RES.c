/*
 * CAN_RES.c
 *
 *  Created on: 26 Oct. 2022
 *      Author: Calvin
 */


#include <CAN_RES.h>

#ifdef QUTMS_CAN_RES

void Parse_RES_Heartbeat(uint8_t *data, RES_Status_t *status) {
    status->estop = !(data[0] & (1 << 0));                        // ESTOP = PDO 2000 Bit 0
    status->sw_k2 = data[0] & (1 << 1);                           // K2 = PDO 2000 Bit 1
    status->bt_k3 = data[0] & (1 << 2);                           // K3 = PDO 2000 Bit 2
    status->radio_quality = data[6];                              // Radio Quality = PDO 2006
    status->loss_of_signal_shutdown_notice = data[7] & (1 << 6);  // LoSSN = PDO 2007 Bi
}

RES_NMT_Boot_t Compose_RES_NMT_Boot(uint8_t msg_type) {
	RES_NMT_Boot_t msg = {};
	msg.id = 0x0;

	msg.data[0] = msg_type;
	msg.data[1] = RES_NODE_ID;

	return msg;
}

#endif
