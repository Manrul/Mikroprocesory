                #define F_CPU 8000000UL
                #include <avr/io.h>                     
                #include <inttypes.h>                 
                #include <avr/interrupt.h>      
                #include <avr/pgmspace.h>               
                #include <stdlib.h>                            
                #include <avr/sfr_defs.h>               
                #include <util/delay_basic.h>   
                #include <util/delay.h>                 
 
             //tablica z lwartoscia poczatkowo
             //wtrakcie pracy bedzie przyjmowala wartosci otrzymana z przertwornika
 		            volatile uint8_t _7segstring[4]={1,3,3,7};
 		            //funkcja z zapisanymi kształtami liter w wyswietlaczy 7 segmentowym
void WyswietlKsztaltCyfry(uint8_t dana)
{    
	const uint8_t ksztalty_cyfr[10] = { 0b00111111, 
                                        0b00000110, 
                                        0b01011011, 
                                        0b01001111, 
                                        0b01100110, 
                                        0b01101101, 
                                        0b01111101, 
                                        0b00000111, 
                                        0b01111111, 
                                        0b01101111 };

	PORTB = ksztalty_cyfr[dana];
 
}
//funkcja służoca do odłączenia katod(wyłącza wyświetlacz)
void WylaczKatody(void)
{
	PORTC &= 0b11110000; 
}
//funckja uruchamiająca daną katode(uruchamia wybrany wyświetlacz)
void ZalaczKatode(uint8_t index)
{
	const uint8_t index_katody[4]={ 0b00000001,
								    0b00000010,
								    0b00000100,
								    0b00001000 };

	PORTC = PORTC|index_katody[index];
}
//funckaj obsługi wyświetalacza
//początkowo wyłącza wyswietlacz
//nastepienie  przy pomocy funkcji wysiwietlkształtcyfry wysyła na porb b odpowiedni ciąg liczb
//nastepnie uruchamia kolejno
void _7SegRoutine(void) 
{
	static uint8_t index_cyfry=0;
		WylaczKatody();
		WyswietlKsztaltCyfry(_7segstring[index_cyfry]);
		ZalaczKatode(index_cyfry);	

		index_cyfry++;

		if( index_cyfry > 3 )
		{
			index_cyfry=0;
		}

}
//funkcja przypisujca odpowiednio cyfre z wyniku otrzymanego z przetwornika do tablicy
void Konwertuj(uint16_t liczba)
{
	_7segstring[0]=liczba/1000;
	_7segstring[1]=(liczba%1000)/100;;
	_7segstring[2]=(liczba%100)/10;
	_7segstring[3]=liczba%10;
}

int	main(void)
{
	//porty
	DDRB = 0xFF; 
	DDRC = 0b00001111;
	DDRA = 0x00;	
	PORTA = 0x00;	
	//uruchominie adc
	ADMUX = (1<<REFS0)|(1<<ADLAR);
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1);
	SFIOR = 0x00;
 
            //timer
	TCCR0=(1<<CS01);
    TIMSK=TIMSK|(1<<TOIE0);
    sei();
 
    while(1) 
    {
			//funkcja konwertuje wartosc z przetwornika na Volty
			// nastepienie zapisuje wynik do tablicy
		Konwertuj((uint16_t)(float)ADC*4.89);

    }
        
}

 //obsługo przerwania wywołująca obsługe wyświetlacza
ISR(TIMER0_OVF_vect)
{
        TCNT0=58;
 		_7SegRoutine(); 
}
