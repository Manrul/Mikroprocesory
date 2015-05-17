#define N 1024			//rozmiar buforu


char Bufor[N];			//bufor
char *wsk_odczyt;		//wskaźnik odczytu
char *wsk_zapis;			//wskaźnik zapisu

void inic_wsk(void)
{
	wsk_zapis = Bufor;
	wsk_odczyt = Bufor;
}

int zapisz_bufor(char dana) //zwraca 0, gdy zapis się udał
{
	if (((wsk_zapis >= wsk_odczyt) || ((wsk_odczyt - wsk_zapis) > 1)) && (wsk_zapis-wsk_odczyt)<N-2)
	{
		*wsk_zapis = dana;
		wsk_zapis++;
		if (wsk_zapis == Bufor + N)
			wsk_zapis = Bufor;
		return 0;
	}
	else
		return 1;
}

char *odczytaj_bufor(void)//jeśli zwraca NULL, bufor jest pusty
{
	char *pom;
	if (wsk_zapis != wsk_odczyt)
	{
		pom = wsk_odczyt;
		wsk_odczyt++;
		if (wsk_odczyt == Bufor + N)
			wsk_odczyt = Bufor;
		return pom;
	}
	return NULL;
}
