#ifndef __SC8813_H
#define __SC8813_H

#include "stdint.h"
#include "stm32f1xx_hal.h"

#define SC8813_ADDR 0XE8

#define VBAT_SET  0X00
#define VBUSREF_I_SET 0X01
#define VBUSREF_I_SET2 0X02
#define VBUSREF_E_SET 0X03
#define VBUSREF_E_SET2 0X04
#define IBUS_LIM_SET 0X05
#define IBAT_LIM_SET 0X06
#define VINREG_SET 0X07
#define RATIO 0X08
#define CTRL0_SET 0X09
#define CTRL1_SET 0X0A
#define CTRL2_SET 0X0B
#define CTRL3_SET 0X0C
#define VBUS_FB_VALUE 0X0D
#define VBUS_FB_VALUE2 0X0E
#define VBAT_FB_VALUE 0X0F
#define VBAT_FB_VALUE2 0X10
#define IBUS_VALUE 0X11
#define IBUS_VALUE2 0X12
#define IBAT_VALUE 0X13
#define IBAT_VALUE2 0X14
#define ADIN_VALUE 0X15
#define ADIN_VALUE_2 0X16
#define STATUS 0X17
#define MASK 0X19


void SC8813_INIT(uint8_t addr);
void SC8813_SetRegPointer(uint8_t addr,uint8_t reg);
void SC8813_SendData(uint8_t addr,uint8_t reg,uint8_t data);
uint8_t SC8813_ReadData(uint8_t addr);
uint16_t SC8813_Get_Data(uint8_t addr);



#endif
