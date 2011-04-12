#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <MC9S12XS128.h>
#define LASER_MAX 15          //激光管数量
#define PWM67 224	
#define PWM01 1482
#define ANGLE_DELTA 30
#define PWM6_MID 224		

//===============全局变量定义======================//
   int temp_pwm67=PWM67;						//激光摆头舵机初始值
  int temp_pwm01=PWM01;						//转向摆头舵机初始值
  byte light_temp_laser_array[LASER_MAX];  //当前激光管信息保存数组
  int testcount=1;
  int count=1;                                  //串口接收延时
  int q_temp_laser_num[LASER_MAX];       //激光管对应的权值
  int countPIT0=0;
  int position=0;                        
  int His_ADD_Position[3];                      //步进累加值历史   His_ADD_Position[2]=aabs[1]
  int His_Position[3];                        //历史position  position[3]=position[1]-position[0] position[2]=aabs[position]
  int angle[2]; 
  int Calculate_HitBlackNum(void);
  int YaoKp ,YaoKd,ZhuanKp,ZhuanKd;
  byte lost_line_flag=0;
  int ADD_Position; 
  int Diff_Position;
  int GDiff_Position[2];                      //步进累加的值
  
//===============时钟初始化========================//

void SetBusCLK_40M()
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x04;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=80MHz;
    _asm(nop);          //BUS CLOCK=40M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}  

//=====================串口接收函数====================//
char SCI_RXD(void)
{
    char ch; 
    while (!(SCI0SR1 & 0x20));       //等待接收数据完毕
    SCI0SR1_RDRF = 1;
    ch = SCI0DRL;
    return ch;
}
//==============串口输出显示函数========================//
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

static void SCI_Init(void)  //SCI
{
    SCI0CR1=0x00;
    SCI0CR2=0x2c;
     SCI0BD=260;                    //设置波特率公式=总线频率/所需要的波特率/16=所要设置的值;
                  
}
//==============延时程序================================//
void delayms(int ms)    //延时程序。
{   
   int ii,jj;
   if (ms<1) ms=1;
   for(ii=0;ii<ms;ii++)
     for(jj=0;jj<3338;jj++);    //40MHz--1ms      
}

//==============aabs绝对值================================//
int aabs(int num) {
if (num>=0)return num;
else {
num=-num;return num;
}
}
 //=====================舵机初始化======================//
void PWM_Init(void){     		//PWM初始化。其中P4,P5控制电机正反转, P6,P7级联激光管控制舵机。

	PWME=0X00;            		//初始化，先是通道使能禁止。
	PWMPRCLK=0x11;				//预分频，A,B时钟为总线的1/2，就是Clock A和Clock B。
  
	PWMSCLA=10;            		//SA时钟设置,Clock SA=Clock A/(2*PWMSCLA)。
	PWMSCLB=35;             	//SB时钟设置,Clock SB=Clock B/(2*PWMSCLB)。
  

	PWMCLK_PCLK0=1;	
	PWMCLK_PCLK1=1;
	PWMCLK_PCLK6=1;
	PWMCLK_PCLK7=1;
  

	PWMPOL_PPOL0=1;				//转向摆头舵机极性选择设置
	PWMPOL_PPOL1=1;
	PWMPOL_PPOL6=1;				//激光摆头数字极性选择设置
	PWMPOL_PPOL7=1;
  
  PWMCTL = 0B00100000;     //通道23级联
  
	PWMCAE_CAE0=0;				//转向摆头舵机对齐方式
	PWMCAE_CAE1=0;	
	PWMCAE_CAE6=1;         		//激光摆头数字舵机对齐方式
	PWMCAE_CAE7=1;
	
  PWMCNT01 = 0;				//01口计数器清零；
  PWMCNT23 = 0;			//计数器23清零 
  
	PWMCTL=0x90;            	//控制寄存器，01和67口级联。
	
	PWMPER23 = 125;    //频率 8kHz 
	PWMPER01=20000;				//1024×1024（频率）*Clock A/2/PWMSCLB/PWMPER67
	PWMPER67=1000;				//1024×1024（频率）*Clock B/2/PWMSCLB/PWMPER67
 
	PWMDTY01=PWM01;
	PWMDTY23 = 0;      //速度为0，即静止
	PWMDTY67=PWM67;				//PWMDTY67/PWMPER67*100%
	PWME=0xff;         			//启动通道使能。
}
//=====================激光初始化======================//
 void LIGHT_Init(void){ 
	DDRA = 0B00011111;  //PA0--PA7激光管信号控制 --- 输出 
	DDRB = 0X00;        //PB0--PB8激光管信号采集 --- 输入
 }
 

