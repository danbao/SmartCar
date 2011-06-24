#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintfҪ�õ�
#include <string.h>      //LCD�е�strlenҪ�õ�
#include <math.h>        //abs����ֵҪ�õ�
#include <stdlib.h>      //������õ�
#include "main.h"
#include "LCD.h"         
#include "SCI.h" 
#include "IR.h"               




void main(void) {
	EnableInterrupts;
  SetBusCLK_40M();    //   ����ʱ�ӳ�ʼ����40MHz.
  SCI_Init();
  AD_Init(); //     AD��ʼ����
  DDRM = 0X1F;        //����LCD
	LCD_start();  //��ʼ��LCDģ�� 
	LCD_clear(); //����Ļ 
	
	LCD_startshow();

  for(;;) {
//  TestSMinfo();
  }
}
