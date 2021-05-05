#ifndef __COM_H
#define __COM_H

#include "usart.h"


#define REG_V 0X71
#define REG_I 0X72
#define REG_P 0X73
#define REG_SET_V 0X74
#define REG_SET_I 0X75
#define REG_OUT_STA 0X76

#define CMD_SHIFT 0X70

#define BUF_SIZE 255  

typedef struct{
	_Bool FLAG;
	uint8_t FUN;
	uint8_t CMD1;
	uint8_t LEN;
	uint8_t DATA[256];
	uint8_t CRC_DATA;
}com;

void UART_RxIdleCallback(UART_HandleTypeDef *huart);

extern uint8_t receive_buf[BUF_SIZE];
extern uint8_t tramsmission_buf[BUF_SIZE];

#endif