//=====================激光点亮======================//
void receive(int send) {
   if(send == 0)   { 
     delayms(1); 
	    light_temp_laser_array[3] = PORTB_PB1^1;	//接收第4组（3,8,13）  
        light_temp_laser_array[8] = PORTB_PB2^1;
        light_temp_laser_array[13] = PORTB_PB4^1;
        PORTA = 0B00000001;					//点亮第0组（1,6,11）
    }   
  

   else if(send == 1)   { 
    delayms(1);
        light_temp_laser_array[0] = PORTB_PB0^1;	//接收第0组（0,5,10）   
        light_temp_laser_array[5] = PORTB_PB1^1; 
        light_temp_laser_array[10] = PORTB_PB3^1;
        PORTA = 0B00000100;					//点亮第1组（2,7,12）
        
    }
    
    else if(send ==2)   { 
     delayms(1);
		light_temp_laser_array[2] = PORTB_PB0^1;	//接收第1组（2,7,12）  
        light_temp_laser_array[7] = PORTB_PB2^1; 
        light_temp_laser_array[12] = PORTB_PB4^1;
        PORTA = 0B00010000;					//点亮第2组（4,9,14）
    } 
    else	if(send == 3)       { 
         delayms(1);
	    light_temp_laser_array[4] = PORTB_PB1^1;	//接收第2组（4,9,14） 
        light_temp_laser_array[9] = PORTB_PB3^1; 
        light_temp_laser_array[14] = PORTB_PB4^1;
     PORTA = 0B00000010;					//点亮第3组（1,6,11）
  }
   else if(send == 4)   {
       delayms(1);
        light_temp_laser_array[1] = PORTB_PB0^1;	//接收第3组（1,6,11）
        light_temp_laser_array[6] = PORTB_PB2^1; 
        light_temp_laser_array[11] = PORTB_PB3^1;	
        PORTA = 0B00001000;					//点亮第4组（3,8,13）
    } 
   
} 


/*==================排除干扰点============================
i-(7-position/2)>3    排除
不足：当这种情况连续出现 则认同
*/
void Confirm_Light(){
 int i=0;
 int halfposition=position/2;
 for(i=0;i<LASER_MAX;i++) {
  if (light_temp_laser_array[i]==0) continue;
  else if (aabs(i-(7-halfposition))>=3) light_temp_laser_array[i] =0;
  else continue;   
 }
}

/*======================lost_blackline();======================*/
void lost_blackline(void){
  int HitBlackNum;
  lost_line_flag=0;
  HitBlackNum=Calculate_HitBlackNum();
  if(HitBlackNum) {
  if (14-aabs(His_Position[2])<=3&&(aabs(His_Position[2]-position))<=2)
      lost_line_flag=0; 
   else if(14-aabs(His_Position[2])<=3&&aabs(His_Position[2]+position)<=11)
   lost_line_flag=1;
  } 
  else  
  lost_line_flag=1; 
}

/* ================= SendSmartcarInfo ====================
      desc: SCI串口发送当前激光管采集信息
      pre:  1当前激光管采集数组，2当前激光管状态
      Post: 无
       
*/ 
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


/*=====================激光管对应权值======================
LASER_MAX    14   13   12   11  10    9   8   7    6    5    4     3     2        1     0
对应的权值  -14  -12  -10   -8  -6   -4  -2   0    2    4    6      8     10       12    14
                                                 
程序未完成，必须有参数和返回值，需要建立联系！  

==========================================================*/

void Laser_num(void){
  int i;
  for(i=0;i<LASER_MAX;i++){
    q_temp_laser_num[i]=14-2*i;
  }
}

