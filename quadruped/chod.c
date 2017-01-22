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
#include "inv.h"

/* algorytm chodu
 * tylnia przednia, przesów
 * drugi pok tak samo
 * tylnie przednia przesow
 * itd
 */
extern quadrupted actual_position;

void noga(enum maszyna_stanu state,int8_t x,int8_t y, int8_t z, uint16_t delay){
	int8_t  i;
	int8_t act_pos=0;

	switch(state){
		case leg_1:{
			act_pos=actual_position.leg1[0];
			actual_position.leg1[0]=x;
			actual_position.leg1[1]=y;
			actual_position.leg1[2]=z;
			break;
			}
		case leg_2:{
			act_pos=actual_position.leg2[0];
			actual_position.leg2[0]=x;
			actual_position.leg2[1]=y;
			actual_position.leg2[2]=z;
			break;
			}
		case leg_3:{
			act_pos=actual_position.leg3[0];
			actual_position.leg3[0]=x;
			actual_position.leg3[1]=y;
			actual_position.leg3[2]=z;
			break;
			}
		case leg_4:{
			act_pos=actual_position.leg4[0];
			actual_position.leg4[0]=x;
			actual_position.leg4[1]=y;
			actual_position.leg4[2]=z;
			break;
		}
		default:
			break;

	}

	if(x-act_pos>0){
		for(i=act_pos;i<=x;i++){
			invers(state,i,y,z+3,delay);
		}
	}
	else{
		for(i=act_pos;i>=x;i--){
			invers(state,i,y,z+3,delay);
			}
	}
			invers(state,x,y,z,delay);
}

void przesun(int8_t przesuniecie,uint16_t delay){

	int8_t i=0;

		while(i!=przesuniecie){
	invers(leg_1,actual_position.leg1[0]-i,actual_position.leg1[1],actual_position.leg1[2],0);
	invers(leg_2,actual_position.leg2[0]-i,actual_position.leg2[1],actual_position.leg2[2],0);
	invers(leg_3,actual_position.leg3[0]+i,actual_position.leg3[1],actual_position.leg3[2],0);
	invers(leg_4,actual_position.leg4[0]+i,actual_position.leg4[1],actual_position.leg4[2],delay);
		if(przesuniecie>0)
			i++;
		else
			i--;
		}
	invers(leg_1,actual_position.leg1[0]-przesuniecie,actual_position.leg1[1],actual_position.leg1[2],0);
	invers(leg_2,actual_position.leg2[0]-przesuniecie,actual_position.leg2[1],actual_position.leg2[2],0);
	invers(leg_3,actual_position.leg3[0]+przesuniecie,actual_position.leg3[1],actual_position.leg3[2],0);
	invers(leg_4,actual_position.leg4[0]+przesuniecie,actual_position.leg4[1],actual_position.leg4[2],delay);

	actual_position.leg1[0]=actual_position.leg1[0]-przesuniecie;
	actual_position.leg2[0]=actual_position.leg2[0]-przesuniecie;
	actual_position.leg3[0]=actual_position.leg3[0]+przesuniecie;
	actual_position.leg4[0]=actual_position.leg4[0]+przesuniecie;

}
