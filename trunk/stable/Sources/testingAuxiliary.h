/* 测试辅助库
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
static void SCISend(unsigned char); //SCI串口发送一个字符
static void SendOneData(byte);      //SCI串口发送一个数据
static void SendSeparator(void);    //SCI串口发送分隔信号“====”，当前后激光管状态不一样时才打印
static void SendLaserStatus(byte);  //SCI串口发送激光管状态枚举类型
static void SendSteerInfo (void);   //SCI串口发送当前舵机转角信息
static void SendTempPulse(unsigned int); //SCI串口发送周期测速的脉冲数
extern void SendSmartcarInfo(byte[],byte,byte,unsigned int); //SCI串口发送当前激光管采集信息(包括整个数组、状态)