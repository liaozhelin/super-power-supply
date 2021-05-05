//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RCT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/08/22
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
//     LCD模块                STM32单片机
//      VCC          接          3.3V         //电源
//      GND          接          GND          //电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI总线
//     LCD模块                STM32单片机    
//       SDA         接          PB15         //液晶屏SPI总线数据写信号
//=======================================液晶屏控制线接线==========================================//
//     LCD模块 					      STM32单片机 
//       BLK         接          PB9          //液晶屏背光控制信号，如果不需要控制，接3.3V
//       SCK         接          PB13         //液晶屏SPI总线时钟信号
//       DC          接          PB10         //液晶屏数据/命令控制信号
//       RES         接          PB12         //液晶屏复位控制信号

//=========================================触摸屏触接线=========================================//
//如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
//	   LCD模块                STM32单片机 
//      T_IRQ        接          PC10         //触摸屏触摸中断信号
//      T_DO         接          PC2          //触摸屏SPI总线读信号
//      T_DIN        接          PC3          //触摸屏SPI总线写信号
//      T_CS         接          PC13         //触摸屏片选控制信号
//      T_CLK        接          PC0          //触摸屏SPI总线时钟信号
**************************************************************************************************/	
 /* @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**************************************************************************************************/	
#include "lcd.h"
#include "stdlib.h"	 
#include "spi.h"
#include "tim.h"
#include "stm32f1xx_hal.h"
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;
#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                ((uint16_t)0x0002)

//画笔颜色,背景颜色
u16 POINT_COLOR,BACK_COLOR;  
u16 DeviceCode;	


/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 data)
{ 
     LCD_CS_CLR;     
	 LCD_RS_CLR;
	 HAL_SPI_Transmit(&hspi1,&data,1,0xffffffff);
     LCD_CS_SET;	
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 data)
{
     LCD_CS_CLR;
	 LCD_RS_SET;
	 HAL_SPI_Transmit(&hspi1,&data,1,0xffffffff);
     LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void Lcd_WriteData_16Bit(u16 Data)
{	
   LCD_CS_CLR;
   unsigned char buf;
   LCD_RS_SET;  
   buf=(Data>>8);
   HAL_SPI_Transmit(&hspi1,&buf,sizeof(buf),10);
   buf=Data;
   HAL_SPI_Transmit(&hspi1,&buf,sizeof(buf),10);
   LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//设置光标位置 
	Lcd_WriteData_16Bit(POINT_COLOR); 
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
	unsigned int i,m; 
	unsigned char buf;	
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	LCD_CS_CLR;
	LCD_RS_SET;
	for(i=0;i<lcddev.height;i++)
	{
    for(m=0;m<lcddev.width;m++)
    {	
		   buf=(Color>>8);
		   HAL_SPI_Transmit(&hspi1,&buf,sizeof(buf),10);
//		   SPI_WriteByte(SPI2,buf);
//		   HAL_SPI_Transmit_DMA(&hspi2,&buf,sizeof(buf));
		   buf=Color;
		   HAL_SPI_Transmit(&hspi1,&buf,sizeof(buf),10);
//		   SPI_WriteByte(SPI2,buf);
//		   HAL_SPI_Transmit_DMA(&hspi2,&buf,sizeof(buf));
		
//		    SPI_WriteByte(SPI2,Color>>8);
//			SPI_WriteByte(SPI2,Color);
		}
	}
	 LCD_CS_SET;
} 

void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 Color){
	unsigned int i,m; 
	unsigned char buf;
	LCD_SetWindows(x1,y1,x2,y2);
	LCD_RS_SET;
	for(i=x1;i<x2+1;i++)
	{
    for(m=y1;m<y2+1;m++)
    {	
		   buf=(Color>>8);
		   HAL_SPI_Transmit(&hspi1,&buf,sizeof(buf),10);
		   buf=Color;
		   HAL_SPI_Transmit(&hspi1,&buf,sizeof(buf),10);
		}
	}
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_RESET(void)
{
	LCD_CS_SET;
	LCD_RST_CLR;
	HAL_Delay(100);
	LCD_RST_SET;
	HAL_Delay(100);
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{  
	
 	LCD_RESET(); //LCD 复位
//************* ST7789V初始化**********//	
	LCD_WR_REG(0x11);
	HAL_Delay(200);
	
//	LCD_WR_REG(0x2a); 		//Column address set
//	LCD_WR_DATA(0x00); 		//start column
//	LCD_WR_DATA(0x00); 
//	LCD_WR_DATA(0x00);		//end column
//	LCD_WR_DATA(0xef);

//	LCD_WR_REG(0x2b); 		//Row address set
//	LCD_WR_DATA(0x00); 		//start row
//	LCD_WR_DATA(0x28); 
//	LCD_WR_DATA(0x01);		//end row
//	LCD_WR_DATA(0x17);

	LCD_WR_REG(0xb2); 		//Porch control
	LCD_WR_DATA(0x0c); 
	LCD_WR_DATA(0x0c); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x33); 
	LCD_WR_DATA(0x33); 

//	LCD_WR_REG(0x20); 		//Display Inversion Off

	LCD_WR_REG(0xb7); 		//Gate control
	LCD_WR_DATA(0x56);   		//35
//---------------------------------ST7789S Power setting--------------------------------------// 
	LCD_WR_REG(0xbb); //VCOMS Setting
	LCD_WR_DATA(0x18);  //1f

	LCD_WR_REG(0xc0); 		//LCM Control
	LCD_WR_DATA(0x2c); 

	LCD_WR_REG(0xc2); 		//VDV and VRH Command Enable
	LCD_WR_DATA(0x01); 

	LCD_WR_REG(0xc3); //VRH Set
	LCD_WR_DATA(0x1f); //12

	LCD_WR_REG(0xc4); 			//VDV Setting
	LCD_WR_DATA(0x20); 

	LCD_WR_REG(0xc6); 			//FR Control 2
	LCD_WR_DATA(0x0f); 
//LCD_WR_REG(0xca); 
//LCD_WR_DATA(0x0f); 
//LCD_WR_REG(0xc8); 
//LCD_WR_DATA(0x08); 
//LCD_WR_REG(0x55); 
//LCD_WR_DATA(0x90); 
	LCD_WR_REG(0xd0);  //Power Control 1
	LCD_WR_DATA(0xa6);   //a4
	LCD_WR_DATA(0xa1); 
//--------------------------------ST7789S gamma setting---------------------------------------// 

	LCD_WR_REG(0xe0); 
	LCD_WR_DATA(0xd0); 
	LCD_WR_DATA(0x0d); 
	LCD_WR_DATA(0x14); 
	LCD_WR_DATA(0x0b); 
	LCD_WR_DATA(0x0b); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x3a);  
	LCD_WR_DATA(0x44); 
	LCD_WR_DATA(0x50); 
	LCD_WR_DATA(0x08); 
	LCD_WR_DATA(0x13); 
	LCD_WR_DATA(0x13); 
	LCD_WR_DATA(0x2d); 
	LCD_WR_DATA(0x32); 

	LCD_WR_REG(0xe1); 				//Negative Voltage Gamma Contro
	LCD_WR_DATA(0xd0); 
	LCD_WR_DATA(0x0d); 
	LCD_WR_DATA(0x14); 
	LCD_WR_DATA(0x0b); 
	LCD_WR_DATA(0x0b); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x3a); 
	LCD_WR_DATA(0x44); 
	LCD_WR_DATA(0x50); 
	LCD_WR_DATA(0x08); 
	LCD_WR_DATA(0x13); 
	LCD_WR_DATA(0x13); 
	LCD_WR_DATA(0x2d); 
	LCD_WR_DATA(0x32);
	
