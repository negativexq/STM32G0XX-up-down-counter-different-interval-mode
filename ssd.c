/*
 *ssd.c
 *
 *definition: Includes seven segment display pin settings, display floatinteger-negative numbers, display text.
 *
 *author: Ömer Faruk KOÇ
 *
 */
#include "stm32g0xx.h"
#include "ssd.h"
#include "bsp.h"
#include <math.h>
static volatile int SSD_DELAY = 8000;
void BSP_ssd_init(void) {
	/*please use this pin numbers */
	BSP_pin_init('A', 0, 'O'); // a A0
	BSP_pin_init('A', 1, 'O'); // b A1
	BSP_pin_init('A', 4, 'O'); // c A2
	BSP_pin_init('A', 5, 'O'); // d A3
	BSP_pin_init('A', 12, 'O'); // e A4
	BSP_pin_init('A', 11, 'O'); // f A5
	BSP_pin_init('A', 6, 'O'); // g A6
	BSP_pin_init('A', 7, 'O'); // dec A7

	BSP_pin_init('B', 6, 'O'); // d1 D1
	BSP_pin_init('B', 7, 'O'); // d2 D0
	BSP_pin_init('B', 1, 'O'); // d3 D3
	BSP_pin_init('B', 3, 'O'); // d4 D13
}
void BSP_ssd_set(float number)
//This function simply display to 4 digit positive or 3 digit negative float and integer numbers.
//There is a if-else if-else structure for each case.
//Detailed flowchart is in report.
{
	int number_int = number;
	float float_part = number - number_int;
	if (float_part < 0) {
		if (float_part > -0.001)
			float_part = 0;
	} else {
		if (float_part < 0.001)
			float_part = 0;
	}
	int digit;
	if (float_part < 0) //number is negative
			{
		digit = -1;
		screen_open(1);
		display(digit);
		delay(SSD_DELAY); //30 fps
		number_int = -number_int;
		float_part = -float_part;
		if (number_int < 10) // shows integer part is only 1 digit, float part is 2 digit
				{
			digit = number_int;
			screen_open(2);
			display_float(digit);
			delay(SSD_DELAY);
			float_part = float_part * 100;
			digit = float_part / 10;
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
			float_part = (float_part - (digit * 10));
			digit = float_part;
			screen_open(4);
			display(digit);
			delay(SSD_DELAY);
		} else if (number_int < 100 && number_int >= 10) //shows integer part is 2 digit and float part is 1 digit
				{
			digit = number_int / 10;
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - (digit * 10));
			digit = number_int;
			screen_open(3);
			display_float(digit);
			delay(SSD_DELAY);
			float_part = float_part * 10;
			digit = float_part;
			screen_open(4);
			display(digit);
			delay(SSD_DELAY);
		} else if (number_int >= 100) //shows integer part is 3 digit and float part is 0 digit
				{
			digit = number_int / 100;
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - digit * 100);
			digit = number_int / 10;
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - (digit * 10));
			digit = number_int;
			screen_open(4);
			display_float(digit);
			delay(SSD_DELAY);
		}
	} else if (float_part > 0) // if number is positive with float part
			{
		if (number_int < 10) //shows integer part is 1 digit and float part is 3 digit
				{
			screen_open(1);
			display_float(number_int);
			delay(SSD_DELAY);
			float_part = float_part * 1000;
			digit = float_part / 100;
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
			float_part = (float_part - (digit * 100));
			digit = float_part / 10;
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
			float_part = (float_part - (digit * 10));
			digit = float_part;
			screen_open(4);
			display(digit);
			delay(SSD_DELAY);
		} else if (number_int < 100 && number_int >= 10) //shows integer part is 2 digit and float part is 2 digit
				{
			digit = number_int / 10;
			screen_open(1);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - (digit * 10));
			digit = number_int;
			screen_open(2);
			display_float(digit);
			delay(SSD_DELAY);
			float_part = float_part * 100;
			digit = float_part / 10;
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
			float_part = (float_part - (digit * 10));
			digit = float_part;
			screen_open(4);
			display(digit);
			delay(SSD_DELAY);
		} else if (number_int >= 100 && number_int < 1000) //shows integer part is 3 digit and float part is 1 digit
				{
			digit = number_int / 100;
			screen_open(1);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - digit * 100);
			digit = number_int / 10;
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - (digit * 10));
			digit = number_int;
			screen_open(3);
			display_float(digit);
			delay(SSD_DELAY);
			float_part = float_part * 10;
			digit = float_part;
			screen_open(4);
			display(digit);
			delay(SSD_DELAY);
		} else if (number_int >= 1000) //shows integer part is 4 digit and float part is 0 digit
				{
			digit = number_int / 1000;
			screen_open(1);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - digit * 1000);
			digit = number_int / 100;
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - (digit * 100));
			digit = number_int / 10;
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
			number_int = (number_int - (digit * 10));
			digit = number_int;
			screen_open(4);
			display_float(digit);
			delay(SSD_DELAY);
		}
	} else if (number_int < 0) //if there is no float part shows integer part is 3 digit with minus
			{
		digit = -1;
		screen_open(1);
		display(digit);
		delay(SSD_DELAY);
		number_int = -number_int;
		int checker = 0;
		digit = number_int / 100;
		if (digit == 0) {
			checker++;
			GPIOA->ODR &= 0;
			GPIOA->ODR = ~GPIOA->ODR;
		} else {
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
		}
		number_int = (number_int - digit * 100);
		digit = number_int / 10;
		if (digit == 0 && checker == 1) {
			checker++;
		} else {
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
		}
		number_int = (number_int - (digit * 10));
		digit = number_int;
		screen_open(4);
		display(digit);
		delay(SSD_DELAY);
	} else //if there is no float part shows integer part is 4 digit
	{
		int checker = 0; //checker allows me to dont display unnecesary zeros
		digit = number_int / 1000;
		if (digit == 0) {
			checker++;
			screen_open(1);
			GPIOA->ODR &= 0;
			GPIOA->ODR = ~GPIOA->ODR;
		} else {
			screen_open(1);
			display(digit);
			delay(SSD_DELAY);
		}
		number_int = (number_int - digit * 1000);
		digit = number_int / 100;
		if (checker == 1 && digit == 0) {
			checker++;
		} else {
			screen_open(2);
			display(digit);
			delay(SSD_DELAY);
		}
		number_int = (number_int - digit * 100);
		digit = number_int / 10;
		if (checker == 2 && digit == 0) {
		} else {
			screen_open(3);
			display(digit);
			delay(SSD_DELAY);
		}
		number_int = (number_int - digit * 10);
		digit = number_int;
		screen_open(4);
		display(digit);
		delay(SSD_DELAY);
	}
}
void BSP_ssd_text(char s)
// this function includes display Overflow and Invalid for SSD
{
	if (s == 'O') {
		screen_open(1);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
		delay(SSD_DELAY);
		screen_open(2);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		delay(SSD_DELAY);
		screen_open(3);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
		GPIOA->ODR &= ~(1U << 6); //g
		delay(SSD_DELAY);
		screen_open(4);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
		delay(SSD_DELAY);
	} else if (s == 'I') {
		screen_open(1);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
		delay(SSD_DELAY);
		screen_open(2);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 6); //g
		delay(SSD_DELAY);
		screen_open(3);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		delay(SSD_DELAY);
		screen_open(4);
		GPIOA->ODR &= 0;
		GPIOA->ODR = ~GPIOA->ODR;
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 6); //g
		delay(SSD_DELAY);
	}
}

