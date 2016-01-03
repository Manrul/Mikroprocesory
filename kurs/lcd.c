/*
 * lcd.c
 *
 *  Created on: 3 sty 2016
 *      Author: Michał
 */
#include "lcd.h"


void lcd_write(unsigned char d, unsigned char rs)		//funkcja pisząca do lcd (komenda lub dana)
{
	lcd_rs=rs;
	lcd_e=1;
	lcd_data=d>>4;			//najpierw część starsza
	lcd_e=0;				//zezwolenie na zapis
	lcd_e=1;
	lcd_data=d;				//część młodsza (kopiuje 4 młodsze bity)
	lcd_e=0;				//zezwolenie na zapis
}

void lcd_write_instruction(unsigned char d)
{
	lcd_write(d,0);
}

void lcd_write_data(unsigned char d)
{
	lcd_write(d,1);
}


