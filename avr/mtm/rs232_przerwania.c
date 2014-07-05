#define F_CPU 8000000UL
 

 
	#include <avr/io.h>                     
	#include <inttypes.h>                  
	#include <avr/interrupt.h>              
	#include <avr/pgmspace.h>        
	#include <stdlib.h>                  
	#include <avr/sfr_defs.h>              
	#include <util/delay_basic.h>   		
	#include <util/delay.h>          

volatile unsigned char rec_data;
unsigned char text1[]={ "Ala ma kota\n\r" };
unsigned char text2[]={ "Ola ma psa\n\r" };


void USART_Transmit( unsigned char data )
{

while ( !( UCSRA & (1<<UDRE)) )
;

UDR = data;
}

void SendString(unsigned char *pntr)
{	
	while(*pntr!='\0')
	{
		USART_Transmit(*pntr); 
		pntr++; 
	}
}

unsigned char USART_Receive( void )
{

while ( !(UCSRA & (1<<RXC)) )
;
return UDR;
}

ISR(USART_RXC_vect)
{
	
	rec_data = UDR;
	USART_Transmit(rec_data);
}

int main()
{	
	
	UCSRA = 0x00;
	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN); //RXCIE - inicjalizacja przerwan//
	
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRH = 0;
	UBRRL = 51;
	sei();

	while(1)
	{	
		if(rec_data == 'a')
		{
		SendString(text1); 
		_delay_ms(100);
		} else if(rec_data == 'k')
			{
		SendString(text2);
		_delay_ms(100);
			} else 
				{
		SendString("Wcisnales zly klawisz lub nic nie wcisnales\n\r");
		_delay_ms(1000);
				}
	}
}
