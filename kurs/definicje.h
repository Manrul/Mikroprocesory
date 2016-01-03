/*
 * definicje.h
 *
 *  Created on: 3 sty 2016
 *      Author: Michał
 */

#ifndef DEFINICJE_H_
#define DEFINICJE_H_

struct diody_2
{
	volatile unsigned char d0:2;
	volatile unsigned char d1:3;
	volatile unsigned char d2:3;
};
#define diody_20 (((struct diody_2*)&PORTC)->d0)
#define diody_21 (((struct diody_2*)&PORTC)->d1)
#define diody_22 (((struct diody_2*)&PORTC)->d2)
#define diody_20dir (((struct diody_2*)&DDRC)->d0)
#define diody_21dir (((struct diody_2*)&DDRC)->d1)
#define diody_22dir (((struct diody_2*)&DDRC)->d2)

struct key_struct
{
	volatile unsigned char k:4;
};
#define keyh				(((struct key_struct*)&PIND)->k)
#define keyh_dir			(((struct key_struct*)&DDRD)->k)
#define keyh_port			(((struct key_struct*)&PORTD)->k)

struct ledy
{
	volatile unsigned char d:8;
};
#define led			(((struct ledy*)&PORTC)->d)
#define led_dir		((*((struct ledy*)&DDRC)).d)

//deklaracje funkcji
void M0bf(char);
void M0af(char);

struct menu
{
	struct menu *left;
	struct menu *right;
	struct menu *up;
	struct menu *down;

	char *str;

	void (*function)(char);
	unsigned short int period;

};
struct menu M0,M1,M2,M0a,M0b,M1a,M1b,M1c,M2a,M2b;
struct menu M0={&M2,&M1,NULL,&M0a,"M0",NULL,0};
struct menu M1={&M0,&M2,NULL,&M1a,"M1",NULL,0};
struct menu M2={&M1,&M0,NULL,&M2a,"M2",NULL,0};

struct menu M0a={&M0b,&M0b,&M0,NULL,"M0a",&M0af,10000};
struct menu M0b={&M0a,&M0a,&M0,NULL,"ADC",&M0bf,1000};

struct menu M1a={&M1c,&M1b,&M1,NULL,"M1a",NULL,0};
struct menu M1b={&M1a,&M1c,&M1,NULL,"M1b",NULL,0};
struct menu M1c={&M1b,&M1a,&M1,NULL,"M1c",NULL,0};

struct menu M2a={&M2b,&M2b,&M2,NULL,"M2a",NULL,0};
struct menu M2b={&M2a,&M2a,&M2,NULL,"M2b",NULL,0};


#endif /* DEFINICJE_H_ */
