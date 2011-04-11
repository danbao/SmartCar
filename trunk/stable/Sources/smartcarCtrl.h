/* 智能车控制库
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                             
*说    明:    

	Written by: swe07024 张苷倩           
  Date:       2010.7.19
  Update:     2010.7.19
  
*/

//【header file】
#include"dealInfo.h"   //信息处理库

//【constant definition】
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

//【function declaration】
void DerectionCtrl (int);  //转向控制
void SpeedCtrl (int,byte,byte*); //速度控制
void BreakCar (byte, Bool*); //紧急制动
void SmartcarInit(void);     //智能车启动初始化
void StartCarDelay (void);   //启动车前的延时2秒