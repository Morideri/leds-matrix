/*
 * sound.c
 *
 * Created: 17/06/2024 06:41:13
 *  Author: gabriel
 */ 


#include <avr/interrupt.h>


#include "..\Header\micro.h"
#include "..\Header\sound.h"
#include "..\Header\timer.h"
#include  "..\Header\cTypes.h"
#include "..\Header\timer.h"


typedef enum{
	WAIT_STEP,
	SOUND_STEP_1,
	SOUND_STEP_2,
	SOUND_STEP_3,
	SOUND_STEP_4,
	SOUND_STEP_5,
	SOUND_STEP_6,
	TOTAL_SOUND_STEP
}SOUND_STEPS;

	
TICTACTOE_SOUNDS_TYPE soundType;
SOUND_STEPS soundStep;


struct SOUND_DATA soundDataArry[TOTAL_NOTES];
struct SOUND_DATA* ptSoundDataFirstAddress;


void soundKeyPressPlayer1(void);
void soundKeyPressPlayer2(void);
void soundPlayer1Win(void);
void soundPlayer2Win(void);
void soundGameDraw(void);


void soundSetNote(MUSICAL_NOTES note){
	halSetBuzzerNote(&soundDataArry[note]);
}


void soundClrNote(void){
	halSetBuzzerNote(&soundDataArry[0]);
}


void soundInitialize(void){ //inicia variaveis
	soundStep = WAIT_STEP;
	soundType = NO_SOUND;
	ptSoundDataFirstAddress = &soundDataArry[0];
	struct SOUND_DATA* ptSoundDataTemp;
	MUSICAL_NOTES musicalNote = NO_NOTE;
	ptSoundDataTemp = ptSoundDataFirstAddress;
	unsigned char topValue[TOTAL_NOTES] = TOP_VALUES;
	unsigned char prescaler[TOTAL_NOTES] = PRESCALERS;
	
	for(unsigned char i = 0; i<TOTAL_NOTES; i++){
		ptSoundDataTemp->note = musicalNote;
		ptSoundDataTemp->topValue = topValue[i];
		ptSoundDataTemp->prescaler = prescaler[i];
		ptSoundDataTemp++;
		musicalNote++;
	}
}




unsigned char soundGetSoundStatus(void){ //verifica status da etapa do som
	if(soundStep==WAIT_STEP)
		return 1; //retorna 1 se não houver sons tocando
	else
		return 0; //retorna 0 se houver
}

void setSound(TICTACTOE_SOUNDS_TYPE soundSet){
	soundType = soundSet; //define som a ser tocado
	soundStep = SOUND_STEP_1; //primeira posição e garante que algum som seja tocado
}

void soundHandler(void){
	switch(soundType){ //verifica qual som deve ser tocado e chama a função referente a ele
		case NO_SOUND: //não toca som
			break;
			
		case KEY_PRESS_JOGADOR_1:
			soundKeyPressPlayer1();
			break;
				
		case KEY_PRESS_JOGADOR_2:
			soundKeyPressPlayer2();
			break;	
			
		case JOGADOR_1_GANHOU:
			soundPlayer1Win();
			break;
				
		case JOGADOR_2_GANHOU:
			soundPlayer2Win();
			break;
				
		case JOGO_EMPATOU:
			soundGameDraw();
			break;
				
		default:
			break;
	}
}

/*
As funções abaixo sao chamadas pelo soundHandler e possuem uma logica parecida
Primeiro verificam se o timer referente ao buzzer esta expirado
então verifica a etapa atual e executa o que deve
sendo que buzzer ligado e desligado estao em etapas alternadas
*/

void soundKeyPressPlayer1(){
	if(Timer__MsGetStatus(BUZZER_SOUND_MS) == TIMER_EXPIRED){
		switch(soundStep){
			case SOUND_STEP_1:
				halSetBuzzerFreq(2048);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,200);
				soundStep = SOUND_STEP_2;
				break;
			
			case SOUND_STEP_2:
				Hal__SetBuzzer(OFF);
				soundStep = WAIT_STEP;
				soundType = NO_SOUND;
				break;
			
			default:
				soundStep = WAIT_STEP; //garante que nenhuma função seja chamada
				soundType = NO_SOUND;	//reinicia variavel
				break;
		}
	}
}

void soundKeyPressPlayer2(){
	if(Timer__MsGetStatus(BUZZER_SOUND_MS) == TIMER_EXPIRED){
		switch(soundStep){
			case SOUND_STEP_1:
				halSetBuzzerFreq(512);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,200);
				soundStep = SOUND_STEP_2;
				break;
			
			
			case SOUND_STEP_2:
				Hal__SetBuzzer(OFF);
				soundStep = WAIT_STEP;
				soundType = NO_SOUND;
				break;
			
			default:
				soundStep = WAIT_STEP; //garante que nenhuma função seja chamada
				soundType = NO_SOUND;	//reinicia variavel
				break;
		}
	}
}


