/***********************************************************
����MC9S12XS128�๦�ܿ����� 
Designed by ����
E-mail:chiusir@yahoo.cn
����汾:V1.1
������:2010��6��16��
�����Ϣ�ο����е�ַ��
��վ��  http://www.lqist.cn
�Ա��꣺http://shop36265907.taobao.com
------------------------------------
Code Warrior 5.0
Target : MC9S12XS128
Crystal: 16.000Mhz
busclock:16.000MHz
pllclock:32.000MHz 
------------------------------------  
����ʹ��˵����
�������ѧϰ����ҵĿ������ϵ������Ȩ�ؾ���
SD����д�������飬Ĭ��Ϊ2G microSD��  

ʹ�ò��裺
1.���ϴ�����
2.�򿪴��ڹ���,��������Ϊ9600,n,8,1
3.����microSD;
4.���ر�������Сϵͳ��,Ȼ�����е�Ƭ��
5.���ڵ��Թ����п��Կ�����ʾ
6.�����ʼ���ɹ������ȶ�ȡSD������������������ò�������
7.Ȼ��дһ������

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
  SD_Init();            //��ʼ��spi��  	 
  while(SD_Reset())     //��λ�Ƿ�ɹ������ɹ�LED��һ��
  {           
	  printp("\nSD card init failed!Please insert your card !\n");
	  Dly_ms(500);	  
	}
	PORTB=0X00;          //��λ�Ƿ�ɹ����ɹ�LEDȫ����
  SPI_High_Rate();   	 //SPI������ٲ���ģʽ  
  printp("\nSD card init is ok! \nStartint to reading...\n");    
	Dly_ms(200);         //�Ե�Ƭ��,��LED��
  PORTB=0Xff;   
  
  //��ȡSD������������
	if(!(Rd_Block(0x00, RXBUF))){
	  
	  PORTB=RXBUF[511]; //LED��ʾ�����ڶ����ֽڵ���ֵ
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
  //д/���SD��0X1FF�������� 
  New_Buf8(RXBUF,'x');
  if(!(Wt_Block(RdWrAdd+2,RXBUF)))    //д0x202��
  {	  
	  PORTB=RXBUF[511]; //LED��ʾ�����ڶ����ֽڵ���ֵ
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
  { //����������û�����
    //����ȡ0x200-0x20a��10��������ݲ����
    for(cnt=0;cnt<10;cnt++)
      if(!(Rd_Block(cnt+RdWrAdd, RXBUF)))
      {    	   
    	  printp("\nBlock 0x%04x is as fellow:\n",cnt+RdWrAdd);
    	  View_Buf8(RXBUF);  
    	}
  }
  return;
}//end