void screen_open(int screen_num) {
	if (screen_num == 1) {
		/*PB0-1-2-3 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 6);
	} else if (screen_num == 2) {
		/*PB0-2-3-4 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 7);
	} else if (screen_num == 3) {
		/*PB0-2-3-4 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 1);
	} else if (screen_num == 4) {
		/*PB0-2-3-4 as seven segment d1-d2-d3-d4*/
		GPIOB->ODR &= 0;
		GPIOB->ODR |= (1U << 3);
	}
}
void display(int digit) {
	GPIOA->ODR &= 0;
	GPIOA->ODR = ~GPIOA->ODR;
	if (digit == -1) {
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 0) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
	} else if (digit == 1) {
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
	} else if (digit == 2) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 3) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 4) {
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 11); //f
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 5) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 11); //f
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 6) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 7) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
	} else if (digit == 8) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 12); //e
		GPIOA->ODR &= ~(1U << 11); //f
		GPIOA->ODR &= ~(1U << 6); //g
	} else if (digit == 9) {
		GPIOA->ODR &= ~(1U << 0); //a
		GPIOA->ODR &= ~(1U << 1); //b
		GPIOA->ODR &= ~(1U << 4); //c
		GPIOA->ODR &= ~(1U << 5); //d
		GPIOA->ODR &= ~(1U << 11); //f
		GPIOA->ODR &= ~(1U << 6); //g
	}
}
void display_float(int digit) {
	display(digit);
	GPIOA->ODR &= ~(1U << 7); //dec
}
void delay(volatile uint32_t s) {
	for (int i = 0; i < s; ++i)
		;
}
