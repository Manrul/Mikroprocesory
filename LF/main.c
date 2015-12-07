/*
 * main.c
 *
 *  Created on: 28 lis 2015
 *      Author: Michał
 */
#include "main.h"

int main()
{
	DDRC&=~(1<<PC0);
	PORTC|=(1<<PC0);

	//zatrzymanie programu do wcisniecia klawisza
	while(PINC & 0x01);
	init();
	while(1)
	{
	}
	return 0;
}
ISR(TIMER0_COMP_vect)
{
	/*przerwanie co 1ms
	 * wywołanie regulatora co 5ms
	 */

	static uint8_t licznik=0;
	licznik++;
	if(licznik>=5)
	{
		licznik=0;
		regulator_pd();
	}
}
