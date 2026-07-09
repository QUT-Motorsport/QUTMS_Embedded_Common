/*
 * QUTMS_can.h
 *
 *  Created on: July 4, 2026
 *
 */

#ifndef QUTMS_can_H
#define QUTMS_can_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdint.h>

/* Defining Message */
#define Compose_CANId(priority, sourceId, autonomous, type, fd, extra, boardIdx) \
    ((((priority)) << 27 | ((sourceId)) << 22 | ((autonomous)) << 21 | ((type)) << 18 | \
      ((fd)) << 17 | ((extra)) << 4 | ((boardIdx))))

/* Priority */
#define QUTMS_PRIO_ERROR      0x00
#define QUTMS_PRIO_HEARTBEAT  0x01
#define QUTMS_PRIO_NORMAL     0x02
#define QUTMS_PRIO_DEBUG      0x03

/* Source ID */
#define QUTMS_SRC_BMU              0x00
#define QUTMS_SRC_ECU              0x01
#define QUTMS_SRC_ACM              0x02
#define QUTMS_SRC_ROS              0x03
#define QUTMS_SRC_SHUTDOWN         0x08
#define QUTMS_SRC_SW_MOTEC         0x0B
#define QUTMS_SRC_CHARGE_CONTROL   0x0F

/* System */
#define QUTMS_SYSTEM_EV 0x00
#define QUTMS_SYSTEM_AV 0x01

/* Type */
#define QUTMS_TYPE_ERROR      0x00
#define QUTMS_TYPE_HEARTBEAT  0x01
#define QUTMS_TYPE_RECEIVE    0x02
#define QUTMS_TYPE_TRANSMIT    0x03
#define QUTMS_TYPE_OBJ_DICT   0x04
#define QUTMS_TYPE_STREAM     0x05

/* CAN TYPE */
#define QUTMS_CAN_TYPE_NORMAL 0x00
#define QUTMS_CAN_TYPE_FD 0x01



// MESSAGE IDS

enum CAN_MSG_IDs {
  /* ECU */
  #ifdef QUTMS_CAN_ECU
    ECU_Heartbeat_ID Compose_CANId(QUTMS_PRIO_HEARTBEAT, QUTMS_SRC_ECU, QUTMS_SYSTEM_EV, QUTMS_CAN_TYPE_NORMAL, 0x00);
    QUTMS_ECU_SHUTDOWN_STATUS;
    QUTMS_ECU_PEDAL_ACCEL;
    QUTMS_ECU_PEDAL_BRAKE;
    QUTMS_ECU_GEARBOX_TEMP_LEFT;
    QUTMS_ECU_GEARBOX_TEMP_RIGHT;
    QUTMS_ECU_COOLING_SENSE_1;
    QUTMS_ECU_COOLING_SENSE_2;
    QUTMS_ECU_COOLING_SENSE_3;
    QUTMS_ECU_COOLING_SENSE_4;
    QUTMS_ECU_COOLING_FLOW_RATE;
    QUTMS_ECU_COOLING_PRESSURE;
    QUTMS_ECU_SUSPENSION_FRONT;
    QUTMS_ECU_SUSPENSION_REAR;
    QUTMS_ECU_STEERING_ANGLE;
    QUTMS_ECU_WHEEL_SPEEDS;
    #endif

  /* ACM */
  #ifdef QUTMS_CAN_ACM
    // leave for now
  #endif


};

#ifdef __cplusplus
}
#endif
#endif /* QUTMS_can_H */