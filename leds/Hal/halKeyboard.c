/*
 * keyboard.c
 *
 * Created: 03/06/2024 15:55:43
 *  Author: gabri
 */ 


#include "..\Header\keyboard.h"
#include "..\Header\adc.h"


const unsigned char AD_Enable_Table[NUM_OF_ANALOG_INPUT] = ADC_PRM_CHANNEL_DATA;
const unsigned char AD_Channel_Table[NUM_OF_ANALOG_INPUT] = ADC_CHANNEL_DATA;

typedef enum
{
	MUX_INIT = 0,       //!< MUX_INIT
	MUX_AD_CONFIG,      //!< MUX_AD_CONFIG
	MUX_DUMMY_STATE_1,  //!< MUX_DUMMY_STATE_1
	MUX_AD_READ,        //!< MUX_AD_READ
	NUM_MUX_STEPS       //!< NUM_MUX_STEPS
} AD_MUX_STATES;
AD_MUX_STATES AD_Mux_State;

//variaveis para ADC
ANALOG_INPUT_TYPE AD_Channel;
unsigned short int AD_Accumulator[NUM_OF_ANALOG_INPUT]; //buffer para soma das leituras
unsigned short int AD_Sample[NUM_OF_ANALOG_INPUT]; //buffer do sample de cada canal
unsigned short int Hal_Analog_Inputs[NUM_OF_ANALOG_INPUT];   // buffer da media do valor do ADC de cada canal
unsigned char AD_Counter[NUM_OF_ANALOG_INPUT]; //variavel de contagem da quantidade de leituras de cada canal

void halKeyBoardInitialize(void){
	ANALOG_INPUT_TYPE analog_index;
	ADC__ConfigModes(MODE_10BITS,AD_SINGLE_CONVERSION);
	AD_Mux_State = 	MUX_INIT;
	AD_Channel = KEYBOARD_ANALOG_INPUT;  // equivalente ao canal AD5 do arduino
	
	for(analog_index = 0; analog_index < NUM_OF_ANALOG_INPUT; analog_index++) //varre todos canais
	{
		if(AD_Enable_Table[analog_index] == ENABLED) //verifica se canal foi definido como adc
		{
			Hal_Analog_Inputs[analog_index] = 0;   // zera os vetotes de valor de cada canal
			AD_Accumulator[analog_index] = 0;
			AD_Counter[analog_index] = 0;
		}
	}
}

void ADProcess(void)
{
	switch (AD_Mux_State)
	{
		case MUX_INIT:
		break;
		case MUX_AD_CONFIG:
		ADC__ConfigModes(MODE_10BITS,AD_SINGLE_CONVERSION);
		break;
		case MUX_DUMMY_STATE_1: //=> This state is placed in order to assure the raising time for ADC reading
		break;
		case MUX_AD_READ:
		if(AD_Enable_Table[AD_Channel] == ENABLED) //verifica se canal adc esta habilitado
		{
			if(AD_Counter[AD_Channel] < NUM_AD_SAMPLES) //caso ainda faltem leituras 
			{
				AD_Sample[AD_Channel] = ADC__GetValue(AD_Channel_Table[AD_Channel]);
				AD_Accumulator[AD_Channel] += AD_Sample[AD_Channel];
				AD_Counter[AD_Channel]++;
			}
			else //caso todas as leituras tenham sido realizadas 
			{ 
				Hal_Analog_Inputs[AD_Channel] = (unsigned short int)(AD_Accumulator[AD_Channel]/NUM_AD_SAMPLES); //tira a media
				AD_Accumulator[AD_Channel] = 0; //reinicia vetor
				AD_Counter[AD_Channel] = 0; //reinicia vetor
			}
		}
		AD_Channel++;
		if(AD_Channel >= NUM_OF_ANALOG_INPUT) //se todos os canais ja tiverem sido analizados
		{
			AD_Channel = 0; //reinicia variavel
		}
		break;
		default:
		break;
	}

	AD_Mux_State++;                                // Ticking the state machine.

	if (AD_Mux_State >= NUM_MUX_STEPS)
	{
		AD_Mux_State = MUX_AD_CONFIG;
	}
}


void halKeyboardBackgroundHandler(void)
{
	ADProcess();
}

unsigned short int Hal_GetAnalogInput(ANALOG_INPUT_TYPE input){
	if(input < NUM_OF_ANALOG_INPUT)
		return Hal_Analog_Inputs[input];  // retorna o valor no buffer HAL_AnalogInputs do canal solicitado
	else return 0;
}










