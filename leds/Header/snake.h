/*
 * snake.h
 *
 * Created: 13/09/2024 12:13:05
 *  Author: gabri
 */ 


#ifndef SNAKE_H_
#define SNAKE_H_
#define snakeLarguraTotal 8
#define snakeAlturaTotal 8
#define snakeTotalFields 64 //snakeLarguraTotal * snakeAlturaTotal
#define snakeInitialSpeedMs 255
typedef enum{
	SNAKE_EMPTY = 0,
	SNAKE_APPLE,
	SNAKE_BODY,
	SNAKE_ALL_FIELD_TYPES
}SNAKE_FIELD_TYPE;


typedef enum{
	SNAKE_NOT_MOVING = 0,
	SNAKE_RIGHT_MOVE,
	SNAKE_LEFT_MOVE,
	SNAKE_UP_MOVE,
	SNAKE_DOWN_MOVE,
	SNAKE_INVALID_MOVE,
	SNAKE_ALL_MOVES	
}SNAKE_MOVE;


typedef enum{
	SNAKE_GAME_ONGOING,
	SNAKE_PLAYER_LOST,
	ALL_SNAKE_CONCLUSIONS
}SNAKE_CONCLUSION;

struct SNAKE_FIELD_DATA{
	SNAKE_FIELD_TYPE field;
	struct SNAKE_FIELD_DATA* prev;
	unsigned char xcoord;
	unsigned char ycoord;
};

typedef enum{
	SNAKE_INITIALIZE_STEP = 0,
	SNAKE_DELAY_STEP,
	SNAKE_INPUT_STEP,
	SNAKE_MOVEMENT_STEP,
	SNAKE_EVALUATION_STEP,
	SNAKE_ALL_STEPS
}SNAKE_STEP;


void snakeInitialize(void);
void snakeHandler(void);

#endif /* SNAKE_H_ */

