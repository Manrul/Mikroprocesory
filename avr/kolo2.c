#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Lcd_Fun.h"

#define CMP_REGISTER (16000/256)		// 16000 kHz




//zmienne globalne
unsigned int ms_timer;
uint8_t licznik=0;

//deklaracje funkcji
inline void InitTimer0(void);
uint8_t klawisz(void);
void Licznik(void);
int lcd_put(char znak, FILE *s);//znak, wskaznik do strumienia


static FILE mystdout= FDEV_SETUP_STREAM(lcd_put, NULL,_FDEV_SETUP_WRITE);

int main(void)
{
	
	
	_delay_ms(1000);
	lcd_init(); //incicjalizacja wyswietlacza
	InitTimer0();
	stdout = &mystdout;
	
	sei();

		while(1)
	{
		
		printf("\rMichal ");
		_delay_ms(1000);
		printf("\nSiecinski ");
		_delay_ms(1000);
		_delay_ms(500); 
	}

		return 0;
}

ISR(TIMER0_COMP_vect)
{
	
	if(ms_timer ==5) {
		
		
		ms_timer=0;
	}
	ms_timer++;
	
	
}

void Licznik(void)
{
	static char wynik=0;
	char pom;
	
	
	pom=klawisz();
	_delay_ms(4);
	if(klawisz()==pom&&wynik!=klawisz())
	{
		if(pom==1&&licznik>1)
		licznik--;
		else if(pom==2&&licznik<20)
		licznik++;
		
		wynik=pom;
	}
}

uint8_t klawisz(void)
{
	DDRA=	0b00000000;
	PORTA=	0b11111111;
	if( (PINA & 0x01) ==0 ) return 1;
	if( (PINA & 0x02) ==0 ) return 2;
	
	return 0;
}

inline void InitTimer0(void)
{
	OCR0=CMP_REGISTER;
	TCCR0= (1<<WGM01 | 1<< CS02);
	TIMSK=0x01 << OCIE0;
}

int lcd_put(char znak, FILE *s)
{
	if (znak == '\r')
	{
		lcd_gotoxy(0, 0);
	} else if (znak == '\n')
	{
		lcd_gotoxy(0, 1);
	} else
	{
		lcd_putchar(znak);
	}
	return 0;
}
