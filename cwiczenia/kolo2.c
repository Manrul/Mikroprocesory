#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Lcd_Fun.h"

//zmienna do przerwań((Fcpu/preskaler)*razy odstęp między przerwaniami w sek)
#define CMP_REGISTER (16000/256)			//dla przerwań co 1ms,(16000000*10^-3)/PRESKALER,(bo 1ms=10^-3)
//#define CMP_REGISTER (160000/1024)		//dla przerwań co 10 ms,16000000*(10*10^-3),(bo 10ms=10*10^-3)

//do klawiatury 4x4
#define KB_PORT PORTD
#define KB_DIR DDRD
#define KB_PIN PIND
//zakres wartości licznika
#define MAX 20
#define MIN 0


//zmienne globalne
unsigned int ms_timer;					// Możliwa zmiana na volatile, gdy będzie potrzeba
uint8_t licznik=0;
//do zegarka
uint8_t sek=0;
uint8_t min=0;
//deklaracje funkcji
inline void InitTimer0(void);			//inicjalizajca timera0
int lcd_put(char znak, FILE *s);		//znak, wskaznik do strumienia
uint8_t KbScan(void);					//funkcja skanująca klawiature 4x1, zwraca numer klawisza
uint8_t KbScan2(void);					//funkcja skanująca klawiature 4x4, zwraca numer klawisza
void Licznik(void);						//funkcja filtrująca odczytane stany klawisza
void Licznik2(void);					//funkcja filtrująca odczytane stany klawisza,inkrementacja co 100ms,(nie testowane)
void lcd_cursor_on(void);				//sterowanie kursorem,do sprawdzenia,zbedne, przekleić funkcje do lcd_fuc.c,tu skasować
void lcd_cursor_off(void);				//sterowanie kursorem,do sprawdzenia,zbedne, przekleić funkcje do lcd_fuc.c,tu skasować
void time_update(void);					//funkcja wywoływana  w przerwaniu co sekunda,aktualizująca czas
//definicja strumienia
static FILE mystdout= FDEV_SETUP_STREAM(lcd_put, NULL,_FDEV_SETUP_WRITE);

int main(void)
{
	
	
	_delay_ms(1000);
	lcd_init(); 
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
//obsługa przerwań,w wersji z wywaływaniem time_update co 1000 przerwań(1000*1ms=1s)
ISR(TIMER0_COMP_vect)
{
	
	if(ms_timer == 1000) {
		ms_timer=0;
		time_update();
	}
	ms_timer++;
	
	
}
//pozostałe funkcje
void Licznik(void)
{
	static char wynik=0;
	char pom;
	
	pom=KbScan();
	_delay_ms(4);
	
	if(KbScan()==pom&&wynik!=KbScan())
	{
		if(pom==1&&licznik>MIN)
			licznik--;
		else if(pom==2&&licznik<MAX)
			licznik++;
		wynik=pom;
	}
}

uint8_t KbScan(void)
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
	TCCR0= (1<<WGM01 | 1<< CS02);				//tryb zerowania po zrównaniu, prescaler=256
	//TCCR0= (1<<WGM01 | 1<<CS02 | 1<<CS00);	 // prescaler=1024(JAK PRZERWANIA MIAŁY BYĆ CO 10MS)
	TIMSK=0x01 << OCIE0;						//zezwolenie na przerwania
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

uint8_t KbScan2(void)
{
	unsigned char skankod=0;
	KB_DIR = 0xF0; // starsza czesc na wyjscie
	KB_PORT = 0x0F; // tam gdzie sa wejscia wysylamy , i podwieszamy rezystor
	_delay_us(2);

	skankod = KB_PIN; // starsza odczytana czesc wrzucamy do skankodu (and 0x0F - wymuszenie by na mlodszej czesci byly 0)
	KB_DIR = 0x0F;
	KB_PORT = 0xF0;
	_delay_us(2);

	skankod = skankod | KB_PIN;
	if(skankod == 0b11101110) return 1;
	if(skankod == 0b11011110) return 2;
	if(skankod == 0b10111110) return 3;
	if(skankod == 0b01111110) return 4;
	if(skankod == 0b11101101) return 5;
	if(skankod == 0b11011101) return 6;
	if(skankod == 0b10111101) return 7;
	if(skankod == 0b01111101) return 8;
	if(skankod == 0b11101011) return 9;
	if(skankod == 0b11011011) return 10;
	if(skankod == 0b10111011) return 11;
	if(skankod == 0b01111011) return 12;
	if(skankod == 0b11100111) return 13;
	if(skankod == 0b11010111) return 14;
	if(skankod == 0b10110111) return 15;
	if(skankod == 0b01110111) return 16;
	
	return 255;
}

void Licznik2(void)
{
	static char wynik=0;
	char pom;
	pom=KbScan2();
	_delay_ms(1);
	
	if(KbScan2()!=pom)
		return;
	if(wynik!=KbScan2())
	{
		if(pom==1)
			licznik--;
		else if(pom==2)
			licznik++;
		PORTB=licznik;
		wynik=pom;
	}
	//else if((pom==1||pom==2)&&KbScan2()==pom)
	//else if(KbScan2()==pom)
	//else if(pom==1||pom==2)
	else   //chyba najlepsza możliwość
	{
		_delay_ms(100);
		pom=KbScan2();//? z tym czy bez?
		
		if(pom==1)
			licznik--;
		else if(pom==2)
			licznik++;
		PORTB=licznik;
		wynik=pom;
	}
}

//Display ON/ OFF Control 0(rs) 0(rw) 0 0 0 0 1 D C B Set display(D), cursor(C), and blinking of cursor(B) on/off control bit.
void lcd_cursor_off(void)
{
	lcd_wr_command(0x0C);
}

void lcd_cursor_on(void)
{
	lcd_wr_command(0x0E);
}

void time_update(void)
{
	sek++;			//lub++sek
	if(sek==60)		//lub sek==59
		{
			min++;
			sek=0;
		}
}
