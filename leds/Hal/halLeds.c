/*
 * halLeds.c
 *
 * Created: 30/05/2024 08:35:18
 *  Author: gabriel
 */ 

#include "..\Header\micro.h"
#include "..\Header\ws2812b.h"
#include "..\Header\cTypes.h"
#include "..\Header\gpio.h"

#include <avr/io.h>
#include <avr/interrupt.h>


//////////////////////////////////////Defines & Declarations//////////////////////////////////////
#define set_bit(Y,bit_x)(Y|=(1<<bit_x))
#define clr_bit(Y,bit_x)(Y&=~(1<<bit_x))
#define tst_bit(Y,bit_x)(Y&(1<<bit_x))
#define cpl_bit(Y,bit_x)(Y&(1<<bit_x))

////////////////////////////////////////Private Functions////////////////////////////////////////
void sendZero(void);
void sendOne(void);


////////////////////////////////////////Public Functions////////////////////////////////////////
void sendDataToDisplay(unsigned char *ptData){
	cli(); //desabilita interrupts para que a imagem no display nao seja afetada
	for(unsigned char contador = TOTAL_LEDS; contador > 0; contador--, ptData--){ //varre do ultimo ate o primeiro endereço
		for(unsigned char bit = 8; bit > 0; bit--){ //teste binario
			if(BIT_TEST(*ptData,(bit-1))) //testa o conteudo para onde ptData aponta e verifica se determinado bit é 1 ou 0 e envia o dado aos leds
				sendOne(); 
			else 
				sendZero();
		}
	}
	sei(); //reabilita interrupts
}

void halLedInitialize(){
	gpioPinConfig(PORT_DATA_LED, PIN_DATA_LED, PIN_TYPE_LED); //configuração do pino DataIn dos leds
}



////////////////////////////////////////Private Functions////////////////////////////////////////


void sendZero(void){
	//Gpio__PinWrite(PORT_DATA_LED, PIN_DATA_LED, HIGH);
	set_bit(PORTD, PD1); //PIN do LED como HIGH
	NOP;
	NOP;
	clr_bit(PORTD, PD1); //PIN do LED como LOW
	NOP;
	NOP;
	NOP;
	NOP;
	NOP;
	NOP;
	NOP;
}

void sendOne(void){
	set_bit(PORTD, PD1); //PIN do LED como HIGH
	NOP;
	NOP;
	NOP;
	NOP;
	NOP;
	NOP;
	clr_bit(PORTD, PD1); //PIN do LED como LOW
	NOP;
	NOP;
}



