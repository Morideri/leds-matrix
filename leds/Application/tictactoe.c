/*
 * tictactoe.c
 *
 * Created: 30/08/2024 12:30:51
 *  Author: gabri
 */ 
#include "..\Header\tictactoe.h"
#include "..\Header\keyboard.h"
#include "..\Header\ws2812b.h"
#include "..\Header\timer.h"
#include "..\Header\sound.h"
#include "..\Header\appl.h"
#define totalAdresses ((TOTAL_LINHAS)*(TOTAL_COLUNAS)*(3))

KEY_PRESSED positionInput;
TIC_TAC_TOE_LINHAS linhaAtual;
TIC_TAC_TOE_COLUNAS colunaAtual;
unsigned char turno;
unsigned char jogadorAtual;

TIC_TAC_TOE_STATUS tictactoeStatus;
TIC_TAC_TOE_EVALUATION gameEvaluation;

void tictactoeGenerateMash(void);
void tictactoeEvaluate(void);
unsigned char validCheck(void);
void getPosition (KEY_PRESSED keyPressed);

void tictactoeInitialize(void){ //inicializa as variaveis e limpa o display
	tictactoeStatus = GAME_INITIALIZE;
	positionInput = INVALID_KEY;
	clearDisplay();
}

void tictactoeHandler(){
	positionInput = getKeyBuffer();
	getPosition(positionInput);
	
	switch(tictactoeStatus){
		case GAME_INITIALIZE: //inicializa ou reinicia as variaveis
			linhaAtual = NENHUMA_LINHA;
			colunaAtual = NENHUMA_COLUNA;
			gameEvaluation = ONGOING_GAME;
			turno = 0;
			tictactoeStatus = WAIT_DELAY;
			Timer__MsSet(DELAY_MS,500);
			setDisplay(AZUL, STANDART_BRIGHT);
			setDisplay(VERMELHO, STANDART_BRIGHT);
			
			break;
			
		case WAIT_DELAY:
			if(Timer__MsGetStatus(DELAY_MS) == TIMER_EXPIRED){
				clearDisplay();
				tictactoeGenerateMash();
				tictactoeStatus = WAIT_VALID_PLAY;
			}
			
		case WAIT_VALID_PLAY:
			getPosition(positionInput); //traduz o numero do botão para sua posição relativa na matriz do teclado
			if(!getTictactoePositionValue(linhaAtual, colunaAtual) && positionInput!=INVALID_KEY) //se nao houver nenhuma cor naquela posição
				tictactoeStatus = GAME_UPDATE;
			break;
		
		case GAME_UPDATE:
		jogadorAtual = (turno%2)?JOGADOR_2:JOGADOR_1; //atualiza qual o jogador desse turno, se turno for par Jogador 1, se impar, jogador 2
		changeHouse(linhaAtual, colunaAtual, jogadorAtual, STANDART_BRIGHT);
		if(jogadorAtual) //virifica o jogador par ou impar e inicia o evento de tecla precionada
		setSound(KEY_PRESS_JOGADOR_1);
		else
		setSound(KEY_PRESS_JOGADOR_2);
		tictactoeStatus = GAME_EVALUATE; //atualiza o status do jogo
		break;
		
		case GAME_EVALUATE:
		tictactoeEvaluate();
		if(gameEvaluation == ONGOING_GAME){ //se o jogo nao tiver acabado
			turno++;
			tictactoeStatus = WAIT_VALID_PLAY; //fica no ciclo até uma jogada valida ser registrada
		}
		else{
			if(displayGetAnimationStatus()==1 && soundGetSoundStatus()==1) //aguarda os eventos da tecla precionada acabarem
			tictactoeStatus = GAME_ENDING; //se tiver acabado segue para o proximo status
		}
		break;
		
		case GAME_ENDING:
			if(gameEvaluation==VITORIA){ //caso o jogo tenha terminado em vitoria, inicia os eventos do display e sons refentes ao jogador que jogou por ultimo
				displaySetAnimation(jogadorAtual);
				if(turno%2)
				setSound(JOGADOR_2_GANHOU);
				else
				setSound(JOGADOR_1_GANHOU);
				} else if(gameEvaluation==EMPATE){ //caso tenha terminado em empate, inicia os eventos de empate
				displaySetAnimation(VERDE);
				setSound(JOGO_EMPATOU);
			}
			Timer__MsSet(DELAY_MS, 1000);
			tictactoeStatus = GAME_ENDING_WAIT; //recomeça o jogo
			break;
		
		case GAME_ENDING_WAIT:
			if(Timer__MsGetStatus(DELAY_MS) == TIMER_EXPIRED){
				resetGameMode();
				tictactoeStatus = GAME_INITIALIZE;
			}
			break;
			
		default:
			break;
	}
}


void tictactoeGenerateMash(void){
	for(unsigned char i = 8; i>0; i--){
		changeIndividual(i, 3, VERMELHO, meshBright);
		changeIndividual(i, 3, VERDE, meshBright);
		changeIndividual(3, i, VERMELHO, meshBright);
		changeIndividual(3, i, VERDE, meshBright);
		
		changeIndividual(i, 6, VERMELHO, meshBright);
		changeIndividual(i, 6, VERDE, meshBright);
		changeIndividual(6, i, VERMELHO, meshBright);
		changeIndividual(6, i, VERDE, meshBright);
		
	}
}

void tictactoeEvaluate(void) //verifica as condições de vitoria ou empate (caso o turno atual implique em todas as casas ocupadas e ninguem ganhou, significa empate)
{
	if(ledMatrix[0][0][jogadorAtual] && ledMatrix[0][3][jogadorAtual] && ledMatrix[0][6][jogadorAtual]){ //verifica coluna 1
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[3][0][jogadorAtual] && ledMatrix[3][3][jogadorAtual] && ledMatrix[3][6][jogadorAtual]){ //verifica coluna 2
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[6][0][jogadorAtual] && ledMatrix[6][3][jogadorAtual] && ledMatrix[6][6][jogadorAtual]){ //verifica coluna 3
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[0][0][jogadorAtual] && ledMatrix[3][0][jogadorAtual] && ledMatrix[6][0][jogadorAtual]){ //verifica linha 1
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[0][3][jogadorAtual] && ledMatrix[3][3][jogadorAtual] && ledMatrix[6][3][jogadorAtual]){ //verifica linha 2
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[0][6][jogadorAtual] && ledMatrix[3][6][jogadorAtual] && ledMatrix[6][6][jogadorAtual]){ //verifica linha 3
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[0][0][jogadorAtual] && ledMatrix[3][3][jogadorAtual] && ledMatrix[6][6][jogadorAtual]){ //verifica diagonal principal
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(ledMatrix[0][6][jogadorAtual] && ledMatrix[3][3][jogadorAtual] && ledMatrix[6][0][jogadorAtual]){ //verifica diagonal secundaria
		gameEvaluation = VITORIA; //retorna valor do respectivo jogador
		}else if(turno>7){ //se for o nono turno (começa em zero) e não houve vitória
		gameEvaluation = EMPATE; //retornará valor 3
	}else
	gameEvaluation = ONGOING_GAME; //caso contrario jogo continua normalmente
}

void getPosition(KEY_PRESSED keyPressed){ //traduz o numero do botão para uma posição linha coluna
	if(keyPressed != INVALID_KEY){
		colunaAtual = (keyPressed%3) + 2*(keyPressed%3);
		linhaAtual =  (keyPressed - (keyPressed%3));		
	} else {
		colunaAtual = NENHUMA_COLUNA;
		linhaAtual = NENHUMA_LINHA;
	}
}