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

void SendSmartcarInfo(byte temp_laser_array[]) {
    int i; 
    int data;
    char g[20]=" ";
    for(i=LASER_MAX-1;i>=0;i--)    //发送激光管信息数组
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        }
//  SCISend('\n');
 // sprintf(g,"%u",p);
  //for(i=0;g[i]!='\0';i++)
  //SCISend(g[i]);  
     
}
 #pragma CODE_SEG __NEAR_SEG NON_BANKED 
//===================摆头舵机中断================//

interrupt 20 void Rx_SetDriver(void)
{
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1;                   //清除标志
    result= SCI_RXD();
    switch(result)
    {
			case 'q':                          //激光摆头舵机向右偏参数
    temp_pwm67=temp_pwm67+5;
    Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"当前摆头舵机值为:%d",temp_pwm67);  
     SCISend_chars(SCIreceive);   
      break;
            case 'w':                   //激光摆头舵机向左偏参数
        temp_pwm67=temp_pwm67-5;
		Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"当前摆头舵机值为:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
			case 'a':                          //激光摆头舵机向右偏参数
        temp_pwm67=temp_pwm67+1;
		Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"当前摆头舵机值为:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
            case 's':                   //激光摆头舵机向左偏参数
        temp_pwm67=temp_pwm67-1;
		Light_SetDriver(temp_pwm67);
    sprintf(SCIreceive,"当前摆头舵机值为:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
            case 'z':                      //激光摆头舵机重置
        temp_pwm67=PWM67; 
		Light_SetDriver(temp_pwm67);
		sprintf(SCIreceive,"摆头舵机复位，当前舵机值为:%d",temp_pwm67);  
     SCISend_chars(SCIreceive); 
      break;
            case 'o':                          //转向摆头舵机向左偏参数 5度档
        temp_pwm45=temp_pwm45+5;
        SCI_SetDriver(temp_pwm45);
		sprintf(SCIreceive,"当前转角舵机值为:%d",temp_pwm45);  
     SCISend_chars(SCIreceive); 
      break;
            case 'p':                         //转向摆头舵机向右偏参数 5度档
        temp_pwm45=temp_pwm45-5;
        SCI_SetDriver(temp_pwm45);
		sprintf(SCIreceive,"当前转角舵机值为:%d",temp_pwm45);  
     SCISend_chars(SCIreceive); 
      break;
            case 'k':                          //转向摆头舵机向左偏参数 5度档
        temp_pwm45=temp_pwm45+1;
        SCI_SetDriver(temp_pwm45);
		sprintf(SCIreceive,"当前转角舵机值为:%d",temp_pwm45);  
     SCISend_chars(SCIreceive); 
      break;
            case 'l':                         //转向摆头舵机向右偏参数 5度档
        temp_pwm45=temp_pwm45-1;
        SCI_SetDriver(temp_pwm45);
		sprintf(SCIreceive,"当前转角舵机值为:%d",temp_pwm45);  
     SCISend_chars(SCIreceive); 
      break;
            case 'm':                      //转向摆头舵机重置
        temp_pwm45=PWM45; 
        SCI_SetDriver(temp_pwm45);
		sprintf(SCIreceive,"转角舵机复位，当前舵机值为:%d",temp_pwm45);  
     SCISend_chars(SCIreceive); 
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT