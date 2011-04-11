/* 信息处理库
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                          
*说    明:    

	Written by: swe07024 张苷倩           
  Date:       2010.7.19
  Update:     2010.7.19
*/

//【header file】
#include <stdtypes.h>
#include "generalFunc.h"
#include "pickInfo.h"  //信息采集库


//【type declaration】
/* ============== 激光管状态枚举类型 LASER_STATUS ================ 
 LEFT_NONE (0) ------ 左空     
     LEFT0 (1) ------ 左0      LEFT01 (2) ------ 左0左1     
     LEFT1 (3) ------ 左1      LEFT12 (4) ------ 左1左2
     LEFT2 (5) ------ 左2      LEFT23 (6) ------ 左2左3    
     LEFT3 (7) ------ 左3      LEFT34 (8) ------ 左3左4
     LEFT4 (9) ------ 左4      LEFT45 (10) ------左4左5    
     LEFT5 (11) ------左5      LEFT56 (12) ------左5左6
     LEFT6 (13) ------左6      LEFT67 (14) ------左6左7 
 MID7 (15) ------ 中7          
     RIGHT78 (16) ------右16        RIGHT8 (17) ------右8    
     RIGHT89 (18) ------右8右9      RIGHT9 (19) ------右9         
    RIGHT910 (20) ------右9右10    RIGHT10 (21) ------右10    
   RIGHT1011 (22) ------右10右11   RIGHT11 (23) ------右11        
   RIGHT1112 (24) ------右11右12   RIGHT12 (25) ------右12    
   RIGHT1213 (26) ------右12右13   RIGHT13 (27) ------右13        
   RIGHT1314 (28) ------右13右14   RIGHT14 (29) ------右14 
  RIGHT_NONE (30) ------右空  
*/    
typedef enum {                               
  LEFT_NONE, LEFT0, LEFT01,LEFT1, LEFT12, LEFT2, LEFT23, LEFT3, LEFT34, LEFT4, LEFT45, LEFT5, LEFT56, LEFT6, LEFT67, MID7,
  RIGHT78, RIGHT8, RIGHT89, RIGHT9, RIGHT910, RIGHT10, RIGHT1011, RIGHT11, RIGHT1112, RIGHT12, RIGHT1213, RIGHT13,RIGHT1314, RIGHT14, RIGHT_NONE    
} LASER_STATUS; 


/* ===========小车相对黑车位置枚举类型 CAR_POSITION ================ 
  MIDDLE (0) ------ 正中     
    LEFT (1) ------ 偏左   FULL_LEFT (2) ------ 完全偏左     
   RIGHT (3) ------ 偏右  FULL_RIGHT (4) ------ 完全偏右
*/    
typedef enum {                               
  MIDDLE, LEFT, FULL_LEFT, RIGHT, FULL_RIGHT    
} CAR_POSITION; 


//【constant definition】
#define PWM1_MID  1488   //舵机中间
#define PWM1_MAXR 1778   //舵机最左
#define PWM1_MAXL 1198   //舵机最右

#define PWM3_SLOW0 45     //速度慢  ( 电压 = 4.48v)
#define PWM3_FAST0 53     //速度快  ( 电压 = 3.67v )
#define PWM3_NORMAL0 50   //速度正常 ( 电压 = 3.2v )
#define PWM3_SUPER_FAST0 51  //直道速度  ( 电压 = 5.5v )

#define PWM3_SLOW1 50     //速度慢  ( 电压 = 4.48v)
#define PWM3_FAST1 56     //速度快  ( 电压 = 3.67v )
#define PWM3_NORMAL1 53   //速度正常 ( 电压 = 3.2v )
#define PWM3_SUPER_FAST1 66  //直道速度  ( 电压 = 5.5v )


#define PWM5_BREAK 60       //反向刹车速度PWM值   60

#define CURVE_PULSE 80     //入弯脉冲数极限值0

#define INSIDE_COUNT_MAX 50  //连续直道次数计数 
#define OUTSIDE_COUNT_MAX 30 //连续照不到黑线次数计数 


//【function declaration】
int  CalculateSpeed (int,Bool,byte,byte);    //计算速度
Bool IsStartline (byte[]);         //判断是否为起始线
byte  CountStartlineFlag (byte,byte[]);  //计算经过起始线的次数
int  CalculateAngle (LASER_STATUS);   //计算舵机要调整的转角
LASER_STATUS GetLaserStatus (LASER_STATUS,byte[],byte, byte*, Bool*,byte[],byte*); //得到激光管状态的枚举类型
byte  CalculateLaserHitNum (byte[]); //计算照到黑线的激光管个数
Bool IsUsualRoad (byte);       //判断是否正常道路   

                                   