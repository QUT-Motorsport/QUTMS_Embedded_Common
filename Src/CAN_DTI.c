/*
 * CAN_DTI.c
 *
 *  Created in: 2026
 *  Author: Chloe B
 */

#include <CAN_DTI.h>

#ifdef QUTMS_CAN_DTI

// DTI 
uint32_t dti_msg_id(dti_pid_t pid, uint32_t node) {
	uint32_t id = ((((uint32_t)(pid)) << 8) | ((uint32_t)(node) & 0xFF));
	return id;
}

/* COMPOSE CONTROL MESSAGES*/

// Set AC Current
dti_msg_t Compose_C1(dti_node_t node, int32_t ac_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C1, node);
    // 0-1 AC Current
    msg.data[0] = (ac_curr >> 8);
    msg.data[1] = ac_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set Brake Current
dti_msg_t Compose_C2(dti_node_t node, int32_t brake_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C2, node);
    // 0-1 Brake Current
    msg.data[0] = (brake_curr >> 8);
    msg.data[1] = brake_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// SET EPRM
dti_msg_t Compose_C3(dti_node_t node, int32_t erpm)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C3, node);
    // Target EPRM
    msg.data[0] = (erpm >> 24);
    msg.data[1] = (erpm >> 16);
    msg.data[2] = (erpm >> 8);
    msg.data[3] = eprm;
    // 4-7 not used
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set position
dti_msg_t Compose_C4(dti_node_t node, int32_t target_pos)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C4, node);
    // 0-1 Target Position
    msg.data[0] = (target_pos >> 8);
    msg.data[1] = target_pos;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set relative ac curr
dti_msg_t Compose_C5(dti_node_t node, int32_t rel_ac_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C5, node);
    // 0-1 Target relative AC Current
    msg.data[0] = (rel_ac_curr >> 8);
    msg.data[1] = rel_ac_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set relative brake curr
dti_msg_t Compose_C6(dti_node_t node, int32_t rel_brake_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C6, node);
    // 0-1 Target relative brake AC Current
    msg.data[0] = (rel_ac_curr >> 8);
    msg.data[1] = rel_ac_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// COMPOSE C7

// Set Max AC Cur
dti_msg_t Compose_C8(dti_node_t node, int32_t max_ac_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C8, node);
    // 0-1 Maximum AC Current
    msg.data[0] = (max_ac_curr >> 8);
    msg.data[1] = max_ac_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set max brake curr
dti_msg_t Compose_C9(dti_node_t node, int32_t max_brake_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C9, node);
    // 0-1 Target maximum brake AC Current
    msg.data[0] = (max_brake_curr >> 8);
    msg.data[1] = max_brake_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set max DC curr
dti_msg_t Compose_C10(dti_node_t node, int32_t max_dc_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C10, node);
    // 0-1 Target maximum brake AC Current
    msg.data[0] = (max_dc_curr >> 8);
    msg.data[1] = max_dc_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Set max DC brake curr
dti_msg_t Compose_C11(dti_node_t node, int32_t max_dc_brake_curr)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C11, node);
    // 0-1 Target maximum brake AC Current
    msg.data[0] = (max_dc_brake_curr >> 8);
    msg.data[1] = max_dc_brake_curr;
    // 2-7 not used
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

// Drive enable
dti_msg_t Compose_C12(dti_node_t node, int16_t driveEnableStat)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_C12, node);
    // 0-1 drive enabled status
    msg.data[0] = driveEnableStat;
    
    // 2-7 not used
    msg.data[1] = 0;
    msg.data[2] = 0;
    msg.data[3] = 0;
    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

#endif