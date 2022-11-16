/*
*main.c
*
*author:
* Omer Faruk Koc - 171024066
*
*/
#include "stm32g0xx.h"
#include "bsp.h"
#include "ssd.h"
static volatile uint32_t Scount = 0;
static volatile int state = -1;
static volatile int button_prevent = 0;
static volatile int wait = 0;
static volatile char error = '\0';
static volatile int SSD_DELAY = 2000;
void delay_ms(volatile uint32_t s);
void counter(void);
void SysTick_Handler(void) {
if (Scount > 0)
Scount--;
else if (Scount == 0)
button_prevent = 0;
}
void TIM2_IRQHandler(void) {
		// Mode 0 › No countdown (0 second interval)
		// Mode 1 › Count down speed is ×1, with 1 second intervals.
		// Mode 2 › Count down speed is ×2, with .5 second intervals
		// Mode 3 › Count down speed is ×10, with .1 second intervals
		// Mode 4 › Count down speed is ×100, with .01 second intervals
		// Mode 5 › Count down speed is ×1000, with .001 second intervals
float number;
switch (state) {
	
	case 0: //Mode 0 › No countdown (0 second interval)
BSP_ssd_set();
	break;
	
	case 1: // Mode 1 › Count down speed is ×1, with 1 second intervals.
BSP_ssd_set();
	break;
	
	case 2: // Mode 2 › Count down speed is ×2, with .5 second intervals
wait = 5;
	break;
	
	case 3: // Mode 3 › Count down speed is ×10, with .1 second intervals
wait = 2;
	break;
	
	case 4: // Mode 4 › Count down speed is ×100, with .01 secondintervals
wait = 1;
	break;

	case 5: // Mode 5 › Count down speed is ×1000, with .001 secondintervals
wait = 3000;
	break;
	
}
	if (state == 0) //
	{
	wait = 1000;
	} else if (state == 1) //
	{
	wait = 120;
	} else if (state == 2) //
	{
	wait = 10;
	}
	else if (state == 3) //
	{
	wait = 10;
	} else if (state == 4) //
	{
	wait = 10;
	} else if (state == 5) //
	{
	wait = 10;
	} else {
	state = 0;
	}
	BSP_timer_flagup(2);
	}
	
	void EXTI4_15_IRQHandler(void) {
	if (button_prevent == 1) {
	} else {
	Scount = 70; //prevent double click by button prevent
	button_prevent = 1; // prevent for double click.
	
	
	int C1; // It will reset after 700ms in Systick Handler
	
	delay(SystemCoreClock / 800); // little delay for debounce about 50ms
	
	C1 = BSP_input_read('B', 4); //
	
	if (C1 == 1) {
	counter();
	}
	}
	BSP_feed_dog(); // feeding the dog if you don't it bites.
	EXTI->RPR1 |= (1U << 4); //pending all interrupts
	EXTI->RPR1 |= (1U << 5);
	EXTI->RPR1 |= (1U << 8);
	EXTI->RPR1 |= (1U << 9);
	}
	
int main(void) {
	BSP_ssd_init(); //seven segment display init
	BSP_button_init();
	BSP_timer_init(2, SystemCoreClock / 120, 1); // timer2 init with
	120 interrupt for second and low priority for screen
	BSP_EXTI_init('B', 4, 0);
	SysTick_Config(SystemCoreClock / 1000); //systick enable
	BSP_IWDG_init(); // watchdog init
	DBG->APBFZ1 |= (1U << 12); //when debugging no more watchdog
	
	while (1) {
		
	}
	
	return 0;
}
	void delay_ms(volatile uint32_t s) {
	Scount = s;
	while (Scount);

}
	void delay2(volatile uint32_t s) {
	for (int i = 0; i < s; ++i);
	}
	void counter(void) {
	delay(SystemCoreClock / 80); // little delay for debounce about 50ms
	int b;
	
	for (int x = 2; x >= 0; x--) {
	//screen_open(1);
	//display(x);
	//delay2(SSD_DELAY);
	if (x == 2) {
	b = 3;
	} else if (x < 2) {
	b = 9;
	}
	for (int y = b; y >= 0; y--) {
	//screen_open(1);
	//display(x);
	//delay2(SSD_DELAY);
	//screen_open(2);
	//display(y);
	//delay2(SSD_DELAY);
	for (int z = 5; z >= 0; z--) {
	//screen_open(1);
	//display(x);
	//delay2(SSD_DELAY);
	//screen_open(2);
	//display(y);
	//delay2(SSD_DELAY);
	//screen_open(3);
	//display(z);
	//delay2(SSD_DELAY);
	for (int v = 9; v >= 0; v--) {
	for (int k = 0; k < wait; k++) {
	int d1 = 1;
	int d2 = 2;
	int d3 = 3;
	int d4 = 4;
	screen_open(d1);
	display(x);
	delay2(SSD_DELAY);
	
	screen_open(d2);
	display(y);
	delay2(SSD_DELAY);
	
	screen_open(d3);
	display(z);
	delay2(SSD_DELAY);
	
	screen_open(d4);
	display(v);
	delay2(SSD_DELAY);
	
	BSP_feed_dog();
	
	int C1 = BSP_input_read('B', 4); //
	if (C1 == 1) {
	BSP_ssd_set();
	
	state++;
	delay(SystemCoreClock / 80); 
	//little delay for debounce about 50ms
	
	delay2(1000);
	
	if (state == 0) //
	{
	wait = 999999;
	} 
	else if (state == 1) //
	{
	wait = 520;
	} 
	else if (state == 2) //
	{
	wait = 260;
	}
	else if (state == 3) //
	{
	wait = 50;
	} 
	else if (state == 4) //
	{
	wait = 8;
	} 
	else if (state == 5) //
	{
	wait = 1;
	} 
	else
	{
	state = 0;
	wait = 999999;
	}
	counter();
