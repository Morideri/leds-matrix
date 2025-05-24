/*
 * atmega328p.h
 *
 * Created: 18/10/2024 09:44:59
 *  Author: gabri
 */ 



#ifndef ATMEGA328P_H_
#define ATMEGA328P_H_

#include "..\Header\defType.h"
#define TOTAL_PORT

/************************************
Criar ponteiro do tipo da estrutura
	volatile XX_REG* NOME_PONTEIRO;
	
iniciar o ponteiro 	
	NOME_PONTEIRO = &addrYY
*************************************/


typedef struct{
	volatile union DEF_BYTE dataIn;
	volatile union DEF_BYTE direction;
	volatile union DEF_BYTE dataOut;
} GPIO_REG;


#define gpioDataB  (*((volatile GPIO_REG *)0x00000023))    //Port B Data Register
#define addrPORTB  &gpioDataB

#define gpioDataC  (*((volatile GPIO_REG *)0x00000026))    //Port C Data Register
#define addrPORTC  &gpioDataC

#define gpioDataD  (*((volatile GPIO_REG *)0x00000029))    //Port D Data Register
#define addrPORTD  &gpioDataD

#define gpioDataVctr {addrPORTB, addrPORTC, addrPORTD};  


// ADC Registers
typedef struct
{
	volatile union DEF_BYTE   adcl;		    /*** ADCL  - Data Result Low  Register;              ***/
	volatile union DEF_BYTE   adch;			/*** ADCH  - Data Result High Register;              ***/
	volatile union DEF_BYTE   adcsra;		/*** ADCSRA - ADC Control and Status  Register A;    ***/
	volatile union DEF_BYTE   adcsrb;	    /*** ADCSRB - ADC Control and Status  Register B;    ***/
	volatile union DEF_BYTE   admux;		/*** ADMUX - ADC Multiplexer election Register;      ***/
	volatile union DEF_BYTE   reserved;		/*** espa?o deixado pelo fabricante                  ***/
	volatile union DEF_BYTE   didr0;		/*** DIDR0 - Digital Input Disable Register;         ***/
	volatile union DEF_BYTE   didr1;		/*** DIDR1 - Digital Input Disable Register;         ***/
} ADC_REG;

#define adcADCL  (*((volatile ADC_REG*)0x78))	/*** ADCL  - Data Result Low  Register;     ***/
#define addrADC  &adcADCL




typedef struct{
	volatile union DEF_BYTE  tccr0a;  //*** TCCR0A  - Timer/Counter Control 0 Register A;     ***/
	volatile union DEF_BYTE  tccr0b;  //*** TCCR0B  - Timer/Counter Control 0 Register B;     ***/
	volatile union DEF_BYTE  tcnt0;   //*** TCNT0   - Timer/Counter 0 Register;               ***/
	volatile union DEF_BYTE  ocr0a;   //*** OCR0A   - Output Compare 0 Register A;            ***/
	volatile union DEF_BYTE  ocr0b;   //*** OCR0B   - Output Compare 0 Register B;            ***/
} TC0_REG;

// TC0 Registers Address
#define TC0_tccr0a  (*((volatile TC0_REG *)0x44))	/*** TCCR0A  - Timer/Counter Control 0 Register A;     ***/
#define addrTC0  &TC0_tccr0a



typedef struct{
	volatile union DEF_BYTE  tccr1a;		/*** TCCR1A  - Timer/Counter Control 1 Register A;  ***/
	volatile union DEF_BYTE  tccr1b;		/*** TCCR1B  - Timer/Counter Control 1 Register B;  ***/
	volatile union DEF_BYTE  tccr1c;		/*** TCCR1C  - Timer/Counter Control 1 Register c;  ***/
	volatile union DEF_BYTE  reserved;		/*** espaco deixado pelo fabricante					***/
	volatile union DEF_BYTE  tcnt1l;		/*** TCNT1L   - Timer/Counter 1 Low Register;       ***/
	volatile union DEF_BYTE  tcnt1h;		/*** TCNT1H   - Timer/Counter 1 High Register;      ***/
	volatile union DEF_BYTE  icr1l;			/*** ICR1L   - Input capture Low Register 1;        ***/
	volatile union DEF_BYTE  icr1h;			/*** ICR1H   - Input capture High Register 1;       ***/
	volatile union DEF_BYTE  ocr1al;		/*** OCR1AL   - Output Compare 1 Low Register A;    ***/
	volatile union DEF_BYTE  ocr1ah;		/*** OCR1AH   - Output Compare 1 High Register A;   ***/
	volatile union DEF_BYTE  ocr1bl;		/*** OCR1BL   - Output Compare 1 Low Register B;    ***/
	volatile union DEF_BYTE  ocr1bh;		/*** OCR1BH   - Output Compare 1 High Register B;   ***/
}TC1_REG;

// TC1 Registers Address
#define TC1_tccr1a  (*((volatile TC1_REG *)0x80))	/*** TCCR1A  - Timer/Counter Control 1 Register A;     ***/
#define addrTC1  &TC1_tccr1a


typedef struct{
	volatile union DEF_BYTE  tccr2a;  /*** TCCR2A  - Timer/Counter Control 2 Register A;     ***/
	volatile union DEF_BYTE  tccr2b;  /*** TCCR2B  - Timer/Counter Control 2 Register B;     ***/
	volatile union DEF_BYTE  tcnt2;   /*** TCNT2   - Timer/Counter 2 Register;               ***/
	volatile union DEF_BYTE  ocr2a;   /*** OCR2A   - Output Compare 2 Register A;            ***/
	volatile union DEF_BYTE  ocr2b;   /*** OCR2B   - Output Compare 2 Register B;            ***/
} TC2_REG;

// TC2 Registers Address
#define TC2_tccr2a  (*((volatile TC2_REG *)0xB0))	/*** TCCR2A  - Timer/Counter Control 0 Register A;     ***/
#define addrTC2  &TC2_tccr2a











#endif /* ATMEGA328P_H_ */