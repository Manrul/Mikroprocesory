/przerwania co 10 ms
//---------------------------------------------------------------
// Przyklad programu obslugi i konfiguracji przerwań dla TIMER0
// Kompilatora: GCC_AVR
// Mikroprocesor: ATmega32/zegar 16 MHz
// Konfiguracja: port D steruje diodami LED
// Dzialanie: z okresem 1[s] stan portu zmienia się na przeciwny
// 03.2014 A.W.
//---------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>

#define CMP_REGISTER (160000/1024)		// 16000 kHz

#define OUTPORT		PORTD
#define DIRPORT		DDRD

unsigned int ms_timer; 					//pomocniczy licznik zliczający od 1 s

//---------------------------------------------------------------
ISR(TIMER0_COMP_vect)	// Obsluga przerwania od TIMER0 
{
	if(ms_timer >0) 
		ms_timer--;
	else {
		ms_timer=100;
		OUTPORT	=~OUTPORT;
	}
}


//---------------------------------------------------------------
void InitTimer0(void)
 {
	OCR0=CMP_REGISTER;				//aby uzyskać okres 1s
	//TCCR0= (1<<WGM01 | 1<< CS02);	//tryb zerowania po zrównaniu, prescaler=256
	TCCR0= (1<<WGM01 | 1<<CS02 | 1<<CS00); // prescaler=1024
	TIMSK=0x01 << OCIE0;			//zezwolenie na przerwania
 }


//---------------------------------------------------------
int main(void)
 {
	
	DIRPORT=0xFF;		// konfiguracja portu na wyjście
	OUTPORT=0x55;		// stan początkowy portu
	
	InitTimer0();
	ms_timer=0;
	
	sei();		// wlaczenie przerwan

	while(1) {
	
		
	}
	
	return 0;
}
