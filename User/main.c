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


/*����� �������� �� ������ ������������ ���� ������,
������������� ������������.
� ����������� �� ������������ - �������� �������*/
int pixels_horizontal = 80;
int pixels_vertical = 160;


/*����� ��������� �������� �� ���������� (1;1) ������������ ���� ������,
������������� ������������. (������������ ����������� ������� ��������� - ��������
�� ��� y)
������ ������� �� �����, ������ � ���. ��������*/
int pixels_dislocation_x = 25;
int pixels_dislocation_y = 0;


uint16_t collor_mass[9] = {YELLOW, WHITE, BLACK, VIOLET, BLUE, LIGHT_BLUE, ORANGE, RED, GREEN};



int main(void) {
		//�������� ��������
    SPI1_Init(); 
    GPIO_Init_Custom(); 
		ST7735_Init();
		rotate_Screen(BLACK, pixels_vertical, pixels_horizontal);
	

	
	  //rotate_Screen(WHITE, 160, 80);
    display_print(LIGHT_BLUE,"11111111");

		while(1);

}



