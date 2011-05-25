#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <stdio.h>       //sprintf要用到
#include "math.h"           //abs绝对值要用到
#include "main.h"           //所有变量的定义都放在main.h文件下了           
#include "dealinfo.h"
#include "control.h"
#include "SCI.h"  
 
/* ================= SendSmartcarInfo ====================
      desc: SCI串口发送当前激光管采集信息
      pre:  1当前激光管采集数组，2当前激光管状态
      Post: 无
       
*/ 
void SendSmartcarInfo(byte temp_laser_array[]) {
    int i; 
    int data;
    char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //发送激光管信息数组
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        }
 SCISend('\n');
 // sprintf(g,"%u",p);
  //for(i=0;g[i]!='\0';i++)
  //SCISend(g[i]);  
     
}

void main(void) 
{
  int i;

     
 // int temp_laserStatus;           //定义一个数组用来接受 上下舵机值
  DisableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  PITInit();
  PWM_Init();
  LIGHT_Init();
  SCI_Init();
  delayms(2);
  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
    if(PITINTE_PINTE0 == 0) 
    {    //若PIT0采集中断为关,即道路信息采集完成
          count++;
          if(count%20==0)
          {  
            count=1; 
    SendSmartcarInfo(light_temp_laser_array);
             //TestSMinfo();   
          }         
          Confirm_Light();
          Clear_baitou();
    // Calculate_HitBlackNum();
     //temp_laserStatus = Status_Judge();
     
  //   CalculateAngle(temp_laserStatus); //得到舵机需要调整的转角 
  //  dajiao();     
          testcount++;
          if(testcount%10==0)
          {
            testcount=1;
            baitou( );
          }

          SpeedCtrl();
     
      PITINTE_PINTE0 = 1;    //开PIT0采集中断 
    }
  }
// _FEED_COP(); /*看门狗，防死循环用的 */
 /* loop forever */
  /* please make sure that you never leave main */
}



#pragma CODE_SEG NON_BANKED 
//【interrupt definitions】
/* ================= PIT0_ISR ====================
      desc: PIT周期定时中断，用于控制激光传感器分时亮
      pre:  无
      Post: 无       
*/ 
void interrupt 66 PIT0_ISR(void) 
{
    g_countPIT0 ++;
    if(g_countPIT0 == 6) 
    {
         g_countPIT0 = 0;
         PITINTE_PINTE0 = 0;
    }  
   if(g_countPIT0 == 0) {  
         PORTA = 0B00000001;
     //delayMS(); 
	    light_temp_laser_array[0] = PORTB_PB0^1;
      light_temp_laser_array[6] = PORTB_PB2^1;
    }
    else if(g_countPIT0 == 1)   { 
        PORTA = 0B00001000;
     //delayMS();  
	    light_temp_laser_array[3] = PORTB_PB1^1;	
        light_temp_laser_array[9] = PORTB_PB3^1;
    }
    else if(g_countPIT0 == 2)   {    
        PORTA = 0B00000010;
     //delayMS();  
	    light_temp_laser_array[1] = PORTB_PB0^1;
        light_temp_laser_array[7] = PORTB_PB2^1;
	   
        
    }
    else if(g_countPIT0 == 3)   {  
       PORTA = 0B00010000;
     //delayMS(); 
	    light_temp_laser_array[4] = PORTB_PB1^1;
        light_temp_laser_array[10] = PORTB_PB3^1;
	 
     
        
    }
    else if(g_countPIT0 == 4)   {  
       PORTA = 0B00000100;
     //delayMS();  
	    light_temp_laser_array[2] = PORTB_PB0^1;
        light_temp_laser_array[8] = PORTB_PB2^1;
   
    }
	else if(g_countPIT0 == 5)   {  
        PORTA = 0B00100000;
     //delayMS();  
	   light_temp_laser_array[5] = PORTB_PB1^1;
     light_temp_laser_array[11] = PORTB_PB3^1;
	 
        
    } 
   
    PITTF_PTF0 = 1;//清中断标志位  
} //PIT0_ISR  

 
/* ================= PIT1_ISR ====================
      desc: PIT周期定时中断，用于测速
      pre:  无
      Post: 无       
*/ 
 void interrupt 67 PIT1_ISR(void) {
    g_temp_pulse = PACNT;
    PACNT = 0x0000;
    PITTF_PTF1 = 1;//清中断标志位 
 } //PIT1_ISR


