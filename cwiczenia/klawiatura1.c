#include <avr/io.h>					//definicje rejestrow proc itd

#define F_CPU 16000000UL			//czestotliwosc generatora kwarcowego
#include <util/delay.h>				//opoznienia


//definicja rejestrów portu do którego podlaczona jest klawiatura
#define KB_PORT PORTD
#define KB_DIR DDRD
#define KB_PIN PIND

//Funkcja skanujaca klawiaturę - wersja 1, zwraca
//numer nacisnietego przycisku lub zero gdy brak detekcji znaku
char KbScan(void)
{
	char result=0;
	KB_DIR =0b00010000; //tylko kolumna C0 na wyjscie
	KB_PORT=0b11101111; //wymuszenie zera
	_delay_us(2); //delaye sa po to by zmienil sie stan na portach
	if( (KB_PIN & 0x01) ==0 ) result=1;
	if( (KB_PIN & 0x02) ==0 ) result=5;
	if( (KB_PIN & 0x04) ==0 ) result=9;
	if( (KB_PIN & 0x08) ==0 ) result=13;
	KB_DIR =0b00100000; //tylko kolumna C1 na wyjscie
	KB_PORT=0b11011111; //wymuszenie zera
	_delay_us(2);
	if( (KB_PIN & 0x01) ==0 ) result=2;
	if( (KB_PIN & 0x02) ==0 ) result=6;
	if( (KB_PIN & 0x04) ==0 ) result=10;
	if( (KB_PIN & 0x08) ==0 ) result=14;
	KB_DIR =0b01000000; //tylko kolumna C2 na wyjscie
	KB_PORT=0b10111111; //wymuszenie zera
	_delay_us(2);
	if( (KB_PIN & 0x01) ==0 ) result=3;
	if( (KB_PIN & 0x02) ==0 ) result=7;
	if( (KB_PIN & 0x04) ==0 ) result=11;
	if( (KB_PIN & 0x08) ==0 ) result=15;
	KB_DIR =0b10000000; //tylko kolumna C3 na wyjscie
	KB_PORT=0b01111111; //wymuszenie zera
	_delay_us(2);
	if( (KB_PIN & 0x01) ==0 ) result=4;
	if( (KB_PIN & 0x02) ==0 ) result=8;
	if( (KB_PIN & 0x04) ==0 ) result=12;
	if( (KB_PIN & 0x08) ==0 ) result=16;
	KB_PORT=0xFF;
	return result;
}

void liczba(uint8_t klawiszDoLiczby)
{
	PORTB=klawiszDoLiczby;
}

int main(void)
{	
	DDRB=0xFF; // dajemy port B na wyjscie

	while(1)
	{
		liczba(KbScan());
	}

return 0;
}
