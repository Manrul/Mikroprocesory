#include <misc.h>
volatile  uint32_t opoznienie=0;
void Przerwanie(void)
{
	if (SysTick_Config(SystemCoreClock / 1000))
	    	{
	    		while (1); //W przypadku błędu program zawiesi się w pętli nieskończonej
	    	}
}
void SysTick_Handler(void)
{
opoznienie++;

}
