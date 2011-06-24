#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>       //sprintf要用到
#include <string.h>      //LCD中的strlen要用到
#include <math.h>        //abs绝对值要用到
#include <stdlib.h>      //随机数用到
#include "main.h"           //所有变量的定义都放在main.h文件下了           
#include "dealinfo.h"
#include "control.h" 
#include "IR.h" 
#include "SCI.h"
 
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
  delayms(3200);
  Laser_num();
  EnableInterrupts;
  for(;;) 
  {
    Light_Up();         //激光整排点亮
     
   //  Collect_IR();   //这两个是红外捕捉和判断红外位置 先注释
   //  Level_IR();
   
   Confirm_Light(); //排除误点
   Clear_baitou();  //position的第一次滤波
   baitou_delay++;
   if(baitou_delay%9==0) 
   {
    baitou_delay=1;
    baitou( ); //先执行摆头舵机，通过计算得出角度，为第二次滤波做准备
    } 
   
   //General_Position();      
  // Collect_Point();
  // Collect_Section();
  // Judge_Slope();
  // Clear_General();
  // delay_count++;
   
   
   
   
  // dajiao();
   
  /* send_count++;
   if(send_count%20==0) {
     send_count=1;
    TestSMinfo();  
   }   
    */
  
//Clear_Speed();
   // SpeedCtrl();  
  
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

void interrupt 66 PIT0_ISR(void){
DisableInterrupts;   
speed_clear[1]= PACNT;
PACNT = 0x0000; 
PITTF_PTF0 = 1;
EnableInterrupts; 
}

#pragma CODE_SEG DEFAULT
