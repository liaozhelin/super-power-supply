#include "my_iic.h"

static void delay_nns(uint16_t D)  //30纳秒ns  根据手册要用到IIC的HS高速模式
{
    while(--D);
}

void delay_nms(uint16_t ms)  //毫秒
{
    uint16_t i;
    uint32_t M = 0;//720W
    for(i = 0;i < ms; i++)
    for(M=12000;M > 0;M--);
}

void delay_nus(uint16_t us)//微秒
{
    uint16_t i;
    uint16_t M = 0;//720W
    for(i = 0;i < us; i++)
    for(M=72;M > 0;M--);
}

/****************IIC***************************/
void MYIIC_IIC_Init(void)
{
    IIC_SDA_H;
    IIC_SCL_H;  
    delay_nns(5);
}
    
void MYIIC_IIC_Start(void)
{
    IIC_SDA_H;            
    IIC_SCL_H;
    delay_nns(5);
    IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
    delay_nns(5);
    IIC_SCL_L;//钳住I2C总线，准备发送或接收数据 
    delay_nns(5);
}    

void MYIIC_IIC_Stop(void)
{
    IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
	delay_nns(5);
    IIC_SCL_H; 
	delay_nns(5);
    IIC_SDA_H;//发送I2C总线结束信号
    delay_nns(5);                                   
}

void MYIIC_IIC_Ack(void)
{
    IIC_SDA_L;
    delay_nns(5);
    IIC_SCL_H;
    delay_nns(5);
    IIC_SCL_L;
	delay_nns(5);
    IIC_SDA_H;
}

void MYIIC_IIC_NAck(void)
{
    IIC_SDA_H;
    delay_nns(5);
    IIC_SCL_H;
	delay_nns(5);
    IIC_SCL_L;
    delay_nns(5);
    IIC_SDA_L;
}        

uint8_t MYIIC_IIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
    //SDA_IN();      //SDA设置为输入  
    IIC_SDA_H;
    delay_nns(5);       
    IIC_SCL_H;
    delay_nns(5);          
    
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            MYIIC_IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_L;//时钟输出0        
    return 0;  
}

void MYIIC_IIC_Send_Byte(uint8_t txd)
{                              
   IIC_SCL_L;//拉低时钟开始数据传输
   for(uint8_t i = 0;i < 8;i++)
    {              
        if(txd&0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;                
        txd<<=1;       
                
        IIC_SCL_H;
        delay_nns(5);
        IIC_SCL_L;
        delay_nns(5);
    }            
    //    IIC_SDA_H;
    //    IIC_SCL_H;            //当去掉wait_ack时的时候添加
    //    delay_nns(5);
        //IIC_SCL_L;
} 

uint8_t MYIIC_IIC_Read_Byte(unsigned char ack)
{
      uint8_t TData=0,i;
    for(i=0;i<8;i++)
    {
        IIC_SCL_H;
        delay_nus(5);
        TData=TData<<1;
        //if(GPIOB->IDR& GPIO_IDR_IDR7)        //判断SDA是否为高
            if(SDA_READ)
        {
            TData|=0x01;
        }
        IIC_SCL_L;
        delay_nus(5);
    }
        if(!ack)
            MYIIC_IIC_NAck();
        else
            MYIIC_IIC_Ack();
//    IIC_SCL_L;
//    delay_nns(5);
//    IIC_SDA_L;
//    delay_nns(5);                //ACK
//    IIC_SCL_H;
//    delay_nns(5);
//    IIC_SCL_L;
//    delay_nns(5);
//    IIC_SDA_H;
    return TData;
}
