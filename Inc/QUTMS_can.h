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

/* DEFINES */
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

// CRYPTO
#define CAN_CRYPTO_NONE 0x00

//Change??
#define CAN_ID_BIT_SHIFT_TYPE (14)


//Change??
#define CAN_MASK_TYPE (0x7 << CAN_ID_BIT_SHIFT_TYPE)
#define CAN_MASK_SRC_ID 0x1FF << 18

//AV
#define RES_NODE_ID 0x011

/* functions */
// function to compose the canID
#define Compose_CANId(priority, sourceID, type, vehicle, CANtype, crypto, boardDependant)                \
    ((((priority)       & 0x7)   << 26) |                                                                \
     (((sourceID)       & 0x1F)  << 21) |                                                                \
     (((type)           & 0x7)   << 18) |                                                                \
	 (((vehicle)        & 0x1)   << 17) |                                                                \
     (((CANtype)        & 0x1)   << 16) |                                                                \
     (((crypto)         & 0xF)   << 12) |                                                                \
     (((boardDependant) & 0xFFF) << 0))

//MesssageIDs
enum CAN_MSG_IDs {
	/* Front_VCU */
	#ifdef QUTMS_CAN_FRONT_VCU
		Front_VCU_Heartbeat_ID = Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_HEARTBEAT, DRIVER, CAN_CRYPTO_NONE, 0x00),
		Front_VCU_RTD_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x01),
		Front_VCU_Pedals_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x02),
		Front_VCU_Steering_Sus_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x03),
		Front_VCU_Wheels_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x04),
		Front_VCU_Pitot_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x05),
		
		Front_VCU_ShutdownStatus_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_FRONT, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x00),
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
		BMU_Heartbeat_ID = Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_BMU, CAN_TYPE_HEARTBEAT, DRIVER, CAN_CRYPTO_NONE, 0x00),
		BMU_TransmitVoltage_CMU_0_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x01),
		BMU_TransmitVoltage_CMU_63_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x02),
		BMU_TransmitTemp_CMU_0_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x03),
		BMU_TransmitTemp_CMU_63_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x04),
		BMU_TransmitBalancing_CMU_0_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x05),
		BMU_TransmitBalancing_CMU_63_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x06),
		BMU_TransmitDieTemps_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x06),
		BMU_TransmitPackPower_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x07),
		BMU_TransmitPackInfo_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x08),
		BMU_TransmitPower_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x09),
		//do we need shutdown status?
		BMU_ShutdownStatus_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMU, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x00),
	#endif

	/* Shutdown */
	#ifdef QUTMS_CAN_SHUTDOWN
		SHUTDOWN_ShutdownTriggered_ID = Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_SHUTDOWN, CAN_TYPE_ERROR, DRIVER, CAN_CRYPTO_NONE, 0x00),
	#endif

	/* Rear_VCU */
	#ifdef QUTMS_CAN_REAR_VCU
		Rear_VCU_Heartbeat_ID = Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_VCU_REAR, CAN_TYPE_HEARTBEAT, DRIVER, CAN_CRYPTO_NONE, 0x00),
		Rear_VCU_Wheels_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_REAR, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x01),
		Rear_VCU_Sus_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_REAR, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x02),
		Rear_VCU_Cooling_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_REAR, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x03),
		Rear_VCU_Fans_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_REAR, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x04),

		Rear_VCU_ShutdownStatus_ID = Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU_REAR, CAN_TYPE_TRANSMIT, DRIVER, CAN_CRYPTO_NONE, 0x00),
	#endif

	/* SW */
	#ifdef QUTMS_CAN_SW
		
	#endif

	/* Charge Control */
	#ifdef QUTMS_CAN_CHRGCTRL
		CHRGCTRL_Heartbeat_ID = Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_CHRGCTRL, CAN_PRIORITY_HEARTBEAT, DRIVER, CAN_CRYPTO_NONE, 0x00),
	#endif
};

/* CHANGE */
// uint32_t Compose_CANId(uint8_t priority, uint16_t sourceId, uint8_t autonomous, uint8_t type, uint16_t extra, uint8_t
// BMSId);
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceID, uint8_t* type, uint8_t* vehicle, uint8_t* CANtype, uint16_t* crypto, uint16_t* boardDependant);

//leave i'm assuming?
typedef struct CAN_MSG_Generic {
	uint32_t timestamp;
	uint32_t ID;
	uint8_t ID_TYPE;
	uint8_t DLC;
	uint8_t data[8];
	// optional pointer to a CAN handle
	void* hcan;
} CAN_MSG_Generic_t;

// leave same??
typedef struct CAN_LOG {
	uint32_t id;
	uint8_t data[8];
} CAN_LOG_t;

// leave??
CAN_LOG_t Compose_CAN_LOG(uint8_t dataType, uint8_t dataLength, uint8_t* data);
void Parse_CAN_LOG(uint8_t* data, uint8_t* dataType, uint8_t* dataLength, uint8_t* rdata);

#ifdef __cplusplus
}
#endif
#endif /* QUTMS_can_H */
