/*
 * Pwm.c
 *
 * Created: 05/11/2019 22:50:57
 *  Author: Ana Watanabe
 */ 

#include <avr/io.h>
#include "..\Header\gpio.h"
#include "..\Header\pwm.h"
#include "..\Header\micro.h"


#define BUZZER_DEFAULT_FREQ 1000

//*********************************************************
//
//   Esta rotina  faz a configuração do PWM (buzzer)
//
//*********************************************************
 

// Inicialização do módulo PWM ( Buzzer está no PD3 OC2B !!)
void Pwm__Initialize(void){
	volatile TC0_REG_TYPE *pwm_pt0;
	volatile TC1_REG_TYPE *pwm_pt1;
	volatile TC2_REG_TYPE *pwm_pt2;

	pwm_pt0 = TC0_REGISTERS;
	pwm_pt1 = TC1_REGISTERS;
	pwm_pt2 = TC2_REGISTERS;

	bitWrite(DDRD, 3, OUTPUT_DIGITAL); // porta de  saida para buzina

	bitWrite(DDRD, 6, OUTPUT_DIGITAL); //pino do buzzer como saida
	bitWrite(DDRD, 5, OUTPUT_DIGITAL); //pino do buzzer como saida
	
	pwm_pt0->TCCR0A_REG.byte =  0b00110011; //modo CTC OC0B muda na igualdade de comparação
	pwm_pt0->TCCR0B_REG.byte = 0b00001000; //CTC prescaler parado

	
	pwm_pt1->TCCR1A_REG.byte =  0b00000000;

	pwm_pt2->TCCR2A_REG.byte =  0b00110001; //MODO 1 para PWM fase corrigida,
	// saida  OC2B  INVERTIDA TOP = 0xFF, OC2B habilitado
	//pwm_pt2->TCCR2B_REG.byte =  0b00000010; //TC2 parado

	Pwm__SetTCFrequency(PWM_TC2, BUZZER_DEFAULT_FREQ);
	Pwm__SetDutyCycle(PWM5, BUZZER_OFF_DUTY);
}


//*********************************************************
//
//   Esta rotina configura o TC numa determinada frequência 
//   ( verifcar no livro para cada TC)
//
//*********************************************************
 
void Pwm__SetTCFrequency(PWM_TC_TYPE tc, unsigned short int frequency){
	volatile TC0_REG_TYPE *pwm_pt0;
	volatile TC1_REG_TYPE *pwm_pt1;
	volatile TC2_REG_TYPE *pwm_pt2;

	pwm_pt0 = TC0_REGISTERS;
	pwm_pt1 = TC1_REGISTERS;
	pwm_pt2 = TC2_REGISTERS;
	
	switch(tc){
		case PWM_TC0:
			pwm_pt0->TCCR0B_REG.byte;
			break;
			
		case PWM_TC1:
			pwm_pt1->TCCR1B_REG.byte;
			break;	
		
		case PWM_TC2:
			if(!frequency){ //se frequencia for 0
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x00); //sem fonte de clock, tc2 parado
			}else if(frequency < 128){
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x07); //prescaler = 1024 dando frequencia de 32Hz
			} else if(frequency  < 256){
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x06); //prescaler = 256 dando frequencia de 128Hz
			} else if(frequency  < 512){
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x05); //prescaler = 128 dando frequencia de 256Hz			
			}else if(frequency  < 1024){
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x04); //prescaler = 64 dando frequencia de 512Hz
			}else if(frequency  < 4096){
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x03); //prescaler =32 dando frequencia de 1024Hz
			}else if(frequency  < 32768){
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x02); //prescaler = 8 dando frequencia de 4096Hz
			}else{
				pwm_pt2->TCCR2B_REG.byte = (unsigned char)(0x01); //prescaler = 8 dando frequencia de 32768Hz
			}
			break;
			
		default:
			break;
	}
}  // fim da função

