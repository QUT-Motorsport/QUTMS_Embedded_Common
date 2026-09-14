/*
 * CAN_DTI.h
 *
 *  Created in: 2026
 *  Author: Chloe B
 *
 */

#ifndef INC_CAN_DTI_H_
#define INC_CAN_DTI_H_

#include <stdint.h>

/* Node IDs */ 
typedef enum {
    DTI_NODE_LEFT = 0x73,
    DTI_NODE_RIGHT = 0x74,
    DTI_NODE_BOTH = 0xFF,
} dti_node_t;

/* Packet IDs */
typedef enum {
    // messages sent from inverter
    DTI_PID_S1 = 0x1F, // CONTROL STATUS - Control mode, Target Iq, motor position, isMotorStill
    DTI_PID_S2 = 0x20, // ERPM_DUTY_VOLT - ERPM, Duty, Input Voltage
    DTI_PID_S3 = 0x21, // CURRENTS_READ - AC Current, DC Current
    DTI_PID_S4 = 0x22, // TEMPS_FAULTS - Controller Temp., Motor Temp., Fault code
    DTI_PID_S5 = 0x23, // FOC - Id, Iq values
    DTI_PID_S6 = 0x24, // CONTROL_DATA - Throttle signal, Brake signal, Digital I/Os, Drive enable, Limit status bits, CAN map version
    DTI_PID_S7 = 0x25, // AC_SET - configured max AC current, available max AC current, configured min AC current, available min AC current
    DTI_PID_S8 = 0x26, // DC_SET - configured max DC current, available max DC current, configured min DC current, available min DC current
    // Commands to Inverter
    DTI_PID_C1 = 0x01, //SET_CURRENT - 
    DTI_PID_C2 = 0x02, // SET_BRAKE_CURRENT - 
    DTI_PID_C3 = 0x03, // SET_EPRM - 
    DTI_PID_C4 = 0x04, // SET_POS - 
    DTI_PID_C5 = 0x05, // SET_REL_CURRENT - 
    DTI_PID_C6 = 0x06, // SET_REL_BRAKECURRENT - 
    DTI_PID_C7 = 0x07, // SET_DIG_OUTPUT - 
    DTI_PID_C8 = 0x08, // SET_MAX_AC_CURRENT - 
    DTI_PID_C9 = 0x09, // SET_MAX_AC_BRAKECURRENT - 
    DTI_PID_C10 = 0x0A, // SET_MAX_DC_CURRENT - 
    DTI_PID_C11 = 0x0B, // SET_MAX_DC_BRAKECURRENT - 
    DTI_PID_C12 = 0x0C, // DRIVE_ENABLE - 
} dti_pid_t;

/* DTI Fault Codes */
typedef enum
{
    DTI_FAULT_NONE = 0x00,                
    DTI_FAULT_OVERVOLTAGE = 0x01,         
    DTI_FAULT_UNDERVOLTAGE = 0x02,        
    DTI_FAULT_DRV_ERROR = 0x03,           
    DTI_FAULT_OVERCURRENT = 0x04,         
    DTI_FAULT_CTLR_OVERTEMP = 0x05,       
    DTI_FAULT_MOTOR_OVERTEMP = 0x06,      
    DTI_FAULT_SENSOR_WIRE = 0x07,         
    DTI_FAULT_SENSOR_GENERAL = 0x08,      
    DTI_FAULT_CAN_COMMAND = 0x09,
    DTI_FAULT_ANALOG_INPUT = 0x0A,
} DTI_FAULTS_t;

typedef enum {
    DTI_DRIVE_ALLOWED = 1,
    DTI_DRIVE_NOT_ALLOWED = 0,
} DTI_drive_status_t;

/* ID */
// Extended CAN ID = Packet ID (bits 28:8) | Node ID (bits 7:0) -> shift the packet ID by 8
uint32_t dti_msg_id(dti_pid_t pid, unit32_t node);

// OLD
// #define dti_msg_id(pid, node)  ((((uint32_t)(pid)) << 8) | ((uint32_t)(node) & 0xFF))
// #define dti_get_packet(id)  ((dti_pid_t)(((id) >> 8)))
// #define dti_get_node(id) ((dti_node_t)((id) & 0xFF))

/* Plain Message */
typedef struct {
    uint32_t id;
    uint8_t data[8];
} dti_msg_t;



// use a predefined packetID, require the node (destination) to be parsed when sending a messsing


/* COMMANDS TO INVERTER */
dti_msg_t Compose_C1(dti_node_t node, int32_t ac_curr);
dti_msg_t Compose_C2(dti_node_t node, int32_t brake_curr);
dti_msg_t Compose_C3(dti_node_t node, int32_t erpm);
dti_msg_t Compose_C4(dti_node_t node, int32_t target_pos)
dti_msg_t Compose_C5(dti_node_t node, int32_t rel_ac_curr)
dti_msg_t Compose_C6(dti_node_t node, int32_t rel_brake_curr)
// Copose 7
dti_msg_t Compose_C8(dti_node_t node, int32_t max_ac_curr)
dti_msg_t Compose_C9(dti_node_t node, int32_t max_brake_curr)
dti_msg_t Compose_C10(dti_node_t node, int32_t max_dc_curr)
dti_msg_t Compose_C11(dti_node_t node, int32_t max_dc_brake_curr)
dti_msg_t Compose_C12(dti_node_t node, int16_t driveEnableStat)


/* TRANSMITTED BY INVERTER */



#endif /* INC_CAN_DTI_H_ */