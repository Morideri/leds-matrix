/*
 * Appl.h
 *
 * Created: 29/05/2024 13:47:47
 *  Author: gabri
 */ 


#ifndef APPL_H_
#define APPL_H_


typedef enum{
	NO_GAME_SELECTED = 0,
	TIC_TAC_TOE,
	GENIUS,
	GENIUS_HARD_MODE,
	SNAKE,
	TOTAL_GAME_MODES,
	DEBUGGER,
}GAME_MODE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================



void applHander(void);
void applInitialize(void);
void resetGameMode(void);




#endif /* APPL_H_ */