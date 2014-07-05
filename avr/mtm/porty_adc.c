      			#define	F_CPU	8000000UL //Definicja  czestotliwości pracy UC
      		//--------------------------------------//
		//------ BIBLIOTEKI STANDARDOWE --------//
		//--------------------------------------//

			#include <avr/io.h>				// zawiera definicje WE/WY uK.(np.drukujace)
			#include <inttypes.h>				// zdeklarowane typy zmiennych
			#include <avr/interrupt.h>			// zdeklarowane nazwy przerwan
			#include <avr/pgmspace.h>			// informacje nt. danego mikrokontrolera (inf. o pamieci)
			#include <stdlib.h>				// standardowa biblioteka
			#include <avr/sfr_defs.h>			// definicje rejestrow specjalnych (porty,przetwroniki itd)
			#include <util/delay_basic.h>			// opóŸnienia (gotowe)
			#include <util/delay.h>				// opóŸnienia (gotowe)

int main(void)
{


	DDRB = 0xFF;        //cale B na wyjscie
	DDRA = 0x00;		// A na wyjscie
	PORTA = 0x00;		// pullup OFF	
	//Ustawienie przetwornika adc
	ADMUX = (1<<REFS0)|(1<<ADLAR);
		// REFS0 - ustawienie napiecia na wartosc napiecia zasilania
		// ADLAR - wlaczenie wyrownania do lewej
		// ostatnie 5 bitow (tu 00000) ustawienie ADC.N (tu ADC.0) (N - nr pinu)
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1);
		// ADEN - wlacza przetwornik
		// ADSC - uruchamia pierwszy pomiar
		// ADATE - wlacza trigger
		// ADIF - flaga przerwania
		// ADIE - odmaskowuje przerwanie
		// ADPS2:0 - dzielnik czestotliwosci
	SFIOR = 0x00;//Free run
	
	
		//zmienne ośmiobitowe
	uint8_t wynik_ADC;
	uint8_t	linijka;

	while(1)//pętla nieskończona          
	{
		

		wynik_ADC = ADCH;//przypisanie zmiennej wyniku pomiaru
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
		
				

		PORTB = linijka;//wystawienie zmiennej linijka na port B(binarnie)
	}
}
