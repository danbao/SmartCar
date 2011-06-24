#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintf要用到
#include <string.h>      //LCD中的strlen要用到
#include <math.h>        //abs绝对值要用到
#include <stdlib.h>      //随机数用到
#include "main.h"
#include "LCD.h"         
#include "SCI.h" 
#include "IR.h"               




void main(void) {
	EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  SCI_Init();
  AD_Init(); //     AD初始化。
  DDRM = 0X1F;        //启动LCD
	LCD_start();  //初始化LCD模块 
	LCD_clear(); //清屏幕 
	
	LCD_startshow();

  for(;;) {
//  TestSMinfo();
  }
}
