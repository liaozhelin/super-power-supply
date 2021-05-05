#include "func.h"



#define  MAX_AJ_V 2500
#define  MIN_AJ_V 0
#define  MAX_AJ_I 3000
#define  MIN_AJ_I 0

sys SYS;
io IO;

uint16_t ADC_DATA[180];//8 * 20 转换 

void TIME_TASK(void){
	if(SYS.TIM.ADC_FLASH){
		//HAL_ADC_Start_DMA(&hadc,(uint32_t *)&ADC_DATA,200);
		//AVAGE();
		SYS.TIM.ADC_FLASH=0;
	}
	if(SYS.TIM.TIM_IO){
		 //SCAN_FUN();
		 SYS.TIM.TIM_IO=0;
	}
	if(SYS.TIM.TIM1S){
         
		 SYS.TIM.TIM1S=0;
	}	
	if(SYS.TIM.LCD_FLASH){
         INTERFACE_SHOW();
		 SYS.TIM.LCD_FLASH=0;
	}
}

void HARDWARE_INIT(void){
	/*GPIO初始化*/
	HAL_GPIO_WritePin(MOS_IN_GPIO_Port,MOS_IN_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOS_OUT_GPIO_Port,MOS_OUT_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LTC_EN_GPIO_Port,LTC_EN_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RELAY_EN_GPIO_Port,RELAY_EN_Pin,GPIO_PIN_RESET);
//	HAL_Delay(50);
//	HAL_GPIO_WritePin(RELAY_EN_GPIO_Port,RELAY_EN_Pin,GPIO_PIN_RESET);
	SPI1->CR2 |= 0X4;//修复SPI1与TIM2同时使用冲突的官方BUG
	
	/*DAC初始化*/
	SET_DAC_VAL(DAC_CHANNEL_1,0.8);
	SET_DAC_VAL(DAC_CHANNEL_2,0.8);
	
	/*ADC初始化*/
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&ADC_DATA,180);//ADC DMA
	
	/*定时器初始化*/
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);//EC11
	TIM3->CCR1 = 100;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	
	LED.LED_COLOR(BLACK_,100);
	
	
	/*I2C外设初始化*/
	INA226_Init();
	SC8813_INIT(SC8813_ADDR);
	/*UART外设初始化*/
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_TC);
	HAL_UART_Receive_DMA(&huart1,(uint8_t*)receive_buf,255);
}

void SOFTWARE_INIT(void){
	/*LCD初始化*/
	LCD_Init();
	INTERFACE_SHOW();
	
	/*结构体初始化*/
	IO.ADCVI.V_OUT=0;
	IO.ADCVI.I_OUT=0;
	IO.ADCVI.P_OUT=0;
	SYS.Status.BEEP=0;
	IO.DACIV.AJ_FLAG=0X21;
	SYS.TIM.LOCK_IV=0;
	HAL_TIM_Base_Start_IT(&htim6);//TIME6
//	TIM3->CCR2 = 0;
//	TIM3->CCR3 = 0;
//	TIM3->CCR4 = 0;
	BEEP(3000,1,70);
	BEEP(5000,1,70);
	BEEP(3000,1,70);
	
}

HAL_StatusTypeDef USER_ADC_SetValue(DAC_HandleTypeDef* hdac, uint32_t Channel, double CValue)
{
	uint32_t Data=0;
	
	if(CValue>3.3)
		return HAL_ERROR;
	
	CValue=CValue/3.3;
	Data=CValue*4096;
	
	return HAL_DAC_SetValue(hdac, Channel, DAC_ALIGN_12B_R, Data);
}

void SET_DAC_VAL(uint16_t CHANNEL,double VAL)//DAC_CHANNEL_1//DAC_CHANNEL_2
{
	if(USER_ADC_SetValue(&hdac, CHANNEL,VAL)!=HAL_OK)
	{
		Error_Handler();
	}
	HAL_DAC_Start(&hdac, CHANNEL);
}


