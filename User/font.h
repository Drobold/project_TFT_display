#ifndef FONT_H
#define FONT_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "all_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "st7735s.h"
#include "delay.h"


//ײטפנû
void ZERO(uint16_t font_color, uint16_t back_color);
void ONE(uint16_t font_color, uint16_t back_color);
void TWO(uint16_t font_color, uint16_t back_color);
void THREE(uint16_t font_color, uint16_t back_color);
void FOR(uint16_t font_color, uint16_t back_color);
void FIVE(uint16_t font_color, uint16_t back_color);
void SIX(uint16_t font_color, uint16_t back_color);
void SEVEN(uint16_t font_color, uint16_t back_color);
void EIGHT(uint16_t font_color, uint16_t back_color);
void NINE(uint16_t font_color, uint16_t back_color);

void TEST_THREE(uint16_t font_color, uint16_t back_color);
void display_print(uint16_t font_collor, char number[]);

#endif

