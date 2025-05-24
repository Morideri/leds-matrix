/*
 * snake.c
 *
 * Created: 13/09/2024 12:14:34
 *  Author: gabri
 */ 
#include "..\Header\snake.h"
#include "..\Header\keyboard.h"
#include "..\Header\ws2812b.h"
#include "..\Header\timer.h"
#include "..\Header\sound.h"
#include "..\Header\numberGenerator.h"
#include "..\Header\appl.h"
#define snakeNull (struct SNAKE_FIELD_DATA*)((unsigned char*)0)

SNAKE_STEP snakeStep;
SNAKE_MOVE snakeInputMove;
SNAKE_MOVE snakeCurrentMove;
SNAKE_MOVE snakePrevMove;
SNAKE_CONCLUSION snakeConclusion;

struct SNAKE_FIELD_DATA snakeFieldData[snakeAlturaTotal][snakeLarguraTotal]; //snakeFieldData[coordenada Y][coordenada X] operacao como se no terceiro quadrante

struct SNAKE_FIELD_DATA* snakeFirstAddress;
struct SNAKE_FIELD_DATA* snakeLastAddress;
struct SNAKE_FIELD_DATA* snakeArryHead;
struct SNAKE_FIELD_DATA* snakeArryTail;
struct SNAKE_FIELD_DATA* snakePrevArryTail;
struct SNAKE_FIELD_DATA* snakeAppleAddress;

KEY_PRESSED keyPressed;

unsigned char snakeSize;
unsigned char snakeAppleFlag;
int coordenadaY;
int coordenadaX;
unsigned char snakeSpeed;

void snakeClearCache(void);
void snakeInitialCondition(void);
void snakePlaceApple(void);
SNAKE_MOVE snakeKeyInterpreter(KEY_PRESSED inputKey);
void snakeNextMove(SNAKE_MOVE nextMove);
void snakeDisplayUpdate(struct SNAKE_FIELD_DATA* ptData);
void snakeEnd(void);

void snakeInitialize(void){
	snakeFirstAddress = &snakeFieldData[0][0]; //define primeiro endereco
	snakeLastAddress = &snakeFieldData[snakeAlturaTotal-1][snakeLarguraTotal-1]; //define ultimo endereco
	snakeStep = SNAKE_INITIALIZE_STEP; //define a etapa da maquina de estado do snakeHandler
	
	struct SNAKE_FIELD_DATA* ptStructTemp = snakeFirstAddress; //ponteiro temporario aponta para o primeiro endereco
	unsigned char xposition = 0; //primeira posicao da linha
	unsigned char yposition = 0; //primeira linha
	while(ptStructTemp<=snakeLastAddress){ //enquanto o endereco for menor que o ultimo endereco
		ptStructTemp->xcoord = 8-xposition; //recebe a coordenada horizontal
		ptStructTemp->ycoord = 8-yposition; //recebe a coordenada vertical
		//as coordenadas sao rotacionadas pois os dados para a matriz sao enviados de tras para frente
		//prepara a proxima iteracao
		xposition++;
		if(xposition == snakeLarguraTotal){ //quando atingir a ultima posicao daquela linha
			yposition++; //avanca para a proxima linha
			xposition = 0; //volta para a primeira posicao comeco
		}
		ptStructTemp++; //vai para o proximo endereco
	}
}

