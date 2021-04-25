/**
 ******************************************************************************
 * @file FSM.c
 * @brief FSM
 ******************************************************************************
 */

#ifdef QUTMS_FSM

#include <FSM.h>

fsm_t fsm_new(state_t *beginState)
{
	// 0 memory then set state
	fsm_t fsm = {0};
	memset(&fsm, 0, sizeof(fsm_t));
	fsm.currentState = beginState;
	fsm.currentState->enter(&fsm);

	return fsm;
}

void fsm_iterate(fsm_t *fsm)
{
	fsm->currentState->iter(fsm);

}

void fsm_changeState(fsm_t *fsm, state_t *newState, char* changeReason)
{
	if(fsm->currentState == newState)
	{
		return;
	}

	char x[80];
	int len = sprintf(x, "Changing FSM State: %s->%s (%s)\r\n", fsm->currentState->stateName, newState->stateName, changeReason);
	fsm_log(fsm, x, len);
	fsm->currentState->exit(fsm);

	fsm->currentState = newState;
	fsm->currentState->enter(fsm);

}

state_t *fsm_getState_t(fsm_t *fsm)
{

	state_t *s = fsm->currentState;
	return s;
}

char* fsm_getState(fsm_t *fsm)
{

	char *n = fsm->currentState->stateName;
	return n;
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

	// Enter state
	fsm->currentState->enter(fsm);
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
