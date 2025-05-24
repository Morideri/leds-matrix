/*
 * gpio.c
 *
 * Created: 29/05/2024 14:03:33
 *  Author: gabri
 */ 



//-------------------------------------- Include Files ----------------------------------------------------------------
#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> //biblioteca para o uso das rotinas de de delay

#include "..\Header\gpio.h"
#include "..\Header\cTypes.h"
#include "..\Header\micro.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
const char GPIO_PIN_SET_MASK[] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
const char GPIO_PIN_CLR_MASK[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
	
const char gpioPinSetMask[] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
const char gpioPinClrMask[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};


volatile GPIO_DATA_TYPE *GPIO_DATA_LIST[NUM_OF_PORTS] = GPIO_DATA;   //esta no Micro.h

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------

/*******************************************************************************
Configura  a porta
*******************************************************************************/
void gpioPinConfig(GPIO_PORT port,unsigned char pin,GPIO_PIN_TYPE type){
	volatile GPIO_DATA_TYPE *ptData;
	unsigned char setBitMask;
	unsigned char clrBitMask;
	
	setBitMask = gpioPinSetMask[pin];
	clrBitMask = gpioPinClrMask[pin];
	
	switch(port){
		case PORT_B:
			ptData = adressPORTB;
			break;
		case PORT_C:
			ptData = adressPORTC;
			break;
		case PORT_D:
			ptData = adressPORTD;
			break;
		default:
			break;
	}
	
	switch(type){
		case OUTPUT_DIGITAL:
		ptData = GPIO_DATA_LIST[port];
		ptData->DIRECION_REG.byte |= setBitMask;	// Config Output
		break;
		
		case INPUT_DIGITAL_PULLUP:
		ptData = GPIO_DATA_LIST[port];
		ptData->DIRECION_REG.byte &= clrBitMask; 	// Config Input
		ptData->DATA_OUT_PULL_REG.byte |= clrBitMask;   // Config Input Pull up
		break;
	}
}


void gpioPinWrite(GPIO_PORT port,unsigned char pin,unsigned char value){
	volatile GPIO_DATA_TYPE *ptData = GPIO_DATA_LIST[port]; // Obter o ponteiro para os dados GPIO
	
	if (value == 0) {
		ptData->DATA_OUT_PULL_REG.byte &= GPIO_PIN_CLR_MASK[pin];
	} else {
		ptData->DATA_OUT_PULL_REG.byte |= GPIO_PIN_SET_MASK[pin];
	}
}


unsigned char gpioPinRead(GPIO_PORT port,unsigned char pin){
		volatile GPIO_DATA_TYPE *ptData;
		unsigned char pin_state = SW_OFF;       // pin_state = OFF  não pressionado
		
		ptData = GPIO_DATA_LIST[port];
		if (ptData->DATA_IN_REG.byte & GPIO_PIN_SET_MASK[pin])     // if(leitura != 0)   ou if(leitura)
		
		pin_state = SW_OFF;     // pin_state = SW_OFF   não acionado
		
		else pin_state = SW_ON;
		
		return (pin_state);
}








