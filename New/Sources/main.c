#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <stdio.h>       //sprintfҪ�õ�
#include "math.h"           //abs����ֵҪ�õ�
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
 // AD_Init(); 
  delayms(4000);
  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
   // Light_Up();         //�������ŵ���
     
   //  Collect_IR();   //�������Ǻ��Ⲷ׽���жϺ���λ�� ��ע��
   //  Level_IR();
 //  if(PITINTE_PINTE1 == 0) 
 //  PITINTE_PINTE1 = 1;   //��PIT1�ɼ��ж�  
   Confirm_Light(); //�ų����
   Clear_baitou();  //position�ĵ�һ���˲�
         
   //  Form_tendency(); //ͨ����ͷ�����ƫ��ֵ�õ�һ���Ƚ�׼ȷ������
   // Calculate_HitBlackNum();
   //temp_laserStatus = Status_Judge();
   //   CalculateAngle(temp_laserStatus); //�õ������Ҫ������ת�� 
  //  dajiao();  
   
      delay_count++;
      if(delay_count%50==0)
      {
       delay_count=1;
       // dajiao();
      }

     send_count++;
   if(send_count%20==0) {
     send_count=1;
    TestSMinfo();
   }
   
   baitou_delay++;
   if(baitou_delay%12==0) 
   {
    baitou_delay=1;
    baitou( ); //��ִ�а�ͷ�����ͨ������ó��Ƕȣ�Ϊ�ڶ����˲���׼��
    } 
  
  
    SpeedCtrl();
   
  }

          
// _FEED_COP(); /*���Ź�������ѭ���õ� */
 /* loop forever */
  /* please make sure that you never leave main */
}



 
#pragma CODE_SEG __NEAR_SEG NON_BANKED
 
void interrupt 66 PIT0_ISR(void){
DisableInterrupts;   
speed_clera[1]= PACNT;
PACNT = 0x0000; 
PITTF_PTF0 = 1;
EnableInterrupts; 
}

#pragma CODE_SEG DEFAULT
