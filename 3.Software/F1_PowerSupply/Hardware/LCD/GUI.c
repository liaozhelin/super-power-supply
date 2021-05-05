#include "gui.h"
#include "lcd.h"
#include "string.h"
#include "font.h" 
#include "spi.h"

void LCD_DrawLine(int x1, int y1, int x2, int y2){
	int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void LCD_DrawRectangle(int x1, int y1, int x2, int y2){
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}  

void LCD_DrawFillRectangle(int x1, int y1, int x2, int y2){
	//LCD_Fill(x1,y1,x2,y2,POINT_COLOR);
}

void _draw_circle_8(int xc, int yc, int x, int y){
	LCD_DrawPoint(xc + x, yc + y);
	LCD_DrawPoint(xc - x, yc + y);
	LCD_DrawPoint(xc + x, yc - y);
	LCD_DrawPoint(xc - x, yc - y);
	LCD_DrawPoint(xc + y, yc + x);
	LCD_DrawPoint(xc - y, yc + x);
	LCD_DrawPoint(xc + y, yc - x);
	LCD_DrawPoint(xc - y, yc - x);
}

void gui_circle(int xc, int yc,int c,int r, int fill){
	int x = 0, y = r, yi, d;
	d = 3 - 2 * r;
	if (fill) 
	{
		// 如果填充（画实心圆）
		while (x <= y) {
			for (yi = x; yi <= y; yi++)
				_draw_circle_8(xc, yc, x, yi);

			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	} else 
	{
		// 如果不填充（画空心圆）
		while (x <= y) {
			_draw_circle_8(xc, yc, x, y);
			if (d < 0) {
				d = d + 4 * x + 6;
			} else {
				d = d + 4 * (x - y) + 10;
				y--;
			}
			x++;
		}
	}
}

void Draw_Triangel(int x0,int y0,int x1,int y1,int x2,int y2){
	LCD_DrawLine(x0,y0,x1,y1);
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x2,y2,x0,y0);
}

static void _swap(int *a, int *b){
	int tmp;
    tmp = *a;
	*a = *b;
	*b = tmp;
}

void Fill_Triangel(int x0,int y0,int x1,int y1,int x2,int y2)
{
	int a, b, y, last;
	int dx01, dy01, dx02, dy02, dx12, dy12;
	long sa = 0;
	long sb = 0;
 	if (y0 > y1) 
	{
    _swap(&y0,&y1); 
		_swap(&x0,&x1);
 	}
 	if (y1 > y2) 
	{
    _swap(&y2,&y1); 
		_swap(&x2,&x1);
 	}
  if (y0 > y1) 
	{
    _swap(&y0,&y1); 
		_swap(&x0,&x1);
  }
	if(y0 == y2) 
	{ 
		a = b = x0;
		if(x1 < a)
    {
			a = x1;
    }
    else if(x1 > b)
    {
			b = x1;
    }
    if(x2 < a)
    {
			a = x2;
    }
		else if(x2 > b)
    {
			b = x2;
    }
		LCD_Fill(a,y0,b,y0,POINT_COLOR);
    return;
	}
	dx01 = x1 - x0;
	dy01 = y1 - y0;
	dx02 = x2 - x0;
	dy02 = y2 - y0;
	dx12 = x2 - x1;
	dy12 = y2 - y1;
	
	if(y1 == y2)
	{
		last = y1; 
	}
  else
	{
		last = y1-1; 
	}
	for(y=y0; y<=last; y++) 
	{
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
    sb += dx02;
    if(a > b)
    {
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) 
	{
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b)
		{
			_swap(&a,&b);
		}
		LCD_Fill(a,y,b,y,POINT_COLOR);
	}
}


void LCD_ShowChar(int x,int y,int fc, int bc, char num,char size,char mode){  
    char temp,t;
    int pos;
	//int colortemp=POINT_COLOR;      
		   
	num=num-' ';//得到偏移后的值
	if(!mode){ //非叠加方式
		LCD_SetWindows(x,y,x+(size/2)-1,y+size-1);//设置单个文字显示窗口
		if(size==64){
			num=(num+' '-'0');
			for(pos=0;pos<256;pos++){
				temp=font64[num][pos];
				for(t=0;t<8;t++){
					if(temp&0x01)Lcd_WriteData_16Bit(fc); 
					else Lcd_WriteData_16Bit(bc);
					temp>>=1; 
				}
			}
		}
		else if(size==32){
			for(pos=0;pos<64;pos++){
				temp=font32[num][pos];
				for(t=0;t<8;t++){
					if(temp&0x01)Lcd_WriteData_16Bit(fc); 
					else Lcd_WriteData_16Bit(bc); 
					temp>>=1; 
				}
			}
		}
		else{
			for(pos=0;pos<size;pos++){
				if(size==12)temp=asc2_1206[num][pos];//调用1206字体
				else if(size==16)temp=asc2_1608[num][pos];		 //调用1608字体
				for(t=0;t<size/2;t++){                 
					if(temp&0x01)Lcd_WriteData_16Bit(fc);  
					else Lcd_WriteData_16Bit(bc); 
					temp>>=1; 
					
				}
				
			}
		}
	}
	else//叠加方式
	{
		if(size<32)
		{
			for(pos=0;pos<size;pos++)
			{
				if(size==12)temp=asc2_1206[num][pos];//调用1206字体
				else if(size==16)temp=asc2_1608[num][pos];		 //调用1608字体
				for(t=0;t<8;t++)
				{   
					POINT_COLOR=fc;              
					if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//画一个点    
					temp>>=1; 
				}

			}
		}
		else
		{
			if(size==64)
			{
				num=(num+' '-'0');
				for(pos=0;pos<255;pos++)
				{
					temp=font64[num][pos];
					for(t=0;t<8;t++)
					{
						POINT_COLOR=fc; 
						if((temp&0x01)&&(pos%4==0))LCD_DrawPoint(x+t,y+(pos/4));//画一个点 
						else if((temp&0x01)&&(pos%4==1))LCD_DrawPoint(x+t+8,y+(pos/4));//画一个点 
						else if((temp&0x01)&&(pos%4==2))LCD_DrawPoint(x+t+16,y+(pos/4));//画一个点 
						else if((temp&0x01)&&(pos%4==3))LCD_DrawPoint(x+t+24,y+(pos/4));//画一个点 
						temp>>=1;
					}
				}
			}
			else if(size==32)
			{
				for(pos=0;pos<64;pos++)
				{
					temp=font32[num][pos];
					for(t=0;t<8;t++)
					{
						POINT_COLOR=fc; 
						if((temp&0x01)&&(pos%2==0))LCD_DrawPoint(x+t,y+(pos/2));//画一个点 
						else if((temp&0x01)&&(pos%2==1))LCD_DrawPoint(x+t+8,y+(pos/2));//画一个点 
						temp>>=1;
					}
				}
			}
		}
	}
	//POINT_COLOR=colortemp;	
	LCD_SetWindows(0,0,lcddev.width,lcddev.height);//恢复窗口为全屏     	   	 	  
}


void LCD_ShowString(int x,int y,char size,char *p,char mode)
{         
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {   
		if(x>(lcddev.width-1)||y>(lcddev.height-1)) 
		return;     
        LCD_ShowChar(x,y,POINT_COLOR,BACK_COLOR,*p,size,mode);
        x+=size/2;
        p++;
    }  
} 

uint32_t mypow(uint8_t m,uint8_t n){
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}

void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,POINT_COLOR,BACK_COLOR,temp+'0',size,0); 
	}
} 


