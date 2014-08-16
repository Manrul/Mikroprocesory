/* Inicjalicja RS232
-prędkość transmisji 9600bit/s
1 bit stopu
parzystość wyłączona
tryb synchroniczny
8 bitów danych */


inline void InicRS232()
{
  UCSRA = 0x00;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	
	//-- RXEN - zalaczenie odbiornika--//
	
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
		//ustawienie prędkości transmisji na 9600bit/s
	UBRRH = 0;
	UBRRL = 51;
}
