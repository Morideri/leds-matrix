/*
 * defType.h
 *
 * Created: 18/10/2024 09:49:51
 *  Author: gabri
 */ 


#ifndef DEFTYPE_H_
#define DEFTYPE_H_

typedef signed char s8;
typedef unsigned char u8;
typedef signed int s16;
typedef unsigned int u16;
typedef signed long int s32;
typedef unsigned long int u32;
typedef signed long long int s64;
typedef unsigned long long int u64;

#define mmioByte(mem_addr) (*(volatile u8 *)(mem_addr))
#define mmioWord(mem_addr) (*(volatile u16 *)(mem_addr))
#define mmioDword(mem_addr) (*(volatile u32 *)(mem_addr))


union DEF_BYTE{
	u8 byte;
	struct
	{
		unsigned char bit0 :1;
		unsigned char bit1 :1;
		unsigned char bit2 :1;
		unsigned char bit3 :1;
		unsigned char bit4 :1;
		unsigned char bit5 :1;
		unsigned char bit6 :1;
		unsigned char bit7 :1;
	} bit;
};

union DEF_WORD{
	u16 halfWord;
	struct{
		union DEF_BYTE LowByte;
		union DEF_BYTE HighByte;
	}Byte;
};

union DEF_D_WORD{
	u32 word;
	struct{
		union DEF_WORD lowHalfWord;
		union DEF_WORD highHalfWord;
	}hWord;
};

union DEF_Q_WORD{
	u64 dWord;
	struct{
		volatile union DEF_D_WORD lowWord;
		union DEF_D_WORD highWord;
	}word;
};



#endif /* DEFTYPE_H_ */