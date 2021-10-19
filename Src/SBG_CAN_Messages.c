#include "SBG_CAN_Messages.h"

SBG_ECAN_MSG_STATUS_01_t Compose_SBG_ECAN_MSG_STATUS_01(uint32_t id, uint32_t time_stamp, uint16_t general_status, uint16_t clock_status)
{
    SBG_ECAN_MSG_STATUS_01_t msg;
    msg.id = id;
    // time_stamp
    msg.data[0] = (time_stamp >> 24) & 0xFF;
    msg.data[1] = (time_stamp >> 16) & 0xFF;
    msg.data[2] = (time_stamp >> 8) & 0xFF;
    msg.data[3] = (time_stamp >> 0) & 0xFF;

    // general_status
    msg.data[4] = (general_status >> 8) & 0xFF;
    msg.data[5] = (general_status >> 0) & 0xFF;

    // clock_status
    msg.data[6] = (general_status >> 8) & 0xFF;
    msg.data[7] = (general_status >> 0) & 0xFF;

    return msg;
}

void Parse_SBG_ECAN_MSG_STATUS_01(uint8_t* data, uint32_t* id, uint32_t* time_stamp, uint16_t* general_status, uint16_t* clock_status)
{
    *id = SBG_ECAN_MSG_STATUS_01_ID;
    *time_stamp = (uint32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
    *general_status = (uint16_t)((data[4] << 8) | (data[5]));
    *clock_status = (uint16_t)((data[6] << 8) | (data[7]));
}

SBG_ECAN_MSG_STATUS_02_t Compose_SBG_ECAN_MSG_STATUS_02(uint32_t id, uint32_t com_status, uint32_t aiding_status)
{
    SBG_ECAN_MSG_STATUS_02_t msg;
    msg.id = id;

    // com_status
    msg.data[0] = (com_status >> 24) & 0xFF;
    msg.data[1] = (com_status >> 16) & 0xFF;
    msg.data[2] = (com_status >> 8) & 0xFF;
    msg.data[3] = (com_status >> 0) & 0xFF;

    // aiding_status
    msg.data[4] = (aiding_status >> 24) & 0xFF;
    msg.data[5] = (aiding_status >> 16) & 0xFF;
    msg.data[6] = (aiding_status >> 8) & 0xFF;
    msg.data[7] = (aiding_status >> 0) & 0xFF;

    return msg;
}

void Parse_SBG_ECAN_MSG_STATUS_02(uint8_t* data, uint32_t* id, uint32_t* com_status, uint32_t* aiding_status)
{
    *id = SBG_ECAN_MSG_STATUS_02_ID;
    *com_status = (uint32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
    *aiding_status = (uint32_t)((data[4] << 25) | (data[5] << 16) | (data[6] << 8) | (data[7]));
}

SBG_ECAN_MSG_STATUS_03_t Compose_SBG_ECAN_MSG_STATUS_03(uint32_t id, uint32_t solution_status, uint16_t heave_status)
{
    SBG_ECAN_MSG_STATUS_03_t msg;
    msg.id = id;

    // solution_status
    msg.data[0] = (solution_status >> 24) & 0xFF;
    msg.data[1] = (solution_status >> 16) & 0xFF;
    msg.data[2] = (solution_status >> 8) & 0xFF;
    msg.data[3] = (solution_status >> 0) & 0xFF;

    // heave_status
    msg.data[4] = (heave_status >> 8) & 0xFF;
    msg.data[5] = (heave_status >> 0) & 0xFF;

    return msg;
}

void Parse_SBG_ECAN_MSG_STATUS_03(uint8_t* data, uint32_t* id, uint32_t* solution_status, uint16_t* heave_status)
{
	*id = SBG_ECAN_MSG_STATUS_03_ID;
	*solution_status = (uint32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
	*heave_status = (uint16_t)((data[4] << 8) | (data[5]));
}

SBG_ECAN_MSG_UTC_0_t Compose_SBG_ECAN_MSG_UTC_0(uint32_t id, uint32_t time_stamp, uint32_t gps_tow)
{
	SBG_ECAN_MSG_UTC_0_t msg;
	msg.id = id;

	// time_stamp
	msg.data[0] = (time_stamp >> 24) & 0xFF;
	msg.data[1] = (time_stamp >> 16) & 0xFF;
	msg.data[2] = (time_stamp >> 8) & 0xFF;
	msg.data[3] = (time_stamp >> 0) & 0xFF;

	// gps_tow
	msg.data[0] = (gps_tow >> 24) & 0xFF;
	msg.data[1] = (gps_tow >> 16) & 0xFF;
	msg.data[2] = (gps_tow >> 8) & 0xFF;
	msg.data[3] = (gps_tow >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_UTC_0(uint8_t* data, uint32_t* id, uint32_t* time_stamp, uint32_t* gps_tow)
{
	*id = SBG_ECAN_MSG_UTC_0_ID;
	*time_stamp = (uint32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
	*gps_tow = (uint32_t)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | (data[7]));
}

SBG_ECAN_MSG_UTC_1_t Compose_SBG_ECAN_MSG_UTC_1(uint32_t id, uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec, uint16_t micro_sec)
{
	SBG_ECAN_MSG_UTC_1_t msg;
	msg.id = id;

	msg.data[0] = year;
	msg.data[1] = month;
	msg.data[2] = day;
	msg.data[3] = hour;
	msg.data[4] = min;
	msg.data[5] = sec;
	msg.data[6] = (micro_sec >> 8) & 0xFF;
	msg.data[7] = (micro_sec >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_UTC_1(uint8_t* data, uint32_t* id, uint8_t* year, uint8_t* month, uint8_t* day, uint8_t* hour, uint8_t* min, uint8_t* sec, uint16_t* micro_sec)
{
	*id = SBG_ECAN_MSG_UTC_1_ID;
	*year = data[0];
	*month = data[1];
	*day = data[2];
	*hour = data[3];
	*minute = data[4];
	*second = data[5];
	*micro_sec = (uint16_t)((data[6] << 8) | (data[7]));
}
