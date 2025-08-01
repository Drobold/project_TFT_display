#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "all_definitions.h"


/**
 * @brief Настраивает основные пины дисплея
 */
void GPIO_Init_Custom(void) {

	
    GPIO_InitTypeDef GPIO_InitStruct;
	
		//Включение тактирования порта А
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
		// Настроим SPI-пины SCK(SCL) и MOSI
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_SCL | GPIO_Pin_SDA;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
    // Настроим CS, DC, RST, BLK как выходы
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_CS | GPIO_Pin_DC | GPIO_Pin_RES | GPIO_Pin_BLK;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}