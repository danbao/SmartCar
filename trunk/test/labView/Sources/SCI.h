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
激光状态转换为16进制
编写日期：200110521
-----------------------------------------  */         
void Testjiguang(byte a[12]) 
{ 
char b[3]; 
int i,result = 0,k = 1,j = 0; 
for(i = 11;i >= 0;i --) 
{ 
if(a[11-i] == '1') result += 1 << (k-1); //如果是1，用1*位权 
if(k == 4 || i == 0) //每四位计算一次结果（result）。 
//如果到了最高位（i==0）不足四位（比如100 0000），也计算 
{ 
switch(result) 
{ 
case 10: b[j++]='A';break; //大于等于十转化成字母 
case 11: b[j++]='B';break; 
case 12: b[j++]='C';break; 
case 13: b[j++]='D';break; 
case 14: b[j++]='E';break; 
case 15: b[j++]='F';break; 
default: b[j++]=result + '0';break; 
} 
result = 0; //结果清零 
k = 0; //表示位权的K清零 
} 
k ++; // 初始位权为1 
}
for(i = 2;i >= 0;i --) 
jiguang[2-i]=b[i];
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
/*=====================激光摆头滤波======================*/

void Clear_baitou(void){
int clear_position;
clear_position=position*100;
JG_clear_position=(JG_clear_position*40+clear_position*100) /140 ;  
}

void TestSMinfo(){
    sdj=rand()%10000;
    xdj=rand()%10000;
	speed=rand()%10000;
	Testjiguang(light_temp_laser_array);
//	Testhongwai(IR_temp_laser_array);
  Clear_baitou();
    sprintf(SCIreceive,"SED%d",JG_clear_position);
    SCISend_chars(SCIreceive);
    }
