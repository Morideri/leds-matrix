/*
 * gpio.h
 *
 * Created: 29/05/2024 13:50:19
 *  Author: gabri
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include "..\Header\micro.h"

#define SW_OFF 1
#define SW_ON  0



#define  bitSet(Y,X) ((Y)|=(1<<(X)))
#define  bitClear(Y, X) ((Y)&=~(1<<(X)))
#define  bitWrite(Y,X,Z)  (Z? bitSet(Y, X):bitClear(Y,X))



//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum{
	INPUT_DIGITAL_PULLUP = 0,
	OUTPUT_DIGITAL
} GPIO_PIN_TYPE;

#define PORT_DATA_TYPE  unsigned char       //This define is mandatory, it defines the register's type

typedef enum{
	PORT_B = 0,
	PORT_C,
	PORT_D,
	NUM_OF_PORTS
}GPIO_PORT;



#define MAX_NUM_OF_PORT_PINS 8
#define MAX_NUM_OF_PORTS 	 3

void gpioPinConfig(GPIO_PORT port,unsigned char pin,GPIO_PIN_TYPE type);
void gpioPinWrite(GPIO_PORT port,unsigned char pin,unsigned char value);
unsigned char gpioPinRead(GPIO_PORT port,unsigned char pin);



#endif /* GPIO_H_ */