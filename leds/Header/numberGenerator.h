/*
 * numberGenerator.h
 *
 * Created: 27/08/2024 17:22:54
 *  Author: gabri
 */ 


#ifndef NUMBERGENERATOR_H_
#define NUMBERGENERATOR_H_

#define maxGeniusNumber 4

typedef enum{
	RNG_GENIUS = 0,
	RNG_GENIUS_HARD,
	RNG_SNAKE,
	TOTAL_RNG
}RNG_ID;


#define maxRngNumbers {4, 8, 63}
#define minRngNumbers {1, 1, 1}

void rngInit(void);
void getNumber(void);
void rngHandler(void);
unsigned char getRandomNumber(RNG_ID ID);


#endif /* NUMBERGENERATOR_H_ */