void INTERFACE_SHOW(void)
{
 	//char BUF[20]="";
	/*分割*/
	
	POINT_COLOR=0x045F;
	LCD_DrawLine(0,220,319,220);
	LCD_DrawLine(0,20,319,20);
	LCD_DrawLine(170,20,170,220);
	LCD_DrawLine(170,90,319,90);
	LCD_DrawLine(197,20,197,90);
	LCD_DrawLine(170,155,319,155);
	/*页眉信息*/
	POINT_COLOR=0x07FF;
	GUI_DrawFont16(0,0,POINT_COLOR,BACK_COLOR,(uint8_t *)"输",1);
	GUI_DrawFont16(16,0,POINT_COLOR,BACK_COLOR,(uint8_t *)"入",1);
	GUI_DrawFont16(100,0,POINT_COLOR,BACK_COLOR,(uint8_t *)"时",1);
	GUI_DrawFont16(116,0,POINT_COLOR,BACK_COLOR,(uint8_t *)"间",1);
	
	/*页脚信息*/
	GUI_DrawFont16(0,224,POINT_COLOR,BACK_COLOR,(uint8_t *)"运",1);
	GUI_DrawFont16(16,224,POINT_COLOR,BACK_COLOR,(uint8_t *)"行",1);

	GUI_DrawFont16(120,224,POINT_COLOR,BACK_COLOR,(uint8_t *)"放",1);
	GUI_DrawFont16(136,224,POINT_COLOR,BACK_COLOR,(uint8_t *)"电",1);
	
    /*预设电压电流信息*/
	GUI_DrawFont16(177,30,POINT_COLOR,BACK_COLOR,(uint8_t *)"预",1);
	GUI_DrawFont16(177,65,POINT_COLOR,BACK_COLOR,(uint8_t *)"设",1);


	/*电压，电流，功率信息*/
	/*电压信息*/
	POINT_COLOR=0x04E0;
	gui_circle(67,80,POINT_COLOR,3,1);//电压信息小数点
	LCD_ShowChar(133,30,POINT_COLOR,BACK_COLOR,'9'+1,64,1);//电压单位V   
	
	/*电流信息*/
	POINT_COLOR=0xFFE0;
	gui_circle(35,140,POINT_COLOR,3,1);
	LCD_ShowChar(133,90,POINT_COLOR,BACK_COLOR,'9'+2,64,1);//电流单位A    
	
	/*功率信息*/
	POINT_COLOR=0x880F;
	gui_circle(67,200,POINT_COLOR,3,1);
	LCD_ShowChar(133,150,POINT_COLOR,BACK_COLOR,'9'+3,64,1);//功率单位W
	/*设置信息*/
	//电压设置单位、小数点
	LCD_ShowChar(304,22,0X04E0,0X0000,'V',32,0);
	LCD_ShowChar(256,22,0X04E0,0X0000,'.',32,0);
	
	//电流设置单位、小数点
	LCD_ShowChar(304,55,0xFFE0,0X0000,'A',32,0);
	LCD_ShowChar(240,55,0xFFE0,0X0000,'.',32,0);

	
	//电流设置
//	POINT_COLOR=0xFFE0;
//	sprintf(BUF,"%d.",IO.DACIV.DAC_I/1000);
//	LCD_ShowString(224,55,32,BUF,0);
//	sprintf(BUF,"%d",IO.DACIV.DAC_I/100%10);
//	LCD_ShowString(256,55,32,BUF,0);
//	sprintf(BUF,"%d",IO.DACIV.DAC_I/10%10);
//	LCD_ShowString(272,55,32,BUF,0);
//	sprintf(BUF,"%dA",IO.DACIV.DAC_I%10);
//	LCD_ShowString(288,55,32,BUF,0);
	
//	ADJUST_IV();
//	POINT_COLOR=0x07FF;
//	LCD_ShowString(180,190,16,"M1",1);
	
}

u16 BUF_VOUT[140],BUF_IOUT[140];

