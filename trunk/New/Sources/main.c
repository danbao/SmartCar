#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include "math.h"           //abs����ֵҪ�õ�
#include "main.h"           //���б����Ķ��嶼����main.h�ļ�����
#include "dealinfo.h"
#include "control.h" 

void main(void) {
  int i;

     
  int temp_laserStatus;           //����һ�������������� ���¶��ֵ
  EnableInterrupts;
  SetBusCLK_40M();    //   ����ʱ�ӳ�ʼ����40MHz.
  PWM_Init();
  LIGHT_Init();
  delayms(2);
  Laser_num();
  for(i=0;;i++) {
    if(i == 5) 
    {i = 0;
   
    //  count++;
      //     if(count%20==0){  
      //        count=1; 
//  SendSmartcarInfo(light_temp_laser_array);
  //  SCISend('\n');    
  //          }         
     temp_laserStatus = Status_Judge();
     CalculateAngle(temp_laserStatus); //�õ������Ҫ������ת�� 
    dajiao();     
   testcount++;
  if(testcount%17==0){
       testcount=1;
   baitou( );
   }
    
     SpeedCtrl();
     receive(i);
    } else receive(i);
  }
// _FEED_COP(); /*���Ź�������ѭ���õ� */
 /* loop forever */
  /* please make sure that you never leave main */
}
