#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintf要用到
#include <string.h>      //LCD中的strlen要用到
#include <math.h>        //abs绝对值要用到
#include "main.h"
#include "LCD.h"         
#include "SCI.h" 
#include "IR.h"               

 int i;




void main(void) {
	EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  SCI_Init();
  AD_Init(); //     AD初始化。
  DDRM = 0X1F;        //启动LCD
	LCD_start();  //初始化LCD模块 
	LCD_clear(); //清屏幕 
	LCD_startshow();
	Prop1=123.45;
  Prop2=-123.45;
  Diff1=-123;
  Diff2=123;
  SpeedMax=1234;
  SpeedMin=0; 
  SpeedNow=345;
  SpeedAver=467.96;
  for(;;) {
    delayms(300);
    sprintf(SCIreceive,"AD值为:%.3d  %.3d  %.3d  %.3d  %.3d  %.3d  %.3d",ReadATD(6),ReadATD(5),ReadATD(4),ReadATD(3),ReadATD(2),ReadATD(1),ReadATD(0));
    SCISend_chars(SCIreceive);
  //  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
