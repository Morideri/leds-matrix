/*
 * rng.c
 *
 * Created: 27/08/2024 17:22:10
 *  Author: gabri
 */ 
#include "..\Header\numberGenerator.h"
#include "..\Header\micro.h"

unsigned char geniusNumberGenerated;

typedef struct{
	unsigned char maxNumber;
	unsigned char currentNumber;	
}RNG_DATA;

RNG_DATA rngDataArray[TOTAL_RNG];

unsigned char rngMaxValueArray[TOTAL_RNG] = maxRngNumbers;
unsigned char rngMinValueArray[TOTAL_RNG] = minRngNumbers;

void rngInit(){
	for(unsigned char Id = 0; Id < TOTAL_RNG; Id++){
		rngDataArray[Id].currentNumber = 0;
	}
}

void rngHandler(){
	for(unsigned char Id = 0; Id < TOTAL_RNG; Id++){
		rngDataArray[Id].currentNumber++;
		if(rngDataArray[Id].currentNumber > rngMaxValueArray[Id]){
			rngDataArray[Id].currentNumber = rngMinValueArray[Id];
		}
	}
}

unsigned char getRandomNumber(RNG_ID ID){
	return rngDataArray[ID].currentNumber;
}