//	LCD_WR_REG(0x36); 			//Memory data access control
//	LCD_WR_DATA(0x00); 
//	
	LCD_WR_REG(0x3A); 			//Interface pixel format
	LCD_WR_DATA(0x55);			//65K	
	//LCD_WR_DATA(0x66);			//262K  RGB 6 6 6

//	LCD_WR_REG(0xe7); 			//SPI2 enable    启用2数据通道模式
//	LCD_WR_DATA(0x00); 


	LCD_WR_REG(0x21);			//Display inversion on
//	LCD_WR_REG(0x29); 			//Display on	
	
	LCD_direction(3);
	
	//LCD_SetWindows(0,0,320,240);
	
	LCD_Clear(BLACK);
	LCD_WR_REG(0x29); 			//Display on
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	

	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA((xStar+lcddev.xoffset)>>8);
	LCD_WR_DATA(xStar+lcddev.xoffset);		
	LCD_WR_DATA((xEnd+lcddev.xoffset)>>8);
	LCD_WR_DATA(xEnd+lcddev.xoffset);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA((yStar+lcddev.yoffset)>>8);
	LCD_WR_DATA(yStar+lcddev.yoffset);		
	LCD_WR_DATA((yEnd+lcddev.yoffset)>>8);
	LCD_WR_DATA(yEnd+lcddev.yoffset);

	LCD_WriteRAM_Prepare();	//开始写入GRAM			
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			lcddev.xoffset=0;
			lcddev.yoffset=0;
			LCD_WriteReg(0x36,0);//BGR==1,MY==0,MX==0,MV==0
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			lcddev.xoffset=0;
			lcddev.yoffset=0;
			LCD_WriteReg(0x36,(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;
            lcddev.xoffset=0;
			lcddev.yoffset=0;			
			LCD_WriteReg(0x36,(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			lcddev.xoffset=0;
			lcddev.yoffset=0;
			LCD_WriteReg(0x36,(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
		break;	
		default:break;
	}		
}	 