/*=====================激光管位置的判定======================

权值公式：  position= ∑（light[i]*lightnum[i]） / blacknum  
Light[i]为第i个激光的数值 0或1   ight_temp_laser_array[3]
Lightnum 为表1值   q_temp_laser_num[LASER_MAX]
blacknum为照黑个数
                                                          
==========================================================*/
int Status_Judge(void) {
  int i,temp_HitBlackNum,sum=0;
  temp_HitBlackNum=Calculate_HitBlackNum();
  for(i=0;i<LASER_MAX;i++){
    sum=sum+light_temp_laser_array[i]*q_temp_laser_num[i];
  }
  position=sum/temp_HitBlackNum;
  
  return position;
    
}

/*=====================激光管照到黑线的个数======================*/

int Calculate_HitBlackNum(void){
  int i,HitBlackNum=0;
  for(i=0;i<LASER_MAX;i++) {
    if(light_temp_laser_array[i]==1){
      HitBlackNum++;
    }
  }
  return HitBlackNum;
}
  
/*=====================激光摆头======================*/
//转向舵机：1482 1772 1204   摆头舵机：224+-90
//0.10712*x^2 + 4.5791*10^(-17)*x + 6.7084
//Diff_Position是增量pd的 加到pwm上的增量
void  baitou (void) {
   
     
    
  
    
    His_Position[1]=position;  
    
    His_Position[2]=position;
    His_Position[2]=aabs(His_Position[2]); 
    
    if(His_Position[2]>1&&His_Position[2]<=3)
    Diff_Position=(4*His_Position[1])/5;
    else if(His_Position[2]>3&&His_Position[2]<=6)
    Diff_Position=(5*His_Position[1])/4;
    else if(His_Position[2]>6&&His_Position[2]<=14)
    Diff_Position=2*His_Position[1];
    else if(His_Position[2]>6&&His_Position[2]<=10)
    Diff_Position=2*His_Position[1];
    else if(His_Position[2]>10&&His_Position[2]<=14)
    Diff_Position=(5*His_Position[1])/2;
    
  /*  else if(His_Position[3]>4&&His_Position[3]<=6)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>6&&His_Position[3]<=8)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>8&&His_Position[3]<=10)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>10&&His_Position[3]<=12)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];
    else if(His_Position[3]>12&&His_Position[3]<=14)
    Diff_Position=(1+2)*His_Position[2]-(2+2*2)*His_Position[1]+2*His_Position[0];  */
    
     His_Position[0]=His_Position[1];
     PWMDTY67=PWMDTY67+Diff_Position;
    
}

/*=======================打角舵机===========================*/
//GDiff_Position是存储 摇头舵机差值 传给打角的参数
void dajiao(void) {
    int ZhuanPwm;
    
    GDiff_Position[1]=PWMDTY67-PWM67;
   
    if(His_Position[2]>0&&His_Position[2]<=4)
    ZhuanPwm=PWM01-(position+GDiff_Position[1])*4-2*(GDiff_Position[1]-GDiff_Position[0]);
    else if(His_Position[2]>4&&His_Position[2]<=8)
    ZhuanPwm=PWM01-(position+GDiff_Position[1])*6-2*(GDiff_Position[1]-GDiff_Position[0]);
    else if(His_Position[2]>8&&His_Position[2]<=14)
    ZhuanPwm=PWM01-(position+GDiff_Position[1])*8-2*(GDiff_Position[1]-GDiff_Position[0]);
    
    
    if(ZhuanPwm>1772)
    ZhuanPwm=1772;
    else if(ZhuanPwm<1204)
    ZhuanPwm=1204;
    
    PWMDTY01=ZhuanPwm;
    GDiff_Position[0]=GDiff_Position[1]; 
  
  
  
  
  
   
   
    
  /*   His_Position[0]=His_Position[1];
     His_Position[1]=position;
     His_Position[2]=position;  
     His_Position[2]=aabs(His_Position[2]);
     His_Position[3]=His_Position[1]-His_Position[0] ;
     ADD_Position=ADD_Position+angle[0];
            
    if(ADD_Position>=120)
    ADD_Position;
    else if(ADD_Position<=-120)
    ADD_Position=-120;
    else
    PWMDTY67=ADD_Position+PWM67;
    
    His_ADD_Position[1]=ADD_Position;
    His_ADD_Position[2]=aabs(His_ADD_Position[1]);
    if( His_ADD_Position[2]>0&& His_ADD_Position[2]<=15)
    ZhuanPwm=PWM01-(-position+His_ADD_Position[1])*4-2*(-His_Position[3]+His_ADD_Position[1]-His_ADD_Position[0]);
    else if( His_ADD_Position[2]>15&&His_ADD_Position[2]<=25)
    ZhuanPwm=PWM01-(-position+His_ADD_Position[1])*7-2*(-His_Position[3]+His_ADD_Position[1]-His_ADD_Position[0]);
    else if( His_ADD_Position[2]>25&& His_ADD_Position[2]<=35)
    ZhuanPwm=PWM01-(-position+His_ADD_Position[1])*7-2*(-His_Position[3]+His_ADD_Position[1]-His_ADD_Position[0]);
    else if( His_ADD_Position[2]>35&&His_ADD_Position[2]<=50)
    ZhuanPwm=PWM01-(-position+His_ADD_Position[1])*7-2*(-His_Position[3]+His_ADD_Position[1]-His_ADD_Position[0]);
    else if( His_ADD_Position[2]>50&& His_ADD_Position[2]<=70)
    ZhuanPwm=PWM01-(-position+His_ADD_Position[1])*6-2*(-His_Position[3]+His_ADD_Position[1]-His_ADD_Position[0]);
    else if( His_ADD_Position[2]>70)
    ZhuanPwm=PWM01-(-position+His_ADD_Position[1])*5-2*(-His_Position[3]+His_ADD_Position[1]-His_ADD_Position[0]);
    
    His_ADD_Position[0]=His_ADD_Position[1];
    if(ZhuanPwm>1772)
    ZhuanPwm=1772;
    else if(ZhuanPwm<1204)
    ZhuanPwm=1204;
    
    PWMDTY01=ZhuanPwm;
    //PWMDTY01=PWM01-(ADD_Position+position)*3;
    
    */
} // DerectionCtrl

