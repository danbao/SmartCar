/* 通用函数库
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                      
*说    明:    

	Written by: swe07024 张苷倩           
  Date:       2010.7.19
*/

//【header file】
#include <stdlib.h>

//【constant definition】 

//【function declaration】
static int GetDist(char,char[]);        //BM模式串匹配中间过程
extern int SeparateInt (int,char[]);    //整型各位数分离
extern int BM( char[], char[], int, int );//BM模式串匹配 


