#include "LED.h"


LED_TypeDef LED = {LED_COLOR};

void LED_COLOR(uint8_t IS_COLOR,uint8_t CCR){
	CCR=(CCR>100?100:CCR);
	CCR=(CCR<0?0:CCR);
	switch(IS_COLOR){
		case RED_:{
			LEDR = CCR;
			LEDG = 0;
			LEDB = 0;
			break;
		}
		case GREEN_:{
			LEDR = 0;
			LEDG = CCR;
			LEDB = 0;
			break;
		}
		case BLUE_:{
			LEDR = 0;
			LEDG = 0;
			LEDB = CCR;
			break;
		}
		case PINK_:{
			LEDR = CCR;
			LEDG = 0;
			LEDB = CCR;			
			break;
		}
		case YELLOW_:{
			LEDR = CCR;
			LEDG = CCR;
			LEDB = 0;
			break;
		}
		case CYAN_:{
			LEDR = 0;
			LEDG = CCR;
			LEDB = CCR;
			break;
		}
		case WHITE_:{
			LEDR = CCR;
			LEDG = CCR;
			LEDB = CCR;
			break;
		}
		default:{
			LEDR = 0;
			LEDG = 0;
			LEDB = 0;
			break;
		}
			
	}
}





