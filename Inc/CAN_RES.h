/*
 * CAN_RES.h
 *
 *  Created on: 26 Oct. 2022
 *      Author: Calvin
 */

#ifndef COMMON_INC_CAN_RES_H_
#define COMMON_INC_CAN_RES_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool sw_k2;
    bool bt_k3;
    bool estop;
    bool loss_of_signal_shutdown_notice;
    uint8_t radio_quality;
} RES_Status_t;

typedef struct RES_Heartbeat {
	uint32_t id;
	uint8_t data[8];
} RES_Heartbeat_t;

void Parse_RES_Heartbeat(uint8_t *data, RES_Status_t *status);

#endif /* COMMON_INC_CAN_RES_H_ */
