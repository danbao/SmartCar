#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */
#include <stdio.h>
#include "LCD.h"
unsigned char lcd[100];
void main(void)
{
	DDRM = 0X1F;        //����LCD
	LCD_start();  //��ʼ��LCDģ�� 
	LCD_clear(); //����Ļ 
//	LCD_startshow();
	//delay_nms(5000);
	LCD_clear(); 
  sprintf(lcd,"abcdefghijklmnopqrst");
	LCD_write_cizu(lcdy,lcdx,lcd);

	
  	while(1)
  	{	
  	delay_nms(30);
  	if(PTM_PTM5)LCD_write_cizu(lcdy,lcdx,"+");
  	else if(PTM_PTM6)LCD_write_cizu(lcdy,lcdx,"-");
  	else if(PTM_PTM7)LCD_write_cizu(lcdy,lcdx,"%");
  	}
}