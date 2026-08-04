/*
 * @file CAN_BMU.h
 * @brief CAN message definitions for the Battery Management Unit (BMU)
 *
 * Defines all BMU CAN message structures, state definitions, status flags, 
 * and compose/parse functions used for communication between the BMU and 
 * other boards
 */

#ifndef INC_CAN_BMU_H_
#define INC_CAN_BMU_H_

#include <QUTMS_can.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * @brief BMU operating states
 * 
 * Defines the possible operating states of the Battery Management Unit. 
 * These values are transmitted in the BMU heartbeat CAN message to allow
 * other boards to determine the current status of the battery system. 
 */
typedef enum {
    BMU_STATE_START = 0x00,
    BMU_STATE_INIT_PERIPHERAL = 0x01,
    BMU_STATE_INIT_CMU = 0x02,
    BMU_STATE_CHECK_CMU_GPIO = 0x03,
    BMU_STATE_CHECK_SENDYNE = 0x04,
    BMU_STATE_CHECK_BOARD = 0x05,
    BMU_STATE_READY = 0x06,
    BMU_STATE_PRECHARGE = 0x07,
    BMU_STATE_TS_ACTIVE = 0x08,
    
    BMU_STATE_CHRG_CHECK_BOARD = 0x16,
    BMU_STATE_CHRG_READY = 0x17,
    BMU_STATE_CHRG_PRECHARGE = 0x18,
    BMU_STATE_CHRG_TS_ACTIVE = 0x19,
    
    BMU_STATE_CHRG_FAIL = 0x1A,
    BMU_STATE_TRIG_SHDN = 0x0D,
    BMU_STATE_SHUTDOWN = 0x0F,
    BMU_STATE_ERROR = 0xFF
} bmu_state_t;


/*
 * @brief BMU Status Flags
 *
 * Contains status information, warnings and  fault conditions 
 * for the Battery Management Unit
 * 
 * Each flag represents a single condition and is packed into a
 * 32 bit value for transmission in the BMU heartbeat CAN message. 
 */
typedef union BMU_Flags {
    uint32_t rawMem;
    struct {
        // Heartbeats status
        uint8_t HB_CMU :1;
        uint8_t HB_SENDYNE1 :1;
        uint8_t HB_SENDYNE2 :1;
        uint8_t HB_VCU_CTRL :1;
        uint8_t HB_CHRG_CTRL :1;

        // Peripheral status
        uint8_t P_WATCHDOG :1;
        uint8_t P_CAN1 :1;
        uint8_t P_CAN2 :1;

        // Contactor status
        uint8_t C_POS :1;
        uint8_t C_NEG :1;
        uint8_t C_PCHRG :1;
        uint8_t PCHRG_TIMEOUT :1;

        // Cell Monitoring Unit (CMU) fault status
        uint8_t CMU_OVER_VOLT :1;
        uint8_t CMU_UNDER_VOLT :1;
        uint8_t CMU_BAD_TEMP :1;
        uint8_t CMU_OPEN_VOLT :1;
        uint8_t CMU_OPEN_TEMP :1;
        uint8_t CMU_MISSING_VOLT :1;
        uint8_t CMU_MISSING_TEMP :1;

        // Shutdown system status
        uint8_t SHDN_BMU :1;
        uint8_t SHDN_PDOC :1;
        uint8_t SHDN_IMD :1;
        uint8_t SHDN_INTERLOCK :1;

        // General BMU status
        uint8_t BALANCING :1;
        uint8_t DIE_TEMPS :1;
        uint8_t HV_KEY :1;
        uint8_t CHRG_DET :1;
        uint8_t CHRG_CTRL :1;
    } _BMU_Flags;
} BMU_Flags_u;

/*
 * @brief Decoded BMU heartbeat information
 *
 * Contains the BMU operating state, status flags and battery information
 * transmitted in the heartbeat CAN message
 */
typedef struct BMU_HEARTBEAT_STATE {
    uint8_t stateID;        // Current BMU operating state
    BMU_Flags_u flags;      // BMU status flags
    uint8_t packState;      // Battery pack state
    uint8_t SOC;            // Battery state of charge
} BMU_HEARTBEAT_STATE_t;

/*
 * @brief Encoded BMU heartbeat information
 *
 * Stores the CAN identifier and 8-byte payload used for 
 * transmission of the CAN message
 */
typedef struct BMU_HEARTBEAT { 
    uint32_t id;  
    uint8_t data[8];
} BMU_HEARTBEAT_t;

BMU_HEARTBEAT_t Compose_BMU_HEARTBEAT(
    BMU_HEARTBEAT_STATE_t *state
);

void Parse_BMU_HEARTBEAT(
    uint8_t *data, 
    BMU_HEARTBEAT_STATE_t *state
);

/*
 * @brief Encoded BMU voltage message
 *
 * Stores the CAN identifier and 8-byte payload used to transmit
 * CMU cell voltage measurements
 */
