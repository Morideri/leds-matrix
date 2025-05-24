/*
 * Pwm.h
 *
 * Created: 05/11/2019 22:26:18
 *  Author: Ana Watanabe
 */ 


#ifndef Pwm_H_
#define Pwm_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\micro.h"
#include "..\Header\sound.h"

typedef enum {
	PWM0 = 0,   // OC0A PD6
	PWM1,       // OC0B PD5
	PWM2,       // OC1A PB1
	PWM3,       // OC1B PB2
	PWM4,       // OC2A PB3
	PWM5,       // OC2B PD3
	NUM_OF_PWM,
} PWM_ID_TYPE;

typedef enum {
	PWM_TC0 = 0,
	PWM_TC1,
	PWM_TC2,
	NUM_OF_PWM_TC,
} PWM_TC_TYPE;

//protótipos
// Inicialização do módulo PWM                                                                                           
void Pwm__Initialize(void);
// Configura o TC numa determinada frequência ( verificar no livro para cada TC)                    
void Pwm__SetTCFrequency( PWM_TC_TYPE tc, unsigned short int frequency);
// Configura o PWM TC num determinado ciclo de trabalho ( 0 a 100%)                        
void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty);

void Pwm__SetTCTopValue(unsigned short int topValue);

void Pwm__SetTCSetPreScaler(unsigned short int preScaler);


void pwmConfiguratePrescaler(PWM_TC_TYPE tcType, unsigned char prescalerVal);
void pwmConfigurateTopValue(PWM_TC_TYPE tcType, unsigned char ocraVal);
void pwmConfigurateCompareValue(PWM_TC_TYPE tcType, unsigned char ocrbVal);

#endif /* Pwm_H_ */



