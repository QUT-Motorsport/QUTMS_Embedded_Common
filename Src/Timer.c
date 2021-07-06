/*
 * Timer.c
 *
 *  Created on: 25 Apr 2021
 *      Author: Thomas Fraser
 */

#include <timer.h>

ms_timer_t timer_init(uint32_t timeout, bool isContinuous, void (*callback)(void* args))
{
	ms_timer_t t =
	{
			.lastTick = 0,
			.isContinuous = isContinuous,
			.isRunning = false,
			.timeout = timeout,
			.callback = callback
	};

	return t;
}

bool timer_update(ms_timer_t* timer, void *args)
{
	if(timer->isRunning)
	{
		if(HAL_GetTick() - timer->lastTick >= timer->timeout)
		{
			if(timer->callback != NULL)
			{
				timer->callback(args);
			}
			if(timer->isContinuous)
			{
				timer_reset(timer);
			} else
			{
				timer_stop(timer);
			}
			return true;
		}
	}
	return false;
}

void timer_start(ms_timer_t* timer)
{
	timer->isRunning = true;
	timer->lastTick = HAL_GetTick();
}

bool timer_isRunning(ms_timer_t* timer)
{
	return timer->isRunning;
}

void timer_reset(ms_timer_t* timer)
{
	timer->isRunning = true;
	timer->lastTick = HAL_GetTick();
}

void timer_stop(ms_timer_t* timer)
{
	timer->isRunning = false;
	timer->lastTick = UINT32_MAX;
}
