#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintfҪ�õ�
#include <string.h>      //LCD�е�strlenҪ�õ�
#include <math.h>        //abs����ֵҪ�õ�
#include <stdlib.h>      //������õ�
#include "main.h"           //���б����Ķ��嶼����main.h�ļ�����  
#include "LCD.h"         
#include "SCI.h" 
#include "IR.h"               



//===================�ɼ����������=======================//
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
  Init_PLL();    //   ����ʱ�ӳ�ʼ����40MHz.
  SCI_Init();
  AD_Init(); //     AD��ʼ����
  for(;;) {
  Collect_IR();
  TestIR(IR_temp_laser_array,IR_position[1]);
  //  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
