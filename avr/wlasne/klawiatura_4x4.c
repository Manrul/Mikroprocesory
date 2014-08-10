//Funkcja SprawdzKlaw zwraca wartosc wciskanego przycisku klawiatury 4x4 1-16 lub 255 gdy żaden nie wybrany.


/*
Sposób podłczenia:
--------------------
|PORTD|| 0| 1| 2| 3|
====================
|    4|| 1| 2| 3| 4|
--------------------
|    5|| 5| 6| 7| 8|
--------------------
|    6|| 9|10|11|12|
--------------------
|    7||13|14|15|16|
--------------------
*/

//Definicje:
#define PORT_pod PORTD
#define DDR_pod DDRD
#define PIN_pod PIND

//Inicjalizacja obsługi klawiatury.
void InicKlaw (void)
{
	DDR_pod = 	0b11110000; //Wiersze jako wyjœcia (starsze 4 bity), kolumny jako wejœcia (m³odsze 4 bity).
}
 
char SprawdzKlaw (void)
{
	char n = 0;
	PORT_pod = 0b11101111;
	while(n<3) 
	{
		asm volatile ("nop");
		if (PIN_pod & 0b11111110) return (1+n*4);
		if (PIN_pod & 0b11111101) return (2+n*4);
		if (PIN_pod & 0b11111011) return (3+n*4);
		if (PIN_pod & 0b11110111) return (4+n*4);
		PORT_pod = (PORT_pod << 1)|0x01 ;
		n++;
	}  
	return 255;
} 
	

  
