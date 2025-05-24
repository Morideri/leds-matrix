/*
 * main_prm.h
 *
 *  Created on: 04/09/2017
 *      Author: MAASDN
 */

#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\cTypes.h"
#include "..\Header\appl.h"
#include "..\Header\gpio.h"
#include "..\Header\adc.h"
#include "..\Header\timer.h"
#include "..\Header\pwm.h"
#include "..\Header\ws2812b.h"
#include "..\Header\tictactoe.h"
#include "..\Header\keyboard.h"
#include "..\Header\sound.h"
#include "..\Header\numberGenerator.h"
#include "..\Header\genius.h"
#include "..\Header\snake.h"
#include "..\Header\depuracao.h"

//-------------------------------------- Defines ----------------------------------------------------------------

#define INITIALIZE_TASKS()\
{\
	applInitialize();\
	ADC__Initialize();\
	Pwm__Initialize();\
	halSoundInitialize();\
	Timer__Initialize();\
	halKeyBoardInitialize();\
	keyboardInitialize();\
	ledInitialize();\
	rngInit();\
	tictactoeInitialize();\
	geniusInitialize();\
	snakeInitialize();\
	debuggerInitialize();\
	soundInitialize();\
}

#define ALL_SLOTS_TASKS()\
{\
	ADC__Handler();\
	halKeyboardBackgroundHandler();\
	Timer__MsHandler();\
	displayBackgroundHandler();\
	keyboardHander();\
}


#define SLOT_1_TASKS()\
{\
}

#define SLOT_2_TASKS()\
{\
	displayHandler();\
}
	
#define SLOT_3_TASKS()\
{\
	soundHandler();\
}
	
#define SLOT_4_TASKS()\
{\
	rngHandler();\
}
	
#define SLOT_5_TASKS()\
{\
	applHander();\
}




#endif /* MAIN_PRM_H_ */
