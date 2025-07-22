/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUTMS_can_H
#define QUTMS_can_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#ifdef QUTMS_CAN_VESC
#include "VESC_CAN_Datatypes.h"
#endif

/* defines */
// Priorities 
#define CAN_PRIORITY_ERROR 0x0
#define CAN_PRIORITY_HEARTBEAT 0x1
#define CAN_PRIORITY_NORMAL 0x2
#define CAN_PRIORITY_DEBUG 0x3

// sourceIDs (pcbs)
#define CAN_SRC_ID_VCU_FRONT 0x01
#define CAN_SRC_ID_ACM 0x02
#define CAN_SRC_ID_MISCO 0x03
#define CAN_SRC_ID_ROS 0x04
#define CAN_SRC_ID_BMU 0x05
#define CAN_SRC_ID_SHUTDOWN 0x06
#define CAN_SRC_ID_VCU_REAR 0x07
#define CAN_SRC_ID_SW 0x08
#define CAN_SRC_ID_CHRGCTRL 0x09

// Message Types
#define CAN_TYPE_ERROR 0x0
#define CAN_TYPE_RECEIVE 0x1
#define CAN_TYPE_TRANSMIT 0x2
#define CAN_TYPE_HEARTBEAT 0x3
#define CAN_TYPE_OBJ_DICT 0x4
#define CAN_TYPE_STREAM 0x7

// Vehicle Type
#define DRIVER 0x00
#define DRIVERLESS 0x01

// CAN Type
#define TYPE_MESSAGE_CANFD 0x01
#define TYPE_MESSAGE_CAN 0x00

//Change??
#define CAN_ID_BIT_SHIFT_TYPE (14)

//Change??
#define CAN_MASK_TYPE (0x7 << CAN_ID_BIT_SHIFT_TYPE)
#define CAN_MASK_SRC_ID 0x1FF << 18

//change??
#define RES_NODE_ID 0x011

/* functions */
// function to compose the canID
#define Compose_CANId(priority, sourceID, type, vehicle, CANtype, crypto, boardDependant)                \
    ((((priority)       & 0x7)   << 26) |                                                                \
     (((sourceID)       & 0x1F)  << 21) |                                                                \                                                              \
     (((type)           & 0x7)   << 18) |                                                               \
	 (((vehicle)        & 0x1)   << 17) |                                                             \
     (((CANtype)        & 0x1)   << 16) |                                                                \
     (((crypto)         & 0xF)   << 12) |                                                                \
     (((boardDependant) & 0xFFF) << 0))

//IDK NOTE
enum CAN_MSG_IDs {
	/* Front_VCU */
	#ifdef QUTMS_CAN_FRONT_VCU
		Front_VCU_Heartbeat_ID = Compose_CANId()
		Front_VCU_Pedals = Compose_CANId()
		Front_VCU_Steering_Sus = Compose_CANId()
		Front_VCU_Wheels = Compose_CANId()
		Front_VCU_Pitot = Compose_CANId()
		//do we need object dict
	#endif
	/* ACM */
	#ifdef QUTMS_CAN_ACM

	#endif
	/* MISCO */
	#ifdef QUTMS_CAN_MISCO

	#endif
	/* ROS */
	#ifdef QUTMS_CAN_ROS

	#endif
	/* BMU */
	#ifdef QUTMS_CAN_BMU

	#endif
	/* Shutdown */
	#ifdef QUTMS_CAN_Shutdown

	#endif
	/* Rear_VCU */
	#ifdef QUTMS_CAN_REAR_VCU
		Rear_VCU_Heartbeat = Compose_CANId()
		Rear_VCU_Wheels = Compose_CANId()
		Rear_VCU_Sus = Compose_CANId()
		Rear_VCU_Cooling = Compose_CANId()
		Rear_VCU_Fans = Compose_CANId()
	#endif
	/* SW */
	#ifdef QUTMS_CAN_SW

	#endif
	/* Charge Control */
	#ifdef QUTMS_CAN_ChrgControl

	#endif
};

/* CHANGE */
// uint32_t Compose_CANId(uint8_t priority, uint16_t sourceId, uint8_t autonomous, uint8_t type, uint16_t extra, uint8_t
// BMSId);
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceId, uint8_t* autonomous, uint8_t* type,
				 uint16_t* extra, uint8_t* BMSId);

typedef struct CAN_MSG_Generic {
	uint32_t timestamp;
	uint32_t ID;
	uint8_t ID_TYPE;
	uint8_t DLC;
	uint8_t data[8];
	// optional pointer to a CAN handle
	void* hcan;
} CAN_MSG_Generic_t;

typedef struct CAN_LOG {
	uint32_t id;
	uint8_t data[8];
} CAN_LOG_t;

CAN_LOG_t Compose_CAN_LOG(uint8_t dataType, uint8_t dataLength, uint8_t* data);
void Parse_CAN_LOG(uint8_t* data, uint8_t* dataType, uint8_t* dataLength, uint8_t* rdata);

#ifdef __cplusplus
}
#endif
#endif /* QUTMS_can_H */
