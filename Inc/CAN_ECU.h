/*
 * @file CAN_ECU.h
 * @brief CAN message definitions for the Electronic Control Unit (ECU)
 *
 * Defines all ECU CAN message structures, state definitions, status flags,
 * and compose/parse functions used for communication between the ECU and
 * other boards
 *
 * Payload layouts are ported from the old "VCU_*" messages in QUTMS.dbc /
 * qutms.c (VCU was the previous name for this board). Message IDs come
 * from the QUTMS_ECU_* entries already reserved in QUTMS_can.h.
 *
 * A few messages are flagged with TODO comments where the old VCU data
 * did not map 1:1 onto the new ECU message list - confirm these with the
 * team lead before treating them as final.
 */

#ifndef INC_CAN_ECU_H_
#define INC_CAN_ECU_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * @brief ECU operating states
 *
 * TODO: placeholder only. BMU's state list (bmu_state_t in CAN_BMU.h) was
 * defined by the team for the BMU's actual init/fault sequence - the ECU
 * needs the same treatment from the team lead. Do not treat these values
 * as final.
 */
typedef enum {
    ECU_STATE_INIT = 0x00,
    ECU_STATE_READY = 0x01,
    ECU_STATE_RTD = 0x02,
    ECU_STATE_ERROR = 0xFF
} ecu_state_t;

/*
 * @brief ECU status flags
 *
 * Only VCU_WARN_PedalPolarity is confirmed from the old DBC
 * (VCU_Heartbeat_CTRL). Remaining bits are reserved for whatever other
 * warnings/faults the team lead wants surfaced in the heartbeat - same
 * role as BMU_Flags_u in CAN_BMU.h.
 */
typedef union ECU_Flags {
    uint16_t rawMem;
    struct {
        uint8_t WARN_PEDAL_POLARITY :1;
        uint16_t RESERVED :15;
    } _ECU_Flags;
} ECU_Flags_u;

/*
 * @brief Decoded ECU heartbeat information
 *
 * Contains the ECU operating state and status flags transmitted in the
 * heartbeat CAN message
 */
typedef struct ECU_HEARTBEAT_STATE {
    uint8_t stateID;       // Current ECU operating state
    ECU_Flags_u flags;     // ECU status flags
} ECU_HEARTBEAT_STATE_t;

/*
 * @brief Encoded ECU heartbeat information
 */
typedef struct ECU_HEARTBEAT {
    uint32_t id;
    uint8_t data[8];
} ECU_HEARTBEAT_t;

ECU_HEARTBEAT_t Compose_ECU_HEARTBEAT(
    ECU_HEARTBEAT_STATE_t *state
);

void Parse_ECU_HEARTBEAT(
    uint8_t *data,
    ECU_HEARTBEAT_STATE_t *state
);

/*
 * @brief Encoded ECU shutdown circuit status message
 *
 * Ported from VCU_ShutdownStatus: a 16-bit bitmask of individual shutdown
 * segment states plus an overall status byte
 */
typedef struct ECU_SHUTDOWN_STATUS {
    uint32_t id;
    uint8_t data[8];
} ECU_SHUTDOWN_STATUS_t;

ECU_SHUTDOWN_STATUS_t Compose_ECU_SHUTDOWN_STATUS(
    uint16_t shutdownLines,    // Bitmask of individual shutdown segment states
    uint8_t shutdownStatus     // Overall shutdown circuit status (0/1)
);

void Parse_ECU_SHUTDOWN_STATUS(
    uint8_t *data,
    uint16_t *shutdownLines,
    uint8_t *shutdownStatus
);

/*
 * @brief Encoded accelerator pedal message
 *
 * Ported from VCU_Pedal_Accel: two independent APPS sensor readings plus
 * their raw ADC counts, for the two-signal plausibility check
 */
typedef struct ECU_PEDAL_ACCEL {
    uint32_t id;
    uint8_t data[8];
} ECU_PEDAL_ACCEL_t;

ECU_PEDAL_ACCEL_t Compose_ECU_PEDAL_ACCEL(
    uint16_t accel_0,          // APPS sensor 1 processed reading
    uint16_t accel_1,          // APPS sensor 2 processed reading
    uint16_t accel_adc_0,      // APPS sensor 1 raw ADC count
    uint16_t accel_adc_1       // APPS sensor 2 raw ADC count
);

