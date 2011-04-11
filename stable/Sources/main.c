/* ������
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                       
*˵    ��:   

	  Written by: swe07024 ����ٻ           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//��header file��
#include "Includes.h"      /* ��ͷ�ļ� */

//��global ariables�� 
byte g_countPIT0 = 0;                //�����Լ���ܷ�ʱ�����жϼ�����1--4ѭ���� 
byte g_temp_laser_array[LASER_MAX];  //��ǰ�������Ϣ��������
byte g_temp_pulse = 0;               //20msһ�β�õĵ�ǰ����ֵ

//��function definitions��
/* ================= main ====================
      desc: ������ں���
      pre:  ��
      Post: ��       
*/
void main(void) {
    // Local Declarations
    byte laser_history_array[LASER_HISTORY_MAX]; //�������ʷ״̬����
  
  	Bool temp_usualRoad_flag = TRUE;      //��ǰ�ж��Ƿ�����·�α�־
  	Bool last_usualRoad_flag = TRUE;      //�ϴ��ж��Ƿ�����·�α�־
  	Bool stopCar_flag = FALSE;            //ͣ����־
  	Bool breakCar_flag = FALSE;           //ɲ����־
  
  	byte startlineFlag_count = 0;         //������ʼ�ߵĴ���
  	byte laser_hitNum = 1;                //�յ����ߵļ���ܸ���
  	byte inside_count = INSIDE_COUNT_MAX; //����������ں��߷�Χ�ڵĴ���
  	byte outside_count = 0;               //����������ں�����Ĵ���
  	byte last_error = 0;                  //ֱ���������ٿ��Ƶ��ϴ����
  	 
  	LASER_STATUS last_laserStatus = MID7;  //�ϴμ����״̬
  	LASER_STATUS temp_laserStatus = MID7;  //��ǰ�����״̬
  	int last_turnAngle = PWM1_MID;     //�ϴζ�������ĽǶ�
  	int temp_turnAngle = PWM1_MID;     //��ǰ�����Ҫ�����ĽǶ�	
  	int last_speed = PWM3_FAST0;   //�ϴ��ٶ�
  	int temp_speed = PWM3_FAST0;   //��ǰ�ٶ� 
  	
  	int i;
    int testcount=0;  //���ͼ������Ϣ����ֵ����
  	for(i=0;i<LASER_HISTORY_MAX;i++) {
  	    laser_history_array[i] = MID7;
  	}
  	
    // Statements
    DisableInterrupts;
    MCUInit();
  	SmartcarInit();
  	EnableInterrupts;
  
    for(;;) {  
         if(PITINTE_PINTE0 == 0) {    //��PIT0�ɼ��ж�Ϊ��,����·��Ϣ�ɼ����
              laser_hitNum = 15 - CalculateLaserHitNum(g_temp_laser_array);
              temp_usualRoad_flag =  IsUsualRoad (laser_hitNum); //�ж��Ƿ�Ϊ������·
              if (temp_usualRoad_flag) {
                  temp_laserStatus = GetLaserStatus(last_laserStatus,g_temp_laser_array,laser_hitNum,&inside_count,&breakCar_flag,laser_history_array,&outside_count); //�õ���ǰ�����״̬
                  temp_turnAngle = CalculateAngle(temp_laserStatus); //�õ������Ҫ������ת��      
                  temp_speed = CalculateSpeed (temp_turnAngle,stopCar_flag,inside_count,outside_count); //�õ���Ҫ������ٶ�
              } 
              else {
                  if((last_usualRoad_flag == TRUE)&&(laser_hitNum>=8&&laser_hitNum<=11)) {          //һ��ִ��
                      startlineFlag_count = CountStartlineFlag(startlineFlag_count,g_temp_laser_array); //����С��������ʼ�ߵĴ���
                      if(startlineFlag_count == 2)  
                            stopCar_flag = TRUE; //���ǵڶ��ξ�����ʼ�ߣ�ͣ����־��λ����ͣ��
                      StopCar(stopCar_flag);      
                  }
              } /**/
            
              
       testcount++;
              
              if(testcount%50==0){
                
               testcount=1;   
             SendSmartcarInfo(g_temp_laser_array,temp_laserStatus,last_laserStatus,g_temp_pulse);//���ͼ������Ϣ
                  } /*   */
              PITINTE_PINTE0 = 1;    //��PIT0�ɼ��ж� 
        }           
        DerectionCtrl(temp_turnAngle); //�������
        
        if(breakCar_flag == TRUE) {  //��ֱ�����䣬��ת����ɲ��
            BreakCar(g_temp_pulse, &breakCar_flag);
        }  
        else
            SpeedCtrl(temp_speed,g_temp_pulse,&last_error);         //������ת�ٶ�
         
        last_speed = temp_speed;                        //���浱ǰ�ٶ�
        last_laserStatus = temp_laserStatus;            //���浱ǰ�����״̬
        last_turnAngle = temp_turnAngle;                //���浱ǰ���ת��
        last_usualRoad_flag = temp_usualRoad_flag;      //���浱ǰ�Ƿ�������·�ı�־ 
        
        for(i=LASER_HISTORY_MAX-1;i>0;i--){             //���漤�����ʷ״̬
            laser_history_array[i] =  laser_history_array[i-1];   
        }
        laser_history_array[0] = temp_laserStatus;
    }
} //main


