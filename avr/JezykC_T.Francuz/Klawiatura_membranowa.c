			#define	F_CPU	1000000UL
			#include <avr/io.h>
			#include <inttypes.h>
			
			

			uint8_t SprawdzPort()
			{
				uint8_t y=0;
				uint8_t x=0;
				while(y<4)
				{
					x=PORTA;
					x=(x|0x0F)^(1<<y);
					PORTA=x;
					asm volatile ("nop");
					x=PINA;
					if((x & 0x70)!=0x70)
					{
						if(( x & 0x10)==0) x=0;
						else if((x & 0x20)==0) x=1;
						else x=2;
						x=x+y*3;
						return x;
					}
					y++;
				}
				return 255;
			}



			void main()
			{
				DDRA=0x0F;
				PORTA=0x7F;
				DDRB = 0xFF;
				PORTA=0x00;
				
				
				
				while(1);
				
				
			}
			
			
			
			
			
