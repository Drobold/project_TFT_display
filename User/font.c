#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "All_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "st7735s.h"
#include "delay.h"


//		int ШАБЛОН[12][9] = {
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0},
//		{0, 0, 0, 0, 0, 0, 0, 0, 0}
//	};



void ZERO(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

		int ZERO [12][9] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 0, 0, 1, 1, 0, 1, 1},
		{1, 1, 0, 0, 1, 1, 0, 1, 1},
		{1, 1, 0, 1, 1, 0, 0, 1, 1},
		{1, 1, 0, 1, 1, 0, 0, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 0}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (ZERO[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (ZERO[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}





void ONE(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

	int ONE[12][9] = {
		{0, 0, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 0, 0, 0}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (ONE[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (ONE[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void TWO(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

	int TWO [12][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (TWO[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (TWO[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void THREE(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

		int THREE[12][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (THREE[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (THREE[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void FOR(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

		int FOR[12][9] = {
		{1, 1, 0, 0, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (FOR[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (FOR[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}


void FIVE(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

		int FIVE[12][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (FIVE[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (FIVE[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void SIX(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	
		int SIX[12][9] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 0}
	};



	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (SIX[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (SIX[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void SEVEN(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	
		int SEVEN[12][9] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0}
	};

	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (SEVEN[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (SEVEN[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void EIGHT(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	
		int EIGHT[12][9] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 0}
	};



	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (EIGHT[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (EIGHT[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void NINE(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	
		int NINE[12][9] = {
		{0, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0}
	};

	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (NINE[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (NINE[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

void TEST_THREE(uint16_t font_color, uint16_t back_color, int *x0, int *x1, int *y0, int *y1) {
	
	rotate_range_x(*x0, *x1);
	rotate_range_y(*y0, *y1);
	

		int TEST_THREE[12][9] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0}
	};

	
	SendCommand(0x2C);
	
	//Переворачиваем матрицу пикселей
	for (int i = 0; i < 9; i++) {
		for (int j = 12-1; j >=0; j--) {
			if (TEST_THREE[j][i] == 0) {
				SendData(back_color >> 8);  
				SendData(back_color & 0xFF);
				delay(1000);
			}
			else if (TEST_THREE[j][i] == 1) {
				SendData(font_color >> 8);  
				SendData(font_color & 0xFF);
				delay(1000);
			}
		}
		
	}
	
}

//void print(int number) {
//	
//	/*
//	x0, x1, y0, y1 - координаты символа
//	Смещения:
//		2 - м/у символами
//		4 - м/у строчками 
//	*/
//	
//	
//	
//	static int x0 = 1+3, x1 = 9+3;
//	static int y0 = 61, y1 = 72;

//	for (int i = 0; i < 4; i++) {
//		for (int i = 0; i < 14; i++) {
//					if (number == 3) {
//						TEST_THREE(BLUE, BLACK, &x0, &x1, &y0, &y1);
//						x0 += 9+2, y0 += 0;
//						x1 += 9+2, y1 += 0;
//					}
//				}

//		x0 = 1+3, x1 = 9+3;
//		y0 = y0-12-5, y1 = y1-12-5;	
//	}
//}



void display_print(char number[]) {
	
	/*
	Функция вывода сообщения на экран
	x0, x1, y0, y1 - координаты символа
	Смещения:
		2 - м/у символами
		3 - отступы
		5 - м/у строчками 
	*/
	
	
	int count_symbol = 1;
	while (number[count_symbol] != '\0') {
		count_symbol++;
	}
	
	int count_line = 0;
	
	static int x0 = 1+3, x1 = 9+3;
	static int y0 = 61, y1 = 72;
		for (int i = 0; i <= count_symbol; i++) {
					if (number[i] == '0') {
						ZERO(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '1') {
						ONE(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '2') {
						TWO(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '3') {
						THREE(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '4') {
						FOR(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '5') {
						FIVE(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '6') {
						SIX(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '7') {
						SEVEN(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '8') {
						EIGHT(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					else if (number[i] == '9') {
						NINE(BLUE, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+2, y0 += 0;
						x1 += 9+2, y1 += 0;
					}
					if (i % 14 == 0 && i != 0) {
						
						//Переход на новую строчку
						x0 = 1+3, x1 = 9+3;
						y0 = y0-12-5, y1 = y1-12-5;
						
						//Подсчет заполненных строк
						count_line++;
					}

					if (number[i] == number[count_symbol] && count_line != 4-1) {
						//Переход на новую строчку
						x0 = 1+3, x1 = 9+3;
						y0 = y0-12-5, y1 = y1-12-5;
						
						count_line++;
					}
					
					//Очистка экрана при заполнеии всех строк
					if (count_line == 3-1) {
						count_line = 0;
						Screen(BLACK, 80, 160);
						
						//Возвращение в исходную позицию
						x0 = 1+3, x1 = 9+3;
						y0 = 61, y1 = 72;
					}

				}
		
	
}