//【type declaration】
/* ============== 激光管状态枚举类型 LASER_STATUS ================ 
 LEFT_NONE (0) ------ 左空     
     LEFT0 (1) ------ 左0      LEFT01 (2) ------ 左0左1     
     LEFT1 (3) ------ 左1      LEFT12 (4) ------ 左1左2
     LEFT2 (5) ------ 左2      LEFT23 (6) ------ 左2左3    
     LEFT3 (7) ------ 左3      LEFT34 (8) ------ 左3左4
     LEFT4 (9) ------ 左4      LEFT45 (10) ------左4左5    
     LEFT5 (11) ------左5      LEFT56 (12) ------左5左6
     LEFT6 (13) ------左6      LEFT67 (14) ------左6左7 
 MID7 (15) ------ 中7          
     RIGHT78 (16) ------右16        RIGHT8 (17) ------右8    
     RIGHT89 (18) ------右8右9      RIGHT9 (19) ------右9         
    RIGHT910 (20) ------右9右10    RIGHT10 (21) ------右10    
   RIGHT1011 (22) ------右10右11   RIGHT11 (23) ------右11        
   RIGHT1112 (24) ------右11右12   RIGHT12 (25) ------右12    
   RIGHT1213 (26) ------右12右13   RIGHT13 (27) ------右13        
   RIGHT1314 (28) ------右13右14   RIGHT14 (29) ------右14 
  RIGHT_NONE (30) ------右空  
*/    