void UPDATA_SHOW(void){
	char BUF[20]="";
	static u16 time=0; 
	ADJUST_IV();
	/*输出电压电流功率更新*/
	
	IO.ADCVI.V_OUT=(uint16_t)((float)INA226_GetVoltage(0x80)*1.25f)/10;
	IO.ADCVI.I_OUT=(uint16_t)(float)INA226_GetShuntVoltage(0x80);
	IO.ADCVI.P_OUT=(uint16_t)(float)INA226_Get_Power(0x80);
	
	BUF_VOUT[time]=IO.ADCVI.V_OUT;
	BUF_IOUT[time]=IO.ADCVI.I_OUT;
	time =(time>139?0:time+1);
	
	
	if(SYS.Status.OUTPUT & 0X80){
		SYS.Status.OUTPUT&=0X7F;
		if(SYS.Status.OUTPUT & 0X01){
			HAL_GPIO_WritePin(RELAY_EN_GPIO_Port,RELAY_EN_Pin,GPIO_PIN_SET);
			BEEP(2500,1,40);
			TIM3->CCR2 = 0;
			TIM3->CCR3 = 0;
			TIM3->CCR4 = 100;
			POINT_COLOR = 0x07FF;
			BACK_COLOR = 0XF800;
			LCD_ShowString(254,224,16," OUTPUT ",0);//输出指示
			
		}else{
			HAL_GPIO_WritePin(RELAY_EN_GPIO_Port,RELAY_EN_Pin,GPIO_PIN_RESET);
			BEEP(1000,2,20);
			TIM3->CCR2 = 0;
			TIM3->CCR3 = 0;
			TIM3->CCR4 = 0;
			POINT_COLOR = 0x07FF;
			BACK_COLOR = 0X0000;
			LCD_ShowString(254,224,16," OUTPUT ",0);//电量信息
		}
	}
	
	/*页眉信息*/
	POINT_COLOR=0x07FF;
	BACK_COLOR = 0X0000;
	sprintf(BUF,"%.2fV",(float)IO.ADCVI.V_IN/100);//输入电压
	LCD_ShowString(35,0,16,BUF,0);
	LCD_ShowString(135,0,16,"2020-6-23 18:20:02 Wed",0);//当前时间
	/*页脚信息*/
	sprintf(BUF,"%02d:%02d:%02d",IO.RUN.HOUR,IO.RUN.MINUTE,IO.RUN.SECOND);//运行时间信息
	LCD_ShowString(35,224,16,BUF,0);//运行时间信息
	LCD_ShowString(155,224,16,"0000mAH",0);//电量信息
	
	//电压高亮设置
	if(IO.DACIV.AJ_FLAG & 0X40){
		switch(IO.DACIV.AJ_FLAG&0X0F){
			case 1:{
				LCD_ShowChar(224,22,0X04E0,0X0000,IO.DACIV.DAC_V/1000+0X30,32,0);
				LCD_ShowChar(240,22,0X04E0,0X0000,IO.DACIV.DAC_V/100%10+0X30,32,0);
				LCD_ShowChar(272,22,0X04E0,0X0000,IO.DACIV.DAC_V/10%10+0X30,32,0);
				LCD_ShowChar(288,22,0X0000,0X04E0,IO.DACIV.DAC_V%10+0X30,32,0);
				if(IO.DACIV.DAC_V+ENC>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+ENC<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += ENC;
				break;
			}
			case 2:{
				LCD_ShowChar(224,22,0X04E0,0X0000,IO.DACIV.DAC_V/1000+0X30,32,0);
				LCD_ShowChar(240,22,0X04E0,0X0000,IO.DACIV.DAC_V/100%10+0X30,32,0);
				LCD_ShowChar(272,22,0X0000,0X04E0,IO.DACIV.DAC_V/10%10+0X30,32,0);
				LCD_ShowChar(288,22,0X04E0,0X0000,IO.DACIV.DAC_V%10+0X30,32,0);
				if(IO.DACIV.DAC_V+(ENC*10)>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+(ENC*10)<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += (ENC*10);
				break;
			}
			case 3:{
				LCD_ShowChar(224,22,0X04E0,0X0000,IO.DACIV.DAC_V/1000+0X30,32,0);
				LCD_ShowChar(240,22,0X0000,0X04E0,IO.DACIV.DAC_V/100%10+0X30,32,0);
				LCD_ShowChar(272,22,0X04E0,0X0000,IO.DACIV.DAC_V/10%10+0X30,32,0);
				LCD_ShowChar(288,22,0X04E0,0X0000,IO.DACIV.DAC_V%10+0X30,32,0);
				if(IO.DACIV.DAC_V+(ENC*100)>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+(ENC*100)<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += (ENC*100);
				break;
			}
			case 4:{
				LCD_ShowChar(224,22,0X0000,0X04E0,IO.DACIV.DAC_V/1000+0X30,32,0);
				LCD_ShowChar(240,22,0X04E0,0X0000,IO.DACIV.DAC_V/100%10+0X30,32,0);
				LCD_ShowChar(272,22,0X04E0,0X0000,IO.DACIV.DAC_V/10%10+0X30,32,0);
				LCD_ShowChar(288,22,0X04E0,0X0000,IO.DACIV.DAC_V%10+0X30,32,0);
				if(IO.DACIV.DAC_V+(ENC*1000)>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+(ENC*1000)<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += (ENC*1000);
				break;
			}
		}
	}
	else{
		LCD_ShowChar(224,22,0X04E0,0X0000,IO.DACIV.DAC_V/1000+0X30,32,0);
		LCD_ShowChar(240,22,0X04E0,0X0000,IO.DACIV.DAC_V/100%10+0X30,32,0);
		LCD_ShowChar(272,22,0X04E0,0X0000,IO.DACIV.DAC_V/10%10+0X30,32,0);
		LCD_ShowChar(288,22,0X04E0,0X0000,IO.DACIV.DAC_V%10+0X30,32,0);
	}
	
	//电流高亮设置
	if(IO.DACIV.AJ_FLAG & 0X80){
		switch(IO.DACIV.AJ_FLAG&0X0F){
			case 1:{
				LCD_ShowChar(224,55,0xFFE0,0X0000,IO.DACIV.DAC_I/1000+0X30,32,0);
				LCD_ShowChar(256,55,0xFFE0,0X0000,IO.DACIV.DAC_I/100%10+0X30,32,0);
				LCD_ShowChar(272,55,0xFFE0,0X0000,IO.DACIV.DAC_I/10%10+0X30,32,0);
				LCD_ShowChar(288,55,0X0000,0xFFE0,IO.DACIV.DAC_I%10+0X30,32,0);
				if(IO.DACIV.DAC_I+ENC>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+ENC<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += ENC;
				break;
			}
			case 2:{
				LCD_ShowChar(224,55,0xFFE0,0X0000,IO.DACIV.DAC_I/1000+0X30,32,0);
				LCD_ShowChar(256,55,0xFFE0,0X0000,IO.DACIV.DAC_I/100%10+0X30,32,0);
				LCD_ShowChar(272,55,0X0000,0xFFE0,IO.DACIV.DAC_I/10%10+0X30,32,0);
				LCD_ShowChar(288,55,0xFFE0,0X0000,IO.DACIV.DAC_I%10+0X30,32,0);
				if(IO.DACIV.DAC_I+(ENC*10)>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+(ENC*10)<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += (ENC*10);
				break;
			}
			case 3:{
				LCD_ShowChar(224,55,0xFFE0,0X0000,IO.DACIV.DAC_I/1000+0X30,32,0);
				LCD_ShowChar(256,55,0X0000,0xFFE0,IO.DACIV.DAC_I/100%10+0X30,32,0);
				LCD_ShowChar(272,55,0xFFE0,0X0000,IO.DACIV.DAC_I/10%10+0X30,32,0);
				LCD_ShowChar(288,55,0xFFE0,0X0000,IO.DACIV.DAC_I%10+0X30,32,0);
				if(IO.DACIV.DAC_I+(ENC*100)>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+(ENC*100)<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += (ENC*100);
				break;
			}
			case 4:{
				LCD_ShowChar(224,55,0X0000,0xFFE0,IO.DACIV.DAC_I/1000+0X30,32,0);
				LCD_ShowChar(256,55,0xFFE0,0X0000,IO.DACIV.DAC_I/100%10+0X30,32,0);
				LCD_ShowChar(272,55,0xFFE0,0X0000,IO.DACIV.DAC_I/10%10+0X30,32,0);
				LCD_ShowChar(288,55,0xFFE0,0X0000,IO.DACIV.DAC_I%10+0X30,32,0);
				if(IO.DACIV.DAC_I+(ENC*1000)>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+(ENC*1000)<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += (ENC*1000);
				break;
			}
		}
	}
	else{
		LCD_ShowChar(224,55,0xFFE0,0X0000,IO.DACIV.DAC_I/1000+0X30,32,0);
		LCD_ShowChar(256,55,0xFFE0,0X0000,IO.DACIV.DAC_I/100%10+0X30,32,0);
		LCD_ShowChar(272,55,0xFFE0,0X0000,IO.DACIV.DAC_I/10%10+0X30,32,0);
		LCD_ShowChar(288,55,0xFFE0,0X0000,IO.DACIV.DAC_I%10+0X30,32,0);
	}
	__HAL_TIM_SET_COUNTER(&htim4,0);
	//电压显示UPDATA
	LCD_ShowChar(0,30,0x04E0,0X0000,IO.ADCVI.V_OUT/1000+0X30,64,0);
	LCD_ShowChar(32,30,0x04E0,0X0000,IO.ADCVI.V_OUT/100%10+0X30,64,0);
	LCD_ShowChar(70,30,0x04E0,0X0000,IO.ADCVI.V_OUT/10%10+0X30,64,0);
	LCD_ShowChar(102,30,0x04E0,0X0000,IO.ADCVI.V_OUT%10+0X30,64,0);
	//电流显示UPDATA
	LCD_ShowChar(0,90,0xFFE0,0X0000,IO.ADCVI.I_OUT/1000+0X30,64,0);
	LCD_ShowChar(38,90,0xFFE0,0X0000,IO.ADCVI.I_OUT/100%10+0X30,64,0);
	LCD_ShowChar(70,90,0xFFE0,0X0000,IO.ADCVI.I_OUT/10%10+0X30,64,0);
	LCD_ShowChar(102,90,0xFFE0,0X0000,IO.ADCVI.I_OUT%10+0X30,64,0);
	//功率显示UPDATA
	LCD_ShowChar(0,150,0x880F,0X0000,IO.ADCVI.P_OUT/1000+0X30,64,0);
	LCD_ShowChar(32,150,0x880F,0X0000,IO.ADCVI.P_OUT/100%10+0X30,64,0);
	LCD_ShowChar(70,150,0x880F,0X0000,IO.ADCVI.P_OUT/10%10+0X30,64,0);
	LCD_ShowChar(102,150,0x880F,0X0000,IO.ADCVI.P_OUT%10+0X30,64,0);
}


void ADJUST_IV(void){
	static int16_t BUF_ENC;
	if(SYS.TIM.LOCK_IV > 10){
		SYS.TIM.LOCK_IV=0;
		IO.DACIV.AJ_FLAG = 0X21;//标志位清除
	}
	if(BUF_ENC!=ENC){
		SYS.TIM.LOCK_IV=1;
	}
	if(IO.DACIV.AJ_FLAG & 0X40){
//		if(IO.DACIV.AJ_FLAG & 0X10){
//			IO.DACIV.AJ_FLAG &= 0XF0;
//			IO.DACIV.AJ_FLAG |= 0X01;
//		}
//		if(KEY_BUF != IO.DACIV.AJ_FLAG&0X0F){
			POINT_COLOR=0x07FF;
			gui_circle(210,35,POINT_COLOR,7,1);
			POINT_COLOR=0x0000;
			gui_circle(210,72,POINT_COLOR,7,1);
//			LCD_DrawRectangle(224,85,288+15,85+1);
//			LCD_DrawRectangle(224,52,288+15,52+1);
//			POINT_COLOR=0xF81F;
//		}
//		switch(IO.DACIV.AJ_FLAG&0X0F){
//			case 1:LCD_DrawRectangle(288,52,288+15,52+1);if(IO.DACIV.DAC_V+ENC>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+ENC<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += ENC;break;
//			case 2:LCD_DrawRectangle(272,52,272+15,52+1);if(IO.DACIV.DAC_V+(ENC*10)>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+(ENC*10)<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += (ENC*10);break;
//			case 3:LCD_DrawRectangle(240,52,240+15,52+1);if(IO.DACIV.DAC_V+(ENC*100)>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+(ENC*100)<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += (ENC*100);break;
//			case 4:LCD_DrawRectangle(224,52,224+15,52+1);if(IO.DACIV.DAC_V+(ENC*1000)>MAX_AJ_I)IO.DACIV.DAC_V=MAX_AJ_I;else if(IO.DACIV.DAC_V+(ENC*1000)<MIN_AJ_I)IO.DACIV.DAC_V=MIN_AJ_I;else IO.DACIV.DAC_V += (ENC*1000);break;
//		}
//		IO.DACIV.AJ_FLAG &= 0XEF;//将第五位置0
//		TIM4 -> CNT = 0;
//		__HAL_TIM_SET_COUNTER(&htim4,0);
	}
	else if(IO.DACIV.AJ_FLAG & 0X80){	
//		if(!(IO.DACIV.AJ_FLAG & 0X10)){
//			IO.DACIV.AJ_FLAG &= 0XF0;
//			IO.DACIV.AJ_FLAG |= 0X01;
//		}
//		if(KEY_BUF != IO.DACIV.AJ_FLAG&0X0F){
			POINT_COLOR=0x07FF;
			gui_circle(210,72,POINT_COLOR,7,1);
			POINT_COLOR=0x0000;
			gui_circle(210,35,POINT_COLOR,7,1);
//			LCD_DrawRectangle(224,85,288+15,85+1);
//			LCD_DrawRectangle(224,52,288+15,52+1);
			
//		}
//		POINT_COLOR=0xF81F;
//		switch(IO.DACIV.AJ_FLAG&0X0F){
//			case 1:LCD_DrawRectangle(288,85,288+15,85+1);if(IO.DACIV.DAC_I+ENC>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+ENC<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += ENC;break;
//			case 2:LCD_DrawRectangle(272,85,272+15,85+1);if(IO.DACIV.DAC_I+(ENC*10)>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+(ENC*10)<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += (ENC*10);break;
//			case 3:LCD_DrawRectangle(256,85,256+15,85+1);if(IO.DACIV.DAC_I+(ENC*100)>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+(ENC*100)<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += (ENC*100);break;
//			case 4:LCD_DrawRectangle(224,85,224+15,85+1);if(IO.DACIV.DAC_I+(ENC*1000)>MAX_AJ_I)IO.DACIV.DAC_I=MAX_AJ_I;else if(IO.DACIV.DAC_I+(ENC*1000)<MIN_AJ_I)IO.DACIV.DAC_I=MIN_AJ_I;else IO.DACIV.DAC_I += (ENC*1000);break;
//		}
//		IO.DACIV.AJ_FLAG |= 0X10;//将第五位置1
//		TIM4 -> CNT = 0;
//		__HAL_TIM_SET_COUNTER(&htim4,0);
	}
	if(IO.DACIV.AJ_FLAG & 0X20){
		POINT_COLOR=0x0000;
		gui_circle(210,72,POINT_COLOR,7,1);
		gui_circle(210,35,POINT_COLOR,7,1);
//		LCD_DrawRectangle(224,85,288+15,85+1);
//		LCD_DrawRectangle(224,52,288+15,52+1);
	}
	BUF_ENC=ENC;
//	KEY_BUF=IO.DACIV.AJ_FLAG&0X0F;
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	//超时检测还没写
	//======ENC_KEY======//
	uint8_t BUF;
	uint16_t i;
	SYS.TIM.LOCK_IV=1;
	if(GPIO_Pin == ENC_KEY_Pin){
		//for(i=0;i<65535;i++){}
		if(!HAL_GPIO_ReadPin(ENC_KEY_GPIO_Port,ENC_KEY_Pin))
		if(IO.DACIV.AJ_FLAG & 0XC0)
		{
			SYS.TIM.LOCK_IV=1;
			BUF = (IO.DACIV.AJ_FLAG & 0X0F);
			IO.DACIV.AJ_FLAG &= 0XF0;
			IO.DACIV.AJ_FLAG += BUF;
		}
	}
	//======LEFT_KEY======//
    else if(GPIO_Pin == KEY1_Pin){ 
		for(i=0;i<65535;i++){}
		if(!HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)){
			for(i=0;i<65535;i++){}
			if(!HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)){
				BUF = (IO.DACIV.AJ_FLAG & 0X0F);
				BUF=(BUF>3?1:BUF+1);
				IO.DACIV.AJ_FLAG &= 0XF0;
				IO.DACIV.AJ_FLAG += BUF;			
			}
		}
	}
	//======A/V_KEY======//
	else if(GPIO_Pin == KEY2_Pin){
		for(i=0;i<65535;i++){}
		if(!HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)){
			for(i=0;i<65535;i++){}
			if(!HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)){
				static uint8_t flag=0;
				if(IO.DACIV.AJ_FLAG & 0x20){flag=1;IO.DACIV.AJ_FLAG &= 0XDF;}
				if(flag==1){IO.DACIV.AJ_FLAG &= 0X3F;IO.DACIV.AJ_FLAG |= 0X40;flag=2;}
				else if(flag==2){IO.DACIV.AJ_FLAG &= 0X3F;IO.DACIV.AJ_FLAG |= 0X80;flag=1;}
			}

		}
	}
	//======RIGHT_KEY======//
	else if(GPIO_Pin == KEY3_Pin){
		for(i=0;i<65535;i++){}
		if(!HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)){
			for(i=0;i<65535;i++){}
			if(!HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)){
				BUF = (IO.DACIV.AJ_FLAG & 0X0F);
				BUF=(BUF<2?4:BUF-1);
				IO.DACIV.AJ_FLAG &= 0XF0;
				IO.DACIV.AJ_FLAG += BUF;			
			}
		}
		
	}
	//======OUTPUT_KEY======//
	else if(GPIO_Pin == KEY4_Pin){ 
		for(i=0;i<65535;i++){}
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)==0){
			SYS.Status.OUTPUT |= 0X80;
			if(SYS.Status.OUTPUT&0X01)SYS.Status.OUTPUT&=0XFE;
			else SYS.Status.OUTPUT|=0X01;
			
		}
		
	}
	//__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
}
unsigned int CNT;
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//	if(htim->Instance==TIM6)//1MS中断
//	{
//		if(CNT%10==0){
//			SYS.TIM.ADC_FLASH=1;
//		}
//		if(CNT%50==0){
//			SYS.TIM.TIM_IO=1;
//		}
//		if(CNT%200==0){
//			SYS.TIM.LCD_FLASH=1;
//		}
//		if(CNT==1000){
//			SYS.TIM.TIM1S=1;
//			if(SYS.TIM.LOCK_IV){
//				SYS.TIM.LOCK_IV+=1;
//			}
//			if((IO.RUN.SECOND+1)>59){
//				IO.RUN.SECOND=0;
//				if((IO.RUN.MINUTE+1)>59){
//					IO.RUN.MINUTE=0;
//					if((IO.RUN.HOUR+1)>23){
//						IO.RUN.HOUR=0;
//					}
//					else{
//						IO.RUN.HOUR+=1;
//					}
//				}
//				else{
//					IO.RUN.MINUTE+=1;
//				}
//			}
//			else{
//				IO.RUN.SECOND+=1;
//			}
//		}
//		CNT=(CNT>1000?0:CNT+1);
//	}
//}