typedef struct BMU_TRANSMIT_VOLTAGE {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_VOLTAGE_t;

BMU_TRANSMIT_VOLTAGE_t Compose_BMU_TRANSMIT_VOLTAGE(
    uint8_t cmuId,              // ID of the CMU
    uint8_t packId,             // ID of the battery pack
    uint16_t voltages[3],       // Array of the 3 cell voltages
    uint16_t age                // Measurement age (ms)
);

void Parse_BMU_TRANSMIT_VOLTAGE(
    uint8_t *data,              // Received CAN message
    uint16_t voltages[3],       // Array to store 3 cell voltages
    uint16_t *age               // Measurement age (ms)
);

/*
 * @brief Encoded BMU temperature message
 *
 * Stores the CAN identifier and 8-byte payload used to transmit
 * CMU cell temperature measurements
 */
typedef struct BMU_TRANSMIT_TEMPERATURE {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_TEMPERATURE_t;

/*
 * Packs 6 cell temperature measurements into CAN messages for 
 * transmission by the BMU
 */
BMU_TRANSMIT_TEMPERATURE_t Compose_BMU_TRANSMIT_TEMPERATURE(
    uint8_t cmuId,              // ID of the CMU
    uint8_t packId,             // ID of the battery pack
    uint8_t temps[6],           // Array of 6 temperatures
    uint16_t age                // Measurement age (ms)
);

void Parse_BMU_TRANSMIT_TEMPERATURE(
    uint8_t *data,              // Received CAN message
    uint8_t temps[6],           // Array to store 6 cell temperatures
    uint16_t *age               // Measurement age (ms)
);

/*
 * @brief Encoded BMU balancing message
 *
 * Stores the CAN identifier and 8-byte payload used to transmit
 * CMU cell balancing status
 */
typedef struct BMU_TRANSMIT_BALANCING {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_BALANCING_t;

BMU_TRANSMIT_BALANCING_t Compose_BMU_TRANSMIT_BALANCING(
    uint8_t cmuId,              // ID of the CMU
    uint16_t balanceState,       // Cell balancing status
    uint8_t dieTemp             // Die temperatures
);

/*
 * @brief Encoded BMU die temperatures message
 *
 * Stores the CAN identifier and 8-byte payload used to transmit
 * CMU die temperature measurements
 */
typedef struct BMU_TRANSMIT_DIETEMPS {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_DIETEMPS_t;

BMU_TRANSMIT_DIETEMPS_t Compose_BMU_TRANSMIT_DIETEMPS(
    uint8_t packId,         // Battery pack ID
    uint8_t temps[8]        // Array of 8 temperatures
);

/*
 * @brief Encoded BMU pack information message
 *
 * Stores the CAN identifier and 8-byte payload used to transmit
 * battery pack current and voltage measurements
 */
typedef struct BMU_TRANSMIT_PACKINFO {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_PACKINFO_t; 

BMU_TRANSMIT_PACKINFO_t Compose_BMU_TRANSMIT_PACKINFO(
    int32_t current,            // Battery pack current (mA)
    int32_t voltage_pack        // Battery pack voltage (mV)
);

/*
 * @brief Encoded BMU pack summary message
 *
 * Stores the CAN identifier and 8-byte payload containing battery pack 
 * summary information including voltage and temperature data 
 */
typedef struct BMU_TRANSMIT_PACKSUMMARY {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_PACKSUMMARY_t;

BMU_TRANSMIT_PACKSUMMARY_t Compose_BMU_TRANSMIT_PACKSUMMARY(
    uint16_t min_cell_mv,       // Minimum cell voltage (mV)
    uint32_t pack_total_mv,     // Total battery pack voltage (mV)
    uint8_t total_valid_cells,  // Number of valid cells detected
    uint8_t max_temps           // Maximum cell temperature
);

/*
 * @brief Encoded BMU State of Charge (SOC) message
 *
 * Stores the CAN identifier and 8-byte payload used to transmit 
 * battery State of Charge and coulomb counter information 
 */
typedef struct BMU_TRANSMIT_SOC {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_SOC_t;

BMU_TRANSMIT_SOC_t Compose_BMU_TRANSMIT_SOC(
    uint8_t soc_percent,        // State of charge %
    uint8_t flags,              // SOC status flags
    uint32_t coulomb_uAh        // Measured charge (µAh)
);

/*
 * @brief Encoded BMU power message
 *
 * Stores the CAN identifier and 8-byte payload used to trasnmit
 * power information
 */
typedef struct BMU_TRANSMIT_POWER {
    uint32_t id;
    uint8_t data[8];
} BMU_TRANSMIT_POWER_t;

BMU_TRANSMIT_POWER_t Compose_BMU_TRANSMIT_POWER(
    uint32_t power          // Battery pack power (W)
);
#endif /* INC_CAN_BMU_H_ */