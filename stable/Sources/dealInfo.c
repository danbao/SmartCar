/* 信息处理函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                        
*说    明: 处理智能车转向和速度信息   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//【header file】
#include "dealInfo.h"

/* ================= GetLaserStatus ====================
      desc: 得到激光管状态枚举类型
      pre:  1.激光管状态变量  2.激光管采集信息数组 3,照到黑线的激光管个数
            4.中间范围的激光管照到黑线的次数   5.刹车标志  
            6.激光管历史状态数组  7.激光管照空的次数 
      Post: 返回激光管状态枚举类型
       
*/ 
LASER_STATUS GetLaserStatus(LASER_STATUS last_status,byte temp_laser_array[],byte laser_hitNum, byte* inside_count, Bool* breakCar_flag, byte laser_history_array[],byte* outside_count) {
  // Local Declarations
  int i;
  Bool out_flag = FALSE;
  LASER_STATUS status = MID7;
  
  //PORTE_PE3 = 1 ;
 
  // Statements
  if(laser_hitNum == 1) {
      if (temp_laser_array[7] == 0 && temp_laser_array[6] == 1 && temp_laser_array[8] == 1)  {
          status = MID7;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[8] == 0 && temp_laser_array[7] == 1 && temp_laser_array[9] == 1){
          status = RIGHT8;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[6] == 0 && temp_laser_array[5] == 1 && temp_laser_array[7] == 1){
          status = LEFT6;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      } 
      else if (temp_laser_array[9] == 0 && temp_laser_array[8] == 1 && temp_laser_array[10] == 1) {
          status = RIGHT9;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[5] == 0 && temp_laser_array[4] == 1 && temp_laser_array[6] == 1) { 
          status = LEFT5;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[10] == 0 && temp_laser_array[9] == 1 && temp_laser_array[11] == 1) {
          status = RIGHT10;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[4] == 0 && temp_laser_array[3] == 1 && temp_laser_array[5] == 1){
          status = LEFT4;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[11] == 0 && temp_laser_array[10] == 1 && temp_laser_array[12] == 1){
          status = RIGHT11;
          if(last_status == LEFT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[3] == 0 && temp_laser_array[2] == 1 && temp_laser_array[4] == 1) {  
          status = LEFT3;
          if(last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[12] == 0 && temp_laser_array[11] == 1 && temp_laser_array[13] == 1){
          status = RIGHT12;
          if(last_status == LEFT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[2] == 0 && temp_laser_array[1] == 1 && temp_laser_array[3] == 1){ 
          status = LEFT2;
          if(last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[13] == 0 && temp_laser_array[12] == 1 && temp_laser_array[14] == 1) {
          status = RIGHT13;
          if(last_status == LEFT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[1] == 0 && temp_laser_array[2] == 1 && temp_laser_array[0] == 1) {
          status = LEFT1;
          if(last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[14] == 0 && temp_laser_array[13] == 1) { 
          status = RIGHT14;
          if(last_status == LEFT_NONE)
              status = last_status;
          else if(last_status == LEFT0)
              status = LEFT_NONE;    
      }
      else if (temp_laser_array[0] == 0 && temp_laser_array[1] == 1) {
          status = LEFT0;
          if(last_status == RIGHT_NONE)
              status = last_status;
          else if(last_status == RIGHT14)
              status = RIGHT_NONE;
      }
  }
  
  else if(laser_hitNum == 2) {
      if (temp_laser_array[0] == 0 && temp_laser_array[1] == 0) {
          status = LEFT01;
          if(last_status == RIGHT_NONE)
              status = last_status;
          else if(last_status == RIGHT14)
              status = RIGHT_NONE;
      }
      else if (temp_laser_array[1] == 0 && temp_laser_array[2] == 0) {
          status = LEFT12;
          if(last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[2] == 0 && temp_laser_array[3] == 0) {
          status = LEFT23;
          if(last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[3] == 0 && temp_laser_array[4] == 0){
          status = LEFT34;
          if(last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[4] == 0 && temp_laser_array[5] == 0){ 
          status = LEFT45;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[5] == 0 && temp_laser_array[6] == 0) {
          status = LEFT56;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[6] == 0 && temp_laser_array[7] == 0){
          status = LEFT67;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[7] == 0 && temp_laser_array[8] == 0) {
          status = RIGHT78;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      } 
      else if (temp_laser_array[8] == 0 && temp_laser_array[9] == 0){
          status = RIGHT89;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[9] == 0 && temp_laser_array[10] == 0) {  
          status = RIGHT910;
          if(last_status == LEFT_NONE || last_status == RIGHT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[10] == 0 && temp_laser_array[11] == 0){
          status = RIGHT1011;
          if(last_status == LEFT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[11] == 0 && temp_laser_array[12] == 0) {   
          status = RIGHT1112;
          if(last_status == LEFT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[12] == 0 && temp_laser_array[13] == 0){  
          status = RIGHT1213;
          if(last_status == LEFT_NONE)
              status = last_status;
      }
      else if (temp_laser_array[13] == 0 && temp_laser_array[14] == 0) {
          status = RIGHT1314;
          if(last_status == LEFT_NONE)
              status = last_status;
          else if(last_status == LEFT0)
              status = LEFT_NONE;
      }
      else if (temp_laser_array[1] == 0 && temp_laser_array[0] == 1 && temp_laser_array[2] == 1 && temp_laser_array[14] == 0) {
          if(last_status == LEFT1 || last_status == LEFT_NONE || last_status == LEFT01|| last_status == LEFT0)
              status = LEFT1;       
      }
      else if (temp_laser_array[13] == 0 && temp_laser_array[14] == 1 && temp_laser_array[12] == 1 && temp_laser_array[0] == 0) {
          if(last_status == RIGHT13 || last_status == RIGHT_NONE || last_status == RIGHT1314|| last_status == RIGHT14 || last_status == RIGHT_NONE )
              status = RIGHT13;       
      }
      else if (temp_laser_array[14] == 0 && temp_laser_array[0] == 0) {
          if(last_status == RIGHT14 || last_status == RIGHT_NONE || last_status == RIGHT1314|| last_status == RIGHT13)
              status = RIGHT14;  
          else if(last_status == LEFT0 || last_status == LEFT_NONE || last_status == LEFT01|| last_status == LEFT1)
              status = LEFT0;
      }
      else 
          status = last_status;    
  } 
  
  else if(laser_hitNum == 3) {
      if(temp_laser_array[0] == 0 && temp_laser_array[1] == 0 && temp_laser_array[14] == 0){
          if(last_status == LEFT01 || last_status == LEFT0 || last_status == LEFT1 || last_status == LEFT_NONE || last_status == LEFT12)
              status = LEFT01;
          
          else if(last_status == RIGHT14 || last_status == RIGHT_NONE || last_status == RIGHT1314 || last_status == RIGHT13)
              status = RIGHT14;
      } 
      else if(temp_laser_array[13] == 0 && temp_laser_array[14] == 0 && temp_laser_array[0] == 0){
          if(last_status == RIGHT1314 || last_status == RIGHT14 || last_status == RIGHT13 || last_status == RIGHT_NONE || last_status == RIGHT1213)
              status = RIGHT1314;
          else if(last_status == LEFT0 || last_status == LEFT_NONE || last_status == LEFT01 || last_status == LEFT1)
              status = LEFT0;
      } 
  } 
  
  else if(laser_hitNum == 0) {
      if(last_status == LEFT0 || last_status == LEFT_NONE || last_status == LEFT01 || last_status == LEFT1)
          status = LEFT_NONE;
      
      else if(last_status == RIGHT14 || last_status == RIGHT_NONE || last_status == RIGHT1314 || last_status == RIGHT13)
          status = RIGHT_NONE;
  }
  
  else {
      status = last_status;    
  }
  
  //判断长直道后的突然入弯 ，使得直道加速，入弯急刹车
  if ( abs(status - MID7) < 9)  
  {
      for(i=1;i<LASER_HISTORY_MAX-1;i++) 
      {
          if( abs ( laser_history_array[0] - laser_history_array[i] ) > 5 ) 
          { 
              out_flag = TRUE;
              break; 
          }
      }
  } 
  else {
      out_flag = FALSE; 
  }
  
  if(out_flag == TRUE) {                        //在判定已经照空之后的情况，我觉得这边也应该分成两中情况来讨论
      if(*inside_count == INSIDE_COUNT_MAX)     //就是当status为LEFT_NONE的时候，然后舵机往右拐
              *breakCar_flag = TRUE;            //当status为RIGHT_NONE的时候，然后舵机往左拐
          *inside_count = 0;
  } 
  else  {
      (*inside_count) = (*inside_count) + 1;
      if(*inside_count > INSIDE_COUNT_MAX) *inside_count = INSIDE_COUNT_MAX; 
  }

  if(PORTE_PE3 == 1)  {  //拨码开关控制
    
    //判断入弯后的连续照空，使得弯道中照空情况最大角度回转时加速，回正时减速
    if( abs(status - MID7) < 15){
        if(*outside_count == OUTSIDE_COUNT_MAX)  
            *breakCar_flag = TRUE;
        *outside_count = 0;
    }
    else {
        (*outside_count) = (*outside_count) + 1;
        if(*outside_count > OUTSIDE_COUNT_MAX) *outside_count = OUTSIDE_COUNT_MAX; 
    }
  }
    
  //转弯后回正刹车减速策略
  if((last_status == LEFT_NONE && status != LEFT_NONE)  ||  (last_status == RIGHT_NONE && status != RIGHT_NONE))
      *breakCar_flag = TRUE;

  
  return status;
} //GetLaserStatus


/* ================= CalculateAngle ====================
      desc: 计算舵机要调整的转角
      pre:  激光管的状态枚举类型
      Post: 舵机调整的转角
       
*/ 
int CalculateAngle(LASER_STATUS temp_laserStatus) {
  // Local Declarations
   int micro_delta0 = 19;   //微调0
  int micro_delta1 = 24;  //微调1
  int micro_delta2 = 44;  //微调2
  int micro_delta3 = 64;  //微调3
  int micro_delta4 = 84;  //微调4
  int micro_delta5 = 104;  //微调5
  
  int mid_delta0 = 128; //中调0
  int mid_delta1 = 148; //中调1
  int mid_delta2 = 168; //中调2
  int mid_delta3 = 188; //中调3
  int mid_delta4 = 208; //中调4
  
  int large_delta0 = 245; //大调0
  int large_delta1 = 260; //大调1
  int large_delta2 = 275; //大调2
  int large_delta3 = 290; //大调3
 
  int angle;
  
  // Statements
  switch( temp_laserStatus ) {
      case  LEFT_NONE:   {
          angle = PWM1_MID - large_delta3;   break;
      }
      case  LEFT0:  {
          angle = PWM1_MID - large_delta2;   break;
      }
      case  LEFT01:  {
          angle = PWM1_MID - large_delta1; break;
      }
      case LEFT1 : {
          angle = PWM1_MID - large_delta0; break;
      }
      case LEFT12:   {
          angle = PWM1_MID - mid_delta4; break;
      }
      case  LEFT2:  {
          angle = PWM1_MID - mid_delta3; break;
      }
      case  LEFT23:  {
          angle = PWM1_MID - mid_delta2; break;
      }
      case  LEFT3: {
          angle = PWM1_MID - mid_delta1; break;
      }
      case  LEFT34:   {
          angle = PWM1_MID - mid_delta0; break;
      }
      case  LEFT4:  {
          angle = PWM1_MID - micro_delta5; break;
      }
      case  LEFT45:  {
          angle = PWM1_MID - micro_delta4; break;
      }
      case  LEFT5: {
          angle = PWM1_MID - micro_delta3; break;
      }
      case  LEFT56:   {
          angle = PWM1_MID - micro_delta2; break;
      }
      case  LEFT6:  {
          angle = PWM1_MID - micro_delta1; break;
      }
      case  LEFT67:   {
          angle = PWM1_MID - micro_delta0; break;
      }
      case  MID7:  {
          angle = PWM1_MID; break;
      }
      case  RIGHT78:   {
          angle = PWM1_MID + micro_delta0; break;
      }
      case  RIGHT8:  {
          angle = PWM1_MID + micro_delta1; break;
      }
      case  RIGHT89:   {
          angle = PWM1_MID + micro_delta2; break;
      }
      case  RIGHT9:  {
          angle = PWM1_MID + micro_delta3; break;
      }
      case  RIGHT910:   {
          angle = PWM1_MID + micro_delta4; break;
      }
      case  RIGHT10:  {
          angle = PWM1_MID + micro_delta5; break;
      }
      case  RIGHT1011:  {
          angle = PWM1_MID + mid_delta0; break;
      }
      case  RIGHT11:  {
          angle = PWM1_MID + mid_delta1; break;
      }
      case  RIGHT1112:   {
          angle = PWM1_MID + mid_delta2; break;
      } 
      case  RIGHT12:  {
          angle = PWM1_MID + mid_delta3; break;
      }
      case  RIGHT1213:   {
          angle = PWM1_MID + mid_delta4; break;
      } 
      case  RIGHT13:  {
          angle = PWM1_MID + large_delta0; break;
      }
      case  RIGHT1314: {
          angle = PWM1_MID + large_delta1; break;
      }
      case  RIGHT14:{
          angle = PWM1_MID + large_delta2; break;
      }
      case  RIGHT_NONE:{
          angle = PWM1_MID + large_delta3; break;
      }
      default: break;
  }  
  
  return angle;    
} //CalculateAngle


/* ================= CalculateSpeed ====================
      desc: 计算速度
      pre:  脉冲数
      Post: 返回速度值
       
*/ 
int CalculateSpeed(int turnAngle, Bool stopCar_flag, byte inside_count, byte outside_count) {
  // Local Declarations
  int pwm3_superFast;
  int pwm3_fast;
  int pwm3_normal;
  int pwm3_slow;
  int speed;
 
  // Statements
  //选择拨码开关
  if(PORTA_PA6 == 0) {
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
  
  
  
  speed = pwm3_normal;
  PORTE |= 0B01100000;  //速度正常时绿色LED灯全灭
  if(stopCar_flag == TRUE) {
      speed = 1;
  } 
  else {     
      if ( abs(turnAngle - PWM1_MID) >= 170 ) {    
          speed = pwm3_slow;
          
      }
      else if( abs(turnAngle - PWM1_MID) <= 70 ) { 
          speed = pwm3_fast;
      }     
  }
  
  if(inside_count == INSIDE_COUNT_MAX) {
      speed = pwm3_superFast; 
      PORTE |= 0x00;   //直道加速时绿色LED灯全亮
  }
  
  if(outside_count == OUTSIDE_COUNT_MAX) {
      speed = pwm3_superFast; 
      PORTE |= 0x00;   //弯道加速时绿色LED灯全亮
  }
  
  return speed;
} //CalculateSpeed


/* ================= IsStartline ====================
      desc: 判断是否为起始线
      pre:  无
      Post: 返回起始线标志
       
*/ 
Bool IsStartline (byte temp_laser_array[]) {
  // Local Declarations
  int ptr,position,i;
  Bool flag = FALSE;
  char sm[LASER_MAX+1];
  char sp0[15] ={0,0,0,0,0,1,1,0,1,1,0,0,0,0,0};
  char sp1[15] ={0,0,0,0,1,1,0,0,1,1,0,0,0,0,0};
  char sp2[15] ={0,0,0,0,0,1,1,0,0,1,1,0,0,0,0};
 // char sp3[6] ={5,0,0,1,0,0};
  
  // Statements 
  ptr = 0;
  for(i=0;i<LASER_MAX;i++)
  {
	  sm[ptr+1] = temp_laser_array[ptr]; 
      ptr++; 
  }
 
       for(i=0;i<LASER_MAX;i++)
      if((sm[i+1] == sp0[i])||(sm[i+1] == sp1[i])||(sm[i+1] == sp0[i]))
          // if(CalculateAngle(15)==PWM1_MID)
        flag = TRUE;	
    
      return flag;
}
 
   /*
  sm[0] = ptr; 
 
  position = BM( sm, sp0, sm[0], sp0[0] );
  if(position < 0)  position = BM( sm, sp1, sm[0], sp1[0] );
  if(position < 0)  position = BM( sm, sp2, sm[0], sp2[0] );
  if(position < 0)  position = BM( sm, sp3, sm[0], sp3[0] );
  if(position > 0)  flag = TRUE;
  */
 
  
 //IsStartline


/* ================= CountStartlineFlag ====================
      desc: 得到经过起始线的次数
      pre:  经过起始线的次数
      Post: 返回经过起始线的次数
       
*/ 
byte  CountStartlineFlag (byte count, byte temp_laser_array[]) {
  // Local Declarations
  
  // Statements
  if( IsStartline(temp_laser_array) )
      count++;
  return count;
} // CountStartlineFlag


/* ================= CalculateLaserHitNum ====================
      desc: 计算照到黑线的激光管个数
      pre:  无
      Post: 返回照到黑线的激光管个数
    
*/ 
byte CalculateLaserHitNum (byte temp_laser_array[]) {
  // Local Declarations
  byte count = 0;
  int i = 0;
  // Statements
  for(i=0;i<LASER_MAX;i++) {
      if (temp_laser_array[i] == 1)
          count++;
  }
  return count;
} //CalculateLaserHitNum


/* ================= IsUsualRoad ====================
      desc: 判断是否正常道路（特殊道路 ----- 1.十字线、2.起始线、3.坡道）
      pre:  照到黑线的激光管个数
      Post: 返回正常道路标志
    
*/ 
Bool IsUsualRoad (byte count) {
  // Local Declarations
  Bool flag = TRUE;
  
  // Statements
  if ( count >= 3 )
      flag = FALSE;
  return flag;
} //IsUsualRoad
