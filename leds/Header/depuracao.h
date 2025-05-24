/*
 * debugger.h
 *
 * Created: 27/09/2024 08:33:16
 *  Author: gabri
 */ 


#ifndef DEPURACAO_H_
#define DEPURACAO_H_

typedef enum{
	NO_DEBUG_SELECTED,
	COLORS,
	SOUND,
	ALL_DEBUG_TYPES,	
}DEBUGGER_TYPES;

typedef enum{
	DEBUGGER_FIRST_STEP = 0,
	DEBUGGER_SECOND_STEP,
	ALL_DEBUGGER_STEPS
}DEBUGGER_STEPS;

void debuggerInitialize(void);
void debuggerHandler(void);

#endif /* DEPURACAO_H_ */