/*
 * chod.c
 *
 *  Created on: 28 gru 2016
 *      Author: Michał
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"

/* algorytm chodu
 * tylnia przednia, przesów
 * drugi pok tak samo
 * tylnie przednia przesow
 * itd
 */

extern volatile quadrupted robot;
extern volatile uint8_t licznik_zapis;
extern volatile uint8_t licznik_odczyt;
extern volatile ruch bufor[max_buff+1];

void noga1(void){

	ruch buf_noga1[5];
	uint8_t i;

	buf_noga1[0].delay=150;
	buf_noga1[0].position=granica_medium+6;
	buf_noga1[0].state=leg_1;
	buf_noga1[0].joint=1;

	buf_noga1[1].delay=150;
	buf_noga1[1].position=granica_medium-2;
	buf_noga1[1].state=leg_1;
	buf_noga1[1].joint=2;

	buf_noga1[2].delay=150;
	buf_noga1[2].position=granica_medium-krok-2;
	buf_noga1[2].state=leg_1;
	buf_noga1[2].joint=0;

	buf_noga1[3].delay=150;
	buf_noga1[3].position=granica_medium+pozycja-2;
	buf_noga1[3].state=leg_1;
	buf_noga1[3].joint=2;

	buf_noga1[4].delay=200;
	buf_noga1[4].position=granica_medium+pozycja-1;
	buf_noga1[4].state=leg_1;
	buf_noga1[4].joint=1;
	for(i=0;i<=4;i++){
		while(!przesunwskzapisu());
		bufor[licznik_zapis]=buf_noga1[i];
	}

}

void noga2(void){
	ruch buf_noga2[5];
	uint8_t i;

	buf_noga2[0].delay=150;
	buf_noga2[0].position=granica_medium-6;
	buf_noga2[0].state=leg_2;
	buf_noga2[0].joint=1;

	buf_noga2[1].delay=150;
	buf_noga2[1].position=granica_medium+2;
	buf_noga2[1].state=leg_2;
	buf_noga2[1].joint=2;

	buf_noga2[2].delay=150;
	buf_noga2[2].position=granica_medium;
	buf_noga2[2].state=leg_2;
	buf_noga2[2].joint=0;

	buf_noga2[3].delay=150;
	buf_noga2[3].position=granica_medium-pozycja;
	buf_noga2[3].state=leg_2;
	buf_noga2[3].joint=2;

	buf_noga2[4].delay=200;
	buf_noga2[4].position=granica_medium-pozycja;
	buf_noga2[4].state=leg_2;
	buf_noga2[4].joint=1;
	for(i=0;i<=4;i++){
		while(!przesunwskzapisu());
		bufor[licznik_zapis]=buf_noga2[i];
	}

}

void noga3(void){

	ruch buf_noga3[5];
	uint8_t i;

	buf_noga3[0].delay=150;
	buf_noga3[0].position=granica_medium+6;
	buf_noga3[0].state=leg_3;
	buf_noga3[0].joint=1;

	buf_noga3[1].delay=150;
	buf_noga3[1].position=granica_medium-2;
	buf_noga3[1].state=leg_3;
	buf_noga3[1].joint=2;

	buf_noga3[2].delay=150;
	buf_noga3[2].position=granica_medium;
	buf_noga3[2].state=leg_3;
	buf_noga3[2].joint=0;

	buf_noga3[3].delay=150;
	buf_noga3[3].position=granica_medium+pozycja;
	buf_noga3[3].state=leg_3;
	buf_noga3[3].joint=2;

	buf_noga3[4].delay=200;
	buf_noga3[4].position=granica_medium+pozycja;
	buf_noga3[4].state=leg_3;
	buf_noga3[4].joint=1;
	for(i=0;i<=4;i++){
		while(!przesunwskzapisu());
		bufor[licznik_zapis]=buf_noga3[i];
	}


}

