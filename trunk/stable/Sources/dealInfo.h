/* ��Ϣ�����
*�� �� ��: 5th Smartcar v3.1_15Laser.mcp                                                                                          
*˵    ��:    

	Written by: swe07024 ����ٻ           
  Date:       2010.7.19
  Update:     2010.7.19
*/

//��header file��
#include <stdtypes.h>
#include "generalFunc.h"
#include "pickInfo.h"  //��Ϣ�ɼ���


//��type declaration��
/* ============== �����״̬ö������ LASER_STATUS ================ 
 LEFT_NONE (0) ------ ���     
     LEFT0 (1) ------ ��0      LEFT01 (2) ------ ��0��1     
     LEFT1 (3) ------ ��1      LEFT12 (4) ------ ��1��2
     LEFT2 (5) ------ ��2      LEFT23 (6) ------ ��2��3    
     LEFT3 (7) ------ ��3      LEFT34 (8) ------ ��3��4
     LEFT4 (9) ------ ��4      LEFT45 (10) ------��4��5    
     LEFT5 (11) ------��5      LEFT56 (12) ------��5��6
     LEFT6 (13) ------��6      LEFT67 (14) ------��6��7 
 MID7 (15) ------ ��7          
     RIGHT78 (16) ------��16        RIGHT8 (17) ------��8    
     RIGHT89 (18) ------��8��9      RIGHT9 (19) ------��9         
    RIGHT910 (20) ------��9��10    RIGHT10 (21) ------��10    
   RIGHT1011 (22) ------��10��11   RIGHT11 (23) ------��11        
   RIGHT1112 (24) ------��11��12   RIGHT12 (25) ------��12    
   RIGHT1213 (26) ------��12��13   RIGHT13 (27) ------��13        
   RIGHT1314 (28) ------��13��14   RIGHT14 (29) ------��14 
  RIGHT_NONE (30) ------�ҿ�  
*/    
typedef enum {                               
  LEFT_NONE, LEFT0, LEFT01,LEFT1, LEFT12, LEFT2, LEFT23, LEFT3, LEFT34, LEFT4, LEFT45, LEFT5, LEFT56, LEFT6, LEFT67, MID7,
  RIGHT78, RIGHT8, RIGHT89, RIGHT9, RIGHT910, RIGHT10, RIGHT1011, RIGHT11, RIGHT1112, RIGHT12, RIGHT1213, RIGHT13,RIGHT1314, RIGHT14, RIGHT_NONE    
} LASER_STATUS; 


/* ===========С����Ժڳ�λ��ö������ CAR_POSITION ================ 
  MIDDLE (0) ------ ����     
    LEFT (1) ------ ƫ��   FULL_LEFT (2) ------ ��ȫƫ��     
   RIGHT (3) ------ ƫ��  FULL_RIGHT (4) ------ ��ȫƫ��
*/    
typedef enum {                               
  MIDDLE, LEFT, FULL_LEFT, RIGHT, FULL_RIGHT    
} CAR_POSITION; 


//��constant definition��
#define PWM1_MID  1488   //����м�
#define PWM1_MAXR 1778   //�������
#define PWM1_MAXL 1198   //�������

#define PWM3_SLOW0 45     //�ٶ���  ( ��ѹ = 4.48v)
#define PWM3_FAST0 53     //�ٶȿ�  ( ��ѹ = 3.67v )
#define PWM3_NORMAL0 50   //�ٶ����� ( ��ѹ = 3.2v )
#define PWM3_SUPER_FAST0 51  //ֱ���ٶ�  ( ��ѹ = 5.5v )

#define PWM3_SLOW1 50     //�ٶ���  ( ��ѹ = 4.48v)
#define PWM3_FAST1 56     //�ٶȿ�  ( ��ѹ = 3.67v )
#define PWM3_NORMAL1 53   //�ٶ����� ( ��ѹ = 3.2v )
#define PWM3_SUPER_FAST1 66  //ֱ���ٶ�  ( ��ѹ = 5.5v )


#define PWM5_BREAK 60       //����ɲ���ٶ�PWMֵ   60

#define CURVE_PULSE 80     //��������������ֵ0

#define INSIDE_COUNT_MAX 50  //����ֱ���������� 
#define OUTSIDE_COUNT_MAX 30 //�����ղ������ߴ������� 


//��function declaration��
int  CalculateSpeed (int,Bool,byte,byte);    //�����ٶ�
Bool IsStartline (byte[]);         //�ж��Ƿ�Ϊ��ʼ��
byte  CountStartlineFlag (byte,byte[]);  //���㾭����ʼ�ߵĴ���
int  CalculateAngle (LASER_STATUS);   //������Ҫ������ת��
LASER_STATUS GetLaserStatus (LASER_STATUS,byte[],byte, byte*, Bool*,byte[],byte*); //�õ������״̬��ö������
byte  CalculateLaserHitNum (byte[]); //�����յ����ߵļ���ܸ���
Bool IsUsualRoad (byte);       //�ж��Ƿ�������·   

                                   