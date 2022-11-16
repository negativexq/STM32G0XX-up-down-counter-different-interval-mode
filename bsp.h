/*
* BSP.h
*
* BOARD SUPPORT PACKAGE
*
* author:
* Omer Faruk Koc - 171024066
*/
#ifndef BSP_H_
#define BSP_H_
#include "stm32g0xx.h"
void BSP_pin_init(char, int, char);
void BSP_output_set(char, int);
void BSP_output_toggle(char, int);
void BSP_output_reset(char, int);
int BSP_input_read(char, int);
void BSP_EXTI_init(char, int, int);
void BSP_timer_init(int, int, int);
void BSP_timer_flagup(int);
void BSP_IWDG_init(void);
void BSP_feed_dog(void);
void BSP_button_init(void);
void BSP_button_control(void);
void BSP_onboard_led_init(void);
void BSP_onboard_led_set(void);
void BSP_onboard_led_clear(void);
void BSP_onboard_led_toggle(void);
void BSP_onboard_button_init(void);
int BSP_onboard_button_read(void);
#endif

