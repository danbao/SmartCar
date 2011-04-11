/* 智能车控制函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                       
*说    明:   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//【header file】
#include "smartcarCtrl.h"


//【function definitions】
/* ================= DerectionCtrl ====================
      desc: 转向控制
      pre:  舵机转角度
      Post: 无
       
*/ 
void  DerectionCtrl (int turn_angle_PWM) {
    // Local Declarations
    int delta =  turn_angle_PWM - PWMDTY01;   //调换位置
    int abs_delta = abs(delta);
    
    // Statements
    if(abs_delta >= ANGLE_DELTA) {
        if(delta > 0)
           PWMDTY01 += ANGLE_DELTA;
        else
           PWMDTY01 -= ANGLE_DELTA;
        
    } 
    else {
        PWMDTY01 += delta;  
    }
  
} // DerectionCtrl


/* ================= SpeedCtrl ====================
      desc: 速度控制
      pre:  参数描述
      Post: 返回值描述
       
*/ 
void SpeedCtrl (int speedPWM, byte temp_pulse, byte* last_error) {
  // Local Declarations
  byte this_error;
  
  int pwm3_superFast;
  int pwm3_fast;
  int pwm3_normal;
  int pwm3_slow;
  
  byte straight_pulse_max;
  byte more_straight_pulse_max;
  byte mid_straight_pulse_max;
  byte least_straight_pulse_max;  
 
  // Statements
  //选择拨码开关
  if(PORTA_PA7 == 0) {
      pwm3_superFast = PWM3_SUPER_FAST0;
      pwm3_fast = PWM3_FAST0;
      pwm3_normal = PWM3_NORMAL0;
      pwm3_slow = PWM3_SLOW0;  
  }
  else{
      pwm3_superFast = PWM3_SUPER_FAST1;
      pwm3_fast = PWM3_FAST1;
      pwm3_normal = PWM3_NORMAL1;
      pwm3_slow = PWM3_SLOW1;    
  }
  
  if(PORTA_PA5 == 0 && PORTA_PA6 == 0) {
      straight_pulse_max = STRAIGHT_PULSE_MAX0;
      more_straight_pulse_max = MORE_STRAIGHT_PULSE_MAX0;
      mid_straight_pulse_max = MID_STRAIGHT_PULSE_MAX0;
      least_straight_pulse_max = LEAST_STRAIGHT_PULSE_MAX0;
  } 
  else if(PORTA_PA5 == 0 && PORTA_PA6 == 1){
      straight_pulse_max = STRAIGHT_PULSE_MAX1;
      more_straight_pulse_max = MORE_STRAIGHT_PULSE_MAX1;
      mid_straight_pulse_max = MID_STRAIGHT_PULSE_MAX1;
      least_straight_pulse_max = LEAST_STRAIGHT_PULSE_MAX1;
  }
  else if(PORTA_PA5 == 1 && PORTA_PA6 == 0){
      straight_pulse_max = STRAIGHT_PULSE_MAX2;
      more_straight_pulse_max = MORE_STRAIGHT_PULSE_MAX2;
      mid_straight_pulse_max = MID_STRAIGHT_PULSE_MAX2;
      least_straight_pulse_max = LEAST_STRAIGHT_PULSE_MAX2;
  }
  else if(PORTA_PA5 == 1 && PORTA_PA6 == 1){
      straight_pulse_max = STRAIGHT_PULSE_MAX3;
      more_straight_pulse_max = MORE_STRAIGHT_PULSE_MAX3;
      mid_straight_pulse_max = MID_STRAIGHT_PULSE_MAX3;
      least_straight_pulse_max = LEAST_STRAIGHT_PULSE_MAX3;
  }
  
  

  PWMDTY45 = 0;
  if(speedPWM == pwm3_superFast){
       this_error =  straight_pulse_max - temp_pulse;
       if ( this_error < 0 )
           PWMDTY23 =  PWMDTY23 + this_error/SPEED_P + *last_error/SPEED_D;
       else if (this_error > 0)
           PWMDTY23 = speedPWM;
  } 
  else if(speedPWM == pwm3_fast){
       this_error =  more_straight_pulse_max - temp_pulse;
       if ( this_error < 0 )
           PWMDTY23 =  PWMDTY23 + this_error/SPEED_MORE_P + *last_error/SPEED_MORE_D;
       else if (this_error > 0)
           PWMDTY23 = speedPWM;
  } 
  else if(speedPWM == pwm3_normal){
       this_error =  mid_straight_pulse_max - temp_pulse;
       if ( this_error < 0 )
           PWMDTY23 =  PWMDTY23 + this_error/SPEED_MID_P + *last_error/SPEED_MID_D;
       else if (this_error > 0)
           PWMDTY23 = speedPWM;
  } 
  else if(speedPWM == pwm3_slow){
       this_error = least_straight_pulse_max - temp_pulse;
       if ( this_error < 0 )
           PWMDTY23 =  PWMDTY23 + this_error/SPEED_LEAST_P + *last_error/SPEED_LEAST_P;
       else if (this_error > 0)
           PWMDTY23 = speedPWM;
  } 
  
  *last_error =  this_error;
} //SpeedCtrl


/* ================= BreakCar ====================
      desc: 紧急制动
      pre:  参数描述
      Post: 返回值描述
       
*/ 
void BreakCar (byte temp_pulse, Bool* breakCar_flag) {
  // Local Declarations
 
  // Statements
  if(temp_pulse >  CURVE_PULSE){
          PWMDTY23 = 0;
          PWMDTY45 = PWM5_BREAK;
      } 
  else *breakCar_flag = FALSE;
  
} //BreakCar

void StopCar ( Bool StopCar_flag)  {
  if( StopCar_flag){
    PWME_PWME3 = 0;
    PWME_PWME5 = 0;
  }
}


/* ================= SmartcarInit ====================
      desc: 智能车启动初始化
      pre:  无
      Post: 无
       
*/ 
void SmartcarInit(void) {
    // Local Declarations
    // Statements
    PORTE = 0Xff;          //绿色LED灯全灭
    PORTA |= 0B00011111;   //激光管全亮  
    PWMDTY01 = PWM1_MID;   //舵机方向转正  
    StartCarDelay();       //延迟2秒再出发
    PWMDTY23 = PWM3_FAST0;  //速度为普通快速     
}  //StartCarInit
  

/* ================= StartCarDelay ====================
      desc: 启动车前的延时2秒
      pre:  无
      Post: 无
       
*/ 
void StartCarDelay (void) {
    // Local Declarations
    int m = 0;
    int n = 0;
    // Statements
    for(m=0;m<3000;m++) {  //延迟2秒再开始出发
         for(n=0;n<3000;n++) {
         }
    }  
} //StartCarDelay


void StartCarDelay1 (void) {
    // Local Declarations
    int m = 0;
    int n = 0;
    // Statements
    for(m=0;m<30;m++) {  //延迟2秒再开始出发
         for(n=0;n<300;n++) {
         }
    }  
} //StartCarDelay