void noga4(void){

	ruch buf_noga4[5];
	uint8_t i;


	buf_noga4[0].delay=150;
	buf_noga4[0].position=granica_medium-6;
	buf_noga4[0].state=leg_4;
	buf_noga4[0].joint=1;

	buf_noga4[1].delay=150;
	buf_noga4[1].position=granica_medium+2;
	buf_noga4[1].state=leg_4;
	buf_noga4[1].joint=2;

	buf_noga4[2].delay=150;
	buf_noga4[2].position=granica_medium+2+krok;
	buf_noga4[2].state=leg_4;
	buf_noga4[2].joint=0;

	buf_noga4[3].delay=150;
	buf_noga4[3].position=granica_medium-pozycja+2;
	buf_noga4[3].state=leg_4;
	buf_noga4[3].joint=2;

	buf_noga4[4].delay=200;
	buf_noga4[4].position=granica_medium-pozycja+1;
	buf_noga4[4].state=leg_4;
	buf_noga4[4].joint=1;
	for(i=0;i<=4;i++){
		while(!przesunwskzapisu());
		bufor[licznik_zapis]=buf_noga4[i];
	}
}

void przesuw1(void){

	ruch buf_move[12];
	uint8_t i;

	buf_move[0].delay=0;
	buf_move[0].position=krok;
	buf_move[0].state=leg_1;
	buf_move[0].joint=0;
	buf_move[1].delay=0;
	buf_move[1].position=krok;
	buf_move[1].state=leg_2;
	buf_move[1].joint=0;
	buf_move[2].delay=0;
	buf_move[2].position=-krok;
	buf_move[2].state=leg_3;
	buf_move[2].joint=0;
	buf_move[3].delay=0;
	buf_move[3].position=-krok;
	buf_move[3].state=leg_4;
	buf_move[3].joint=0;

	buf_move[4].delay=0;
	buf_move[4].position=granica_medium-pozycja;
	buf_move[4].state=leg_4;
	buf_move[4].joint=2;
	buf_move[5].delay=0;
	buf_move[5].position=granica_medium-pozycja;
	buf_move[5].state=leg_4;
	buf_move[5].joint=1;
	buf_move[6].delay=0;
	buf_move[6].position=granica_medium+pozycja;
	buf_move[6].state=leg_1;
	buf_move[6].joint=2;
	buf_move[7].delay=0;
	buf_move[7].position=granica_medium+pozycja;
	buf_move[7].state=leg_1;
	buf_move[7].joint=1;

	buf_move[8].delay=0;
	buf_move[8].position=-1;
	buf_move[8].state=leg_3;
	buf_move[8].joint=1;
	buf_move[9].delay=0;
	buf_move[9].position=-2;
	buf_move[9].state=leg_3;
	buf_move[9].joint=2;
	buf_move[10].delay=0;
	buf_move[10].position=+1;
	buf_move[10].state=leg_2;
	buf_move[10].joint=1;
	buf_move[11].delay=250;
	buf_move[11].position=+2;
	buf_move[11].state=leg_2;
	buf_move[11].joint=2;
	for(i=0;i<=11;i++){
		while(!przesunwskzapisu());
		bufor[licznik_zapis]=buf_move[i];
	}

}

void struct_init(int init){

			robot.leg3[0]=init;
			robot.leg3[1]=init;
			robot.leg3[2]=init;
			robot.leg4[0]=init;
			robot.leg4[1]=init;
			robot.leg4[2]=init;
			robot.leg2[0]=init;
			robot.leg2[1]=init;
			robot.leg2[2]=init;
			robot.leg1[0]=init;
			robot.leg1[1]=init;
			robot.leg1[2]=init;
}


_Bool przesunwskzapisu(void){
	/*zwraca 0 gdy nie udało sie przesunac
		 * 1 gdy  przesunieto
		 */
	_Bool flaga=1;

	if(licznik_zapis<max_buff){
			if(licznik_zapis>=licznik_odczyt){
				licznik_zapis++;
			}
			else{
				if(licznik_zapis+1<licznik_odczyt)
					licznik_zapis++;
				else
					flaga=0;
				}
			}
			else{
				if(licznik_odczyt!=0)
					licznik_zapis=0;
				else
					flaga=0;
				}


	return flaga;
}

_Bool przesunwskodczytu(void){
	/*zwraca 0 gdy nie udało sie przesunac
	 * 1 gdy  przesunieto
	 */
	_Bool flaga=1;
	if(licznik_odczyt<max_buff){
		if(licznik_zapis<licznik_odczyt){
			licznik_odczyt++;
				}
		else{
			if(licznik_odczyt+1<=licznik_zapis)
				licznik_odczyt++;
			else
				flaga=0;
				}
	}
	else{
		if(licznik_zapis!=0)
			licznik_odczyt=0;
		else
			flaga=0;
	}
	return flaga;
}
