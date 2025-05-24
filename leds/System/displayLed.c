/*
 * displayLed.c
 *
 * Created: 05/06/2024 13:54:26
 *  Author: gabri
 */ 

#include "..\Header\ws2812b.h"
#include "..\Header\cTypes.h"
#include "..\Header\tictactoe.h"
#include "..\Header\timer.h"

//defines e declarations

unsigned char ledMatrix[QUANTIDADE_LINHAS][QUANTIDADE_COLUNAS][QUANTIDADE_CORES];
unsigned char* ptMatrix;
unsigned char updateFlag;

unsigned char ongoingAnimation;



typedef enum{
	NO_ANIMATION = 0,
	ANIMATION_STEP_1,
	ANIMATION_STEP_2,
	ANIMATION_STEP_3,
	ANIMATION_STEP_4,
	ANIMATION_STEP_5,
	ANIMATION_STEP_6,
	TOTAL_ANIMATION_STEPS
}DISPLAY_ANIMATION_STEP;


TIC_TAC_TOE_ANIMATION_TYPES tictactoeAnimation;
DISPLAY_ANIMATION_STEP animationStep;
CORES_PRIMARIAS diplayCor;


void displayAnimation(void);

unsigned char displayGetAnimationStatus(void){ //função que retorna status da animação
	if(animationStep==NO_ANIMATION) //se animationStep for diferente de NO_ANIMATION
		return 1;
	else
		return 0;
}

void displaySetAnimation(unsigned char animationType){ //define a cor que ira piscar em todo display
	if(animationStep==NO_ANIMATION){
		if(animationType == 0){
			diplayCor = AZUL;
		}else if(animationType == 1){
			diplayCor = VERMELHO;
		}else if(animationType == 2){
			diplayCor = VERDE;
		}
	animationStep = ANIMATION_STEP_1; //permite que animação inicie
	}
}

void displayHandler(void){
	if(animationStep!=NO_ANIMATION) //se diferente de no animation
		displayAnimation(); 
}


//private functions
void setAll(CORES_PRIMARIAS cor, unsigned char intensidade_da_cor);
void clearAll(void);

void ledInitialize(void){ //inicia variaveis
	clearAll(); //garante display limpo
	halLedInitialize(); //inicia a camada HAL referente aos leds
	tictactoeAnimation = NO_ANIMATION; 
}

void displayBackgroundHandler(void){
	if(updateFlag){ //verifica se o displau deve ser atualizado
		sendDataToDisplay(matrixLastAddress); //atualiza
		updateFlag = FALSE; //define que display ja foi atualizado
	}
}

unsigned short int getTictactoePositionValue(unsigned char row, unsigned char col){ //verifica se ha valores nao nulos na posição de parametro de entrada
	unsigned short int positionValue = 0;
	positionValue += ledMatrix[row][col][VERDE];
	positionValue += ledMatrix[row][col][VERMELHO]; 
	positionValue += ledMatrix[row][col][AZUL];
	return positionValue; //se houver, o valor de retorno sera não-nulo
}

void changeIndividual(unsigned char linha, unsigned char coluna, CORES_PRIMARIAS cor, unsigned char intensidade_da_cor){ //muda um unico led
	ledMatrix[QUANTIDADE_LINHAS - linha][QUANTIDADE_COLUNAS - coluna][cor] = intensidade_da_cor; //atualiza a matriz
	updateFlag = TRUE; //indica que o display deve ser atualizado
}

void changeHouse(unsigned char linha, unsigned char coluna, CORES_PRIMARIAS cor, unsigned char brilho){ //muda 4 leds para determinada cor
	ledMatrix[linha][coluna][cor] = brilho;
	ledMatrix[linha+1][coluna][cor] = brilho;
	ledMatrix[linha][coluna+1][cor] = brilho;
	ledMatrix[linha+1][coluna+1][cor] = brilho;
	updateFlag = TRUE; //indica que o display deve ser atualizado
}

