#ifndef __FUNC_H
#define __FUNC_H

#include "include.h"
//-------USER-------//
#include "lcd.h"
#include "GUI.h"
#include "tim.h"
#include "dac.h"
#include "adc.h"
#include "ina226.h"
#include "sc8813.h"
#include "usart.h"
#include "Com.h"
#include "LED.h"
#include "ds1307.h"
#include "24cxx.h"


void HARDWARE_INIT(void);
void SOFTWARE_INIT(void);

#define  ENC  (int16_t)(__HAL_TIM_GET_COUNTER(&htim4))

typedef struct{
	struct{
		uint8_t OUTPUT;
		uint8_t LOCK;
		uint8_t BEEP;
	}Status;
	struct{
		uint8_t ADC_FLASH;
		uint8_t TIM_IO;
		uint8_t TIM1S;
		uint8_t LOCK_IV;
		uint8_t LCD_FLASH;
	}TIM;
}sys;

typedef struct{
	struct{
		uint16_t V_OUT;
		uint16_t I_OUT;
		uint16_t P_OUT;
		uint16_t V_IN;
		uint16_t IN_TEMP;
	}ADCVI;
	struct{
		uint16_t DAC_I;
		uint16_t DAC_V;
		uint8_t AJ_FLAG; //0X80电流选中   0X40电压选中   0X20锁定模式   0X01重复标志位   0XFF(1-4)选中位数
	}DACIV;
	struct{
		uint8_t BLK;
		uint8_t DIRECTION;
	}LCD;
	struct{
		float TEMP;
		float HUM;
	}HT;
	struct{
		uint8_t YEAR;
		uint8_t MOUTH;
		uint8_t DATA;
		uint8_t WEEK;
		uint8_t HOUR;
		uint8_t MINUTE;
		uint8_t SECOND;
	}CLOCK;
	struct{
		uint8_t HOUR;
		uint8_t MINUTE;
		uint8_t SECOND;
		uint16_t CAPACITY;
	}RUN;
	struct{
		float A_X;
		float A_Y;
		float A_Z;
	}MPU;
}io;


//DAC控制
void TIME_TASK(void);
void SET_DAC_VAL(uint16_t CHANNEL,double VAL);
void INTERFACE_SHOW(void);
void UPDATA_SHOW(void);
void ADJUST_IV(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void BEEP(uint16_t freq,uint16_t repeat,uint16_t time);

extern u16 BUF_VOUT[140],BUF_IOUT[140];
extern sys SYS;
extern io IO;

#endif
