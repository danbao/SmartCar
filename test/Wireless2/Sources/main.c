#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintfҪ�õ�
#include <string.h>      //LCD�е�strlenҪ�õ�
#include <math.h>        //abs����ֵҪ�õ�
#include "main.h"
#include "LCD.h"         
#include "SCI.h"               






void main(void) {
	EnableInterrupts;
  SetBusCLK_40M();    //   ����ʱ�ӳ�ʼ����40MHz.
  SCI_Init();
  DDRM = 0X1F;        //����LCD
	LCD_start();  //��ʼ��LCDģ�� 
	LCD_clear(); //����Ļ 
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
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