void Parse_ECU_PEDAL_ACCEL(
    uint8_t *data,
    uint16_t *accel_0,
    uint16_t *accel_1,
    uint16_t *accel_adc_0,
    uint16_t *accel_adc_1
);

/*
 * @brief Encoded brake pedal message
 *
 * Ported from VCU_Pedal_Brake: two brake pressure sensor circuits, each
 * with a raw ADC count and a signed pressure reading (raw * 0.0625 = PSI)
 */
typedef struct ECU_PEDAL_BRAKE {
    uint32_t id;
    uint8_t data[8];
} ECU_PEDAL_BRAKE_t;

ECU_PEDAL_BRAKE_t Compose_ECU_PEDAL_BRAKE(
    uint16_t brake_adc_0,      // Brake pressure sensor 1 raw ADC count
    uint16_t brake_adc_1,      // Brake pressure sensor 2 raw ADC count
    int16_t brake_psi_0,       // Brake pressure sensor 1 (raw * 0.0625 = PSI)
    int16_t brake_psi_1        // Brake pressure sensor 2 (raw * 0.0625 = PSI)
);

void Parse_ECU_PEDAL_BRAKE(
    uint8_t *data,
    uint16_t *brake_adc_0,
    uint16_t *brake_adc_1,
    int16_t *brake_psi_0,
    int16_t *brake_psi_1
);

/*
 * @brief Encoded gearbox temperature message
 *
 * Ported from VCU_Temp_Gearbox_Left / VCU_Temp_Gearbox_Right: raw ADC,
 * derived resistance and temperature (raw * 0.1 = degC) for one gearbox
 * temperature sensor. Same layout used for both left and right messages.
 *
 * NOTE: the DBC signal is unsigned (VCU_Gearbox_Temp_Left_Temp : 39|16@0+),
 * unlike the cooling loop temperature signals which are signed - meaning
 * this can't represent sub-zero temperatures as currently encoded. Ported
 * as-is (unsigned); flag with the team lead if negative gearbox temps
 * need to be representable.
 */
typedef struct ECU_GEARBOX_TEMP {
    uint32_t id;
    uint8_t data[8];
} ECU_GEARBOX_TEMP_t;

ECU_GEARBOX_TEMP_t Compose_ECU_GEARBOX_TEMP_LEFT(
    uint16_t adc,              // Raw ADC count
    uint16_t resistance,       // Derived thermistor resistance
    uint16_t temp              // Temperature (raw * 0.1 = degC, unsigned)
);

void Parse_ECU_GEARBOX_TEMP_LEFT(
    uint8_t *data,
    uint16_t *adc,
    uint16_t *resistance,
    uint16_t *temp
);

ECU_GEARBOX_TEMP_t Compose_ECU_GEARBOX_TEMP_RIGHT(
    uint16_t adc,
    uint16_t resistance,
    uint16_t temp
);

void Parse_ECU_GEARBOX_TEMP_RIGHT(
    uint8_t *data,
    uint16_t *adc,
    uint16_t *resistance,
    uint16_t *temp
);

/*
 * @brief Encoded cooling loop sensor message
 *
 * Ported from VCU_Cooling_R_In / L_In / R_Out / L_Out: this is the
 * worked example from the team lead's meeting - a dual-purpose
 * pressure/temperature sensor, packing raw and converted readings for
 * both quantities into one 8-byte message. Same layout reused across
 * COOLING_SENSE_1..4 (right-in, left-in, right-out, left-out).
 */
typedef struct ECU_COOLING_SENSE {
    uint32_t id;
    uint8_t data[8];
} ECU_COOLING_SENSE_t;

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_1(
    uint16_t pressure_kPa,     // Pressure (raw * 0.1 = kPa)
    uint16_t temp_mV,          // Raw sensor voltage (mV)
    uint16_t pressure_PSI,     // Pressure (raw * 0.01 = PSI)
    int16_t temp_C             // Temperature (raw * 0.1 = degC)
);

void Parse_ECU_COOLING_SENSE_1(
    uint8_t *data,
    uint16_t *pressure_kPa,
    uint16_t *temp_mV,
    uint16_t *pressure_PSI,
    int16_t *temp_C
);

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_2(
    uint16_t pressure_kPa,
    uint16_t temp_mV,
    uint16_t pressure_PSI,
    int16_t temp_C
);

