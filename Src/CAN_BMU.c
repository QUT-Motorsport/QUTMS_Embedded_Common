/* 
 * @file CAN_BMU.c
 * @brief Implementation of BMU CAN message compose and parse functions
 *
 * Provides functions for converting between BMU data structures and 
 * CAN message payloads for communication between the BMU and other 
 * vehicle boards
 */

#ifdef QUTMS_CAN_BMU

#include <QUTMS_BMU.h>

/*
 * @brief Compose BMU heartbeat message
 *
 * Packs BMU state information, status flags, pack state and SOC
 * into an 8-byte payload
 */
BMU_HEARTBEAT_t Compose_BMU_HEARTBEAT(BMU_HEARTBEAT_STATE_t *state) {
    BMU_HEARTBEAT_t msg;

    // CAN message ID
    msg.id = QUTMS_BMU_HEARTBEAT;

    // BMU state information 
    msg.data[0] = state->stateID;

    // Splits 32-bit status flags into 4 CAN bytes
    msg.data[1] = (state->flags.rawMem) & 0xFF;
    msg.data[2] = (state->flags.rawMem >> 8) & 0xFF;
    msg.data[3] = (state->flags.rawMem >> 16) & 0xFF;
    msg.data[4] = (state->flags.rawMem >> 24) & 0xFF;

    // Battery pack information 
    msg.data[5] = (state->packState) & 0xFF;
    msg.data[6] = state->SOC;

    return msg;
}

/*
 * @brief Parse BMU heartbeat message 
 *
 * Extracts BMU state information, status flahs, pack statn and SOC
 * from a recieved CAN payload
 */
void Parse_BMU_HEARTBEAT(uint8_t *data, BMU_HEARTBEAT_STATE_t *state) {
    // Extracts BMU operating state 
    state->stateID = data[0];

    // Reconstructs 32-bit status flags from CAN payload bytes
    state->flags.rawMem = data[1] | data[2] << 8 | data[3] << 16 | data[4] << 24;

    // Extracts battey pack information
    state->packState = data[5];
    state->SOC = data[6];
}

/*
 * @brief Compose BMU voltage messgae
 *
 * Packs CMU cell voltage mesaurements and measurement age into an 
 * 8-byte CAN payload
 */
