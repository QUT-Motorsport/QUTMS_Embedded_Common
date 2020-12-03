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
#include "cmsis_os.h"

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

typedef int (*fsm_log_function)(const char* restrict, ...);

/**
 * @brief FSM state
 */
struct state {
	fsm_function enter; /**< State enter function */
	fsm_function iter; /**< State iterate function */
	fsm_function exit; /**< State exit function */
	char *stateName;
};

/**
 * @brief FSM structure
 */
struct fsm {
	state_t *currentState; /**< Current FSM State */
	fsm_log_function log;
	osSemaphoreId_t sem; /**< FSM change state semaphore */
	osSemaphoreId_t updating; /**< FSM iterating semaphore */
};

/**
 * @brief Creates a new FSM object
 * @param beginState The inital state to be set for the FSM
 * @return A pointer to the FSM object
 */
fsm_t *fsm_new(state_t *beginState);

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
 * @brief Gets a pointer to the current state of the FSM
 * @param fsm A pointer to the FSM object
 * @return A pointer to the current state object
 */
state_t *fsm_getState_t(fsm_t *fsm);

/**
 * @brief Gets the name of the current state of the FSM
 * @param fsm A pointer to the FSM object
 * @return A string of the name of the current FSM state
 */
char* fsm_getState(fsm_t *fsm);

/**
 * @brief Resets the FSM to a state without calling exit and enter function
 * @param fsm A pointer to the FSM object
 * @param resetState A pointer to the state to reset to
 */
void fsm_reset(fsm_t *fsm, state_t *resetState);

/**
 * @brief Delete by memory freeing the FSM object
 * @param fsm A pointer to the FSM object
 */
void fsm_delete(fsm_t *fsm);

/**
 * @brief Set the function that the fsm will log with
 * @param fsm the fsm object to set the log function for
 * @param func the function that will be called when fsm->log is called
 * @note The function prototype must follow the following standard: void x(char* msg, size_t length).
 * Any other prototype will 100% break things
 */
void fsm_setLogFunction(fsm_t *fsm, fsm_log_function func);

/**
 * @brief Logs informaiton based on the user defined log function
 * @param fsm The fsm object
 * @param msg The message to log
 * @param length The strlen() of the message
 */
void fsm_log(fsm_t *fsm, char* msg, ...);

#endif /* INC_FSM_H_ */
