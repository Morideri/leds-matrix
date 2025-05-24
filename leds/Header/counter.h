/*
 * counter.h
 *
 * Created: 14/10/2024 10:55:49
 *  Author: gabri
 */ 


#ifndef COUNTER_H_
#define COUNTER_H_


union BYTE{
	unsigned char byte;
	struct
	{
		unsigned char bit0 :1;
		unsigned char bit1 :1;
		unsigned char bit2 :1;
		unsigned char bit3 :1;
		unsigned char bit4 :1;
		unsigned char bit5 :1;
		unsigned char bit6 :1;
		unsigned char bit7 :1;
	} bit;
};



typedef enum{
	act1 = 0,
	act2,
	act3,
	act4
}PIN_ACTION;



//opera sobre os bits 0 1 e 2 do TCCR0B
typedef enum { 
	tcStop = 0,
	clkMode1,
	clkMode2,
	clkMode3,
	clkMode4,
	clkMode5,
	clkFall,
	clkRise
}CLOCK_SELECTION_TIMER_0;

typedef enum {
	opNormal = 0,
	opCorrect,
	opCTC,
	opFast,
}OPERATION_MODE_TIMER_0;

typedef enum { //para pwm rapido e pwm fase corrigida deve-se ativar o pino WGM02 do registrador TCCR0B
	topStd = 0,
	topOCR
}COUNTER_TOP_VALUE;


typedef union{
	union BYTE byteA;
	struct{
		OPERATION_MODE_TIMER_0 opMode:2;
		unsigned char reservedA:2;
		PIN_ACTION pinAction:4;
	}bitFieldA;
}REGISTER_A_COUNTER;

typedef union{
	union BYTE byteB;
	struct{
		CLOCK_SELECTION_TIMER_0 clkSel:3;
		COUNTER_TOP_VALUE topVal:1;
		unsigned char reservedB;
	}bitFieldB;
}REGISTER_B_COUNTER;

struct{
	REGISTER_A_COUNTER regA;	
	REGISTER_B_COUNTER regB;
}COUNTER_8_BITS_CONFIGURATION;









#endif /* COUNTER_H_ */