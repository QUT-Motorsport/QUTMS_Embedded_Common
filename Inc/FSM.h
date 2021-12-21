/**
 ******************************************************************************
 * @file FSM.h
 * @brief FSM
 ******************************************************************************
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief Typedef state as state_t
 */
typedef struct state state_t;

/**
 * @brief Typedef fsm as fsm_t
 */
typedef struct fsm fsm_t;

/**
 * @brief fsm_function Typedef
 * @param A pointer to the FSM object
 */
typedef void (*fsm_function)(fsm_t*);

typedef void (*fsm_log_function)(const char *, size_t);

/**
 * @brief FSM state
 */
struct state {
	fsm_function enter;
	fsm_function body;
	uint8_t stateID;
};

/**
 * @brief FSM structure
 */
struct fsm {
	state_t *currentState; /**< Current FSM State */
	fsm_log_function log;

	// generic callbacks to enter and exit (for debug CAN messages)
	fsm_function state_enter;
	fsm_function state_exit;
};

/**
 * @brief Creates a new FSM object
 * @param beginState The inital state to be set for the FSM
 * @return the initialized FSM object
 */
fsm_t fsm_new(state_t *beginState, fsm_function state_enter, fsm_function state_exit);

/**
 * @brief Iterates the FSM by calling fsm->currentState->iter(fsm)
 * @param fsm A pointer to the FSM object
 */
void fsm_iterate(fsm_t *fsm);

/**
 * @brief Changes the state of the FSM
 * @param fsm A pointer to the FSM object
 * @param newState A pointer to the new state to change to
 */
void fsm_changeState(fsm_t *fsm, state_t *newState, char* changeReason);

/**
 * @brief Set the function that the fsm will log with
 * @param fsm the fsm object to set the log function for
 * @param func the function that will be called when fsm->log is called
 * @note The function prototype must follow the following standard: void x(char* msg, size_t length).
 * Any other prototype will 100% break things
 */
void fsm_setLogFunction(fsm_t *fsm, fsm_log_function func);

/**
 * @brief Logs information based on the user defined log function
 * @param fsm The fsm object
 * @param msg The message to log
 * @param length The strlen() of the message
 */
void fsm_log(fsm_t *fsm, char* msg, size_t len);

#endif /* INC_FSM_H_ */
