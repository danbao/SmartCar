#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintf要用到
#include <string.h>      //LCD中的strlen要用到
#include <math.h>        //abs绝对值要用到
#include <stdlib.h>      //随机数用到
#include "main.h"           //所有变量的定义都放在main.h文件下了  
#include "LCD.h"         
#include "SCI.h" 
#include "IR.h"               



//===================采集红外进数组=======================//
void Collect_IR(void)
{
 IR_temp_laser_array[0]=ReadATD(0);
 delayMS();
 IR_temp_laser_array[1]=ReadATD(1);
 delayMS();
 IR_temp_laser_array[2]=ReadATD(2);
 delayMS();
 IR_temp_laser_array[3]=ReadATD(3);
 delayMS();
 IR_temp_laser_array[4]=ReadATD(4);
 delayMS();
 IR_temp_laser_array[5]=ReadATD(5);
 delayMS();
 IR_temp_laser_array[6]=ReadATD(6);
 
}

void main(void) {
	EnableInterrupts;
  Init_PLL();    //   设置时钟初始化。40MHz.
  SCI_Init();
  AD_Init(); //     AD初始化。
  for(;;) {
  Collect_IR();
  TestIR(IR_temp_laser_array,IR_position[1]);
  //  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
