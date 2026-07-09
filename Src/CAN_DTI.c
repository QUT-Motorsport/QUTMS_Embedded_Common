/*
 * CAN_DTI.c
 *
 *  Created on: July 4, 2026
 *      Author: Chloe
 */

#include <CAN_DTI.h>

#ifdef QUTMS_CAN_DTI

// Construct an ID 
dti_msg_t Compose_setERPM(dti_node_t node, int32_t erpm)
{
    dti_msg_t msg;

    msg.id = dti_msg_id(DTI_PID_SET_EPRM, node);

    msg.data[0] = (erpm >> 24);
    msg.data[1] = (erpm >> 16);
    msg.data[2] = (erpm >> 8);
    msg.data[3] = eprm;

    msg.data[4] = 0;
    msg.data[5] = 0;
    msg.data[6] = 0;
    msg.data[7] = 0;

    return msg;
}

#endif