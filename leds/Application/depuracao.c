/*
 * debugger.c
 *
 * Created: 27/09/2024 08:33:06
 *  Author: gabri
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "..\Header\depuracao.h"
#include "..\Header\keyboard.h"
#include "..\Header\ws2812b.h"
#include "..\Header\timer.h"
#include "..\Header\sound.h"
#include "..\Header\numberGenerator.h"
#include "..\Header\appl.h"

#include "..\Header\gpio.h"
#include "..\Header\pwm.h"
//#include "..\Header\micro.h"


#include "..\Header\atmega328p.h"



DEBUGGER_TYPES debuggerType;
DEBUGGER_STEPS debuggerStep;

KEY_PRESSED inputKey;
KEY_PRESSED lastKey;

MUSICAL_NOTES debugNote;

unsigned char debugCount;



void debuggerInitialize(void){
	debuggerType = NO_DEBUG_SELECTED;
	debuggerStep = DEBUGGER_FIRST_STEP;
	inputKey = INVALID_KEY;
	debugNote = 0;	
	debugCount = 0;
}



void debuggerHandler(void){
	cli();
	switch(debuggerStep){
		case DEBUGGER_FIRST_STEP:
			while(1){
				
				for(unsigned char __Cor = 0; __Cor < 3; __Cor++){
					
					for(unsigned char __Intensidade = 255; __Intensidade >1;__Intensidade-=2){
						for(unsigned char __Coluna = 8; __Coluna > 0; __Coluna--){
							for(unsigned char __Linha = 8; __Linha > 0; __Linha--){
								changeIndividual(__Linha, __Coluna, __Cor, __Intensidade);
							}
							sendDataToDisplay(matrixLastAddress);
							cli();
							_delay_ms(2);
						
						}
					}				
				}
			break;
			
		case DEBUGGER_SECOND_STEP:
	
			break;
			
		default:
			break;
		}
	}
}

				/*
				for(unsigned char __Cor = 0; __Cor < 3; __Cor++){
					for(unsigned char __Linha = 0; __Linha <= 8; __Linha++){
						for(unsigned char __Coluna = 0; __Coluna <= 8; __Coluna++){
							changeIndividual(__Linha, __Coluna, __Cor, 15);
						}
						sendDataToDisplay(matrixLastAddress);
						_delay_ms(1000);
					}

					for(unsigned char __Coluna = 8; __Coluna > 0; __Coluna--){
						for(unsigned char __Linha = 8; __Linha > 0; __Linha--){
							changeIndividual(__Linha, __Coluna, __Cor, 0);
						}
						sendDataToDisplay(matrixLastAddress);
						_delay_ms(1000);
					}
				}
				*/