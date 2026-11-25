/*
 * @file CAN_ECU.c
 * @brief Implementation of ECU CAN message compose and parse functions
 *
 * Provides functions for converting between ECU data structures and
 * CAN message payloads for communication between the ECU and other
 * vehicle boards
 */

#ifdef QUTMS_CAN_ECU

#include <CAN_ECU.h>

/*
 * @brief Compose ECU heartbeat message
 *
 * Packs ECU state information and status flags into an 8-byte payload
 */
ECU_HEARTBEAT_t Compose_ECU_HEARTBEAT(ECU_HEARTBEAT_STATE_t *state) {
    ECU_HEARTBEAT_t msg;

    msg.id = QUTMS_ECU_HEARTBEAT;

    msg.data[0] = state->stateID;
    msg.data[1] = (state->flags.rawMem) & 0xFF;
    msg.data[2] = (state->flags.rawMem >> 8) & 0xFF;

    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Parse ECU heartbeat message
 *
 * Extracts ECU state information and status flags from a received payload
 */
void Parse_ECU_HEARTBEAT(uint8_t *data, ECU_HEARTBEAT_STATE_t *state) {
    state->stateID = data[0];
    state->flags.rawMem = data[1] | (data[2] << 8);
}

/*
 * @brief Compose ECU shutdown circuit status message
 */
ECU_SHUTDOWN_STATUS_t Compose_ECU_SHUTDOWN_STATUS(uint16_t shutdownLines, uint8_t shutdownStatus) {
    ECU_SHUTDOWN_STATUS_t msg;

    msg.id = QUTMS_ECU_SHUTDOWN_STATUS;

    msg.data[0] = shutdownLines & 0xFF;
    msg.data[1] = (shutdownLines >> 8) & 0xFF;
    msg.data[2] = shutdownStatus;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Parse ECU shutdown circuit status message
 */
void Parse_ECU_SHUTDOWN_STATUS(uint8_t *data, uint16_t *shutdownLines, uint8_t *shutdownStatus) {
    *shutdownLines = data[0] | (data[1] << 8);
    *shutdownStatus = data[2];
}

/*
 * @brief Compose accelerator pedal message
 *
 * Packs both APPS sensor readings and their raw ADC counts into an
 * 8-byte payload
 */
ECU_PEDAL_ACCEL_t Compose_ECU_PEDAL_ACCEL(uint16_t accel_0, uint16_t accel_1, uint16_t accel_adc_0, uint16_t accel_adc_1) {
    ECU_PEDAL_ACCEL_t msg;

    msg.id = QUTMS_ECU_PEDAL_ACCEL;

    msg.data[0] = accel_0 & 0xFF;
    msg.data[1] = (accel_0 >> 8) & 0xFF;
    msg.data[2] = accel_1 & 0xFF;
    msg.data[3] = (accel_1 >> 8) & 0xFF;
    msg.data[4] = accel_adc_0 & 0xFF;
    msg.data[5] = (accel_adc_0 >> 8) & 0xFF;
    msg.data[6] = accel_adc_1 & 0xFF;
    msg.data[7] = (accel_adc_1 >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse accelerator pedal message
 */
void Parse_ECU_PEDAL_ACCEL(uint8_t *data, uint16_t *accel_0, uint16_t *accel_1, uint16_t *accel_adc_0, uint16_t *accel_adc_1) {
    *accel_0 = data[0] | (data[1] << 8);
    *accel_1 = data[2] | (data[3] << 8);
    *accel_adc_0 = data[4] | (data[5] << 8);
    *accel_adc_1 = data[6] | (data[7] << 8);
}

/*
 * @brief Compose brake pedal message
 *
 * Packs both brake pressure sensor ADC counts and converted PSI readings
 * into an 8-byte payload
 */
ECU_PEDAL_BRAKE_t Compose_ECU_PEDAL_BRAKE(uint16_t brake_adc_0, uint16_t brake_adc_1, int16_t brake_psi_0, int16_t brake_psi_1) {
    ECU_PEDAL_BRAKE_t msg;

    msg.id = QUTMS_ECU_PEDAL_BRAKE;

    msg.data[0] = brake_adc_0 & 0xFF;
    msg.data[1] = (brake_adc_0 >> 8) & 0xFF;
    msg.data[2] = brake_adc_1 & 0xFF;
    msg.data[3] = (brake_adc_1 >> 8) & 0xFF;
    msg.data[4] = brake_psi_0 & 0xFF;
    msg.data[5] = (brake_psi_0 >> 8) & 0xFF;
    msg.data[6] = brake_psi_1 & 0xFF;
    msg.data[7] = (brake_psi_1 >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse brake pedal message
 */
void Parse_ECU_PEDAL_BRAKE(uint8_t *data, uint16_t *brake_adc_0, uint16_t *brake_adc_1, int16_t *brake_psi_0, int16_t *brake_psi_1) {
    *brake_adc_0 = data[0] | (data[1] << 8);
    *brake_adc_1 = data[2] | (data[3] << 8);
    *brake_psi_0 = (int16_t)(data[4] | (data[5] << 8));
    *brake_psi_1 = (int16_t)(data[6] | (data[7] << 8));
}

/*
 * @brief Compose left gearbox temperature message
 */
ECU_GEARBOX_TEMP_t Compose_ECU_GEARBOX_TEMP_LEFT(uint16_t adc, uint16_t resistance, uint16_t temp) {
    ECU_GEARBOX_TEMP_t msg;

    msg.id = QUTMS_ECU_GEARBOX_TEMP_LEFT;

    msg.data[0] = adc & 0xFF;
    msg.data[1] = (adc >> 8) & 0xFF;
    msg.data[2] = resistance & 0xFF;
    msg.data[3] = (resistance >> 8) & 0xFF;
    msg.data[4] = temp & 0xFF;
    msg.data[5] = (temp >> 8) & 0xFF;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Parse left gearbox temperature message
 */
void Parse_ECU_GEARBOX_TEMP_LEFT(uint8_t *data, uint16_t *adc, uint16_t *resistance, uint16_t *temp) {
    *adc = data[0] | (data[1] << 8);
    *resistance = data[2] | (data[3] << 8);
    *temp = data[4] | (data[5] << 8);
}

/*
 * @brief Compose right gearbox temperature message
 */
ECU_GEARBOX_TEMP_t Compose_ECU_GEARBOX_TEMP_RIGHT(uint16_t adc, uint16_t resistance, uint16_t temp) {
    ECU_GEARBOX_TEMP_t msg;

    msg.id = QUTMS_ECU_GEARBOX_TEMP_RIGHT;

    msg.data[0] = adc & 0xFF;
    msg.data[1] = (adc >> 8) & 0xFF;
    msg.data[2] = resistance & 0xFF;
    msg.data[3] = (resistance >> 8) & 0xFF;
    msg.data[4] = temp & 0xFF;
    msg.data[5] = (temp >> 8) & 0xFF;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Parse right gearbox temperature message
 */
void Parse_ECU_GEARBOX_TEMP_RIGHT(uint8_t *data, uint16_t *adc, uint16_t *resistance, uint16_t *temp) {
    *adc = data[0] | (data[1] << 8);
    *resistance = data[2] | (data[3] << 8);
    *temp = data[4] | (data[5] << 8);
}

/*
 * @brief Compose cooling loop sensor message
 *
 * Shared packing logic for the four cooling sense messages (right-in,
 * left-in, right-out, left-out) - each carries raw and converted
 * pressure plus raw and converted temperature for one sensor
 */
static ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE(uint32_t id, uint16_t pressure_kPa, uint16_t temp_mV, uint16_t pressure_PSI, int16_t temp_C) {
    ECU_COOLING_SENSE_t msg;

    msg.id = id;

    msg.data[0] = pressure_kPa & 0xFF;
    msg.data[1] = (pressure_kPa >> 8) & 0xFF;
    msg.data[2] = temp_mV & 0xFF;
    msg.data[3] = (temp_mV >> 8) & 0xFF;
    msg.data[4] = pressure_PSI & 0xFF;
    msg.data[5] = (pressure_PSI >> 8) & 0xFF;
    msg.data[6] = temp_C & 0xFF;
    msg.data[7] = (temp_C >> 8) & 0xFF;

    return msg;
}

static void Parse_ECU_COOLING_SENSE(uint8_t *data, uint16_t *pressure_kPa, uint16_t *temp_mV, uint16_t *pressure_PSI, int16_t *temp_C) {
    *pressure_kPa = data[0] | (data[1] << 8);
    *temp_mV = data[2] | (data[3] << 8);
    *pressure_PSI = data[4] | (data[5] << 8);
    *temp_C = (int16_t)(data[6] | (data[7] << 8));
}

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_1(uint16_t pressure_kPa, uint16_t temp_mV, uint16_t pressure_PSI, int16_t temp_C) {
    return Compose_ECU_COOLING_SENSE(QUTMS_ECU_COOLING_SENSE_1, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

void Parse_ECU_COOLING_SENSE_1(uint8_t *data, uint16_t *pressure_kPa, uint16_t *temp_mV, uint16_t *pressure_PSI, int16_t *temp_C) {
    Parse_ECU_COOLING_SENSE(data, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_2(uint16_t pressure_kPa, uint16_t temp_mV, uint16_t pressure_PSI, int16_t temp_C) {
    return Compose_ECU_COOLING_SENSE(QUTMS_ECU_COOLING_SENSE_2, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

void Parse_ECU_COOLING_SENSE_2(uint8_t *data, uint16_t *pressure_kPa, uint16_t *temp_mV, uint16_t *pressure_PSI, int16_t *temp_C) {
    Parse_ECU_COOLING_SENSE(data, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_3(uint16_t pressure_kPa, uint16_t temp_mV, uint16_t pressure_PSI, int16_t temp_C) {
    return Compose_ECU_COOLING_SENSE(QUTMS_ECU_COOLING_SENSE_3, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

void Parse_ECU_COOLING_SENSE_3(uint8_t *data, uint16_t *pressure_kPa, uint16_t *temp_mV, uint16_t *pressure_PSI, int16_t *temp_C) {
    Parse_ECU_COOLING_SENSE(data, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

ECU_COOLING_SENSE_t Compose_ECU_COOLING_SENSE_4(uint16_t pressure_kPa, uint16_t temp_mV, uint16_t pressure_PSI, int16_t temp_C) {
    return Compose_ECU_COOLING_SENSE(QUTMS_ECU_COOLING_SENSE_4, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

void Parse_ECU_COOLING_SENSE_4(uint8_t *data, uint16_t *pressure_kPa, uint16_t *temp_mV, uint16_t *pressure_PSI, int16_t *temp_C) {
    Parse_ECU_COOLING_SENSE(data, pressure_kPa, temp_mV, pressure_PSI, temp_C);
}

/*
 * @brief Compose cooling loop flow rate message
 *
 * TODO: combines the old VCU_FlowRate_Left and VCU_FlowRate_Right
 * messages into one - confirm this merge with the team lead
 */
ECU_COOLING_FLOW_RATE_t Compose_ECU_COOLING_FLOW_RATE(uint16_t flow_lpm_left, uint16_t flow_freq_left, uint16_t flow_lpm_right, uint16_t flow_freq_right) {
    ECU_COOLING_FLOW_RATE_t msg;

    msg.id = QUTMS_ECU_COOLING_FLOW_RATE;

    msg.data[0] = flow_lpm_left & 0xFF;
    msg.data[1] = (flow_lpm_left >> 8) & 0xFF;
    msg.data[2] = flow_freq_left & 0xFF;
    msg.data[3] = (flow_freq_left >> 8) & 0xFF;
    msg.data[4] = flow_lpm_right & 0xFF;
    msg.data[5] = (flow_lpm_right >> 8) & 0xFF;
    msg.data[6] = flow_freq_right & 0xFF;
    msg.data[7] = (flow_freq_right >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse cooling loop flow rate message
 */
void Parse_ECU_COOLING_FLOW_RATE(uint8_t *data, uint16_t *flow_lpm_left, uint16_t *flow_freq_left, uint16_t *flow_lpm_right, uint16_t *flow_freq_right) {
    *flow_lpm_left = data[0] | (data[1] << 8);
    *flow_freq_left = data[2] | (data[3] << 8);
    *flow_lpm_right = data[4] | (data[5] << 8);
    *flow_freq_right = data[6] | (data[7] << 8);
}

/*
 * @brief Compose cooling loop pressure message
 *
 * TODO: assumes this maps to the old VCU_CoolingLoop_Pressure_Bar
 * message - confirm with the team lead (see header comment)
 */
ECU_COOLING_PRESSURE_t Compose_ECU_COOLING_PRESSURE(uint16_t pump1_pressure_bar, uint16_t pump2_pressure_bar, uint8_t sensor_status) {
    ECU_COOLING_PRESSURE_t msg;

    msg.id = QUTMS_ECU_COOLING_PRESSURE;

    msg.data[0] = pump1_pressure_bar & 0xFF;
    msg.data[1] = (pump1_pressure_bar >> 8) & 0xFF;
    msg.data[2] = pump2_pressure_bar & 0xFF;
    msg.data[3] = (pump2_pressure_bar >> 8) & 0xFF;
    msg.data[4] = sensor_status;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Parse cooling loop pressure message
 */
void Parse_ECU_COOLING_PRESSURE(uint8_t *data, uint16_t *pump1_pressure_bar, uint16_t *pump2_pressure_bar, uint8_t *sensor_status) {
    *pump1_pressure_bar = data[0] | (data[1] << 8);
    *pump2_pressure_bar = data[2] | (data[3] << 8);
    *sensor_status = data[4];
}

/*
 * @brief Compose suspension rotation message
 *
 * Shared packing logic for the front and rear suspension messages
 */
static ECU_SUSPENSION_t Compose_ECU_SUSPENSION(uint32_t id, uint16_t left_adc, uint16_t right_adc, int16_t left_rot, int16_t right_rot) {
    ECU_SUSPENSION_t msg;

    msg.id = id;

    msg.data[0] = left_adc & 0xFF;
    msg.data[1] = (left_adc >> 8) & 0xFF;
    msg.data[2] = right_adc & 0xFF;
    msg.data[3] = (right_adc >> 8) & 0xFF;
    msg.data[4] = left_rot & 0xFF;
    msg.data[5] = (left_rot >> 8) & 0xFF;
    msg.data[6] = right_rot & 0xFF;
    msg.data[7] = (right_rot >> 8) & 0xFF;

    return msg;
}

static void Parse_ECU_SUSPENSION(uint8_t *data, uint16_t *left_adc, uint16_t *right_adc, int16_t *left_rot, int16_t *right_rot) {
    *left_adc = data[0] | (data[1] << 8);
    *right_adc = data[2] | (data[3] << 8);
    *left_rot = (int16_t)(data[4] | (data[5] << 8));
    *right_rot = (int16_t)(data[6] | (data[7] << 8));
}

ECU_SUSPENSION_t Compose_ECU_SUSPENSION_FRONT(uint16_t left_adc, uint16_t right_adc, int16_t left_rot, int16_t right_rot) {
    return Compose_ECU_SUSPENSION(QUTMS_ECU_SUSPENSION_FRONT, left_adc, right_adc, left_rot, right_rot);
}

void Parse_ECU_SUSPENSION_FRONT(uint8_t *data, uint16_t *left_adc, uint16_t *right_adc, int16_t *left_rot, int16_t *right_rot) {
    Parse_ECU_SUSPENSION(data, left_adc, right_adc, left_rot, right_rot);
}

ECU_SUSPENSION_t Compose_ECU_SUSPENSION_REAR(uint16_t left_adc, uint16_t right_adc, int16_t left_rot, int16_t right_rot) {
    return Compose_ECU_SUSPENSION(QUTMS_ECU_SUSPENSION_REAR, left_adc, right_adc, left_rot, right_rot);
}

void Parse_ECU_SUSPENSION_REAR(uint8_t *data, uint16_t *left_adc, uint16_t *right_adc, int16_t *left_rot, int16_t *right_rot) {
    Parse_ECU_SUSPENSION(data, left_adc, right_adc, left_rot, right_rot);
}

/*
 * @brief Compose steering angle message
 *
 * Packs both steering sensor readings and their raw ADC counts into an
 * 8-byte payload
 */
ECU_STEERING_ANGLE_t Compose_ECU_STEERING_ANGLE(int16_t steering_0, int16_t steering_1, uint16_t steering_adc_0, uint16_t steering_adc_1) {
    ECU_STEERING_ANGLE_t msg;

    msg.id = QUTMS_ECU_STEERING_ANGLE;

    msg.data[0] = steering_0 & 0xFF;
    msg.data[1] = (steering_0 >> 8) & 0xFF;
    msg.data[2] = steering_1 & 0xFF;
    msg.data[3] = (steering_1 >> 8) & 0xFF;
    msg.data[4] = steering_adc_0 & 0xFF;
    msg.data[5] = (steering_adc_0 >> 8) & 0xFF;
    msg.data[6] = steering_adc_1 & 0xFF;
    msg.data[7] = (steering_adc_1 >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse steering angle message
 */
void Parse_ECU_STEERING_ANGLE(uint8_t *data, int16_t *steering_0, int16_t *steering_1, uint16_t *steering_adc_0, uint16_t *steering_adc_1) {
    *steering_0 = (int16_t)(data[0] | (data[1] << 8));
    *steering_1 = (int16_t)(data[2] | (data[3] << 8));
    *steering_adc_0 = data[4] | (data[5] << 8);
    *steering_adc_1 = data[6] | (data[7] << 8);
}

/*
 * @brief Compose wheel speed message
 *
 * TODO: front wheels only - see header comment on rear wheel speed
 */
ECU_WHEEL_SPEEDS_t Compose_ECU_WHEEL_SPEEDS(uint16_t freq_left, uint16_t freq_right, uint16_t rpm_left, uint16_t rpm_right) {
    ECU_WHEEL_SPEEDS_t msg;

    msg.id = QUTMS_ECU_WHEEL_SPEEDS;

    msg.data[0] = freq_left & 0xFF;
    msg.data[1] = (freq_left >> 8) & 0xFF;
    msg.data[2] = freq_right & 0xFF;
    msg.data[3] = (freq_right >> 8) & 0xFF;
    msg.data[4] = rpm_left & 0xFF;
    msg.data[5] = (rpm_left >> 8) & 0xFF;
    msg.data[6] = rpm_right & 0xFF;
    msg.data[7] = (rpm_right >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse wheel speed message
 */
void Parse_ECU_WHEEL_SPEEDS(uint8_t *data, uint16_t *freq_left, uint16_t *freq_right, uint16_t *rpm_left, uint16_t *rpm_right) {
    *freq_left = data[0] | (data[1] << 8);
    *freq_right = data[2] | (data[3] << 8);
    *rpm_left = data[4] | (data[5] << 8);
    *rpm_right = data[6] | (data[7] << 8);
}

/*
 * @brief Compose ready-to-drive status message
 */
ECU_RTD_t Compose_ECU_RTD(ECU_RTD_Flags_u flags) {
    ECU_RTD_t msg;

    msg.id = QUTMS_ECU_RTD;

    msg.data[0] = flags.rawMem;
    msg.data[1] = 0;
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Parse ready-to-drive status message
 */
void Parse_ECU_RTD(uint8_t *data, ECU_RTD_Flags_u *flags) {
    flags->rawMem = data[0];
}

#endif
