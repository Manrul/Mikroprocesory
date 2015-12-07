/*
 * main.h
 *
 *  Created on: 1 gru 2015
 *      Author: Michał
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <avr/io.h>					// zawiera definicje WE/WY uK.(np.drukujace)
#include <inttypes.h>				// zdeklarowane typy zmiennych
#include <avr/interrupt.h>			// zdeklarowane nazwy przerwan
#include <avr/pgmspace.h>			// informacje nt. danego mikrokontrolera (inf. o pamieci)
#include <stdlib.h>					// standardowa biblioteka
#include <avr/sfr_defs.h>			// definicje rejestrow specjalnych (porty,przetwroniki itd)
#include <util/delay_basic.h>		// opóźnienia (gotowe)
#include <util/delay.h>

//zmienna okreslajaca wartosc maksymalna licznika pwm
#define TOP 512
//próg czułości wykrywania lini
#define czulosc 150
//parametry regulatora pd
#define Kp 1
#define Kd 0



/*inicjalizacja wejsc czujnikow,
 * guzika, wyjsc diod
 * timera do odczytu danych i aktualizacji pwm w zadanym odstepie czasu
 * timera to generacji sygnału pwm
 * opcjonalnie  przerwanie od sygnalu wejsciowego
 */
void init(void);
/*funkcja odczytująca stan wejsc odpowiadajacych za czujniki
 * zapisujaca wszystko do odpowiedniej zmiennej
 */
int8_t odczyt_czujnikow(void);

/*regulator PD(
 * odpowiadajacy za wysterowanie pwm, na podstawie
 * odczytow z czujnikow
 */
void regulator_pd(void);





#endif /* MAIN_H_ */
