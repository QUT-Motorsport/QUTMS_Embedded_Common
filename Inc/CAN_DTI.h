/*
 * CAN_DTI.h
 *
 *  Created on: July 4, 2026
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
    DTI_PID_ERPM_DUTY_VOLT = 0x20,
    DTI_PID_Currents = 0x21,
    DTI_PID_SET_EPRM = 0x03,
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


/* Plain Message */
typedef struct {
    uint32_t id;
    uint8_t data[8];
} dti_msg_t;

/* ID */

// Extended CAN ID = Packet ID (bits 28:8) | Node ID (bits 7:0) -> shift the packet ID by 8
#define dti_msg_id(pid, node)  ((((uint32_t)(pid)) << 8) | ((uint32_t)(node) & 0xFF))
#define dti_get_packet(id)  ((dti_pid_t)(((id) >> 8)))
#define dti_get_node(id) ((dti_node_t)((id) & 0xFF))


/* COMMANDS TO INVERTER */
dti_msg_t Compose_setERPM(dti_node_t node, int32_t erpm);


/* TRANSMITTED BY INVERTER */



#endif /* INC_CAN_DTI_H_ */