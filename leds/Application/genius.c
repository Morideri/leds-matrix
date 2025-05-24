/*
 * genius.c
 *
 * Created: 30/08/2024 13:34:37
 *  Author: gabri
 */ 
#include "..\Header\genius.h"
#include "..\Header\keyboard.h"
#include "..\Header\ws2812b.h"
#include "..\Header\timer.h"
#include "..\Header\sound.h"
#include "..\Header\numberGenerator.h"
#include "..\Header\appl.h"


GENIUS_CORES geniusVector[2*geniusMaxCounter];
GENIUS_CORES *geniusPt;


GENIUS_CORES geniusUserInputColor;
GENIUS_CORES geniusActualColor;

GENIUS_STEP geniusStep;

GENIUS_CONCLUSION geniusConclusion;
KEY_PRESSED geniusKeyPressed;

unsigned char desligarDisplay;

#define geniusVectorFirstAdress &geniusVector[0]

unsigned char geniusCurrentTurn;
unsigned char geniusTurnCounter;
unsigned char geniusUserCounter;
unsigned char geniusUpdateInputFlag;
void clearGeniusVector(void);
void geniusShowData(GENIUS_CORES geniusColor);

void geniusInitialize(){
	geniusCurrentTurn = 0;
	geniusStep = GENIUS_INITIALIZE;
}

void geniusHandler(unsigned char hardModeFlag){
	if(Timer__MsGetStatus(DELAY_MS) == TIMER_EXPIRED){
		switch(geniusStep){
			case GENIUS_INITIALIZE:
				geniusCurrentTurn = 0;
				geniusUserCounter = 0;
				desligarDisplay = 0;
				geniusUpdateInputFlag = 0;
				geniusConclusion = GENIUS_WAIT_INPUT;
				geniusKeyPressed = INVALID_KEY;
				geniusUserInputColor = GENIUS_INVALID_COLOR;
				clearGeniusVector();
				if(hardModeFlag){
					setDisplay(VERDE, 15);
					setDisplay(VERMELHO, STANDART_BRIGHT);
				}else{
					setDisplay(VERDE, STANDART_BRIGHT);
					setDisplay(VERMELHO, STANDART_BRIGHT);
				}
				Timer__MsSet(DELAY_MS, 500);
				geniusStep = GENIUS_WAIT_STEP;
				break;
				
			case GENIUS_WAIT_STEP:
				clearDisplay();
				geniusStep =  GENIUS_SETUP_STEP;
				break;
				
			case GENIUS_SETUP_STEP:
				if(hardModeFlag){
					geniusVector[geniusCurrentTurn] = (GENIUS_CORES)(getRandomNumber(RNG_GENIUS_HARD)); //
				}else{
					geniusVector[geniusCurrentTurn] = (GENIUS_CORES)(getRandomNumber(RNG_GENIUS)); //
				}
				
				geniusTurnCounter = 0;  //inicia a variável para o proximo passo
				geniusStep = GENIUS_SHOW_COLOR_STEP;
				break;
				
			case GENIUS_SHOW_COLOR_STEP:
				if(geniusTurnCounter<=geniusCurrentTurn){
					if(!desligarDisplay){
						geniusActualColor = geniusVector[geniusTurnCounter];
						geniusShowData(geniusActualColor);
						geniusTurnCounter++;
						Timer__MsSet(DELAY_MS, 500);
						desligarDisplay = 1;	
					}else{
						clearDisplay();
						Timer__MsSet(DELAY_MS, 200);
						desligarDisplay = 0;
					}
					
				} else {
					geniusStep = GENIUS_INPUT_SETUP_STEP;
				}
				
				break;
			
			case GENIUS_INPUT_SETUP_STEP:
				clearDisplay();
				Timer__MsSet(GENIUS_MS, 5000);
				geniusStep = GENIUS_INPUT_STEP; //GENIUS_INPUT_STEP
				break;
				
			case GENIUS_INPUT_STEP:
			
				//se em algum momento que entrar em GENIUS_INPUT_STEP getKeyBuffer estiver como INVALID_KEY, isto eh, se o botao estiver despressionado, a flag de update atualiza
				if(getKeyBuffer() == INVALID_KEY) geniusUpdateInputFlag = 1;
			
				if(geniusUpdateInputFlag){
					geniusKeyPressed = getKeyBuffer();
					if(hardModeFlag){
						switch(geniusKeyPressed){
							case KEY_2:
							geniusUserInputColor = GENIUS_AZUL;
							break;
							
							case KEY_4:
							geniusUserInputColor = GENIUS_VERMELHO;
							break;
							
							case KEY_6:
							geniusUserInputColor = GENIUS_VERDE;
							break;
							
							case KEY_8:
							geniusUserInputColor = GENIUS_AMARELO;
							break;
							
							//para genius hard mode//
							case KEY_1:
							geniusUserInputColor = GENIUS_CYAN;
							break;
							
							case KEY_3:
							geniusUserInputColor = GENIUS_PURPLE;
							break;
							
							case KEY_7:
							geniusUserInputColor = GENIUS_PINK;
							break;
							
							case KEY_9:
							geniusUserInputColor = GENIUS_WHITE;
							break;
							
							default:
							geniusUserInputColor = GENIUS_INVALID_COLOR;
							break;
						}
					}else{
						switch(geniusKeyPressed){
							case KEY_2:
							geniusUserInputColor = GENIUS_AZUL;
							break;
							
							case KEY_4:
							geniusUserInputColor = GENIUS_VERMELHO;
							break;
							
							case KEY_6:
							geniusUserInputColor = GENIUS_VERDE;
							break;
							
							case KEY_8:
							geniusUserInputColor = GENIUS_AMARELO;
							break;
							
							default:
							geniusUserInputColor = GENIUS_INVALID_COLOR;
							break;
						}
						
					}
					
				}
				
				if(geniusUserInputColor != GENIUS_INVALID_COLOR){
					geniusUpdateInputFlag = 0;	
					geniusShowData(geniusUserInputColor);
				}
				geniusStep = GENIUS_EVALUATION_STEP;
				break; 
			
			case GENIUS_EVALUATION_STEP:
				if(Timer__MsGetStatus(GENIUS_MS) == TIMER_EXPIRED){ //jogador demorou de mais
					geniusConclusion = GENIUS_USER_LOST;
				}else if(geniusUserInputColor == GENIUS_INVALID_COLOR){ //ainda ha tempo, mas um input de jogada nao foi contabilizado
					geniusConclusion = GENIUS_WAIT_INPUT;
				}else if(geniusVector[geniusUserCounter] != geniusUserInputColor){ //jogada errada
					geniusConclusion = GENIUS_USER_LOST;
				}else if(geniusUserCounter < geniusCurrentTurn){ //jogada correta mas ainda faltam outras 
					geniusConclusion = GENIUS_TURN_NOT_ENDED;
				}else if(geniusCurrentTurn < (geniusMaxCounter + 8*hardModeFlag)-1){ //turno vencido mas restam outros existem 8 turnos a mais no modo dificil
					geniusConclusion = GENIUS_NEXT_TURN;
				}else {
					geniusConclusion = GENIUS_USER_WON;
				}
				geniusStep = GENIUS_CONCLUSION_STEP;
				break;
				
			case GENIUS_CONCLUSION_STEP:
				switch(geniusConclusion){
					case GENIUS_WAIT_INPUT:
					geniusStep = GENIUS_INPUT_STEP;
					break;
					
					case GENIUS_TURN_NOT_ENDED:
					Timer__MsSet(DELAY_MS, 200);
					geniusUserInputColor = GENIUS_INVALID_COLOR;
					geniusUserCounter++;
					geniusStep = GENIUS_INPUT_SETUP_STEP;
					break;
					
					case GENIUS_NEXT_TURN:
					Timer__MsSet(DELAY_MS, 200);
					geniusUserInputColor = GENIUS_INVALID_COLOR;
					geniusUserCounter = 0;
					geniusCurrentTurn++;
					geniusStep = GENIUS_SETUP_STEP;
					break;
					
					case GENIUS_USER_LOST:
					displaySetAnimation(VERMELHO);
					clearDisplay();
					geniusStep = GENIUS_EXIT_STEP;
					break;
					
					case GENIUS_USER_WON:
					clearDisplay();
					displaySetAnimation(VERDE);
					geniusStep = GENIUS_EXIT_STEP;
					break;
						
					
					default:
					break;
				}
				break;
				
			case GENIUS_EXIT_STEP:
			if(displayGetAnimationStatus()){
				resetGameMode();
				geniusStep = GENIUS_INITIALIZE;
			}
			default:
				break;
		}
	}
}

