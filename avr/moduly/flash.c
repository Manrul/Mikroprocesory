//biblioteka z potrzebnymi definicjami i funkcjami

#include <avr/pgmspace.h>


const char __attribute__((__progmem__))  x[]="xxx";//przykład zapisu łańcucha znaków do pamięci flash
const char PROGMEM x1[]="xxx";
//PROGMEM jest makrem zastępującym zapis __attribute__((__progmem__))



//Funkcje odpowiadające za ODCZYT danych z pamięci flash 

pgm_read_byte(adres);//zwraca bajt danych spod podanego adresu
pgm_read_word(adres);//zwraca 2 bajty danych spod podanego adresu
pgm_read_dword(adres);//zwraca 4 bakty danych spod podanego adresu
pgm_read_float(adres);//zwraca dane o typie float spod podanego adresu


//Zapis typu złożonego  do pamięci flash

const char PROGMEM m1[]="zamknij";
const char PROGMEM m2[]="otwórz";
const char PROGMEM m3[]="wybierz";
const char * const Menu[3] PROGMEM = {m1,m2,m3};
