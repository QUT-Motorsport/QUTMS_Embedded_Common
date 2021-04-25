/*
 * window_filtering.c
 *
 *  Created on: 9 Mar 2021
 *      Author: Calvin
 */

#include "window_filtering.h"
#include <stdlib.h>

void window_filter_initialize(window_filter_t *filter, uint16_t initial_value, size_t window_size) {
	filter->current_idx = 0;
	filter->window_size = window_size;

	filter->prev_values = calloc(window_size, sizeof(uint16_t));

	for (int i = 0; i < window_size; i++) {
		filter->prev_values[i] = initial_value;
	}
	filter->running_sum = initial_value * window_size;
	filter->current_filtered = initial_value;
	filter->initialized = true;
}

void window_filter_update(window_filter_t *filter, uint16_t new_value) {
	// simple window filter

	if (!filter->initialized) {
		window_filter_initialize(filter, new_value, filter->window_size);
	} else {
		// remove the oldest value from the running sum and add the new value
		filter->running_sum += new_value
				- filter->prev_values[filter->current_idx];

		// update the oldest value with the new value (round robin style)
		filter->prev_values[filter->current_idx] = new_value;

		// increment the index so it wraps around
		filter->current_idx = (filter->current_idx + 1)
				% filter->window_size;

		filter->current_filtered = filter->running_sum / filter->window_size;
	}
}

void window_filter_delete(window_filter_t *filter) {
	if (filter->prev_values != NULL) {
		free(filter->prev_values);
		filter->prev_values = NULL;
		filter->initialized = false;
	}
}
