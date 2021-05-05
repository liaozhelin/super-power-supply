#ifndef __GUI_H__
#define __GUI_H__

#include "stdint.h"

void LCD_DrawLine(int x1, int y1, int x2, int y2);
void LCD_DrawRectangle(int x1, int y1, int x2, int y2);
void LCD_DrawFillRectangle(int x1, int y1, int x2, int y2);
void _draw_circle_8(int xc, int yc, int x, int y);
void gui_circle(int xc, int yc,int c,int r, int fill);
void Draw_Triangel(int x0,int y0,int x1,int y1,int x2,int y2);
void Fill_Triangel(int x0,int y0,int x1,int y1,int x2,int y2);
void LCD_ShowChar(int x,int y,int fc, int bc, char num,char size,char mode);
void LCD_ShowString(int x,int y,char size,char *p,char mode);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);
void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode);
void Gui_Drawbmp16(uint16_t x,uint16_t y,uint16_t x_size,uint16_t y_size,const unsigned char *p);
void Show_Chart(uint16_t x,uint16_t y,uint16_t wide,uint16_t height,uint16_t *p);

#endif