/*=====================计算激光/转向 摆头的角度值======================*/
//27  23  21  20  18  17 16 14 12 11 10  9  7  1 0
void CalculateAngle(int i) {
  // Local Declarations
  int light_micro_delta0 = 0;   /*激微调0*/    int Steering_micro_delta0 = 10;  /*向微调0*/
  int light_micro_delta1 = 1;  /*激微调1*/     int Steering_micro_delta1 = 15;  /*向微调0*/
  int light_micro_delta2 = 1;  /*激微调2*/     int Steering_micro_delta2 = 30;  /*向微调0*/
  int light_micro_delta3 = 1;  /*激微调3*/     int Steering_micro_delta3 = 50;  /*向微调0*/
  int light_micro_delta4 = 2;  /*激微调4*/     int Steering_micro_delta4 = 60;  /*向微调0*/
  int light_micro_delta5 = 2;  /*激微调5*/     int Steering_micro_delta5 = 70;  /*向微调0*/
  
  int light_mid_delta0 = 2;  /*激中调0*/       int Steering_mid_delta0 = 80;  /*向中调0*/
  int light_mid_delta1 = 2; /*激中调1*/        int Steering_mid_delta1 = 90;  /*向中调1*/
  int light_mid_delta2 = 2; /*激中调2*/        int Steering_mid_delta2 = 100;  /*向中调2*/
  int light_mid_delta3 = 2; /*激中调3*/        int Steering_mid_delta3 = 110;  /*向中调3*/
  int light_mid_delta4 = 2; /*激中调4*/        int Steering_mid_delta4 = 120;  /*向中调4*/
  
  int light_large_delta0 = 2; /*激大调0*/      int Steering_large_delta0 = 130; /*向大调0*/
  int light_large_delta1 = 2; /*激大调1*/      int Steering_large_delta1 = 140; /*向大调1*/
  int light_large_delta2 = 2; /*激大调2*/      int Steering_large_delta2 = 150; /*向大调2*/
  int light_large_delta3 = 2; /*激大调3*/      int Steering_large_delta3 = 160; /*向大调3*/
 
  
  // Statements
  switch( i ) {
      case  15:   {
          angle[0] =light_large_delta3;
          angle[1] =-Steering_large_delta3;
          break;
      }
      case  14:  {
          angle[0] =light_large_delta2;  
          angle[1] =-Steering_large_delta2;
          break;
      }
      case  13:  {
          angle[0] =light_large_delta1; 
          angle[1] =-Steering_large_delta1;
          break;
      }
      case  12 : {
          angle[0] =light_large_delta0;
          angle[1] =-Steering_large_delta0;
          break;
      }
      case  11:   {
          angle[0] =light_mid_delta4;
          angle[1]=-Steering_mid_delta4;
          break;
      }
      case  10:  {
          angle[0] =light_mid_delta3;
          angle[1]=-Steering_mid_delta3;
          break;
      }
      case  9:  {
          angle[0] =light_mid_delta2;
          angle[1]=-Steering_mid_delta2;
          break;
      }
      case  8: {
          angle[0] =light_mid_delta1; 
          angle[1]=-Steering_mid_delta1;
          break;
      }
      case  7:   {
          angle[0] =light_mid_delta0; 
          angle[1]=-Steering_mid_delta0;
          break;
      }
      case  6:  {
          angle[0] =light_micro_delta5; 
          angle[1]=-Steering_micro_delta5;
          break;
      }
      case  5:  {
          angle[0] =light_micro_delta4; 
          angle[1]=-Steering_micro_delta4;
          break;
      }
      case  4: {
          angle[0] =light_micro_delta3; 
          angle[1]=-Steering_micro_delta3;
          break;
      }
      case  3:   {
          angle[0] =light_micro_delta2; 
          angle[1]=-Steering_micro_delta2;
          break;
      }
      case  2:  {
          angle[0] =light_micro_delta1; 
          angle[1]=-Steering_micro_delta1;
          break;
      }
      case  1:   {
          angle[0] =light_micro_delta0; 
          angle[1]=-Steering_micro_delta0;
          break;
      }
      case  0:  {
          angle[0] = 0;
          angle[1]=0;
          break;
      }
      case  -1:   {
          angle[0] = -light_micro_delta0; 
          angle[1]= Steering_micro_delta0;
          break;
      }
      case  -2:  {
          angle[0] =- light_micro_delta1; 
          angle[1]= Steering_micro_delta1;
          break;
      }                 
      case  -3:   {
          angle[0] = -light_micro_delta2; 
          angle[1]= Steering_micro_delta2;
          break;
      }
      case  -4:  {
          angle[0] = -light_micro_delta3; 
          angle[1]= Steering_micro_delta3;
          break;
      }
      case  -5:   {
          angle[0] = -light_micro_delta4; 
          angle[1]= Steering_micro_delta4;
          break;
      }
      case  -6:  {
          angle[0] = -light_micro_delta5; 
          angle[1]= Steering_micro_delta5;
          break;
      }
      case  -7:  {
          angle[0] = -light_mid_delta0; 
          angle[1]= Steering_mid_delta0;
          break;
      }
      case  -8:  {
          angle[0] =  -light_mid_delta1; 
          angle[1]= Steering_mid_delta1;
          break;
      }
      case  -9:   {
          angle[0] =  -light_mid_delta2; 
          angle[1]= Steering_mid_delta2;
          break;
      } 
      case  -10:  {
          angle[0] =  -light_mid_delta3; 
          angle[1]= Steering_mid_delta3;
          break;
      }
      case  -11:   {
          angle[0] = -light_mid_delta4; 
          angle[1]= Steering_mid_delta4;
          break;
      } 
      case  -12:  {
          angle[0] =  -light_large_delta0; 
          angle[1] = Steering_large_delta0;
          break;
      }
      case  -13: {
          angle[0] =  -light_large_delta1; 
          angle[1] = Steering_large_delta1;
          break;
      }
      case  -14:{
          angle[0] =  -light_large_delta2; 
          angle[1] = Steering_large_delta2;
          break;
      }
      case  -15:{
          angle[0] =  -light_large_delta3; 
          angle[1] = Steering_large_delta3;
          break;
      }
      default: break;
  }  
  
  //return *angle;    
} //CalculateAngle

