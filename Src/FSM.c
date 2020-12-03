
/**
 ******************************************************************************
 * @file FSM.c
 * @brief FSM
 ******************************************************************************
 */

#ifdef QUTMS_FSM

#include <FSM.h>

fsm_t *fsm_new(state_t *beginState)
{
	// malloc, 0 memory then set state
	fsm_t *fsm = malloc(sizeof(fsm_t));
	memset(fsm, 0, sizeof(fsm_t));
	fsm->currentState = beginState;

	// Set semaphores
	fsm->sem = osSemaphoreNew(3U, 3U, NULL);
	fsm->updating = osSemaphoreNew(3U, 3U, NULL);

	// Enter state
	if(osSemaphoreAcquire(fsm->sem, 32U) == osOK)
	{
		fsm->currentState->enter(fsm);
		osSemaphoreRelease(fsm->sem);
	}

	return fsm;
}

void fsm_iterate(fsm_t *fsm)
{
	if(osSemaphoreAcquire(fsm->updating, 32U) == osOK) {
		fsm->currentState->iter(fsm);
		osSemaphoreRelease(fsm->updating);
	} else
	{
		fsm_log(fsm, "Unable to gain fsm updating semaphore", strlen("Unable to gain fsm updating semaphore"));
	}
}

void fsm_changeState(fsm_t *fsm, state_t *newState, char* changeReason)
{
	if(fsm->currentState == newState)
	{
		return;
	}
	if(osSemaphoreAcquire(fsm->sem, 32U) == osOK)
	{
		char x[80];
		int len = sprintf(x, "Changing FSM State: %s->%s (%s)\r\n", fsm->currentState->stateName, newState->stateName, changeReason);
		fsm_log(fsm, x, len);
		fsm->currentState->exit(fsm);

		fsm->currentState = newState;
		fsm->currentState->enter(fsm);

		osSemaphoreRelease(fsm->sem);
	} else
	{
		fsm_log(fsm, "Unable to gain fsm sem semaphore", strlen("Unable to gain fsm sem semaphore"));
	}
}

state_t *fsm_getState_t(fsm_t *fsm)
{
	if(osSemaphoreAcquire(fsm->sem, 32U) == osOK)
	{
		state_t *s = fsm->currentState;
		osSemaphoreRelease(fsm->sem);
		return s;
	} else
	{
		fsm_log(fsm, "Unable to gain fsm updating semaphore", strlen("Unable to gain fsm sem semaphore"));
	}
	return NULL;
}

char* fsm_getState(fsm_t *fsm)
{
	if(osSemaphoreAcquire(fsm->sem, 32U) == osOK)
	{
		char *n = fsm->currentState->stateName;
		osSemaphoreRelease(fsm->sem);
		return n;
	} else
	{
		fsm_log(fsm, "Unable to gain fsm updating semaphore", strlen("Unable to gain fsm updating semaphore"));
	}
	return NULL;
}

void fsm_reset(fsm_t *fsm, state_t *resetState)
{
	char x[80];
	int len = sprintf(x, "Resetting FSM to: %s\r\n", resetState->stateName);
	fsm_log(fsm, x, len);
	fsm_log_function f = fsm->log;
	memset(fsm, 0, sizeof(fsm_t));
	fsm->log = f;
	fsm->currentState = resetState;

	// Set semaphores
	fsm->sem = osSemaphoreNew(3U, 3U, NULL);
	fsm->updating = osSemaphoreNew(3U, 3U, NULL);

	// Enter state
	if(osSemaphoreAcquire(fsm->sem, 32U) == osOK)
	{
		fsm->currentState->enter(fsm);
		osSemaphoreRelease(fsm->sem);
	}
}

void fsm_delete(fsm_t *fsm)
{
	osSemaphoreDelete(fsm->sem);
	osSemaphoreDelete(fsm->updating);
	free(fsm);
	fsm = NULL;
}

void fsm_setLogFunction(fsm_t *fsm, fsm_log_function func)
{
	// To be defined by programmer
	fsm->log = func;
}

void fsm_log(fsm_t *fsm, char* msg, ...)
{
	va_list args;
	va_start(args, msg);
	fsm->log(msg, args);
	va_end(args);
}

#endif
