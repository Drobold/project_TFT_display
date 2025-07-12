#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "All_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "st7735s.h"
#include "delay.h"
#include "font.h"

uint16_t collor_mass[9] = {YELLOW, WHITE, BLACK, VIOLET, BLUE, LIGHT_BLUE, ORANGE, RED, GREEN};



int main(void) {
		//Основные фцункции
    SPI1_Init(); 
    GPIO_Init_Custom(); 
		ST7735_Init();
		uint16_t font_color = LIGHT_BLUE;
		
		//Начальный цвет экрана
		Screen(BLACK, 80, 160);
	
    display_print("9875478");
		
		while(1);

}


