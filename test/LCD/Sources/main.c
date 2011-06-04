#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */
#include <stdio.h>
#include <string.h>
#define uchar 	unsigned char
#define uint 	unsigned int
#include "LCD.h"
void main(void)
{
	LCD_init();  //³õÊ¼»¯LCDÄ£¿é 
	LCD_start();
  LCD_show();
  	while(1)
  	{	
    LCD_determine();
  	}
}