#include <avr/io.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>	
#include <stdio.h>
#define CMP_REGISTER (16000/256)		// 16000 kHz


// Sterowanie 7-segmentowym wyświetlaczem LED
// ------------------------------------------

//definicja portow sterujacych katodami i segmentami LED
#define SEGMENT_PORT	PORTD	
#define SEGMENT_DIR	    DDRD	
#define CATHODE_PORT	PORTB	//wykorzystywane 4 mlodsze bity
#define CATHODE_DIR		DDRB	//

#define MAX_LED_CODES 	10	//liczba możliwych znakow
#define MAX_LED_DIGITS	4	//liczba wyswietlaczy 7-segmentowych


unsigned int ms_timer;
uint8_t led_i=0;





// tablica dekodowania cyfr LED
char LedCodeTab[MAX_LED_CODES+1]= {		
 /*'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',  ' '  */
  0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F, 0x6F, 0x00  };

char LedsStr[4]={0,0,0,0};	//wyswietlana liczba 

//---------------------------------------------------------------
void LedDisp_Init(void)	//konfiguracja portˇw steruj¦cych wyťwietlaczem
 {
	SEGMENT_DIR	=0xFF;	//przypisanie kierunkow portow sterujacych
	CATHODE_DIR =CATHODE_DIR | 0x0F;
 }

//---------------------------------------------------------------
//Funkcja aktualizuje wyswietlacz LED 
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
	OCR0=CMP_REGISTER;				//aby uzyskać okres 1s
	TCCR0= (1<<WGM01 | 1<< CS02);	//tryb zerowania po zrównaniu, prescaler=256
	TIMSK=0x01 << OCIE0;			//zezwolenie na przerwania
 }
 ISR(TIMER0_COMP_vect)	// Obsluga przerwania od TIMER0 
{
		
	if(ms_timer ==5) {
			//Led_Update();
		LED_PS(3);
		//wektor();
			ms_timer=0;
			}
		ms_timer++;
	
}
void LED_PS(uint8_t ktora)
{
		uint8_t pom;
		if(ktora==5)
		SEGMENT_PORT=~0x88;
		else{
		pom=Led_Update();
if(led_i==ktora)
SEGMENT_PORT=~(LedCodeTab[pom]|0x80);
if(led_i+4==ktora)
SEGMENT_PORT=~(LedCodeTab[pom]|0x80);

}
}
void wektor(void)
{
SEGMENT_PORT=~0x88;
}

void przelicz(int czas)
{
uint8_t tab[4];

LedsStr[3]=czas%10;
LedsStr[2]=(czas%100)/10;
LedsStr[1]=(czas%1000)/100;
LedsStr[0]=czas/1000;




}



//-------------------------------
// test funkcji wyświetlacza LCD
//-------------------------------
int main(void) 
{
	
	LedDisp_Init();
	LedsStr[0]=2;
	LedsStr[1]=0;
	LedsStr[2]=1;
	LedsStr[3]=7;
	InitTimer0();
	sei();	
	int czas=0;
	char msg[10];
	while( 1) {
		_delay_ms(100);
		czas++; 
	//	przelicz(czas);
		sprintf(msg,"%4.2d",czas);
		LedsStr[0]=msg[0]-'0';
		LedsStr[1]=msg[1]-'0';
		LedsStr[2]=msg[2]-'0';
		LedsStr[3]=msg[3]-'0';
		 
	}


	return 0;
}
