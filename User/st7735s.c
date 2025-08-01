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
 * @brief ���� �������� ������ �� �������
 */
void SendCommand(uint8_t cmd) {
	
	// ������ ��� CS ������, ����� ������������ �������
	GPIO_ResetBits(GPIOA, GPIO_Pin_CS);
	// ������������� ��� DC � ��������� "�������" (DC = 0)
	GPIO_ResetBits(GPIOA, GPIO_Pin_DC);
	
	// ���������� ������ ����� SPI
	SPI_I2S_SendData(SPI1, cmd);
	
	// ������� ���������� �������� ������
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	// ������ ��� CS �������, ����� ��������� ��������
	GPIO_SetBits(GPIOA, GPIO_Pin_CS);
}


/**
 * @brief ���� �������� ������ �� �������
 */
void SendData(uint8_t data) {

	// ������ ��� CS ������, ����� ������������ �������
	GPIO_ResetBits(GPIOA, GPIO_Pin_CS);
	// ������������� ��� DC � ��������� "������" (DC = 1)
	GPIO_SetBits(GPIOA, GPIO_Pin_DC);
	
	// ���������� ������ ����� SPI
	SPI_I2S_SendData(SPI1, data);
	
	// ������� ���������� �������� ������
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	// ������ ��� CS �������, ����� ��������� ��������
	GPIO_SetBits(GPIOA, GPIO_Pin_CS);
}


/**
 * @brief ������������� �������
 */
void ST7735_Init(void) {
	
    // ����� �������
    GPIO_ResetBits(GPIOA, GPIO_Pin_RES);
    delay(1000);
    GPIO_SetBits(GPIOA, GPIO_Pin_RES);
    delay(1000);
	
		GPIO_SetBits(GPIOA, GPIO_Pin_BLK);//��������� ������
		delay(1000);
	
    // ����� �� ������� ������
    SendCommand(0x11); // ����� �� ������� ������
    delay(1000);

    // ��������� ������� ����� (RGB565, 16 ���)
    SendCommand(0b00111010); // COLMOD: Pixel Format Set
    SendData(0b00000101);    // 16 ���/�������

    // ��������� �������
    SendCommand(0x29); // Display ON
    delay(1000);
}


/**
 * @brief ��������� ���������� ������ �� ��� X
 *
 * ������� ���������� 16-������ ����� ���� ��������. �������
���� �� �������� ������ � ������������ ����, ������ ������������
������� ����.
 *
 * @param value1 - ������ �� Y
 * @param value2 - ����� �� Y
 */
void range_y(int value1, int value2) {

	SendCommand(0x2B); // ��������� �������
	SendData(0); SendData(value1+pixels_dislocation_y); //[16 ���]
	SendData(0); SendData(value2+pixels_dislocation_y); //[16 ���]
}


/**
 * @brief ��������� ���������� ������ �� ��� X
 *
 * ������� ���������� 16-������ ����� ���� ��������. �������
���� �� �������� ������ � ������������ ����, ������ ������������
������� ����.
 * 26 - �������� ������������ ��������� ������������ �������� �� ������ �� ��� X
1 - ���� �� �����
 *
 * @param value1 - ������ �� X
 * @param value2 - ����� �� X
 */
void range_x(int value1, int value2) {

	SendCommand(0x2A); // ��������� ������
	SendData(0); SendData(value1+pixels_dislocation_x); //[16 ���]
	SendData(0); SendData(value2+pixels_dislocation_x); //[16 ���]
}


/**
 * @brief ��������� ���������� �� ����� ��� X
 *
 * ������� ������������ ����������� �� 90 ��������.
��� X � Y �������� �������
 *
 * @param value1 - ������ �� ����� X
 * @param value2 - ����� �� ����� X
 */
void rotate_range_x(int value1, int value2) {

	SendCommand(0x2B); // ��������� �������
	SendData(0); SendData(value1+pixels_dislocation_y); //[16 ���]
	SendData(0); SendData(value2+pixels_dislocation_y); //[16 ���]
}


/**
 * @brief ��������� ���������� �� ����� ��� Y
 *
 * ������� ������������ ����������� �� 90 ��������.
��� X � Y �������� �������
26 - �������� ������������ ��������� ������������ �������� �� ������
1 - ���� �� �����
 *
 * @param value1 - ������ �� ����� Y
 * @param value2 - ����� �� ����� Y
 */
void rotate_range_y(int value1, int value2) {

	SendCommand(0x2A);
	SendData(0); SendData(value1+pixels_dislocation_x); //[16 ���]
	SendData(0); SendData(value2+pixels_dislocation_x); //[16 ���]
}



/**
 * @brief ��������� ���� ����� ����� ������
 *
 * x � y - ������ �������� ��������
������������ ��� ������, ��������������� ������������
 *
 * @param color - ���� ������
 * @param x - ����� �������� �� ��� X
 * @param y - ����� �������� �� ��� Y
 */
void Screen(uint16_t color, int x, int y) {
	
	//��������� �����
	SendCommand(0x28);
	
	range_x(1, x);
	range_y(1, y);
	
	// ������ ������ ��������
  SendCommand(0x2C);
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			SendData(color >> 8);  // ��������� ������� ���� �����
      SendData(color & 0xFF); // ��������� ������� ���� �����
		}
	}
	//�������� �����
	SendCommand(0x29);
}


/**
 * @brief ��������� ���� ����� ����� ������
 *
 * x � y - ������ �������� ��������
������������ ������������ ��� ������
 *
 * @param color - ���� ������
 * @param x - ����� �������� �� ��� X
 * @param y - ����� �������� �� ��� Y
 */
void rotate_Screen(uint16_t color, int x, int y) {
	
	//��������� �����
	SendCommand(0x28);
	
	rotate_range_x(1, x);
	rotate_range_y(1, y);
	
	// ������ ������ ��������
  SendCommand(0x2C);
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			SendData(color >> 8);  // ��������� ������� ���� �����
      SendData(color & 0xFF); // ��������� ������� ���� �����
		}
	}
	//�������� �����
	SendCommand(0x29);
}


