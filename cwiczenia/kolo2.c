#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Lcd_Fun.h"
//zmienna do przerwań((Fcpu/preskaler)*razy odstęp między przerwaniami w sek)
//#define CMP_REGISTER (16000/256) //dla przerwań co 1ms,(16000000*10^-3)/PRESKALER,(bo 1ms=10^-3)
#define CMP_REGISTER  125//(fcpu*500us/64) da przerwanie co 0.5ms
#define LI_max 20
#define LI_min 1
#define O_max 40
#define O_min 2



volatile uint8_t flaga_u=0;
uint8_t liczba_i=1;
uint8_t liczba_o=1;
volatile  uint8_t ms_timer; // Możliwa zmiana na volatile, gdy będzie potrzeba


//deklaracje funkcji
inline void InitTimer0(void); //inicjalizajca timera0
int lcd_put(char znak, FILE *s); //znak, wskaznik do strumienia
void time_update(void); //funkcja wywoływana w przerwaniu co sekunda,aktualizująca czas
uint8_t KbScan(void); //funkcja skanująca klawiature 4x1, zwraca numer klawisza
uint8_t Licznik(void); //funkcja filtrująca odczytane stany klawisza
void generuj();
//definicja strumienia
static FILE mystdout= FDEV_SETUP_STREAM(lcd_put, NULL,_FDEV_SETUP_WRITE);
int main(void)
{
	_delay_ms(1000);
	lcd_init();
	InitTimer0();
	DDRB=0x01;
	stdout = &mystdout;
	
	uint8_t flaga_l=0;
	uint8_t klaw;
	sei();
	while(1)
	{
		
		if(flaga_u==0)
		printf("\rUstawienia ");
		
		if(flaga_l==0){
			
			printf("\nLiczba im:%2d",liczba_i);
		}
		else{
			
			printf("\nOkres:    %2d",liczba_o);
		}




		klaw=Licznik();
		if(klaw==1)
		{
			flaga_l=(flaga_l+1)%2;
		}
		if(flaga_l==0)
		{
			if(klaw==2&&liczba_i<LI_max)
			liczba_i++;
			if(klaw==3&&liczba_i>LI_min)
			liczba_i--;
		}
		if(flaga_l==1)
		{
			if(klaw==2&&liczba_o<O_max)
			liczba_o++;
			if(klaw==3&&liczba_o>O_min)
			liczba_o--;
		}
		if(klaw==4){
			flaga_u=1;
			printf("\rGeneracja      ");
			generuj();

		}
	}
	return 0;
}
//obsługa przerwań,w wersji z wywaływaniem time_update co 1000 przerwań(1000*1ms=1s)
ISR(TIMER0_COMP_vect)
{
	ms_timer++;
}
//pozostałe funkcje

inline void InitTimer0(void)
{
	OCR0=CMP_REGISTER;
	TCCR0= (1<<WGM01 | 1<< CS00 | 1<< CS01); //tryb zerowania po zrównaniu, prescaler=64
	TIMSK=0x01 << OCIE0; //zezwolenie na przerwania
}
int lcd_put(char znak, FILE *s)
{
	if (znak == '\r')
	lcd_gotoxy(0, 0);
	else if (znak == '\n')
	lcd_gotoxy(0, 1);
	else
	lcd_putchar(znak);
	return 0;
}

uint8_t KbScan(void)
{
	DDRD= 0b00000000;
	PORTD= 0b11111111;
	if( (PIND & 0x01) ==0 ) return 1;
	if( (PIND & 0x02) ==0 ) return 2;
	if( (PIND & 0x04) ==0 ) return 3;
	if( (PIND & 0x08) ==0 ) return 4;
	return 0;
}



uint8_t Licznik(void)
{	static uint8_t wynik=0;
	uint8_t pom=0;
	pom=KbScan();
	_delay_ms(4);
	if(KbScan()==pom&&wynik!=KbScan())
	{
		wynik=pom;
		return pom;
	}
	return 0;
}
void generuj(void)
{
	uint8_t i= liczba_i;
	while(i)
	{
		PORTB=0x01;
		while(ms_timer<=liczba_o);
		PORTB=0x00;
		ms_timer=0;
		while(ms_timer<=liczba_o);
		ms_timer=0;
		i--;
		flaga_u=0;
	}
	

}