void soundPlayer1Win(void){
		if(Timer__MsGetStatus(BUZZER_SOUND_MS) == TIMER_EXPIRED){
			switch(soundStep){
				case SOUND_STEP_1:
				halSetBuzzerFreq(1024);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,200);
				soundStep = SOUND_STEP_2;
				break;
				
				case SOUND_STEP_2:
				Hal__SetBuzzer(OFF);
				Timer__MsSet(BUZZER_SOUND_MS,100);
				soundStep = SOUND_STEP_3;
				break;
				
				case  SOUND_STEP_3:
				halSetBuzzerFreq(1024);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,200);
				soundStep = SOUND_STEP_4;
				break;
				
				case  SOUND_STEP_4:
				Hal__SetBuzzer(OFF);
				Timer__MsSet(BUZZER_SOUND_MS,100);
				soundStep = SOUND_STEP_5;
				break;
				
				case  SOUND_STEP_5:
				halSetBuzzerFreq(2048);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,400);
				soundStep = SOUND_STEP_6;
				break;
				
				case  SOUND_STEP_6:
				Hal__SetBuzzer(OFF);
				soundStep = WAIT_STEP;
				soundType = NO_SOUND;
				break;
				
				default:
				Hal__SetBuzzer(OFF);
				soundStep = WAIT_STEP; //garante que nenhuma função seja chamada
				soundType = NO_SOUND;	//reinicia variavel
				break;
		}
	}
}


void soundPlayer2Win(void){
		if(Timer__MsGetStatus(BUZZER_SOUND_MS) == TIMER_EXPIRED){
			switch(soundStep){
				case SOUND_STEP_1:
				halSetBuzzerFreq(1024);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,200);
				soundStep = SOUND_STEP_2;
				break;
				
				case SOUND_STEP_2:
				Hal__SetBuzzer(OFF);
				Timer__MsSet(BUZZER_SOUND_MS,100);
				soundStep = SOUND_STEP_3;
				break;
				
				case  SOUND_STEP_3:
				halSetBuzzerFreq(1024);
				Hal__SetBuzzer(ON);
				Timer__MsSet(BUZZER_SOUND_MS,200);
				soundStep = SOUND_STEP_4;
				break;
				
				case  SOUND_STEP_4:
				Hal__SetBuzzer(OFF);
				Timer__MsSet(BUZZER_SOUND_MS,100);
				soundStep = SOUND_STEP_5;
				break;
				
				case  SOUND_STEP_5:
				halSetBuzzerFreq(512);
				Timer__MsSet(BUZZER_SOUND_MS,400);
				Hal__SetBuzzer(ON);
				soundStep = SOUND_STEP_6;
				break;
				
				case  SOUND_STEP_6:
				Hal__SetBuzzer(OFF);
				soundStep = WAIT_STEP;
				soundType = NO_SOUND;
				break;
				
				default:
				Hal__SetBuzzer(OFF);
				soundStep = WAIT_STEP; //garante que nenhuma função seja chamada
				soundType = NO_SOUND; //reinicia variavel
				break;
		}
	}
}

void soundGameDraw(void){
	if(Timer__MsGetStatus(BUZZER_SOUND_MS) == TIMER_EXPIRED){
		switch(soundStep){
			case SOUND_STEP_1:
			halSetBuzzerFreq(256);
			Hal__SetBuzzer(ON);
			Timer__MsSet(BUZZER_SOUND_MS,400);
			soundStep = SOUND_STEP_2;
			break;
			
			case SOUND_STEP_2:
			Hal__SetBuzzer(OFF);
			Timer__MsSet(BUZZER_SOUND_MS,100);
			soundStep = SOUND_STEP_3;
			break;
			
			case  SOUND_STEP_3:
			halSetBuzzerFreq(128);
			Hal__SetBuzzer(ON);
			Timer__MsSet(BUZZER_SOUND_MS,200);
			soundStep = SOUND_STEP_4;
			break;
			
			case  SOUND_STEP_4:
			Hal__SetBuzzer(OFF);
			Timer__MsSet(BUZZER_SOUND_MS,100);
			soundStep = SOUND_STEP_5;
			break;
			
			case  SOUND_STEP_5:
			halSetBuzzerFreq(128);
			Timer__MsSet(BUZZER_SOUND_MS,200);
			Hal__SetBuzzer(ON);
			soundStep = SOUND_STEP_6;
			break;
			
			case  SOUND_STEP_6:
			Hal__SetBuzzer(OFF);
			soundStep = WAIT_STEP;
			soundType = NO_SOUND;
			break;
			
			default:
			Hal__SetBuzzer(OFF);
			soundStep = WAIT_STEP; //garante que nenhuma função seja chamada
			soundType = NO_SOUND;	//reinicia variavel
			break;
		}
	}
}