//=====================激光摆头舵机改变函数======================//
void Light_SetDriver(int value){
  PWMDTY67 = value; 
}
void SCI_SetDriver(int value){
  PWMDTY01 = value; 
}
void SpeedCtrl (void) {
PWMDTY23=84;
}

void main(void) {
  int i;

     
  int temp_laserStatus;           //定义一个数组用来接受 上下舵机值
  EnableInterrupts;
  SetBusCLK_40M();    //   设置时钟初始化。40MHz.
  PWM_Init();
  LIGHT_Init();
  delayms(2);
  Laser_num();
   SCI_Init();
  for(i=0;;i++) {
    if(i == 5) 
    {i = 0;
   // Confirm_Light();    
   //   count++;
  //         if(count%20==0){  
  //            count=1; 
 //  SendSmartcarInfo(light_temp_laser_array);
 //   SCISend('\n');    
 //            }         
     temp_laserStatus = Status_Judge();
     CalculateAngle(temp_laserStatus); //得到舵机需要调整的转角      
   testcount++;
   if(testcount%15==0){
       testcount=1;
    baitou( );
   }
     dajiao();
     SpeedCtrl();
     receive(i);
    } else receive(i);
  }
// _FEED_COP(); /*看门狗，防死循环用的 */
 /* loop forever */
  /* please make sure that you never leave main */
}
//===================摆头舵机中断================//
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
interrupt 20 void Rx_SetDriver(void)
{
    char tmp;
    char result;
    DisableInterrupts;
    tmp = SCI0SR1;                   //清除标志
    result= SCI_RXD();
    switch(result)
    {
      case 'd':                          //激光摆头舵机向右偏参数
        temp_pwm67=temp_pwm67+1;
        Light_SetDriver(temp_pwm67);
       SCISend('d'); 
      break;
            case 'a':                   //激光摆头舵机向左偏参数
        temp_pwm67=temp_pwm67-1;
        Light_SetDriver(temp_pwm67);
       SCISend('a'); 
      break;
            case 'r':                      //激光摆头舵机重置
        temp_pwm67=PWM67; 
        Light_SetDriver(temp_pwm67);
       SCISend('r');
      break;
            case 'j':                          //转向摆头舵机向左偏参数 5度档
        temp_pwm01=temp_pwm01+5;
        SCI_SetDriver(temp_pwm01);
       SCISend('j'); 
      break;
            case 'l':                         //转向摆头舵机向右偏参数 5度档
        temp_pwm01=temp_pwm01-5;
        SCI_SetDriver(temp_pwm01);
       SCISend('l'); 
      break;
            case 'n':                          //转向摆头舵机向左偏参数 5度档
        temp_pwm01=temp_pwm01+1;
        SCI_SetDriver(temp_pwm01);
       SCISend('n'); 
      break;
            case 'm':                         //转向摆头舵机向右偏参数 5度档
        temp_pwm01=temp_pwm01-1;
        SCI_SetDriver(temp_pwm01);
       SCISend('m'); 
      break;
            case 'p':                      //转向摆头舵机重置
        temp_pwm01=PWM01; 
        SCI_SetDriver(temp_pwm01);
       SCISend('p');
      break;
    }
    EnableInterrupts;
}
#pragma CODE_SEG DEFAULT