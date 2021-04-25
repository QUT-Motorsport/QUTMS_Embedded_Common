/*
 * Timer.h
 *
 *  Created on: 25 Apr 2021
 *      Author: thomas
 */

#ifndef COMMON_INC_TIMER_H_
#define COMMON_INC_TIMER_H_

#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


typedef struct timer {
	uint32_t lastTick;
	uint32_t timeout;
	bool isContinuous;
	bool isRunning;
	void (*callback)(void *);
} ms_timer_t;

ms_timer_t timer_init(uint32_t timeout, bool isContinuous, void (*callback)(void* args));

bool timer_update(ms_timer_t* timer, void *args);

void timer_start(ms_timer_t* timer);

void timer_reset(ms_timer_t* timer);

bool timer_isRunning(ms_timer_t* timer);

void timer_stop(ms_timer_t* timer);

void timer_delete(ms_timer_t* timer);


#endif /* COMMON_INC_TIMER_H_ */
