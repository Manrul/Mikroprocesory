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
-RCX zakończony odbiór(buforze są nie odczytane dane)
-TCX oznaczający zakończenie transmisji
-UDRE ustawia się gdy UC może przyjąć nowe dane(bufor jest pusty)
-FE ustawia się gdy UC wykryje błędną ramke danych
-DOR ustawia się gdy UC wykryje przepełnienie danych
-PE-ustawia się gdy jest błąd parzystośsci
-U2X podwójna szybkość(jedynie dla transmisji asynchronicznej)
-MPCM tryb pracy między procesorami

KOLEJNY REJESTR UCSRB:
-RXCIE ustawienie bitu powoduje generowanie przerwań po zakończonym odbiorze danych(RCX=1)
-TXCIE włącza przerwania po zakończeniu wysyłania danych (TXC=1)
-UDRIE odblokowuje przerwanie pojawiające się gdy procesor jest gotowy przyjąć nowe dane(UDRE=1)
-RXEN-uruchamia odbiornik modułu USART
-TXEN uruchamia nadajnik modułu USART
-UCSZ2-bity ustawiające liczbe bitów danych w ramce*
-RXB8 rejestr tylko do odczytu,stanowioący 9 bit danych odebranych
-TXB8 rejest zawiarający 9 bit danych przy wysyłaniu


REJESTR UCSRC:
-URSEL wybór dostępu do rejestrów UBRRH i UCSRC, chcąc dokonać zapisu do UCSRC należy ustawić 1 na tym bicie
-UMSEL wybór trybu pracu modułu(1-praca synchroniczna,0-asynchroniczna)
-UPM1:0-ustawienie trybu parzystości
-USBS wybór liczby bitów stopu(0-1bit,1-2 bity)
-UCSZ1:0-kontunuacja ustawiania liczby bitów w ramce*
-UCPOL "Polaryzacja zegara"?(jedynie dla pracy synchronicznej)

*MOŻLIWE KONFIRURACJE BITÓW
UCSZ2 UCSZ1 UCSZ0 Rozmiar znaku
0 0 0 5 bitów
0 0 1 6 bitów
0 1 0 7 bitów
0 1 1 8 bitów
1 0 0 zastrzeżone
1 0 1 zastrzeżone
1 1 0 zastrzeżone
1 1 1 9 bitów

Rejestry UBRRL i UBRRH-słuzą do wyboru szybkości transmisji,
ich wartość dobiora się na podstawie równania:UBRR=(F_CPU/(16*v_transmisji))-1
następnie należy dokonać zapisu do odpowienich części rejestru
*/