void geniusShowData(GENIUS_CORES geniusColor){
	clearDisplay();
	switch(geniusColor){
		case GENIUS_INVALID_COLOR:
			break;
		
		case GENIUS_AZUL:
			changeHouse(0, 3, AZUL, STANDART_BRIGHT);
			break;
			
		case GENIUS_VERMELHO:
			changeHouse(3, 0, VERMELHO, STANDART_BRIGHT);
			break;
			
		case GENIUS_VERDE:
			changeHouse(3, 6, VERDE, STANDART_BRIGHT);
			break;
			
		case GENIUS_AMARELO:
			changeHouse(6, 3, VERDE, STANDART_BRIGHT);
			changeHouse(6, 3, VERMELHO, STANDART_BRIGHT);
			break;
			
		case GENIUS_CYAN:
			changeHouse(0, 0, VERDE, STANDART_BRIGHT);
			changeHouse(0, 0, AZUL, STANDART_BRIGHT);
			break;
			
		case GENIUS_PURPLE:
			changeHouse(0, 6, VERMELHO, 24);
			changeHouse(0, 6, AZUL, 24);
			break;
			
		case GENIUS_PINK:
			changeHouse(6, 0, VERMELHO, 32);
			changeHouse(6, 0, AZUL, 7);
			changeHouse(6, 0, VERDE, 7);
			break;
			
		case GENIUS_WHITE:
			changeHouse(6, 6, VERMELHO, STANDART_BRIGHT);
			changeHouse(6, 6, AZUL, STANDART_BRIGHT);
			changeHouse(6, 6, VERDE, STANDART_BRIGHT);
			break;
			
		default:
			break;
	}
}


void clearGeniusVector(){
	geniusPt = &geniusVector[0];
	
	for(unsigned char i = geniusMaxCounter; i>0; i--, geniusPt++){
		*geniusPt = 0;
	}
}

