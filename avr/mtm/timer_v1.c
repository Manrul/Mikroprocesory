		#define	F_CPU	8000000UL 
		#include <avr/io.h>				
		#include <inttypes.h>			
		#include <avr/interrupt.h>		
		#include <avr/pgmspace.h>		
		#include <avr/sfr_defs.h>	
		#include <util/delay_basic.h>	
		#include <util/delay.h>			


volatile	uint16_t _100cntr=0; 

void LedBlink(void)
{

		static uint8_t blink = 0; 
		
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


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 58; 
	_100cntr++;
}


int main(void)
{

	DDRB = 0xFF; 
	TCCR0 = (1<<CS01); 
	TIMSK = TIMSK | (1<<TOIE0); 
	sei(); 
	
	
	while(1)
	{
		if(_100cntr >= 500) 
		{
			_100cntr = 0;	

			LedBlink(); 
		}
	}

}
