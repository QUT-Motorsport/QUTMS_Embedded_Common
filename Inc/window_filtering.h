/*
 * window_filtering.h
 *
 *  Created on: 9 Mar 2021
 *      Author: Calvin
 */

#ifndef INC_WINDOW_FILTERING_H_
#define INC_WINDOW_FILTERING_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_FILTER_SIZE 256

typedef struct window_filter {
	uint32_t current_filtered;
	uint32_t prev_values[MAX_FILTER_SIZE];
	uint32_t running_sum;
	uint32_t current_idx;
	bool initialized;
	uint16_t window_size;
} window_filter_t;

void window_filter_initialize(window_filter_t *filter, uint32_t initial_value, uint16_t window_size);

void window_filter_update(window_filter_t *filter, uint32_t new_value);

#endif /* INC_WINDOW_FILTERING_H_ */
