/*
 * @file CAN_ChrgCtrl.c
 * @brief Implementation of the Charge Control message compose and parse functions
 *
 * Provides functions for converting between Charge Control data structures and 
 * CAN message payload for communication between Charge Control and charger
 */
#ifdef QUTMS_CAN_CHRG_CTRL

#include "CAN_ChrgCtrl.h"


/*
 * @brief Compose Charge Control heartbeat message
 *
 * Packs Charge Control state information and status flags into an 8-byte payload
 */
CHRGCTRL_HEARTBEAT_t Compose_CHRG_CTRL_HEARTBEAT(CHRGCTRL_HEARTBEATSTATE_t *state) {
    CHRGCTRL_HEARTBEAT_t msg;

    // CAN message ID
    msg.id = QUTMS_CHARGE_CONTROL_HEARTBEAT;

    // Charge Control state information 
    msg.data[0] = state->stateID;
    msg.data[1] = state->flags.rawMem;

    return msg;
}

/*
 * @brief Parse Charge Control Heartbeat
 *
 * Extracts Charge Control state information and status flags from a recieved payload
 */
void Parse_CHRGCTRL_HEARTBEAT(uint8_t *data, CHRGCTRL_HEARTBEAT_STATE_t *state) {
    // Extracts Charge Control operating state
    state->stateID = msg.data[0];
    state->flag.rawMem = msg.data[1];
}

#endif