/*
 * main.c
 *
 *  Created on: 11 sty 2016
 *      Author: Michał
 */

#include "main.h"


volatile uint8_t serwo=prosto;//pozycja srodkowa?zakres od 3-23?
uint8_t tab[5]={0,0,0,0,0};
uint8_t dir[5]={skos_l,prosto,skos_p,lewo,prawo};

int main(void){
	start();
	while(guzik);
	PORTD|=(1<<PD1);
	_delay_ms(500);
	regulator();
	return 0;
}
ISR(TIMER2_COMP_vect){
	static uint8_t licznik=0;
	if(licznik==serwo)
		PORTD&=~(1<<PD7);
	if(licznik<199){
		licznik++;
		PORTD|=(1<<PD7);
	}
	else
		licznik=0;
}
void init_pin(void){
	DDRD|=(1<<PD1)|(1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD6)|(1<<PD7);
	DDRD&=~(1<<PD0);
	PORTD|=(1<<PD0);
}
void init_adc(void){
	ADMUX|=(1<<REFS0)|(1<ADLAR);
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}
void init_timer0(void){
	 TCCR0|=(1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS00);
	 OCR0=predkosc;
}
void init_timer1(void){
	 TCCR1A |=(1<<COM1A1)|(1<<WGM10);
	 TCCR1B |=(1<<WGM12)|(1<<CS10);
	 OCR1A=predkosc;
}
void init_timer2(void){
	 TCCR2|=(1<<WGM21)|(1<<CS21);
	 OCR2=100;
	 TIMSK|=(1<< OCIE2);
}
void start(void){
	init_pin();
	init_adc();
	init_timer0();
	init_timer1();
	init_timer2();
}
void sl_przod(void){
	PORTD|=(1<<PD6);
	PORTD&=~(1<<PD4);
}
void sl_tyl(void){
	PORTD|=(1<<PD4);
	PORTD&=~(1<<PD6);

}
void sl_stop(void){
	PORTD&=~(1<<PD6)|(1<<PD4);
}
void sp_przod(void){
	PORTD|=(1<<PD3);
	PORTD&=~(1<<PD2);
}
void sp_tyl(void){
	PORTD|=(1<<PD2);
	PORTD&=~(1<<PD3);

}
void sp_stop(void){
	PORTD&=~(1<<PD2)|(1<<PD3);
}
void pomiar(uint8_t i){
		ADCSRA|=(1<<ADSC);//włączenie pomiaru
		while(ADCSRA & (1<<ADSC)) {};//czekanie na koniec pomiaru
		tab[i]=ADCH;
}
void regulator(void){
	uint8_t i;
	while(1){
		sl_przod();
		sp_przod();
		for(i=0;i<3;i++){
			serwo=dir[i];
			_delay_ms(6);
			pomiar(i);
		}
		if(tab[0]>poziom||tab[1]>poziom||tab[2]>poziom){
			sp_stop();
			sl_stop();
			przeszkoda();
		}
	}
}
void przeszkoda(void){
	serwo=dir[3];
	_delay_ms(6);
	pomiar(3);
	serwo=dir[4];
	_delay_ms(6);
	pomiar(4);
	if(tab[3]<poziom)
		omin_lewo();
	else if(tab[4]<poziom)
		omin_prawo();
	else
		omin_uciekaj();
}
void omin_lewo(void){
	sp_przod();
	sl_tyl();
	serwo=dir[2];
	do{
		pomiar(2);
		_delay_ms(6);
	}
	while(tab[2]<poziom);
	sp_stop();
	sl_stop();
}
void omin_prawo(void){
	sl_przod();
	sp_tyl();
	serwo=dir[2];
	do {
		pomiar(2);
		_delay_ms(6);
	}
	while(tab[2]<poziom);
	sp_stop();
	sl_stop();
}
void omin_uciekaj(void){
	sl_tyl();
	sp_tyl();
	serwo=dir[2];
	_delay_ms(200);
	sp_stop();
	sl_stop();
	_delay_ms(20);
	sl_przod();
	sp_tyl();
	do {
		pomiar(2);
		_delay_ms(6);
	}
	while(tab[2]<poziom);
	sp_stop();
	sl_stop();
}
