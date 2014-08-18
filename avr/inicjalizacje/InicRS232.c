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
/*W ogólnym przypadku należy odpowienio ustawić rejestry
UCSRA,którego kolejne bity odpowiadają za:
-RCX(tylko do odczytu)-ustawia się gdy w buforze są nie odczytane dane
-TCX oznaczający zakończenie transmisji
-kolejne 4 bity są flagami jedyniue do odczytu
-U2X podwójna szybkość(jedynie dla transmisji asynchronicznej)
-MPCM tryb pracy między procesorami

KOLEJNY REJESTR UCSRB:
-RXCIE ustawienie bitu powoduje generowanie przerwań po zakończonym odbiorze danych
-TXCIE włącza przerwania po zakończeniu wysyłania danych 
-UDRIE odblokowuje przerwanie pojawiające się gdy procesor jest gotowy przyjąć nowe dane
-RXEN-uruchamia odbiornik modułu USART
-TXEN uruchamia nadajnik modułu USART
-UCSZ2-0-bity ustawiające liczbe bitów danych w ramce*
-RXB8 rejestr tylko do odczytu,stanowioący 9 bit danych odebranych
-TXB8 rejest zawiarający 9 bit danych przy wysyłaniu

