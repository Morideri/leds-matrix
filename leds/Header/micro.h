/*
 * micro.h
 *
 * Created: 29/05/2024 13:55:03
 *  Author: gabri
 */ 


#ifndef MICRO_H_
#define MICRO_H_



#include <avr/io.h>

// ************************************  Enums, Structs *****************************************************
//union Low Byte bit definitions Bits 0 - 7
typedef union
{
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
} DEF_LOWBYTE;

//union High Byte bit definitions Bits 8 - 15
typedef union
{
	unsigned char byte;
	struct
	{
		unsigned char bit8 :1;
		unsigned char bit9 :1;
		unsigned char bit10 :1;
		unsigned char bit11 :1;
		unsigned char bit12 :1;
		unsigned char bit13 :1;
		unsigned char bit14 :1;
		unsigned char bit15 :1;
	} bit;
} DEF_HIBYTE;


// ***************************  GPIO Ports Registers ********************************************************
// Port Data and Direction Registers
typedef struct
{
	volatile DEF_LOWBYTE DATA_IN_REG;
	volatile DEF_LOWBYTE DIRECION_REG;
	volatile DEF_LOWBYTE DATA_OUT_PULL_REG;
} GPIO_DATA_TYPE;

// Port Data and Direction Registers Address
#define GPIOB_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000023))    //Port B Data Register
#define GPIOC_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000026))    //Port C Data Register
#define GPIOD_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000029))    //Port D Data Register

#define adressPORTB  &GPIOB_DATA
#define adressPORTC  &GPIOC_DATA
#define adressPORTD  &GPIOD_DATA
#define GPIO_DATA {adressPORTB, adressPORTC, adressPORTD};   






// ADC Registers    
typedef struct
{
	volatile DEF_LOWBYTE   ADCL_REG;     /*** ADCL  - Data Result Low  Register;              ***/
	volatile DEF_HIBYTE    ADCH_REG;     /*** ADCH  - Data Result High Register;              ***/
	volatile DEF_LOWBYTE   ADCSRA_REG;   /*** ADCSRA - ADC Control and Status  Register A;    ***/
	volatile DEF_LOWBYTE   ADCSRB_REG;   /*** ADCSRB - ADC Control and Status  Register B;    ***/
	volatile DEF_LOWBYTE   ADMUX_REG;	 /*** ADMUX - ADC Multiplexer election Register;      ***/
	volatile DEF_LOWBYTE   LIXO;         /*** espa?o deixado pelo fabricante                  ***/
	volatile DEF_LOWBYTE   DIDR0_REG;	 /*** DIDR0 - Digital Input Disable Register;         ***/
	volatile DEF_LOWBYTE   DIDR1_REG;	 /*** DIDR1 - Digital Input Disable Register;         ***/
} ADC_REG_TYPE;

// Port Data and Direction Registers Address
#define ADC_ADCL  (*((volatile ADC_REG_TYPE *)0x78))	/*** ADCL  - Data Result Low  Register;     ***/
#define ADC_REGISTERS  &ADC_ADCL




// PWM registers

typedef struct
{
	volatile DEF_LOWBYTE  TCCR0A_REG;  //*** TCCR0A  - Timer/Counter Control 0 Register A;     ***/
	volatile DEF_LOWBYTE  TCCR0B_REG;  //*** TCCR0B  - Timer/Counter Control 0 Register B;     ***/
	volatile DEF_LOWBYTE  TCNT0_REG;   //*** TCNT0   - Timer/Counter 0 Register;               ***/
	volatile DEF_LOWBYTE  OCR0A_REG;   //*** OCR0A   - Output Compare 0 Register A;            ***/
	volatile DEF_LOWBYTE  OCR0B_REG;   //*** OCR0B   - Output Compare 0 Register B;            ***/
} TC0_REG_TYPE;

// TC0 Registers Address
#define TC0_TCCR0A  (*((volatile TC0_REG_TYPE *)0x44))	/*** TCCR0A  - Timer/Counter Control 0 Register A;     ***/

//#define TC0_TCCR0B  (*((volatile DEF_LOWBYTE *)0x00))    /*** TCCR0B  - Timer/Counter Control 0 Register B;     ***/
//#define TC0_TCNT0   (*((volatile DEF_LOWBYTE *)0x00))    /*** TCNT0   - Timer/Counter 0 Register;               ***/
//#define TC0_OCR0A   (*((volatile DEF_LOWBYTE *)0x00))    /*** OCR0A   - Output Compare 0 Register A;            ***/
//#define TC0_OCR0B  (*((volatile DEF_LOWBYTE  *)0x00))     /*** OCR0B   - Output Compare 0 Register B;            ***/

#define TC0_REGISTERS  &TC0_TCCR0A

