#ifndef __MY_IIC_H
#define __MY_IIC_H

#include "stm32f1xx_hal.h"
#include "stdint.h"

//IO²Ù×÷
#define IIC_SCL_H   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET) //SCL H
#define IIC_SCL_L   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET) //SCL H
#define IIC_SDA_H   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET) //SDA_H
#define IIC_SDA_L   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET) //SDA_L
#define READ_SDA    HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)  //ÊäÈëSDA
#define SDA_READ    GPIOB->IDR& GPIO_IDR_IDR11

static void delay_nns(uint16_t D);
void delay_nms(uint16_t ms);
void delay_nus(uint16_t us);
void MYIIC_IIC_Init(void);
void MYIIC_IIC_Start(void);
void MYIIC_IIC_Stop(void);
void MYIIC_IIC_Ack(void);
void MYIIC_IIC_NAck(void);
uint8_t MYIIC_IIC_Wait_Ack(void);
void MYIIC_IIC_Send_Byte(uint8_t txd);
uint8_t MYIIC_IIC_Read_Byte(unsigned char ack);

#endif

