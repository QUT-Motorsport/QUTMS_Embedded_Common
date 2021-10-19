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
	*min = data[4];
	*sec = data[5];
	*micro_sec = (uint16_t)((data[6] << 8) | (data[7]));
}

SBG_ECAN_MSG_IMU_INFO_t Compose_SBG_ECAN_MSG_IMU_INFO(uint32_t id, uint32_t time_stamp, uint16_t imu_status, uint16_t temperature)
{
	SBG_ECAN_MSG_IMU_INFO_t msg;
	msg.id = id;

	// time_stamp
	msg.data[0] = (time_stamp >> 24) & 0xFF;
	msg.data[1] = (time_stamp >> 16) & 0xFF;
	msg.data[2] = (time_stamp >> 8) & 0xFF;
	msg.data[3] = (time_stamp >> 0) & 0xFF;

	// imu_status
	msg.data[4] = (imu_status >> 8) & 0xFF;
	msg.data[5] = (imu_status >> 0) & 0xFF;

	// temperature
	msg.data[6] = (temperature >> 8) & 0xFF;
	msg.data[7] = (temperature >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_IMU_INFO(uint8_t* data, uint32_t* id, uint32_t* time_stamp, uint16_t* imu_status, int16_t* temperature)
{
	*id = SBG_ECAN_MSG_IMU_INFO_ID;
	*time_stamp = (uint32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
	*imu_status = (uint16_t)((data[4] << 8) | (data[5]));
	*temperature = (uint16_t)((data[6] << 8) | (data[7]));
}

SBG_ECAN_MSG_IMU_ACCEL_t Compose_SBG_ECAN_MSG_IMU_ACCEL(uint32_t id, int16_t accel_x, int16_t accel_y, int16_t accel_z)
{
	SBG_ECAN_MSG_IMU_ACCEL_t msg;
	msg.id = id;

	// accel_x
	msg.data[0] = (accel_x >> 8) & 0xFF;
	msg.data[1] = (accel_x >> 0) & 0xFF;

	// accel_y
	msg.data[2] = (accel_y >> 8) & 0xFF;
	msg.data[3] = (accel_y >> 0) & 0xFF;

	// accel_z
	msg.data[4] = (accel_z >> 8) & 0xFF;
	msg.data[6] = (accel_z >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_IMU_ACCEL(uint8_t* data, uint32_t* id, int16_t* accel_x, int16_t* accel_y, int16_t* accel_z)
{
	*id = SBG_ECAN_MSG_IMU_ACCEL_ID;
	*accel_x = (uint16_t)((data[0] << 8) | (data[1]));
	*accel_y = (uint16_t)((data[2] << 8) | (data[3]));
	*accel_z = (uint16_t)((data[4] << 8) | (data[5]));
}

SBG_ECAN_MSG_IMU_GYRO_t Compose_SBG_ECAN_MSG_IMU_GYRO(uint32_t id, int16_t gyro_x, int16_t gyro_y, int16_t gyro_z)
{
	SBG_ECAN_MSG_IMU_GYRO_t msg;
	msg.id = id;

	// gyro_x
	msg.data[0] = (gyro_x >> 8) & 0xFF;
	msg.data[1] = (gyro_x >> 0) & 0xFF;

	// gyro_y
	msg.data[2] = (gyro_y >> 8) & 0xFF;
	msg.data[3] = (gyro_y >> 0) & 0xFF;

	// gyro_z
	msg.data[4] = (gyro_z >> 8) & 0xFF;
	msg.data[5] = (gyro_z >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_IMU_GYRO(uint8_t* data, uint32_t* id, int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z)
{
	*id = SBG_ECAN_MSG_IMU_GYRO_ID;
	*gyro_x = (int16_t)((data[0] << 8) | (data[1]));
	*gyro_y = (int16_t)((data[2] << 8) | (data[3]));
	*gyro_z = (int16_t)((data[4] << 8) | (data[5]));
}

SBG_ECAN_MSG_IMU_DELTA_VEL_t Compose_SBG_ECAN_MSG_IMU_DELTA_VEL(uint32_t id, int16_t delta_vel_x, int16_t delta_vel_y, int16_t delta_vel_z)
{
	SBG_ECAN_MSG_IMU_DELTA_VEL_t msg;
	msg.id = id;

	// delta_vel_x
	msg.data[0] = (delta_vel_x >> 8) & 0xFF;
	msg.data[1] = (delta_vel_x >> 0) & 0xFF;

	// delta_vel_y
	msg.data[2] = (delta_vel_y >> 8) & 0xFF;
	msg.data[3] = (delta_vel_y >> 0) & 0xFF;

	// delta_vel_z
	msg.data[4] = (delta_vel_z >> 8) & 0xFF;
	msg.data[5] = (delta_vel_z >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_IMU_DELTA_VEL(uint8_t* data, uint32_t* id, int16_t* delta_vel_x, int16_t* delta_vel_y, int16_t* delta_vel_z)
{
	*id = SBG_ECAN_MSG_IMU_DELTA_VEL_ID;
	*delta_vel_x = (int16_t)((data[0] << 8) | (data[1]));
	*delta_vel_y = (int16_t)((data[2] << 8) | (data[3]));
	*delta_vel_z = (int16_t)((data[4] << 8) | (data[5]));
}

SBG_ECAN_MSG_IMU_DELTA_ANGLE_t Compose_SBG_ECAN_MSG_IMU_DELTA_ANGLE(uint32_t id, int16_t delta_angle_x, int16_t delta_angle_y, int16_t delta_angle_z)
{
	SBG_ECAN_MSG_IMU_DELTA_ANGLE_t msg;
	msg.id = id;

	// delta_angle_x
	msg.data[0] = (delta_angle_x >> 8) & 0xFF;
	msg.data[1] = (delta_angle_x >> 0) & 0xFF;

	// delta_angle_y
	msg.data[2] = (delta_angle_y >> 8) & 0xFF;
	msg.data[3] = (delta_angle_y >> 0) & 0xFF;

	// delta_angle_z
	msg.data[4] = (delta_angle_z >> 8) & 0xFF;
	msg.data[5] = (delta_angle_z >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_IMU_DELTA_ANGLE(uint8_t* data, uint32_t* id, int16_t* delta_angle_x, int16_t* delta_angle_y, int16_t* delta_angle_z)
{
	*id = SBG_ECAN_MSG_IMU_DELTA_ANGLE_ID;
	*delta_angle_x = (int16_t)((data[0] << 8) | (data[1]));
	*delta_angle_y = (int16_t)((data[2] << 8) | (data[3]));
	*delta_angle_z = (int16_t)((data[4] << 8) | (data[5]));
}

SBG_ECAN_MSG_EKF_INFO_t Compose_SBG_ECAN_MSG_EKF_INFO(uint32_t id, uint32_t time_stamp)
{
	SBG_ECAN_MSG_EKF_INFO_t msg;
	msg.id = id;

	// time_stamp
	msg.data[0] = (time_stamp >> 24) & 0xFF;
	msg.data[1] = (time_stamp >> 16) & 0xFF;
	msg.data[2] = (time_stamp >> 8) & 0xFF;
	msg.data[3] = (time_stamp >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_EKF_INFO(uint8_t* data, uint32_t* id, uint32_t* time_stamp)
{
	*id = SBG_ECAN_MSG_EKF_INFO_ID;
	*time_stamp = (uint32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
}

SBG_ECAN_MSG_EKF_QUAT_t Compose_SBG_ECAN_MSG_EKF_QUAT(uint32_t id, int16_t q0, int16_t q1, int16_t q2, int16_t q3)
{
	SBG_ECAN_MSG_EKF_QUAT_t msg;
	msg.id = id;

	// q0
	msg.data[0] = (q0 >> 8) & 0xFF;
	msg.data[1] = (q0 >> 0) & 0xFF;

	// q1
	msg.data[2] = (q1>> 8) & 0xFF;
	msg.data[3] = (q1 >> 0) & 0xFF;

	// q2
	msg.data[4] = (q2>> 8) & 0xFF;
	msg.data[5] = (q2 >> 0) & 0xFF;

	// q3
	msg.data[6] = (q3>> 8) & 0xFF;
	msg.data[7] = (q3 >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_EKF_QUAT(uint8_t* data, uint32_t* id, int16_t* q0, int16_t* q1, int16_t* q2, int16_t* q3)
{
	*id = SBG_ECAN_MSG_EKF_QUAT_ID;
	*q0 = (int16_t)((data[0] << 8) | data[1]);
	*q1 = (int16_t)((data[2] << 8) | data[3]);
	*q2 = (int16_t)((data[4] << 8) | data[5]);
	*q3 = (int16_t)((data[6] << 8) | data[7]);
}

SBG_ECAN_MSG_EKF_EULER_t Compose_SBG_ECAN_MSG_EKF_EULER(uint32_t id, int16_t roll, int16_t pitch, int16_t yaw)
{
	SBG_ECAN_MSG_EKF_EULER_t msg;
	msg.id = id;

	// roll
	msg.data[0] = (roll >> 8) & 0xFF;
	msg.data[1] = (roll >> 0) & 0xFF;

	// pitch
	msg.data[2] = (pitch >> 8) & 0xFF;
	msg.data[3] = (pitch >> 0) & 0xFF;

	// yaw
	msg.data[4] = (yaw >> 8) & 0xFF;
	msg.data[5] = (yaw >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_EKF_EULER(uint8_t* data, uint32_t* id, int16_t* roll, int16_t* pitch, int16_t* yaw)
{
	*id = SBG_ECAN_MSG_EKF_EULER_ID;
	*roll = (int16_t)((data[0] << 8) | (data[1]));
	*pitch = (int16_t)((data[2] << 8) | (data[3]));
	*yaw = (int16_t)((data[4] << 8) | (data[5]));
}

SBG_ECAN_MSG_EKF_ORIENTATION_ACC_t Compose_SBG_ECAN_MSG_EKF_ORIENTATION_ACC(uint32_t id, int16_t roll_acc, int16_t pitch_acc, int16_t yaw_acc)
{
	SBG_ECAN_MSG_EKF_ORIENTATION_ACC_t msg;
	msg.id = id;

	// roll_acc
	msg.data[0] = (roll_acc >> 8) & 0xFF;
	msg.data[1] = (roll_acc >> 0) & 0xFF;

	// pitch_acc
	msg.data[2] = (pitch_acc >> 8) & 0xFF;
	msg.data[3] = (pitch_acc >> 0) & 0xFF;

	// yaw_acc
	msg.data[4] = (yaw_acc >> 8) & 0xFF;
	msg.data[5] = (yaw_acc >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_EKF_ORIENTATION_ACC(uint8_t* data, uint32_t* id, int16_t* roll_acc, int16_t* pitch_acc, int16_t* yaw_acc)
{
	*id = SBG_ECAN_MSG_EKF_ORIENTATION_ACC_ID;
	*roll_acc = (int16_t)((data[0] << 8) | data[1]);
	*pitch_acc = (int16_t)((data[2] << 8) | data[3]);
	*yaw_acc = (int16_t)((data[4] << 8) | data[5]);
}

SBG_ECAN_MSG_EKF_POS_t Compose_SBG_ECAN_MSG_EKF_POS(uint32_t id, int32_t latitude, int32_t longitude)
{
	SBG_ECAN_MSG_EKF_POS_t msg;
	msg.id = id;

	// latitude
	msg.data[0] = (latitude >> 24) & 0xFF;
	msg.data[1] = (latitude >> 16) & 0xFF;
	msg.data[2] = (latitude >> 8) & 0xFF;
	msg.data[3] = (latitude >> 0) & 0xFF;

	// longitude
	msg.data[4] = (longitude >> 24) & 0xFF;
	msg.data[5] = (longitude >> 16) & 0xFF;
	msg.data[6] = (longitude >> 8) & 0xFF;
	msg.data[7] = (longitude >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_EKF_POS(uint8_t* data, uint32_t* id, int32_t* latitude, int32_t* longitude)
{
	*id = SBG_ECAN_MSG_EKF_POS_ID;
	*latitude = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
	*longitude = (int32_t)((data[4] << 24) | (data[5] << 16) | (data[6] << 8) | (data[7]));
}

SBG_ECAN_MSG_EKF_ALTITUDE_t Compose_SBG_ECAN_MSG_EKF_ALTITUDE(uint32_t id, int32_t altitude, int16_t undulation)
{
	SBG_ECAN_MSG_EKF_ALTITUDE_t msg;
	msg.id = id;

	// altitude
	msg.data[0] = (altitude >> 24) & 0xFF;
	msg.data[1] = (altitude >> 16) & 0xFF;
	msg.data[2] = (altitude >> 8) & 0xFF;
	msg.data[3] = (altitude >> 0) & 0xFF;

	// undulation
	msg.data[4] = (altitude >> 8) & 0xFF;
	msg.data[5] = (altitude >> 0) & 0xFF;

	return msg;
}

void Parse_SBG_ECAN_MSG_EKF_ALTITUDE(uint8_t* data, uint32_t* id, int32_t* altitude, int16_t* undulation)
{
	*id = SBG_ECAN_MSG_EKF_ALTITUDE_ID;
	*altitude = (int32_t)((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | (data[3]));
	*undulation = (int16_t)((data[4] << 8) | (data[5]));
}