//*********************************************************
//
//   Esta rotina configura o PWM TC num determinado 
//   ciclo de trabalho ( 0 a 100)
//
//*********************************************************
void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty){
volatile TC0_REG_TYPE *pwm_pt0;
volatile TC1_REG_TYPE *pwm_pt1;
volatile TC2_REG_TYPE *pwm_pt2;

pwm_pt0 = TC0_REGISTERS;
pwm_pt1 = TC1_REGISTERS;
pwm_pt2 = TC2_REGISTERS;
if (duty >100)
   duty = 100;
switch (pwm){
case PWM0:
	pwm_pt0->OCR0A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;
case PWM1:
	pwm_pt0->OCR0B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;
case PWM2:
	pwm_pt1->OCR1AH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
 	break;    
case PWM3:
	 pwm_pt1->OCR1BH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	 break;    
case PWM4:
	 pwm_pt2->OCR2A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	 break;    
case PWM5:
	pwm_pt2->OCR2B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;    
default:
	break;	
}
}




void pwmConfiguratePrescaler(PWM_TC_TYPE tcType, unsigned char prescalerVal){
	volatile TC0_REG_TYPE *pwm_pt0;
	//volatile TC1_REG_TYPE *pwm_pt1;
	//volatile TC2_REG_TYPE *pwm_pt2;
	
	pwm_pt0 = TC0_REGISTERS;
	//pwm_pt1 = TC1_REGISTERS;
	//pwm_pt2 = TC2_REGISTERS;
	
	unsigned char prescalerBit0;
	unsigned char prescalerBit1;
	unsigned char prescalerBit2;
	
	if (prescalerVal<=0b00000111){ //verifica se os bits a serem tratados estao limitados a aqueles do prescaler
		prescalerBit0 = ((prescalerVal)&(1UL<<(0)));
		prescalerBit1 = ((prescalerVal)&(1UL<<(1)));
		prescalerBit2 = ((prescalerVal)&(1UL<<(2)));
	}else {
		prescalerBit0 = 0;
		prescalerBit1 = 0;
		prescalerBit2 = 0;
	} //timer parado
	
	switch(tcType){
		case PWM_TC0:
			pwm_pt0->TCCR0B_REG.bit.bit0 = prescalerBit0;
			pwm_pt0->TCCR0B_REG.bit.bit1 = prescalerBit1;
			pwm_pt0->TCCR0B_REG.bit.bit2 = prescalerBit2;
			
			break;
			
		case PWM_TC1:
			break;
			
		case PWM_TC2:
			break;
			
		default:
			break;	
	}
}

void pwmConfigurateTopValue(PWM_TC_TYPE tcType, unsigned char ocraVal){
	volatile TC0_REG_TYPE *pwm_pt0;
	//volatile TC1_REG_TYPE *pwm_pt1;
	//volatile TC2_REG_TYPE *pwm_pt2;
	
	pwm_pt0 = TC0_REGISTERS;
	//pwm_pt1 = TC1_REGISTERS;
	//pwm_pt2 = TC2_REGISTERS;
	
	switch(tcType){
		case PWM_TC0:
		pwm_pt0->OCR0A_REG.byte = ocraVal;
		break;
		
		case PWM_TC1:
		break;
			
		case PWM_TC2:
		break;
			
		default:
		break;
	}
}

void pwmConfigurateCompareValue(PWM_TC_TYPE tcType, unsigned char ocrbVal){
	volatile TC0_REG_TYPE *pwm_pt0;
	//volatile TC1_REG_TYPE *pwm_pt1;
	//volatile TC2_REG_TYPE *pwm_pt2;
		
	pwm_pt0 = TC0_REGISTERS;
	//pwm_pt1 = TC1_REGISTERS;
	//pwm_pt2 = TC2_REGISTERS;
		
	switch(tcType){
		case PWM_TC0:
		pwm_pt0->OCR0B_REG.byte = ocrbVal;
		break;
		
		case PWM_TC1:
		break;
		
		case PWM_TC2:
		break;
		
		default:
		break;
	}
}
