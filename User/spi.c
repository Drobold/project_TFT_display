#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

void SPI1_Init(void) {
	/*
	Настройка SPI соединения
	*/
    SPI_InitTypeDef SPI_InitStruct;
	
		//Включает тактирование периферийного устройства SPI1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
		//Настройка направления передачи данных
    SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
	
		//Делает контроллер главным устройством
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	
		//Устанавливает размер передаваемых данных
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	
		//Устанавливает полярность тактового сигнала (SCK)
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	
		//Устанавливает фазу тактового сигнала (SCK)
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	
		//Устанавливает управление сигналом NSS (Slave Select)
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
		
		//Устанавливает прескалер (делитель) для скорости передачи данных SPI
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    
		//Настраивает передачу со старшего бита(Most Significant Bit)
		SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    
		//Устанавливает полином для вычисления CRC
		SPI_InitStruct.SPI_CRCPolynomial = 7;
		
		//Инициализация параметров
    SPI_Init(SPI1, &SPI_InitStruct);
		
		//Включает работу SPI1
    SPI_Cmd(SPI1, ENABLE);
}