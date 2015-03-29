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

char KbScan2(void)
{
	unsigned char skankod=0;
	KB_DIR = 0xF0; // starsza czesc na wyjscie
	KB_PORT = 0x0F; // tam gdzie sa wejscia wysylamy , i podwieszamy rezystor
	_delay_us(2);

	skankod = KB_PIN; // starsza odczytana czesc wrzucamy do skankodu (and 0x0F - wymuszenie by na mlodszej czesci byly 0)
	
	KB_DIR = 0x0F;
	KB_PORT = 0xF0;
	_delay_us(2);

	skankod = skankod | KB_PIN;

	return skankod;
}

char zamien(char no2btn)
{
	if(no2btn == 0b11101110) return 1;
	if(no2btn == 0b11011110) return 2;
	if(no2btn == 0b10111110) return 3;
	if(no2btn == 0b01111110) return 4;
	if(no2btn == 0b11101101) return 5;
	if(no2btn == 0b11011101) return 6;
	if(no2btn == 0b10111101) return 7;
	if(no2btn == 0b01111101) return 8;
	if(no2btn == 0b11101011) return 9;
	if(no2btn == 0b11011011) return 10;
	if(no2btn == 0b10111011) return 11;
	if(no2btn == 0b01111011) return 12;
	if(no2btn == 0b11100111) return 13;
	if(no2btn == 0b11010111) return 14;
	if(no2btn == 0b10110111) return 15;
	if(no2btn == 0b01110111) return 16;
	

	return 0;
}

int main(void)
{	
	DDRB=0xFF; // dajemy port B na wyjscie

	while(1)
	{
		liczba(zamien(KbScan2()));
	}

return 0;
}
