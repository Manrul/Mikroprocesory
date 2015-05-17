#include <avr/io.h>
#define F_CPU		8000000L
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <stdio.h>
//------------------------------------------------------------
#define BAUDRATE	9600L			//predkosc transmisji w bodach
#define BAUD_REG  ((F_CPU/(16*BAUDRATE))-1) //dzielnika dla transm.szeregowej

#define FIFO_L 128							 //dlugosc kolejek FIFO

struct  { unsigned char wi;					 //indeks odczytu unsigned
		 char ri;								//indeks zawpisu unsigned 
		 char buff[FIFO_L]; 
	 } InputFifo ={0,0},						//kolejeka wejściowa FIFO 
	OutputFifo={0,0};							//kolejeka wyjściowa FIFO


char *znajdz(char *str1, char *str2)//str1-przeszukiwany w poczukiwaniu str2
{
	int i, j, k;
	for (i = 0; *(str1+i) != '\0'; i++)
	{
		for (j = i, k = 0; *(str2+k) != '\0'&& *(str1+j) == *(str2+k); j++, k++);
		if (k > 0 && *(str2+k) == '\0')
		return *(str1+i);
	}
	return 0;
}		
		
		
ISR(USART_RXC_vect) /*VECTOR(11), USART, RxComplete*/ 
{   
	 InputFifo.buff[InputFifo.wi++]=UDR;   //umieszczenie danej w kolejce    
		if (InputFifo.wi == FIFO_L)
		 InputFifo.wi = 0; 
}
	//---------------------------------------------------
	// zwraca: 0 -gdy bufor odbiornika pusty
 //    1 -gdy pobrany znak umieszczony w '*p_dada'
unsigned char GetFromSerial(unsigned char *p_dada) 
 {
	  if (InputFifo.ri == InputFifo.wi)
		 return 0;  
	  else  {
		     *p_dada = InputFifo.buff[InputFifo.ri++]; 
			 if (InputFifo.ri == FIFO_L) 
				InputFifo.ri=0;
			return 1; 
			 } 
}
		
ISR(USART_UDRE_vect) /*VECTOR(12), USART Data Register Empty*/
 {                                 
	  if (OutputFifo.wi == OutputFifo.ri) 
			UCSRB &= ~(1<<UDRIE); //bufor FIFO pusty - wylaczenie przerwania   
	   else {    UDR = OutputFifo.buff[OutputFifo.ri++]; //dana z bufora do rejestru UDR 
		      if (OutputFifo.ri == FIFO_L)
				 OutputFifo.ri = 0; 	
			 }
 }
		
void PutToSerial(unsigned char data) 
{                                    
      OutputFifo.buff[OutputFifo.wi++] = data;
	   
	  if (OutputFifo.wi == FIFO_L )
		 OutputFifo.wi = 0;  
	UCSRB |=(1<<UDRIE);  // wlaczenie przerwan
 } 
		

void uart_init(void)		//Inicjowanie portu UART
{
	UBRRH=(BAUD_REG>>8); 		//dzielnk dzestotliwosci transmisji
	UBRRL= BAUD_REG;

	//Format ramki danych: 8data,2stopbit
	UCSRC=(1<<URSEL)| (1<<USBS)| (3<<UCSZ0);
	UCSRB=(1<<RXEN)| (1<<TXEN); 			//zezwolenie na odbior i nadawanie
	UCSRB |=(1<<RXCIE);
}
//---------------------------------------------------------------

// pomocnicza funkcja wysyłająca napis do kolejki 
void StrToSerial(char *msg) 
{ 
	while(*msg!=0)
	 PutToSerial(*msg++);
 }

//---------------------------------------------------------------
//--------------------------------------------------------------
int main(void)
 { 
	 unsigned char dana;
	 uint8_t flaga = 1;
	 char *adres;
	  DDRB =0xFF;							//PB- wyjściowy port testowy
	  PORTB =0x00;
	   uart_init();							//inicjowanie portu szeregowego 
	  sei();								//włączenie przerwań
	    for( ; ; ) {
	 // generacja impulsu, brak obsługi portu szeregowego na 110 ms 
		    PORTB |= (1<<PB0);  
			 _delay_ms(10);   
			  PORTB &=~(1<<PB0);
			    _delay_ms(100);
//pobranie danych z kolejki wejśc. - umieszczenie w kolejce wyjściowej 
 while( GetFromSerial( &dana) ) 
  { 
	   adres=znajdz(InputFifo.buff, "zapal");
	   if(adres&&flaga==1)
	   {
		  
		   StrToSerial(" zapalono");
		   PutToSerial(10);//'\n'
		  // PutToSerial(13);//'\r'
		   *adres="zapa1";
		   flaga=0;
		   dana=' ';
		   PORTB|=(1<<PB1);
		    InputFifo.ri = InputFifo.wi;
	   }
	    adres=znajdz(InputFifo.buff, "zgas");
	    if(adres&&flaga==1)
	    {
		    
		    StrToSerial(" zgaszono ");
			PutToSerial(10);
		    *adres="zga1";
		    flaga=0;
		    dana=' ';
		    PORTB &=~ (1<<PB1);
		    InputFifo.ri = InputFifo.wi;
	    }
	  switch(dana) { 
		   case '0': StrToSerial("zero-"); break;
		   case '1': StrToSerial("jeden-"); break;
		   case '2': StrToSerial("dwa-");  break;
		   case '3': StrToSerial("trzy-");  break;
		   case '4': StrToSerial("cztery-"); break; 
		   case '5': StrToSerial("piec-"); break; 
	       case '6': StrToSerial("szesc-"); break; 
		   case '7': StrToSerial("siedem-"); break; 
		   case '8': StrToSerial("osiem-"); break; 
		   case '9': StrToSerial("dziewiec-"); break; 
		   default : PutToSerial(dana); break;
					 }
				}
			 flaga=1;
		 }
 return 0;
}
