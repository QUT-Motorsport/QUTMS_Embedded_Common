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
dti_msg_t Compose_C1(dti_node_t node, int16_t ac_curr)
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
dti_msg_t Compose_C2(dti_node_t node, int16_t brake_curr)
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
dti_msg_t Compose_C4(dti_node_t node, int16_t target_pos)
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
dti_msg_t Compose_C5(dti_node_t node, int16_t rel_ac_curr)
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
dti_msg_t Compose_C6(dti_node_t node, int16_t rel_brake_curr)
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
dti_msg_t Compose_C8(dti_node_t node, int16_t max_ac_curr)
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
dti_msg_t Compose_C9(dti_node_t node, int16_t max_brake_curr)
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
dti_msg_t Compose_C10(dti_node_t node, int16_t max_dc_curr)
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
dti_msg_t Compose_C11(dti_node_t node, int16_t max_dc_brake_curr)
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

/* PARSE STATUS MESSAGES */

/*

data[?];
data[?] | (data[?] << 8);
    */

// CONTROL STATUS 
void Parse_S1(uint8_t data[8], int8_t *controlMode, int16_t *trargetIq, int16_t *motorPos, int8_t *isMotStill) {
    *controlMode = data[0];
    *trargetIq = data[1] | (data[2] << 8);
    *motorPos = data[3] | (data[4] << 8);
    *isMotStill = data[5];
}
//ERPM_DUTY_VOLT
void Parse_S2(uint8_t data[8], int32_t *EPRM, int16_t *dutyCycle, int16_t *inputVolt){
    *EPRM = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 32);
    *dutyCycle = data[4] | (data[5] << 8);
    *inputVolt = data[6] | (data[7] << 8);
}
// CURRENTS_READ 
void Parse_S3(uint8_t data[8], int16_t *ACcurr, int16_t *DCcurr) {
    *ACcurr = data[0] | (data[1] << 8);
    *DCcurr = data[2] | (data[3] << 8);
}
// TEMPS_FAULT
void Parse_S4(uint8_t data[8], int16_t *invertTemp, int16_t *motTemp, int16_t *faultCode){
    *invertTemp = data[0] | (data[1] << 8);
    *motTemp = data[2] | (data[3] << 8);
    *faultCode = data[4];
}
// FOC
void Parse_S5(uint8_t data[8], int32_t *Id, int32_t *Iq){
    *Id = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 32);
    *Iq = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 32);

}
// CONTROL_DATA
void Parse_S6(uint8_t data[8], int8_t *throttleSig, int8_t *brakeSig, int8_t *digIn1, 
    int8_t *digIn2, int8_t *digIn3, int8_t *digIn4, int8_t *digOut1, int8_t *digOut2, int8_t *digOut3, 
    int8_t *digOut4, int8_t *driveEnable, int8_t *capTempLim, int8_t *DCcurrLim, int8_t *driveEnableLim, 
    int8_t *IGBTaccelLim, int8_t *IGBTtempLim, int8_t *inputVoltLim, int8_t *motAccTempLim, int8_t *motTempLim,
    int8_t *RPMminLim, int8_t *RPMmaxLim, int8_t *powerLim, int8_t *CANver) {
    *throttleSig = 
    *brakeSig =
    *digIn1 =
    *digIn2 =   
    *digIn3 = 
    *digIn4 =
    *digOut1 =
    *digOut2 =   
    *digOut3 = 
    *digOut4 =
    *driveEnable =
    *capTempLim = 
    *DCcurrLim = 
    *driveEnableLim =
    *IGBTaccelLim =
    *IGBTtempLim = 
    *inputVoltLim =
    *motAccTempLim = 
    *motTempLim = 
    *RPMminLim =
    *RPMmaxLim =
    *powerLim = 
    *CANver = 
}
// AC_SET
void Parse_S7(uint8_t data[8], int16_t *maxACcur, int16_t *availMaxAC, int16_t minACcurr, int16_t availMinAC){
    *maxACcurr = data[0] | (data[1] << 8);
    *availMaxAC = data[2] | (data[3] << 8);
    *minACcurr = data[4] | (data[5] << 8);
    *availMinAC = data[6] | (data[6] << 8);
}
// DC_SET
void Parse_S8(uint8_t data[8], int16_t *maxDCcur, int16_t *availMaxDC, int16_t minDCcurr, int16_t availMinDC){
    *maxDCcurr = data[0] | (data[1] << 8);
    *availMaxDC = data[2] | (data[3] << 8);
    *minDCcurr = data[4] | (data[5] << 8);
    *availMinDC = data[6] | (data[6] << 8);
}

#endif