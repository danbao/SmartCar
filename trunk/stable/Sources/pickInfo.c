/* 信息采集函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                        
*说    明:   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//【header file】
#include "pickInfo.h"



//【function definitions】
/* ================= SaveLaser ====================
      desc: 保存激光头采集路况
      pre:  1.激光管信息保存数组 2.激光管信息接收数组
      Post: 无
       
*/ 
void SaveLaser (byte last_laser_array[], byte temp_laser_array[]) {
  // Local Declarations
  int i = 0;
  // Statements
  for(i=0;i<LASER_MAX;i++) {
      last_laser_array[i] = temp_laser_array[i];  
  }
} //SaveLaser


