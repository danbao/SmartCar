#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>      //随机数用到
#define uchar 	unsigned char
#define uint 	unsigned int
#define LASER_MAX 12          //激光管数量
byte light_temp_laser_array[12]={1,0,1,0,1,0,1,1,1,0,0,0};
int IR_temp_laser_array[7]={130,0,200,0,255,100,150};
#include "LCD.h"

void main(void)
{
   uchar x;	
 // EnableInterrupts;
	LCD_init();  //初始化LCD模块 
//LCD_start();

  for(;;)
  	{ 
  	if (LCD_checkkey()==0x00) continue;
	   	else 
		{     LCD_clear();
          x= LCD_keyscan();
          LCD_write_zi(0,0,x);
    delay_nms(100);
		}
  	}
}