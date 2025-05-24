/*
 * tictactoe.h
 *
 * Created: 03/06/2024 10:49:43
 *  Author: gabriel
 */ 


#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#define JOGADOR_1 AZUL
#define JOGADOR_2 VERMELHO


#define meshBright 2


typedef enum{
	LINHA_1 = 0,
	LINHA_2,
	LINHA_3,
	TOTAL_LINHAS,
	NENHUMA_LINHA
}TIC_TAC_TOE_LINHAS;

typedef enum{
	COLUNA_1 = 0,
	COLUNA_2,
	COLUNA_3,
	TOTAL_COLUNAS,
	NENHUMA_COLUNA
}TIC_TAC_TOE_COLUNAS;

typedef enum{
	VITORIA_JOGADOR_1 = 0,
	VITORIA_JOGADOR_2,
	DRAW,
	ALL_ANIMATION_TYPES
}TIC_TAC_TOE_ANIMATION_TYPES;


typedef enum{
	ONGOING_GAME = 0,
	VITORIA,
	EMPATE,
	TOTAL_GAME_EVALUATIONS
}TIC_TAC_TOE_EVALUATION;


typedef enum{
	GAME_INITIALIZE= 0,
	WAIT_DELAY,
	WAIT_VALID_PLAY,
	GAME_UPDATE,
	GAME_EVALUATE,
	GAME_ENDING,
	GAME_ENDING_WAIT,
	TOTAL_TIC_TAC_TOE_STATUS
}TIC_TAC_TOE_STATUS;


void tictactoeHandler(void);
void tictactoeInitialize(void);
unsigned short int getTictactoePositionValue(unsigned char row, unsigned char col);



#endif /* TICTACTOE_H_ */