void snakeHandler(void){
	switch(snakeStep){
		case SNAKE_INITIALIZE_STEP:
			snakeClearCache();
			snakeAppleAddress = snakeNull;
			snakePrevArryTail = snakeNull;
			snakeConclusion = SNAKE_GAME_ONGOING;
			snakeInputMove = SNAKE_NOT_MOVING;
			snakeCurrentMove = SNAKE_NOT_MOVING;
			snakePrevMove = SNAKE_NOT_MOVING;
			snakeSpeed = snakeInitialSpeedMs;
			setDisplay(VERMELHO, 18); //mostra no display...
			setDisplay(VERDE, 18);
			setDisplay(AZUL, 7);
			Timer__MsSet(DELAY_MS, 200); //... por esse tempo em milisegundos
			snakeStep = SNAKE_DELAY_STEP;
			break;
			
		case SNAKE_DELAY_STEP:
			if(Timer__MsGetStatus(DELAY_MS) == TIMER_EXPIRED){ //se o tempo ja tiver passado
				clearDisplay();
				snakeInitialCondition();
				snakeDisplayUpdate(snakeArryHead); //posicionamento inicial da cobra
				snakePlaceApple(); //posiciona uma maca
				snakeDisplayUpdate(snakeAppleAddress);
				Timer__MsSet(SNAKE_MS, 5000);
				snakeStep = SNAKE_INPUT_STEP;	
			}
			break;
			
		case SNAKE_INPUT_STEP:
			keyPressed = getKeyBuffer(); //recebe tecla pressionada
			snakeInputMove = snakeKeyInterpreter(keyPressed); //interpreta a direcao
			if((snakeInputMove!=SNAKE_INVALID_MOVE)&&(snakeInputMove!=snakeCurrentMove)){ //caso o input seja valido
				switch(snakePrevMove){ //verifica se o proximo movimento esta tentando ser se onde a cobra esta vindo
					case SNAKE_NOT_MOVING: //primeiro movimento
					if(snakeInputMove!=SNAKE_LEFT_MOVE){
						snakeCurrentMove = snakeInputMove;
						Timer__MsExpire(SNAKE_MS);
					}
					break;
				
					case SNAKE_UP_MOVE:
					if(snakeInputMove!=SNAKE_DOWN_MOVE) snakeCurrentMove = snakeInputMove;
					break;
				
					case SNAKE_DOWN_MOVE:
					if(snakeInputMove!=SNAKE_UP_MOVE) snakeCurrentMove = snakeInputMove;
					break;
					
					case SNAKE_LEFT_MOVE:
					if(snakeInputMove!=SNAKE_RIGHT_MOVE) snakeCurrentMove = snakeInputMove;
					break;
				
					case SNAKE_RIGHT_MOVE:
					if(snakeInputMove!=SNAKE_LEFT_MOVE) snakeCurrentMove = snakeInputMove;
					break;
				
					default:
					break;
				}
			}

			if(Timer__MsGetStatus(SNAKE_MS) == TIMER_EXPIRED) snakeStep = SNAKE_MOVEMENT_STEP;
			break;
			
		case SNAKE_MOVEMENT_STEP:
			snakeNextMove(snakeCurrentMove);
			snakeDisplayUpdate(snakeArryHead);
			snakeDisplayUpdate(snakeArryTail);
			snakeDisplayUpdate(snakePrevArryTail);
			snakePrevMove = snakeCurrentMove; //atualiza movimento anterior
			Timer__MsSet(SNAKE_MS, snakeSpeed); //timer ate o proximo movimento
			snakeStep = SNAKE_EVALUATION_STEP;
			break;
			
		case SNAKE_EVALUATION_STEP:
			if(snakeConclusion == SNAKE_PLAYER_LOST){
				if(snakeSize){
					if(Timer__MsGetStatus(SNAKE_MS)==TIMER_EXPIRED){
						snakeEnd();
						snakeSize--;
						Timer__MsSet(SNAKE_MS, 50);
					}
					
				}else {
					snakeStep = SNAKE_INITIALIZE_STEP;
					clearDisplay();
					resetGameMode();
				}
			}else{
				if(!snakeAppleFlag){ //caso n haja maca
					snakePlaceApple(); //posiciona a maca
					snakeDisplayUpdate(snakeAppleAddress); //atualiza display
				}
				snakeStep = SNAKE_INPUT_STEP; //avalia proximo input
			}
			break;
		
		default:
			break;
	}
}

/////////////////////////////////////////////////////////////////////
/////////////////////////funcoes privadas////////////////////////////
/////////////////////////////////////////////////////////////////////