BMU_TRANSMIT_VOLTAGE_t Compose_BMU_TRANSMIT_VOLTAGE(uint8_t cmuId, uint8_t packId, uint16_t voltages[3], uint16_t age)
{
    BMU_TRANSMIT_VOLTAGE_t msg;
    
    //Constructs CAN ID using CMU and pack identifiers 
    msg.id = QUTMS_BMU_TRANSMIT_VOLTAGE_N_0 | ((cmuId & 0x3FF) << 4) | (packId & 0xF);

    // Three cell voltage measurements 
    msg.data[0] = voltages[0] & 0xFF;
    msg.data[1] = (voltages[0] >> 8) & 0xFF;
    msg.data[2] = voltages[1] & 0xFF;
    msg.data[3] = (voltages[1] >> 8) & 0xFF;
    msg.data[4] = voltages[2] & 0xFF;
    msg.data[5] = (voltages[2] >> 8) & 0xFF;

    // Measurement age
    msg.data[6] = age & 0xFF;
    msg.data[7] = (age >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse BMU voltage message
 *
 * Extracts CMU cell voltage measurements and measurement age from
 * a recieved payload 
 */
void Parse_BMU_TRANSMIT_VOLTAGE(uint8_t *data, uint16_t voltages[3], uint16_t *age) 
{
    // Reconstructs three cell voltage measurements 
    voltages[0] = data[0] | data[1] << 8;
    voltages[1] = data[2] | data[3] << 8;
    voltages[2] = data[4] | data[5] << 8;

    // Reconstructs measurement age
    *age = data[6] | data[7] << 8;
}

/*
 * @brief Compose BMU temperature message 
 *
 * Packs CMU cell temperature measurements and measurement age into an 
 * 8-byte payload
 */
BMU_TRANSMIT_TEMPERATURE_t Compose_BMU_TRANSMIT_TEMPERATURE(uint8_t cmuId, uint8_t packId, uint8_t temps[6], uint16_t age) {
    BMU_TRANSMIT_TEMPERATURE_t msg;
    
    // Constructs CAN ID using CMU and pack identifiers
    msg.id = QUTMS_BMU_TRANSMIT_TEMPERATURE_N_0 | ((cmuId & 0x3FF) << 4) | (packId & 0xF);

    // Six cell temperature measurements 
    msg.data[0] = temps[0];
    msg.data[1] = temps[1];
    msg.data[2] = temps[2];
    msg.data[3] = temps[3];
    msg.data[4] = temps[4];
    msg.data[5] = temps[5];

    // Measurement age
    msg.data[6] = age & 0xFF;
    msg.data[7] = (age >> 8) & 0xFF;

    return msg;
}

/*
 * @brief Parse BMU temperature message
 *
 * Extracts CMU cell temperature measurements and measurement age from 
 * a recieved payload 
 */
void Parse_BMU_TRANSMIT_TEMPERATURE(uint8_t *data, uint8_t temps[6], uint16_t *age) {
    // Extracts six temperature messages 
    temps[0] = data[0];
    temps[1] = data[1];
    temps[2] = data[2];
    temps[3] = data[3];
    temps[4] = data[4];
    temps[5] = data[5];

    // Reconstructs measurement age 
    *age = data[6] | data[7] << 8;
}

/*
 * @brief Compose BMU balancing message
 *
 * Packs CMU cell balancing status and die temperature information into
 * an 8-byte CAN payload
 */
BMU_TRANSMIT_BALANCING_t Compose_BMU_TRANSMIT_BALANCING(uint8_t cmuId, uint16_t balanceState, uint8_t dieTemp) {
    BMU_TRANSMIT_BALANCING_t msg;

    // Constructs CAN ID using CMU identifier 
    msg.id = QUTMS_BMU_TRANSMIT_BALANCING_N_0 | ((cmuId & 0x3FF) << 4);

    // Balancing status
    msg.data[0] = balanceState & 0xFF; 
    msg.data[1] = (balanceState >> 8) & 0xFF;

    // Die temperature
    msg.data[2] = dieTemp;

    return msg;
}

/*
 * @brief Compose BMU die temperature measurements 
 *
 * Packs battery pack die temperature measurements into an 
 * 8-byte CAN payload 
 */
BMU_TRANSMIT_DIETEMPS_t Compose_BMU_TRANSMIT_DIETEMPS(uint8_t packId, uint8_t temps[8]) {
    BMU_TRANSMIT_DIETEMPS_t msg;
    
    // Constructs CAN ID using pack identifier 
    msg.id = QUTMS_BMU_TRANSMIT_DIETEMPS | (packId & 0xF);

    // Packs 8 temperautre measurements into CAN payload
    for (int i = 0; i < 8; i++) {
        msg.data[i] = temps[i];
    }

    return msg;
}

/*
 * @brief Compose BMU pack info message
 *
 * Packs battery pack current and voltage measurements into 
 * an 8-byte CAN payload
 */ 
BMU_TRANSMIT_PACKINFO_t Compose_BMU_TRANSMIT_PACKINFO(int32_t current, int32_t voltage_pack) {
    BMU_TRANSMIT_PACKINFO_t msg;

    //CAN message ID
    msg.id = QUTMS_BMU_TRANSMIT_PACKINFO;
    
    // Battery pack current
    msg.data[0] = current & 0xFF;
    msg.data[1] = (current >> 8) & 0xFF;
    msg.data[2] = (current >> 16) & 0xFF;
    msg.data[3] = (current >> 24) & 0xFF;

    // Battery pack voltage
    msg.data[4] = voltage_pack & 0xFF;
    msg.data[5] = (voltage_pack >> 8) & 0xFF;
    msg.data[6] = (voltage_pack >> 16) & 0xFF;
    msg.data[7] = (voltage_pack >> 24) & 0xFF;

    return msg;
}

/*
 * @brief Compose BMU pack summary message
 *
 * Packs battery pack summary information including minimum cell
 * voltage, total pack voltage, valid cell count and maximum
 * temperature into a CAN payload
 */
BMU_TRANSMIT_PACKSUMMARY_t Compose_BMU_TRANSMIT_PACKSUMMARY(uint16_t min_cell_mv, uint32_t pack_total_mv, uint8_t total_valid_cells, uint8_t max_temps) {
    BMU_TRANSMIT_PACKSUMMARY_t msg;

    // CAN message ID
    msg.id = QUTMS_BMU_TRANSMIT_PACKSUMMARY;

    // Minimum cell voltage
    msg.data[0] = min_cell_mv & 0xFF;
    msg.data[1] = (min_cell_mv >> 8) & 0xFF;

    // Total battery pack voltage 
    msg.data[2] = pack_total_mv & 0xFF;
    msg.data[3] = (pack_total_mv >> 8) & 0xFF;
    msg.data[4] = (pack_total_mv >> 16) & 0xFF;
    msg.data[5] = (pack_total_mv >> 24) & 0xFF;

    // Cell and temperature summary information 
    msg.data[6] = total_valid_cells;
    msg.data[7] = max_temps;
    
    return msg;
}

/*
 * @brief Compose BMU State of Charge (SOC) message
 *
 * Packs battery State of Charge information, status flags, and 
 * coulomb counter data into an 8-byte payload
 */
BMU_TRANSMIT_SOC_t Compose_BMU_TRANSMIT_SOC(uint8_t soc_percent, uint8_t flags, uint32_t coulomb_uAh) {
    BMU_TRANSMIT_SOC_t msg;

    // CAN message ID
    msg.id = QUTMS_BMU_TRANSMIT_SOC;

    // SOC percentage and status flags
    msg.data[0] = soc_percent;
    msg.data[1] = flags;
    
    // Coulomb counter value 
    msg.data[2] = (uint8_t)(coulomb_uAh & 0xFF);
    msg.data[3] = (uint8_t)((coulomb_uAh >> 8) & 0xFF);
    msg.data[4] = (uint8_t)((coulomb_uAh >> 16) & 0xFF);
    msg.data[5] = (uint8_t)((coulomb_uAh >> 24) & 0xFF);

    // Reseved bytes
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

/*
 * @brief Compose BMU power message
 *
 * Packs calculated battery pack power into an 8-byte CAN payload
 */
BMU_TRANSMIT_POWER_t Compose_BMU_TRANSMIT_POWER(uint32_t power) {
    BMU_TRANSMIT_POWER_t msg;
    
    // CAN message ID
    msg.id = QUTMS_BMU_TRANSMIT_POWER;

    // Battery pack power 
    msg.data[0] = power & 0xFF;
    msg.data[1] = (power >> 8) & 0xFF;
    msg.data[2] = (power >> 16) & 0xFF;
    msg.data[3] = (power >> 24) & 0xFF;

    return msg;
}

#endif