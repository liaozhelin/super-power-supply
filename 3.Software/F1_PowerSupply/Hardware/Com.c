#include "Com.h"
#include "string.h"
#include "Func.h"

#define MAX_LEN 30
#define MIN_LEN 6 
#define DEBUG_MODE 

#define Transmission_Header 	tramsmission_buf[0] = 0XB0;tramsmission_buf[1] = 0XE0;tramsmission_buf[2] = COM.FUN - CMD_SHIFT;
#define Transmission_CMD        tramsmission_buf[3]
#define Transmission_SIZE       tramsmission_buf[4]

uint8_t data_length;
com COM;
uint8_t receive_buf[BUF_SIZE];
uint8_t tramsmission_buf[BUF_SIZE];

void REC_ANALY(void);
void DATA_FUN(void);

void UART_RxIdleCallback(UART_HandleTypeDef *huart){
	//空闲中断
	if(RESET != __HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)){
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		
		HAL_UART_DMAStop(&huart1);
		data_length = BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
		
#ifdef DEBUG_MODE
		printf("Receive Data(length = %d): ",data_length);
		HAL_UART_Transmit(&huart1,receive_buf,data_length,0x200);
        printf("\r\n");
#endif
		
		REC_ANALY();//串口解析函数 2021-04-24
		DATA_FUN();//命令执行函数 2021-04-24
		
		memset(receive_buf,0,data_length);
		data_length = 0;
		HAL_UART_Receive_DMA(&huart1,(uint8_t*)receive_buf,BUF_SIZE);
		
	}
}


//串口解析函数 2021-04-24
void REC_ANALY(void){
	COM.FLAG = 0;
	uint8_t i=0;
	if(data_length < MIN_LEN || data_length > MAX_LEN)return;
	else{
		if(receive_buf[0]!=0XB0)return;
		else{
			if(receive_buf[1]!=0XE0)return;
			else{
				
#ifdef DEBUG_MODE
				printf("Header OK r\n");
#endif
				if(receive_buf[receive_buf[4]+6]!=0X0D)return;
				else{
					if(receive_buf[receive_buf[4]+7]!=0X0A)return;
					else{
						COM.FLAG = 1;
						COM.FUN = receive_buf[2];
						COM.CMD1 =  receive_buf[3];
						COM.LEN = receive_buf[4];
						for(i=0;i< COM.LEN;i++){
							COM.DATA[i] = receive_buf[i+5];
						}
						COM.CRC_DATA = receive_buf[i+6];
						//crc检测函数
#ifdef DEBUG_MODE
						printf("Tail OK \r\n");
						printf("FUN=%X \r\n CMD1=%X \r\n CMD_LEN=%x \r\n DATA=%s \r\n",COM.FUN,COM.CMD1,COM.LEN,COM.DATA);
#endif

						
					}
				}
			}
		}
	}
}


void REG_V_FUN(void){
	Transmission_Header;
	Transmission_CMD = 0X00;
	tramsmission_buf[4] = sizeof(IO.ADCVI.V_OUT);
	tramsmission_buf[5] = IO.ADCVI.V_OUT >> 8;
	tramsmission_buf[6] = IO.ADCVI.V_OUT;
	tramsmission_buf[7] = COM.CRC_DATA;
	tramsmission_buf[8] = 0X0D;
	tramsmission_buf[9] = 0X0A;
 	HAL_UART_Transmit(&huart1,tramsmission_buf,sizeof(IO.ADCVI.V_OUT)+8,0x200);
#ifdef DEBUG_MODE
	printf("REG_V_FUN OK|r\n");
#endif
}

void REG_I_FUN(void){
	
}

void REG_P_FUN(void){
	
}

void REG_SET_V_FUN(void){
	
}

void REG_SET_I_FUN(void){
	
}

void REG_OUT_STA_FUN(void){
	
}

//命令执行函数 2021-04-24
void DATA_FUN(void){
	if(COM.FLAG){
		switch(COM.FUN){
			case REG_V:REG_V_FUN();break;
			case REG_I:REG_I_FUN();break;
			case REG_P:REG_P_FUN();break;
			case REG_SET_V:REG_SET_V_FUN();break;
			case REG_SET_I:REG_SET_I_FUN();break;
			case REG_OUT_STA:REG_OUT_STA_FUN();break;
			
			default: 
				printf("ERROR CMD \r\n");
				break;
		}
	}
}
