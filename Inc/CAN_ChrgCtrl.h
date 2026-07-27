#ifndef COMMON_INC_CAN_CHRGCTRL_H_
#define COMMON_INC_CAN_CHRGCTRL_H_

#include <QUTMS_can.h>
#include <stdint.h>

enum CHRGCTRL_STATE {
    CHRGCTRL_STATE_IDLE = 0x01,
    CHRGCTRL_STATE_PRECHARGE_REQUEST = 0x02,
    CHRGCTRL_STATE_PRECHARGE = 0x03,
    CHRGCTRL_STATE_CHARGING = 0x04,
    CHRGCTRL_STATE_STOP_CHARGE = 0x0F
};

typedef union CHRGCTRL_Flags {
    uint8_t rawMem; 
    struct {
        uint8_t HB_AMS;
    };
} CHRGCTRL_Flags_u;

typedef struct CHRGCTRL_HEARTBEAT_STATE {
    uint8_t stateID;
    CHRGCTRL_Flags_u flags;
} CHRGCTRL_HEARTBEAT_STATE_t;

typedef struct CHRGCTRL_HEARTBEAT {
    uint32_t id;
    uint8_t data[8];
} CHRGCTRL_HEARTBEAT_t;

CHRGCTRL_HEARTBEAT_t Compose_CHRG_CTRL_HEARTBEAT(CHRGCTRL_HEARTBEAT_STATE_t *state);
void Parse_QUTMS_CHRG_CTRL_HEARTBEAT( uint8_t *data, CHRGCTRL_HEARTBEAT_STATE_t *state);

#endif