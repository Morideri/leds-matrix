/*
 * GccApplication22.c
 *
 * Created: 20/10/2023 12:28:32
 * Author : gabri
 */ 
#define F_CPU 16000000UL //freq 16Mhz
//modificar arquivos prm na pasta Header
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

#include "..\Header\mainPrm.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
typedef enum
{
	SLOT_1,
	SLOT_2,
	SLOT_3,
	SLOT_4,
	SLOT_5,
	NUM_OF_MAIN_SLOTS
}MAIN_SLOT_TYPE;

//-------------------------------------- Global Variables ----------------------------------------------------------------

MAIN_SLOT_TYPE Slot;


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

int main(void)
{
	Slot = SLOT_1;
	// 16Mhz/64 = 250 kHz
	//250 ciclos a 250 kHz = 1 ms
	// 65535?250+1=65286
	
	TCCR1A = 0;							 //confira timer para opera??o normal pinos OC1A e OC1B desconectados
	TCCR1B = 0;							 //limpa registrador
	TCCR1B |= (1 << CS11) | (1 << CS10); //define o prescaler como 64.
	TCNT1 = 65286;						 //para contar 1ms
	TIMSK1 |= (1 << TOIE1);
	sei();

	
	
	// Functions Initialization
	INITIALIZE_TASKS();
	
	//Main Loop
	for(;;)
	{
	
		ALL_SLOTS_TASKS();
		do{
		
		switch(Slot)
		{
			case SLOT_1:
			SLOT_1_TASKS();
			break;

			case SLOT_2:
			SLOT_2_TASKS();
			break;

			case SLOT_3:
			SLOT_3_TASKS();
			break;

			case SLOT_4:
			SLOT_4_TASKS();
			break;

			case SLOT_5:
			SLOT_5_TASKS();
			break;

			default:
			Slot = SLOT_1;
			break;
		}

		}while(TCNT1 < 65285);
		Slot++;
		if(Slot >= NUM_OF_MAIN_SLOTS)
		Slot = SLOT_1;
	}
}