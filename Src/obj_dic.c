/*
 * obj_dic.c
 *
 *  Created on: 6 Oct. 2021
 *      Author: Calvin
 */

#include "obj_dic.h"

#include <stdlib.h>
#include <string.h>

void OD_init(obj_dict_t *obj_dict) {
	// default values for all variables
	for (int i = 0; i < OBJECT_COUNT; i++) {
		obj_dict->variables[i] = 0;
		obj_dict->update_flag[i] = true;
	}

	obj_dict->init = true;
}

// interprets CAN message and processes as required
bool OD_handleCAN(obj_dict_t *obj_dict, uint8_t data[8], uint8_t *output) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	uint8_t type = data[0];
	uint8_t data_size = data[1];

	if (data_size != sizeof(OD_type_t)) {
		return false;
	}

	uint8_t index = data[2];

	OD_type_t value = 0;
	for (int i = 0; i < data_size; i++) {
		value |= (data[3 + i] << (i * 8));
	}

	if (type == OD_MSG_GET) {
		// get value request

		if (index < OBJECT_COUNT) {
			// don't clear the flag upon retrieving here
			// since this was an external request
			value = OD_getValue(obj_dict, index, false);

			// generate output CAN message with value
			OD_generateCAN(obj_dict, OD_MSG_VALUE, index, value, output);

			// need to send a response, so return true so we can use the CAN output
			return true;
		} else {
			return false;
		}

	} else if (type == OD_MSG_SET) {
		// set value request

		// set the value as request
		OD_type_t new_value = OD_setValue(obj_dict, index, value);

		// generate output CAN message with value as confirmation
		OD_generateCAN(obj_dict, OD_MSG_VALUE, index, new_value, output);

		// need to send a response, so return true so we can use the CAN output
		return true;

	} else if (type == OD_MSG_VALUE) {
		// response value -> do nothing

		// TODO: this is where you'd update a value if you sent off a request
		// ala openCAN object dictionary
		// but for now this is just an api to update board parameters
		// so we really should never be getting a message with this only sending it

		return false;
	} else {
		// invalid type
		return false;
	}
}

// generates body for CAN message
void OD_generateCAN(obj_dict_t *obj_dict, uint8_t type, uint8_t index,
		OD_type_t value, uint8_t output[8]) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	// clear output to all zeros
	memset(output, 0, 8);

	uint8_t data_size = sizeof(OD_type_t);

	// 0 - get, 1 - set
	// output[0 - 3:0] : value size
	// output[0 - 7:4] : request type

	output[0] = type;
	output[1] = data_size;

	// index in dictionary
	output[2] = index;

	// copy value
	for (int i = 0; i < data_size; i++) {
		output[3 + i] = (value >> (i * 8)) & 0xff;
	}
}

// retrieves value from object dictionary
OD_type_t OD_getValue(obj_dict_t *obj_dict, uint8_t index, bool clearFlag) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if (index < OBJECT_COUNT) {

		if (clearFlag) {
			obj_dict->update_flag[index] = false;
		}

		return obj_dict->variables[index];
	} else {
		return 0;
	}
}

// sets value in object dictionary
OD_type_t OD_setValue(obj_dict_t *obj_dict, uint8_t index, OD_type_t value) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if (index < OBJECT_COUNT) {
		// update variable in dictionary
		obj_dict->variables[index] = value;

		// flag this variable as having been updated
		obj_dict->update_flag[index] = true;

		// return updated value as confirmation
		return obj_dict->variables[index];
	} else {
		return 0;
	}
}

// gets the updated flag status of an index
bool OD_flagStatus(obj_dict_t *obj_dict, uint8_t index) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if (index < OBJECT_COUNT) {
		return obj_dict->update_flag[index];
	} else {
		return false;
	}
}
