/*
 * halSound.c
 *
 * Created: 17/06/2024 06:44:50
 *  Author: gabriel
 */ 
#include "..\Header\micro.h"
#include "..\Header\sound.h"
#include "..\Header\pwm.h"
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char timerTopValue;
unsigned char timerPrescaler;

void Hal__SetBuzzer(unsigned char state)
{
	if(state > 0)
		{
		Pwm__SetDutyCycle(PWM5,BUZZER_DEFAULT_ON_DUTY);
		}
	else
		{
		Pwm__SetDutyCycle(PWM5,BUZZER_OFF_DUTY);
		}
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * 
 */
void halSetBuzzerFreq(unsigned short int frequency){
	Pwm__SetTCFrequency(PWM_TC2, frequency);
}

void halSetBuzzerNote(struct SOUND_DATA* ptSoundData){
	unsigned char topVal = ptSoundData->topValue;
	unsigned char prescalerVal = ptSoundData->prescaler;
	pwmConfigurateTopValue(PWM_TC0, topVal);
	pwmConfiguratePrescaler(PWM_TC0, prescalerVal);
	pwmConfigurateCompareValue(PWM_TC0, topVal);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void halSoundInitialize(void){
	timerTopValue = 0;
	timerPrescaler = 0;
	TIMSK0|=(1<<OCIE0A);
	DDRD|=(1<<PD5); //saida digital no bit do OC0B
	PORTD&=!(1<<PD5); //PD5 definido como 0
}



void halSetNote(struct SOUND_DATA* ptSoundData){
	timerPrescaler = ptSoundData->prescaler;
	timerTopValue = ptSoundData->topValue;
	if(!timerTopValue){ //se valor de top for zero
		timerPrescaler = 0;
	}
	
	
}

