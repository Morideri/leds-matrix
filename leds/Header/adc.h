/*
 * Adc.h
 *
 * Created: 29/05/2024 13:45:44
 *  Author: gabri
 */ 
/*
O circuito de aproximacoes do ADC requer uma frequencia de entrada entre 50kHz e 200kHz para uma maxima resolucao
para resolucoes menores que 10bits uma frequencia maior pode ser empregada
*/

#ifndef ADC_H_
#define ADC_H_


//-------------------------------------- Include Files ----------------------------------------------------------------

#include "..\Header\micro.h"
#include "..\Header\defType.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define ENABLED   1
#define DISABLED  0

#define CONFIG_AD_CH0     DISABLED
#define CONFIG_AD_CH1     DISABLED
#define CONFIG_AD_CH2     DISABLED
#define CONFIG_AD_CH3     DISABLED
#define CONFIG_AD_CH4     DISABLED
#define CONFIG_AD_CH5     ENABLED

#define ADC_PRM_CHANNEL_DATA {CONFIG_AD_CH0, CONFIG_AD_CH1, CONFIG_AD_CH2, CONFIG_AD_CH3, CONFIG_AD_CH4, CONFIG_AD_CH5}

#define ADC_SAMPLING_TIME	50	//unsigned short int

typedef enum
{
	AD_CH0 = 0,
	AD_CH1,
	AD_CH2,
	AD_CH3,
	AD_CH4,
	AD_CH5,
	NUM_OF_AD_CHANNELS,
}AD_CHANNEL_TYPE;

typedef enum
{
	MODE_8BITS = 0, 	//8  bits mode is 0b00
	MODE_10BITS,	    //10 bits mode is 0b01
	NUM_OF_MODES
}AD_MODE_TYPE;

typedef enum{
	AD_SINGLE_CONVERSION = 0,
	AD_CONTINUOUS_CONVERSION,
	NUM_OF_CONVERSION_TYPES
}AD_CONVERSION_TYPE;



#define ADC_CHANNEL_DATA {AD_CH0, AD_CH1, AD_CH2, AD_CH3, AD_CH4, AD_CH5}
	
	
typedef enum{
	ADC_STEP_INIT = 0,
	ADC_STEP_SAMPLING,
	ADC_STEP_CONFIG_CHANNEL,
	ADC_STEP_WAIT_CONVERSION,
	ADC_STEP_READ_RESULT
}ADC_CONV_STEPS_TYPE;






#define ADC_ENABLED   1
#define ADC_DISABLED  0


#define ADC_PIN_0 ADC_DISABLED
#define ADC_PIN_1 ADC_DISABLED
#define ADC_PIN_2 ADC_DISABLED
#define ADC_PIN_3 ADC_DISABLED
#define ADC_PIN_4 ADC_DISABLED
#define ADC_PIN_5 ADC_ENABLED

#define ADC_TOTAL_PIN 6
#define ADC_TOTAL_SAMPLE 6

#define ADC_DEFAULT_PRECISION ADC_10_BITS
#define ADC_DEFAULT_TENSION_REFERENCE ADC_AVCC
#define ADC_DEFAULT_PIN ADC_CHANNEL_5



typedef enum{
	ADC_SETUP_STEP = 0,
	ADC_SAMPLE_STEP,
	ADC_CONFIG_STEP,
	ADC_WAIT_STEP,
	ADC_READ_STEP
}ADC_PROCESS_STEP;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************ESTRUTURAS PARA O REGISTRADOR ADMUX	*******************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum{
	ADC_AREF = 0,
	ADC_AVCC,
	ADC_REF_RESERVED,
	ADC_INTERN_REF,
}ADC_REFERENCIAL_TENSION;

typedef enum{
	ADC_8_BITS = 0,
	ADC_10_BITS
}ADC_PRECISION;

typedef enum{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_INTERNAL_TEMP,
	ADD_MUX_RESERVED_0, //1001
	ADD_MUX_RESERVED_1, //1010
	ADD_MUX_RESERVED_2, //1011
	ADD_MUX_RESERVED_3, //1100
	ADD_MUX_RESERVED_4, //1101
	ADC_FIXED_TENSION,
	ADC_NO_TENSION
}ADC_MUX;

