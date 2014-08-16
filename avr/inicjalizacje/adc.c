
/*Inicjalizacja przetwornika adc
z wyrównaniem do lewej,w trybie
ciągłego pomiaru */

inline void InicADC()
 {
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
	}
