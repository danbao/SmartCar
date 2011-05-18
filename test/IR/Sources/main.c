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
  for(i=0;i<=7;i++) {
    delayms(300);
    if(i==7){
      i=0;sprintf(SCIreceive,"AD0值为:%f/n",ReadATD(0)/51.0);
    }
    else sprintf(SCIreceive,"AD%d值为:%f/n",i,ReadATD(i)/51.0);
    SCISend_chars(SCIreceive);
  //  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
