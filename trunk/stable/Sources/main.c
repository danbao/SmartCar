/* 主函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                       
*说    明:   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//【header file】
#include "Includes.h"      /* 总头文件 */

//【global ariables】 
byte g_countPIT0 = 0;                //用来对激光管分时亮的中断计数（1--4循环） 
byte g_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
byte g_temp_pulse = 0;               //20ms一次测得的当前脉冲值

//【function definitions】
/* ================= main ====================
      desc: 程序入口函数
      pre:  无
      Post: 无       
*/
void main(void) {
    // Local Declarations
    byte laser_history_array[LASER_HISTORY_MAX]; //激光管历史状态数组
  
  	Bool temp_usualRoad_flag = TRUE;      //当前判断是否正常路段标志
  	Bool last_usualRoad_flag = TRUE;      //上次判断是否正常路段标志
  	Bool stopCar_flag = FALSE;            //停车标志
  	Bool breakCar_flag = FALSE;           //刹车标志
  
  	byte startlineFlag_count = 0;         //经过起始线的次数
  	byte laser_hitNum = 1;                //照到黑线的激光管个数
  	byte inside_count = INSIDE_COUNT_MAX; //激光管连续在黑线范围内的次数
  	byte outside_count = 0;               //激光管连续在黑线外的次数
  	byte last_error = 0;                  //直道加速匀速控制的上次误差
  	 
  	LASER_STATUS last_laserStatus = MID7;  //上次激光管状态
  	LASER_STATUS temp_laserStatus = MID7;  //当前激光管状态
  	int last_turnAngle = PWM1_MID;     //上次舵机调整的角度
  	int temp_turnAngle = PWM1_MID;     //当前舵机需要调整的角度	
  	int last_speed = PWM3_FAST0;   //上次速度
  	int temp_speed = PWM3_FAST0;   //当前速度 
  	
  	int i;
    int testcount=0;  //发送激光管信息计数值定义
  	for(i=0;i<LASER_HISTORY_MAX;i++) {
  	    laser_history_array[i] = MID7;
  	}
  	
    // Statements
    DisableInterrupts;
    MCUInit();
  	SmartcarInit();
  	EnableInterrupts;
  
    for(;;) {  
         if(PITINTE_PINTE0 == 0) {    //若PIT0采集中断为关,即道路信息采集完成
              laser_hitNum = 15 - CalculateLaserHitNum(g_temp_laser_array);
              temp_usualRoad_flag =  IsUsualRoad (laser_hitNum); //判断是否为正常道路
              if (temp_usualRoad_flag) {
                  temp_laserStatus = GetLaserStatus(last_laserStatus,g_temp_laser_array,laser_hitNum,&inside_count,&breakCar_flag,laser_history_array,&outside_count); //得到当前激光管状态
                  temp_turnAngle = CalculateAngle(temp_laserStatus); //得到舵机需要调整的转角      
                  temp_speed = CalculateSpeed (temp_turnAngle,stopCar_flag,inside_count,outside_count); //得到需要输出的速度
              } 
              else {
                  if((last_usualRoad_flag == TRUE)&&(laser_hitNum>=8&&laser_hitNum<=11)) {          //一定执行
                      startlineFlag_count = CountStartlineFlag(startlineFlag_count,g_temp_laser_array); //计算小车经过起始线的次数
                      if(startlineFlag_count == 2)  
                            stopCar_flag = TRUE; //若是第二次经过起始线，停车标志置位，即停车
                      StopCar(stopCar_flag);      
                  }
              } /**/
            
              
       testcount++;
              
              if(testcount%50==0){
                
               testcount=1;   
             SendSmartcarInfo(g_temp_laser_array,temp_laserStatus,last_laserStatus,g_temp_pulse);//发送激光管信息
                  } /*   */
              PITINTE_PINTE0 = 1;    //开PIT0采集中断 
        }           
        DerectionCtrl(temp_turnAngle); //调整舵机
        
        if(breakCar_flag == TRUE) {  //若直道入弯，反转减速刹车
            BreakCar(g_temp_pulse, &breakCar_flag);
        }  
        else
            SpeedCtrl(temp_speed,g_temp_pulse,&last_error);         //调整正转速度
         
        last_speed = temp_speed;                        //保存当前速度
        last_laserStatus = temp_laserStatus;            //保存当前激光管状态
        last_turnAngle = temp_turnAngle;                //保存当前舵机转角
        last_usualRoad_flag = temp_usualRoad_flag;      //保存当前是否正常道路的标志 
        
        for(i=LASER_HISTORY_MAX-1;i>0;i--){             //保存激光管历史状态
            laser_history_array[i] =  laser_history_array[i-1];   
        }
        laser_history_array[0] = temp_laserStatus;
    }
} //main


#pragma CODE_SEG NON_BANKED 
//【interrupt definitions】
/* ================= PIT0_ISR ====================
      desc: PIT周期定时中断，用于控制激光传感器分时亮
      pre:  无
      Post: 无       
*/ 
void interrupt 66 PIT0_ISR(void) {
    g_countPIT0 ++;
    if(g_countPIT0 == 5) {
         g_countPIT0 = 0;
         PITINTE_PINTE0 = 0;
    }  
    /*激光管循环控制顺序为 ------- 第1组（1,6,11），第2组（2,7,12），第3组（3,8,13），第4组（4,9,14），第0组（0,5,10）
      每次进中断，对上次亮的一组激光管先赋值，再换下一组的激光管亮
    */                                                    
   if(g_countPIT0 == 0) {   
        g_temp_laser_array[4] = PORTB_PB1; //接收第4组（4,9,14） 
    //StartCarDelay1 ()    ;
        g_temp_laser_array[9] = PORTB_PB3; //点亮第0组（0,5,10）
        g_temp_laser_array[14] = PORTB_PB4;
        PORTA = 0B00000001; 
    }
    else if(g_countPIT0 == 1)   {    
        g_temp_laser_array[0] = PORTB_PB0; //接收第0组（0,5,10）   
        g_temp_laser_array[5] = PORTB_PB1; //点亮第1组（1,6,11）
        g_temp_laser_array[10] = PORTB_PB3;
        PORTA = 0B00000010;        
    }
    else if(g_countPIT0 == 2)   {    
        g_temp_laser_array[1] = PORTB_PB0; //接收第1组（1,6,11）
        g_temp_laser_array[6] = PORTB_PB2; //点亮第2组（2,7,12）
        g_temp_laser_array[11] = PORTB_PB3;
        PORTA = 0B00000100;
    }
    else if(g_countPIT0 == 3)   {  
        g_temp_laser_array[2] = PORTB_PB0; //接收第2组（2,7,12）  
        g_temp_laser_array[7] = PORTB_PB2; //点亮第3组（3,8,13）
        g_temp_laser_array[12] = PORTB_PB4;
        PORTA = 0B00001000;
    }
    else if(g_countPIT0 == 4)   {  
        g_temp_laser_array[3] = PORTB_PB1; //接收第3组（3,8,13）  
        g_temp_laser_array[8] = PORTB_PB2; //点亮第4组（4,9,14）
        g_temp_laser_array[13] = PORTB_PB4;
        PORTA = 0B00010000;
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




