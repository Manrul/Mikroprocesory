/*Inicjalizacja Timera, w trybie normalnym
preskaler ustawiony na 8
generuje przerwanie do przepełnieniu rejestru*/


inline void InicTimer0()
{
  TCCR0 = (1<<CS01);
	TIMSK = TIMSK | (1<<TOIE0); 
}