void Parse_ECU_COOLING_SENSE_2(
    uint8_t *data,
    uint16_t *pressure_kPa,
    uint16_t *temp_mV,
    uint16_t *pressure_PSI,
    int16_t *temp_C
);

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_3(
    uint16_t pressure_kPa,
    uint16_t temp_mV,
    uint16_t pressure_PSI,
    int16_t temp_C
);

void Parse_ECU_COOLING_SENSE_3(
    uint8_t *data,
    uint16_t *pressure_kPa,
    uint16_t *temp_mV,
    uint16_t *pressure_PSI,
    int16_t *temp_C
);

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_4(
    uint16_t pressure_kPa,
    uint16_t temp_mV,
    uint16_t pressure_PSI,
    int16_t temp_C
);

void Parse_ECU_COOLING_SENSE_4(
    uint8_t *data,
    uint16_t *pressure_kPa,
    uint16_t *temp_mV,
    uint16_t *pressure_PSI,
    int16_t *temp_C
);

/*
 * @brief Encoded cooling loop flow rate message
 *
 * TODO: the old scheme had two separate messages, VCU_FlowRate_Left and
 * VCU_FlowRate_Right (2 signals each: L/min and raw pulse frequency).
 * QUTMS_can.h only reserves one QUTMS_ECU_COOLING_FLOW_RATE ID, so this
 * assumes left and right are meant to be combined into a single 8-byte
 * message (4 x 16-bit values fits exactly). Confirm this merge with the
 * team lead before relying on it.
 */
typedef struct ECU_COOLING_FLOW_RATE {
    uint32_t id;
    uint8_t data[8];
} ECU_COOLING_FLOW_RATE_t;

ECU_COOLING_FLOW_RATE_t Compose_ECU_COOLING_FLOW_RATE(
    uint16_t flow_lpm_left,    // Left loop flow rate (raw * 0.01 = L/min)
    uint16_t flow_freq_left,   // Left loop raw pulse frequency
    uint16_t flow_lpm_right,   // Right loop flow rate (raw * 0.01 = L/min)
    uint16_t flow_freq_right   // Right loop raw pulse frequency
);

void Parse_ECU_COOLING_FLOW_RATE(
    uint8_t *data,
    uint16_t *flow_lpm_left,
    uint16_t *flow_freq_left,
    uint16_t *flow_lpm_right,
    uint16_t *flow_freq_right
);

/*
 * @brief Encoded cooling loop pressure message
 *
 * TODO: the old scheme had three related messages -
 * VCU_CoolingLoop_Status (raw mV pump pressure/temp),
 * VCU_CoolingLoop_Pressure_Bar (converted bar + sensor status), and the
 * per-side In/Out messages already covered by COOLING_SENSE_1..4.
 * QUTMS_can.h only reserves one QUTMS_ECU_COOLING_PRESSURE ID, so this
 * assumes it maps to the Pressure_Bar variant (matches the "PRESSURE"
 * name most closely). The raw-mV pump status data from
 * VCU_CoolingLoop_Status has no home in the current ID list - confirm
 * with the team lead whether that's intentionally dropped.
 */
typedef struct ECU_COOLING_PRESSURE {
    uint32_t id;
    uint8_t data[8];
} ECU_COOLING_PRESSURE_t;

ECU_COOLING_PRESSURE_t Compose_ECU_COOLING_PRESSURE(
    uint16_t pump1_pressure_bar,   // Pump 1 pressure (raw * 0.001 = bar)
    uint16_t pump2_pressure_bar,   // Pump 2 pressure (raw * 0.001 = bar)
    uint8_t sensor_status          // Cooling loop sensor status flags
);

void Parse_ECU_COOLING_PRESSURE(
    uint8_t *data,
    uint16_t *pump1_pressure_bar,
    uint16_t *pump2_pressure_bar,
    uint8_t *sensor_status
);

/*
 * @brief Encoded suspension rotation message
 *
 * Ported from VCU_Suspension_Rot_Front / Rear: raw ADC and converted
 * rotation reading (raw * 0.001, units TBD) for both sensors on one
 * axle. Same layout used for both front and rear messages.
 */
