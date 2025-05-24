/*
 * keyboard.c
 *
 * Created: 03/06/2024 15:47:24
 *  Author: gabri
 */ 

#include "..\Header\keyboard.h"	
#include "..\Header\cTypes.h"
#include "..\Header\timer.h"
#include "..\Header\mathFunctions.h"




typedef enum{
	HANDLER_INIT = 0,
	GET_ANALOG_INPUT_DATA,
	STABLE_VERIFICATION,
	ANALOG_PROCESSING,
	ALL_KEYBOARD_HANDLE_STATE
}KEYBOARD_HANDLE_STATE;

KEYBOARD_HANDLE_STATE keyboardHandleState;
KEY_PRESSED keyBuffer;


unsigned short int analogInputArry[NUM_KEY_READ];
unsigned short int analogInput;
unsigned short int analogInputAccumulator;
unsigned char inputCounter;
short int readVariation;
short int variationAccumulator;

unsigned short int* analogPt;


void positionProcess(void);


void keyboardInitialize(){ //inicia variaveis
	keyBuffer = INVALID_KEY; //leitura invalida
	keyboardHandleState = GET_ANALOG_INPUT_DATA; //estado inicial da maquina de estado

	analogPt = &analogInputArry[0]; //inicia ponteiro
	for(inputCounter =  0; inputCounter <= NUM_KEY_READ; inputCounter++){ //varre todas as posições do vetor
		*analogPt = 0; //define como zero
		analogPt++; //atualiza para onde o ponteiro deve apontar
	}
}

void keyboardHander(void){ //chama a função que analiza a tecla pressionada
	positionProcess();
}

KEY_PRESSED getKeyBuffer(void){ //função externa que retorna posição salva em um buffer
	return keyBuffer;
}

void positionProcess(void){
	switch(keyboardHandleState){ 
		case HANDLER_INIT: //inicia variaveis
			analogPt = &analogInputArry[0];
			variationAccumulator = 0;
			analogInputAccumulator = 0;
			keyboardHandleState++; //proximo estado
			break;
		
		case GET_ANALOG_INPUT_DATA:
			if(Timer__MsGetStatus(KEYBOARD_TIMER_MS) == TIMER_EXPIRED){ //se o tempo de espera entre leituras tiver expirado
				analogInputArry[inputCounter] = Hal_GetAnalogInput(KEYBOARD_ANALOG_INPUT); //salva valor no vetor
				analogInputAccumulator += analogInputArry[inputCounter]; //soma valor na variavel
				inputCounter++; //atualiza quantos inputs ja foram contabilizados
				Timer__MsSet(KEYBOARD_TIMER_MS,1); //redefine timer
			}
			if(inputCounter>=NUM_KEY_READ) //se todas as leituras indicadas ja tiverem sido realizadas
				keyboardHandleState++; //vai para o proximo estado
			break;
				
		case STABLE_VERIFICATION:
			for(;inputCounter > 1; inputCounter--){ //como input counter ja esta no seu valor maximo dado o estado anterior verificado por (inputCounter>=NUM_KEY_READ), 
													//varre todas as posiveis diferenças entre valor e o valor seguinto do vetor que as guarda seus valores (analogInputArry)
				analogInput = *analogPt; //recebe valor do vetor 
				analogPt++; //muda para onde o ponteiro aponta
				readVariation = analogInput - *analogPt; //tira a diferença
				variationAccumulator += module(readVariation); //incrementa o modulo da diferença na variavel
			}
			
			inputCounter--; //garante retorno do valor de inputCounter para zero
			
			if(variationAccumulator<MAX_VARIATION){ //se a variação maxima for menor que a permitida
				analogInput = (unsigned short int)(analogInputAccumulator/NUM_KEY_READ); //tira a media e atualiza variavel
			}
			else{ //se não, o valor da leitura da leitura é dita como invalida
				analogInput = 0;
			}
			keyboardHandleState++; //vai para o proximo estado
			break;
		
		case ANALOG_PROCESSING: //verifica qual botão pressionada a depender do valor analogico lido
			if(analogInput>920)
				keyBuffer = KEY_3;
			else if(analogInput>840)
				keyBuffer =  KEY_2;
			else if(analogInput>700)
				keyBuffer =  KEY_1;
			else if(analogInput>610)
				keyBuffer =  KEY_6;
			else if(analogInput>510)
				keyBuffer =  KEY_5;
			else if(analogInput>390)
				keyBuffer =  KEY_4;
			else if(analogInput>290)
				keyBuffer =  KEY_9;
			else if(analogInput>190)
				keyBuffer =  KEY_8;
			else if(analogInput>100)
				keyBuffer = KEY_7;
			else //analogInput = 0; é considerado invalida
				keyBuffer = INVALID_KEY;
				
			keyboardHandleState++; //vai para o proximo estado
			break;
		
		default:
			keyboardHandleState = HANDLER_INIT; //retorna para o inicio
			break;
	}

}