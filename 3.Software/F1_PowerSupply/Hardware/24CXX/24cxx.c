#include "24cxx.h" 
#include "my_iic.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32F103开发板V1
//24CXX驱动 代码(适合24C01~24C256)		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/15
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////


//初始化IIC接口
void AT24CXX_Init(void)
{
	MYIIC_IIC_Init();
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
    MYIIC_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		MYIIC_IIC_Send_Byte(0XA0);	   //发送写命令
		MYIIC_IIC_Wait_Ack();
		MYIIC_IIC_Send_Byte(ReadAddr>>8);//发送高地址	    
	}else MYIIC_IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	   
	MYIIC_IIC_Wait_Ack(); 
    MYIIC_IIC_Send_Byte(ReadAddr%256);   //发送低地址
	MYIIC_IIC_Wait_Ack();	    
	MYIIC_IIC_Start();  	 	   
	MYIIC_IIC_Send_Byte(0XA1);           //进入接收模式			   
	MYIIC_IIC_Wait_Ack();	 
    temp=MYIIC_IIC_Read_Byte(0);		   
    MYIIC_IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
    MYIIC_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		MYIIC_IIC_Send_Byte(0XA0);	    //发送写命令
		MYIIC_IIC_Wait_Ack();
		MYIIC_IIC_Send_Byte(WriteAddr>>8);//发送高地址	  
	}else MYIIC_IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
	MYIIC_IIC_Wait_Ack();	   
    MYIIC_IIC_Send_Byte(WriteAddr%256);   //发送低地址
	MYIIC_IIC_Wait_Ack(); 	 										  		   
	MYIIC_IIC_Send_Byte(DataToWrite);     //发送字节							   
	MYIIC_IIC_Wait_Ack();  		    	   
    MYIIC_IIC_Stop();					//产生一个停止条件 
	HAL_Delay(100);	 				//EEPROM的写入速度比较慢，加入延迟
} 
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}








