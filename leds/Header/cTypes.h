/*
 * cTypes.h
 *
 * Created: 29/05/2024 13:48:59
 *  Author: gabri
 */ 


#ifndef CTYPES_H_
#define CTYPES_H_

#define ENABLED		1
#define DISABLED 	0

#define TRUE		1
#define FALSE		0

#define HIGH		1
#define LOW			0

#define ON			1
#define OFF			0

#define BIT_TEST(mem,bit)   ((mem)&(1UL<<(bit))) //This macro is used to perform test on bit of the data
#define BIT_SET(mem,bit)    ((mem)|=(1UL<<(bit))) //This macro is used to set the bit of the data
#define BIT_CLR(mem,bit)    ((mem)&=~(1UL<<(bit))) //This macro is used to clear the bit of the data
#define BIT_TOGGLE(mem,bit) ((mem)^=(1UL<<(bit))) //This macro is used to toggle the bit of the data


#endif /* CTYPES_H_ */