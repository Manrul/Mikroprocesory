			#define	F_CPU	1000000UL
			#include <avr/io.h>
			#include <inttypes.h>
			
			

			uint8_t SprawdzPort()
			{
				uint8_t y=0;
				uint8_t x;
				while(y<4) //Ponieważ są 4 rzędy klawiszy
				{
					x=PORTA;
					x=(x|0x0F)^(1<<y);// Sprawdz który rząd jest aktywny
					PORTA=x;
					asm volatile ("nop");
					x=PINA;
					if((x & 0x70)!=0x70)//sprawdza czy jakis klawisz jest wcisniety
					{
						if(( x & 0x10)==0) x=0;//sprawdza z której kolumny jest ten klawisz
						else if((x & 0x20)==0) x=1;
						else x=2;
						x=x+y*3;//wyznacza numer wybranego klawisza
						return x;
					}
					y++;
				}
				return 255;
			}



			void main()
			{
				DDRA=0x0F; //4 rzedy to wyjscia,3 kolumny to wejscia
				PORTA=0x7F;//włacza pull up na kolumnach,ustawia 1 w rzedach
				
				while(1);
				
				
			}
			
			
			
			
			
