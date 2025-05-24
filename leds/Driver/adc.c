/*
 * adc.c
 *
 * Created: 29/05/2024 14:00:14
 *  Author: gabri
 */ 


//-------------------------------------- Include Files --------------------------------------------------------------------
#include <avr/io.h> 
#include "..\Header\cTypes.h"
#include "..\Header\adc.h"
#include "..\Header\gpio.h"



 #include "..\Header\micro.h"
 #include "..\Header\defType.h"
 
//-------------------------------------- PUBLIC (Variables) ------------------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define HI_BYTE_MASK          0xFF00
#define LO_BYTE_MASK          0x00FF

const unsigned char Adc_Enable_Table[NUM_OF_AD_CHANNELS]= ADC_PRM_CHANNEL_DATA;




const unsigned char ADC_BIT_SET_MASK[] = {0x1,0x2,0x4,0x8,0x10,0x20};
const unsigned char ADC_BIT_CLR_MASK[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF};
	
	

//-------------------------------------- Global Variables ----------------------------------------------------------------
/*
//+++++++++++
//ADC VARIAVAIES
const u8 ADC_ENABLE_PIN_MASK = (ADC_PIN_0)|(ADC_PIN_1<<1)|(ADC_PIN_2<<2)|(ADC_PIN_3<<3)|(ADC_PIN_4<<4)|(ADC_PIN_5<<5);
const u8 ADC_ENABLED_PIN_TABLE[] = {ADC_PIN_0, ADC_PIN_1, ADC_PIN_2, ADC_PIN_3, ADC_PIN_4, ADC_PIN_5};
AD_CHANNEL_TYPE adcPin;
volatile u16* ptAdcValue;

ADC_PROCESS_STEP adcStep;
u16 adcBuffer[ADC_TOTAL_PIN];

ADC_MULTIPLEXER* ptAdcADMUX;
ADC_STATUS_CONTROL_A* ptAdcADCSRA;
ADC_STATUS_CONTROL_B* ptAdcADCSRB;
ADC_DIGITAL_INPUT_DISABLE* ptAdcDIDR0;

ADC_REGISTERS_CONFIGURATION adcPinConfigMask[ADC_TOTAL_PIN];
*/
//+++++++++++




// Variaveis do ADC
unsigned short int ADC_Buffer[NUM_OF_AD_CHANNELS];
ADC_CONV_STEPS_TYPE Adc_Step;
AD_CHANNEL_TYPE Adc_Channel;
unsigned short int Sampling_Time;


/*
const unsigned char adcEnableTable[NUM_OF_AD_CHANNELS] = ADC_PRM_CHANNEL_DATA;

unsigned short int samplingTime;
*/
AD_CHANNEL_TYPE Adc_Channel;

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------





//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
void ADC__Initialize(void) //configura pinos de digital para analogico e inicializa o ADC_Buffer[]
{
	unsigned char channel;
	volatile ADC_REG_TYPE *adcPt;   // tipo definido no micro.h
	adcPt = ADC_REGISTERS;          // adc_pt aponta para o inicio dos regs do ADC ($000078)

	Adc_Step = ADC_STEP_INIT;   // inicializa o Adc_Step em INIT
	Sampling_Time = 0;
	adcPt->DIDR0_REG.byte = 0x00;  //  nenhuma entrada analogica habilitada
	
	for(channel = 0; channel < NUM_OF_AD_CHANNELS; channel++){
		ADC_Buffer[channel] = 0;

		if(Adc_Enable_Table[channel] == ENABLED) //se canal habilitado, entao deixa analagico
		{
			// Configures relative input as analog input
			if(channel < NUM_OF_AD_CHANNELS){							// CH0 to CH5 are configured in DIDR0
			   adcPt->DIDR0_REG.byte |= ADC_BIT_SET_MASK[channel];	// configura como analogico conforme o canal enabled
			}
		}
	}  
}

//---------------------------------------------------------------------------------------------------------------------

