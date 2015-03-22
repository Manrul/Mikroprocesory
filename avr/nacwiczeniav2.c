#include <avr/io.h>				//definicje rejestrow proc itd
#include <util/delay.h>				//opoznienia
#define F_CPU 16000000UL			//czestotliwosc generatora kwarcowego

#define KB_PORT PORTD
#define KB_DIR DDRD
#define KB_PIN PIND

uint8_t licznik=0;


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
	if(skankod == 0b11101110) return 1;
	if(skankod == 0b11011110) return 2;
	if(skankod == 0b10111110) return 3;
	if(skankod == 0b01111110) return 4;
	if(skankod == 0b11101101) return 5;
	if(skankod == 0b11011101) return 6;
	if(skankod == 0b10111101) return 7;
	if(skankod == 0b01111101) return 8;
	if(skankod == 0b11101011) return 9;
	if(skankod == 0b11011011) return 10;
	if(skankod == 0b10111011) return 11;
	if(skankod == 0b01111011) return 12;
	if(skankod == 0b11100111) return 13;
	if(skankod == 0b11010111) return 14;
	if(skankod == 0b10110111) return 15;
	if(skankod == 0b01110111) return 16;

}
//ze zmiana wartosci klawisza
void Licznik(void)
{
	static char wynik=0;
	char pom;
	pom=KbScan2();
	_delay_ms(1);
	if(wynik!=KbScan2()&&KbScan2()==pom)
	{
			wynik=pom;
			if(pom==KbScan2())
		{
					if(pom==1)
						licznik--;
					else if(pom==2)
						licznik++;
					//wynik=pom;
					PORTB=licznik;
		}
	}
			
}
//ze zmianą klawisza lub co 100ms
void Licznik2(void)
{
	static char wynik=0;
	char pom;
	pom=KbScan2();
	
	if(wynik!=KbScan2())
	{
			//pom=KbScan2();
			wynik=pom;
			_delay_ms(1);
				if(pom==KbScan2())
		{
					if(pom==1)
						licznik--;
					else if(pom==2)
						licznik++;
					//wynik=pom;
					PORTB=licznik;
		}
	}
	else if(pom==1||pom==2)
	{
		_delay_ms(100);
	
	//	pom=KbScan2();
	//	_delay_ms(1);
	//	if(pom==KbScan2())
	//	{
			if(pom==1)
			licznik--;
			else if(pom==2)
			licznik++;
			wynik=pom;
			PORTB=licznik;
	//	}
	}
}

int main(void)
{
	DDRB=0xFF; 
	PORTB=0x00;
	while(1)
	{
		Licznik();
		//lub Licznik2();
	}

	return 0;
}
