		#define	F_CPU	8000000UL 
		#include <avr/io.h>				
		#include <inttypes.h>			
		#include <avr/interrupt.h>		
		#include <avr/pgmspace.h>		
		#include <avr/sfr_defs.h>	
			


volatile	uint16_t _100cntr=0; //zmiena typu volatile aby mogła być zmieniana wewnątrz przerwań
//funkcje zmieniająca stan portu b(zapala/gasi diody podłączone do niego)
void LedBlink(void)
{

		static uint8_t blink = 0; //zmienna typu static aby zapamietac jej poprzedni stan po kolejnym wywołaniu funkcji
		
		if(blink == 0)
		{
			PORTB = 0x00;
			blink = 1;
		}
		else
			{
				PORTB = 0xFF;
				blink = 0;
			}


}

//Funkcja obsługi przerwania
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 58; //zmienna licznika,tak dobrana aby przerwania występołwały 
			// co 200us
	_100cntr++;//zmienna inkrmentująca się wraz z każdym przerwaniem
}


int main(void)
{

	DDRB = 0xFF; //---PORTB na wyjscie-----//
		//ustawienia timera
	TCCR0 = (1<<CS01); //--- ustawiamy prescaler na 8
	TIMSK = TIMSK | (1<<TOIE0); // | = OR ---- nie mozemy ruszac bitow
				// od 7 do 2, zostawiamy OCIE0 (domyslnie 0),
				// dajemy 1 na TOIE0
	sei(); //odblokowanie przerwan
	
	
	while(1)
	{//uruchamienie funkcji co 500 przerwan
		if(_100cntr >= 500) 
		{
			_100cntr = 0;	

			LedBlink(); 
		}
	}

}
