#ifndef ST7735S_H
#define ST7735S_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "All_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "st7735s.h"
#include "delay.h"

void SendData(uint8_t data);
void SendCommand(uint8_t data);
void ST7735_Init(void);
void range_y(int value1, int value2);
void range_x(int value1, int value2);
void rotate_range_x(int value1, int value2);
void rotate_range_y(int value1, int value2);
void Screen(uint16_t color, int x, int y);
#endif