typedef union{
	u8 admuxReg;
	struct{
		ADC_MUX admuxPinSelect:4; //selecao de pino do adc
		unsigned char admuxReserved:1; //bit sem uso
		ADC_PRECISION admuxPrecision:1; //selecao de alinhamento esquerda ou direita
		ADC_REFERENCIAL_TENSION admuxRef:2; //selecao da tensao de referencia
	}admuxConfig;
}ADC_MULTIPLEXER;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************ESTRUTURAS PARA O REGISTRADOR ADCSRA	*******************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum{
	ADC_CLOCK_BY_1 = 0,
	ADC_CLOCK_BY_2,
	ADC_CLOCK_BY_4,
	ADC_CLOCK_BY_8,
	ADC_CLOCK_BY_16,
	ADC_CLOCK_BY_32,
	ADC_CLOCK_BY_64,
	ADC_CLOCK_BY_128,
}ADC_CLOCK_PRESCALER;

typedef enum{
	ADC_INT_NE = 0,
	ADC_INT_EN
}ADC_INTERRUPT_ENABLE;

typedef enum{
	ADC_INT_FLAG_OFF = 0,
	ADC_INT_FLAG_ON
}ADC_INTERRUPT_FLAG;

typedef enum{
	ADC_AUTOTRIGGER_OFF = 0,
	ADC_AUTOTRIGGER_ON
}ADC_AUTOTRIGGER_ENABLE;

typedef enum{
	ADC_STOP = 0,
	ADC_START	
}ADC_START_CONVERSION;

typedef enum{
	ADC_NE = 0,
	ADC_EN
}ADC_ENABLE;

typedef union{
	u8 adcsraReg;
	struct{
		ADC_CLOCK_PRESCALER adcsraClk:3;
		ADC_INTERRUPT_ENABLE adcsraInt:1;
		ADC_INTERRUPT_FLAG adcsraIntFlag:1;
		ADC_AUTOTRIGGER_ENABLE adcsraAutoTrig:1;
		ADC_START_CONVERSION adcsraStartConv:1;
		ADC_ENABLE adcStart:1;
	}adcsraConfig;
}ADC_STATUS_CONTROL_A;



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************ESTRUTURAS PARA O REGISTRADOR ADCSRB	*******************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum{
	ADC_CONT_CONV = 0,	//conversao continua
	ADC_ANALAG_COMP,	//comparador analogico
	ADC_EXTERN_INT0,	//interrupcao externa 0
	ADC_COMPA_TC0,		//igualdade de comparacao A TC0
	ADC_OVERFLOW_TC0,	//estouro de contagem TC0
	ADC_COMPB_TC1,		//igualdade de comparacao B TC1
	ADC_OVERFLOW_TC1,	//estouro de contagem TC1
	ADC_CAPTURE_EVENT	//evento de captura
}ADC_AUTOTRIGGER_SOURCE;

typedef enum{
	ADC_ACME_OFF = 0,
	ADC_ACME_ON
}ADC_ANALOG_COMP_MUX_ENABLE;

typedef union{
	u8 adcsrbReg;
	struct{
		ADC_AUTOTRIGGER_SOURCE adcsrbAutoSource:3;
		unsigned char adcsrbReservedA:3;
		ADC_ANALOG_COMP_MUX_ENABLE adcsrbAcme:1;
		unsigned char adcsrbReservedB:1;
	}adcsrbConf;	
}ADC_STATUS_CONTROL_B;


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************ESTRUTURAS PARA O REGISTRADOR DIDR0	*******************************//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum{
	ADC_DIGITAL_EN = 0, //se 0, entrada digital esta ativada
	ADC_DIGITAL_NE		//se 1, entrada analogica esta ativada
}ADC_DIGITAL_DISABLE;

typedef union{
	u8 didr0Reg;
	struct{
		ADC_DIGITAL_DISABLE didr0DigitalPin0:1;
		ADC_DIGITAL_DISABLE didr0DigitalPin1:1;
		ADC_DIGITAL_DISABLE didr0DigitalPin2:1;
		ADC_DIGITAL_DISABLE didr0DigitalPin3:1;
		ADC_DIGITAL_DISABLE didr0DigitalPin4:1;
		ADC_DIGITAL_DISABLE didr0DigitalPin5:1;
		u8 didr0Reserved:2;
	}didr0Conf;
}ADC_DIGITAL_INPUT_DISABLE;


typedef struct{
	ADC_MULTIPLEXER adcRegADMUX;
	ADC_STATUS_CONTROL_A adcRegADCSRA;
	ADC_STATUS_CONTROL_B adcRegADCSRB;
	ADC_DIGITAL_INPUT_DISABLE adcRegDIDR0;
}ADC_REGISTERS_CONFIGURATION;



	
//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void adcInitialize(void);

void ADC__Initialize(void);
void ADC__ConfigModes(AD_MODE_TYPE  mode, AD_CONVERSION_TYPE conv_type);
unsigned short int ADC__GetValue(AD_CHANNEL_TYPE channel);
void ADC__Handler(void);
#endif /* ADC_H_ */
