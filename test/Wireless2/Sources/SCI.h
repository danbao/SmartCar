/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.04.11
	说明：串口调用及无线模块
----------------------------------------------*/
/*--------------------------------------------
SCI_RXD: 串口接收函数
编写日期：20110411
----------------------------------------------*/
char SCI_RXD(void)
{
    char ch; 
    while (!(SCI0SR1 & 0x20));       //等待接收数据完毕
    SCI0SR1_RDRF = 1;
    ch = SCI0DRL;
    return ch;
}
/*---------------------------------------------
SCISend: 串口输出显示函数(显示单个字符)
输入参数：ch：显示的字符；
编写日期：20110411
-----------------------------------------------*/
void SCISend(unsigned char ch)
{ 
  if (ch == '\n')  
  {
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0d;   
      while(!(SCI0SR1&0x80)) ;     
      SCI0DRL= 0x0a;               
     return;
  } 
  else while (!(SCI0SR1&0x80));
    SCI0DRH=0;
    SCI0DRL=ch;
}
/*---------------------------------------------
LCD_write_cizu: 串口输出显示函数(显示字符串)
输入参数：ch：显示的字符串
编写日期：20110411
-----------------------------------------------*/
void SCISend_chars(const signed char ch[])
 {
 int i;
 for(i=0;i<strlen(ch);i++) {
 SCISend(ch[i]);
 }
 SCISend('\n');
 }
 /*---------------------------------------
SCI_Init: SCI初始化
编写日期：200110411
-----------------------------------------  */
static void SCI_Init(void)  //SCI
{
    SCI0CR1=0x00;
    SCI0CR2=0x2c;
     SCI0BD=260;                     //设置波特率公式=总线频率/所需要的波特率/16=所要设置的值;
                  
}
 /*---------------------------------------
无线串口中断
编写日期：200110411
-----------------------------------------  */         
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1;                  	 //清除标志
    result= SCI_RXD();
    switch(result)
    {
      case 'p':							 //增加P1值
       Prop1=Prop1+1;
     sprintf(SCIreceive,"Proportion1值为:%.2f%.2f%.2f%.2f",Prop1,Prop2,Diff1,Diff2);  
     SCISend_chars(SCIreceive);    
      break;
      case 'c':                          //清屏
   sprintf(SCIreceive,"Proportion2值为:%d%d",abs(SpeedMin),SpeedMin);            
    SCISend_chars(SCIreceive);
    //LCD_clear();
      break;
      case 'n':
      sprintf(SCIreceive,"P1:%.2f P2:%.2f D1:%.2f D2:%.2f\n最大速度:%d\n最小速度:%d\n当前速度:%d\n平均速度:%.2f\n",Prop1,Prop2,Diff1,Diff2,SpeedMax,SpeedMin,SpeedNow,SpeedAver);
      SCISend_chars(SCIreceive);
       break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT