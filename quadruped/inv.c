/*
 * inv.c
 *
 *  Created on: 30 gru 2016
 *      Author: Michał
 */
#include "inv.h"

extern quadrupted robot;

void invers(enum maszyna_stanu state,int x,int y, int z){
	float q1, q2, q3;
	float r,d;

	//struct leg wynik;
	q1 = atan2(y,x);

	r=sqrt(x*x+y*y);
	d=(((r-a1)*(r-a1)+(z-e1)*(z-e1)-(a2*a2)-(a3*a3))/(2*a2*a3));
	q3=atan2(-sqrt(1-d),d);

	q2=atan2(z-e1,r-a1)-atan2(a3*sin(q3),a2+a3*cos(q3));
	//q2=0;
	//q3=0;
	//q1=3.14/2;
	int pom=0;//
	int pom1=0;
	switch(state){
		case leg_1:{
			robot.leg1[0]=(int)round(q1 / 0.076 + granica_low)-2;
			robot.leg1[1]=(int)round(q2 / 0.076)+granica_medium-pom1;
			robot.leg1[2]=(int)round((-M_PI/2-q3) / 0.076)+granica_medium+pom+2;//bylo4
			break;
			}
		case leg_2:{
			robot.leg2[0]=(int)round(q1 / 0.076 + granica_low)-2;
			robot.leg2[1]=(int)round(-q2 / 0.076)+granica_medium+pom1;
			robot.leg2[2]=(int)round((M_PI/2+q3) / 0.076)+granica_medium-pom;//-1
			break;
			}
		case leg_3:{
			robot.leg3[0]=(int)round(q1 / 0.076 + granica_low)-2;
			robot.leg3[1]=(int)round(q2 / 0.076)+granica_medium-pom1;
			robot.leg3[2]=(int)round((-M_PI/2-q3) / 0.076)+granica_medium+2+pom;//bylo4
			break;
			}
		case leg_4:{
			robot.leg4[0]=(int)round(q1 / 0.076 + granica_low)-3;
			robot.leg4[1]=(int)round(-q2 / 0.076)+granica_medium+pom1;//lub-1tu nic
			robot.leg4[2]=(int)round((M_PI/2+q3) / 0.076)+granica_medium-pom;//-1
			break;
		}
		default:
			break;
	}
}


