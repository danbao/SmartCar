/* ���ܳ����ƿ�
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                             
*˵    ��:    

	Written by: swe07024 ����ٻ           
  Date:       2010.7.19
  Update:     2010.7.19
  
*/

//��header file��
#include"dealInfo.h"   //��Ϣ�����

//��constant definition��
#define ANGLE_DELTA 190

#define STRAIGHT_PULSE_MAX0 220
#define MORE_STRAIGHT_PULSE_MAX0 200
#define MID_STRAIGHT_PULSE_MAX0 190
#define LEAST_STRAIGHT_PULSE_MAX0 185

#define STRAIGHT_PULSE_MAX1 250
#define MORE_STRAIGHT_PULSE_MAX1 250
#define MID_STRAIGHT_PULSE_MAX1 230
#define LEAST_STRAIGHT_PULSE_MAX1 210

#define STRAIGHT_PULSE_MAX2 280
#define MORE_STRAIGHT_PULSE_MAX2 270
#define MID_STRAIGHT_PULSE_MAX2 250
#define LEAST_STRAIGHT_PULSE_MAX2 240

#define STRAIGHT_PULSE_MAX3 320
#define MORE_STRAIGHT_PULSE_MAX3 290
#define MID_STRAIGHT_PULSE_MAX3 270
#define LEAST_STRAIGHT_PULSE_MAX3 260

#define SPEED_P 10
#define SPEED_D 10
#define SPEED_LEAST_P 4
#define SPEED_LEAST_D 5
#define SPEED_MID_P 4
#define SPEED_MID_D 5
#define SPEED_MORE_P 4
#define SPEED_MORE_D 5

//��function declaration��
void DerectionCtrl (int);  //ת�����
void SpeedCtrl (int,byte,byte*); //�ٶȿ���
void BreakCar (byte, Bool*); //�����ƶ�
void SmartcarInit(void);     //���ܳ�������ʼ��
void StartCarDelay (void);   //������ǰ����ʱ2��