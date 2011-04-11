/* ��Ϣ������
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                        
*˵    ��: �������ܳ�ת����ٶ���Ϣ   

	  Written by: swe07024 ����ٻ           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//��header file��
#include "dealInfo.h"

/* ================= GetLaserStatus ====================
      desc: �õ������״̬ö������
      pre:  1.�����״̬����  2.����ܲɼ���Ϣ���� 3,�յ����ߵļ���ܸ���
            4.�м䷶Χ�ļ�����յ����ߵĴ���   5.ɲ����־  
            6.�������ʷ״̬����  7.������տյĴ��� 
      Post: ���ؼ����״̬ö������
       
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
  
  //�жϳ�ֱ�����ͻȻ���� ��ʹ��ֱ�����٣����伱ɲ��
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
  
  if(out_flag == TRUE) {                        //���ж��Ѿ��տ�֮���������Ҿ������ҲӦ�÷ֳ��������������
      if(*inside_count == INSIDE_COUNT_MAX)     //���ǵ�statusΪLEFT_NONE��ʱ��Ȼ�������ҹ�
              *breakCar_flag = TRUE;            //��statusΪRIGHT_NONE��ʱ��Ȼ���������
          *inside_count = 0;
  } 
  else  {
      (*inside_count) = (*inside_count) + 1;
      if(*inside_count > INSIDE_COUNT_MAX) *inside_count = INSIDE_COUNT_MAX; 
  }

  if(PORTE_PE3 == 1)  {  //���뿪�ؿ���
    
    //�ж������������տգ�ʹ��������տ�������ǶȻ�תʱ���٣�����ʱ����
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
    
  //ת������ɲ�����ٲ���
  if((last_status == LEFT_NONE && status != LEFT_NONE)  ||  (last_status == RIGHT_NONE && status != RIGHT_NONE))
      *breakCar_flag = TRUE;

  
  return status;
} //GetLaserStatus


/* ================= CalculateAngle ====================
      desc: ������Ҫ������ת��
      pre:  ����ܵ�״̬ö������
      Post: ���������ת��
       
*/ 
int CalculateAngle(LASER_STATUS temp_laserStatus) {
  // Local Declarations
   int micro_delta0 = 19;   //΢��0
  int micro_delta1 = 24;  //΢��1
  int micro_delta2 = 44;  //΢��2
  int micro_delta3 = 64;  //΢��3
  int micro_delta4 = 84;  //΢��4
  int micro_delta5 = 104;  //΢��5
  
  int mid_delta0 = 128; //�е�0
  int mid_delta1 = 148; //�е�1
  int mid_delta2 = 168; //�е�2
  int mid_delta3 = 188; //�е�3
  int mid_delta4 = 208; //�е�4
  
  int large_delta0 = 245; //���0
  int large_delta1 = 260; //���1
  int large_delta2 = 275; //���2
  int large_delta3 = 290; //���3
 
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
      desc: �����ٶ�
      pre:  ������
      Post: �����ٶ�ֵ
       
*/ 
int CalculateSpeed(int turnAngle, Bool stopCar_flag, byte inside_count, byte outside_count) {
  // Local Declarations
  int pwm3_superFast;
  int pwm3_fast;
  int pwm3_normal;
  int pwm3_slow;
  int speed;
 
  // Statements
  //ѡ���뿪��
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
  PORTE |= 0B01100000;  //�ٶ�����ʱ��ɫLED��ȫ��
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
      PORTE |= 0x00;   //ֱ������ʱ��ɫLED��ȫ��
  }
  
  if(outside_count == OUTSIDE_COUNT_MAX) {
      speed = pwm3_superFast; 
      PORTE |= 0x00;   //�������ʱ��ɫLED��ȫ��
  }
  
  return speed;
} //CalculateSpeed


/* ================= IsStartline ====================
      desc: �ж��Ƿ�Ϊ��ʼ��
      pre:  ��
      Post: ������ʼ�߱�־
       
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
      desc: �õ�������ʼ�ߵĴ���
      pre:  ������ʼ�ߵĴ���
      Post: ���ؾ�����ʼ�ߵĴ���
       
*/ 
byte  CountStartlineFlag (byte count, byte temp_laser_array[]) {
  // Local Declarations
  
  // Statements
  if( IsStartline(temp_laser_array) )
      count++;
  return count;
} // CountStartlineFlag


/* ================= CalculateLaserHitNum ====================
      desc: �����յ����ߵļ���ܸ���
      pre:  ��
      Post: �����յ����ߵļ���ܸ���
    
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
      desc: �ж��Ƿ�������·�������· ----- 1.ʮ���ߡ�2.��ʼ�ߡ�3.�µ���
      pre:  �յ����ߵļ���ܸ���
      Post: ����������·��־
    
*/ 
Bool IsUsualRoad (byte count) {
  // Local Declarations
  Bool flag = TRUE;
  
  // Statements
  if ( count >= 3 )
      flag = FALSE;
  return flag;
} //IsUsualRoad
