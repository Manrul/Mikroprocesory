      			#define	F_CPU	8000000UL 
			#include <avr/io.h>				
			#include <inttypes.h>			
			#include <avr/interrupt.h>	
			#include <avr/pgmspace.h>		
			#include <stdlib.h>				
			#include <avr/sfr_defs.h>		
			#include <util/delay_basic.h>	
			#include <util/delay.h>		


int main(void)
{


	DDRB = 0xFF;        
	DDRA = 0x00;		
	PORTA = 0x00;		
	ADMUX = (1<<REFS0)|(1<<ADLAR);
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1);
	SFIOR = 0x00;
	
	

	uint8_t wynik_ADC;
	uint8_t	linijka;

	while(1)          
	{
		

		wynik_ADC = ADCH;
		linijka = 0;
		if( wynik_ADC < 32 ) linijka = 1;
		if( wynik_ADC > 32) linijka = 2;
		if( wynik_ADC > 64) linijka = 4;
		if( wynik_ADC > 96) linijka = 8;
		if( wynik_ADC > 128) linijka = 16;
		if( wynik_ADC > 160) linijka = 32;
		if( wynik_ADC > 192) linijka = 64;
		if( wynik_ADC > 224) linijka = 128;
		if( wynik_ADC > 256) linijka = 256;
		
				

		PORTB = linijka;
	}
}
