/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
	说明：串口调用及无线模块
----------------------------------------------*/
int test_sdj,test_xdj,test_speed,test_position;
long test_IR_position;
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
 int i=0;
 do{
 SCISend(ch[i]);
 i++;
 }while(ch[i]!='\0');
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
发送激光管信息数组
编写日期：200110602
-----------------------------------------  */ 
void Testjiguang(byte temp_laser_array[]) {
    int i; 
    int data;
    for(i=LASER_MAX-1;i>=0;i--)    //发送激光管信息数组
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        }   
}     
/*---------------------------------------
发送红外信息数组（不成熟，暂不使用）
编写日期：200110602
-----------------------------------------  */  
/*void TestIR(byte temp_laser_array[]) {
    int i; 
    int data;
    for(i=0;i<=6;i++)    //发送激光管信息数组
        {data=temp_laser_array[i];
		SCISend_chars(data);
        }   
		data=IR_position[1]+10;
		SCISend_chars(data);
}      */

/*---------------------------------------
无线模块发送总函数
编写日期：200110602
参数 t：用于循环几次发送一次
-----------------------------------------  */  
void TestSMinfo(void){
   test_sdj=temp_pwm67;		//上舵机的值
    test_xdj=temp_pwm45;		//下舵机的值
	test_speed=g_temp_pulse;	//速度值
	test_position=JG_clear[1];		//激光滤波值
//	test_IR_position=IR_position[1]+10;	//红外滤波值
	SCISend_chars("SED");		//发送标识符
	Testjiguang(light_temp_laser_array);	//发送激光数组
   (void)sprintf(SCIreceive,"%.5d%.4d%.4d%.4dEND",test_position+10000,test_sdj,test_xdj,test_speed);
   /*%.3d%.3d%.3d%.3d%.3d%.3d%.3d%.3d*/
   /*,IR_temp_laser_array[0],IR_temp_laser_array[1],IR_temp_laser_array[2],IR_temp_laser_array[3],IR_temp_laser_array[4],IR_temp_laser_array[5],IR_temp_laser_array[6],test_IR_position*/
   SCISend_chars(SCIreceive);
   SCISend('\n');
  }