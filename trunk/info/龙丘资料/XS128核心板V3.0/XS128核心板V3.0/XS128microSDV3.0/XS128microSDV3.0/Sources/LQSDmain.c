/***********************************************************
龙丘MC9S12XS128多功能开发板 
Designed by 龙丘
E-mail:chiusir@yahoo.cn
软件版本:V1.1
最后更新:2010年6月16日
相关信息参考下列地址：
网站：  http://www.lqist.cn
淘宝店：http://shop36265907.taobao.com
------------------------------------
Code Warrior 5.0
Target : MC9S12XS128
Crystal: 16.000Mhz
busclock:16.000MHz
pllclock:32.000MHz 
------------------------------------  
程序使用说明：
程序仅供学习，商业目的请联系龙丘，侵权必究！
SD卡读写操作试验，默认为2G microSD卡  

使用步骤：
1.插上串口线
2.打开串口工具,速率设置为9600,n,8,1
3.插上microSD;
4.下载本程序到最小系统板,然后运行单片机
5.串口调试工具中可以看到提示
6.如果初始化成功，会先读取SD卡的引导区，并输出该部分内容
7.然后写一个区，

************************************************************/
#include "derivative.h"
#include "LQprintp.h"  
#include <stdio.h>         
#include <string.h>  
#include "LQSDdriver.h"

  
byte RXBUF[512]={0}; 
 
void CLS_Buf(byte buffer[],byte L)
{
    int i;     
    for(i=0;i<L;i++)	//128[word]*16[blk]=8192[byte]
		*(buffer+i)=0;
}

#pragma CODE_SEG DEFAULT      
void main(void)
{  
	word RdWrAdd=0xff,cnt=0; 
	
	Init_Dev();  
  PORTB=0x00;
  putstr("\nLongQiu s.&t. MicroSD reading and writing:\n");     
  EnableInterrupts;
  
  
  PORTB=0Xf0;
  SD_Init();            //初始化spi口  	 
  while(SD_Reset())     //复位是否成功，不成功LED灭一半
  {           
	  printp("\nSD card init failed!Please insert your card !\n");
	  Dly_ms(500);	  
	}
	PORTB=0X00;          //复位是否成功，成功LED全部亮
  SPI_High_Rate();   	 //SPI进入高速操作模式  
  printp("\nSD card init is ok! \nStartint to reading...\n");    
	Dly_ms(200);         //稍等片刻,让LED亮
  PORTB=0Xff;   
  
  //读取SD卡引导区数据
	if(!(Rd_Block(0x00, RXBUF))){
	  
	  PORTB=RXBUF[511]; //LED显示倒数第二个字节的数值
	  printp("\nSD card reading is ok!\nBootload area is as fellow:\n");
	  View_Buf8(RXBUF);  
	}
	else
	{
	  PTM_PTM1=1;
    PTM_PTM0=0;       
	  printp("\nSD card reading failed!\n"); 
	}	
  RdWrAdd=0X200;
  //写/清空SD卡0X1FF区的数据 
  New_Buf8(RXBUF,'x');
  if(!(Wt_Block(RdWrAdd+2,RXBUF)))    //写0x202块
  {	  
	  PORTB=RXBUF[511]; //LED显示倒数第二个字节的数值
	  printp("\nSD card writing is ok!\n");
	}
	else
	{ 	  
    PTM_PTM0=0;       
	  printp("\nSD card writing failed!\n"); 
	}
  Dly_ms(2000);  
  
  RdWrAdd=0X200;
  for(;;)
  { //在这里添加用户代码
    //随便读取0x200-0x20a这10个块的内容并输出
    for(cnt=0;cnt<10;cnt++)
      if(!(Rd_Block(cnt+RdWrAdd, RXBUF)))
      {    	   
    	  printp("\nBlock 0x%04x is as fellow:\n",cnt+RdWrAdd);
    	  View_Buf8(RXBUF);  
    	}
  }
  return;
}//end




