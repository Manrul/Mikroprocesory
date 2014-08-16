#include <avr/eeprom.h>

EEMEM int a=100;//Zapisuje zmienną typu Int do eeprom
				//Ważne żeby odrazu przypisać wartość
				
	//Funkcje służące do odczytu pamięci eeprom
	//odczyt bloku pamięci
	eeprom_read_block(void * miejsce przeznaczenia,const void *adres_w_eeprom,size_t liczba_bitów) ;
	eeprom_read_typ(const typ *adres)
	
	/* gdzie typ to jeden z:
	byte-1 bajt
	word- 2 bajty
	dword-typy long
	float
	np:*/
	EEMEM int x=1234;
	int a=eeprom_read_word(&x);
	
	
	
	//Zapis eeprom
	 //odczytanie bloku pamięci
	eeprom_write_block(const void * źródło,const void *adres_w_eeprom,size_t liczba_bitów)
	//lub
	
	eeprom_write_typ(typ *zmienna_w_eeprom,typ dane)
	
	//gdzie typ ma znaczenie identyczne jak poprzednio
	//przykłady
	
	eeprom_write_word(&x,a)
	
	eeprom_write_block(&punkt,&ptk,sizeof(punkt))
	//gdzie punkt jest zmienna nalezącą do pewnej struktury danych
	
	
	
//Modyfikacja w pamięci eeprom(typ znaczenie jak wcześniej)
void eeprom_update_typ(typ *zmienna_w_eeprom,typ dane)
void eeprom_update_block(const void *źródło,void * adres_w_eeprom,sizeof ilość)

//Inne przydatne funckje
eeprom_is_ready()//zwraca tru gdy eeprom nie jest zapisywana aktualniee
eeprom_busy_wait()//zatrzymuje działanie programu na czas zapisu pamięci eeprom
