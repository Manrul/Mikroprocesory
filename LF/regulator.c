/*
 * regulator.c
 *
 *  Created on: 7 gru 2015
 *      Author: Michał
 */
#include "main.h"




/* funkcja odczytujaca stan czujnikow
 * poprzez multipleksowanie
 * kanałow przetwornika adc
 * zwraca uchyb wzgledem lini
 */
int8_t odczyt_czujnikow()
{
	//tablica z wagami kolejnych czujników//treba dobrac
	int8_t tab[8]={-16,-8,-4,-2,2,4,8,16};
	int8_t uchyb=0;
	uint8_t i;

	for(i=0;i<=7;i++)
	{
		ADMUX &= 0b11110000;
		ADMUX |= (i & 0b00000111);
		asm("nop");//synchronizacja
		ADCSRA|=(1<<ADSC);//włączenie pomiaru
		while(ADCSRA & (1<<ADSC)) {};//czekanie na koniec pomiaru
		if(ADCH>czulosc)//trzeba dobrac czulosc i znak <>
			uchyb+=tab[i];
	}
	return uchyb;
}


void regulator_pd(void)
{
	static int8_t uchyb_p=0;
	int8_t uchyb,regulator;
	int16_t pom_a,pom_b;
	uchyb=odczyt_czujnikow();
	regulator=Kp*uchyb+Kd*(uchyb-uchyb_p);
	uchyb_p=uchyb;
		pom_a=OCR1A-regulator;
		pom_b=OCR1B+regulator;
		if(pom_a>=TOP)
			pom_a=TOP-1;
		else if(pom_a<=0)
			pom_a=1;
		if(pom_b>=TOP-1)
			pom_b=TOP-1;
		else if(pom_b<=0)
			pom_b=1;


		OCR1A=pom_a;
		OCR1B=pom_b;
}


