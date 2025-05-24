/*
 * sound.h
 *
 * Created: 17/06/2024 06:39:38
 *  Author: gabriel
 */ 


#ifndef SOUND_H_
#define SOUND_H_


#define NUM_NOTES 26
//#define NOTES_FREQUENCY {0, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880}
#define TOP_VALUES {	 0, 141, 133, 126, 118, 112, 105, 99, 94, 88, 83, 79, 74, 70, 66, 252, 238, 224, 212, 200, 189, 178, 168, 158, 149, 141}
#define PRESCALERS {	 0, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b100, 0b011, 0b011, 0b011, 0b011, 0b011, 0b011, 0b011, 0b011, 0b011, 0b011, 0b011}

typedef enum {
	NO_NOTE = 0, 
	C3,      // Dó 3
	Cs3_Db3,  // Dó# 3 / Réb 3
	D3,       // Ré 3
	Ds3_Eb3,  // Ré# 3 / Mib 3
	E3,       // Mi 3
	F3,       // Fá 3
	Fs3_Gb3,  // Fá# 3 / Solb 3
	G3,       // Sol 3
	Gs3_Ab3,  // Sol# 3 / Láb 3
	A3,       // Lá 3
	As3_Bb3,  // Lá# 3 / Sib 3
	B3,       // Si 3
	C4,       // Dó 4
	Cs4_Db4,  // Dó# 4 / Réb 4
	D4,       // Ré 4
	Ds4_Eb4,  // Ré# 4 / Mib 4
	E4,       // Mi 4
	F4,       // Fá 4
	Fs4_Gb4,  // Fá# 4 / Solb 4
	G4,       // Sol 4
	Gs4_Ab4,  // Sol# 4 / Láb 4
	A4,       // Lá 4
	As4_Bb4,  // Lá# 4 / Sib 4
	B4,       // Si 4
	C5,        // Dó 5
	TOTAL_NOTES
}MUSICAL_NOTES;

struct SOUND_DATA{
	MUSICAL_NOTES note;
	unsigned char topValue;
	unsigned char prescaler;
};

typedef enum{
	SOUND_IDLE = 0,
	SOUND_PLAYING,
	ALL_SOUND_STATUS
}SOUND_STATUS;


typedef enum{
	SOUND_TIC_TAC_TOE_INPUT_1 = 0,
	SOUND_TIC_TAC_TOE_INPUT_2,
	SOUND_TIC_TAC_TOE_WIN_1,
	SOUND_TIC_TAC_TOE_WIN_2,
	SOUND_TIC_TAC_TOE_DRAW,
	TOTAL_SOUND_TIC_TAC_TOE
}SOUND_TIC_TAC_TOE;
/*
#define GENERIC_SOUND_INITIALIZE() ({\
\	
})

#define TIC_TAC_TOE_WIN_1_SEQUENCE_MASK [A3, B3, C4];

*/
struct{
	unsigned char totalSteps;
}SOUND_DATA_TIC_TAC_TOE;



typedef enum{
	SOUND_GENIUS_1,
	SOUND_GENIUS_2,
	SOUND_GENIUS_3,
	SOUND_GENIUS_4,
	SOUND_GENIUS_HARD_1_2,
	SOUND_GENIUS_HARD_1_3,
	SOUND_GENIUS_HARD_2_4,
	SOUND_GENIUS_HARD_3_4,
	SOUND_GENIUS_LOST,
	SOUND_GENIUS_WON,
	TOTAL_GENIUS_SOUND
}SOUND_GENIUS;

typedef enum{
	SOUND_SNAKE_MOVE = 0,
	SOUND_SNAKE_EAT_APPLE,
	SOUND_SNAKE_LOST,
	TOTAL_SNAKE_SOUND
}SOUND_SNAKE;


