/*
 * keyboard.h
 *
 * Created: 03/06/2024 15:47:46
 *  Author: gabri
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "..\Header\adc.h"

#define KEYBOARD_ANALOG_INPUT 5
#define NUM_AD_SAMPLES 4
#define MAX_VARIATION 10
#define NUM_KEY_READ 5

typedef enum
{
	ANALOG_INPUT_0 = 0,
	ANALOG_INPUT_1,
	ANALOG_INPUT_2,
	ANALOG_INPUT_3,
	ANALOG_INPUT_4,
	ANALOG_INPUT_5,
	NUM_OF_ANALOG_INPUT,
}ANALOG_INPUT_TYPE;

typedef enum{
	KEY_1 = 0,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	INVALID_KEY,
	TOTAL_KEYS	
}KEY_PRESSED;

void halKeyBoardInitialize(void);
void halKeyboardBackgroundHandler(void);
unsigned short int Hal_GetAnalogInput(ANALOG_INPUT_TYPE input);
void keyboardInitialize(void);
unsigned char getKeyPressedPosition(void);
void keyboardHander(void);
KEY_PRESSED getKeyBuffer(void);

#endif /* KEYBOARD_H_ */