void snakeClearCache(void){
	struct SNAKE_FIELD_DATA* ptStructTemp = snakeFirstAddress; //ponteiro temporario aponta para o primeiro endereco
	while(ptStructTemp<=snakeLastAddress){ //enquanto o endereco for menor que o ultimo endereco
		ptStructTemp->field = SNAKE_EMPTY; //inicia sem nada
		ptStructTemp->prev = snakeNull; // Inicializando o ponteiro como null
		ptStructTemp++; //vai para o proximo endereco
	}	
}


void snakeInitialCondition(void){
	snakeSize = 3; //tamanho inicial
	coordenadaX = 3; 
	coordenadaY = 3;
	snakeArryHead = &snakeFieldData[coordenadaY][coordenadaX]; //recebe endereco da primeira parte da cobra
	snakeFieldData[3][3].field = SNAKE_BODY;
	snakeFieldData[3][3].prev = &snakeFieldData[3][2]; //aponta para a parte anterior da cobra
	snakeFieldData[3][2].field = SNAKE_BODY;
	snakeFieldData[3][2].prev = &snakeFieldData[3][1]; //aponta para a parte anterior da cobra
	snakeFieldData[3][1].field = SNAKE_BODY;
	snakeFieldData[3][1].prev = snakeNull; //aponta para o vetor nulo
	snakeArryTail = &snakeFieldData[3][1]; //recebe o ultimo endereco que possui uma parte da cobra
}

void snakePlaceApple(void){
	unsigned char randomNumber = getRandomNumber(RNG_SNAKE);
	struct SNAKE_FIELD_DATA* ptStructTemp = snakeFirstAddress;
	do {
		if(ptStructTemp>=snakeLastAddress){ //caso seja a ultima casa
			ptStructTemp = snakeFirstAddress; //volta para a primeira posicao
		}else ptStructTemp++; //vai para proxima posicao
		if(ptStructTemp->field != SNAKE_BODY) randomNumber--; //so decrementa o valor do numero aleatorio caso o espaco que tentar posicionar a maca esteja livre
	} while (randomNumber>0);
	
	//sai do laco quando estiver em uma posicao vazia e o contador estiver zerado
	ptStructTemp->field = SNAKE_APPLE;
	snakeAppleAddress = ptStructTemp;
	snakeAppleFlag = 1; //maca existe no campo
	if(snakeSpeed>(snakeInitialSpeedMs/2)) snakeSpeed-=2; //diminui o periodo de atraso do movimento ate um limite de o dobro da velocidade
}

SNAKE_MOVE snakeKeyInterpreter(KEY_PRESSED inputKey){
	switch(inputKey){ //interpreta baseada na tecla pressionada
		case KEY_2: //botao superior
		return SNAKE_UP_MOVE;
		break;
		
		case KEY_4: //botao a esquerda
		return SNAKE_LEFT_MOVE;
		break;
		
		case KEY_6: //botao a direita
		return SNAKE_RIGHT_MOVE;
		break;
		
		case KEY_8: //botao inferior
		return SNAKE_DOWN_MOVE;
		break;
		
		default:
		return SNAKE_INVALID_MOVE;
		break;
	}
}


