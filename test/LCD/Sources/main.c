#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>      //������õ�
#define uchar 	unsigned char
#define uint 	unsigned int
#define LASER_MAX 12          //���������
byte light_temp_laser_array[12]={1,0,1,0,1,0,1,1,1,0,0,0};
int IR_temp_laser_array[7]={130,0,200,0,255,100,150};
#include "LCD.h"

void main(void)
{
 // EnableInterrupts;
	LCD_init();  //��ʼ��LCDģ�� 
LCD_start();
	delay_nms(5000);
  LCD_show();
  for(;;)
  	{	
  	LCD_determine();
}
}