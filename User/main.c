#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "all_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "st7735s.h"
#include "delay.h"
#include "font.h"


/*Число пикселей на экране относительно осей экрана,
установленных разрабочиком.
В зависимости от ориентировки - поменять местами*/
int pixels_horizontal = 80;
int pixels_vertical = 160;


/*Число смещенных пикселей до координаты (1;1) относительно осей экрана,
установленных разрабочиком. (Относительно стандартной системы координат - смещение
по оси y)
Менять местами не нужно, учтено в доп. функциях*/
int pixels_dislocation_x = 25;
int pixels_dislocation_y = 0;


uint16_t collor_mass[9] = {YELLOW, WHITE, BLACK, VIOLET, BLUE, LIGHT_BLUE, ORANGE, RED, GREEN};



int main(void) {
		//Основные фцункции
    SPI1_Init(); 
    GPIO_Init_Custom(); 
		ST7735_Init();
		rotate_Screen(BLACK, pixels_vertical, pixels_horizontal);
	

	
	  //rotate_Screen(WHITE, 160, 80);
    display_print(LIGHT_BLUE,"11111111");

		while(1);

}



