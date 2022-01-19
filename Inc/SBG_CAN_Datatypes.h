#ifndef COMMON_INC_SBG_CAN_DATATYPES_H_
#define COMMON_INC_SBG_CAN_DATATYPES_H_

typedef enum _SBG_CAN_PACKET_ID
{
    SBG_ECAN_MSG_STATUS_01_ID = 0x100,
    SBG_ECAN_MSG_STATUS_02_ID = 0x101,
    SBG_ECAN_MSG_STATUS_03_ID = 0x102,
    SBG_ECAN_MSG_UTC_0_ID = 0x110,
    SBG_ECAN_MSG_UTC_1_ID = 0x111,
    SBG_ECAN_MSG_IMU_INFO_ID = 0x120,
    SBG_ECAN_MSG_IMU_ACCEL_ID = 0x121,
    SBG_ECAN_MSG_IMU_GYRO_ID = 0x122,
    SBG_ECAN_MSG_IMU_DELTA_VEL_ID = 0x123,
    SBG_ECAN_MSG_IMU_DELTA_ANGLE_ID = 0x124,
    SBG_ECAN_MSG_EKF_INFO_ID = 0x130,
    SBG_ECAN_MSG_EKF_QUAT_ID = 0x131,
    SBG_ECAN_MSG_EKF_EULER_ID = 0x132,
    SBG_ECAN_MSG_EKF_ORIENTATION_ACC_ID = 0x133,
    SBG_ECAN_MSG_EKF_POS_ID = 0x134,
    SBG_ECAN_MSG_EKF_ALTITUDE_ID = 0x135,
    SBG_ECAN_MSG_EKF_POS_ACC_ID = 0x136,
    SBG_ECAN_MSG_EKF_VEL_NED_ID = 0x137,
    SBG_ECAN_MSG_EKF_VEL_NED_ACC_ID = 0x138,
    SBG_ECAN_MSG_EKF_VEL_BODY_ID = 0x139,
    SBG_ECAN_MSG_AUTO_TRACK_SLIP_CURV_ID = 0x220,
    SBG_ECAN_MSG_MAG_0_ID = 0x150,
    SBG_ECAN_MSG_MAG_1_ID = 0x151,
    SBG_ECAN_MSG_MAG_2_ID = 0x152,
    SBG_ECAN_MSG_ODO_INFO_ID = 0x160,
    SBG_ECAN_MSG_ODO_VEL_ID = 0x161,
    SBG_ECAN_MSG_AIR_DATA_INFO_ID = 0x162,
    SBG_ECAN_MSG_AIR_DATA_ALTITUDE_ID = 0x163,
    SBG_ECAN_MSG_AIR_DATA_AIRSPEED_ID = 0x164,
    SBG_ECAN_MSG_GPS1_VEL_INFO_ID = 0x170,
    SBG_ECAN_MSG_GPS1_VEL_ID = 0x171,
    SBG_ECAN_MSG_GPS1_VEL_ACC_ID = 0x172,
    SBG_ECAN_MSG_GPS1_COURSE_ID = 0x173,
    SBG_ECAN_MSG_GPS1_POS_INFO_ID = 0x174,
    SBG_ECAN_MSG_GPS1_POS_ID = 0x175,
    SBG_ECAN_MSG_GPS1_POS_ALT_ID = 0x176,
    SBG_ECAN_MSG_GPS1_POS_ACC_ID = 0x177,
    SBG_ECAN_MSG_GPS1_HDT_INFO_ID = 0x178,
    SBG_ECAN_MSG_GPS1_HDT_ID = 0x179,
    SBG_ECAN_MSG_EVEN_INFO_A_ID = 0x200,
    SBG_ECAN_MSG_EVENT_INFO_B_ID = 0x202,
    SBG_ECAN_MSG_EVENT_INFO_C_ID = 0x204,
    SBG_ECAN_MSG_EVENT_INFO_D_ID = 0x206,
    SBG_ECAN_MSG_EVENT_INFO_E_ID = 0x207,
    SBG_ECAN_MSG_EVEN_TIME_A_ID = 0x201,
    SBG_ECAN_MSG_EVEN_TIME_B_ID = 0x203,
    SBG_ECAN_MSG_EVENT_TIME_C_ID = 0x205,
    SBG_ECAN_MSG_EVEN_TIME_D_ID = 0x207,
    SBG_ECAN_MSG_EVEN_TIME_E_ID = 0x209,
} SBG_CAN_PACKET_ID;

#endif