/*
#include <stdio.h>
#include <math.h>

#define F_CPU 16000000UL

const unsigned int prescalers[] = {1, 8, 32, 64, 256, 1024};
const char *prescaler_strings[] = {"1", "8", "32", "64", "256", "1024"};
const double notes[] = {220.00, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00};

typedef struct {
	unsigned int top;
	const char *prescaler;
} Timer2Config;

Timer2Config calculate_timer2_config(double frequency) {
	Timer2Config best_config = {0xFFFF, "None"}; // Initialize with invalid values
	double best_error = INFINITY;

	for (unsigned int i = 0; i < sizeof(prescalers) / sizeof(prescalers[0]); i++) {
		unsigned int prescaler = prescalers[i];
		double top_value = (double)F_CPU / (2.0 * prescaler * frequency) - 1.0;
		if (top_value >= 0 && top_value <= 255) {
			double actual_frequency = (double)F_CPU / (2.0 * prescaler * (round(top_value) + 1));
			double error = fabs(actual_frequency - frequency);
			if (error < best_error) {
				best_error = error;
				best_config.top = (unsigned int)round(top_value);
				best_config.prescaler = prescaler_strings[i];
			}
		}
	}

	return best_config;
}

int main() {
	printf("Note\tFrequency (Hz)\tTOP Value\tPrescaler\n");
	printf("-------------------------------------------------\n");
	for (unsigned int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
		Timer2Config config = calculate_timer2_config(notes[i]);
		printf("%c%c%d\t%7.2f\t\t%3u\t\t%s\n",
		(i % 12 == 9) ? 'A' : (i % 12 == 10) ? 'B' : (i % 12 == 11) ? 'C' :
		(i % 12 == 0) ? 'C' : (i % 12 == 1) ? 'D' : (i % 12 == 2) ? 'D' :
		(i % 12 == 3) ? 'E' : (i % 12 == 4) ? 'F' : (i % 12 == 5) ? 'F' :
		(i % 12 == 6) ? 'G' : (i % 12 == 7) ? 'G' : 'A',
		(i % 12 == 1 || i % 12 == 3 || i % 12 == 6 || i % 12 == 8 || i % 12 == 10) ? '#' : ' ',
		(i / 12) + 3,
		notes[i],
		config.top,
		config.prescaler);
	}

	return 0;
}

*/
typedef enum {
	KEY_PRESS_JOGADOR_1 = 0,
	KEY_PRESS_JOGADOR_2,
	JOGADOR_1_GANHOU,
	JOGADOR_2_GANHOU,
	JOGO_EMPATOU,
	NO_SOUND,
	NUM_OF_SOUNDS
}TICTACTOE_SOUNDS_TYPE;


	
#define BUZZER_DEFAULT_ON_DUTY			50	//40%
#define BUZZER_OFF_DUTY					 0		//0%



//Protótipos

void Hal__SetBuzzer(unsigned char state);
void halSetBuzzerFreq(unsigned short int frequency);
void soundHandler(void);
void soundInitialize(void);
void setSound(TICTACTOE_SOUNDS_TYPE soundSet);
unsigned char soundGetSoundStatus(void);

//

void halBuzzerInitialize(void);
void soundSetNote(MUSICAL_NOTES note);
void soundClrNote(void);
void halSetBuzzerNote(struct SOUND_DATA* ptSoundData);
//

void halSoundInitialize(void);
void halSetNote(struct SOUND_DATA* ptSoundData);


#endif /* Sounds_H_ */


