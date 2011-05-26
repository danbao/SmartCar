/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.04.11
	说明：串口调用及无线模块
----------------------------------------------*/
char jiguang[3],hongwai[28];
int sdj,xdj,speed;
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
激光状态转换为16进制
编写日期：200110521
-----------------------------------------  */         
void Testjiguang(byte temp_laser_array[]) 
{ 
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
}

/*---------------------------------------
红外状态转换为16进制
编写日期：200110521
-----------------------------------------  */   
void Testhongwai(float a[]) {
int i,tmp;
char *p;
p=hongwai;
for (i=0;i<7;i++)
{
		tmp = (int)(a[i]*1000+0.5);	//转换成整型值
		sprintf(p, "%04d", tmp);//转换成16进制字符串
		p+=4;
}   
}

void TestSMinfo(){
	SCISend_chars("SED");
	Testjiguang(light_temp_laser_array);
	Clear_baitou();
  sprintf(SCIreceive,"%4d",JG_clear_position);
  SCISend_chars(SCIreceive);
	SCISend('\n');
    }
