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

typedef struct Timer {
	uint32_t lastTick;
	uint32_t timeout;
	bool isContinuous;
	void (*fcn)(void);
} Timer_t;

Timer_t Timer_init(uint32_t timeout, bool isContinuous, void (*fcn)(void));

bool Timer_update(Timer_t* timer);

void Timer_start(Timer_t* timer);

void Timer_reset(Timer_t* timer);

void Timer_stop(Timer_t* timer);

void Timer_delete(Timer_t* timer);

#endif /* COMMON_INC_TIMER_H_ */
