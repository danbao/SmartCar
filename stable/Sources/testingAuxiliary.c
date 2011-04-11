/* 测试辅助函数
*工 程 名: 5th Smartcar v3.1_15Laser.mcp                                                                                         
*说    明:   

	  Written by: swe07024 张苷倩           
    Date:       2010.7.19
    Update:     2010.7.19
*/

//【header file】
#include "testingAuxiliary.h"
#include "dealInfo.h"


//【function definitions】
/* ================= SCISend ====================
      desc: SCI串口发送一个字符
      pre:  要发送的字符
      Post: 无
       
*/ 
void SCISend(unsigned char o)
{
    while (!(SCI0SR1&0x80));
    SCI0DRH=0;
    SCI0DRL=o;
}  //SCISend


/* ================= SendOneData ====================
      desc: SCI串口发送一个数据
      pre:  要发送的数据
      Post: 无
       
*/ 
void SendOneData(byte data)  {
    if(data == 0)
        SCISend('0');
    else if(data == 1)
        SCISend('1');
} //SendOneData


/* ================= SendSeparator ====================
      desc: SCI串口发送分隔信号“====”，当前后激光管状态不一样时才打印
      pre:  无
      Post: 无
       
*/ 
void SendSeparator(void)  {
   int i;
   for(i=0;i<4;i++)
      SCISend('=');  
} //SendSeparator

 
/* ================= SendSteerInfo ====================
      desc: SCI串口发送当前舵机转角信息
      pre:  无
      Post: 无
       
*/ 
void SendSteerInfo (void) {
    int i,length;
    char str[6] = "";
    int data = PWMDTY01;
    length = SeparateInt(data,str);
	  for(i=0;i<5;i++)
	      SCISend(' ');
	  for(i=length-1; i>=0; i--)
		    SCISend(str[i]);
} //SendSteerInfo


/* ================= SendSpeed ====================
      desc: SCI串口发送当前速度
      pre:  无
      Post: 无
       
*/ 
void SendSpeed (void) {
    int i,length;
    char str[6] = "";
    int data = PWMDTY23;
    length = SeparateInt(data,str);
	  for(i=0;i<5;i++)
	      SCISend(' ');
	  for(i=length-1; i>=0; i--)
		    SCISend(str[i]);
} //SendSpeed


/* ================= SendLaserStatus ====================
      desc: SCI串口发送当前激光管状态枚举类型
      pre:  无
      Post: 无
       
*/ 
void SendLaserStatus(byte laser_status) {
   int i;
   for(i=0;i<4;i++)
      SCISend(' '); 
    
   switch( laser_status ) {
      case  LEFT_NONE:   {
          SCISend('p');   break;
      }
      case  LEFT0:  {
          SCISend('n');   break;
      }
      case  LEFT01:  {
          SCISend('m'); break;
      }
      case LEFT1 : {
          SCISend('l'); break;
      }
      case LEFT12:   {
          SCISend('k'); break;
      }
      case  LEFT2:  {
          SCISend('j'); break;
      }
      case  LEFT23:  {
          SCISend('i'); break;
      }
      case  LEFT3: {
          SCISend('h'); break;
      }
      case  LEFT34:   {
          SCISend('g'); break;
      }
      case  LEFT4:  {
          SCISend('f'); break;
      }
      case  LEFT45:  {
          SCISend('e'); break;
      }
      case  LEFT5: {
          SCISend('d'); break;
      }
      case  LEFT56:   {
          SCISend('c'); break;
      }
      case  LEFT6:  {
          SCISend('b'); break;
      }
      case  LEFT67:   {
          SCISend('a'); break;
      }
      case  MID7:  {
          SCISend('X'); break;
      }
      case  RIGHT78:   {
          SCISend('A'); break;
      }
      case  RIGHT8:  {
          SCISend('B'); break;
      }
      case  RIGHT89:   {
          SCISend('C'); break;
      }
      case  RIGHT9:  {
          SCISend('D'); break;
      }
      case  RIGHT910:   {
          SCISend('E'); break;
      }
      case  RIGHT10:  {
          SCISend('F'); break;
      }
      case  RIGHT1011:  {
          SCISend('G'); break;
      }
      case  RIGHT11:  {
          SCISend('H');break;
      }
      case  RIGHT1112:   {
          SCISend('I'); break;
      } 
      case  RIGHT12:  {
          SCISend('J'); break;
      }
      case  RIGHT1213:   {
          SCISend('K'); break;
      } 
      case  RIGHT13:  {
          SCISend('L'); break;
      }
      case  RIGHT1314: {
          SCISend('M'); break;
      }
      case  RIGHT14:{
          SCISend('N'); break;
      }
      case  RIGHT_NONE:{
          SCISend('P'); break;
      }
      default: break;
  }  
} //SendLaserStatus
 

/* ================= SendTempPulse ====================
      desc: SCI串口发送周期测速的脉冲数
      pre:  周期测速的脉冲数
      Post: 无
       
*/ 
void SendTempPulse(unsigned int temp_pulse) {
    int i,length;
    char str[6] = "";
    length = SeparateInt(temp_pulse,str);
	  for(i=0;i<5;i++)
	      SCISend(' ');
	  for(i=length-1; i>=0; i--)
		    SCISend(str[i]);
} //SendTempPulse(



/* ================= SendSmartcarInfo ====================
      desc: SCI串口发送当前激光管采集信息
      pre:  1当前激光管采集数组，2当前激光管状态
      Post: 无
       
*/ 
void SendSmartcarInfo(byte temp_laser_array[],byte temp_laserStatus,byte last_laserStatus,unsigned int temp_pulse) {
    int i; 
    for(i=LASER_MAX-1;i>=0;i--)             //发送激光管信息数组
        SendOneData(temp_laser_array[i]);
 
    SendLaserStatus(temp_laserStatus);//发送激光管状态
    SendSteerInfo ();  //发送舵机转角
    SendSpeed();       //发送速度
    SendTempPulse(temp_pulse);   //发送周期测速的脉冲数
   
    if(temp_laserStatus != last_laserStatus)      //若状态发生改变，发送分隔符
        SendSeparator();
    SCISend(13); 
    SCISend(10);    
} //SendSmartcarInfo
 