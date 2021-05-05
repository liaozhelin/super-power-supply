#include "sc8813.h"
#include "my_iic.h"
void SC8813_INIT(uint8_t addr)
{
	SC8813_SendData(addr,VBAT_SET,0X11);//3S电芯 4.2V单芯
	SC8813_SendData(addr,CTRL0_SET,0X04);//关OTG /VINREG 100X /300KHZ
	SC8813_SendData(addr,CTRL1_SET,0X01);//以IBUS电流为限制 /涓流充电开启/充电终止控制（自动）/OTG超功率保护/
	SC8813_SendData(addr,CTRL2_SET,0X01);//关闭PGGATE频率控制 /摆率2mv/us
	SC8813_SendData(addr,CTRL3_SET,0X22);//关闭PGGATE/GPO开漏输出/ADC转换开启/5khhz带宽/正常循环相应/折返电流模式/EOC门限为1（10）/PFM脉冲频率调制关闭	
	
}

void SC8813_SendData(uint8_t addr,uint8_t reg,uint8_t data)
{
    uint8_t temp = 0;
    MYIIC_IIC_Start();
    MYIIC_IIC_Send_Byte(addr);
    MYIIC_IIC_Wait_Ack();
 
    MYIIC_IIC_Send_Byte(reg);
    MYIIC_IIC_Wait_Ack();
    
    temp = data;
    MYIIC_IIC_Send_Byte(temp);
    MYIIC_IIC_Wait_Ack();
 
//    temp = (uint8_t)(data&0x00FF);
//    MYIIC_IIC_Send_Byte(temp);
//    MYIIC_IIC_Wait_Ack();
    
    MYIIC_IIC_Stop();
}

void SC8813_SetRegPointer(uint8_t addr,uint8_t reg)
{
    MYIIC_IIC_Start();
 
    MYIIC_IIC_Send_Byte(addr);
    MYIIC_IIC_Wait_Ack();
 
    MYIIC_IIC_Send_Byte(reg);
    MYIIC_IIC_Wait_Ack();
 
    MYIIC_IIC_Stop();
}

uint8_t SC8813_ReadData(uint8_t addr)
{
    uint8_t temp=0;
    MYIIC_IIC_Start();
 
    MYIIC_IIC_Send_Byte(addr+1);
    MYIIC_IIC_Wait_Ack();
    
    temp = MYIIC_IIC_Read_Byte(0);
//    temp<<=8;    
//    temp |= MYIIC_IIC_Read_Byte(0);
    
    MYIIC_IIC_Stop();
    return temp;
}

uint8_t temp[2];

uint16_t SC8813_Get_Data(uint8_t addr)
{
	
	uint16_t buf=0;
	SC8813_SetRegPointer(addr,0X0D);
	temp[0]=SC8813_ReadData(addr);
	SC8813_SetRegPointer(addr,0x0E);
	temp[1]=SC8813_ReadData(addr);
	buf = ((temp[0]*4) + temp[1]+1);
	return buf;
}
