/*
 * timer.c
 *
 * Created: 29/05/2024 15:59:03
 *  Author: gabri
 */ 
//-------------------------------------- Include Files ----------------------------------------------------------------
#include <avr/interrupt.h>
#include "..\Header\cTypes.h"
#include "..\Header\timer.h"


//------------------------- Variáveis Globais---------------------
unsigned char flag_mili_seg = 0;    // variável global para saber se passou 1 mili segundo.


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------

//!Millisecond Timer structure
typedef struct
{
	TIMER_STATUS Status;
    unsigned short int Count;
}TYPE_MSTIMER;

TYPE_MSTIMER Ms_Timers[NUM_OF_MS_TIMERS];
 
#if (MS_TIMERS_RESOLUTION < 1)
    #error The MS_TIMERS_RESOLUTION parameter must be 1 or greater!!!.
#endif

#define cpl_bit(REG,BIT) (REG ^= (1<<BIT))
#define clr_bit(REG,BIT) (REG &= ~(1<<BIT))

//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

void Timer__Initialize(void)
{
	unsigned char i;

	for (i=0; i < NUM_OF_MS_TIMERS; i++)
	{
		Ms_Timers[i].Status = TIMER_EXPIRED;
		Ms_Timers[i].Count = 0;
	}
}


//===================================== All Handlers ==========================+=====================

void Timer__MsHandler(void)
{
	unsigned char i;
	if(flag_mili_seg>0){
		for(i=0; i < NUM_OF_MS_TIMERS; i++)                       
		{
			if(Ms_Timers[i].Status == TIMER_IS_RUNNING) 	//Is this timer running?
			{
				Ms_Timers[i].Count--;                   
				if(!(Ms_Timers[i].Count))               
				{
					Ms_Timers[i].Status = TIMER_EXPIRED;   //Set timer timeout
				}
			}
		}
	flag_mili_seg--;
	
	}
	
}

//===================================== MillisecondTimers ==========================+=====================
/**
 *
 */
void Timer__MsSet(MS_TIMER_NAME id, unsigned short int ms_value)
{
	unsigned long time;                           
	
	if (id < NUM_OF_MS_TIMERS)
	{
		if (ms_value < MS_TIMERS_RESOLUTION)                     
		{
			Ms_Timers[id].Status = TIMER_EXPIRED;                   
		}
		else                                        
		{   
			time = ms_value / MS_TIMERS_RESOLUTION;
			Ms_Timers[id].Count = (unsigned short int)time;  
			
			Ms_Timers[id].Status = TIMER_IS_RUNNING;		
			
		}
	}
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * 
 */
void Timer__MsExpire(MS_TIMER_NAME id)
{
	if (id < NUM_OF_MS_TIMERS)
	{
		Ms_Timers[id].Count = 0;
		Ms_Timers[id].Status = TIMER_EXPIRED;
	}
}

//-----------------------------------------------------------------------------------------------------------------
/**
 * 
 */
TIMER_STATUS Timer__MsGetStatus (MS_TIMER_NAME id)
{
	return (Ms_Timers[id].Status);
}



//=====================================================================================================================
//-------------------------------------- Interruption  Functions ------------------------------------------------------------
//=====================================================================================================================
ISR(TIMER1_OVF_vect)                              //interrupção do TIMER1 (pg.158){
{
	TCNT1 = 65295;   //para contar a cada 1ms top 65536
	flag_mili_seg++;    //seta o flag indicando que passou 1ms	
}



