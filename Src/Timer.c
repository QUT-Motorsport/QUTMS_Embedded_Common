/*
 * Timer.c
 *
 *  Created on: 25 Apr 2021
 *      Author: Thomas Fraser
 */

#include <Timer.h>

Timer_t Timer_init(uint32_t timeout, bool isContinuous, void (*fcn)(void))
{
	Timer_t t =
	{
		.lastTick = 0,
		.isContinuous = isContinuous,
		.timeout = timeout,
		.fcn = fcn
	};

	return t;
}

bool Timer_update(Timer_t* timer)
{
	if(HAL_GetTick() - timer->lastTick >= timer->timeout)
	{
		timer->fcn();
		if(timer->isContinuous)
		{
			Timer_reset(timer);
		}
		return true;
	}
	return false;
}

void Timer_start(Timer_t* timer)
{
	timer->lastTick = HAL_GetTick();
}

void Timer_reset(Timer_t* timer)
{
	timer->lastTick = HAL_GetTick();
}

void Timer_stop(Timer_t* timer)
{
	timer->lastTick = UINT32_MAX;
}

void Timer_delete(Timer_t* timer)
{
	timer = NULL;
}
