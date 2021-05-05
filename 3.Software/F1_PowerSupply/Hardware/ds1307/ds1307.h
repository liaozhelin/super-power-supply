/******************************************************************************
* @ File name --> ds1307.h
* @ Author    --> By@ Sam Chan
* @ Version   --> V1.0
* @ Date      --> 11 - 27 - 2013
* @ Brief     --> 时钟芯片DS1307驱动
* @           --> 本驱动函数兼容DS1307、DS1338、DS1338Z芯片
*
* @ Copyright (C) 20**
* @ All rights reserved
*******************************************************************************
*
*                                  File Update
* @ Version   --> V1.
* @ Author    --> By@
* @ Date      --> 
* @ Revise    --> 
*
******************************************************************************/

#ifndef _ds1307_h_ 
#define _ds1307_h_

#include "stdint.h"

/******************************************************************************
                              外部函数头文件
                    应用到不同的外设头文件请在这里修改即可                        
******************************************************************************/


/******************************************************************************
                        DS1307 / DS1338芯片选择宏定义
******************************************************************************/

#define Chip_Type           1   //选择芯片类型，请修改这里即可
                                //1: 驱动的芯片型号是DS1307
                                //0: 驱动的芯片型号是DS1338 or DS1338Z

/******************************************************************************
                               DS1307寄存器结构定义                          
******************************************************************************/

typedef struct
{
    uint8_t second;  //秒
    uint8_t minute;  //分
    uint8_t hour;    //小时
    uint8_t week;    //星期
    uint8_t date;    //日
    uint8_t month;   //月
    uint8_t year;    //年

    uint8_t SQWE;    //频率输出控制寄存器
}Time_Typedef;

extern Time_Typedef TimeValue;  //定义时间缓存指针

/******************************************************************************
                                    参数宏定义                       
******************************************************************************/

#define DS1307_Write			0xd0	//写命令
#define DS1307_Read			    0xd1	//读命令，或者用（DS1307_Write + 1）

#define Clear_Register			0x00	//清除寄存器值填充数据

#define test_data               0x55    //此数据用来检测DS1307是否存在于总线上用，可以改用其他值

/******************************************************************************
                                  地址参数宏定义
******************************************************************************/

#define Address_second          0x00    //秒寄存器地址
#define Address_minute          0x01    //分钟寄存器地址
#define Address_hour            0x02    //小时寄存器地址
#define Address_week            0x03    //星期寄存器地址
#define Address_date            0x04    //日寄存器地址
#define Address_month           0x05    //月寄存器地址
#define Address_year            0x06    //年寄存器地址

#define Address_SQWE            0x07    //频率输出设置寄存器地址

//RAM地址

#define RAM_Address0            0x08
#define RAM_Address1            0x09
#define RAM_Address2            0x0a
#define RAM_Address3            0x0b
#define RAM_Address4            0x0c
#define RAM_Address5            0x0d
#define RAM_Address6            0x0e
#define RAM_Address7            0x0f

#define RAM_Address8            0x10
#define RAM_Address9            0x11
#define RAM_Address10            0x12
#define RAM_Address11            0x13
#define RAM_Address12            0x14
#define RAM_Address13            0x15
#define RAM_Address14            0x16
#define RAM_Address15            0x17
#define RAM_Address16            0x18
#define RAM_Address17            0x19
#define RAM_Address18            0x1a
#define RAM_Address19            0x1b
#define RAM_Address20            0x1c
#define RAM_Address21            0x1d
#define RAM_Address22            0x1e
#define RAM_Address23            0x1f

#define RAM_Address24            0x20
#define RAM_Address25            0x21
#define RAM_Address26            0x22
#define RAM_Address27            0x23
#define RAM_Address28            0x24
#define RAM_Address29            0x25
#define RAM_Address30            0x26
#define RAM_Address31            0x27
#define RAM_Address32            0x28
#define RAM_Address33            0x29
#define RAM_Address34            0x2a
#define RAM_Address35            0x2b
#define RAM_Address36            0x2c
#define RAM_Address37            0x2d
#define RAM_Address38            0x2e
#define RAM_Address39            0x2f

#define RAM_Address40            0x30
#define RAM_Address41            0x31
#define RAM_Address42            0x32
#define RAM_Address43            0x33
#define RAM_Address44            0x34
#define RAM_Address45            0x35
#define RAM_Address46            0x36
#define RAM_Address47            0x37
#define RAM_Address48            0x38
#define RAM_Address49            0x39
#define RAM_Address50            0x3a
#define RAM_Address51            0x3b
#define RAM_Address52            0x3c
#define RAM_Address53            0x3d
#define RAM_Address54            0x3e
#define RAM_Address55            0x3f

/******************************************************************************
                            时间参数屏蔽无效位宏定义                 
******************************************************************************/

#define Shield_secondBit			0x7f
#define Shield_minuteBit			0x7f
#define Shield_hourBit				0x3f
#define Shield_weekBit				0x07
#define Shield_dateBit				0x3f
#define Shield_monthBit				0x1f	

/******************************************************************************
                                  参数命令定义                      
******************************************************************************/

#define Control_Chip_Run            (0<<7)
#define Control_Chip_Stop           (1<<7)  //晶振也停止工作

#define Hour_Mode12                 (1<<6)  //12小时模式
#define Hour_Mode24                 (0<<6)  //24小时模式

#define Hour_AM                     (0<<5)  //上午
#define Hour_PM                     (1<<5)  //下午

#define SQWE_OUT_Hight              (1<<7)  //OUT位设置，频率输出打开时，设置1，SQW/OUT pin输出1，否则输出0
#define SQWE_OUT_Low                (0<<7)

#define SQWE_Disable                (0<<4)  //关闭频率输出
#define SQWE_Enable                 (1<<4)  //打开频率输出

#define CLKOUT_f1                   0x00	//输出1Hz
#define CLKOUT_f4096                0x01	//输出4.096KHz
#define CLKOUT_f8192                0x02	//输出8.192KHz
#define CLKOUT_f32768               0x03	//输出32.768KHz

//DS1338 and DS1338Z芯片的频率输出寄存器控制位

#if Chip_Type==0	//没定义则使用的是DS1338或者DS1338Z芯片

	#define OSF_Disable                 (1<<5)  //停止晶振
	#define OSF_Enable                  (0<<5)  //启动晶振

#endif

/******************************************************************************
                                外部功能函数
******************************************************************************/

void DS1307_Time_Init(Time_Typedef *TimeVAL);  //时间日历初始化

void DS1307_Write_Byte(uint8_t REG_ADD,uint8_t dat);  //DS1307某寄存器写入一个字节数据

uint8_t DS1307_Read_Byte(uint8_t REG_ADD);    //DS1307某寄存器读取一个字节数据

void DS1307_Operate_Register(uint8_t REG_ADD,uint8_t *pBuff,uint8_t num,uint8_t mode);  //DS1307对时间日历寄存器操作，写入数据或者读取数据

void DS1307_ReadWrite_Time(uint8_t mode);    //DS1307读取或者写入时间信息

uint8_t DS1307_Check(void);  //DS1307测试好坏

void DS1307_RAM_Write_Data(uint8_t* pBuff,uint8_t WRadd,uint8_t num);  //DS1307内置的RAM写数据操作

void DS1307_RAM_Read_Data(uint8_t* pBuff,uint8_t WRadd,uint8_t num);   //DS1307内置的RAM读数据操作



#endif  /* end ds1307.h */

