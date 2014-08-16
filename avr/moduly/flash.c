#include <avr/pgmspace.h>//biblioteka z potrzebnymi definicjami i funkcjami


const char __attribute__((__progmem__))  x[]="xxx";//przykład zapisu łańcucha znaków do pamięci flash
const char PROGMEM x1[]="xxx";
//PRGMEM jest makrem zastępującym zapis __attribute__((__progmem__))



//Funkcje odpowiadające za ODCZYT danych za pamięci flash 

pgm_read_byte(adres);//zwraca bajt danych spod podanego adresu
pgm_read_word(adres);//zwraca 2 bajty
pgm_read_dword(adres);//zwraca 4 bakty
pgm_read_float(adres);//zwraca wartość  o typie float 

//Zapis tablicy do pamięci flash
const char PROGMEM m1[]="zamknij";
const char PROGMEM m2[]="otwórz";
const char PROGMEM m3[]="wybierz";

const char * const Menu[3] PROGMEM = {m1,m2,m3};
