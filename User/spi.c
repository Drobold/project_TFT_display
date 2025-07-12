#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

void SPI1_Init(void) {
	/*
	��������� SPI ����������
	*/
    SPI_InitTypeDef SPI_InitStruct;
	
		//�������� ������������ ������������� ���������� SPI1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
		//��������� ����������� �������� ������
    SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	
		//������ ���������� ������� �����������
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	
		//������������� ������ ������������ ������
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	
		//������������� ���������� ��������� ������� (SCK)
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	
		//������������� ���� ��������� ������� (SCK)
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	
		//������������� ���������� �������� NSS (Slave Select)
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
		
		//������������� ��������� (��������) ��� �������� �������� ������ SPI
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    
		//����������� �������� �� �������� ����(Most Significant Bit)
		SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    
		//������������� ������� ��� ���������� CRC
		SPI_InitStruct.SPI_CRCPolynomial = 7;
		
		//������������� ����������
    SPI_Init(SPI1, &SPI_InitStruct);
		
		//�������� ������ SPI1
    SPI_Cmd(SPI1, ENABLE);
}