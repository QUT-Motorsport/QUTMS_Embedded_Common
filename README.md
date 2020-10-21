# QUTMS_Embedded_Common
Common libraries to be shared across embedded board source code

# FSM
## Required Files
* FSM.h 
* FSM.c
* xx_States.h -> (_To be written by user_)
* xx_States.c  -> (_To be written by user_)

## Usage
Main
```c
#include "FSM.h"

// Create a new FSM
fsm_t *fsm = fsm_new(&userDefinedInitialState);

// Set its log user defined log method, prototype is:
// void log(char* msg, size_t len);
fsm_setLogFunction(fsm, &logFn);

// Reset the FSM to a given state, will keep log function.
fsm_reset(fsm, &userDefinedInitialState);

// Your main loop
for(;;)
{
	// Iterate the FSM
	fsm_iterate(fsm);
}
```

## How to design states
State Header
```c
#include "fsm.h"

// Create the state
state_t stateName;

// Enter, Iterate and Exit functions
void stateName_enter(fsm_t *fsm);
void stateName_iterate(fsm_t *fsm);
void stateName_exit(fsm_t *fsm);
```

State C
```c
#include "stateHeader.h"

stateName = {&stateName_enter, &stateName_iterate, &stateName_exit, "stateName_s"};

void stateName_enter(fsm_t *fsm)
{
	// Do code here, maybe change the state, like this?
	fsm_changeState(fsm, &stateName2); // FSM pointer is passed everywhere.
}
```

## Info
If you need any advice on implementation of the FSM, ask Tom or check the AMS repo and the following files:
* FSM.h
* FSM.c
* main.h
* main.c
* AMS_FSM_States.h
* AMS_FSM_States.c