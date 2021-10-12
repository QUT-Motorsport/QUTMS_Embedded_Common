/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef QUTMS_can_H
#define QUTMS_can_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
//#include "can.h"
#ifdef QUTMS_CAN_VESC
#include "VESC_CAN_Datatypes.h"
#endif

// defines
#define CAN_PRIORITY_ERROR 0x0
#define CAN_PRIORITY_HEARTBEAT 0x1
#define CAN_PRIORITY_NORMAL 0x2
#define CAN_PRIORITY_DEBUG 0x3

#define CAN_SRC_ID_SHDN 0x06
#define CAN_SRC_ID_AMS 0x10
#define CAN_SRC_ID_BMS 0x12
#define CAN_SRC_ID_PDM 0x14
#define CAN_SRC_ID_CC 0x16
#define CAN_SRC_ID_GENERAL_SENSOR 0x18
#define CAN_SRC_ID_VCU 0x20
#define CAN_SRC_ID_DEBUG 0x22

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

#define Compose_VESCCANId(type, vescid)((((type) << 8) | ((vescid))))


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
	BMS_BadCellVoltage_ID 			= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_ERROR, 0x00, 0x00),
	BMS_BadCellTemperature_ID		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_ERROR, 0x01, 0x00),
	BMS_TransmitVoltage_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x02, 0x00),
	BMS_TransmitTemperature_ID 		= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x03, 0x00),
	BMS_ChargeEnabled_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_RECEIVE, 0x00, 0x00),
	BMS_Shutdown_ID					= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_RECEIVE, 0x01, 0x00),
	BMS_ShutdownAck_ID				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x01, 0x00),
	BMS_TransmitBalancing_ID		= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_BMS, DRIVER, CAN_TYPE_TRANSMIT, 0x04, 0x00),
#endif

	/** CC */
#ifdef QUTMS_CAN_CC
	CC_ReadyToDrive_ID 				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, CAN_TYPE_TRANSMIT, 0x0, 0x0),
	CC_FatalShutdown_ID 			= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_CC, DRIVER, CAN_TYPE_ERROR, 0x0, 0x0),
	CC_SoftShutdown_ID				= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_CC, DRIVER, CAN_TYPE_ERROR, 0x1, 0x0),
	CC_TransmitPedals_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, CAN_TYPE_TRANSMIT, 0x1, 0x0),
	CC_TransmitSteering_ID			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, CAN_TYPE_TRANSMIT, 0x2, 0x0),
	CC_OBJ_DICT_ID					= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_CC, DRIVER, CAN_TYPE_RECEIVE, 0x3, 0x0),
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

	// Shutdown
#ifdef QUTMS_CAN_SHDN
	SHDN_ShutdownTriggered_ID		= Compose_CANId(CAN_PRIORITY_ERROR, CAN_SRC_ID_SHDN, DRIVER, CAN_TYPE_ERROR, 0x0, 0x0),
#endif

	/** General Sensor */
#ifdef QUTMS_CAN_GENERAL_SENSOR
	GENERAL_SENSOR_LinearPot_ID		= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_GENERAL_SENSOR, DRIVER, CAN_TYPE_TRANSMIT, 0x00, 0x00),
	GENERAL_SENSOR_GearboxTemp_ID	= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_GENERAL_SENSOR, DRIVER, CAN_TYPE_TRANSMIT, 0x01, 0x00),
	GENERAL_SENSOR_RadiatorTemp_ID	= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_GENERAL_SENSOR, DRIVER, CAN_TYPE_TRANSMIT, 0x02, 0x00),
#endif

	// VCU
#ifdef QUTMS_VCU
	VCU_MotorTemp_ID 				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU, DRIVER, CAN_TYPE_TRANSMIT, 0x00, 0x00),
	VCU_IMU_Accel_ID 				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU, DRIVER, CAN_TYPE_TRANSMIT, 0x01, 0x00),
	VCU_IMU_Gyro_ID 				= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU, DRIVER, CAN_TYPE_TRANSMIT, 0x02, 0x00),
	VCU_LinearTravel_ID 			= Compose_CANId(CAN_PRIORITY_NORMAL, CAN_SRC_ID_VCU, DRIVER, CAN_TYPE_TRANSMIT, 0x03, 0x00),
