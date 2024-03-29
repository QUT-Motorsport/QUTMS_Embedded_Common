/**
 ******************************************************************************
 * @file FSM.c
 * @brief FSM
 ******************************************************************************
 */

#ifdef QUTMS_FSM

#include <FSM.h>

void fsm_init(fsm_t *fsm, state_t *beginState, fsm_function state_enter, fsm_function state_exit)
{
	fsm->currentState = beginState;
	fsm->state_enter = state_enter;
	fsm->state_exit = state_exit;

	fsm->state_enter(fsm);
	fsm->currentState->enter(fsm);
}

void fsm_iterate(fsm_t *fsm)
{
	fsm->currentState->body(fsm);
}

void fsm_changeState(fsm_t *fsm, state_t *newState, char* changeReason)
{
	if(fsm->currentState == newState)
	{
		return;
	}

	char x[80];
	int len = sprintf(x, "Changing FSM State: 0x%02x -> 0x%02x (%s)\r\n", fsm->currentState->stateID, newState->stateID, changeReason);
	fsm_log(fsm, x, len);

	// exit callback
	fsm->state_exit(fsm);

	// change state
	fsm->currentState = newState;

	// enter callback
	fsm->state_enter(fsm);
	fsm->currentState->enter(fsm);

}

void fsm_setLogFunction(fsm_t *fsm, fsm_log_function func) {
	fsm->log = func;
}

void fsm_log(fsm_t *fsm, char* msg, size_t len) {
	if (fsm->log != NULL) {
		fsm->log(msg, len);
	}
}

#endif
