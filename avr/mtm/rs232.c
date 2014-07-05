			 #define	F_CPU	8000000UL 
			#include <avr/io.h>				
			#include <inttypes.h>			
			#include <avr/interrupt.h>	
			#include <avr/pgmspace.h>		
			#include <stdlib.h>				
			#include <avr/sfr_defs.h>		
			#include <util/delay_basic.h>	
			#include <util/delay.h>	


//funkcja wysyłająca znak, otrzymany przy wywołaniu
void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) )
;
/* Put data into buffer, sends the data */
UDR = data;
}


int main()
{	
	//Ustawienie usart
	UCSRA = 0x00;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	//-- jesli chcemy odbierac dane to RXCIE dajemy 1 --//
	//-- RXEN - zalaczenie odbiornika --//
	
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
		//ustawienie prędkości transmisji na 9600bit/s
	UBRRH = 0;
	UBRRL = 51;

	while(1)
	{//funkcjia wysyłająca kolejnie liczby co 100ms
		static uint8_t i=0;
		i++;

		USART_Transmit(i);
		_delay_ms(100);
	}
}
