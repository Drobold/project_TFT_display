#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "All_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "delay.h"

void SendCommand(uint8_t cmd) {
	/*
	Блок отправки команд на дисплей
	*/
	
	// Делаем пин CS низким, чтобы активировать дисплей
	GPIO_ResetBits(GPIOA, GPIO_Pin_CS);
	// Устанавливаем пин DC в состояние "команда" (DC = 0)
	GPIO_ResetBits(GPIOA, GPIO_Pin_DC);
	
	// Отправляем данные через SPI
	SPI_I2S_SendData(SPI1, cmd);
	
	// Ожидаем завершения передачи данных
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	// Делаем пин CS высоким, чтобы завершить передачу
	GPIO_SetBits(GPIOA, GPIO_Pin_CS);
}

void SendData(uint8_t data) {
	/*
	Блок отправки данных на дисплей
	*/
	
	// Делаем пин CS низким, чтобы активировать дисплей
	GPIO_ResetBits(GPIOA, GPIO_Pin_CS);
	// Устанавливаем пин DC в состояние "данные" (DC = 1)
	GPIO_SetBits(GPIOA, GPIO_Pin_DC);
	
	// Отправляем данные через SPI
	SPI_I2S_SendData(SPI1, data);
	
	// Ожидаем завершения передачи данных
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	// Делаем пин CS высоким, чтобы завершить передачу
	GPIO_SetBits(GPIOA, GPIO_Pin_CS);
}

void ST7735_Init(void) {
	/*
	Инициализация дисплея
	*/
	
    // Сброс дисплея
    GPIO_ResetBits(GPIOA, GPIO_Pin_RES);
    delay(1000);
    GPIO_SetBits(GPIOA, GPIO_Pin_RES);
    delay(1000);
	
		GPIO_SetBits(GPIOA, GPIO_Pin_BLK);//Включение экрана
		delay(1000);
	
    // Выход из спящего режима
    SendCommand(0x11); // Выход из спящего режима
    delay(1000);

    // Установка формата цвета (RGB565, 16 бит)
    SendCommand(0b00111010); // COLMOD: Pixel Format Set
    SendData(0b00000101);    // 16 бит/пиксель

    // Включение дисплея
    SendCommand(0x29); // Display ON
    delay(1000);
}

void range_y(int value1, int value2) {
		/*
	Установка диаппазона столбца по Y
		value1 - Начало по Y
		value1 - Конец по Y
	*/
	SendCommand(0x2B); // Установка столбца
	SendData(0); SendData(value1); //[16 бит]
	SendData(0); SendData(value2); //[16 бит]
}

void range_x(int value1, int value2) {
	/*
	Установка диаппазона строки по оси X
		value1 - Начало по X
		value1 - Конец по X
	*/
	SendCommand(0x2A); // Установка строки
	SendData(0); SendData(value1+26-1); //[16 бит]
	SendData(0); SendData(value2+26-1); //[16 бит]
}

void rotate_range_x(int value1, int value2) {
		/*
	Установка диаппазона по новой оси X
		value1 - Начало по новой X
		value1 - Конец по новой X
	*/
	SendCommand(0x2B); // Установка столбца
	SendData(0); SendData(value1); //[16 бит]
	SendData(0); SendData(value2); //[16 бит]
}

void rotate_range_y(int value1, int value2) {
	/*
	Установка диаппазона по новой оси Y
		value1 - Начало по новой Y
		value1 - Конец по новой Y
	*/
	SendCommand(0x2A);
	SendData(0); SendData(value1+26-1); //[16 бит]
	SendData(0); SendData(value2+26-1); //[16 бит]
}




void Screen(uint16_t color, int x, int y) {
	/*
	Заполняет весь экран одним цветом
		color - цвет экрана
		x - число пикселей по оси X
		y - число пикселей по оси Y
	*/
	
	//Отключить экран
	SendCommand(0x28);
	
	range_x(1, x);
	range_y(1, y);
	
	// Начало записи пикселей
  SendCommand(0x2C);
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			SendData(color >> 8);  // Отправить старший байт цвета
      SendData(color & 0xFF); // Отправить младший байт цвета
		}
	}
	//Включить экран
	SendCommand(0x29);
}


