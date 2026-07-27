#ifdef QUTMS_CAN_CHRG_CTRL

#include "CAN_ChrgCtrl.h"

CHRGCTRL_HEARTBEAT_t Compose_CHRG_CTRL_HEARTBEAT(CHRGCTRL_HEARTBEATSTATE_T *state) {
    CHRGCTRL_HEARTBEAT_t msg;

    msg.id = QUTMS_CHARGE_CONTROL_HEARTBEAT;
    msg.data[0] = state->stateID;
    msg.data[1] = state->flags.rawMem;

    return msg;
}

void Parse_CHRGCTRL_HEARTBEAT(uint8_t *data, CHRGCTRL_HEARTBEAT_STATE_t *state) {
    state->stateID = msg.data[0];
    state->flag.rawMem = msg.data[1];
}

#endif