void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
{
	uint8_t i,j;
	uint16_t k;
	uint16_t HZnum;
	uint16_t x0=x;
	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//自动统计汉字数目
	
			
	for (k=0;k<HZnum;k++) 
	{
	  if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
	  { 	
			LCD_SetWindows(x,y,x+15,y+15);
		    for(i=0;i<16*2;i++)
		    {
				for(j=0;j<8;j++)
		    	{	
					if(!mode) //非叠加方式
					{
						if(tfont16[k].Msk[i]&(0x80>>j))LCD_WR_DATA(fc);
						else LCD_WR_DATA(bc);
					}
					else
					{
						POINT_COLOR=fc;
						if(tfont16[k].Msk[i]&(0x80>>j))	LCD_DrawPoint(x,y);//画一个点
						x++;
						if((x-x0)==16)
						{
							x=x0;
							y++;
							break;
						}
					}

				}
				
			}
			
			
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
	LCD_SetWindows(0,0,lcddev.width,lcddev.height);//恢复窗口为全屏  
} 

void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t x_size,uint16_t y_size,const unsigned char *p) //显示40*40 QQ图片
{
  	int i; 
	uint16_t buf=0;
	LCD_SetWindows(x,y,x+x_size-1,y+y_size-1);//窗口设置
//    for(i=0;i<200*120;i++)
//	{	
//	 	picL=*(p+i*2);	//数据低位在前
//		picH=*(p+i*2+1);				
//		Lcd_WriteData_16Bit(picH<<8|picL);  						
//	}	
	for(i=0;i<x_size*y_size;i++)
	{	
		//LCD_RS_SET;
		buf=(*((p+i*2)+1)<<8) | *((p+i*2));
		//LCD_WR_DATA(buf);
		HAL_SPI_Transmit(&hspi1,(uint8_t *)&buf,2,10); 
	}	
	LCD_SetWindows(0,0,lcddev.width,lcddev.height);//恢复窗口为全屏  
}

void Show_Chart(uint16_t x,uint16_t y,uint16_t wide,uint16_t height,uint16_t *p){
	uint16_t i,buf;
	for(i=x;i<x+wide;i++){
		buf = *(p+i-x)/8;
		POINT_COLOR = 0x04E0;
		LCD_DrawLine(i,y,i,y-buf-1);
		POINT_COLOR = 0x07F8                                                               ;
		LCD_DrawLine(i,y-buf-1,i,y-buf);
		
	}
}