/*
//================================================================================ //
// MUSICAS COM O ATMEGA //
// Leitura de arquivos RTTTL - Ringtones //
//================================================================================ //
#define F_CPU 16000000UL //frequência de operação de 16MHz
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
//Definições de macros
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) //ativa bit
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) //limpa bit
#define som PB1 //pino OC1A para saída do sinal
#define d_inic 4 //valor inicial de duração da nota musical
#define o_inic 5 //valor inicial da oitava
#define b 100 //o nr de batidas indica a velocidade da musica (alterar para mudar a velocidade), maior = mais rápido
#define t_min (7500/b)*10//tempo mínimo para formar o tempo base das notas musicais (1/32)
						 //Max. de 255 caract. para MUSICA, caso contrário o índice de varredura deve ser
						 //alterado para unsigned int (não usar espaço entre os caracteres)
//Marcha Imperial - Star Wars
const char MUSICA[] PROGMEM={"e,e,e,8c,16p,16g,e,8c,16p,16g,e,p,b,b,b,8c6,16p,16g,d#,8c,16p,16g,e,8p"};
//------------------------------------------------------------------------------------
int main()
{
	unsigned int k;
	unsigned char d, o, j, n, i=0;
	DDRB |= (1<<som); //habilita a saída de som
	TCCR1A = 1<<COM1A0;//TC1 modo CTC comparação com OCR1A, prescaler=1
	TCCR1B = (1<<WGM12)|(1<<CS10);
	//------------------------------------------------------------------------------
	//LEITURA E EXECUÇÃO DO ARQUIVO RTTTL
	//------------------------------------------------------------------------------
	do
	{
		o = o_inic; //carrega o valor default para a oitava
		if((pgm_read_byte(&MUSICA[i])=='3')&&(pgm_read_byte(&MUSICA[i+1])=='2')){d=32; i+=2;}
		else if((pgm_read_byte(&MUSICA[i])=='1')&&(pgm_read_byte(&MUSICA[i+1])=='6')){d=16;
		i+=2;}
		else if(pgm_read_byte(&MUSICA[i])=='8') {d=8; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='4') {d=4; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='2') {d=2; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='1') {d=1; i++;}
		else d=d_inic; //carrega o valor dafault para a duração
		if(pgm_read_byte(&MUSICA[i+1])=='#')
		{
			switch(pgm_read_byte(&MUSICA[i]))//carrega a oitava # default (4a)
			{
				case 'a': OCR1A = 17159; break;//A# - Lá#
				case 'c': OCR1A = 14429; break;//C# - Dó#
				case 'd': OCR1A = 12852; break;//D# - Ré#
				case 'f': OCR1A = 10807; break;//F# - Fá#
				case 'g': OCR1A = 9627; break;//G# - Sól#
			}
			i+=2;
		}
		250
		else
		{
			switch(pgm_read_byte(&MUSICA[i]))//carrega a oitava default (4a)
			{
				case 'a': OCR1A = 18181; break;//A - Lá
				case 'b': OCR1A = 16197; break;//B - Si
				case 'c': OCR1A = 15287; break;//C - Dó
				case 'd': OCR1A = 13618; break;//D - Ré
				case 'e': OCR1A = 12131; break;//E - Mi
				case 'f': OCR1A = 11449; break;//F - Fá
				case 'g': OCR1A = 10199; break;//G - Sol
				case 'p': clr_bit(TCCR1A,COM1A0); break;//p = pausa
			}
			i++;
		}
		n = 32/d; //tempo de duração de cada nota musical
		if(pgm_read_byte(&MUSICA[i])=='.'){n=n+(n/2); i++;}//duração 50% >
		if(pgm_read_byte(&MUSICA[i])=='4') { o=4; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='5'){ o=5; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='6'){ o=6; i++;}
		else if(pgm_read_byte(&MUSICA[i])=='7'){ o=7; i++;}
		if(pgm_read_byte(&MUSICA[i])=='.'){n=n+(n/2); i++;}// duração 50% >
		switch(o)//troca a oitava se não for a default (o = 4)
		{
			case 5: OCR1A = OCR1A>>1; break; //divide por 2
			case 6: OCR1A = OCR1A>>2; break; //divide por 4
			case 7: OCR1A = OCR1A>>4; break; //divide por 8
		}
		//------------------------------------------------------------------------
		for(j=0;j<n;j++)//nr de repetições para a nota 1/32
		{
			for(k=t_min;k!=0;k--) _delay_us(100);
		}
		//------------------------------------------------------------------------
		set_bit(TCCR1A,COM1A0); //habilita o som
	}while(pgm_read_byte(&MUSICA[i++])==',');//leitura até o final da música
	TCCR1A=0; //desabilita o som e o TC1
	TCCR1B=0;
	//-----------------------------------------------------------------------------
	while(1){} //laço infinito
}
//==================================================================================
*/