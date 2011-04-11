/* 芯片初始化库
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                          
*说    明:    

	Written by: swe07024 张苷倩           
  Date:       2010.7.19
*/

//【header file】
#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */

//【constant definition】

//【function declaration】
static void PWMInit (void);  //PWM输出
static void PITInit (void);  //定时器
static void PLLInit (void);  //时钟频率
static void GIOInit (void);  //普通IO口
static void SCIInit (void);  //SCI串口
static void PACNTInit(void); //测速模块
extern void MCUInit (void);  //芯片总初始化

