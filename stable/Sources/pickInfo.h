/* 信息采集库
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                           
*说    明:    

	Written by: swe07024 张苷倩           
  Date:       2010.7.19
*/

//【header file】
#include "derivative.h"

//【function declaration】
void SaveLaser (byte[],byte[]);    //保存激光头采集路况

//【constant definition】
#define LASER_MAX 15          //激光管数量
#define LASER_HISTORY_MAX 20  //激光管状态历史
 