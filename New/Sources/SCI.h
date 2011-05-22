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
void SCISend_chars(const char ch[])
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
    tmp = SCI0SR1; 	//清除标志
    result= SCI_RXD();
    switch(result)
    {
      case '1':							 //增加P1值
      YP1=YP1+0.2;
     sprintf(SCIreceive,"摇头P1值为:%.1f",YP1);  
     SCISend_chars(SCIreceive);    
      break;
      case '2':							 //减小P1值
      YP1=YP1-0.2;    
     sprintf(SCIreceive,"摇头P1值为:%.1f",YP1);  
     SCISend_chars(SCIreceive);    
      break;
      case '3':							 //增加P2值
      YP2=YP2+0.2;
     sprintf(SCIreceive,"摇头P2值为:%.1f",YP2);  
     SCISend_chars(SCIreceive);    
      break;      
      case '4':							 //减小P2值
      YP2=YP2-0.2;
     sprintf(SCIreceive,"摇头P2值为:%.1f",YP2);  
     SCISend_chars(SCIreceive);    
      break;
      case 'e':							 //增加P3值
      YP3=YP3+0.2;
     sprintf(SCIreceive,"摇头P3值为:%.1f",YP3);  
     SCISend_chars(SCIreceive);    
      break;
      case 'd':							 //减小P3值
      YP3=YP3-0.2;
     sprintf(SCIreceive,"摇头P3值为:%.1f",YP3);  
     SCISend_chars(SCIreceive);    
      break;
      case 'r':							 //增加P4值
      YP4=YP4+0.2;
     sprintf(SCIreceive,"摇头P4值为:%.1f",YP4);  
     SCISend_chars(SCIreceive);    
      break;
      case 'f':							 //减小P4值
      YP4=YP4-0.2;
     sprintf(SCIreceive,"摇头P4值为:%.1f",YP4);  
     SCISend_chars(SCIreceive);    
      break;
      case 't':							 //增加P5值
      YP5=YP5+0.2;
     sprintf(SCIreceive,"摇头P5值为:%.1f",YP5);  
     SCISend_chars(SCIreceive);
      case 'g':							 //减小P5值
      YP5=YP5-0.2;
     sprintf(SCIreceive,"摇头P5值为:%.1f",YP5);  
     SCISend_chars(SCIreceive);      
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT