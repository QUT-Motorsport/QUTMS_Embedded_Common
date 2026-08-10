/*
 * @file CAN_ChrgCtrl.h
 * @brief CAN message definitions for Charge Control
 *
 * Defines all Charge Control CAN message structures, state definitions, status flags,
 * and compose/parse functions used for communication between the Charge Control and
 * other boards
 */

#ifndef COMMON_INC_CAN_CHRGCTRL_H_
#define COMMON_INC_CAN_CHRGCTRL_H_

#include <QUTMS_can.h>
#include <stdint.h>

/*
 * @brief Charge Control operating states
 *
 * Defines the possible operating states of Charge Control.
 * These values are transmitted in the Charge Control heartbeat CAN message to indicate
 * the charging status of the accumulator
 */
enum CHRGCTRL_STATE {
    CHRGCTRL_STATE_IDLE = 0x01,
    CHRGCTRL_STATE_PRECHARGE_REQUEST = 0x02,
    CHRGCTRL_STATE_PRECHARGE = 0x03,
    CHRGCTRL_STATE_CHARGING = 0x04,
    CHRGCTRL_STATE_STOP_CHARGE = 0x0F
};

/*
 * @brief Charge Control status flags
 *
 * Contains status information, warning and fault conditions for Charge Control
 * 
 * Each flag represents a single condition and is packed into a 8 bit value
 * for transmission in the Charge Control heartbeat CAN message 
 */
typedef union CHRGCTRL_Flags {
    uint8_t rawMem; 
    struct {
        uint8_t HB_AMS;
    };
} CHRGCTRL_Flags_u;

/*
 * @brief Decoded Charge Control heartbeat information
 *
 * Contains the Charge Control operating state and status flags transmitted in
 * the heartbeat CAN message
 */
typedef struct CHRGCTRL_HEARTBEAT_STATE {
    uint8_t stateID;
    CHRGCTRL_Flags_u flags;
} CHRGCTRL_HEARTBEAT_STATE_t;

/*
 * @brief Encoded Charge Control heartbeat
 *
 * Stores the CAN identifier and 8-byte used for transmission of the CAN message
 */
typedef struct CHRGCTRL_HEARTBEAT {
    uint32_t id;
    uint8_t data[8];
} CHRGCTRL_HEARTBEAT_t;

CHRGCTRL_HEARTBEAT_t Compose_CHRG_CTRL_HEARTBEAT(
    CHRGCTRL_HEARTBEAT_STATE_t *state)
;

void Parse_QUTMS_CHRG_CTRL_HEARTBEAT(
    uint8_t *data, 
    CHRGCTRL_HEARTBEAT_STATE_t *state
);

#endif /* COMMON_INC_CAN_CHRGCTRL_H_*/