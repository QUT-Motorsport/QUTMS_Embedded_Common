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
		// clear to zero
		obj_dict->variables[i].init = 0;
		obj_dict->variables[i].update = 1;
	}

	obj_dict->init = true;
}

uint8_t OD_getVariableSize(uint8_t data_type) {
	if (data_type == OD_TYPE_UINT16) {
		return 2;
	}
	else if (data_type == OD_TYPE_INT16) {
		return 2;
	}
	else if (data_type == OD_TYPE_UINT32) {
		return 4;
	}
	else if (data_type == OD_TYPE_INT32) {
		return 4;
	}
	else if (data_type == OD_TYPE_FLOAT) {
		return 4;
	}
	else {
		return 0;
	}
}

// interprets CAN message and processes as required
bool OD_handleCAN(obj_dict_t *obj_dict, uint8_t data[8], uint8_t *output) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	uint8_t type = data[0];
	uint8_t data_size = data[1];

	uint8_t index = data[2];
	uint8_t value_type = data[3];

	uint32_t value = 0;
	for (int i = 0; i < data_size; i++) {
		value |= (data[4 + i] << (i * 8));
	}

	if (index < OBJECT_COUNT) {
		if (obj_dict->variables[index].size != data_size) {
			return false;
		}

		if (obj_dict->variables[index].type != value_type) {
			return false;
		}
	} else {
		return false;
	}

	if (data_size != OD_getVariableSize(value_type)) {
		return false;
	}


	if (type == OD_MSG_GET) {
		// get value request

		if (index < OBJECT_COUNT) {
			// don't clear the flag upon retrieving here
			// since this was an external request
			OD_getValue(obj_dict, index, false, &value);

			// generate output CAN message with value
			OD_generateCAN(obj_dict, OD_MSG_VALUE, index, &value, value_type, output);

			// need to send a response, so return true so we can use the CAN output
			return true;
		}
		else {
			return false;
		}

	}
	else if (type == OD_MSG_SET) {
		// set value request

		// set the value as request
		OD_setValue(obj_dict, index, &value);

		// generate output CAN message with value as confirmation
		OD_generateCAN(obj_dict, OD_MSG_VALUE, index, &value, value_type, output);

		// need to send a response, so return true so we can use the CAN output
		return true;

	}
	else if (type == OD_MSG_VALUE) {
		// response value -> do nothing

		// TODO: this is where you'd update a value if you sent off a request
		// ala openCAN object dictionary
		// but for now this is just an api to update board parameters
		// so we really should never be getting a message with this only sending it

		return false;
	}
	else {
		// invalid type
		return false;
	}
}

// generates body for CAN message
void OD_generateCAN(obj_dict_t *obj_dict, uint8_t msg_type, uint8_t index, void *value, uint8_t value_type,
		uint8_t output[8]) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	// clear output to all zeros
	memset(output, 0, 8);

	uint8_t data_size = sizeof(uint32_t);

	// 0 - get, 1 - set
	// output[0 - 3:0] : value size
	// output[0 - 7:4] : request type

	output[0] = msg_type;
	output[1] = data_size;

	// index in dictionary
	output[2] = index;
	output[3] = value_type;

	uint32_t data = *((uint32_t*) value);

	// copy value
	for (int i = 0; i < data_size; i++) {
		output[4 + i] = (data >> (i * 8)) & 0xff;
	}
}

bool OD_initValue(obj_dict_t *obj_dict, uint8_t index, uint8_t data_type, void *value) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if (index < OBJECT_COUNT) {

		obj_dict->variables[index].size = OD_getVariableSize(data_type);

		if (obj_dict->variables[index].size == 0) {
			return false;
		}

		// update variable in dictionary
		obj_dict->variables[index].variable = value;

		obj_dict->variables[index].init = 1;

		obj_dict->variables[index].type = data_type;

		// flag this variable as having been updated
		obj_dict->variables[index].update = 1;

		return true;
	}
	else {
		return false;
	}
}

// retrieves value from object dictionary
bool OD_getValue(obj_dict_t *obj_dict, uint8_t index, bool clearFlag, void *value) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if ((index < OBJECT_COUNT) && (obj_dict->variables[index].init == 1)) {

		if (clearFlag) {
			obj_dict->variables[index].update = 0;
		}

		// copy to output value
		memcpy(value, obj_dict->variables[index].variable, 4);

		return true;
	}
	else {
		return false;
	}
}

// sets value in object dictionary
bool OD_setValue(obj_dict_t *obj_dict, uint8_t index, void *value) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if ((index < OBJECT_COUNT) && (obj_dict->variables[index].init == 1)) {
		// update variable in dictionary
		memcpy(obj_dict->variables[index].variable, value, 4);

		// flag this variable as having been updated
		obj_dict->variables[index].update = 1;

		return true;
	}
	else {
		return false;
	}
}

// gets the updated flag status of an index
bool OD_flagStatus(obj_dict_t *obj_dict, uint8_t index) {
	if (!obj_dict->init) {
		OD_init(obj_dict);
	}

	if (index < OBJECT_COUNT) {
		return obj_dict->variables[index].update == 1;
	}
	else {
		return false;
	}
}
