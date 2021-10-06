/*
 * object_dictionary.h
 *
 *  Created on: 6 Oct. 2021
 *      Author: Calvin
 */

#ifndef COMMON_INC_OBJ_DIC_H_
#define COMMON_INC_OBJ_DIC_H_

#include <stdbool.h>
#include <stdint.h>

#define OBJECT_COUNT 16

enum OD_MSG_TYPE {
	OD_MSG_GET = 0,
	OD_MSG_SET = 1,
	OD_MSG_VALUE = 2
};

typedef uint16_t OD_type_t;

typedef struct obj_dict {
	OD_type_t variables[OBJECT_COUNT];
	bool update_flag[OBJECT_COUNT];
	bool init;
} obj_dict_t;


void OD_init(obj_dict_t *obj_dict);

// interprets CAN message as either get value
bool OD_handleCAN(obj_dict_t *obj_dict, uint8_t data[8], uint8_t *output);

// generates body for CAN message
void OD_generateCAN(obj_dict_t *obj_dict, uint8_t type, uint8_t index, OD_type_t value, uint8_t *output);

// retrieves value from object dictionary
OD_type_t OD_getValue(obj_dict_t *obj_dict, uint8_t index, bool clearFlag);

// sets value in object dictionary
OD_type_t OD_setValue(obj_dict_t *obj_dict, uint8_t index, OD_type_t value);

// gets the updated flag status of an index
bool OD_flagStatus(obj_dict_t *obj_dict, uint8_t index);



#endif /* COMMON_INC_OBJ_DIC_H_ */
