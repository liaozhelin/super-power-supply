#ifndef __LED_H
#define __LED_H

#include "stdint.h"
#include "tim.h"

#define  LEDB TIM3->CCR2
#define  LEDR TIM3->CCR3
#define  LEDG TIM3->CCR4

void LED_COLOR(uint8_t IS_COLOR,uint8_t CCR);


typedef enum{
	RED_  = (uint8_t)0,
	GREEN_ = (uint8_t)1,
	BLUE_ = (uint8_t)2,
	PINK_ = (uint8_t)3,
	YELLOW_ = (uint8_t)4,
	CYAN_ = (uint8_t)5,
	WHITE_ = (uint8_t)6,
	
	BLACK_ = (uint8_t)7,
}IS_COLOR;

typedef struct{
	
	void (*LED_COLOR)(uint8_t,uint8_t);
	
}LED_TypeDef;

extern LED_TypeDef LED;

#endif