typedef struct
{
	volatile DEF_LOWBYTE  TCCR1A_REG;  /*** TCCR1A  - Timer/Counter Control 1 Register A;     ***/
	volatile DEF_LOWBYTE  TCCR1B_REG;  /*** TCCR1B  - Timer/Counter Control 1 Register B;     ***/
	volatile DEF_LOWBYTE  TCCR1C_REG;  /*** TCCR1C  - Timer/Counter Control 1 Register c;     ***/
	volatile DEF_LOWBYTE  LIXO;    /*** espa?o deixado pelo fabricante    */
	volatile DEF_LOWBYTE  TCNT1L_REG;  /*** TCNT1L   - Timer/Counter 1 Low Register;        ***/
	volatile DEF_HIBYTE   TCNT1H_REG;  /*** TCNT1H   - Timer/Counter 1 High Register;       ***/
	volatile DEF_LOWBYTE  ICR1L_REG;   /*** ICR1L   - Input capture Low Register 1;         ***/
	volatile DEF_HIBYTE   ICR1H_REG;   /*** ICR1H   - Input capture High Register 1;        ***/
	volatile DEF_LOWBYTE  OCR1AL_REG;  /*** OCR1AL   - Output Compare 1 Low Register A;     ***/
	volatile DEF_HIBYTE   OCR1AH_REG;  /*** OCR1AH   - Output Compare 1 High Register A;    ***/
	volatile DEF_LOWBYTE  OCR1BL_REG;  /*** OCR1BL   - Output Compare 1 Low Register B;     ***/
	volatile DEF_HIBYTE   OCR1BH_REG;  /*** OCR1BH   - Output Compare 1 High Register B;    ***/
}TC1_REG_TYPE;

// TC1 Registers Address
#define TC1_TCCR1A  (*((volatile TC1_REG_TYPE *)0x80))	/*** TCCR1A  - Timer/Counter Control 1 Register A;     ***/
//#define TC1_TCCR1B  (*((volatile DEF_LOWBYTE *)0x00))    /*** TCCR1B  - Timer/Counter Control 1 Register B;     ***/
//#define TC1_TCCR1C  (*((volatile DEF_LOWBYTE *)0x00))    /*** TCCR1B  - Timer/Counter Control 1 Register C;     ***/
//#define TC1_TCNT1L   (*((volatile DEF_LOWBYTE *)0x00))    /*** TCNT1L   - Timer/Counter 1 Low Register;         ***/
//#define TC1_TCNT1H   (*((volatile DEF_LOWBYTE *)0x00))    /*** TCNT1H   - Timer/Counter 1 High Register;        ***/
//#define TC1_ICR1L   (*((volatile DEF_LOWBYTE *)0x00))    /*** ICR1L   - Input capture Low Register 1;           ***/
//#define TC1_ICR1H   (*((volatile DEF_LOWBYTE *)0x00))    /*** ICR1H   - Input capture High Register 1;          ***/
//#define TC1_OCR1AL   (*((volatile DEF_LOWBYTE *)0x00))    /*** OCR1AL   - Output Compare 0 Low Register A;      ***/
//#define TC1_OCR1AH   (*((volatile DEF_LOWBYTE *)0x00))    /*** OCR1AH   - Output Compare 0 High Register A;     ***/
//#define TC1_OCR1BL  (*((volatile DEF_LOWBYTE *)0x00))     /*** OCR1BL   - Output Compare 0 Low Register B;      ***/
//#define TC1_OCR1BH  (*((volatile DEF_LOWBYTE *)0x00))     /*** OCR1BH   - Output Compare 0 High Register B;     ***/

#define TC1_REGISTERS  &TC1_TCCR1A

typedef struct
{
	volatile DEF_LOWBYTE  TCCR2A_REG;  /*** TCCR2A  - Timer/Counter Control 2 Register A;     ***/
	volatile DEF_LOWBYTE  TCCR2B_REG;  /*** TCCR2B  - Timer/Counter Control 2 Register B;     ***/
	volatile DEF_LOWBYTE  TCNT2_REG;   /*** TCNT2   - Timer/Counter 2 Register;               ***/
	volatile DEF_LOWBYTE  OCR2A_REG;   /*** OCR2A   - Output Compare 2 Register A;            ***/
	volatile DEF_LOWBYTE  OCR2B_REG;   /*** OCR2B   - Output Compare 2 Register B;            ***/
} TC2_REG_TYPE;

// TC2 Registers Address
#define TC2_TCCR2A  (*((volatile TC2_REG_TYPE *)0xB0))	/*** TCCR2A  - Timer/Counter Control 0 Register A;     ***/
//#define TC2_TCCR2B  (*((volatile DEF_LOWBYTE *)0x00))    /*** TCCR2B  - Timer/Counter Control 0 Register B;     ***/
//#define TC2_TCNT2   (*((volatile DEF_LOWBYTE *)0x00))    /*** TCNT2   - Timer/Counter 0 Register;               ***/
//#define TC2_OCR2A   (*((volatile DEF_LOWBYTE *)0x00))    /*** OCR2A   - Output Compare 0 Register A;            ***/
//#define TC2_OCR2B  (*((volatile DEF_LOWBYTE  *)0x00))     /*** OCR2B   - Output Compare 0 Register B;            ***/

#define TC2_REGISTERS  &TC2_TCCR2A




#endif /* MICRO_H_ */