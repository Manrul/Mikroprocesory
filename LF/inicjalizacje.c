/*
 * inicjalizacje.c
 *
 *  Created on: 2 gru 2015
 *      Author: Michał
 */
#include "main.h"

/*inicjalizacja pinów odpowiedzialnych
 * za diody i sterowanie mostkiem h
 * (kierunek obrotu silnika)
 */
void init_pin(void)
{
	/*PA0-PA3-diody
	 * PC0- wejscie przycisku z rezystorem podciagajacym
	 * PC6 i PC7- diody
	 * PD0-przerwanie zewnetrzene
	 * PD4-PD7 sterowanie kierunkiem silnika//
	 * PE0 i PE1 U
	 * PF0-PF7 wejście do czujników
	 */
	DDRA|=(1<<PE0)|(1<<PE1)|(1<<PE2)|(1<<PE3);
	DDRC|=(1<<PC6)|(1<<PC7);
	DDRD|=(1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7);
	DDRF=0x00;
}

/* funkcja inicjualizująca timer1
 * do generacji sygnału pwm
 * w trybie fast pwm, synał doprowadzony
 * do wyjsc OC1A i OC1B
 * zerowane sa przy dopasowaniu
 * ustawiane przy ICR1(TOP)
 * czyli gdy  rosnie wartosc OCR1A i OCR1B(OCRnx)
 * wzieksza sie wypełnienie///chyba
 */
void init_pwm(void)
{
	 	 TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
	 	 TCCR1B|=(1<<WGM12)|(1<<WGM13)|(1<<CS10);
	 	 ICR1=TOP;
}

/* funkcja do uruchomienie przetwornika adc
 * w trybie 8 bitowym
 * rejestr ADMUX należy aktualizowac
 * w funkcji odpowiadajacej za odczyt czujnikow
 * w celu multipleksowania kanałów
 */
void init_adc(void)
{
	ADMUX|=(1<<REFS0)|(1<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

/*Timer potrzebny do wywolywania funkji
 * odczytu portow i wyliczania nastaw pwm
 * w równych odstepach czasowych
 * przerwanie co 1ms przy zegarze 16MHz
*/
void init_timer(void)
{
	OCR0=250;
	TCCR0|=(1<<WGM01)|(1<CS02);
	TIMSK|=(1<<OCIE0);
	sei();
}

/*funkcja uruchamiajaca interfejs
 * UART w celu debugowania
 */
void init_uart(void)
{
	/* Ramka danych: 8data, 2stop bit
	 * predkosci 9600BAUD
	 */
	 UBRR0H = 0;
	 UBRR0L =103;
	 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	 UCSR0C = (1<<USBS0)|(1<<UCSZ00)|(1<<UCSZ10);//|(3<<UCSZ00) ZAMIAST TYCH DWOCH
}

/* funkcja wywolujaca funkcje odpowiadajace
 * za inicjalizacje portow//peryferiow
 */
void init(void)
{
	init_pin();
	init_pwm();
	init_adc();
	init_timer();
	init_uart();
}
