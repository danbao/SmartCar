#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintfҪ�õ�
#include <string.h>      //LCD�е�strlenҪ�õ�
#include <math.h>        //abs����ֵҪ�õ�
#include "main.h"
#include "LCD.h"         
#include "SCI.h" 
#include "IR.h"               

 int i;




void main(void) {
	EnableInterrupts;
  SetBusCLK_40M();    //   ����ʱ�ӳ�ʼ����40MHz.
  SCI_Init();
  AD_Init(); //     AD��ʼ����
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
  for(i=0;i<=7;i++) {
    delayms(300);
    if(i==7){
      i=0;sprintf(SCIreceive,"AD0ֵΪ:%f/n",ReadATD(0)/51.0);
    }
    else sprintf(SCIreceive,"AD%dֵΪ:%f/n",i,ReadATD(i)/51.0);
    SCISend_chars(SCIreceive);
  //  _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