void clearHouse(unsigned char linha, unsigned char coluna){ //muda 4 leds para determinada cor
	for(unsigned char i = 0; i < 3; i++){
		ledMatrix[linha][coluna][i] = 0;
		ledMatrix[linha+1][coluna][i] = 0;
		ledMatrix[linha][coluna+1][i] = 0;
		ledMatrix[linha+1][coluna+1][i] = 0;
	}
	updateFlag = TRUE; //indica que o display deve ser atualizado
}

void clearDisplay(void){ //função externa que limpa o display
	clearAll();
}

void setDisplay(CORES_PRIMARIAS cor, unsigned char brilho){  //função externa que liga todos os leds de determianda cor
	setAll(cor, brilho);
}

////private
void setAll(CORES_PRIMARIAS cor, unsigned char intensidade_da_cor) //função que liga todos os bits da matrizLED
{
	ptMatrix = matrixFirstAddress; //endereço do primeiro elemento da matriz led mais o valor da cor a ser modificada
	ptMatrix+=cor; //aponta para o endereço da cor
	
	for(unsigned char contador = TOTAL_PIXELS; contador > 0; contador--, ptMatrix+=QUANTIDADE_CORES){ //posição do ponteiro incrementa em 3 para que sempre fique na mesma cor
		*ptMatrix = intensidade_da_cor; //o conteudo para onde o ponteiro aponta recebe o parametro de entrada instensidade da cor
	}
	updateFlag = TRUE; //indica que o display deve ser atualizado
}

void clearAll(){
	ptMatrix = matrixFirstAddress; //endereço do primeiro elemento da matriz led mais o valor da cor a ser modificada
	for(unsigned char contador = 0; contador < TOTAL_LEDS; contador++, ptMatrix++){ //posição do ponteiro incrementa em 3 para que sempre fique na mesma cor
		*ptMatrix = 0; //o conteudo para onde o ponteiro aponta recebe o parametro de entrada instensidade da cor
	}
	updateFlag = TRUE;  //indica que o display deve ser atualizado
}

void changeMatrix(unsigned char* ptData){
	ptMatrix = &ledMatrix[0][0][0];
	for(unsigned char i = 0; i>0; i++, ptData++, ptMatrix++){
		(*ptMatrix) = (*ptData);
	}
	updateFlag = TRUE;
}



void displayAnimation(void){ //animação cuja a cor a piscar é definida pela variavel diplayCor, atualizada em displaySetAnimation
	if(Timer__MsGetStatus(DISPLAY_ANIMATION_MS) == TIMER_EXPIRED){ //se a animação de data etapa tiver acabada, executa determinada tarefa
		switch(animationStep){
			case ANIMATION_STEP_1:
			clearDisplay();
			Timer__MsSet(DISPLAY_ANIMATION_MS,500);
			setDisplay(diplayCor, STANDART_BRIGHT);
			break;
			
			case ANIMATION_STEP_2:
			Timer__MsSet(DISPLAY_ANIMATION_MS,500);
			clearDisplay();
			break;
			
			case ANIMATION_STEP_3:
			Timer__MsSet(DISPLAY_ANIMATION_MS,500);
			setDisplay(diplayCor, STANDART_BRIGHT);
			break;
			
			case ANIMATION_STEP_4:
			Timer__MsSet(DISPLAY_ANIMATION_MS,500);
			clearDisplay();
			break;
			
			case ANIMATION_STEP_5:
			Timer__MsSet(DISPLAY_ANIMATION_MS,500);
			setDisplay(diplayCor, STANDART_BRIGHT);
			break;
			
			case ANIMATION_STEP_6:
			Timer__MsSet(DISPLAY_ANIMATION_MS,500);
			clearDisplay();
			break;
			
			default:
				break;
		}
		animationStep++; //atualiza maquina de estado
	}
	if(animationStep>=TOTAL_ANIMATION_STEPS) //se todas as etapas tiverem sido executadas
		animationStep = NO_ANIMATION; //reinicia a variavel de modo a indicar que nenhuma outra animação ira ocorrer
}

