#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#include <stdio.h>       //sprintf要用到
#include "math.h"           //abs绝对值要用到
#include "main.h"           //所有变量的定义都放在main.h文件下了           
#include "dealinfo.h"
#include "control.h"
#include "SCI.h" 
#include "IR.h" 
 
/* ================= SendSmartcarInfo ====================
      desc: SCI串口发送当前激光管采集信息
      pre:  1当前激光管采集数组，2当前激光管状态
      Post: 无
       
*/ 

void main(void) 
{

 // int temp_laserStatus;           //定义一个数组用来接受 上下舵机值
  DisableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  PITInit();          //PIT初始
  PWM_Init();
  LIGHT_Init();
  SCI_Init();
  Tect_Speed_Init();    //ECT 捕捉初始
 // AD_Init(); 
  delayms(4000);
  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
   // Light_Up();         //激光整排点亮
     
   //  Collect_IR();   //这两个是红外捕捉和判断红外位置 先注释
   //  Level_IR();
 //  if(PITINTE_PINTE1 == 0) 
 //  PITINTE_PINTE1 = 1;   //开PIT1采集中断  
   Confirm_Light(); //排除误点
   Clear_baitou();  //position的第一次滤波
         
   //  Form_tendency(); //通过摆头舵机和偏差值得到一个比较准确的趋势
   // Calculate_HitBlackNum();
   //temp_laserStatus = Status_Judge();
   //   CalculateAngle(temp_laserStatus); //得到舵机需要调整的转角 
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
    baitou( ); //先执行摆头舵机，通过计算得出角度，为第二次滤波做准备
    } 
  
    Clear_Speed();
    SpeedCtrl();
   
  }

          
// _FEED_COP(); /*看门狗，防死循环用的 */
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