#endif


	DEBUG_EnterState_ID				= Compose_CANId(CAN_PRIORITY_DEBUG, CAN_SRC_ID_DEBUG, DRIVER, CAN_TYPE_TRANSMIT, 0x00, 0x00),
	DEBUG_ExitState_ID				= Compose_CANId(CAN_PRIORITY_DEBUG, CAN_SRC_ID_DEBUG, DRIVER, CAN_TYPE_TRANSMIT, 0x01, 0x00),

#ifdef QUTMS_CAN_VESC
	VESC_SetDuty_ID					= Compose_VESCCANId(VESC_CAN_PACKET_SET_DUTY, 0),
	VESC_SetCurrent_ID				= Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT, 0),
	VESC_SetCurrentBrake_ID			= Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_BRAKE, 0),
	VESC_SetRPM_ID					= Compose_VESCCANId(VESC_CAN_PACKET_SET_RPM, 0),
	VESC_Status_1_ID				= Compose_VESCCANId(VESC_CAN_PACKET_STATUS, 0),
	VESC_SetCurrentRel_ID			= Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_REL, 0),
	VESC_SetCurrentBrakeRel_ID		= Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_BRAKE_REL, 0),
	VESC_SetCurrentHandbrake_ID		= Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_HANDBRAKE, 0),
	VESC_SetCurrentHandbrakeRel_ID	= Compose_VESCCANId(VESC_CAN_PACKET_SET_CURRENT_HANDBRAKE_REL, 0),
	VESC_Status_2_ID				= Compose_VESCCANId(VESC_CAN_PACKET_STATUS_2, 0),
	VESC_Status_3_ID				= Compose_VESCCANId(VESC_CAN_PACKET_STATUS_3, 0),
	VESC_Status_4_ID				= Compose_VESCCANId(VESC_CAN_PACKET_STATUS_4, 0),
	VESC_Ping_ID					= Compose_VESCCANId(VESC_CAN_PACKET_PING, 0),
	VESC_Pong_ID					= Compose_VESCCANId(VESC_CAN_PACKET_PONG, 0),
	VESC_SetCurrentLimits			= Compose_VESCCANId(VESC_CAN_PACKET_CONF_CURRENT_LIMITS, 0),
	VESC_SetCurrentLimitsEEPROM		= Compose_VESCCANId(VESC_CAN_PACKET_CONF_STORE_CURRENT_LIMITS, 0),
	VESC_SetCurrentInLimits			= Compose_VESCCANId(VESC_CAN_PACKET_CONF_CURRENT_LIMITS_IN, 0),
	VESC_SetCurrentInLimitsEEPROM	= Compose_VESCCANId(VESC_CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN, 0),
	VESC_Status_5_ID				= Compose_VESCCANId(VESC_CAN_PACKET_STATUS_5, 0),
	VESC_Shutdown_ID				= Compose_VESCCANId(VESC_CAN_PACKET_SHUTDOWN, 0),
#endif
};

//uint32_t Compose_CANId(uint8_t priority, uint16_t sourceId, uint8_t autonomous, uint8_t type, uint16_t extra, uint8_t BMSId);
void Parse_CANId(uint32_t CANId, uint8_t* priority, uint16_t* sourceId, uint8_t* autonomous, uint8_t* type, uint16_t* extra, uint8_t* BMSId);

typedef struct CAN_MSG_Generic
{
	uint32_t timestamp;
	uint32_t ID;
	uint8_t ID_TYPE;
	uint8_t DLC;
	uint8_t data[8];
	// optional pointer to a CAN handle
	void *hcan;
} CAN_MSG_Generic_t;

typedef struct CAN_LOG
{
	uint32_t id;
	uint8_t data[8];
} CAN_LOG_t;

CAN_LOG_t Compose_CAN_LOG(uint8_t dataType, uint8_t dataLength, uint8_t* data);
void Parse_CAN_LOG(uint8_t *data, uint8_t *dataType, uint8_t* dataLength, uint8_t *rdata);

#ifdef __cplusplus
}
#endif
#endif /* QUTMS_can_H */

