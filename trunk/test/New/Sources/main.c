#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "LCD.h"
#include "SCI.h"
void main(void) {
  EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
   SCI_Init();
DDRM = 0X1F;        //启动LCD
	LCD_start();  //初始化LCD模块 
	LCD_clear(); //清屏幕 
	LCD_startshow();
	LCD_clear(); //清屏幕 
	Prop1=123;
  Prop2=123;
  Diff1=123;
  Diff2=123;
  SpeedMax=1234;
  SpeedMin=-234; 
  for(;;) {
  sprintf(lcd,"P1:%d P2:%d\nD1:%d D2:%d\nSpeedMax:%d\nSpeedMin:%d",Prop1,Prop2,Diff1,Diff2,SpeedMax,SpeedMin);
	LCD_write_cizu(0,0,lcd);   
  }
 /* loop forever */
  /* please make sure that you never leave main */
}