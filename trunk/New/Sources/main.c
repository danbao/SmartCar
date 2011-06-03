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
  AD_Init(); 
  delayms(2);
  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
   // while(PITINTE_PINTE1 == 0); 
     
   //  Collect_IR();   //�������Ǻ��Ⲷ׽���жϺ���λ�� ��ע��
   //  Level_IR();
     
      
    if(PITINTE_PINTE0 == 0&&PITINTE_PINTE1 == 0) 
    {    //��PIT0�ɼ��ж�Ϊ��,����·��Ϣ�ɼ����
     
     //if(PITINTE_PINTE1 == 0) 
    // temp_speed=Calculate_speed(g_temp_pulse);

             TestSMinfo(30);//����������Ϣ�ķ���       
          Confirm_Light(); //�ų����
          Clear_baitou();  //position�ĵ�һ���˲�
          baitou( ); //��ִ�а�ͷ�����ͨ������ó��Ƕȣ�Ϊ�ڶ����˲���׼��
          Form_tendency(); //ͨ����ͷ�����ƫ��ֵ�õ�һ���Ƚ�׼ȷ������
    // Calculate_HitBlackNum();
     //temp_laserStatus = Status_Judge();
     
  //   CalculateAngle(temp_laserStatus); //�õ������Ҫ������ת�� 
  //  dajiao();     
          delay_count++;
          if(delay_count%10==0)
          {
            delay_count=1;
            dajiao();
          }
          PITINTE_PINTE0 = 1;    //��PIT0�ɼ��ж� 
          PITINTE_PINTE1 = 1;   //��PIT1�ɼ��ж�  
    }
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
void interrupt 66 PIT0_ISR(void) 
{
    g_countPIT0 ++;
    if(g_countPIT0 == 6) 
    {
       g_countPIT0 = 0;
       PITINTE_PINTE0 = 0;
    }  
   if(g_countPIT0 == 0) 
   {  
      PORTA = 0B00000001;
      delayMS();
	    light_temp_laser_array[0] = PORTB_PB0^1;
      light_temp_laser_array[6] = PORTB_PB2^1;
    }
    else if(g_countPIT0 == 1)   
    { 
      PORTA = 0B00001000;
      delayMS();
	    light_temp_laser_array[3] = PORTB_PB1^1;	
      light_temp_laser_array[9] = PORTB_PB3^1;
    }
    else if(g_countPIT0 == 2)   
    {    
      PORTA = 0B00000010;
      delayMS();
	    light_temp_laser_array[1] = PORTB_PB0^1;
      light_temp_laser_array[7] = PORTB_PB2^1;
    }
    else if(g_countPIT0 == 3)   
    {  
      PORTA = 0B00010000;
      delayMS(); 
	    light_temp_laser_array[4] = PORTB_PB1^1;
      light_temp_laser_array[10] = PORTB_PB3^1; 
    }
    else if(g_countPIT0 == 4)   
    {  
      PORTA = 0B00000100;
      delayMS();  
	    light_temp_laser_array[2] = PORTB_PB0^1;
      light_temp_laser_array[8] = PORTB_PB2^1;
   
    }
	else if(g_countPIT0 == 5)   
	{  
      PORTA = 0B00100000;
      delayMS();  
	    light_temp_laser_array[5] = PORTB_PB1^1;
      light_temp_laser_array[11] = PORTB_PB3^1;  
    } 
    PITTF_PTF0 = 1;//���жϱ�־λ  
} //PIT0_ISR  

 
/* ================= PIT1_ISR ====================
      desc: PIT���ڶ�ʱ�жϣ����ڲ���
      pre:  ��
      Post: ��       
*/ 
 void interrupt 67 PIT1_ISR(void) {
    g_temp_pulse = PACNT;
    PACNT = 0x0000;
    PITTF_PTF1 = 1;//���жϱ�־λ 
    PITINTE_PINTE1 = 0;
 } //PIT1_ISR


