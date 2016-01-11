/*
 * main.h
 *
 *  Created on: 11 sty 2016
 *      Author: Michał
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define guzik (PIND & 0x01)

#define prosto 13		//czujnik "patrzy" prosto
#define lewo  22		//czujnik "patrzy w lewo
#define prawo 4			//czujnik "patrzy" w prawo
#define skos_l 18		//czujnik "patrzy" lekkow w lewo
#define skos_p 8		//czujnik "patrzy" lekko w prawo
#define predkosc 150	 //predkosc jazdy
#define poziom 200  	//prog wykrywania przeszkody
#define czas_pomiaru 6	//czas na ustabilizowanie sie pomiaru
#define uciekaj 300		//jak dlugo ma sie cofac


void start(void);
void init_pin(void);
void init_adc(void);
void init_timer0(void);
void init_timer1(void);
void init_timer2(void);
void sl_przod(void);
void sl_tyl(void);
void sl_stop(void);
void sp_przod(void);
void sp_tyl(void);
void sp_stop(void);
void pomiar(uint8_t);
void regulator(void);
void przeszkoda(void);
void omin_lewo(void);
void omin_prawo(void);
void omin_uciekaj(void);

#endif /* MAIN_H_ */
