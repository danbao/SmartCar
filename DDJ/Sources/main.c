#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintfҪ�õ�
#include <string.h>      //LCD�е�strlenҪ�õ�
#include <math.h>        //abs����ֵҪ�õ�
#include <stdlib.h>      //������õ�
#include "main.h"           //���б����Ķ��嶼����main.h�ļ�����           
#include "dealinfo.h"
#include "control.h"  
#include "SCI.h"
#include "IR.h" 
/* ================= SendSmartcarInfo ====================
      desc: SCI���ڷ��͵�ǰ����ܲɼ���Ϣ
      pre:  1��ǰ����ܲɼ����飬2��ǰ�����״̬
      Post: ��
       
*/ 

void main(void) 
{

 // int temp_laserStatus;           //����һ�������������� ���¶��ֵ
  DisableInterrupts;
  SetBusCLK_40M();    //   ����ʱ�ӳ�ʼ����40MHz.
  PITInit();          //PIT��ʼ
  PWM_Init();
  LIGHT_Init();
  SCI_Init();
  Tect_Speed_Init();    //ECT ��׽��ʼ
  AD_Init(); 
  delayms(3000);

  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
 Collect_IR();   //�����ȡ
// Test_IR(IR_temp_laser_array);
// TestCross_judge();
   send_count++;
   if(send_count%20==0) {
     send_count=1;
    TestSMinfo(test_info_send);  
   }   
 }
    
 
   
  
  

          
// _FEED_COP(); /*���Ź�������ѭ���õ� */
 /* loop forever */
  /* please make sure that you never leave main */
}



 
#pragma CODE_SEG NON_BANKED 
//��interrupt definitions��
/* ================= PIT0_ISR ====================
      desc: PIT���ڶ�ʱ�жϣ����ڿ��Ƽ��⴫������ʱ��
      pre:  ��
      Post: ��       
*/ 
void interrupt 66 PIT0_ISR(void) {
    DisableInterrupts; 
   PITCE_PCE0=0;PITCE_PCE0=1; 
    Light_Up();         //�������ŵ���   
   Confirm_Light(); //�ų����
   if(nothing_flag==1)
     {
      //Clear_baitou();  //position�ĵ�һ���˲�
     // baitou_delay=9;
     } 
   
   else if(nothing_flag==0) 
   {
   Clear_baitou();  //position�ĵ�һ���˲�
   baitou_delay++;
   if(baitou_delay%6==0) 
   {
    baitou_delay=1;
    baitou( ); //��ִ�а�ͷ�����ͨ������ó��Ƕȣ�Ϊ�ڶ����˲���׼��
    JG_clear[1]=0;
    } 
   }
   
   General_Position();      
  // Collect_Point();
  // Collect_Section();
  // Judge_Slope();
   Clear_General();
  // delay_count++;
   
   
   
   
   dajiao();
   

    
  
Clear_Speed();
SpeedCtrl(startingline_flag); 
  EnableInterrupts; 
   
}   
 
void interrupt 67 PIT1_ISR(void){
PITCE_PCE1=0;PITCE_PCE1=1;
speed_clear[1]= PACNT;
PACNT = 0x0000; 

}//PIT0_ISR

#pragma CODE_SEG DEFAULT