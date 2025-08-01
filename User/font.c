#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#include "all_definitions.h"
#include "spi.h"
#include "gpio.h"
#include "st7735s.h"
#include "delay.h"

extern int pixels_vertical;
extern int pixels_horizontal;



//Смещения шрифта
const int between_symbol = 2;
const int ceiling = 8;
const int left_end = 3;
const int between_lines = 5;
const int symbols_in_string;



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


	/**
	 * @brief Отрисовывает ноль
	 *
	 * Параметры в группах (x0, x1) и (y0, y1) задают свой пиксель дважды -
	его начало и конец тем же значением. Функция аналогична для всех цифр
	 *
	 * @param font_color - цвет цифры
	 * @param back_color - цвет фона
	 * @param *x0 - координата начального пикселя по x 
	 * @param *x1 - координата конечного пикселя по x
	 * @param *y0 - координата начального пикселя по y
	 * @param *x0 - координата конечного пикселя по y 
	 */
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



/**
 * @brief Функция вывода сообщения на экран
 *
 * x0, x1, y0, y1 - координаты символа
	Смещения в пикселях
 *  
 * @param number[] - массив символов
 */

void display_print(uint16_t font_collor, char number[]) {
	
	//счетчик символов для перебора
	int count_symbol = 1;
	while (number[count_symbol] != '\0') {
		count_symbol++;
	}
	
	//Счетчик строк
	int count_line = 0;
	
	//Координаты для вывода текущего символа со смещениями
	static int x0 = 1+between_symbol;
  static int x1 = 9+between_symbol;
	
	static int y0 = 69-ceiling;
  static int	y1 = 80-ceiling;
	
		for (int i = 0; i <= count_symbol; i++) {
					if (number[i] == '0') {
						ZERO(font_collor, BLACK, &x0, &x1, &y0, &y1);
						//Сдвиг на следующую позицию
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '1') {
						ONE(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '2') {
						TWO(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '3') {
						THREE(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '4') {
						FOR(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '5') {
						FIVE(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '6') {
						SIX(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '7') {
						SEVEN(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '8') {
						EIGHT(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					else if (number[i] == '9') {
						NINE(font_collor, BLACK, &x0, &x1, &y0, &y1);
						x0 += 9+between_symbol, y0 += 0;
						x1 += 9+between_symbol, y1 += 0;
					}
					
					//Подсчет числа символов в строке
					int symbols_in_string = (pixels_vertical - left_end)/(9+between_symbol);
					
					int lines_on_display = (pixels_horizontal - ceiling)/(12+between_lines);
					
					//Если заполнена вся строка и она не последняя:
					if (((i+1) % symbols_in_string == 0) && ((count_line) != lines_on_display)) {
						
						//Переход на новую строчку
						x0 = 1+left_end, x1 = 9+left_end;
						y0 = y0-12-between_lines, y1 = y1-12-between_lines;
					
						
						//Подсчет заполненных строк
						count_line++;
					}
					
					//Если заполнена вся строка и она последняя
					if (((i+1) % symbols_in_string == 0) && ((count_line) == lines_on_display)) {
						
						//Очистка экрана
						rotate_Screen(BLACK, pixels_vertical, pixels_horizontal);
						
						x0 = 1+left_end, x1 = 9+left_end;
						y0 = 69-ceiling; y1 = 80-ceiling;
						count_line = 0;
					}
//					
//					//Если ... и это последняя строка
//					if (number[i] == number[count_symbol] && ((count_line+1) == lines_on_display)) {
//						

//						
//						count_line++;
//					}
					


				}
		
	
}

