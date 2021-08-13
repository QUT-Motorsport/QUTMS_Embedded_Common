/**
 ******************************************************************************
 * @file General_Sensor_CAN_Messages.h
 * @brief General Sensor CAN Messages
 ******************************************************************************
 */

#ifndef INC_GENERAL_SENSOR_CAN_MESSAGES_H_
#define INC_GENERAL_SENSOR_CAN_MESSAGES_H_

#include "stdbool.h"
#include <stdlib.h>
#include "QUTMS_can.h"

/**
 * @brief General Sensor Board Sensor IDs
 */

typedef struct General_Sensor_LinearPot_t
{
    uint32_t id; /**< CAN Packet ID */
    uint8_t data[5]; /**< Data */
}  General_Sensor_LinearPot_t;

/**
 * @brief General Sensor Linear Potentiometer Composer
 * @param potNum The potentiometer number
 * @param boardNum The corresponding board number
 * @param travel The linear potentiometer reading corresponding to travel
 * @return The composed potentiometer travel packet
 */ 
General_Sensor_LinearPot_t Compose_General_Sensor_Travel (uint8_t boardNum, uint16_t travel1, uint16_t travel2);

/**
 * @brief General Sensor Board Travel Parser
 * @param packet The General_Sensor_RadiatorTemp_t packet to parse
 * @param potNum The potentiometer number
 * @param boardNum The corresponding board number
 * @param travel The linear potentiometer reading corresponding to travel
 */ 
void Parse_General_Sensor_Travel(uint8_t *data, uint8_t *boardNum, uint16_t *travel1, uint16_t *travel2);

typedef struct General_Sensor_GearboxTemp_t
{
    uint32_t id; /**< CAN Packet ID */
    uint8_t data[2]; /**< Data */
}  General_Sensor_GearboxTemp_t;

/**
 * @brief General Sensor Gearbox Temp Composer
 * @param gearboxNum The gearbox number 
 * @param boardNum The corresponding board number
 * @param temperature The temperature reading
 * @return The composed gearbox temperature packet
 */ 
General_Sensor_GearboxTemp_t Compose_General_Sensor_GearboxTemp (uint8_t gearboxNum, uint8_t boardNum, uint8_t temperature);

/**
 * @brief General Sensor Board Travel Parser
 * @param packet The General_Sensor_RadiatorTemp_t packet to parse
 * @param gearboxNum The gearbox number 
 * @param boardNum The corresponding board number
 * @param temperature The temperature reading
 */ 
General_Sensor_GearboxTemp_t Parse_General_Sensor_GearboxTemp(uint8_t* data, uint8_t* gearboxNum, uint8_t* boardNum, uint8_t* temperature);

typedef struct General_Sensor_RadiatorTemp_t
{
    uint32_t id; /**< CAN Packet ID */
    uint8_t data[2]; /**< Data */
}  General_Sensor_RadiatorTemp_t;

/**
 * @brief General Sensor Gearbox Temp Composer
 * @param radNum The radiator being sensed (1 or 2)
 * @param boardNum The corresponding board number
 * @param temperature The temperature reading
 * @return The composed radiator temperature packet
 */ 
General_Sensor_GearboxTemp_t Compose_General_Sensor_RadiatorTemp (uint8_t radNum, uint8_t boardNum, uint8_t temperature);

/**
 * @brief General Sensor Board Travel Parser
 * @param packet The General_Sensor_RadiatorTemp_t packet to parse
 * @param radNum The radiator being sensed (1 or 2)
 * @param boardNum The corresponding board number
 * @param temperature The temperature reading
 */ 
General_Sensor_GearboxTemp_t Parse_General_Sensor_RadiatorTemp(uint8_t* data, uint8_t* radNum, uint8_t* boardNum, uint8_t* temperature);

#endif /* INC_GENERAL_SENSOR_CAN_MESSAGES_H_ */