#pragma CODE_SEG NON_BANKED 
//��interrupt definitions��
/* ================= PIT0_ISR ====================
      desc: PIT���ڶ�ʱ�жϣ����ڿ��Ƽ��⴫������ʱ��
      pre:  ��
      Post: ��       
*/ 
void interrupt 66 PIT0_ISR(void) {
    g_countPIT0 ++;
    if(g_countPIT0 == 5) {
         g_countPIT0 = 0;
         PITINTE_PINTE0 = 0;
    }  
    /*�����ѭ������˳��Ϊ ------- ��1�飨1,6,11������2�飨2,7,12������3�飨3,8,13������4�飨4,9,14������0�飨0,5,10��
      ÿ�ν��жϣ����ϴ�����һ�鼤����ȸ�ֵ���ٻ���һ��ļ������
    */                                                    
   if(g_countPIT0 == 0) {   
        g_temp_laser_array[4] = PORTB_PB1; //���յ�4�飨4,9,14�� 
    //StartCarDelay1 ()    ;
        g_temp_laser_array[9] = PORTB_PB3; //������0�飨0,5,10��
        g_temp_laser_array[14] = PORTB_PB4;
        PORTA = 0B00000001; 
    }
    else if(g_countPIT0 == 1)   {    
        g_temp_laser_array[0] = PORTB_PB0; //���յ�0�飨0,5,10��   
        g_temp_laser_array[5] = PORTB_PB1; //������1�飨1,6,11��
        g_temp_laser_array[10] = PORTB_PB3;
        PORTA = 0B00000010;        
    }
    else if(g_countPIT0 == 2)   {    
        g_temp_laser_array[1] = PORTB_PB0; //���յ�1�飨1,6,11��
        g_temp_laser_array[6] = PORTB_PB2; //������2�飨2,7,12��
        g_temp_laser_array[11] = PORTB_PB3;
        PORTA = 0B00000100;
    }
    else if(g_countPIT0 == 3)   {  
        g_temp_laser_array[2] = PORTB_PB0; //���յ�2�飨2,7,12��  
        g_temp_laser_array[7] = PORTB_PB2; //������3�飨3,8,13��
        g_temp_laser_array[12] = PORTB_PB4;
        PORTA = 0B00001000;
    }
    else if(g_countPIT0 == 4)   {  
        g_temp_laser_array[3] = PORTB_PB1; //���յ�3�飨3,8,13��  
        g_temp_laser_array[8] = PORTB_PB2; //������4�飨4,9,14��
        g_temp_laser_array[13] = PORTB_PB4;
        PORTA = 0B00010000;
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
 } //PIT1_ISR




