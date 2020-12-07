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
#define CAN_PRIORITY_ERROR 0x0
#define CAN_PRIORITY_HEARTBEAT 0x1
#define CAN_PRIORITY_NORMAL 0x2
#define CAN_PRIORITY_DEBUG 0x3

#define CAN_SRC_ID_AMS 0x10
#define CAN_SRC_ID_BMS 0x12
#define CAN_SRC_ID_PDM 0x14
#define CAN_SRC_ID_CC 0x16

#define CAN_TYPE_ERROR 0x0
#define CAN_TYPE_HEARTBEAT 0x1
#define CAN_TYPE_RECEIVE 0x2
#define CAN_TYPE_TRANSMIT 0x3
#define CAN_TYPE_STREAM 0x7

#define DRIVER 0x00
#define DRIVERLESS 0x01


#define CAN_MASK_SRC_ID 0x1FF << 18

// functions

#define Compose_CANId(priority, sourceId, autonomous, type, extra, BMSId)(\
		(((priority) & 0x3) << 27 \
				| ((sourceId) & 0x1FF) << 18 \
				| ((autonomous) & 0x1) << 17 \
				| ((type) & 0x7) << 14 \
				| ((extra) & 0x3FF) << 4 \
				| ((BMSId) & 0xF)))

enum CAN_MSG_IDs {
	/** AMS */
#ifdef QUTMS_CAN_AMS
	AMS_CellVoltageShutdown_ID 		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x0, 0x0, 0x0),
	AMS_CellTemperatureShutdown_ID 	= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x0, 0x1, 0x0),
	AMS_MissingBMS_ID 				= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x0, 0x2, 0x0),
	AMS_HeartbeatRequest_ID 		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x1, 0x0, 0x0),
	AMS_HeartbeatResponse_ID 		= Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_AMS, DRIVER, 0x1, 0x01, 0x0),
	AMS_StartUp_ID					= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x2, 0x0, 0x0),
	AMS_ResetTractive_ID			= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x2, 0x1, 0x0),
	AMS_Shutdown_ID 				= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x2, 0x2, 0x0),
	AMS_RequestTemperature_ID 		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x2, 0x3, 0x0),
	AMS_TransmitTemperature_ID		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x3, 0x3, 0x0),
	AMS_RequestChargeState_ID 		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x2, 0x4, 0x0),
	AMS_TransmitChargeState_ID 		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x3, 0x4, 0x0),
	AMS_Ready_ID					= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_AMS, DRIVER, 0x3, 0x0, 0x0),
#endif

	/** BMS */
#ifdef QUTMS_CAN_BMS
	BMS_BadCellVoltage_ID 			= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, CAN_TYPE_ERROR, DRIVER, 0x00, 0x00),
	BMS_BadCellTemperature_ID		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, CAN_TYPE_ERROR, DRIVER, 0x01, 0x00),
	BMS_TransmitVoltage_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x02, 0x00),
	BMS_TransmitTemperature_ID 		= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x3, 0x00),
	BMS_ChargeEnabled_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_RECEIVE, 0x0, 0x00),
#endif

	/** CC */
#ifdef QUTMS_CAN_CC
	CC_ReadyToDrive_ID 				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, 0x0, 0x0, 0x0),
	CC_FatalShutdown_ID 			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, 0x0, 0x1, 0x0),
	CC_SoftShutdown_ID				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, 0x0, 0x1, 0x1),
#endif

	/** PDM */
#ifdef QUTMS_CAN_PDM
	PDM_InitiateStartup_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_RECEIVE, 0x00, 0x0),
	PDM_StartupOk_ID 				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_TRANSMIT, 0x00, 0x0),
	PDM_SelectStartup_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_TRANSMIT, 0x01, 0x0),
	PDM_SetChannelStates_ID 		= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_RECEIVE, 0x02, 0x0),
	PDM_Heartbeat_ID				= Compose_CANId(CAN_PRIORITY_HEARTBEAT, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_HEARTBEAT, 0x0, 0x0),
	PDM_RequestDutyCycle_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_RECEIVE, 0x3, 0x0),
	PDM_SetDutyCycle_ID 			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_RECEIVE, 0x4, 0x0),
	PDM_TransmitDutyCycle_ID		= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_PDM, DRIVER, CAN_TYPE_TRANSMIT, 0x4, 0x0),
#endif

};

//uint32_t Compose_CANId(uint8_t priority, uint16_t sourceId, uint8_t autonomous, uint8_t type, uint16_t extra, uint8_t BMSId);
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceId, uint8_t* autonomous, uint8_t* type, uint16_t* extra, uint8_t* BMSId);

typedef struct CAN_MSG_Generic
{
	CAN_RxHeaderTypeDef header;
	uint8_t data[8];
	void *hcan;
} CAN_MSG_Generic_t;

typedef struct CAN_LOG
{
	uint32_t id;
	uint8_t data[8];
}	CAN_LOG_t;

CAN_LOG_t Compose_CAN_LOG(uint8_t dataType, uint8_t dataLength, uint8_t* data);
void Parse_CAN_LOG(uint8_t *data, uint8_t *dataType, uint8_t* dataLength, uint8_t *rdata);

#ifdef __cplusplus
}
#endif
#endif /* QUTMS_can_H */

