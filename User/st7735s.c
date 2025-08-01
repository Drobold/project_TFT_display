#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "all_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "delay.h"

extern int pixels_vertical;
extern int pixels_horizontal;

extern int pixels_dislocation_x;
extern int pixels_dislocation_y;


/**
 * @brief Блок отправки команд на дисплей
 */
void SendCommand(uint8_t cmd) {
	
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


/**
 * @brief Блок отправки данных на дисплей
 */
void SendData(uint8_t data) {

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


/**
 * @brief Инициализация дисплея
 */
void ST7735_Init(void) {
	
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


/**
 * @brief Установка диаппазона строки по оси X
 *
 * Функция отправляет 16-битный адрес двух пикселей. Старший
байт не содержит адреса и отправляется ноль, следом отправляется
младший байт.
 *
 * @param value1 - Начало по Y
 * @param value2 - Конец по Y
 */
void range_y(int value1, int value2) {

	SendCommand(0x2B); // Установка столбца
	SendData(0); SendData(value1+pixels_dislocation_y); //[16 бит]
	SendData(0); SendData(value2+pixels_dislocation_y); //[16 бит]
}


/**
 * @brief Установка диаппазона строки по оси X
 *
 * Функция отправляет 16-битный адрес двух пикселей. Старший
байт не содержит адреса и отправляется ноль, следом отправляется
младший байт.
 * 26 - смещение относительно реального расположения пикселей на экране по оси X
1 - пока не помню
 *
 * @param value1 - Начало по X
 * @param value2 - Конец по X
 */
void range_x(int value1, int value2) {

	SendCommand(0x2A); // Установка строки
	SendData(0); SendData(value1+pixels_dislocation_x); //[16 бит]
	SendData(0); SendData(value2+pixels_dislocation_x); //[16 бит]
}


/**
 * @brief Установка диаппазона по новой оси X
 *
 * функция поворачивает изображение на 90 градусов.
Оси X и Y меняются местами
 *
 * @param value1 - Начало по новой X
 * @param value2 - Конец по новой X
 */
void rotate_range_x(int value1, int value2) {

	SendCommand(0x2B); // Установка столбца
	SendData(0); SendData(value1+pixels_dislocation_y); //[16 бит]
	SendData(0); SendData(value2+pixels_dislocation_y); //[16 бит]
}


/**
 * @brief Установка диаппазона по новой оси Y
 *
 * функция поворачивает изображение на 90 градусов.
Оси X и Y меняются местами
26 - смещение относительно реального расположения пикселей на экране
1 - пока не помню
 *
 * @param value1 - Начало по новой Y
 * @param value2 - Конец по новой Y
 */
void rotate_range_y(int value1, int value2) {

	SendCommand(0x2A);
	SendData(0); SendData(value1+pixels_dislocation_x); //[16 бит]
	SendData(0); SendData(value2+pixels_dislocation_x); //[16 бит]
}



/**
 * @brief Заполняет весь экран одним цветом
 *
 * x и y - номера конечных пикселей
Используются оси экрана, предусмотренные разрабочиком
 *
 * @param color - цвет экрана
 * @param x - число пикселей по оси X
 * @param y - число пикселей по оси Y
 */
void Screen(uint16_t color, int x, int y) {
	
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


/**
 * @brief Заполняет весь экран одним цветом
 *
 * x и y - номера конечных пикселей
Используются перевернутые оси экрана
 *
 * @param color - цвет экрана
 * @param x - число пикселей по оси X
 * @param y - число пикселей по оси Y
 */
void rotate_Screen(uint16_t color, int x, int y) {
	
	//Отключить экран
	SendCommand(0x28);
	
	rotate_range_x(1, x);
	rotate_range_y(1, y);
	
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


