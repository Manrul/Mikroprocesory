//Funkcja SprawdzKlaw zwraca wartosc wciskanego przycisku klawiatury 4x3 1-12 lub 255 gdy żaden nie wybrany.



//Definicje:
#define PORT_pod PORTD
#define DDR_pod DDRD
#define PIN_pod PIND

//Inicjalizacja obsługi klawiatury.
inline void InicKlaw (void)
{
	DDR_pod = 	0b00001111;
	PORT_pod =	0b11111110; //Wiersze jako wyjœcia (młodsze 4 bity), kolumny jako wejœcia (starsze 4 bity).
}
 
char SprawdzKlaw (void)
{
	char n = 0;
	PORT_pod = 0b11111110;
	while(n<4) 
	{
		asm volatile ("nop");
		if (~PIN_pod & 0b00010000) return (1+n*3);
		if (~PIN_pod & 0b00100000) return (2+n*3);
		if (~PIN_pod & 0b01000000) return (3+n*3);
		
		PORT_pod = (PORT_pod << 1)|0x01;
		n++;
	}  
	return 255;
} 
