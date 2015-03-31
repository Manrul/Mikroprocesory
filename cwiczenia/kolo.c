#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define CMP_REGISTER (16000/256)		// 16000 kHz
#define SEGMENT_PORT	PORTD
#define SEGMENT_DIR	DDRD
#define CATHODE_PORT	PORTB
#define CATHODE_DIR	DDRB
#define MAX_LED_CODES 	10
#define MAX_LED_DIGITS	4


unsigned int ms_timer;
uint8_t led_i=0;
uint8_t licznik=5;
uint8_t i=1;
char LedCodeTab[MAX_LED_CODES+1]= {
	/*'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',  ' '  */
0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F, 0x6F, 0x00  };

char LedsStr[4]={0,0,0,5};	//wyswietlana liczba

void LedDisp_Init(void)
{
	SEGMENT_DIR	=0xFF;
	CATHODE_DIR =CATHODE_DIR | 0x0F;
}

uint8_t Led_Update(void)
{
	//	static uint8_t led_i=0;	//aktualny indeks wyswietlanej pozycji
	uint8_t tmp;
	//aktualizacja portu C/A wyswietlacza 7-segmentowego
	CATHODE_PORT =(CATHODE_PORT & 0xF0) | ~(1<<led_i);
	
	tmp=LedsStr[led_i++];
	if(tmp>MAX_LED_CODES)
	tmp=MAX_LED_CODES;

	SEGMENT_PORT= ~LedCodeTab[tmp];
	
	if(led_i >=MAX_LED_DIGITS) led_i=0;
	return tmp;
}

void InitTimer0(void)
{
	OCR0=CMP_REGISTER;
	TCCR0= (1<<WGM01 | 1<< CS02);
	TIMSK=0x01 << OCIE0;
}

ISR(TIMER0_COMP_vect)
{
	if(ms_timer==5)
	{
		Led_Update();
		ms_timer=0;
	}
	ms_timer++;
}

uint8_t klawisz()
{
	DDRA=	0b00000000;
	PORTA=	0b11111111;
	if( (PINA & 0x01) ==0 ) return 1;
	if( (PINA & 0x02) ==0 ) return 2;
	if( (PINA & 0x04) ==0 ) mruganie();
	
	return 0;
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
	LedsStr[3]=licznik%10;
	LedsStr[2]=(licznik%100)/10;
	LedsStr[1]=(licznik%1000)/100;
	LedsStr[0]=licznik/1000;
}

void mruganie(void)
{
	uint8_t i;

	for(i=0;i<licznik;i++)
	{
		PORTC|=0b00000001;
		_delay_ms(500);
		PORTC&=0b11111110;
		_delay_ms(500);
	}
}

int plusiles(uint8_t pom)
{
	uint8_t licz;

	for(licz=0;licz<5;licz++)
	{
		_delay_ms(100);
		if(pom!=klawisz())
		{
			i=1;
			licz=5;
			    return 0;
		}
	}
	if(i==0)
	{

		if( (PINA & 0x01) ==0&&licznik>5 ) licznik=licznik-5;
		if( (PINA & 0x02) ==0&&licznik<15) licznik=licznik+5;
		if(licznik<1) licznik=1;
		if (licznik>20) licznik=20;
		
		LedsStr[3]=licznik%10;
		LedsStr[2]=(licznik%100)/10;
		LedsStr[1]=(licznik%1000)/100;
		LedsStr[0]=licznik/1000;
	}
	return 0;
}

int main(void)
{
	DDRC|=0b00000001;
	uint8_t pom;
	
	LedDisp_Init();
	InitTimer0();
	sei();

	while(1) {
		pom=klawisz();
			if(i)
					Licznik();
		_delay_ms(100);
			if(pom==klawisz())
				{
					i=0;
					plusiles(pom);
				}
			}

		return 0;
}
