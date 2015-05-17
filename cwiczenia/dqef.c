
#include <avr/io.h>
#include <stdio.h>
#define F_CPU		16000000L	
#include <util/delay.h>	

//------------------------------------------------------------
#define BAUDRATE	9600L			//predkosc transmisji w bodach	
#define BAUD_REG  ((F_CPU/(16*BAUDRATE))-1) //dzielnika dla transm.szeregowej 

void uart_init(void)		//Inicjowanie portu UART 
 {
	UBRRH=(BAUD_REG>>8); 		//dzielnk dzestotliwosci transmisji
	UBRRL= BAUD_REG; 

	//Format ramki danych: 8data,2stopbit
	UCSRC=(1<<URSEL)| (1<<USBS)| (3<<UCSZ0);
	UCSRB=(1<<RXEN)| (1<<TXEN); 			//zezwolenie na odbior i nadawanie
 }
 //---------------------------------------------------------------
 int uart_putchar(char c, FILE *stream) //funkcja wyjsciowa strumienia
{
   loop_until_bit_is_set(UCSRA, UDRE);   
   UDR=c;
   return 0;
} 	

//funkcja wejsciowa strumienia
int uart_getch(FILE *stream)
{
	loop_until_bit_is_set(UCSRA,RXC);
	return UDR;
}


char isRsData(void)
 {

	if( (UCSRA & (1<< RXC)) !=0 )
		return 1;
	else 
		return 0;

 }

// definicja strumienia do zapisu 
static FILE rsInOut= 
		FDEV_SETUP_STREAM(uart_putchar, uart_getch, _FDEV_SETUP_RW );




//---------------------------------------------------------------
int main(void)
 {
	unsigned char dana;
	char *msg;


	uart_init();	//inicjowanie portu szeregowego
		  
	stdout = &rsInOut;
	stdin =  &rsInOut;
		
	printf("\r Zamiana cyfr w tekst:\r");

	for( ; ; ) { 
		//_delay_ms(20);	//pogorszenie
		while( isRsData())  { 	
				
			  dana=	UDR;

			  switch(dana) {
		  		case '0': msg="zero-";	break;
				case '1': msg="one-"; 	break;
				case '2': msg="two-";  	break;
				case '3': msg="three-";	break;
				case '4': msg="four-";	break;
				case '5': msg="five-";	break;
				case '6': msg="six-"; 	break;
				case '7': msg="seven-";	break;
				case '8': msg="eight-";	break;
				case '9': msg="nine-";	break;
				
				default : msg=" \r";	break;
			}
			printf(msg);
			
		}
	}
	return 0;
 }
