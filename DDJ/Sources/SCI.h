/*--------------------------------------------
    Date:       2011.04.11
    Update:     2011.06.02
	说明：串口调用及无线模块
----------------------------------------------*/
int SCI_i=0;
int *SCI_PWMDTY,*SCI_DP;
byte test_info_send=1;
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
	SCISend_chars("SEDJG");
    for(i=LASER_MAX-1;i>=0;i--)    //发送激光管信息数组
        {data=temp_laser_array[i]  ;
            if(data == 0) {
            SCISend('0');   
            }
        else if(data == 1) {
             SCISend('1'); 
        }
        } 
    SCISend_chars("END");
    SCISend('\n'); 		
}     
/*---------------------------------------
发送红外信息数组（不成熟，暂不使用）
编写日期：200110607
----------------------------------------- */ 
void TestIR(byte temp_laser_array[]) {
    int i; 
    char data[5];
	SCISend_chars("SEDIR");
    for(i=0;i<=6;i++)    //发送激光管信息数组
        {  
    (void)sprintf(data,"%.1d",temp_laser_array[i]);
		SCISend_chars(data);
        }
		SCISend_chars("END");
	    SCISend('\n'); 	
}      
/*---------------------------------------
发送相关参数
编写日期：2001100607
-----------------------------------------  */ 
void Testpara(int test_sdj,int test_xdj,int test_speed,int test_position) {
char SCIsenddata[50];
	(void)sprintf(SCIsenddata,"SEDPR%.5d%.4d%.4d%.4dEND",test_position+10000,test_sdj,test_xdj,test_speed);
    SCISend_chars(SCIsenddata);  
    SCISend('\n');  
}  
/*---------------------------------------
无线模块发送总函数
编写日期：200110602
参数 t：用于循环几次发送一次
-----------------------------------------  */  
void TestSMinfo(byte a){
if(a!=0){
Testjiguang(light_temp_laser_array);	//发送激光数组
Testpara(PWMDTY45,PWMDTY01,speed_clear[1],JG_clear[3]);//发送相关参数
TestIR(IR_temp_laser_array);
}
}
/*---------------------------------------
无线模块接收处理
编写日期：200110611
参数  command：填入字符串处理
-----------------------------------------  */ 
void SCI_REC_chuli(char a[],int x)
{
	char *p;
	char *q;
	switch(x){
  case 1:{
	p = strtok(a, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP1=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP2=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP3=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP4=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP5=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP6=*SCI_DP;} 
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);DP7=*SCI_DP;}
  }
  break; 
  case 3:{
	p = strtok(a, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP1=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP2=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP3=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP4=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP5=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP6=*SCI_DP;} 
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP7=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP8=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP9=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BP10=*SCI_DP;}
  }
  break;
  case 4:{
	p = strtok(a, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD1=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD2=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD3=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD4=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD5=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD6=*SCI_DP;} 
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD7=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD8=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD9=*SCI_DP;}
	p = strtok(NULL, ";");
	if(*p!='F'){*SCI_DP=atoi(p);BD10=*SCI_DP;}
  }
  break; 
	case 2:{
	q = strtok(a, ";"); 
	{
	  *SCI_PWMDTY=atoi(q); 
  PWMDTY01=*SCI_PWMDTY;
	}
	q = strtok(NULL, ";"); 
	{
	  *SCI_PWMDTY=atoi(q);
	PWMDTY23=*SCI_PWMDTY;
	}
	}   
	break;
	}
}
/*---------------------------------------
无线模块返回当前参数值
编写日期：200110612
-----------------------------------------  */ 
void SCI_REC_NOW(){
char SCIsend[80];
/*	(void)sprintf(SCIsend,"DP值:%.3d %.3d %.3d %.3d %.3d %.3d %.3d",DP1,DP2,DP3,DP4,DP5,DP6,DP7);		
  SCISend_chars(SCIsend);*/
  SCISend('\n');  
  (void)sprintf(SCIsend,"BP值:%.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d %.2d",BP1,BP2,BP3,BP4,BP5,BP6,BP7,BP8,BP9,BP10);		
  SCISend_chars(SCIsend);
  SCISend('\n');  
  (void)sprintf(SCIsend,"BD值:%.3d %.3d %.3d %.3d %.3d %.3d %.3d %.3d %.3d %.3d",BD1,BD2,BD3,BD4,BD5,BD6,BD7,BD8,BD9,BD10);		
  SCISend_chars(SCIsend);
  SCISend('\n');  
  (void)sprintf(SCIsend,"舵机值:%.4d%.4d",PWMDTY01,PWMDTY45);		
  SCISend_chars(SCIsend);
  SCISend('\n');  
  SCISend('\n');   
}

/*---------------------------------------
无线串口中断接收
编写日期：20110411
-----------------------------------------*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SCI(void)
{
    DisableInterrupts; 
      	test_info_send=0;
      SCIreceive[SCI_i]=SCI_RXD();
      switch(SCIreceive[SCI_i]) {
        case '@': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,1);  //调节DP
        }  
        break;
        case '&': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,3); //调节BP
        }  
        break;
        case '!': 
        {
          SCI_i=0;
          SCI_REC_chuli(SCIreceive,4); //调节BD
        }  
        break;
        case '$': 
        {
          SCI_i=0;
          SCI_REC_NOW();               //反馈回值
        }  
        break;
        case '#': 
        {
          SCI_i=0;
         SCI_REC_chuli(SCIreceive,2);   //调节上下舵机值
        }
        break;
        case '%': 
        {
          SCI_i=0;
      test_info_send=1; 
        }
        break;
      default:
        SCI_i++;
         break; 
      }
    EnableInterrupts;
} 
#pragma CODE_SEG DEFAULT