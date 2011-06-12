#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintfҪ�õ�
#include <string.h>      //LCD�е�strlenҪ�õ�
#include <math.h>        //abs����ֵҪ�õ�
#include <stdlib.h>      //������õ�
#include "main.h"           //���б����Ķ��嶼����main.h�ļ�����           
#include "dealinfo.h"
#include "control.h" 
#include "IR.h" 
#include "SCI.h"
 
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
 // AD_Init(); 
  delayms(3200);
  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
    Light_Up();         //�������ŵ���
     
   //  Collect_IR();   //�������Ǻ��Ⲷ׽���жϺ���λ�� ��ע��
   //  Level_IR();
   Confirm_Light(); //�ų����
   Clear_baitou();  //position�ĵ�һ���˲�
   General_Position();      
   Collect_Point();
   Collect_Section();
   Judge_Slope();
   Clear_General();
   
   dajiao();

  /* send_count++;
   if(send_count%20==0) {
     send_count=1;
    TestSMinfo();  
   }   
    */
  
   baitou_delay++;
   if(baitou_delay%10==0) 
   {
    baitou_delay=1;
    baitou( ); //��ִ�а�ͷ�����ͨ������ó��Ƕȣ�Ϊ�ڶ����˲���׼��
    } 
  
   
    Clear_Speed();
    SpeedCtrl();
   
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
void interrupt 67 PIT1_ISR(void) {
    DisableInterrupts; 
    TestSMinfo(test_info_send); 
    PITTF_PTF1 = 1;//���жϱ�־λ 
    EnableInterrupts; 
} //PIT0_ISR  

 
void interrupt 66 PIT0_ISR(void){
DisableInterrupts;   
speed_clera[1]= PACNT;
PACNT = 0x0000; 
PITTF_PTF0 = 1;
EnableInterrupts; 
}

#pragma CODE_SEG DEFAULT