void snakeNextMove(SNAKE_MOVE nextMove){
	struct SNAKE_FIELD_DATA* ptStructTemp = &snakeFieldData[coordenadaY][coordenadaX]; //aponta para a primeira parte da cobra
	//se sair do limite recebe coordenada do extremo oposto
	
	switch(nextMove){ //avalia o proximo movimento
		case SNAKE_UP_MOVE:
			coordenadaY--;
			if(coordenadaY<0) coordenadaY = 7; 
			break;
		
		case SNAKE_RIGHT_MOVE:
			coordenadaX++;
			if(coordenadaX>=snakeLarguraTotal) coordenadaX = 0;
			break;
			
		case SNAKE_LEFT_MOVE:
			coordenadaX--;
			if(coordenadaX<0) coordenadaX = 7;
			break;
			
		case SNAKE_DOWN_MOVE:
			coordenadaY++;
			if(coordenadaY>=snakeAlturaTotal) coordenadaY = 0;
			break;
			
		default:
			break;
	}
	
	snakeArryHead = &snakeFieldData[coordenadaY][coordenadaX]; //atualiza endereco da primeira parte da cobra

	if(snakeArryHead->field == SNAKE_APPLE){ //se a proxima casa for uma maca aumenta o tamanho da cobra
		snakeArryHead->field = SNAKE_BODY; //atualiza para uma parte da cobra
		snakeArryHead->prev = ptStructTemp; //aponta para o endereco anterior
		snakeSize++;
		snakeAppleFlag = 0; //maca comida
		return; //nova parte é acrescentada sem remover a ultima
	}
	
	snakeArryTail->field = SNAKE_EMPTY;
	snakeArryTail->prev = snakeNull;
	
	if(snakeArryHead->field == SNAKE_BODY){ //se houver outra parte da cobra no local desconsiderando a ultima
		snakeArryHead = ptStructTemp;
		snakeConclusion = SNAKE_PLAYER_LOST;
		return;
	}
	
	unsigned char counter = 1; //a primeira iteracao sera feita logo a seguir
	snakeArryHead->field = SNAKE_BODY; //atualiza a nova casa como uma parte da cobra
	snakeArryHead->prev = ptStructTemp; //recebe endereco anterior
	
	while(counter<snakeSize){ //iteracao das demais partes
		counter++; //proxima iteracao
		if(counter == snakeSize){
			snakePrevArryTail = snakeArryTail;
			snakeArryTail = ptStructTemp; //recebe endereco da ultima parte
		}
		ptStructTemp = ptStructTemp->prev; //recebe endereco da parte imediatamente anterior da cobra		
	}
	snakeArryTail->prev = snakeNull; //como é o ultimo endereco o anterior é o vetor null
}


void snakeDisplayUpdate(struct SNAKE_FIELD_DATA* ptData){
	SNAKE_FIELD_TYPE fieldType;
	unsigned char xPos;
	unsigned char yPos;
	unsigned char snakeBright = 31;
	unsigned char snakeBrightSecundary = 0;
	do{
		xPos = ptData->ycoord;
		yPos = ptData->xcoord;
		fieldType = ptData->field;
		switch(fieldType){
			case SNAKE_EMPTY:
				changeIndividual(xPos, yPos, AZUL, 0);
				changeIndividual(xPos, yPos, VERDE, 0);
				changeIndividual(xPos, yPos, VERMELHO, 0);
				break;
			
			case SNAKE_APPLE:
				changeIndividual(xPos, yPos, AZUL, 0);
				changeIndividual(xPos, yPos, VERDE, 0);
				changeIndividual(xPos, yPos, VERMELHO, 31);
				break;
				
			case SNAKE_BODY:
				changeIndividual(xPos, yPos, AZUL, snakeBrightSecundary);
				changeIndividual(xPos, yPos, VERDE, snakeBright);
				changeIndividual(xPos, yPos, VERMELHO, 0);
				if(snakeBright>7)snakeBright--; //brilho minimo
				if(snakeBrightSecundary<7)snakeBrightSecundary++;
				if(ptData==snakeArryTail){
					changeIndividual(xPos, yPos, VERDE, 7);
					changeIndividual(xPos, yPos, VERMELHO, 7);
					changeIndividual(xPos, yPos, AZUL, 0);
					
				}
				break;
			
			default:
				break;
		}
		ptData = ptData->prev;
	}while(ptData != snakeNull);
}

void snakeEnd(void){
	unsigned char xPos;
	unsigned char yPos;
	snakeArryHead->field = SNAKE_EMPTY;
	xPos = snakeArryHead->ycoord;
	yPos = snakeArryHead->xcoord;
	changeIndividual(xPos, yPos, AZUL, 0);
	changeIndividual(xPos, yPos, VERDE, 0);
	changeIndividual(xPos, yPos, VERMELHO, 0);
	snakeArryHead = snakeArryHead->prev;	
}