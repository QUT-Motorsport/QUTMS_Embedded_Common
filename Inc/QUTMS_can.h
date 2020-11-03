/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUTMS_can_H
#define QUTMS_can_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "can.h"

// defines
#define CAN_SRC_ID_AMS 0x10
#define CAN_SRC_ID_BMS 0x12

#define CAN_MASK_SRC_ID 0x1FF << 18

// functions

uint32_t Compose_CANId(uint8_t priority, uint16_t sourceId, uint8_t autonomous, uint8_t type, uint16_t extra, uint8_t BMSId);
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceId, uint8_t* autonomous, uint8_t* type, uint16_t* extra, uint8_t* BMSId);

typedef struct CAN_MSG_Generic {
	CAN_RxHeaderTypeDef header;
	uint8_t data[8];
	void *hcan;
} CAN_MSG_Generic_t;

#ifdef __cplusplus
}
#endif
#endif /* QUTMS_can_H */

