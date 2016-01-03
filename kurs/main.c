#include <avr/io.h>
#include <avr/interrupt.h>
//#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>				//do sprintf
#include <stdlib.h>
#include "lcd.h"
#include "definicje.h"



//zmienne globalne
volatile unsigned char lcd_buff_full=0;
volatile unsigned char key=0;
char *lcd_buff;
unsigned char menu_local;
volatile unsigned char runme=0;
struct menu *menu_ptr;

int main(void)
{

	diody_20dir=3;			//ustawienie diod na wyjście
	diody_21dir=7;
	diody_22dir=7;
	diody_20=2;
	diody_21=3;
	diody_22=4;

	menu_ptr=&M0;



	//ustawienie adc
	ADMUX = (1<<REFS0)|(1<<ADLAR);
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<ADPS1);

	OCR0=199;					//konfiguracja timera
	TCCR0|=1<<CS01|1<<WGM01;
	TIMSK|=1<<OCIE0;
	sei();


	lcd_rs_dir=1;
	lcd_e_dir=1;
	lcd_data_dir=15;

	led_dir=255;
	keyh_dir=0;
	keyh_port=15;

	lcd_buff=malloc(80);	//80 bajtów przydzielonej pamięci (z biblioteki stdlib) na nasz bufor
	lcd_buff_full=1;		//koniec uzupełniania bufora-->można wypisać
	while(lcd_buff_full);
	key=255;
	while(1)
	{
		if(lcd_buff_full==1) continue;
		if(menu_local!=0)
			if(runme !=0)
			{
				(*(menu_ptr->function))(2);
				runme=0;
			}
			else
				(*(menu_ptr->function))(0);
		else
			if(key!=0)
			{
			switch(key)
			{
				case 1: // down/ENTER
					if(menu_ptr->down!=NULL)
						menu_ptr=menu_ptr->down;
					else if(menu_ptr->function!=NULL)
						{
							(*(menu_ptr->function))(1);
							menu_local=1;
							key=254;
						}
					break;

				case 2: //right
					if(menu_ptr->right!=NULL)
						menu_ptr=menu_ptr->right;
					break;
				case 4:	//left
					if(menu_ptr->left!=NULL)
						menu_ptr=menu_ptr->left;
					break;
				case 8:	//up/esc
					if(menu_ptr->up!=NULL)
						menu_ptr=menu_ptr->up;
					break;
				default:
					break;
			}
			if(key!=254)
			{
				sprintf(lcd_buff,"\001\x01\004\377%s",menu_ptr->str);
				lcd_buff_full=1;
				key=0;
			}
		}
	}
	return 0;
}


ISR(TIMER0_COMP_vect)
{

	static unsigned char lcd_cnt=0;
	static unsigned char lcd_index=0;

	static unsigned char key_cnt=0;
	static unsigned char key_level=0;
	static unsigned char key_reg=0;
	static unsigned short int period_cnt=0;

	if(menu_ptr->period!=0)
		if(period_cnt==0)
		{
			runme=1;
			period_cnt=menu_ptr->period;
		}
	if(period_cnt>0)
		period_cnt--;

	if(lcd_cnt==0 && lcd_buff_full!=0)
	{
		switch(*(lcd_buff+lcd_index))
		{
			case 1:
				lcd_index++;
				lcd_write_instruction(*(lcd_buff+lcd_index));
				lcd_index++;
				break;

			case 4:
				lcd_index++;
				lcd_cnt=*(lcd_buff+lcd_index);
				lcd_index++;
				break;

			case 0:
				lcd_index=0;
				lcd_buff_full=0;
				break;

			default:
				lcd_write_data(*(lcd_buff+lcd_index));
				lcd_index++;
		}

	}
	if(lcd_cnt>0)
		lcd_cnt--;

	if(key_cnt==0)
	{
		switch(key_level)
		{
			case 0:
				key_reg=keyh;
				if(key_reg!=15)
				{
					key_level=1;
					key_cnt=200;
				}
				break;
			case 1:
				if(keyh==key_reg)
					key=~key_reg&0x0F;		//negujemy i zeruremy najstarsze bity
				key_level=2;
				break;
			case 2:
				if(keyh==15)
					key_level=0;
				break;
			default:
				break;
		}
	}

	if(key_cnt>0)
		key_cnt--;


}



void M0af(char n)
{

	static struct diody_2 diody012;
	static int tmp=0;

	switch(n)
	{
	case 0:
		if(key!=0)
		{
			switch(key)
			{
				case 1:
					if(menu_local<3)
					{
						menu_local++;
					}
					else if(menu_local==3)
					{
						diody_20=diody012.d0;
						diody_21=diody012.d1;
						diody_22=diody012.d2;
						menu_local=0;
						key=255;
					}
					break;
				case 2:
					if(menu_local==1)
					{
						if(diody_20<3)
							diody012.d0++;
					}
					else if(menu_local==2)
					{
						if(diody_21<7)
							diody012.d1++;
					}
					else if(menu_local==3)
					{
						if(diody_22<7)
							diody012.d2++;
					}
					break;
				case 4:
					if(menu_local==1)
					{
						if(diody_20>0)
							diody012.d0--;
					}
					else if(menu_local==2)
					{
						if(diody_21>0)
							diody012.d1--;
					}
					else if(menu_local==3)
					{
						if(diody_22>0)
							diody012.d2--;
					}
					break;
				case 8:
					menu_local--;
					if(menu_local==0)
						key=255;
					break;
				}

			if(key!=255)
			{
				sprintf(lcd_buff,"\001\x0C\004\020\001\x80\004\020A=%d B=%d C=%d\001\%c\004\020\001\x0F\004\020",diody012.d0,diody012.d1,diody012.d2,(menu_local-1)*4+2+0x80);
				lcd_buff_full=1;
				key=0;
			}
		}

		break;
	case 1:
		diody012.d0=diody_20;
		diody012.d1=diody_21;
		diody012.d2=diody_22;
		break;
	case 2:
		sprintf(lcd_buff,"\001\x0C\004\020\001\xC0\004\020%d \001%c\004\020\001\x0D\004\020",tmp, 0x80+(menu_local-1)*4+2);

		lcd_buff_full=1;
		tmp++;
	break;
	}
}
void M0bf(char n)
{
   static char kanal=0;
	switch(n)
	{
	case 0:
		if(key!=0)
		{
			switch(key)
			{
				case 1:
					ADMUX &= 0b11111000;
					ADMUX |= (kanal & 0b00000111);
					menu_local=0;
					key=255;
					break;

				case 2:
					if(kanal <7)
						kanal++;
					break;
				case 4:
					if(kanal >0)
						kanal--;
					break;
				case 8:
					menu_local--;
					if(menu_local==0)
						key=255;
					break;
				}

			if(key!=255)
			{
				sprintf(lcd_buff,"\001\x0C\004\020\001\x80\004\020Kanal:01234567\004\020\001\x0F\004\020",(kanal-1)+7+0x80);
				lcd_buff_full=1;
				key=0;
			}
		}
		break;
	case 1:
		break;
	case 2:
		sprintf(lcd_buff,"\001\x0C\004\020\001\xC0\004\020%d \001%c\004\020\001\x0D\004\020",ADCH, 0x80+(kanal-1)+7);
		lcd_buff_full=1;
		break;
	}
}
