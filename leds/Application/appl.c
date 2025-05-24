/*
 * appl.c
 *
 * Created: 29/05/2024 15:55:54
 *  Author: gabri
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\appl.h"
#include "..\Header\tictactoe.h"
#include "..\Header\keyboard.h"
#include "..\Header\ws2812b.h"
#include "..\Header\genius.h"
#include "..\Header\timer.h"
#include "..\Header\snake.h"
#include "..\Header\depuracao.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------


//-------------------------------------- Global Variables ----------------------------------------------------------------
GAME_MODE gameMode;
KEY_PRESSED keyPressed;
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------
void gameSelect(void);


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
void applInitialize(){
	gameMode = NO_GAME_SELECTED;
	keyPressed = INVALID_KEY;
}

void resetGameMode(){
	gameMode = NO_GAME_SELECTED;
	keyPressed = INVALID_KEY;
}

void applHander(void){		
	
	switch(gameMode){
		case NO_GAME_SELECTED:
			gameSelect();
			break;
			
		case TIC_TAC_TOE:
			tictactoeHandler();
			break;
				
		case GENIUS:
			geniusHandler(0); //flag hard mode clear
			break;
		
		case GENIUS_HARD_MODE:
			geniusHandler(1); //flag hard mode set
			break;
			
		case SNAKE:
			snakeHandler();
			break;
			
		case DEBUGGER:
			debuggerHandler();
			break;
		
		default:
			break;
	}
}

void gameSelect(void){
	keyPressed = getKeyBuffer();
	switch(keyPressed){
		case KEY_1:
		gameMode = TIC_TAC_TOE;
		break;
		
		case KEY_2:
		gameMode = GENIUS;
		break;
		
		case KEY_3:
		gameMode = GENIUS_HARD_MODE;
		break;
		
		case KEY_4:
		gameMode = SNAKE;
		break;
		
		case KEY_9:
		gameMode = DEBUGGER;
		break;
		
		default:
		break;
	}
}


//---------------------------------------------------------------------------------------------------------------------
