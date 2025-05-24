/*
 * displayLed.h
 *
 * Created: 30/05/2024 08:37:40
 *  Author: gabriel
 */ 


#ifndef WS2812B_H_
#define WS2812B_H_


typedef enum{
	AZUL = 0,
	VERMELHO,
	VERDE,
	QUANTIDADE_CORES
}CORES_PRIMARIAS;

typedef enum{
	NORMAL = 0,
	ZIGZAG,	
}LED_ORGANIZATION_TYPE;

typedef enum{
	MESH_TIC_TAC_TOE = 0,
	MESH_GENIUS,
	ALL_MESH_TYPES
}LED_MESH_TYPE;

#define QUANTIDADE_LINHAS 8
#define QUANTIDADE_COLUNAS 8
#define TOTAL_PIXELS (QUANTIDADE_LINHAS*QUANTIDADE_COLUNAS)
#define TOTAL_LEDS (QUANTIDADE_LINHAS*QUANTIDADE_COLUNAS*QUANTIDADE_CORES)
#define STANDART_BRIGHT 31

#define PIN_DATA_LED PD1 //LED1 é o substituto de PD1 na programação
#define PORT_DATA_LED PORT_D //port do PIN do LED
#define PIN_TYPE_LED OUTPUT_DIGITAL  //direção do PIN do LED
#define matrixLastAddress &ledMatrix[QUANTIDADE_LINHAS-1][QUANTIDADE_COLUNAS-1][QUANTIDADE_CORES-1]
#define matrixFirstAddress &ledMatrix[0][0][0]

#define NOP asm volatile("nop\n\t") //assembly NOP, delay 62.5ns


extern unsigned char ledMatrix[QUANTIDADE_LINHAS][QUANTIDADE_COLUNAS][QUANTIDADE_CORES];



void ledInitialize(void);
void halLedInitialize(void);
void sendDataToDisplay(unsigned char *ptData);
void displayBackgroundHandler(void);
void changeIndividual(unsigned char linha, unsigned char coluna, CORES_PRIMARIAS cor, unsigned char intensidade_da_cor);
void clearDisplay(void);
void setDisplay(CORES_PRIMARIAS cor, unsigned char brilho);
void changeHouse(unsigned char linha, unsigned char coluna, CORES_PRIMARIAS cor, unsigned char intensidade_da_cor);
void clearHouse(unsigned char linha, unsigned char coluna);
void changeMatrix(unsigned char* ptData);

void generateMash(LED_MESH_TYPE meshType, unsigned char brilho);


void displayHandler(void);
unsigned char displayGetAnimationStatus(void);
void displaySetAnimation(unsigned char color);

#endif /* DISPLAYLED_H_ */