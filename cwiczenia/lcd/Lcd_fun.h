/*
 * lcd.h
 *
 *  Created on: 3 sty 2016
 *      Author: Michał
 */

#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>
void lcd_write(unsigned char, unsigned char);
void lcd_write_instruction(unsigned char);
void lcd_write_data(unsigned char);

struct lcd
{
	volatile unsigned char 		rs:1;
	volatile unsigned char 		  :1;
	volatile unsigned char 		 e:1;
	volatile unsigned char 		  :1;
	volatile unsigned char 	  data:4;
};
#define lcd_rs				(((struct lcd*)&PORTB)->rs)
#define lcd_rs_dir			(((struct lcd*)&DDRB)->rs)
#define lcd_e				(((struct lcd*)&PORTB)->e)
#define lcd_e_dir			(((struct lcd*)&DDRB)->e)
#define lcd_data			(((struct lcd*)&PORTD)->data)
#define lcd_data_dir		(((struct lcd*)&DDRD)->data)



#endif /* LCD_H_ */
