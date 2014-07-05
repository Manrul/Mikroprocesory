     #define	F_CPU	8000000UL 
			#include <avr/io.h>				
			#include <inttypes.h>			
			#include <avr/interrupt.h>	
			#include <avr/pgmspace.h>		
			#include <stdlib.h>				
			#include <avr/sfr_defs.h>		
			#include <util/delay_basic.h>	
			#include <util/delay.h>	



void USART_Transmit( unsigned char data )
{

while ( !( UCSRA & (1<<UDRE)) )
;

UDR = data;
}


int main()
{	
	
	UCSRA = 0x00;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);

	UBRRH = 0;
	UBRRL = 51;

	while(1)
	{
		static uint8_t i=0;
		i++;

		USART_Transmit(i);
		_delay_ms(100);
	}
}
