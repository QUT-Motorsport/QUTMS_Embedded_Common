/*
 * CAN_VCU.h
 *
 *  Created on: Sep 22, 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_CAN_VCU_H_
#define COMMON_INC_CAN_VCU_H_

#include <QUTMS_can.h>
#include <stdbool.h>

#define VCU_ID_SHDN                      0
#define VCU_ID_CTRL                      1
#define VCU_ID_DASH                      2
#define VCU_ID_EBS                       3
#define VCU_ID_ASSI                      4
#define VCU_ID_EBS_BTN                   5
#define VCU_ID_ACCU                      6
#define VCU_ID_COOL_L                    7
#define VCU_ID_COOL_R                    8
#define VCU_ID_SENSOR                    9

#define VCU_OD_ID_CTRL_REGEN_MAX_CURRENT 0x00
#define VCU_OD_ID_CTRL_REGEN_DEADZONE    0x01

typedef enum
{
    VCU_STATE_START = 0x00,
    VCU_STATE_PERIPHERAL_INIT = 0x01,
    VCU_STATE_SENSOR_INIT = 0x02,
    VCU_STATE_BOARD_CHECK = 0x03,

    // CTRL VCU
    VCU_STATE_BMU_CHECK = 0x04,
    VCU_STATE_IDLE = 0x05,
    VCU_STATE_PRECHARGE_REQUEST = 0x06,
    VCU_STATE_PRECHARGE = 0x07,
    VCU_STATE_INVERTER_CHECK = 0x08,
    VCU_STATE_INVERTER_ENERGIZE = 0x18,
    VCU_STATE_RTD_RDY = 0x09,
    VCU_STATE_RTD_BTN = 0x10,
    VCU_STATE_DRIVING = 0x11,

    // Dash VCU
    VCU_STATE_DASH = 0x12,

    // SHDN VCU
    VCU_STATE_SHDN = 0x13,

    // ASSI VCU
    VCU_STATE_ASSI = 0x14,

    // EBS ADC VCU
    VCU_STATE_EBS_BTN = 0x15,

    // ACCU VCU
    VCU_STATE_ACCU = 0x16,

    // COOL VCU
    VCU_STATE_COOL = 0x17,

    // SENSOR VCU
    VCU_STATE_SENSOR = 0x18,

    // EBS VCU
    VCU_STATE_EBS_PWR = 0x20,
    VCU_STATE_EBS_CHECK_ASMS = 0x21,
    VCU_STATE_EBS_CHECK_PRESSURE = 0x22,
    VCU_STATE_EBS_CHECK_PRESSURE_BTN = 0x23,
    VCU_STATE_EBS_CHECK_PRESSURE_LOW = 0x24,
    VCU_STATE_EBS_CHECK_PRESSURE_HIGH = 0x25,
    VCU_STATE_EBS_CTRL_ACK = 0x26,
    VCU_STATE_EBS_IDLE = 0x30,
    VCU_STATE_EBS_PCHRG_PRESSED = 0x31,
    VCU_STATE_EBS_CHECK_TS = 0x32,
    VCU_STATE_EBS_CHECK_COMPUTE = 0x33,
    VCU_STATE_EBS_READY = 0x34,
    VCU_STATE_EBS_RELEASE_BRAKE = 0x35,
    VCU_STATE_EBS_DRIVE = 0x36,
    VCU_STATE_EBS_BRAKING = 0x2F,

    // 0xA- for Autonomous
    VCU_STATE_AV_IDLE = 0xA0,
    VCU_STATE_AV_PRECHARGE_REQUEST = 0xA1,
    VCU_STATE_AV_PRECHARGE = 0xA2,
    VCU_STATE_AV_INVERTER_CHECK = 0xA3,
    VCU_STATE_AV_RTD = 0xA4,
    VCU_STATE_AV_DRIVING = 0xA5,
    VCU_STATE_AV_EMERGENCY = 0xAF,

    // Error states
    VCU_STATE_TS_ERROR = 0xFE,
    VCU_STATE_SHUTDOWN = 0x0F,
    VCU_STATE_ERROR = 0xFF
} VCU_STATE;

typedef union VCU_Flags_Core
{
    uint8_t rawMem;
    struct
    {
        uint8_t P_CAN : 1;
        uint8_t P_ADC : 1;
        uint8_t P_ISRC : 1;
        uint8_t P_IMU : 1;
        uint8_t P_Watchdog : 1;
        uint8_t P_CAN1 : 1;
        uint8_t P_CAN2 : 1;
    } _VCU_Flags_Core;
} VCU_Flags_Core_u;

typedef union VCU_Flags_Ctrl
{
    uint16_t rawMem;
    // 13 bits
    struct
    {
        uint8_t HB_BMU : 1;
        uint8_t HB_MCISO : 1;
        uint8_t HB_INV : 1;
        uint8_t S_Accel0 : 1;
        uint8_t S_Accel1 : 1;
        uint8_t S_Brake0 : 1;
        uint8_t S_Brake1 : 1;
        uint8_t IMP_APPS : 1;  // T.4.2.5
        uint8_t IMP_BSE : 1;   // T.4.3.3
        uint8_t IMP_Pedal : 1; // EV.5.7
        uint8_t Brake_Pressed : 1;
        uint8_t HB_ACM : 1;
        uint8_t HB_Torque : 1;
        uint8_t AV_ACTIVE : 1;
    } _VCU_Flags_Ctrl;
} VCU_Flags_Ctrl_u;

typedef union VCU_Flags_Dash
{
    uint16_t rawMem;
    // 11 bits
    struct
    {
        uint8_t HB_BMU : 1;
        uint8_t HB_VCU_SHDN : 1;
        uint8_t S_Sus_L : 1;
        uint8_t S_Sus_R : 1;
        uint8_t S_Steer0 : 1;
        uint8_t S_Steer1 : 1;
        uint8_t IMP_Steer : 1;
        uint8_t LED_AMS : 1;
        uint8_t LED_IMD : 1;
        uint8_t LED_BSPD : 1;
        uint8_t LED_PDOC : 1;
        uint8_t BRAKE_LIGHT : 1;
    } _VCU_Flags_Dash;
} VCU_Flags_Dash_u;

typedef union VCU_Flags_SHDN
{
    uint16_t rawMem;
    struct
    {
        uint8_t S_Sus_L : 1;
        uint8_t S_Sus_R : 1;
        uint8_t SHDN_Status : 1;
    } _VCU_Flags_SHDN;
} VCU_Flags_SHDN_u;

typedef union VCU_Flags_EBS
{
    uint16_t rawMem;
    struct
    {
        uint8_t CTRL_PWR : 1;
        uint8_t CTRL_EBS : 1;
        uint8_t CTRL_SHDN : 1;
        uint8_t DET_24V : 1;
        uint8_t DET_PWR_EBS : 1;
        uint8_t DET_BTN : 1;
        uint8_t HB_DVL : 1;
        uint8_t HB_EBS_ADC : 1;
    } _VCU_Flags_EBS;
} VCU_Flags_EBS_u;

typedef union VCU_Flags_ASSI
{
    uint16_t rawMem;
    struct
    {
        uint8_t AS_STATE : 3;
    } _VCU_Flags_ASSI;
} VCU_Flags_ASSI_u;

typedef union VCU_Flags_EBS_BTN
{
    uint16_t rawMem;
    struct
    {
        uint8_t BTN_PRESSED : 1;
    } _VCU_Flags_EBS_BTN;
} VCU_Flags_EBS_BTN_u;

typedef union VCU_Flags_ACCU
{
    uint16_t rawMem;
    struct
    {
        uint8_t HB_VCU_CTRL : 1;
        uint8_t S_Sus_L : 1;
        uint8_t S_Sus_R : 1;
        uint8_t SHDN_Status : 1;
        uint8_t FAN_REAR : 1;
        uint8_t BRAKE_LIGHT : 1;
    } _VCU_Flags_ACCU;
} VCU_Flags_ACCU_u;

typedef union VCU_Flags_COOL
{
    uint16_t rawMem;
    struct
    {
        uint8_t HB_VCU_CTRL : 1;
        uint8_t TEMP_RAD : 1;
        uint8_t TEMP_BRAKE : 1;
        uint8_t SIDE_FAN : 1;
        uint8_t SIDE_PUMP : 1;
    } _VCU_Flags_COOL;
} VCU_Flags_COOL_u;

typedef union VCU_Flags_Other
{
    uint16_t rawMem;
    VCU_Flags_Ctrl_u ctrl;
    VCU_Flags_Dash_u dash;
    VCU_Flags_SHDN_u shdn;
    VCU_Flags_EBS_u ebs;
    VCU_Flags_EBS_BTN_u ebs_btn;
    VCU_Flags_ASSI_u assi;
    VCU_Flags_ACCU_u accu;
    VCU_Flags_COOL_u cool;
} VCU_Flags_Other_u;

typedef struct VCU_HeartbeatState
{
    uint8_t stateID;
    VCU_Flags_Core_u coreFlags;
    VCU_Flags_Other_u otherFlags;
    uint16_t VCU;
} VCU_HeartbeatState_t;

typedef struct VCU_Heartbeat
{
    uint32_t id;
    uint8_t data[8];
} VCU_Heartbeat_t;

VCU_Heartbeat_t Compose_VCU_Heartbeat(uint8_t id, VCU_HeartbeatState_t *state);
void Parse_VCU_Heartbeat(const uint8_t *data, VCU_HeartbeatState_t *state);

typedef struct VCU_RTD
{
    uint32_t id;
} VCU_RTD_t;

VCU_RTD_t Compose_VCU_RTD();

typedef struct VCU_MotorTemp
{
    uint32_t id;
    uint8_t data[8];
} VCU_MotorTemp_t;

VCU_MotorTemp_t
Compose_VCU_MotorTemp(uint8_t VCU_ID, uint32_t temp0, uint32_t temp1);

void Parse_VCU_MotorTemp(const uint8_t *data, uint32_t *temp0, uint32_t *temp1);

typedef struct VCU_IMU_Accel
{
    uint32_t id;
    uint8_t data[8];
} VCU_IMU_Accel_t;

VCU_IMU_Accel_t Compose_VCU_IMU_Accel(
    uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z
);

typedef struct VCU_IMU_Gyro
{
    uint32_t id;
    uint8_t data[8];
} VCU_IMU_Gyro_t;

VCU_IMU_Gyro_t Compose_VCU_IMU_Gyro(
    uint8_t VCU_ID, uint16_t scale, int16_t x, int16_t y, int16_t z
);

typedef struct VCU_LinearTravel
{
    uint32_t id;
    uint8_t data[8];
} VCU_LinearTravel_t;

VCU_LinearTravel_t
Compose_VCU_LinearTravel(uint8_t VCU_ID, bool front, uint16_t t0, uint16_t t1);

typedef struct VCU_AirPressure
{
    uint32_t id;
    uint8_t data[8];
} VCU_AirPressure_t;

VCU_AirPressure_t
Compose_VCU_AirPressure(uint8_t VCU_ID, uint16_t pressure_raw);

typedef struct VCU_TransmitSteering
{
    uint32_t id;
    uint8_t data[8];
} VCU_TransmitSteering_t;

VCU_TransmitSteering_t Compose_VCU_TransmitSteering(
    int16_t steering0, int16_t steering1, uint16_t adc0, uint16_t adc1
);
void Parse_VCU_TransmitSteering(
    const uint8_t *data, int16_t *steering0, int16_t *steering1, uint16_t *adc0,
    uint16_t *adc1
);

typedef struct VCU_ShutdownStatus_t
{
    uint32_t id;
    uint8_t data[8];
} VCU_ShutdownStatus_t;

VCU_ShutdownStatus_t Compose_VCU_ShutdownStatus(
    uint8_t line0, uint8_t line1, uint8_t line2, uint8_t line3, bool status
);
void Parse_VCU_ShutdownStatus(
    const uint8_t *data, uint8_t *line0, uint8_t *line1, uint8_t *line2,
    uint8_t *line3, bool *status
);

typedef struct VCU_Pedal_Accel
{
    uint32_t id;
    uint8_t data[8];
} VCU_Pedal_Accel_t;

VCU_Pedal_Accel_t Compose_VCU_Pedal_Accel(
    uint16_t accel0, uint16_t accel1, uint16_t accel_adc0, uint16_t accel_adc1
);
void Parse_VCU_Pedal_Accel(
    const uint8_t *data, uint16_t *accel0, uint16_t *accel1
);

typedef struct VCU_Pedal_Brake
{
    uint32_t id;
    uint8_t data[8];
} VCU_Pedal_Brake_t;

VCU_Pedal_Brake_t Compose_VCU_Pedal_Brake(
    uint16_t brake_adc0, uint16_t brake_adc1, int16_t brake_psi0,
    int16_t brake_psi1
);
void Parse_VCU_Pedal_Brake(
    const uint8_t *data, uint16_t *brake_adc0, uint16_t *brake_adc1,
    int16_t *brake_psi0, int16_t *brake_psi1
);

typedef struct VCU_Temp_Gearbox
{
    uint32_t id;
    uint8_t data[8];
} VCU_Temp_Gearbox_t;

VCU_Temp_Gearbox_t Compose_VCU_Temp_Gearbox(
    uint8_t VCU_ID, uint16_t adc, uint16_t R, uint16_t temp
);

typedef struct VCU_Suspension_Rot
{
    uint32_t id;
    uint8_t data[8];
} VCU_Suspension_Rot_t;

VCU_Suspension_Rot_t Compose_VCU_Suspension_Rot(
    uint8_t VCU_ID, uint16_t adcL, uint16_t adcR, int16_t degL, int16_t degR
);

typedef struct VCU_Flow_Rate {
	uint32_t id;
	uint8_t data[8];
} VCU_Flow_Rate_t;

VCU_Flow_Rate_t Compose_VCU_Flow_Rate(uint8_t vcu_id, uint16_t lpm, uint16_t freq);

typedef struct VCU_Wheel_Speed {
	uint32_t id;
	uint8_t data[8];
} VCU_Wheel_Speed_t;

VCU_Wheel_Speed_t Compose_VCU_Wheel_Speed(uint16_t freq_fl, uint16_t freq_fr, uint16_t rpm_fl, uint16_t rpm_fr);

// Object Dictionary

typedef struct VCU_OBJ_DICT
{
    uint32_t id;
    uint8_t data[8];
} VCU_OBJ_DICT_t;

VCU_OBJ_DICT_t Compose_VCU_OBJ_DICT(uint8_t VCU_ID, uint8_t data[8]);
void Parse_VCU_OBJ_DICT(
    const uint8_t *data, uint8_t *type, uint8_t *data_size, uint8_t *index,
    uint32_t *value
);

#endif /* COMMON_INC_CAN_VCU_H_ */
