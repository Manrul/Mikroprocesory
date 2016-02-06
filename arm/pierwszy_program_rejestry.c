
#include "stm32f407xx.h"


int main(void){
	volatile uint32_t delay;

	//zegar portu d
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;

	GPIOD->MODER|=GPIO_MODER_MODER12_0|GPIO_MODER_MODER13_0|GPIO_MODER_MODER14_0|GPIO_MODER_MODER15_0;
	GPIOD->BSRR=GPIO_BSRR_BS_12|GPIO_BSRR_BS_15;
	while(1){
		GPIOD->BSRR=GPIO_BSRR_BS_12|GPIO_BSRR_BR_15;
		for(delay = 1000000; delay; delay--){};
		GPIOD->BSRR=GPIO_BSRR_BS_13|GPIO_BSRR_BR_12;
		for(delay = 1000000; delay; delay--){};
		GPIOD->BSRR=GPIO_BSRR_BS_14|GPIO_BSRR_BR_13;
		for(delay = 1000000; delay; delay--){};
		GPIOD->BSRR=GPIO_BSRR_BS_15|GPIO_BSRR_BR_14;
		for(delay = 1000000; delay; delay--){};
		}
	return 0;
}


