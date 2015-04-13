#include "stm32f4xx_flash.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <misc.h>

void RCC_Config(void){
	ErrorStatus HSEStartUpStatus;

	RCC_DeInit();				// Reset ustawień RCC
	RCC_HSEConfig(RCC_HSE_ON);	// Włącz HSE
	HSEStartUpStatus = RCC_WaitForHSEStartUp();		// Czekaj aż zegar HSE będzie gotowy

	if(HSEStartUpStatus == SUCCESS){
		FLASH_PrefetchBufferCmd(ENABLE);
		FLASH_SetLatency(FLASH_Latency_7);			// Opóżnienie dostępu do pamięci flash (>48Mhz = 2)
		RCC_HCLKConfig(RCC_SYSCLK_Div1);			// Sygnał dla rdzenia
		RCC_PCLK2Config(RCC_HCLK_Div1);				// Sygnal dla magistrali APB2 (max 72MHz)
		RCC_PCLK1Config(RCC_HCLK_Div2);				// Sygnał dla magistrali APB1 (max 36MHz)

		//RCC_PLLConfig(RCC_PLLSource_HSE, 8, 288, 4, 6);	// PLL for sysclk = 72MHz, usb = 48MHz
		RCC_PLLConfig(RCC_PLLSource_HSE,8,336,2,7);
		RCC_PLLCmd(ENABLE);									// Włącz PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);	// Czekaj za PLL

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);			// SYSCLK = PLL

		while(RCC_GetSYSCLKSource() != 0x08);				// Czekaj za SYSCLK
	}
}
