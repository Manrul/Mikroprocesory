  #define F_CPU 8000000UL
	#include <avr/io.h>
	#include <inttypes.h>                  
	#include <avr/interrupt.h>              
	#include <avr/pgmspace.h>               
	#include <stdlib.h>                   
	#include <avr/sfr_defs.h>              
	#include <util/delay_basic.h>   		
	#include <util/delay.h>                 

volatile unsigned char wynik[5];
volatile unsigned char rec_data;


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

ISR(USART_RXC_vect)
{
	// ECHO //
	rec_data = UDR;
	USART_Transmit(rec_data);
}

int main()
{	
	//--ADC--//
	DDRB = 0xFF;
	DDRA = 0x00;		
	PORTA = 0x00;		
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1);
	SFIOR = 0x00;	
	
	UCSRA = 0x00;
	UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRH = 0;
	UBRRL = 51;
	sei();

	
	while(1)
	{	
		if(rec_data == 'a')
		{
		itoa((int)((float)ADC), wynik, 10);
		SendString("\n\r");
		SendString(wynik);
		} else
			{
			SendString("Nico Rosberg miszcz F1\n\r");
			_delay_ms(1000);
			}
	}
}