typedef struct ECU_SUSPENSION {
    uint32_t id;
    uint8_t data[8];
} ECU_SUSPENSION_t;

ECU_SUSPENSION_t Compose_ECU_SUSPENSION_FRONT(
    uint16_t left_adc,     // Front-left suspension pot raw ADC count
    uint16_t right_adc,    // Front-right suspension pot raw ADC count
    int16_t left_rot,      // Front-left rotation (raw * 0.001)
    int16_t right_rot      // Front-right rotation (raw * 0.001)
);

void Parse_ECU_SUSPENSION_FRONT(
    uint8_t *data,
    uint16_t *left_adc,
    uint16_t *right_adc,
    int16_t *left_rot,
    int16_t *right_rot
);

ECU_SUSPENSION_t Compose_ECU_SUSPENSION_REAR(
    uint16_t left_adc,
    uint16_t right_adc,
    int16_t left_rot,
    int16_t right_rot
);

void Parse_ECU_SUSPENSION_REAR(
    uint8_t *data,
    uint16_t *left_adc,
    uint16_t *right_adc,
    int16_t *left_rot,
    int16_t *right_rot
);

/*
 * @brief Encoded steering angle message
 *
 * Ported from VCU_TransmitSteering: two independent steering sensor
 * readings (raw * 0.1 = deg) plus their raw ADC counts, mirroring the
 * same two-signal plausibility pattern as pedal accel
 */
typedef struct ECU_STEERING_ANGLE {
    uint32_t id;
    uint8_t data[8];
} ECU_STEERING_ANGLE_t;

ECU_STEERING_ANGLE_t Compose_ECU_STEERING_ANGLE(
    int16_t steering_0,        // Steering sensor 1 (raw * 0.1 = deg)
    int16_t steering_1,        // Steering sensor 2 (raw * 0.1 = deg)
    uint16_t steering_adc_0,   // Steering sensor 1 raw ADC count
    uint16_t steering_adc_1    // Steering sensor 2 raw ADC count
);

void Parse_ECU_STEERING_ANGLE(
    uint8_t *data,
    int16_t *steering_0,
    int16_t *steering_1,
    uint16_t *steering_adc_0,
    uint16_t *steering_adc_1
);

/*
 * @brief Encoded wheel speed message
 *
 * Ported from VCU_Wheel_Speed_Front (front wheels only). The old DBC has
 * no rear wheel speed message - rear wheel speed is likely derived from
 * motor ERPM instead, since CAN_DTI.h / CAN_Sevcon.h already report
 * motor speed for the driven rear wheels. Confirm with the team lead
 * that QUTMS_ECU_WHEEL_SPEEDS is meant to be front-only.
 */
typedef struct ECU_WHEEL_SPEEDS {
    uint32_t id;
    uint8_t data[8];
} ECU_WHEEL_SPEEDS_t;

ECU_WHEEL_SPEEDS_t Compose_ECU_WHEEL_SPEEDS(
    uint16_t freq_left,    // Front-left wheel speed sensor raw frequency
    uint16_t freq_right,   // Front-right wheel speed sensor raw frequency
    uint16_t rpm_left,     // Front-left wheel speed (raw * 0.1 = RPM)
    uint16_t rpm_right     // Front-right wheel speed (raw * 0.1 = RPM)
);

void Parse_ECU_WHEEL_SPEEDS(
    uint8_t *data,
    uint16_t *freq_left,
    uint16_t *freq_right,
    uint16_t *rpm_left,
    uint16_t *rpm_right
);

/*
 * @brief Encoded ready-to-drive status message
 *
 * Ported from VCU_RTD: front and rear ready-to-drive flags
 */
typedef union ECU_RTD_Flags {
    uint8_t rawMem;
    struct {
        uint8_t RTD_FRONT :1;
        uint8_t RTD_REAR :1;
        uint8_t RESERVED :6;
    } _ECU_RTD_Flags;
} ECU_RTD_Flags_u;

typedef struct ECU_RTD {
    uint32_t id;
    uint8_t data[8];
} ECU_RTD_t;

ECU_RTD_t Compose_ECU_RTD(
    ECU_RTD_Flags_u flags
);

void Parse_ECU_RTD(
    uint8_t *data,
    ECU_RTD_Flags_u *flags
);

#endif /* INC_CAN_ECU_H_ */
