/*
 * timer.h
 *
 * Created: 29/05/2024 13:57:21
 *  Author: gabri
 */ 


#ifndef TIMER_H_
#define TIMER_H_


//-------------------------------------- Include Files ----------------------------------------------------------------


//-------------------------------Defines-----------------------
typedef enum{
	TIMER_EXPIRED = 0,
	TIMER_IS_RUNNING = 1,
}TIMER_STATUS;


/**
 * TIMERS RESOLUTION
 *
 * Recommended values in ms: 1, 5, 20, 25, 50, 100, or 1000
 */
#define MS_TIMERS_RESOLUTION     1//1

typedef enum
{
	KEYBOARD_TIMER_MS = 0,
	DISPLAY_ANIMATION_MS,
	BUZZER_SOUND_MS,
	DELAY_MS,
	GENIUS_MS,
	SNAKE_MS,
	DEBUGGER_MS,
	NUM_OF_MS_TIMERS
} MS_TIMER_NAME;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void Timer__Initialize(void);

void Timer__MsHandler(void);
void Timer__MsSet(MS_TIMER_NAME, unsigned short int);
void Timer__MsExpire(MS_TIMER_NAME); //expira o timer externamente e zera a contagem
TIMER_STATUS Timer__MsGetStatus(MS_TIMER_NAME);

// Protótipo da função de interrupção
ISR(TIMER1_OVF_vect); // Protótipo da Interrupção TIMER1.  Tabela de vetores pag. 158



#endif /* TIMER_H_ */