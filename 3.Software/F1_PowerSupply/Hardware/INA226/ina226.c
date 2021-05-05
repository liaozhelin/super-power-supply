#include "ina226.h"
#include "my_iic.h"

INA226 INA226_data;

/**********************IIC_END*************************/

void INA226_Init(void)
{
    MYIIC_IIC_Init();
    HAL_Delay(10);
    //    INA226_SendData(INA226_ADDR1,CFG_REG,0xC000);

//    HAL_Delay(10);
    //uint16_t cfg_reg_value = 0x4000|(3<<9)|(4<<6)|(4<<3)|7;
//    INA226_SendData(INA226_ADDR1,CFG_REG,0x484f);
//    INA226_SendData(INA226_ADDR1,CAL_REG,0x0012);
    INA226_SendData(INA226_ADDR1,0x00,0x4727);
    INA226_SendData(INA226_ADDR1,0x05,0x800);//A00
}

void INA226_SendData(uint8_t addr,uint8_t reg,uint16_t data)
{
    uint8_t temp = 0;
    MYIIC_IIC_Start();
    MYIIC_IIC_Send_Byte(addr);
    MYIIC_IIC_Wait_Ack();
 
    MYIIC_IIC_Send_Byte(reg);
    MYIIC_IIC_Wait_Ack();
    
    temp = (uint8_t)(data>>8);
    MYIIC_IIC_Send_Byte(temp);
    MYIIC_IIC_Wait_Ack();
 
    temp = (uint8_t)(data&0x00FF);
    MYIIC_IIC_Send_Byte(temp);
    MYIIC_IIC_Wait_Ack();
    
    MYIIC_IIC_Stop();
}


void INA226_SetRegPointer(uint8_t addr,uint8_t reg)
{
    MYIIC_IIC_Start();
 
    MYIIC_IIC_Send_Byte(addr);
    MYIIC_IIC_Wait_Ack();
 
    MYIIC_IIC_Send_Byte(reg);
    MYIIC_IIC_Wait_Ack();
 
    MYIIC_IIC_Stop();
}


uint16_t INA226_ReadData(uint8_t addr)
{
    uint16_t temp=0;
    MYIIC_IIC_Start();
 
    MYIIC_IIC_Send_Byte(addr+1);
    MYIIC_IIC_Wait_Ack();
    
    temp = MYIIC_IIC_Read_Byte(1);
    temp<<=8;    
    temp |= MYIIC_IIC_Read_Byte(0);
    
    MYIIC_IIC_Stop();
    return temp;
}


long INA226_GetShunt_Current(uint8_t addr)
{
    long temp=0;    
    INA226_SetRegPointer(addr,CUR_REG);
    temp = INA226_ReadData(addr);
    if(temp&0x8000)    
    {
        temp = ~(temp - 1);    
            temp = (uint16_t)temp - 2 * (uint16_t)temp;
    }
	return temp;
}
 
//获取 id
uint16_t  INA226_Get_ID(uint8_t addr)
{
    uint32_t temp=0;
    INA226_SetRegPointer(addr,INA226_GET_ADDR);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}
 
//获取校准值
uint16_t INA226_GET_CAL_REG(uint8_t addr)
{    
    uint32_t temp=0;
    INA226_SetRegPointer(addr,CAL_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}
 
//1.25mV/bit
uint32_t INA226_GetVoltage(uint8_t addr)
{
    uint32_t temp=0;
    INA226_SetRegPointer(addr,BV_REG);
    temp = INA226_ReadData(addr);
    return (uint32_t)temp;    
}
 
 
 
//2.5uV/bit,感觉这个值是测不准的，所以下面改成2.2了
uint32_t INA226_GetShuntVoltage(uint8_t addr)
{
    uint32_t temp=0;
    INA226_SetRegPointer(addr,SV_REG);
    temp = INA226_ReadData(addr);
    if(temp&0x8000)    temp = ~(temp - 1);    
    return (uint32_t)temp;    
}
 
 
uint16_t INA226_Get_Power(uint8_t addr)
{
    int16_t temp=0;
    INA226_SetRegPointer(addr,PWR_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}
 
 
void GetVoltage(float *Voltage)//mV
{
    Voltage[0] = INA226_GetVoltage(INA226_ADDR1)*1.25f;
 //   printf("INA226_V = %.2f\r\n", Voltage[0]);
}
 
 
void Get_Shunt_voltage(float *Voltage)//uV
{
    Voltage[0] = (INA226_GetShuntVoltage(INA226_ADDR1)*2.2);//这里原来乘的系数是2.5
    
}
 
 
void Get_Shunt_Current(float *Current)//mA
{
    Current[0] = (INA226_GetShunt_Current(INA226_ADDR1)* 2.5f);
}
 
 
void GetPower(void)//W
{
    GetVoltage(&INA226_data.voltageVal);            //mV
    Get_Shunt_voltage(&INA226_data.Shunt_voltage);    //uV
    Get_Shunt_Current(&INA226_data.Shunt_Current);    //mA
    INA226_data.powerVal=INA226_data.voltageVal*0.001f * INA226_data.Shunt_Current*0.001f;
}
uint16_t read_dat;
float read_vol;
//float GetV(void)
//{
//    //电压采样
//    MYIIC_IIC_Start();
//    MYIIC_IIC_Send_Byte(0x80);
//    MYIIC_IIC_Wait_Ack();
//    MYIIC_IIC_Send_Byte(0x00);
//    MYIIC_IIC_Wait_Ack();
//    MYIIC_IIC_Send_Byte(0x47);
//    MYIIC_IIC_Wait_Ack();
//    MYIIC_IIC_Send_Byte(0x27);
//	MYIIC_IIC_Wait_Ack();
//	MYIIC_IIC_Stop();
//    HAL_Delay(1);    
//        
//	MYIIC_IIC_Start();
//    MYIIC_IIC_Send_Byte(0x81);
//    MYIIC_IIC_Wait_Ack();
//    read_dat = MYIIC_IIC_Read_Byte(1)<<8;
//    //IIC_Wait_Ack();
//    read_dat = read_dat + MYIIC_IIC_Read_Byte(0);
//    read_vol = 0.00125*read_dat;    
//    MYIIC_IIC_Stop();
//    return read_vol;
//}