void BEEP(uint16_t freq,uint16_t repeat,uint16_t time)
{
	if(SYS.Status.BEEP)
	{
		freq = 720000 / freq;
		TIM2->PSC = freq;
		while(repeat--)
		{
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
			HAL_Delay(time);
			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1); //PWM 
			HAL_Delay(time);
		}
		HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
	}
}

//uint32_t ADC_MIX[4];
//void AVAGE(void){
//	uint8_t i,j;
//    for(j=0;j<4;j++){
//		for(i=0;i<50;i++){
//			ADC_MIX[j]+=ADC_DATA[(i*4)+j];
//		}
//	}
//	for(j=0;j<4;j++){
//		ADC_MIX[j]/=50;
//	}
//	IO.ADCVI.V_OUT=(uint16_t)(((float)ADC_MIX[0]/11.5)*10);
//	IO.ADCVI.I_OUT=(uint16_t)((float)ADC_MIX[1]/1.32);
//	IO.ADCVI.V_IN=(uint16_t)(((float)ADC_MIX[2]/11.4)*10);
////	IO.ADCVI.IN_TEMP=(float)((ADC_MIX[3]*3300/4096-1400)/2.5+25);M
//	IO.ADCVI.P_OUT=(uint16_t)(((float)IO.ADCVI.V_OUT/100 * (float)IO.ADCVI.I_OUT/1000)*100);
//}