void ADC__Handler(void)
{
	unsigned short int value, value_high;
	volatile ADC_REG_TYPE *adcPt;
	adcPt = ADC_REGISTERS;
	value = 0; //inicializa value


	
	switch(Adc_Step)
	{
	case ADC_STEP_INIT:
		Adc_Channel++;											// Selects next channel
		if(Adc_Channel >= NUM_OF_AD_CHANNELS)
		{
			Adc_Channel = AD_CH0;  // varre constantemente todas os canais
		}

		if(Adc_Enable_Table[Adc_Channel] == ENABLED)			// Checks if current channel is enabled
		{
			Adc_Step = ADC_STEP_SAMPLING;
			Sampling_Time = ADC_SAMPLING_TIME;
		}
		break;

	case ADC_STEP_SAMPLING:
		if(Sampling_Time)
		{
			Sampling_Time--; 
		}
		else
		{
			Adc_Step = ADC_STEP_CONFIG_CHANNEL;	
		}
		break;

	case ADC_STEP_CONFIG_CHANNEL:
	    adcPt->ADMUX_REG.byte |= (unsigned char)Adc_Channel;	// Configures the channel be read
		// ADC Enabled, no autotrigger, no interrupt, prescaler 128
		adcPt->ADCSRA_REG.byte =  0x87; 
		// start conversion
		adcPt->ADCSRA_REG.bit.bit6  = 1;    //seta bit 6 (ADSC)
		Adc_Step = ADC_STEP_WAIT_CONVERSION;					// Set next step
		break;
		
	case ADC_STEP_WAIT_CONVERSION:
		if(adcPt->ADCSRA_REG.bit.bit6 == 0)	// Wait until conversion be completed
		   	Adc_Step = ADC_STEP_READ_RESULT;
		break;

	case ADC_STEP_READ_RESULT:  // AQUI ? feita a leitura do ADC f?sico!!!
	    if(adcPt->ADMUX_REG.bit.bit5 == 1)   //8 bits
		   value = (unsigned short int)(adcPt->ADCH_REG.byte)& (LO_BYTE_MASK); // 8 bits   testado ok
		if(adcPt->ADMUX_REG.bit.bit5 == 0)    // 10 bits
		   {
			value = (unsigned short int)((adcPt->ADCL_REG.byte)& LO_BYTE_MASK);
			value_high = (unsigned short int)(adcPt->ADCH_REG.byte <<8); 
			value |= value_high;	// Reads the conversion result bytes  
		   }

		ADC_Buffer[Adc_Channel] = value;  //value stored in the buffer ADC_Buffer of that channel.
		Adc_Step = ADC_STEP_INIT;
		

	 	break;

	default:
		Adc_Step = ADC_STEP_INIT;
		break;
	}
	
}  


//---------------------------------------------------------------------------------------------------------------------

 void ADC__ConfigModes(AD_MODE_TYPE  mode, AD_CONVERSION_TYPE conv_type)  //tipos dos parametros definidos no adc.h
{
	volatile ADC_REG_TYPE *adcPt;
	adcPt = ADC_REGISTERS;
	
	// selecio tensao de referencia:
	adcPt->ADMUX_REG.bit.bit7 = 0;   //tensao de referencia 5V
	adcPt->ADMUX_REG.bit.bit6 = 1;   //tensao de referencia 5V


	if(mode < NUM_OF_MODES)
	{
		if (mode == MODE_8BITS)
		   adcPt->ADMUX_REG.bit.bit5 = 1;  //Micro.h => ADLAR = 1, alinhado a esquerda e a leitura no ADCH (8 bits)
		if (mode == MODE_10BITS)
		   adcPt->ADMUX_REG.bit.bit5 = 0;  //ADLAR = 0, alinhado a direita e a leitura ocorre primeiro no ADCL e depois ADCH (10 bits)
	}
		
	if(conv_type < NUM_OF_CONVERSION_TYPES)
	{
		if (conv_type == AD_SINGLE_CONVERSION)
		   adcPt->ADCSRA_REG.bit.bit5 = 0;      //Micro.h => ADATE = 0, uma leitura
		if (conv_type == AD_CONTINUOUS_CONVERSION){
		   adcPt->ADCSRA_REG.bit.bit5 = 1;       //ADATE = 1, a fonte de disparo pode ser conversao continua, comparador analogico, etc
		   adcPt->ADCSRB_REG.byte &= 0b11111000; //opera apenas nos bits de interesse
		}
	}
}



//---------------------------------------------------------------------------------------------------------------------


//Returns the current ADC value saved in the ADC_Buffer for a specific channel
unsigned short int ADC__GetValue(AD_CHANNEL_TYPE channel)
{
	if(channel < NUM_OF_AD_CHANNELS)
	{
		return ADC_Buffer[channel];  // retorna valor do ADC lido no ADC_Buffer do canal solcitado!
	}
	return 0;
}




//---------------------------------------------------------------------------------------------------------------------
//=====================================================================================================================
//-------------------------------------- PRIVATE Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------------------
