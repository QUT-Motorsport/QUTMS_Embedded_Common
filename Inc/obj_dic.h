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
	OD_MSG_GET = 0, OD_MSG_SET = 1, OD_MSG_VALUE = 2
};

enum OD_DATA_TYPE {
	OD_TYPE_UINT16 = 0, OD_TYPE_INT16 = 1, OD_TYPE_UINT32 = 2, OD_TYPE_INT32 = 3, OD_TYPE_FLOAT = 4
};

typedef struct OD_type {
	void *variable;
	union {
		uint8_t flags;
		struct {
			uint8_t init : 1;
			uint8_t update : 1;
			uint8_t size : 3;
			uint8_t type : 3;
		};
	};
} OD_type_t;

typedef struct obj_dict {
	OD_type_t variables[OBJECT_COUNT];
	bool init;
} obj_dict_t;

void OD_init(obj_dict_t *obj_dict);

uint8_t OD_getVariableSize(uint8_t data_type);

// interprets CAN message as either get value
bool OD_handleCAN(obj_dict_t *obj_dict, uint8_t data[8], uint8_t *output);

// generates body for CAN message
void OD_generateCAN(obj_dict_t *obj_dict, uint8_t msg_type, uint8_t index, void *value, uint8_t value_type,
		uint8_t output[8]);

bool OD_initValue(obj_dict_t *obj_dict, uint8_t index, uint8_t data_type, void *value);

// retrieves value from object dictionary
bool OD_getValue(obj_dict_t *obj_dict, uint8_t index, bool clearFlag, void *value);

// sets value in object dictionary
bool OD_setValue(obj_dict_t *obj_dict, uint8_t index, void *value);

// gets the updated flag status of an index
bool OD_flagStatus(obj_dict_t *obj_dict, uint8_t index);

#endif /* COMMON_INC_OBJ_DIC_H_ */
