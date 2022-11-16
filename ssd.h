/*
 * ssd.h
 *
 * BOARD SUPPORT PACKAGE
 *
 * author: Ömer Faruk KOÇ
 *
 */
#ifndef SSD_H_
#define SSD_H_
#include "ssd.h"

#include "stm32g0xx.h"
#include "bsp.h"
#include <math.h>
void screen_open(int);
void display(int);
void display_float(int);
void BSP_ssd_init(void);
void BSP_ssd_set(float);
void BSP_ssd_text(char);
void ssd_func_text(int);
void delay(volatile uint32_t);
#endif
