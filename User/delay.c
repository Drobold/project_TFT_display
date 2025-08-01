#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"


/**
 * @brief Задержка
 * 
 * @param x - время в микросекундах
 */
void delay(int x) {
	for (int i = 0; i < x; i++) {
	}
}